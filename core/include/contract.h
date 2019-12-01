#pragma once

#include <stdint.h>

enum class ContractSide: uint16_t {
    BuyLong                 = 0x01,
    SellShort               = 0x02,

    UnknownSide             = 0xFFFF
};

enum class ContractPlatform: uint16_t {
    BitmexContract                      = 0x01,
    /* Add new platform*/

    UnknownPlatform             = 0xFFFF
};

class Contract {
protected:
    Contract(double leverage, ContractSide side);

    double const m_leverage;
    ContractSide const m_side;

    double m_liqPriceRatio;

public:
    ~Contract() {}
    double getROEPct(double entryPrice, double price) const;
    double getLiqPriceRatio() const {return m_liqPriceRatio;}
};

class BitmexContract : public Contract {
public:
    BitmexContract(double leverage, ContractSide side) : Contract(leverage, side) {}
};
