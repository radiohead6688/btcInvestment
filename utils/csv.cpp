#include <istream>
#include <iostream>
#include <fstream>
#include <streambuf>
#include <map>
#include <vector>
#include <string>

#include "csv.h"

void CSVRow::readNextRow(std::istream& str) {
    std::string line;
    std::getline(str, line);

    std::stringstream lineStream(line);
    std::string cell;

    m_data.clear();
    while(std::getline(lineStream, cell, ','))
    {
        m_data.push_back(cell);
    }

    if (!lineStream && cell.empty())    // check for a trailing comma with no data after it
    {
        m_data.push_back("");   // add an empty element
    }
}

std::istream& operator>>(std::istream& str, CSVRow& data)
{
    data.readNextRow(str);
    return str;
}

CSVIterator& CSVIterator::operator++() {
    if (m_str) {
        if (!((*m_str) >> m_row)) {
            m_str = nullptr;
        }
    }
    return *this;
}

CSVIterator CSVIterator::operator++(int) {
    CSVIterator tmp(*this);
    ++(*this);
    return tmp;
}

bool CSVIterator::operator==(CSVIterator const& rhs) {
    return ((this == &rhs) || ((this->m_str == nullptr) && (rhs.m_str == nullptr)));
}

void writeCSV(std::string fileName) {
    std::ofstream oFile;

    oFile.open(fileName, std::ios::out | std::ios::trunc);
    oFile << "Date" << "," << "Open" << "," << "High" << "," << "Low" << "," << "Close" << std::endl
          << "Dec 6 2019" << "," << "8888.8" << "," << "9999.9" << "," << "7777.7" << "," << "8001.1" << std::endl
          << "Dec 7 2019" << "," << "8003.3" << "," << "9999.9" << "," << "7534.8" << "," << "9001.1" << std::endl;

    oFile.close();
}

void readCSV(std::string fileName) {
    std::ifstream file(fileName);
    CSVRow row;
    while(file >> row)
    {
        std::cout << "4th Element(" << row[1] << ")\n";
    }

    //for(CSVIterator loop(file); loop != CSVIterator(); ++loop)
    //{
        //std::cout << "4th Element(" << (*loop)[1] << ")\n";
    //}
}

std::map<double,double> revenue(std::vector<double> &btcPrices) {
    std::map<double,double> ret;
    for (auto i = btcPrices.begin(); i != btcPrices.end(); ++i) {
        //double r = 
        //revenue.insert(i,
    }
    return ret;
}
