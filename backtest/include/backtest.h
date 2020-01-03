#pragma once

#include <stdint.h>
#include <string>
#include <vector>

struct DailyPrice {
    std::string date;
    double open;
    double high;
    double low;
    double close;
};

class Backtest {
public:
    //Backtest(std::vector<DailyPrice> const& historyPrices, Strategy strategy);
    void run();

private:
    std::vector<DailyPrice> m_historyPrices;
    //Strategy m_strategy;
    unsigned m_duration = 0;
};
