#pragma once

#include <stdint.h>

enum class ContractSide: uint16_t {
    BuyLongType                 = 0x01,
    SellShortType               = 0x02,

    UnknownType                 = 0xFFFF
};

class Contract {
public:
    Contract(double entryPrice, double btcQuantity, double leverage, ContractSide side);

    double getValue(double price) const;

private:
    const double m_entryPrice;
    const double m_leverage;
    const ContractSide m_side;

    double m_liqPrice;
};
