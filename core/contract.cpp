#include <iostream>

#include "contract.h"

Contract::Contract(double leverage, ContractSide side) : m_leverage(leverage), m_side(side)
{
    switch (side) {
        case ContractSide::BuyLongType:
            m_liqPriceRatio = m_leverage / (1 + m_leverage);
            break;
        case ContractSide::SellShortType:
            m_liqPriceRatio = m_leverage / (m_leverage - 1);
            break;
        default:
            break;
    }
}

double Contract::getValue(double entryPrice, double price, double quantity) const {
    double liqPrice = entryPrice * m_liqPriceRatio;

    switch (m_side) {
        case ContractSide::BuyLongType:
            if (price <= liqPrice) {
                std::cout << "Price is lower than liquidation price. Rekt!\n";
                return 0.0;
            } else {
                return ((1/entryPrice - 1/price) * quantity * entryPrice * m_leverage) * price;
            }
            break;
        case ContractSide::SellShortType:
            if (price >= liqPrice) {
                std::cout << "Price is higher than liquidation price. Rekt!\n";
                return 0.0;
            } else {
                return ((1/price - 1/entryPrice) * quantity * entryPrice * m_leverage) * price;
            }
            break;
        case ContractSide::UnknownType:
            std::cout << "Invalid contract side!\n";
            exit(-1);
    }
}
