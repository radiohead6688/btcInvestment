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

void calculateStrategy() {
    //double elecProp;
    //double productivity;
    //double initCollaLevel;
    //double remainCollaRatio;
    //cout << "Enter electricity fee proportion ";
    //cin >> elecProp;
    //cout << "Enter productivity: ";
    //cin >> productivity;
    //cout << "Enter initial collateral Level: ";
    //cin >> initCollaLevel;
    //cout << "Enter the ration of remaining and collateral: ";
    //cin >> remainCollaRatio;

    //cout << elecProp << " " << productivity << " " << initCollaLevel
         //<< " " << remainCollaRatio << endl;

    double const elecProp = 0.78;
    double const productivity = 130;
    double const initCollaLevel = 0.6;
    double const remainCollaRatio = 0.25;
    double colla, sell, remain;
    /*
     * colla + sell + remain = productivity;
     * colla * initCollaLevel + sell = productivity * elecProp;
     * remain = colla * remainCollaRatio;
     */

    colla = (1 - elecProp) * productivity / (1 + remainCollaRatio - initCollaLevel);
    remain = colla * remainCollaRatio;
    sell = productivity - colla - remain;

    cout << "Collateral: " << colla << "\nSell: " << sell << "\nRemaining: " << remain << endl;
}

int main()
{
    //calculateStrategy();
    //testStrategy();
    Strategy s;
    s.run();


    return 0;
}
