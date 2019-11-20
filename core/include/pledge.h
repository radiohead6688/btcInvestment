#pragma once

#include "method.h"

class Pledge: public Method {
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

class BabelPledge: public Pledge {
public:
    BabelPledge(double icl, double mrfil, double mrful, double ll, double ai, unsigned short td);

    MethodType getMethodType() const override {return Method::PledgeType;}
    double getValue(double price, double quantity) const override;

private:
    const double m_refundLevel;

    double m_refundPriceRatio1, m_refundPriceRatio2;
};

class GateioPledge: public Pledge {
public:
    GateioPledge(double icl, double mrfil, double ll, double ai, unsigned short td) :
        Pledge(icl, mrfil, ll, ai, td) {}

    MethodType getMethodType() const override {return Method::PledgeType;}
    double getValue(double price, double quantity) const override;
};
