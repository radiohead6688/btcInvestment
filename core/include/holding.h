#pragma once

class Holding {
private:
    double m_balance = 0.0;
    double m_fee = 0.001;

public:
    Holding() : m_balance(0.0) {}
    explicit Holding(double balance) : m_balance(balance) {}

    double getValue(double price) const;
    double sell(double price, double quantity);
    double buy(double quantity);
};

