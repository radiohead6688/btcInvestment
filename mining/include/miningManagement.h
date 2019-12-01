#pragma once

#include "miner.h"
#include "miningFarm.h"

#include <vector>

class MiningMgmt {
public:
    MiningMgmt(std::vector<MiningFarm> const& miningFarms);
    ~MiningMgmt() {}

    double getElecFeeCNY(unsigned duration) const;

private:
    std::vector<MiningFarm> m_miningFarms;
};
