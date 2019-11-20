#pragma once

#include "method.h"

class Holding : public Method {
public:
    Holding() {}

    MethodType getMethodType() const override {return Method::HoldingType;}
    double getValue(double price, double quantity) const override;
};

