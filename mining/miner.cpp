#include "miner.h"

#include <iostream>

Miner::Miner(MinerType type) : m_type(type) {
    switch (m_type) {
        case MinerType::InnosiliconT2T_30T:
            m_power = 2.4;
            m_hashrate = 30;
            break;
        case MinerType::Avalon1047_37T:
            m_power = 2.4;
            m_hashrate = 37;
            break;
        case MinerType::WhatsMinerM21s_54T:
            m_power = 3.3;
            m_hashrate = 54;
            break;
        default:
            std::cout << "Unknown miner type\n";
            exit(-1);
            break;
    }
}

double Miner::getDailyElecFeeCNY(double elecFeePerKwh, double powerLineLossRatio) const {
    return m_power * 24 * (1 + powerLineLossRatio)  * elecFeePerKwh;
}

double Miner::getDailyIncomeCNY(double dailyIncomeCNYPerTHS) const {
    return m_hashrate * dailyIncomeCNYPerTHS;
}

double Miner::getDailyIncomeBTC(double dailyIncomeBTCPerTHS) const {
    return m_hashrate * dailyIncomeBTCPerTHS;
}

double Miner::getElecProp(double elecFeePerKwh, double dailyIncomeCNYPerTHS,
        double powerLineLossRatio) const {
    double elecFeeCNY = getDailyElecFeeCNY(elecFeePerKwh, powerLineLossRatio);
    double dailyIncomeCNY = getDailyIncomeCNY(dailyIncomeCNYPerTHS);
    return elecFeeCNY / dailyIncomeCNY;
}
