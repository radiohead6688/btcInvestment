#include "miningFarm.h"

MiningFarm::MiningFarm(Location location, std::map<MinerType, unsigned> &minerNums,
        double powerLineLossRatio, double elecFeePerKwh,
        std::vector<unsigned short> elecFeeCollectionDate)
        : m_location(location), m_minerNums(minerNums), m_powerLineLossRatio(powerLineLossRatio),
          m_elecFeePerKwh(elecFeePerKwh), m_elecFeeCollectionDate(elecFeeCollectionDate) {
    for (auto const& i : m_minerNums) {
        m_miners.insert({i.first, new Miner(i.first)});
    }
}

MiningFarm::~MiningFarm() {
    for (auto const& i : m_miners) {
        delete i.second;
    }
}

