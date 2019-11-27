#include <iostream>
#include <fstream>
#include <string>
#include <streambuf>
#include <map>
#include <vector>

#include "strategy.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

void writeCSV(string str) {
    std::ofstream oFile;

    oFile.open("scoresheet.csv", std::ios::out | std::ios::trunc);
    //oFile << "姓名" << "," << "年龄" << "," << "班级" << "," << "班主任" << endl;
    //oFile << "张三" << "," << "22" << "," << "1" << "," << "JIM" << endl;
    //oFile << "李四" << "," << "23" << "," << "3" << "," << "TOM" << endl;

    oFile.close();
}

string readCSV(string file) {
    std::ifstream iFile(file);
    string readStr((std::istreambuf_iterator<char>(iFile)),  std::istreambuf_iterator<char>());
    cout << readStr.c_str();
    iFile.close();
    return readStr;
}

std::map<double,double> revenue(std::vector<double> &btcPrices) {
    std::map<double,double> ret;
    for (auto i = btcPrices.begin(); i != btcPrices.end(); ++i) {
        //double r = 
        //revenue.insert(i,
    }
    return ret;
}

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

void calculateCollateral(double elecFeeUsdt) {
    double entryPrice = 6900.0;
    double elecQty = elecFeeUsdt / entryPrice;
    double refillCollaRatio = 1.0 / 3.0;
    double initCollaLevel = 0.6;

    double collaQty = elecQty / initCollaLevel;;
    double refillQty = collaQty * refillCollaRatio;

    double quantity = collaQty + refillQty;

    cout.precision(4);
    cout << std::fixed
         << "entryPrice: " << entryPrice << endl
         << "elecQty: " << elecQty << endl
         << "initCollaLevel: " <<  initCollaLevel << endl
         << "refillCollaRatio: " << refillCollaRatio << endl
         << "quantity: " << quantity << endl
         << "collaQty: " << collaQty << endl
         << "refillQty: " << refillQty << endl;
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

//void getBtcQty(double price) {
    //double elecProp = 0.78;
    //double elecFeeCNY = 1000000;
    //double usdtRate = 7.0;
    //double elecQty = (elecFeeCNY / usdtRate) / price;
    //double quantity = elecQty / elecProp;
    //double initCollaLevel = 0.6;
    //double remainCollaRatio = 0.3333;
    //cout << "elecProp: " << elecProp << endl
         //<< "elecFeeCNY: " << elecFeeCNY << endl
         //<< "usdtRate: " << usdtRate << endl
         //<< "elecQty: " << elecQty << endl
         //<< "quantity: " << quantity << endl
         //<< endl;

    //Facts facts;
    //Config config(facts);

    ////Strategy s(fact, config);
    ////s.run();
//}

int main()
{
    //calculateStrategy(150000);
    calculateCollateral(150000);

    //testStrategy();

    //Facts facts(7150);
    //Config config(facts);

    //Facts facts(7150, 1000000);
    //Config config(facts);
    //Strategy* s = new Strategy(facts, config);
    //s.run();

    return 0;
}
