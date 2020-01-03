#include <iostream>

#include "argument.h"
#include "strategy.h"
#include "simulation.h"
#include "strategyBuilder.h"
#include "trade.h"
#include "pledge.h"
#include "contract.h"
#include "log.h"
#include "csv.h"

using std::cout;
using std::endl;

int main()
{
    Strategy* sPtr = StrategyFactory::createStrategy();
    Simulation si(sPtr);

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
