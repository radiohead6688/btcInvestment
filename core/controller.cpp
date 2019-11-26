#include <iostream>

#include "controller.h"

using std::cout;
using std::endl;

struct Config {
    double elecProp;
    double entryPrice;
    double quantity;
    double durationInDays;

    struct {
        double tProp;
    } trade;

    struct {
        double pProp;
        PledgeType type;
    } pledge;

    struct {
        double cProp;
    } contract;
};

Controller::Controller(double elecProp, double entryPrice, double quantity, double tProp,
        double pProp, double cProp, PledgeType pType, unsigned short durationInDays,
        double tradeFee, double leverage, ContractSide cSide, double netRefiilTimesLimit)
        : m_elecProp(elecProp), m_entryPrice(entryPrice), m_initQty(quantity),
        m_pledgeDuration(durationInDays), m_balance(quantity), m_elecQty(elecProp * quantity),
        m_netRefillTimesLimit(netRefiilTimesLimit)
{
    initTrade(tProp, tradeFee);
    initPledge(pProp, pType);
    initContract(cProp, leverage, cSide);

    payElecFee();

    cout << "Balance: " << m_balance << endl;

    //TODO: change m_pledge to real days
    m_pledgePast = m_pledgeDuration;
}

Controller::~Controller() {
    delete m_trade;
    delete m_pledge;
    delete m_contract;
}

double Controller::getQty(double price) const {
    return m_balance
           + m_usdtBalance/ price
           + m_pledgeQty * m_pledge->getROEPct(m_entryPrice, price, m_pledgeQty, m_initPledgeQty,
                   m_pledgePast)
           + m_contractQty * m_contract->getROEPct(m_entryPrice, price);
}

void Controller::sell(double targetQty, double price) {
    if (targetQty == 0) {
        return;
    }

    double quantity = m_trade->getTradeQty(targetQty);
    if (quantity > m_balance) {
        cout << "Failed to sell the desired quantity. Insufficient balance!\n"
             << "Need: " << quantity << endl
             << "Balance: " << m_balance << endl;
        exit(-1);
    }

    m_balance -= quantity;
    m_usdtBalance += targetQty * price;

    cout << "Sold " << quantity << " btc at price " << price
         << " for " << targetQty * price << " usdt.\n";
}

void Controller::purchase(double targetQty, double price) {
    if (targetQty == 0) {
        return;
    }

    double quantity = m_trade->getTradeQty(targetQty);
    double usdtQty = quantity * price;

    if (usdtQty < m_usdtBalance) {
        cout << "Failed to purchase the desired quantity. Insufficient usdt balance!" << endl
             << "Need: " << quantity << " usdt" << endl
             << "USDT Balance: " << m_usdtBalance << " usdt" << endl;
        exit(-1);
    }
    m_usdtBalance -= usdtQty;
    m_balance += targetQty;

    cout << "Purchased " << targetQty << " btc at price " << price
         << " using " << quantity * price << " usdt." << endl;
}

void Controller::initTrade(double tProp, double tradeFee) {
    m_trade = new Trade(tradeFee);
    sell(m_initQty * tProp, m_entryPrice);
}

void Controller::initPledge(double pProp, PledgeType pType) {
    switch (pType) {
        case PledgeType::BabelPledgeType:
            m_pledge = new BabelPledge();
            break;
        case PledgeType::GateioPledgeType:
            m_pledge = new GateioPledge();
            break;
        case PledgeType::MatrixportPledgeType:
            break;
        default:
            break;
    }

    double pledgeQty = pProp * m_initQty;
    if (pledgeQty > m_balance) {
        cout << "Failed to initiate pledge. Insufficient balance" << endl
             << "Need: " << pledgeQty << endl
             << "Balance: " << m_balance << endl;
        exit(-1);
    }
    m_balance -= pledgeQty;
    m_pledgeQty += pledgeQty;
    m_initPledgeQty = m_pledgeQty;
    m_usdtBalance += m_pledge->getInitCollaLevel() * m_pledgeQty * m_entryPrice;
}

void Controller::initContract(double cProp, double leverage, ContractSide cSide) {
    m_contract = new Contract(leverage, cSide);
    double contractQty = cProp * m_initQty;
    if (contractQty > m_balance) {
        cout << "Failed to initiate contract. Insufficient balance" << endl
             << "Need: " << contractQty << endl
             << "Balance: " << m_balance << endl;
        exit(-1);
    }
    m_balance -= contractQty;
    m_contractQty += contractQty;
}

void Controller::payElecFee() {
    double elecFee = m_elecQty * m_entryPrice;
    if (elecFee > m_usdtBalance) {
        cout << "Failed to pay electricity fee. Insufficient usdt balance" << endl
             << "Need: " << elecFee << endl
             << "USDT Balance: " << m_usdtBalance << endl;
        exit(-1);
    }
    m_usdtBalance -= elecFee;
    cout << "Paid electricity fee of " << elecFee << " usdt" << endl;
}

void Controller::increasePledge(double quantity) {
    if (quantity > m_balance) {
        cout << "Failed to increase pledge. Insufficient balance" << endl
             << "Need: " << quantity << endl
             << "Balance: " << m_balance << endl;
        return;
    }
    m_balance -= quantity;
    m_pledgeQty += quantity;
}

void Controller::refillPledge() {
    if (m_refilledTimes - m_refundedTimes > m_netRefillTimesLimit) {
        cout << "Already refilled " << m_refilledTimes - m_refundedTimes << " times." << endl;
        return;
    }
    double refillQty = m_initPledgeQty *
        m_pledge->getRefillRatio(m_refilledTimes - m_refundedTimes);
    increasePledge(refillQty);
    m_refilledTimes += 1;
    cout << "Refilled pledge with " << refillQty << " btc." << endl;
}

void Controller::endPledge(double price) {
    if (m_pledgeQty == 0) {
        return;
    }

    double quantity = m_pledgeQty *
        m_pledge->getROEPct(m_entryPrice, price, m_pledgePast, m_pledgeQty, m_initPledgeQty);
    m_pledgeQty = 0;
    m_balance += quantity;
    cout << "Ended pledge. Get " << quantity << " btc back." << endl;
}

void Controller::pledgeLiquidated() {
    m_pledge = 0;
    cout << "Pledge liquidated :(" << endl;
}

