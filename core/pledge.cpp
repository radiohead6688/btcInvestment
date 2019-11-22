#include "pledge.h"
#include <iostream>
#include "exception.h"

using std::cout;
using std::endl;

Pledge::Pledge(double icl, double mrfil, double ll, double air, unsigned short td) :
    m_initCollaLevel(icl), m_refillLevel(mrfil), m_liqLevel(ll),
    m_annualizedInterestsRate(air), m_termInDays(td)
{
    m_dailyInterests = m_annualizedInterestsRate/ 365;

    m_liqPriceRatio = m_initCollaLevel / m_liqLevel;

    m_refillPriceRatio1 = m_initCollaLevel / m_refillLevel;
    m_refillCollaRatio1 = (1/m_refillPriceRatio1) - 1;
    m_liqPriceRatio1 = m_initCollaLevel / (m_liqLevel * (m_refillCollaRatio1 + 1));

    m_refillPriceRatio2 = m_initCollaLevel / (m_refillLevel * (m_refillCollaRatio1 + 1));
    m_refillCollaRatio2 = (1/m_refillPriceRatio2) - 1;
    m_liqPriceRatio2 = m_initCollaLevel / (m_liqLevel * (m_refillCollaRatio2 + 1));
}

BabelPledge::BabelPledge(unsigned short td) :
        Pledge(0.6, 0.8, 0.9, 0.0888, td)
{
    m_refundPriceRatio1 = m_initCollaLevel / ((m_refillCollaRatio1 + 1) * m_refundLevel);
    m_refundPriceRatio2 = m_initCollaLevel / ((m_refillCollaRatio2 + 1) * m_refundLevel);

    cout << "daily interests: " << m_dailyInterests << endl
         << "refill price: " << m_refillPriceRatio1 << endl
         << "liquidation price: " << m_liqPriceRatio << endl
         << "refill ratio: " << m_refillCollaRatio1 << endl
         << "liquidation price after refill: " << m_liqPriceRatio1 << endl
         << "refund price: " << m_refundPriceRatio1 << endl
         << "second refill price: " <<  m_refillPriceRatio2 << endl
         << "second refill ratio: " << m_refillCollaRatio2 << endl
         << "liquidation price after second refill: " << m_liqPriceRatio2 << endl
         << "second refund price: " << m_refundPriceRatio2 << endl;
}

double BabelPledge::getValue(double entryPrice, double currPrice, double quantity) const
{
    double ret = 0.0;
    double liqPrice = entryPrice * getLiqPriceRatio();
    if (currPrice <= liqPrice) {
        return 0.0;
    }

    return quantity * (currPrice - m_initCollaLevel * entryPrice);
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

double BabelPledge::refill() {
    double refillCollaRatio;;
    try {
        switch (m_refilled - m_refunded) {
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

    m_refilled += 1;

    return refillCollaRatio;
}

double BabelPledge::refund() {
    double refundCollaRatio;;
    try {
        switch (m_refilled - m_refunded) {
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

GateioPledge::GateioPledge(unsigned short td) : Pledge(0.7, 0.8, 0.9, 0.1388, td)
{
}
