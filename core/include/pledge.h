#pragma once

#include <stdint.h>

enum class PledgeType: uint16_t {
    BabelPledgeType               = 0x01,
    GateioPledgeType              = 0x02,
    MatrixportPledgeType          = 0x03,
    /* Add new type */

    UnknownType = 0xFFFF,
};

class Pledge {
protected:
    Pledge(double icl, double mrfil, double ll, double ai, unsigned short td);

    const double m_initCollaLevel;
    const double m_refillLevel;
    const double m_liqLevel;
    const double m_annualizedInterests;
    const unsigned short m_termInDays;
    double m_dailyInterests;
    double m_liqPriceRatio;

    unsigned short m_refilled = 0;
    double m_refillPriceRatio1, m_refillPriceRatio2;
    double m_liqPriceRatio1, m_liqPriceRatio2;
    double m_refillCollaRatio1, m_refillCollaRatio2;

public:
    virtual double getValue(double price) const = 0;

};

class BabelPledge: public Pledge {
public:
    BabelPledge(unsigned short td);

    double getValue(double price) const override;

    double getLiqPrice() const;
    double refill();

private:
    const double m_refundLevel = 0.4;

    double m_refundPriceRatio1, m_refundPriceRatio2;
};

class GateioPledge: public Pledge {
public:
    GateioPledge(unsigned short td);

    double getValue(double price) const override;
};
