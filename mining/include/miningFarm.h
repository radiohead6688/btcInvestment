#pragma once

#include "miner.h"

#include <stdint.h>
#include <vector>
#include <map>

enum class MiningFarmSite : uint16_t {
    YunNanLeased            = 0x01,
    YunNanOwn               = 0x02,
    ZhunDong                = 0x03,
    LanZhou                 = 0x04,
    WuHai                   = 0x05,
    /* Add new platform*/

    UnknownPlatform = 0xFFFF,
};


class MiningFarm {
public:
    MiningFarm(MiningFarmSite site, std::map<MinerType, unsigned> minerNums,
            double powerLineLossRatio, double elecFeePerKwh,
            std::vector<unsigned short> elecFeeDate);

    ~MiningFarm() {}

    double getTotalHashrate() const {return m_totalHashrate;}
    double getElecFeeCNY(unsigned duration) const;
    std::vector<unsigned short> getElecFeeDate() const {return m_elecFeeDate;}

private:
    MiningFarmSite m_site;
    double m_elecFeePerKwh;
    double m_powerLineLossRatio;
    double m_totalHashrate = 0.0;   // in THS
    std::vector<unsigned short> m_elecFeeDate;
    std::map<MinerType, unsigned> m_minerNums;
    std::map<MinerType, Miner> m_miners;
};
