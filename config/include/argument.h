#pragma once

#include "pledge.h"
#include "trade.h"
#include "contract.h"
#include "portfolio.h"
#include "strategy.h"

enum class RefillCollaType {
    FullyReserved                   = 0x01,
    SellAndBuyBackAtRefillPrice     = 0x02,
};

class Argument {
public:
    struct {
        PledgeFactory::Platform platform    = PledgeFactory::Platform::Babel;
        unsigned short durationInDays       = 90;
        unsigned short netRefillTimesLimit  = 1;
        RefillCollaType refillCollaType     = RefillCollaType::SellAndBuyBackAtRefillPrice;
    } m_pledge;

    struct {
        TradeFactory::Platform platform     = TradeFactory::Platform::Offline;
    } m_trade;

    //struct {
        //ContractPlatform platform;
        //double leverage;
        //ContractSide side;
    //} m_contract;

public:
    Strategy::Type m_strategyType  = Strategy::Type::StockPledge;
    //Strategy::Type m_strategyType  = Strategy::Type::StockOnly;
    double m_entryPrice                     = 8100;
    double m_elecUsdtQty                    = 582766;
    double m_btcQty                         = 106.0;
    double m_usdtQty                        = 0.0;
};

extern Argument ARGs;
