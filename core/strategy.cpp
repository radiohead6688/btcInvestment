#include <iostream>

#include "strategy.h"
#include "controller.h"

using std::cout;
using std::endl;

Strategy::Strategy(const Facts& facts, const Config& config) {
    double elecProp = 0.78;
    double entryPrice = 7050;
    double quantity = 38.4615;
    double tProp = 0.576923;
    double pProp = 0.338462;
    double cProp = 0;
    PledgePlatform pledgePlatform = PledgePlatform::BabelPledge;
    double durationInDays = 90;
    double tradeFee = 0;
    double leverage = 1;
    unsigned short netRefillTimesLimit = 1;
    ContractSide contractSide = ContractSide::SellShort;

    m_c = new Controller(elecProp, entryPrice, quantity, tProp, pProp, cProp, pledgePlatform,
            durationInDays, tradeFee, leverage, contractSide, netRefillTimesLimit);

    //m_c = new Controller(facts.elecProp, facts.entryPrice, facts.quantity, config.tProp, config.pProp, config.cProp, facts.pledgePlatform, facts.durationInDays, facts.tradeFee, facts.leverage, facts.contractSide, facts.netRefillTimesLimit);

    double refPrices[] = {4000, 4556, 5400, 6075, 7500, 8100, 9135, 10000, 12000, 14000,
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

double Strategy::getQty(double price) const {
    return m_c->getQty(price);
}
