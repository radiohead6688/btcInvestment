#include "strategy.h"

struct Config {
    double elecProp;
    double entryPrice;
    double quantity;
    double durationInDays;

    struct {
        double hProp;
    } holding;

    struct {
        double pProp;
        PledgeType type;
    } pledge;

    struct {
        double cProp;
    } contract;
};

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

    m_quantityHolding = quantity * hProp;
    m_quantityPledge = quantity * pProp;
    m_quantityContract = quantity * cProp;
}

double Strategy::getValue(double currPrice) const
{
    double ret = 0.0;

    if (m_holding){
        ret += m_holding->getValue(currPrice);
    }

    if (m_pledge){
        ret += m_pledge->getValue(m_entryPrice, currPrice, m_quantityPledge);
    }

    if (m_contract){
        ret += m_contract->getValue(currPrice);
    }

    return ret;
}

