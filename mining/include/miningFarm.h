#pragma once

#include "miner.h"

#include <stdint.h>
#include <vector>
#include <map>

enum class Location : uint16_t {
    YunNan                  = 0x01,
    ZhunDong                = 0x02,
    LanZhou                 = 0x03,
    WuHai                   = 0x04,
    /* Add new platform*/

    UnknownPlatform = 0xFFFF,
};


class MiningFarm {
public:
    MiningFarm(Location location, std::map<MinerType, unsigned> &minerNums, double powerLineLossRatio, double elecFeePerKwh, std::vector<unsigned short> elecFeeCollectionDate);
    ~MiningFarm();

private:
    Location m_location;
    double m_elecFeePerKwh;
    double m_powerLineLossRatio;
    std::vector<unsigned short> m_elecFeeCollectionDate;
    std::map<MinerType, unsigned> m_minerNums;
    std::map<MinerType, Miner*> m_miners;
};
