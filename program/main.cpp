#include <iostream>

#include "strategy.h"
#include "trade.h"
#include "pledge.h"
#include "contract.h"
#include "log.h"

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

struct Configs {
    struct {
        Trade* ptr = nullptr;
        double quantity = 0;
    } trade;

    struct {
        Pledge* ptr = nullptr;
        double quantity = 0;
        unsigned short duration = 0;
        unsigned short netRefillTimesLimits = 0;
    } pledge;

    struct {
        Contract* ptr = nullptr;
        double quantity = 0;
    } contract;

    double usdtLoanAmnt = 0;
    double entryPrice = 0;
    double elecProp = 0;
    double elecFee = 0;
};

void loanAmntEqualsElecFee(double elecFeeUsdt, double entryPrice, unsigned short duration,
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

void getCollaWithFixedLoan(double elecFeeUsdt, double entryPrice, double refillCollaRatio,
        unsigned short duration) {
    double elecQty = elecFeeUsdt / entryPrice;
    double initCollaLevel = 0.6;
    double refillPriceRatio = 0.75;
    double liqPriceRatio = 0.5;
    double annulizedInterestsRate = 0.0888;
    double dailyInterestsRate = annulizedInterestsRate / 365;

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
         //<< "质押平台：" << "贝宝 (初始质押率 " << initCollaLevel << "，预警质押率 " << 80%，平仓质押率90%)" << endl
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

int main()
{
    //calculateStrategy(150000);
    loanAmntEqualsElecFee(150000, 7500, 90, 1);
    //for (double i = 7000; i < 8000; i += 100) {
        //getCollaWithFixedLoan(150000, i, 1.0/3.0, 90);
        //getCollaWithFixedLoan(150000, i, 0.25, 90);
        //cout << endl;
    //}

    //testStrategy();

    return 0;
}
