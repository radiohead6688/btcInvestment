#pragma once

#include "trade.h"
#include "pledge.h"
#include "contract.h"

class Strategy {
public:
    Strategy(double elecProp, double entryPrice, double quantity, double tProp, double pProp,
            double cProp, PledgeType pType, unsigned short days, double tradeFee, double leverage,
            ContractSide contractSide);

    ~Strategy();

    void initTrade(double tProp, double tradeFee);
    void initPledge(double pProp, PledgeType pType);
    void initContract(double cProp, double leverage, ContractSide side);

    double getQty(double price) const;
    void sell(double quantity, double price);
    void purchase(double quantity, double price);
    void payElecFee();

private:
    const double m_initQty;
    const double m_elecProp;
    const double m_elecQty;
    const double m_entryPrice;

    Trade* m_trade;
    Contract* m_contract;
    Pledge* m_pledge;

    double m_sellQty;

    double m_contractQty;
    double m_pledgeQty;
    double m_balance;
    double m_usdtBalance = 0;

    unsigned short m_pledgeDuration;
    unsigned short m_pledgePast;
};
