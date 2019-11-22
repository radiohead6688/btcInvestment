#include <cassert>
#include <iostream>

#include "contract.h"

Contract::Contract(double leverage, ContractSide side) : m_leverage(leverage), m_side(side)
{
    assert(m_leverage > 0);
    switch (side) {
        case ContractSide::BuyLongType:
            m_liqPriceRatio = m_leverage / (1 + m_leverage);
            break;
        case ContractSide::SellShortType:
            if (m_leverage <= 1.0){
                m_liqPriceRatio = 0xFFFFFFFF;   //figure out bitmex mechanism
            } else {
                m_liqPriceRatio = m_leverage / (m_leverage - 1);
            }
            break;
        default:
            break;
    }
}

double Contract::getValue(double entryPrice, double price, double quantity) const {
    double liqPrice = entryPrice * m_liqPriceRatio;
    std::cout << liqPrice << std::endl;

    switch (m_side) {
        case ContractSide::BuyLongType:
            if (price <= liqPrice) {
                std::cout << "Price is lower than liquidation price. Rekt!\n";
                return 0.0;
            } else {
                return (quantity + (1/entryPrice - 1/price) * quantity * entryPrice *
                        m_leverage) * price;
            }
            break;
        case ContractSide::SellShortType:
            if (price >= liqPrice) {
                std::cout << "Price is higher than liquidation price. Rekt!\n";
                return 0.0;
            } else {
                return (quantity + (1/price - 1/entryPrice) * quantity * entryPrice *
                        m_leverage) * price;
            }
            break;
        case ContractSide::UnknownType:
            std::cout << "Invalid contract side!\n";
            exit(-1);
    }
}
