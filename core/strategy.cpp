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
    double cProp, PledgeType pType, unsigned short days, double tradeFee, double leverage,
    ContractSide contractSide) : m_elecProp(elecProp), m_entryPrice(entryPrice),
    m_initQuantity(quantity)
{
    m_holding = new Holding(tradeFee);

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

    m_contract = new Contract(leverage, contractSide);

    m_quantityHolding = quantity * hProp;
    m_quantityPledge = quantity * pProp;
    m_quantityContract = quantity * cProp;
}

double Strategy::getValue(double price) const
{
    return m_holding->getValue(price, m_quantityHolding)
         + m_pledge->getValue(m_entryPrice, price, m_quantityPledge)
         + m_contract->getValue(m_entryPrice, price, m_quantityContract);
}

