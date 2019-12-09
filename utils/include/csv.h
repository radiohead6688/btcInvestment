#pragma once

#include <string>
#include <iterator>
#include <iterator>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

class CSVRow
{
public:
    std::string const& operator[](std::size_t index) const {return m_data[index];}
    std::size_t size() const {return m_data.size();}
    void readNextRow(std::istream& str);

private:
    std::vector<std::string> m_data;
};

std::istream& operator>>(std::istream& str, CSVRow& data);

class CSVIterator
{
public:
    typedef std::input_iterator_tag iterator_category;
    typedef CSVRow value_type;
    typedef std::size_t difference_type;
    typedef CSVRow* pointer;
    typedef CSVRow& reference;

    CSVIterator(std::istream& str) : m_str(str.good() ? &str : nullptr) { ++(*this); }
    CSVIterator() : m_str(nullptr) {}

    // Pre Increment
    CSVIterator& operator++();
    // Post increment
    CSVIterator operator++(int);
    CSVRow const& operator*() const {return m_row;}
    CSVRow const* operator->() const {return &m_row;}

    bool operator==(CSVIterator const& rhs);
    bool operator!=(CSVIterator const& rhs) {return !((*this) == rhs);}

private:
    std::istream* m_str;
    CSVRow m_row;
};

void writeCSV(std::string fileName);

void readCSV(std::string file);
