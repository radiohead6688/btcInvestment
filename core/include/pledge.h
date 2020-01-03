#pragma once

#include <stdint.h>
#include <memory>

class PledgeBase {
public:
    virtual ~PledgeBase() = default;

    virtual double getRefillPriceRatio(unsigned short netRefilledTimes) const = 0;

    virtual double getRefillCollaRatio(unsigned short netRefiilTimes) const = 0;

    virtual double getLiqPriceRatio(unsigned short netRefilledTimes) const = 0;

    virtual double getRefundPriceRatio(unsigned short netRefilledTimes) const = 0;

    virtual double getRefundCollaRatio(unsigned short netRefilledTimes) const = 0;

    double getInitCollaLevel() const { return m_initCollaLevel; }

    double getDailyInterestsRate() const { return m_dailyInterests; }

    double getRefillLevel() const { return m_refillLevel; }

    double getLiqLevel() const { return m_liqLevel; }

protected:
    PledgeBase(double icl, double mrfil, double ll, double air);

protected:
    double m_initCollaLevel;

    double m_refillLevel;

    double m_liqLevel;

    double m_annualizedInterestsRate;

    double m_dailyInterests;

    double m_liqPriceRatio;

    double m_refillPriceRatio1, m_refillPriceRatio2;

    double m_liqPriceRatio1, m_liqPriceRatio2;

    double m_refillCollaRatio1, m_refillCollaRatio2;
};

/*
 * initial collateral level = 0.6
 * margin refill level = 0.8
 * margin refund level = 0.4
 * liquidation level = 0.9
 * annualized interests rate = 0.0888
 */
class BabelPledge: public PledgeBase {
public:
    BabelPledge();

    double getRefillPriceRatio(unsigned short netRefilledTimes) const override;

    double getLiqPriceRatio(unsigned short netRefilledTimes) const override;

    double getRefillCollaRatio(unsigned short netRefiilTimes) const override;

    double getRefundPriceRatio(unsigned short netRefilledTimes) const override;

    double getRefundCollaRatio(unsigned short netRefilledTimes) const override;

private:
    double const m_refundLevel = 0.4;

    double m_refundPriceRatio1, m_refundPriceRatio2;
};

/*
 * initial collateral level = 0.7
 * margin refill level = 0.8
 * liquidation level = 0.9
 */
class GateioPledge : public PledgeBase {
public:
    GateioPledge();

    double getRefillPriceRatio(unsigned short netRefilledTimes) const override {return 0;}

    double getLiqPriceRatio(unsigned short netRefilledTimes) const override {return 0;}

    double getRefillCollaRatio(unsigned short netRefiilTimes) const override {return 0;}

    //TODO
    double getRefundPriceRatio(unsigned short netRefilledTimes) const override {return 0;}

    double getRefundCollaRatio(unsigned short netRefilledTimes) const override {return 0;}
};

class PledgeFactory {
public:
    enum class Platform {
        Babel                   = 0x01,
        Gateio                  = 0x02,
        /* Add new platform*/

        Unknown = 0xFFFF,
    };

    static std::unique_ptr<PledgeBase> createPledge(Platform platform);
};

class Portfolio;

class Pledge {
public:
    Pledge(std::unique_ptr<PledgeBase> platform, double entryPrice, double initCollaQty,
            unsigned short netRefillTimesLimit, unsigned short term);

    ~Pledge();

    void init();

    void setPortfolio(std::shared_ptr<Portfolio> portfolio) { m_portfolio = portfolio; }

    double evaluateQty() const;

    void update(double price);

    double getMaxRefillCollaRatio() const;

private:
    void incrCollaQty(double qty);

    void updateRefillAndRefundPrice(unsigned short netRefilledTimes);

    void refill();

    // TODO: gatio no refunding, use abstract factory
    void refund();

private:
    std::unique_ptr<PledgeBase> m_platform;

    std::shared_ptr<Portfolio> m_portfolio;

    double const m_entryPrice;

    double const m_initCollaQty;

    unsigned short const m_term;

    unsigned short const m_netRefillTimesLimit;

    double m_refillPrice;

    double m_refundPrice;

    double m_liqPrice;

    double m_loanUsdtAmnt;

    double m_collaQty = 0;

    unsigned short m_duration = 0;

    unsigned short m_refilledTimes = 0;

    unsigned short m_refundedTimes = 0;

    bool m_liquidated = false;
};
