#include "miningManagement.h"

#include <iostream>

MiningMgmt::MiningMgmt(std::vector<MiningFarm> const& miningFarms)
        : m_miningFarms(miningFarms) {
    for (auto const& m : m_miningFarms) {
        std::vector<unsigned short> elecFeeDate = m.getElecFeeDate();
        for (auto i : elecFeeDate) {
            m_elecFeeBrief[i].push_back(m);
        }

        //m_totalHashrate += m.getTotalHashrate();
    }
}

double MiningMgmt::getElecFeeCNY(unsigned duration) const {
    double ret = 0.0;

    for (auto const& i : m_miningFarms) {
        ret += i.getElecFeeCNY(duration);
    }

    return ret;
}

std::map<unsigned, double> MiningMgmt::getElecFeeBrief() const {
    std::map<unsigned, double> elecFeeBrief;

    for (auto const& m : m_elecFeeBrief) {
        double elecFee = 0.0;
        for (auto i : m.second) {
            size_t elecFeeTimes = i.getElecFeeDate().size();
            elecFee += i.getElecFeeCNY(30 / elecFeeTimes);
        }
        elecFeeBrief[m.first] = elecFee;
    }
    return elecFeeBrief;
}
