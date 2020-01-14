#include <iostream>

#include "pledge.h"
#include "portfolio.h"
#include "exception.h"

using std::cout;
using std::endl;

PledgeBase::PledgeBase(double icl, double mrfil, double ll, double air) :
    m_initCollaLevel(icl), m_refillLevel(mrfil), m_liqLevel(ll),
    m_annualizedInterestsRate(air) {

    m_dailyInterests = m_annualizedInterestsRate / 365;

    m_liqPriceRatio = m_initCollaLevel / m_liqLevel;

    m_refillPriceRatio1 = m_initCollaLevel / m_refillLevel;
    m_refillCollaRatio1 = (1 / m_refillPriceRatio1) - 1;
    m_liqPriceRatio1 = m_initCollaLevel / (m_liqLevel * (m_refillCollaRatio1 + 1));

    m_refillPriceRatio2 = m_initCollaLevel / (m_refillLevel * (m_refillCollaRatio1 + 1));
    m_refillCollaRatio2 = (1/m_refillPriceRatio2) - 1;
    m_liqPriceRatio2 = m_initCollaLevel / (m_liqLevel * (m_refillCollaRatio2 + 1));
}

/*
 * @brief Returns real time quantity at given price
 * @param entryPrice        entry price
 * @param price             current price
 * @param currQty           current pledge quantity
 * @param initQty           initial pledge quantity
 * @param duration          pledge duration
 * @param netRefilledTimes  net refill times
 * @return Returns real time quantity at given price
 * @TODO correct the ratio
 */
//double PledgeBase::getQty(double entryPrice, double price, double currQty, double initQty,
        //unsigned short duration, unsigned short netRefilledTimes) const {
    //if (price == 0 || currQty == 0) {
        //return 0.0;
    //}

    //if ((price / entryPrice) <= getLiqPriceRatio(netRefilledTimes)) {
        //return 0.0;
    //}

    //return currQty - m_initCollaLevel * (entryPrice / price) * initQty
            //* (1 + duration * m_dailyInterests);
//}

BabelPledge::BabelPledge() : PledgeBase(0.6, 0.8, 0.9, 0.0888) {
    //cout.precision(8);
    //cout << std::fixed
         //<< "Babel PledgeBase:" << endl
         //<< "daily interests: " << m_dailyInterests << endl
         //<< "refill price: " << m_refillPriceRatio1 << endl
         //<< "liquidation price: " << m_liqPriceRatio << endl
         //<< "refill ratio: " << m_refillCollaRatio1 << endl
         //<< "liquidation price after refill: " << m_liqPriceRatio1 << endl
         //<< "refund price: " << m_refundPriceRatio1 << endl
         //<< "second refill price: " <<  m_refillPriceRatio2 << endl
         //<< "second refill ratio: " << m_refillCollaRatio2 << endl
         //<< "liquidation price after second refill: " << m_liqPriceRatio2 << endl
         //<< "second refund price: " << m_refundPriceRatio2 << endl;
}

double BabelPledge::getRefillPriceRatio(unsigned short netRefilledTimes) const {
    double ret;

    try {
        switch (netRefilledTimes) {
            case 0:
                ret = m_refillPriceRatio1;
                break;
            case 1:
                ret = m_refillPriceRatio2;
                break;
            //TODO: added more times
            default:
                cout << "Invalid refill times. Check strategy." << endl;
                throw;
                break;
        }
    } catch (std::exception const & e) {
        exit(-1);
    }

    return ret;
}

double BabelPledge::getRefundPriceRatio(unsigned short netRefilledTimes) const {
    double ret;
    try {
        switch (netRefilledTimes) {
            case 0:
                cout << "Nothing to refund. Check strategy." << endl;
                throw;
                break;
            case 1:
                ret = m_refundPriceRatio1;
                break;
            case 2:
                ret = m_refundPriceRatio2;
                break;
            default:
                cout << "Invalid refund times. Check strategy." << endl;
                throw;
                break;
        }
    } catch (std::exception const& e) {
        exit(-1);
    }

    return ret;
}

double BabelPledge::getLiqPriceRatio(unsigned short netRefilledTimes) const {
    double liqPriceRatio;
    try {
        switch (netRefilledTimes) {
            case 0:
                liqPriceRatio = m_liqPriceRatio;
                break;
            case 1:
                liqPriceRatio = m_liqPriceRatio1;
                break;
            case 2:
                liqPriceRatio = m_liqPriceRatio2;
                break;
            default:
                cout << "Invalid refill times. Check strategy." << endl;
                throw;
                break;
        }
    } catch (std::exception const& e) {
        exit(-1);
    }

    return liqPriceRatio;
}

double BabelPledge::getRefillCollaRatio(unsigned short netRefilledTimes) const {
    double refillCollaRatio;
    try {
        switch (netRefilledTimes) {
            case 0:
                refillCollaRatio = m_refillCollaRatio1;
                break;
            case 1:
                refillCollaRatio = m_refillCollaRatio2 - m_refillCollaRatio1;
                break;
            default:
                cout << "Refilled twice already." << endl;
                throw;
                break;
        }
    } catch(std::exception const& e) {
        exit(-1);
    }

    return refillCollaRatio;
}

double BabelPledge::getRefundCollaRatio(unsigned short netRefilledTimes) const {
    double refundCollaRatio;
    try {
        switch (netRefilledTimes) {
            case 0:
                cout << "Nothing to refund. Check strategy." << endl;
                throw;
                break;
            case 1:
                refundCollaRatio = m_refillCollaRatio1;
                break;
            case 2:
                refundCollaRatio = m_refillCollaRatio2 - m_refillCollaRatio1;
                break;
            default:
                cout << "Invalid refill times. Check strategy." << endl;
                throw;
                break;
        }
    } catch (std::exception const& e) {
        exit(-1);
    }

    return refundCollaRatio;
}

GateioPledge::GateioPledge()
        : PledgeBase(0.7, 0.8, 0.9, 0.1388) {
}

Pledge::Pledge(std::unique_ptr<PledgeBase> platform, double entryPrice, double initCollaQty,
        unsigned short netRefillTimesLimit, unsigned short term)
        : m_platform(std::move(platform)), m_entryPrice(entryPrice), m_initCollaQty(initCollaQty),
          m_netRefillTimesLimit(netRefillTimesLimit), m_term(term) {
    m_collaQty = m_initCollaQty;

    m_loanUsdtAmnt = m_platform->getInitCollaLevel() * m_initCollaQty * m_entryPrice;

    updatePrices();
}

std::unique_ptr<PledgeBase> PledgeFactory::createPledge(Platform platform) {
    switch (platform) {
        case Platform::Babel:
            return std::make_unique<BabelPledge>();
        case Platform::Gateio:
            return std::make_unique<GateioPledge>();
        case Platform::Unknown:
        default:
            throw "Invalid pledge platform.\n";
    }
}

Pledge::~Pledge() {
}

void Pledge::init() {
    //m_entryPrice = ARGs.m_entryPrice;
    //m_term = ARGs.m_pledge.durationInDays;
    //m_netRefillTimesLimit = ARGs.m_pledge.netRefillTimesLimit;

    //m_initCollaQty = ARGs.m_pledge.qty;
    //if (m_initCollaQty > m_portfolio->getBtcBal()) {
        //cout << "Failed to initiate pledgeCtrl. Insufficient balance." << endl;
        //exit(-1);
    //}

    //m_portfolio->decrBtcBal(m_initCollaQty);
    //m_collaQty = m_initCollaQty;
    //m_loanUsdtAmnt = m_platform->getInitCollaLevel() * m_initCollaQty * m_entryPrice;
    //m_portfolio->incrUsdtBal(m_loanUsdtAmnt);

    //m_refillPrice = m_entryPrice *
            //m_platform->getRefillPriceRatio(m_refilledTimes - m_refundedTimes);
}

void Pledge::incrCollaQty(double qty) {
    if (qty > m_portfolio->getBtcBal()) {
        cout << "Failed to increase pledge. Insufficient balance" << endl;
        return;
    }

    m_portfolio->decrBtcBal(qty);
    m_collaQty += qty;
}

double Pledge::evaluateQty() const {
    if (m_liquidated) {
        return 0.0;
    }

    return m_collaQty - m_portfolio->getUsdtValueInBtc(m_loanUsdtAmnt);
}

void Pledge::update(double price) {
    if (m_liquidated) {
        return;
    }

    if (m_refilledTimes - m_refundedTimes < m_netRefillTimesLimit && price <= m_refillPrice) {
        refill();
    }

    m_liqPrice = m_entryPrice * m_platform->getLiqPriceRatio(m_refilledTimes - m_refundedTimes);
    if (price <= m_liqPrice) {
        m_liquidated = true;
        return;
    }

    if (m_refilledTimes - m_refundedTimes > 0 && price >= m_refundPrice) {
        refund();
    }
}

double Pledge::getMaxRefillCollaRatio() const {
    return m_platform->getRefillCollaRatio(m_netRefillTimesLimit);
}
void Pledge::updatePrices() {
    updateLiqPrice();
    updateRefillPrice();
    updateRefundPrice();
}

void Pledge::updateLiqPrice() {
    double liqLevel = m_platform->getLiqLevel();
    m_liqPrice = m_loanUsdtAmnt / (liqLevel * m_collaQty);
}

void Pledge::updateRefillPrice() {
    double refillLevel = m_platform->getRefillLevel();
    m_refillPrice = m_loanUsdtAmnt / (refillLevel * m_collaQty);
}

double Pledge::getRefillCollaQty() const {
    double initCollaLevel = m_platform->getInitCollaLevel();
    double collaQtyRequired = m_loanUsdtAmnt / (initCollaLevel * m_refillPrice);
    return collaQtyRequired - m_collaQty;
}

void Pledge::refill() {
    double refillQty = getRefillCollaQty();

    double btcBal = m_portfolio->getBtcBal();
    if (refillQty > btcBal) {
        double qty = refillQty - btcBal;
        m_portfolio->purchaseBtc(qty);
    }

    m_portfolio->decrBtcBal(refillQty);
    m_collaQty += refillQty;

    updatePrices();

    m_refilledTimes += 1;

    cout << "Refilled pledge with " << refillQty << " btc." << endl;
}

void Pledge::updateRefundPrice() {
    double refundLevel = m_platform->getRefundLevel();
    m_refundPrice = m_loanUsdtAmnt / (refundLevel * m_collaQty);
}

double Pledge::getRefundCollaQty() const {
    double initCollaLevel = m_platform->getInitCollaLevel();
    double collaQtyRequired = m_loanUsdtAmnt / (initCollaLevel * m_refundPrice);
    return m_collaQty - collaQtyRequired;
}

void Pledge::refund() {
    double refundQty = getRefundCollaQty();

    m_portfolio->incrBtcBal(refundQty);
    m_collaQty -= refundQty;

    updatePrices();

    m_refundedTimes += 1;

    cout << "Refunded pledge with " << refundQty << " btc." << endl;
}
