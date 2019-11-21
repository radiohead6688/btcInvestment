#pragma once

#include <stdint.h>

class Method {
public:
    enum class MethodType: uint16_t {
        HoldingType                 = 0x01,
        PledgeType                  = 0x02,
        ContractType                = 0x03,
        /* Add new type */

        UnknownType = 0xFFFF,
    };

    virtual ~Method() {}

    virtual MethodType getMethodType() const = 0;
    virtual double getValue(double price, double quantity) const = 0;
};
