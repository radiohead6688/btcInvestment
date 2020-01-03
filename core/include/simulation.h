#pragma once

#include "portfolio.h"
#include "strategy.h"

#include <memory>

class Simulation {
public:
    Simulation(Strategy* strategy);

    void init();

    void payElecFee(double elecUsdtQty) {}

private:
    std::shared_ptr<Portfolio> m_portfolio;
};
