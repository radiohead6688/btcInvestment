#pragma once

class Holding {
private:
    double m_fee;

public:
    Holding(double fee) : m_fee(fee) {}
    explicit Holding() {}

    double getValue(double price, double quantity) const;
    double getSellValue(double price, double quantity) const;
    double getBuyQuantity(double price, double quantity) const;
};
