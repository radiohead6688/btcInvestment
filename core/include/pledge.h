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
    Pledge(double icl, double mrfil, double ll, double air, unsigned short durationInDays);

    const double m_initCollaLevel;
    const double m_refillLevel;
    const double m_liqLevel;
    const double m_annualizedInterestsRate;
    const unsigned short m_termInDays;
    double m_dailyInterests;
    double m_liqPriceRatio;

    unsigned short m_refilled = 0;
    double m_refillPriceRatio1, m_refillPriceRatio2;
    double m_liqPriceRatio1, m_liqPriceRatio2;
    double m_refillCollaRatio1, m_refillCollaRatio2;

public:
    virtual double getValue(double entryPrice, double currPrice, double quantity) const = 0;
    virtual double getLiqPriceRatio() const = 0;
    virtual double refill() = 0;
};

class BabelPledge: public Pledge {

/*
 * initial collateral level = 0.6
 * margin refill level = 0.8
 * margin refund level = 0.4
 * liquidation level = 0.9
 * annualized interests rate = 0.0888
 */

public:
    BabelPledge(unsigned short durationInDays);

    double getValue(double entryPrice, double currPrice, double quantity) const override;
    double getLiqPriceRatio() const override;
    double refill() override;

    double refund();

private:
    const double m_refundLevel = 0.4;

    double m_refundPriceRatio1, m_refundPriceRatio2;
    unsigned short m_refunded = 0;
};

class GateioPledge: public Pledge {

/*
 * initial collateral level = 0.7
 * margin refill level = 0.8
 * liquidation level = 0.9
 */

public:
    GateioPledge(unsigned short durationInDays);

    double getValue(double entryPrice, double currPrice, double quantity) const override {return 0;}
    double getLiqPriceRatio() const override {return 0;}
    double refill() override {return 0;}
};
