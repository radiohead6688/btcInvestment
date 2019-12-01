#include <iostream>

#include "strategyBuilder.h"
#include "miningManagement.h"
#include "miningFarm.h"

using std::cout;
using std::endl;

/*
 * collaQty + tradeQty + refillQty = quantity;
 * collaQty * initCollaLevel + (1 - tradeFeeRate) * tradeQty = quantity * elecProp;
 * refillQty = collaQty * refillCollaRatio;
 */
void calculateStrategy(double elecFeeUsdt) {
    double elecProp = 0.78;
    double entryPrice = 6900.0;
    double elecQty = elecFeeUsdt / entryPrice;
    double quantity = elecQty / elecProp;
    double refillCollaRatio = 1.0 / 3.0;
    double initCollaLevel = 0.6;
    double tradeFeeRate = 0.007;

    double collaQty = ((1.0 - tradeFeeRate) - elecProp) * quantity /
            ((1.0 + refillCollaRatio) * (1.0 - tradeFeeRate)  - initCollaLevel);
    double refillQty = collaQty * refillCollaRatio;
    double tradeQty = quantity - collaQty - refillQty;

    double tProp = tradeQty / quantity;
    double pProp = collaQty / quantity;
    double rProp = refillQty / quantity;

    double usdtLoanAmnt = collaQty * initCollaLevel * entryPrice;
    double tradeAmnt = tradeQty * (1 - tradeFeeRate) * entryPrice;

    cout.precision(4);
    cout << std::fixed
         << "entryPrice: " << entryPrice << endl
         << "elecProp: " << elecProp << endl
         << "elecQty: " << elecQty << endl
         << "quantity: " << quantity << endl
         << "initCollaLevel: " <<  initCollaLevel << endl
         << "refillCollaRatio: " << refillCollaRatio << endl
         << "collaQty: " << collaQty << endl
         << "tradeQty: " << tradeQty << endl
         << "refillQty: " << refillQty << endl
         << "pProp: " << pProp << endl
         << "tProp: " << tProp << endl
         << "rProp: " << rProp << endl
         << "usdtLoanAmnt: " << usdtLoanAmnt << endl
         << "tradeAmnt: " << tradeAmnt << endl
         << "totalAmnt: " << usdtLoanAmnt + tradeAmnt << endl;
}

void getCollaQtyByFixedLoan(double elecFeeUsdt, double entryPrice, unsigned short duration,
        unsigned short netRefillTimesLimit) {
    Trade* trade = new OfflineTrade();
    Pledge* pledge = new BabelPledge();
    Contract* contract = new BitmexContract(1.0, ContractSide::SellShort);

    Configs configs;

    double elecQty = elecFeeUsdt / entryPrice;
    double initCollaLevel = pledge->getInitCollaLevel();
    double refillLevel = pledge->getRefillLevel();
    double refillPriceRatio = pledge->getRefillPriceRatio(netRefillTimesLimit);
    double refillCollaRatio = pledge->getRefillCollaRatio(netRefillTimesLimit);
    double liqLevel = pledge->getLiqLevel();
    double liqPriceRatio = pledge->getLiqPriceRatio(netRefillTimesLimit);
    double dailyInterestsRate = pledge->getDailyInterestsRate();

    double collaQty = elecQty / initCollaLevel;;
    double refillQty = collaQty * refillCollaRatio;

    double quantity = collaQty + refillQty;

    cout.precision(4);
    //cout << std::fixed
         //<< "entryPrice: " << entryPrice << endl
         //<< "elecQty: " << elecQty << endl
         //<< "initCollaLevel: " <<  initCollaLevel << endl
         //<< "refillCollaRatio: " << refillCollaRatio << endl
         //<< "quantity: " << quantity << endl
         //<< "collaQty: " << collaQty << endl
         //<< "refillQty: " << refillQty << endl;

    cout << std::fixed
         << "贷款总额：" << elecFeeUsdt << " usdt" << endl
         << "质押物：" << collaQty << " btc" << endl
         << "储备质押物：" << refillQty << " btc" << endl
         << "质押物总计：" << quantity << " btc" << endl
         << "质押币价：" << entryPrice << " usdt" << endl
         << "质押平台：" << "贝宝 (初始质押率 " << initCollaLevel << "，预警质押率 "
                << refillLevel << "，平仓质押率 " << liqLevel << endl
         << "质押周期：" << duration << " 天" << endl
         << "年化利息：" << "8.88%" << endl
         << "质押 " << collaQty << " btc，获得贷款 " << elecFeeUsdt << " usdt。" << endl
         << "储备 " << refillQty << " btc，以备价格下跌至 " << refillPriceRatio * entryPrice
                << " usdt时进行补仓。" << endl
         << "补仓后若币价持续下跌至 " << liqPriceRatio * entryPrice
                << " usdt将被强制平仓。" << endl
         << "质押期满后取回扣除贷款和利息所剩的质押btc。" << endl
         << "未来价值 = " << quantity << " * p' - " << elecFeeUsdt << " * (1 + "
                << duration * dailyInterestsRate << ")" << endl;
}

void testStrategy() {
    double refPrices[] = {4000, 4556, 5400, 6075, 7500, 8100, 9135, 10000, 12000, 14000,
                          18000, 20000, 22400, 24000, 26000, 30000, 50000, 80000};

    cout << "Price\t\tQuantity" << endl;

    for (auto &i : refPrices) {
        Facts facts(7050, 1500000);
        Config config(facts);
        Strategy* s = new Strategy(facts, config);
        double quantity = s->getQty(i);
        cout << i << "\t\t" << quantity << endl << endl;
        delete s;
    }
}

double getDailyElecFeeCNY(double power, double elecFeePerKwh) {
    return power * 24 * 1.02 * elecFeePerKwh;
}

double getDailyIncomeCNY(double hashrate, double dailyIncomeCNYPerTHS) {
    return hashrate * dailyIncomeCNYPerTHS;
}

double getElecProp(double elecFeeCNY, double dailyIncomeCNY) {
    return elecFeeCNY / dailyIncomeCNY;
}

double calculateElecFeeCNY(double usdtCNYRate, double price) {
    MiningFarm yunNan = {Location::YunNan,
            std::map<MinerType, unsigned> {{MinerType::InnosiliconT2T_30T, 2150}},
            0.03,
            0.39,
            std::vector<unsigned short> {7, 22}
            };

    MiningFarm zhunDong = {Location::ZhunDong,
            std::map<MinerType, unsigned> {{MinerType::InnosiliconT2T_30T, 1000}},
            0.025,
            0.38,
            std::vector<unsigned short> {7, 17, 27}
            };

    MiningFarm lanZhou = {Location::LanZhou,
            std::map<MinerType, unsigned> {{MinerType::Avalon1047_37T, 1025}},
            0.03,
            0.37,
            std::vector<unsigned short> {22}
            };

    MiningFarm wuHai = {Location::WuHai,
            std::map<MinerType, unsigned> {{MinerType::WhatsMinerM21s_54T, 302},
                                           {MinerType::InnosiliconT2T_30T, 2074}},
            0.023,
            0.39,
            std::vector<unsigned short> {12, 27}
            };

    std::vector<MiningFarm> miningFarms = {yunNan, zhunDong, lanZhou, wuHai};

    MiningMgmt miningMgmt = {miningFarms};

    double monthlyElecFeeCNY = miningMgmt.getElecFeeCNY(30);
    cout.precision(4);
    cout << std::fixed
         << "Monthly electricity fee: " << monthlyElecFeeCNY << " CNY, "
         << monthlyElecFeeCNY / usdtCNYRate << " usdt, "
         << monthlyElecFeeCNY / usdtCNYRate / price << " btc" << endl;

    std::map<unsigned, double> elecFeeBrief = miningMgmt.getElecFeeBrief();
    cout << "Electricity fee collection date:" << endl;
    for (auto i : elecFeeBrief) {
        cout << "\t" << i.first << ": " << i.second << " CNY, "
             << i.second / usdtCNYRate << " usdt, "
             << i.second / usdtCNYRate / price << " btc" << endl;
    }


    return 0.0;
}
