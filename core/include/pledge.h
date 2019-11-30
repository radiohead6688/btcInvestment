#pragma once

#include <stdint.h>

enum class PledgePlatform: uint16_t {
    BabelPledge                   = 0x01,
    GateioPledge                  = 0x02,
    MatrixportPledge              = 0x03,
    /* Add new platform*/

    UnknownPlatform = 0xFFFF,
};

class Pledge {
protected:
    Pledge(double icl, double mrfil, double ll, double air);

    const double m_initCollaLevel;
    const double m_refillLevel;
    const double m_liqLevel;
    const double m_annualizedInterestsRate;
    double m_dailyInterests;
    double m_liqPriceRatio;

    unsigned short m_refilled = 0;
    double m_refillPriceRatio1, m_refillPriceRatio2;
    double m_liqPriceRatio1, m_liqPriceRatio2;
    double m_refillCollaRatio1, m_refillCollaRatio2;

public:
    virtual ~Pledge() {}
    virtual double getRefillPriceRatio(unsigned short netRefilledTimes) const = 0;
    virtual double getRefillCollaRatio(unsigned short netRefiilTimes) = 0;
    virtual double getLiqPriceRatio(unsigned short netRefilledTimes) const = 0;

    double getInitCollaLevel() const {return m_initCollaLevel;}
    double getDailyInterestsRate() const {return m_dailyInterests;}
    double getRefillLevel() const {return m_refillLevel;}
    double getLiqLevel() const {return m_liqLevel;}
    double getROEPct(double entryPrice, double price, double currQty, double initQty,
            unsigned short duration, unsigned short netRefilledTimes) const;
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
    BabelPledge();

    double getRefillPriceRatio(unsigned short netRefilledTimes) const override;
    double getLiqPriceRatio(unsigned short netRefilledTimes) const override;
    double getRefillCollaRatio(unsigned short netRefiilTimes) override;

    double refund(unsigned short netRefilledTimes);

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
    GateioPledge();

    double getRefillPriceRatio(unsigned short netRefilledTimes) const override {return 0;}
    double getLiqPriceRatio(unsigned short netRefilledTimes) const override {return 0;}
    double getRefillCollaRatio(unsigned short netRefiilTimes) override {return 0;}
};
