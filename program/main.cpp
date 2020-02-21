#include <iostream>

#include "argument.h"
#include "strategy.h"
#include "simulation.h"
#include "trade.h"
#include "pledge.h"
#include "csv.h"

int main()
{
    //Argument stockOnlyArg;
    //stockOnlyArg.m_trade.platform = TradeFactory::Platform::Offline;
    //stockOnlyArg.m_entryPrice = 8100;
    //stockOnlyArg.m_elecUsdtQty = 582766;
    //stockOnlyArg.m_btcQty = 106;
    //stockOnlyArg.m_usdtQty = 0.0;

    //Strategy* stockOnlyStrategy = StrategyFactory::createStrategy(stockOnlyArg);
    //Simulation stockOnlySimulation(stockOnlyStrategy);
    //stockOnlySimulation.run();

    //std::cout << std::endl;

    Argument stockPledgeArg;
    stockPledgeArg.m_pledge.platform = PledgeFactory::Platform::Babel;
    stockPledgeArg.m_pledge.durationInDays = 90;
    stockPledgeArg.m_pledge.netRefillTimesLimit = 1;
    stockPledgeArg.m_pledge.refillCollaType = RefillCollaType::SellAndBuyBackAtRefillPrice;
    //stockPledgeArg.m_pledge.refillCollaType = RefillCollaType::FullyReserved;
    stockPledgeArg.m_entryPrice = 9600;
    stockPledgeArg.m_elecUsdtQty = 306873;
    stockPledgeArg.m_btcQty = 91;
    stockPledgeArg.m_usdtQty = 0.0;

    Strategy* stockPledgeStrategy = StrategyFactory::createStrategy(stockPledgeArg);
    Simulation stockPledgeSimulation(stockPledgeStrategy);
    //stockPledgeSimulation.run();

    //std::unique_ptr<Stock> ptr = sPtr->getStock();
    //std::cout << ptr->getBtyQty();
    //getCollaQtyByFixedLoan(324225, 7205, 90, 1);

    //calculateStrategyByFixedQuantity(114.06, 90*31/30);

    //calculateElecFeeCNY(7.08, 7300);
    //calculateStrategyByFixedElecFee(283046.55);

    //calculateStrategyByFixedElecFee(150000);
    //getCollaQtyByFixedLoan(150000, 7500, 90, 1);
    //for (double i = 7000; i < 8000; i += 100) {
        //getCollaQtyByFixedLoan(150000, 7500, 90, 1);
        //cout << endl;
    //}

    return 0;
}
