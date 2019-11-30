#pragma once

#include <stdint.h>

enum class MinerType : uint16_t {
    /* Innosilicon */
    InnosiliconT2T_30T          = 0x0001,

    /* Avalon */
    Avalon1047_37T              = 0x0101,

    /* WhatsMiner */
    WhatsMinerM21s_54T          = 0x0203,

    /* AntMiner */
    /* Add new miner type */

    UnknownMinerType            = 0xFFFF
};

class Miner {
public:
    Miner(MinerType type);

    double getDailyElecFeeCNY(double elecFeePerKwh, double powerLineLossRatio) const;
    double getDailyIncomeCNY(double dailyIncomeCNYPerTHS) const;
    double getElecProp(double elecFeeCNY, double dailyIncomeCNY, double powerLineLossRatio) const;

private:
    MinerType m_type;
    double m_power;         // in kWh
    double m_hashrate;      // in THS
};
