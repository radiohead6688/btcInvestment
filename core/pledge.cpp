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

BabelPledge::BabelPledge(double icl, double mrfil, double mrful, double ll, double ai, unsigned short td) :
        Pledge(icl, mrfil, ll, ai, td),  m_refundLevel(mrful)
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

double BabelPledge::getValue(double price, double quantity) const
{
    return 0;
}

