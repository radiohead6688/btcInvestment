#include <iostream>
#include <fstream>
#include <streambuf>
#include <map>
#include <vector>
#include <string>

#include "csv.h"

void writeCSV(std::string str) {
    std::ofstream oFile;

    oFile.open("scoresheet.csv", std::ios::out | std::ios::trunc);
    //oFile << "姓名" << "," << "年龄" << "," << "班级" << "," << "班主任" << endl;
    //oFile << "张三" << "," << "22" << "," << "1" << "," << "JIM" << endl;
    //oFile << "李四" << "," << "23" << "," << "3" << "," << "TOM" << endl;

    oFile.close();
}

std::string readCSV(std::string file) {
    std::ifstream iFile(file);
    std::string readStr((std::istreambuf_iterator<char>(iFile)),  std::istreambuf_iterator<char>());
    std::cout << readStr.c_str();
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


