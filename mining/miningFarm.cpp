#include "miningFarm.h"

#include <iostream>

MiningFarm::MiningFarm(Location location, std::map<MinerType, unsigned> minerNums,
        double powerLineLossRatio, double elecFeePerKwh,
        std::vector<unsigned short> elecFeeCollectionDate)
        : m_location(location), m_minerNums(minerNums), m_powerLineLossRatio(powerLineLossRatio),
          m_elecFeePerKwh(elecFeePerKwh), m_elecFeeCollectionDate(elecFeeCollectionDate) {
    for (auto const& i : m_minerNums) {
        m_miners.insert({i.first, Miner(i.first)});
    }
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
