#pragma once

#include <memory>

class TradeBase {
public:
    virtual ~TradeBase() = default;

    double getUsdtNeeded(double price, double tartgetQty) const;

    double getBuyableQty(double price, double usdtAmnt) const;

    double getTradedToTargetRatio() const { return 1 / (1 - m_feeRate); }

    double getTargetToTradedRatio() const { return 1 - m_feeRate; }

    double getFeeRate() const { return m_feeRate; }

protected:
    explicit TradeBase(double feeRate) : m_feeRate(feeRate) { }

    double const m_feeRate;
};

/*
 * transaction fee rate = 0.007
 */
class OfflineTrade : public TradeBase {
public:
    OfflineTrade() : TradeBase(0.007) { }
};

class TradeFactory {
public:
    enum class Platform : uint16_t {
        Offline             = 0x01,
        /* Add new platform */

        Unknown = 0xFFFF
    };

    static std::unique_ptr<TradeBase> createTrade(Platform platform);
};

class Stock {
public:
    Stock(std::unique_ptr<TradeBase> platform, double btcQty, double usdtQty);

    ~Stock() = default;

    double getTradeFee() const { return m_platform->getFeeRate(); }

    double getBtyQty() const { return m_btcQty; }

    double getUsdtQty() const { return m_usdtQty; }

    double getUsdtValueInBtc(double price, double usdtQty) const;

    void incrBtcQty(double qty);

    void decrBtcQty(double qty);

    void incrUsdtQty(double qty);

    void decrUsdtQty(double qty);

    void purchaseBtc(double price, double netQty);

    void sellBtc(double price, double targetQty);

    double evaluateQty(double price);

    void update(double price) { }

private:
    std::unique_ptr<TradeBase> m_platform;

    double m_btcQty;

    double m_usdtQty;
};
