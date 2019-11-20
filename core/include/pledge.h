#pragma once

#include "investment.h"

class Pledge: public Investment {
protected:
    Pledge(double icl, double mrfil, double ll, double ai, unsigned short td);

    const double m_initCollaLevel;
    const double m_refillLevel;
    const double m_liqLevel;
    const double m_annualizedInterests;
    const unsigned short m_termInDays;
    double m_dailyInterests;
    double m_liqPriceRatio;

    double m_refillPriceRatio1, m_refillPriceRatio2;
    double m_liqPriceRatio1, m_liqPriceRatio2;
    double m_refillCollaRatio1, m_refillCollaRatio2;

};

class Babel: public Pledge {
public:
    Babel(double icl, double mrfil, double mrful, double ll, double ai, unsigned short td);

    InvestmentType getInvestmentType() const override {return Investment::PledgeType;}
    double getValue(double price, double quantity) const override;

public:
    const double m_refundLevel;

    double m_refundPriceRatio1, m_refundPriceRatio2;

};
