#pragma once

#include "trade.h"
#include "pledge.h"
#include "contract.h"

class Controller {
public:
    Controller(double elecProp, double entryPrice, double quantity, double tProp, double pProp,
            double cProp, PledgeType pType, unsigned short days, double tradeFee, double leverage,
            ContractSide contractSide, double netRefiilTimesLimit);

    ~Controller();

    void initTrade(double tProp, double tradeFee);
    void initPledge(double pProp, PledgeType pType);
    void initContract(double cProp, double leverage, ContractSide side);

    double getQty(double price) const;
    void sell(double quantity, double price);
    void purchase(double quantity, double price);
    void payElecFee();

public:     // Pledge interface
    void refillPledge();
    void endPledge(double price);
    void pledgeLiquidated();
    double getLiqPrice() const;

private:
    void increasePledge(double quantity);

private:
    const double m_initQty;
    const double m_elecProp;
    const double m_elecQty;
    const double m_entryPrice;
    const unsigned short m_pledgeDuration;
    const unsigned short m_netRefillTimesLimit;

    Trade* m_trade = nullptr;
    Contract* m_contract = nullptr;
    Pledge* m_pledge = nullptr;

    double m_contractQty;

    double m_pledgeQty;
    double m_initPledgeQty;
    unsigned short m_pledgePast = 0;
    unsigned short m_refilledTimes = 0;
    unsigned short m_refundedTimes = 0;

    double m_balance;

    double m_usdtBalance = 0;
};

