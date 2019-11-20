#include "strategy.h"

Strategy::Strategy(double elecProp, double entryPrice, Holding* h, Pledge* p, Contract* c,
    double qh, double qp, double qc) : m_elecProp(elecProp), m_entryPrice(entryPrice),
    m_quantityHolding(qh), m_quantityPledge(qp), m_quantityContract(qc), m_holding(h), m_pledge(p),
    m_contract(c)
{
}

Strategy::Strategy(double elecProp, double entryPrice, Pledge* p, double qp) :
    m_elecProp(elecProp), m_entryPrice(entryPrice),  m_pledge(p), m_quantityPledge(qp)
{
    m_holding = nullptr;
    m_contract = nullptr;

    m_quantityHolding = 0.0;
    m_quantityContract = 0.0;

}

Strategy::Strategy(double elecProp, double entryPrice, Holding* h, double qh) :
    m_elecProp(elecProp), m_entryPrice(entryPrice),  m_holding(h), m_quantityHolding(qh)
{
    m_pledge = nullptr;
    m_contract = nullptr;

    m_quantityPledge= 0.0;
    m_quantityContract = 0.0;
}

Strategy::Strategy(double elecProp, double entryPrice, Contract* c, double qc) :
    m_elecProp(elecProp), m_entryPrice(entryPrice),  m_contract(c), m_quantityContract(qc)
{
    m_pledge = nullptr;
    m_holding= nullptr;

    m_quantityHolding= 0.0;
    m_quantityPledge= 0.0;
}

double Strategy::getValue(double price) const
{
    double ret = 0.0;
    //return m_holding->getValue() + m_contract->getValue() + m_pledge->getValue();
    if (m_holding){
        ret += m_holding->getValue(price, m_quantityHolding);
    }

    if (m_pledge){
        ret += m_pledge->getValue(price, m_quantityPledge);
    }

    if (m_contract){
        ret += m_contract->getValue(price, m_quantityContract);
    }

    return ret;
}

