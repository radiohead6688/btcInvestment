#pragma once

#include "miner.h"
#include "miningFarm.h"

#include <vector>

class MiningMgmt {
public:
    MiningMgmt(std::vector<MiningFarm> const& miningFarms);
    ~MiningMgmt() {}

    double getElecFeeCNY(unsigned duration) const;
    std::map<unsigned, double> getElecFeeBrief() const;

private:
    std::vector<MiningFarm> m_miningFarms;
    std::map<unsigned short, std::vector<MiningFarm>> m_elecFeeBrief;
    double m_totalHashrate = 198000;   // in THS, at most 202830
};
