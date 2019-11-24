#include <iostream>

#include "strategy.h"

using std::cout;
using std::endl;

struct Config {
    double elecProp;
    double entryPrice;
    double quantity;
    double durationInDays;

    struct {
        double hProp;
    } holding;

    struct {
        double pProp;
        PledgeType type;
    } pledge;

    struct {
        double cProp;
    } contract;
};

Strategy::Strategy(double elecProp, double entryPrice, double quantity, double hProp,
        double pProp, double cProp, PledgeType pType, unsigned short durationInDays,
        double tradeFee, double leverage, ContractSide cSide) : m_elecProp(elecProp),
        m_entryPrice(entryPrice), m_initQty(quantity), m_pledgeDuration(durationInDays)
{
    m_elecQty = elecProp * m_initQty;

    initHolding(tradeFee);
    initPledge(pProp, pType);
    initContract(cProp, leverage, cSide);



    payElecFee();

    //TODO: change m_pledge to real days
    m_pledgePast = m_pledgeDuration;

}

Strategy::~Strategy() {
    delete m_holding;
    delete m_pledge;
    delete m_contract;
}

double Strategy::getQty(double price) const
{
    return m_holdingQty +
           m_usdtQty / price +
           m_pledgeQty * m_pledge->getROEPct(m_entryPrice, price, m_pledgePast) +
           m_contractQty * m_contract->getROEPct(m_entryPrice, price);
}

void Strategy::sell(double targetQty, double price) {
    double quantity = m_holding->getTradeQty(targetQty);
    if (quantity > m_holdingQty) {
        cout << "Failed to sell the desired quantity. Insufficient holding balance!\n"
             << "Need: " << quantity << endl
             << "Holding: " << m_holdingQty << endl;
        exit(-1);
    }
    m_holdingQty -= quantity;
    m_usdtQty += targetQty * price;
}

void Strategy::purchase(double targetQty, double price) {
    double quantity = m_holding->getTradeQty(targetQty);
    double usdtQty= quantity * price;

    if (usdtQty < m_usdtQty) {
        cout << "Failed to purchase the desired quantity. Insufficient usdt balance!\n"
             << "Need: " << quantity << " usdt" << endl
             << "USDT Balance: " << m_usdtQty << " usdt" << endl;
        exit(-1);
    }
    m_usdtQty -= usdtQty;
    m_holdingQty += targetQty;
}

void Strategy::initHolding(double tradeFee) {
    m_holding = new Holding(tradeFee);
    m_holdingQty = m_initQty;
}

void Strategy::initPledge(double pProp, PledgeType pType) {
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
    if (pledgeQty > m_holdingQty) {
        cout << "Failed to initiate pledge. Insufficient holding balance\n";
    }
    m_pledgeQty += pledgeQty;
    m_holdingQty -= pledgeQty;
    m_usdtQty += m_pledge->getInitCollaLevel() * m_pledgeQty * m_entryPrice;
}

void Strategy::initContract(double cProp, double leverage, ContractSide cSide) {
    m_contract = new Contract(leverage, cSide);
    double contractQty = cProp * m_initQty;
    if (contractQty > m_holdingQty) {
        cout << "Failed to initiate contract. Insufficient holding balance\n";
    }
    m_contractQty += contractQty;
    m_holdingQty -= contractQty;
}

void Strategy::payElecFee() {
    sell(m_elecQty, m_entryPrice);
    m_usdtQty -= m_elecQty * m_entryPrice;
}
