#pragma once

#include "investment.h"

class Holding : public Investment {
public:
    Holding();

    InvestmentType getInvestmentType() const override {return Investment::HoldingType;}
    double getValue(double price, double quantity) const override;
};

