#pragma once

class Trade {
private:
    double m_fee;

public:
    explicit Trade(double fee) : m_fee(fee) {}

    double getValue(double price, double quantity) const;
    double getTradeQty(double targetQty) const;
};
