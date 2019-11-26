#include "pledge.h"
#include <iostream>
#include "exception.h"

using std::cout;
using std::endl;

Pledge::Pledge(double icl, double mrfil, double ll, double air) :
    m_initCollaLevel(icl), m_refillLevel(mrfil), m_liqLevel(ll),
    m_annualizedInterestsRate(air) {

    m_dailyInterests = m_annualizedInterestsRate/ 365;

    m_liqPriceRatio = m_initCollaLevel / m_liqLevel;

    m_refillPriceRatio1 = m_initCollaLevel / m_refillLevel;
    m_refillCollaRatio1 = (1/m_refillPriceRatio1) - 1;
    m_liqPriceRatio1 = m_initCollaLevel / (m_liqLevel * (m_refillCollaRatio1 + 1));

    m_refillPriceRatio2 = m_initCollaLevel / (m_refillLevel * (m_refillCollaRatio1 + 1));
    m_refillCollaRatio2 = (1/m_refillPriceRatio2) - 1;
    m_liqPriceRatio2 = m_initCollaLevel / (m_liqLevel * (m_refillCollaRatio2 + 1));
}

/*
 * @brief Returns ROE percentage (quantity-base)
 * @param entryPrice    entry price
 * @param price         current price
 * @return Returns the Return On Equity percentage
 * @TODO correct the ratio
 */
double Pledge::getROEPct(double entryPrice, double price, double currQty, double initQty,
        unsigned short duration) const {

    double ret = 0.0;
    if (price / entryPrice <= getLiqPriceRatio()) {
        return 0.0;
    }

    return 1 - m_initCollaLevel * (entryPrice / price) * (initQty / currQty)
            * (1 + duration * m_dailyInterests);
}

BabelPledge::BabelPledge() : Pledge(0.6, 0.8, 0.9, 0.0888) {
    m_refundPriceRatio1 = m_initCollaLevel / ((m_refillCollaRatio1 + 1) * m_refundLevel);
    m_refundPriceRatio2 = m_initCollaLevel / ((m_refillCollaRatio2 + 1) * m_refundLevel);

    //cout << "Babel Pledge:" << endl
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

double BabelPledge::getLiqPriceRatio() const {
    double liqPriceRatio;
    try {
        switch (m_refilled - m_refunded) {
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
                cout << "Refilled too many times. Check strategy." << endl;
                throw;
                break;
        }
    } catch (const std::exception& e) {
        exit(-1);
    }

    return liqPriceRatio;
}

double BabelPledge::getRefillRatio(unsigned short netRefilledTimes) {
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
    } catch(const std::exception& e) {
        exit(-1);
    }

    return refillCollaRatio;
}

double BabelPledge::refund(unsigned short netRefilledTimes) {
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
                cout << "Refilled more than twice. Check strategy." << endl;
                throw;
                break;
        }
    } catch (const std::exception& e) {
        exit(-1);
    }

    m_refunded += 1;

    return refundCollaRatio;
}

GateioPledge::GateioPledge() : Pledge(0.7, 0.8, 0.9, 0.1388) {
}
