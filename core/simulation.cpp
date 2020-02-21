#include "simulation.h"
//#include "argument.h"

#include <memory>
#include <iostream>

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

void Simulation::payElecFee(double elecUsdtQty) {
    //double m_portfolio->getBtcBal();
    //double usdtBal = m_portfolio->getUsdtBal();
    //if (usdtBal >= elecUsdtQty) {
        //m_portfolio->decrUsdtBal(elecUsdtQty);
    //} else {
        //double usdtLess = elecUsdtQty - usdtBal;

    //}
}

void Simulation::payElecFeeWithUsdt(double elecUsdtQty) {
    m_portfolio->decrUsdtBal(elecUsdtQty);
}

void Simulation::payElecFeeWithBtc(double elecUsdtQty, double price) {
    double tradeFee = m_portfolio->getTradeFee();
    m_portfolio->decrBtcBal(elecUsdtQty / price * (1 + tradeFee));
}

void Simulation::payInterests() {
}

void Simulation::init() {
}

void Simulation::run() {
    for (int i = 0; i < 6; ++i) {
        //if (i < 31) {
            //auto itr = m_elecFee.find((i + m_startDate) % 31);
            //if (itr != m_elecFee.end()) {
                //payElecFee(itr->second);
            //}
        //}

        if (i < 31) {
            if (i + m_startDate == 13) {
                payElecFeeWithUsdt(m_elecFee[13]);
                //payElecFeeWithBtc(m_elecFee[13], 8106.13);
            }

            if (i + m_startDate == 16) {
                //payElecFeeWithUsdt(m_elecFee[16]);
                payElecFeeWithBtc(m_elecFee[16], 8702);
            }

            if (i + m_startDate == 22) {
                payElecFeeWithUsdt(m_elecFee[22]);
            }

            if (i + m_startDate == 27) {
                payElecFeeWithUsdt(m_elecFee[27]);
            }

            if (i + m_startDate == 32) {        // 7th next month
                payElecFeeWithUsdt(m_elecFee[7]);
            }
        }

        if (i + m_startDate == 14) {
            m_portfolio->decrBtcBal(12.67);
            m_portfolio->incrUsdtBal(106442.41);
        }

        if (i != 0 && i % 31 == 0) {
            payInterests();
        }

        m_portfolio->updatePrice(m_prices[i]);

        double btcQty;
        btcQty = m_portfolio->evaluateQty();
        balance[i + m_startDate] = btcQty;
        std::cout << i + m_startDate << ": " << btcQty << std::endl;
    }
}
