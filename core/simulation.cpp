#include "simulation.h"
//#include "argument.h"

#include <memory>

Simulation::Simulation(Strategy* strategy) {
    switch (strategy->getType()) {
        case Strategy::Type::StockOnly: {
            StockOnlyStrategy* stockOnlyStrategy = dynamic_cast<StockOnlyStrategy*>(strategy);

            m_portfolio = std::make_shared<StockOnlyPortfolio>(
                    std::move(stockOnlyStrategy->getStock()));
            break;
        }
        case Strategy::Type::StockPledge: {
            StockPledgeStrategy* stockPledgeStrategy =
                    dynamic_cast<StockPledgeStrategy*>(strategy);

            m_portfolio = std::make_shared<StockPledgePortfolio>(
                    std::move(stockPledgeStrategy->getStock()),
                    std::move(stockPledgeStrategy->getPledge()));
            break;
        }
        case Strategy::Type::Unknown:
        default:
            throw "Invalid strategy type.\n";
    }
}

void Simulation::init() {
}
