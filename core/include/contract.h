#pragma once

#include <stdint.h>

enum class ContractSide: uint16_t {
    BuyLongType                 = 0x01,
    SellShortType               = 0x02,

    UnknownType                 = 0xFFFF
};

class Contract {
public:
    Contract(double leverage, ContractSide side);

    double getROEPct(double entryPrice, double price) const;
    double getLiqPriceRatio() const {return m_liqPriceRatio;}

private:
    const double m_leverage;
    const ContractSide m_side;

    double m_liqPriceRatio;
};
