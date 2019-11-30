#include <cassert>
#include <iostream>

#include "contract.h"

using std::cout;
using std::endl;

Contract::Contract(double leverage, ContractSide side) : m_leverage(leverage), m_side(side) {
    assert(m_leverage > 0);
    switch (side) {
        case ContractSide::BuyLong:
            m_liqPriceRatio = m_leverage / (1 + m_leverage);
            break;
        case ContractSide::SellShort:
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

double Contract::getROEPct(double entryPrice, double price) const {
    double liqPrice = entryPrice * m_liqPriceRatio;

    switch (m_side) {
        case ContractSide::BuyLong:
            if (price <= liqPrice) {
                cout << "Price is lower than liquidation price. Rekt :(" << endl;
                return 0.0;
            } else {
                return 1 + (1 - entryPrice / price) * m_leverage;
            }
            break;
        case ContractSide::SellShort:
            if (price >= liqPrice) {
                cout << "Price is higher than liquidation price. Rekt :(" << endl;
                return 0.0;
            } else {
                return 1 + (entryPrice / price - 1) * m_leverage;
            }
            break;
        case ContractSide::UnknownSide:
            std::cout << "Invalid contract side!\n";
            exit(-1);
    }
}
