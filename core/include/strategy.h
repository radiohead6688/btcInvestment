#pragma once

#include "trade.h"
#include "pledge.h"

#include <memory>

class Argument;

class Strategy {
public:
    enum class Type : uint16_t {
        StockOnly               = 0x01,
        StockPledge             = 0x02,
        /* Add new platform */

        Unknown = 0xFFFF,
    };

    virtual ~Strategy() = default;

    virtual Type getType() const = 0;
};

class StockOnlyStrategy : public Strategy {
public:
    StockOnlyStrategy(Argument const& args);

    ~StockOnlyStrategy() = default;

    Type getType() const override { return Type::StockOnly; }

    std::unique_ptr<Stock> getStock() { return std::move(m_stock); }

protected:
    std::unique_ptr<Stock> m_stock;
};

class StockPledgeStrategy : public Strategy {
public:
    StockPledgeStrategy(Argument const& args);

    ~StockPledgeStrategy() = default;

    Type getType() const override { return Type::StockPledge; }

    std::unique_ptr<Stock> getStock() { return std::move(m_stock); }

    std::unique_ptr<Pledge> getPledge() { return std::move(m_pledge); }

protected:
    std::unique_ptr<Stock> m_stock;

    std::unique_ptr<Pledge> m_pledge;
};

class StrategyFactory {
public:
    static Strategy* createStrategy(Argument const& args);
};
