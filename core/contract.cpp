#include "contract.h"

Contract::Contract(double entryPrice, double btcQuantity, double leverage, ContractSide side) :
    m_entryPrice(entryPrice), m_leverage(leverage), m_side(side)
{
    switch (side) {
        case ContractSide::BuyLongType:
            m_liqPrice = m_entryPrice * (m_leverage / (1 + m_leverage));
            break;
        case ContractSide::SellShortType:
            m_liqPrice = m_entryPrice * (m_leverage / (1 + m_leverage));
            break;
        default:
            break;
    }
    //m_liqPrice = 
}

