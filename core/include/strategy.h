#pragma once

#include "holding.h"
#include "pledge.h"
#include "contract.h"

class Strategy {
public:
    Strategy(double elecProp, double entryPrice, double quantity, double hProp, double pProp,
            double cProp, PledgeType pType, unsigned short days, double tradeFee, double leverage,
            ContractSide contractSide);

    ~Strategy();

    void initHolding(double tradeFee);
    void initPledge(double pProp, PledgeType pType);
    void initContract(double cProp, double leverage, ContractSide side);

    double getQty(double price) const;
    void sell(double quantity, double price);
    void purchase(double quantity, double price);
    void payElecFee();

private:
    double m_elecProp;
    double m_initQty;
    double m_entryPrice;


    Holding* m_holding;
    Contract* m_contract;
    Pledge* m_pledge;

    double m_elecQty;
    double m_holdingQty;
    double m_contractQty;
    double m_pledgeQty;
    double m_usdtQty= 0;

    unsigned short m_pledgeDuration;
    unsigned short m_pledgePast;
};
