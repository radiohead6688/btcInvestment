#pragma once

#include <vector>
#include <iostream>

#include "controller.h"

using std::cout;
using std::endl;

struct Facts {
    Facts(double price, double elecFee) {
        entryPrice = price;
        elecFeeCNY = elecFee;
        elecQty = (elecFeeCNY / usdtRate) / entryPrice;
        quantity = elecQty / elecProp;

        print();
    }

    void print() {
        //cout << "entryPrice: " << entryPrice << endl
             //<< "elecProp: " << elecProp << endl
             //<< "elecFeeCNY: " << elecFeeCNY << endl
             //<< "usdtRate: " << usdtRate << endl
             //<< "elecQty: " << elecQty << endl
             //<< "quantity: " << quantity << endl
             //<< "initCollaLevel: " <<  initCollaLevel << endl
             //<< "remainCollaRatio: " << remainCollaRatio << endl
             //<< endl;
    }

    double entryPrice;
    double elecProp = 0.78;
    double elecFeeCNY;
    double usdtRate = 7.0;
    double elecQty;
    double quantity;
    double initCollaLevel = 0.6;
    double remainCollaRatio = 0.3333;

    PledgeType pledgeType = PledgeType::BabelPledgeType;
    double durationInDays = 90;
    double tradeFee = 0;
    double leverage = 1;
    unsigned short netRefiilTimesLimit = 1;
    ContractSide contractSide = ContractSide::SellShortType;
};

struct Config {
    Config(const Facts &facts) {
        totalQty = facts.quantity;
        pledgeQty = (1 - facts.elecProp) * totalQty /
                (1 + facts.remainCollaRatio - facts.initCollaLevel);
        tradeQty = facts.elecQty - pledgeQty * facts.initCollaLevel;
        balance = totalQty - pledgeQty - tradeQty;

        tProp = tradeQty / totalQty;
        pProp = pledgeQty / totalQty;
        cProp = contractQty / totalQty;

        //cout << "pledgeQty: " << pledgeQty << endl
             //<< "tradeQty: " << tradeQty << endl
             //<< "balance: " << balance << endl
             //<< "pProp: " << pProp << endl
             //<< "tProp: " << tProp << endl;
    }
    double totalQty = 0;

    double tradeQty = 0;
    double pledgeQty = 0;
    double balance = 0;
    double contractQty = 0;

    double tProp = 0;
    double pProp = 0;
    double cProp = 0;
};

class Strategy {
public:
    Strategy(const Facts& facts, const Config& config);
    ~Strategy();

    void run();
    double getQty(double price) const;
private:
    std::vector<double> m_refPrices;

    Controller* m_c = nullptr;

};
