#include "strategy.h"

Strategy::Strategy(double elecProp, double entryPrice, double quantity, double hProp, double pProp,
    double cProp, PledgeType pType, unsigned short days) : m_elecProp(elecProp), m_entryPrice(entryPrice), m_initQuantity(quantity)
{
    m_holding = new Holding(quantity * hProp);

    switch (pType) {
        case PledgeType::BabelPledgeType:
            m_pledge = new BabelPledge(days);
            break;
        case PledgeType::GateioPledgeType:
            m_pledge = new GateioPledge(days);
            break;
        case PledgeType::MatrixportPledgeType:
            break;
        default:
            break;
    }
}

//Strategy::Strategy(double elecProp, double entryPrice, Pledge* p, double qp) :
    //m_elecProp(elecProp), m_entryPrice(entryPrice),  m_pledge(p), m_quantityPledge(qp)
//{
    //m_holding = nullptr;
    //m_contract = nullptr;

    //m_quantityHolding = 0.0;
    //m_quantityContract = 0.0;

//}

//Strategy::Strategy(double elecProp, double entryPrice, Holding* h, double qh) :
    //m_elecProp(elecProp), m_entryPrice(entryPrice),  m_holding(h), m_quantityHolding(qh)
//{
    //m_pledge = nullptr;
    //m_contract = nullptr;

    //m_quantityPledge= 0.0;
    //m_quantityContract = 0.0;
//}

//Strategy::Strategy(double elecProp, double entryPrice, Contract* c, double qc) :
    //m_elecProp(elecProp), m_entryPrice(entryPrice),  m_contract(c), m_quantityContract(qc)
//{
    //m_pledge = nullptr;
    //m_holding= nullptr;

    //m_quantityHolding= 0.0;
    //m_quantityPledge= 0.0;
//}

double Strategy::getValue(double price) const
{
    double ret = 0.0;

    if (m_holding){
        ret += m_holding->getValue(price);
    }

    if (m_pledge){
        ret += m_pledge->getValue(price);
    }

    if (m_contract){
        ret += m_contract->getValue(price);
    }

    return ret;
}

