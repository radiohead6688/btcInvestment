#include "miningFarm.h"

#include <iostream>
#include <functional>
#include <algorithm>
#include <map>

MiningFarm::MiningFarm(Location location, std::map<MinerType, unsigned> minerNums,
        double powerLineLossRatio, double elecFeePerKwh,
        std::vector<unsigned short> elecFeeDate)
        : m_location(location), m_minerNums(minerNums), m_powerLineLossRatio(powerLineLossRatio),
          m_elecFeePerKwh(elecFeePerKwh), m_elecFeeDate(elecFeeDate) {
    for (auto const& i : m_minerNums) {
        Miner miner = Miner(i.first);
        m_miners.insert({i.first, miner});
        m_totalHashrate += i.second * miner.getHashrate();
    }

    std::sort(m_elecFeeDate.begin(), m_elecFeeDate.end(),
            std::less<unsigned short>());
}

double MiningFarm::getElecFeeCNY(unsigned duration) const {
    double dailyElecFee = 0.0;

    for (auto const& i : m_minerNums) {
        std::map<MinerType, Miner>::const_iterator it = m_miners.find(i.first);
        if (it == m_miners.end()) {
            std::cout << "MinerType not found in this mining farm\n";
            exit(-1);
        } else {
            dailyElecFee += i.second *
                    it->second.getDailyElecFeeCNY(m_elecFeePerKwh, m_powerLineLossRatio);
        }
    }

    return dailyElecFee * duration;
}
