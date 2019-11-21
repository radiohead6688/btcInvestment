#include "pledge.h"
#include <iostream>

using std::cout;
using std::endl;

Pledge::Pledge(double icl, double mrfil, double ll, double ai, unsigned short td) :
    m_initCollaLevel(icl), m_refillLevel(mrfil), m_liqLevel(ll),
    m_annualizedInterests(ai), m_termInDays(td)
{
    m_dailyInterests = ai / 365;

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

double BabelPledge::getValue(double price) const
{
    double ret = 0.0;


    return ret;
}

double BabelPledge::getLiqPrice() const {
    double liqPrice;
    switch (m_refilled) {
        case 0:
            liqPrice = m_entryPrice * m_liqPriceRatio;
            break;
        case 1:
            liqPrice = m_entryPrice * m_liqPriceRatio1;
            break;
        case 2:
            liqPrice = m_entryPrice * m_liqPriceRatio2;
            break;
    }
    return liqPrice;
}

double BabelPledge::refill() {
    double refillCollaRatio;;
    switch (m_refilled) {
        case 0:
            refillCollaRatio = m_refillCollaRatio1;
            break;
        case 1:
            refillCollaRatio = m_refillCollaRatio2 - m_refillCollaRatio1;
            break;
    }

    m_refilled += 1;

    return refillCollaRatio;
}

GateioPledge::GateioPledge(unsigned short td) : Pledge(0.7, 0.8, 0.9, 0.1388, td)
{
}
