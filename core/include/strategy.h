#pragma once

#include <vector>
#include <iostream>

#include "controller.h"

struct Facts {
    Facts(double price, double elecFee) {
        entryPrice = price;
        elecFeeCNY = elecFee;
        elecQty = (elecFeeCNY / usdtRate) / entryPrice;
        quantity = elecQty / elecProp;

        print();
    }

    void print() {
        //std::cout << "entryPrice: " << entryPrice << std::endl
             //<< "elecProp: " << elecProp << std::endl
             //<< "elecFeeCNY: " << elecFeeCNY << std::endl
             //<< "usdtRate: " << usdtRate << std::endl
             //<< "elecQty: " << elecQty << std::endl
             //<< "quantity: " << quantity << std::endl
             //<< "initCollaLevel: " <<  initCollaLevel << std::endl
             //<< "remainCollaRatio: " << remainCollaRatio << std::endl
             //<< std::endl;
    }

    double entryPrice;
    double elecProp = 0.78;
    double elecFeeCNY;
    double usdtRate = 7.0;
    double elecQty;
    double quantity;
    double initCollaLevel = 0.6;
    double remainCollaRatio = 0.3333;

    PledgePlatform pledgePlatform = PledgePlatform::BabelPledge;
    double durationInDays = 90;
    double tradeFee = 0;
    double leverage = 1;
    unsigned short netRefillTimesLimit = 1;
    ContractSide contractSide = ContractSide::SellShort;
};

struct Config {
    Config(Facts const&facts) {
        totalQty = facts.quantity;
        pledgeQty = (1 - facts.elecProp) * totalQty /
                (1 + facts.remainCollaRatio - facts.initCollaLevel);
        tradeQty = facts.elecQty - pledgeQty * facts.initCollaLevel;
        balance = totalQty - pledgeQty - tradeQty;

        tProp = tradeQty / totalQty;
        pProp = pledgeQty / totalQty;
        cProp = contractQty / totalQty;

        //std::cout << "pledgeQty: " << pledgeQty << std::endl
             //<< "tradeQty: " << tradeQty << std::endl
             //<< "balance: " << balance << std::endl
             //<< "pProp: " << pProp << std::endl
             //<< "tProp: " << tProp << std::endl;
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
    Strategy(Facts const& facts, Config const& config);
    ~Strategy();

    void run();
    double getQty(double price) const;
private:
    std::vector<double> m_refPrices;

    Controller* m_c = nullptr;

};
