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
    oFile << "姓名" << "," << "年龄" << "," << "班级" << "," << "班主任" << endl;
    oFile << "张三" << "," << "22" << "," << "1" << "," << "JIM" << endl;
    oFile << "李四" << "," << "23" << "," << "3" << "," << "TOM" << endl;

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
 * colla + sell + remain = productivity;
 * colla * initCollaLevel + sell = productivity * elecProp;
 * remain = colla * remainCollaRatio;
 */
void calculateStrategy() {
    double const elecProp = 0.78;
    double const productivity = 130;
    double const initCollaLevel = 0.6;
    double const remainCollaRatio = 0.25;
    double colla, sell, remain;

    colla = (1 - elecProp) * productivity / (1 + remainCollaRatio - initCollaLevel);
    remain = colla * remainCollaRatio;
    sell = productivity - colla - remain;

    cout << "Collateral: " << colla << "\nSell: " << sell << "\nRemaining: " << remain << endl;
}

void testStrategy() {
    double refPrices[] = {4000, 4556, 5400, 6075, 7500, 8100, 9135, 10000, 12000, 14000,
                          18000, 20000, 22400, 24000, 26000, 30000, 50000, 80000};

    cout << "Price\t\tQuantity" << endl;

    for (auto &i : refPrices) {
        Strategy* s = new Strategy();
        double quantity = s->getQty(i);
        cout << i << "\t\t" << quantity << endl << endl;
        delete s;
    }
}

int main()
{
    //calculateStrategy();

    testStrategy();

    //Strategy s;
    //s.run();


    return 0;
}
