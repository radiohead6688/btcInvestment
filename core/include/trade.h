#pragma once

enum class TradePlatform: uint16_t {
    OfflineTrade                = 0x01,
    /* Add new platform*/

    UnknownPlatform             = 0xFFFF,
};

class Trade {
protected:
    explicit Trade(double fee) : m_fee(fee) {}

    const double m_fee;

public:
    virtual ~Trade() {}

    double getValue(double price, double quantity) const;
    double getTradeQty(double targetQty) const;
};

/*
 * transaction fee rate = 0.007
 */
class OfflineTrade : public Trade {
public:
    OfflineTrade() : Trade(0.007) {}
};
