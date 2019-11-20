#pragma once

#include <stdint.h>


class Investment {
public:
    enum InvestmentType: uint16_t {
        HoldingType                 = 0x01,
        PledgeType                  = 0x02,
        ContractType                = 0x03,
        /* Add new type */

        UnknownType = 0xFFFF,
    };

    virtual ~Investment() {}

    virtual InvestmentType getInvestmentType() const = 0;
    virtual double getValue(double price, double quantity) const = 0;
};

class Holding : public Investment {
public:
    Holding();

    InvestmentType getInvestmentType() const override {return Investment::HoldingType;}
    double getValue(double price, double quantity) const override;

//private:
    //double m_balance;
};

class Contract: public Investment {
public:
    Contract();

    InvestmentType getInvestmentType() const override {return Investment::ContractType;}
    //double getValue(double price, double quantity) const override;

private:
    enum Side : uint16_t {
        BuyLong                     = 0x01,
        SellShort                   = 0x02,
        UnknownType                 = 0xFFFF
    };
    const double m_entryPrice;
    double m_liqPrice;
    double m_size;

};

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

class Strategy {
public:
    Strategy(double elecProp, double quantity, double entryPrice, Holding* holding = nullptr,
        Pledge* pledge = nullptr, Contract* contract = nullptr) : m_elecProp(elecProp), m_quantity(quantity), m_entryPrice(entryPrice),
        m_holding(holding), m_pledge(pledge), m_contract(contract) {}

    Strategy(double elecProp, double quantity, double entryPrice, Pledge* pledge) :
        m_elecProp(elecProp), m_quantity(quantity), m_entryPrice(entryPrice),  m_pledge(pledge)
        {m_quantityPledge = quantity;}

    ~Strategy() {}

    double getValue(double price) const;
private:
    double m_elecProp;
    double m_quantity;
    double m_entryPrice;

    Holding* m_holding;
    Contract* m_contract;
    Pledge* m_pledge;

    double m_quantityHolding;
    double m_quantityContract;
    double m_quantityPledge;
};
