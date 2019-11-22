#pragma once

#include "holding.h"
#include "pledge.h"
#include "contract.h"

class Strategy {
public:
    Strategy(double elecProp, double entryPrice, double quantity, double hProp, double pProp,
        double cProp, PledgeType pType, unsigned short days, double tradeFee, double leverage,
        ContractSide contractSide);

    Strategy(double elecProp, double entryPrice, Holding* h, double qh);
    Strategy(double elecProp, double entryPrice, Pledge* p, double qp);
    Strategy(double elecProp, double entryPrice, Contract* c, double qc);

    ~Strategy() {}

    double getValue(double price) const;
private:
    double m_elecProp;
    double m_initQuantity;
    double m_entryPrice;

    Holding* m_holding;
    Contract* m_contract;
    Pledge* m_pledge;

    double m_quantityHolding;
    double m_quantityContract;
    double m_quantityPledge;
    unsigned short m_pledgeDuration;
    unsigned short m_pledgePast;

    double m_usdtBalance = 0;
};
