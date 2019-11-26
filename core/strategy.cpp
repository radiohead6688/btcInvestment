#include <iostream>

#include "strategy.h"
#include "controller.h"

using std::cout;
using std::endl;

Strategy::Strategy() {
    double elecProp = 0.7;
    double entryPrice = 8100;
    double quantity = 130;
    double tProp = 0.4546;
    double pProp = 0.4091;
    double cProp = 0;
    PledgeType pledgeType = PledgeType::BabelPledgeType;
    double durationInDays = 90;
    //double tradeFee = 0.001;
    double tradeFee = 0;
    double leverage = 1;
    unsigned short netRefiilTimesLimit = 1;
    ContractSide contractSide = ContractSide::SellShortType;

    m_c = new Controller(elecProp, entryPrice, quantity, tProp, pProp, cProp, pledgeType,
            durationInDays, tradeFee, leverage, contractSide, netRefiilTimesLimit);

    double refPrices[] = {4000, 4556, 5400, 6075, 7500, 8100, 9135, 1000, 12000, 14000,
                          18000, 20000, 22400, 24000, 26000, 30000, 50000, 80000};
    unsigned refPricesSize = sizeof(refPrices) / sizeof(double);
    m_refPrices.insert(m_refPrices.end(), &refPrices[0], &refPrices[refPricesSize]);
}

Strategy::~Strategy() {
    delete m_c;
}

void Strategy::run() {
    cout << "Price\t\tQuantity" << endl;

    for (auto &i : m_refPrices) {
        double quantity = m_c->getQty(i);
        cout << i << "\t\t" << quantity << endl;
    }
}


