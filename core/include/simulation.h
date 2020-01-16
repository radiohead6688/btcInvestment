#pragma once

#include "portfolio.h"
#include "strategy.h"

#include <memory>
#include <vector>
#include <map>

class Simulation {
public:
    Simulation(Strategy* strategy);

    void init();

    void run();

    void payElecFee(double elecUsdtQty);

    void payInterests();

private:
    void payElecFeeWithUsdt(double elecUsdtQty);

    void payElecFeeWithBtc(double elecUsdtQty, double price);

private:
    std::shared_ptr<Portfolio> m_portfolio;

    std::vector<double> m_prices = {
        8106.13, 8462.78, 8728.39, 8639.82, 10000, 8300, 8000, 7600, 7400,
        8100, 8200, 8300, 8400, 8500, 8300, 8000, 7600, 7400,
        8100, 8200, 8300, 8400, 8500, 8300, 8000, 7600, 7400,
        8100, 8200, 8300, 8400, 8500, 8300, 8000, 7600, 7400,
        8100, 8200, 8300, 8400, 8500, 8300, 8000, 7600, 7400,
        8100, 8200, 8300, 8400, 8500, 8300, 8000, 7600, 7400,
        8100, 8200, 8300, 8400, 8500, 8300, 8000, 7600, 7400,
        8100, 8200, 8300, 8400, 8500, 8300, 8000, 7600, 7400,
        8100, 8200, 8300, 8400, 8500, 8300, 8000, 7600, 7400,
        8100, 8200, 8300, 8400, 8500, 8300, 8000, 7600, 8100,
    };

    unsigned short m_startDate = 13;

    std::map<unsigned short, double> m_elecFee = {
        {13,129863}, {16,80372.96368}, {22, 119559.4832}, {27, 224563.6114}, {7, 80372.96368}
    };

    double m_interests = 0.22;   //btc

    std::map<unsigned short, double> balance;
};
