#pragma once

#include "method.h"

class Contract: public Method {
public:
    Contract();

    MethodType getMethodType() const override {return Method::ContractType;}
    //double getValue(double price, double quantity) const override;

private:
    enum Side : uint16_t {
        BuyLong                     = 0x01,
        SellShort                   = 0x02,
        UnknownType                 = 0xFFFF
    };
    const double m_entryPrice;
    double m_liqPrice;
    double m_size;
};
