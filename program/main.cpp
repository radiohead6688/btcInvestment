#include <iostream>

#include "strategy.h"
#include "strategyBuilder.h"
#include "trade.h"
#include "pledge.h"
#include "contract.h"
#include "log.h"

using std::cout;
using std::endl;

void test(){
    double dailyElecFeeCNY = getDailyElecFeeCNY(2.4, 0.385);
    double dailyIncomeCNY= getDailyIncomeCNY(30, 1.07);
    double elecProp = dailyElecFeeCNY / dailyIncomeCNY;
    cout.precision(8);
    cout << elecProp << endl;
}

int main()
{
    //test();
    calculateElecFeeCNY();
    //calculateStrategy(150000);
    //getCollaQtyByFixedLoan(150000, 7500, 90, 1);
    //for (double i = 7000; i < 8000; i += 100) {
        //getCollaQtyByFixedLoan(150000, 7500, 90, 1);
        //cout << endl;
    //}

    //testStrategy();

    return 0;
}
