#include "miningManagement.h"

MiningMgmt::MiningMgmt(std::vector<MiningFarm> const& miningFarms)
        : m_miningFarms(miningFarms) {
}

double MiningMgmt::getElecFeeCNY(unsigned duration) const {
    double ret = 0.0;

    for (auto const& i : m_miningFarms) {
        ret += i.getElecFeeCNY(duration);
    }

    return ret;
}


