#pragma once

#include "holding.h"
#include "pledge.h"
#include "contract.h"

class Strategy {
public:
    Strategy(double elecProp, double entryPrice, Holding* h, Pledge* p, Contract* c,
        double qh, double qp, double qc);

    Strategy(double elecProp, double entryPrice, Holding* h, double qh);
    Strategy(double elecProp, double entryPrice, Pledge* p, double qp);
    Strategy(double elecProp, double entryPrice, Contract* c, double qc);

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
