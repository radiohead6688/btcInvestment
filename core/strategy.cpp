#include "strategy.h"
#include "trade.h"
#include "argument.h"

#include <iostream>

StockOnlyStrategy::StockOnlyStrategy(Argument const& args) {
    double btcQty = args.m_btcQty;
    double usdtQty = args.m_usdtQty;
    std::unique_ptr<TradeBase> platform = TradeFactory::createTrade(args.m_trade.platform);

    m_stock = std::make_unique<Stock>(std::move(platform), btcQty, usdtQty);
}

StockPledgeStrategy::StockPledgeStrategy(Argument const& args) {
    double entryPrice = args.m_entryPrice;
    double btcQty = args.m_btcQty;
    double usdtQty = args.m_usdtQty;
    double elecUsdtQty = args.m_elecUsdtQty;

    std::unique_ptr<TradeBase> tPlatform = TradeFactory::createTrade(args.m_trade.platform);

    std::unique_ptr<PledgeBase> pPlatform = PledgeFactory::createPledge(args.m_pledge.platform);
    double pledgeTerm = args.m_pledge.durationInDays;
    unsigned short netRefillTimesLimit = args.m_pledge.netRefillTimesLimit;
    double initCollaLevel = pPlatform->getInitCollaLevel();

    // TODO: add 2 refills support, for now supports ONLY 1 refill
    double refillCollaQty = pPlatform->getRefillCollaRatio(netRefillTimesLimit - 1);
    double reservedRefillCollaRatio;
    switch (args.m_pledge.refillCollaType) {
        case RefillCollaType::FullyReserved:
            reservedRefillCollaRatio = refillCollaQty;
            break;
        case RefillCollaType::SellAndBuyBackAtRefillPrice:
            int tradeTimes = 2;
            reservedRefillCollaRatio = refillCollaQty *
                    pPlatform->getRefillPriceRatio(netRefillTimesLimit - 1);
            for (int i = 0; i < tradeTimes; ++i) {
                reservedRefillCollaRatio *= tPlatform->getTradedToTargetRatio();
            }
            break;
    }
    double interestsCollaRatio = pledgeTerm * pPlatform->getDailyInterestsRate();

    double targetToTradedRatio = tPlatform->getTargetToTradedRatio();

    double maximumLoanUsdtQty = (btcQty / (1 + reservedRefillCollaRatio + interestsCollaRatio)) *
            initCollaLevel * entryPrice;

    double collaQty, refillQty, interestsQty, sellQty, remainQty;
    if (maximumLoanUsdtQty >= elecUsdtQty) {
        collaQty = elecUsdtQty / initCollaLevel;
        refillQty = collaQty * reservedRefillCollaRatio;
        interestsQty = collaQty * initCollaLevel * interestsCollaRatio;
        sellQty = 0.0;
        remainQty = btcQty - collaQty - refillQty - interestsQty;
    } else {
        collaQty = (btcQty - elecUsdtQty / (entryPrice * targetToTradedRatio)) /
                (1 + reservedRefillCollaRatio + initCollaLevel * interestsCollaRatio -
                 initCollaLevel / targetToTradedRatio);
        refillQty = collaQty * reservedRefillCollaRatio;
        interestsQty = collaQty * initCollaLevel * interestsCollaRatio;
        sellQty = btcQty - collaQty - refillQty - interestsQty;
        remainQty = 0.0;
    }

    //double refillPrice = entryPrice * pPlatform->getRefillPriceRatio(netRefillTimesLimit - 1);
    //double originalLiqPrice = entryPrice * pPlatform->getLiqPriceRatio(netRefillTimesLimit - 1);
    double refilledLiqPrice = entryPrice * pPlatform->getLiqPriceRatio(netRefillTimesLimit);
    double liqPrice = entryPrice * pPlatform->getLiqPriceRatio(netRefillTimesLimit - 1);
    double refundPrice = entryPrice * pPlatform->getRefundPriceRatio(netRefillTimesLimit);

    double stockBtcQty = remainQty + sellQty + refillQty + interestsQty;
    //m_stock = std::make_unique<Stock>(std::move(tPlatform), stockBtcQty, usdtQty);

    //m_pledge = std::make_unique<Pledge>(std::move(pPlatform), entryPrice, collaQty,
            //netRefillTimesLimit, pledgeTerm);

    m_stock = std::make_unique<Stock>(std::move(tPlatform), 56, 243000);

    m_pledge = std::make_unique<Pledge>(std::move(pPlatform), 8100, 50, 1, 90);

    std::cout.precision(4);
    //std::cout << std::fixed
         //<< "entryPrice: " << entryPrice << std::endl
         //<< "refillPrice: " << m_pledge->getRefillPrice() << std::endl
         //<< "originalLiqPrice: " << m_pledge->getLiqPrice() << std::endl
         //<< "LiqPrice after refill: " << refilledLiqPrice << std::endl
         //<< "liqPrce: " << liqPrice << std::endl
         //<< "refundPrice: " << m_pledge->getRefundPrice() << std::endl
         //<< std::endl
         //<< "quantity: " << btcQty << std::endl
         //<< "elecUsdtQty: " << elecUsdtQty << std::endl
         //<< "initCollaLevel: " <<  initCollaLevel << std::endl
         //<< "reservedRefillCollaRatio: " << reservedRefillCollaRatio << std::endl
         //<< "collaQty: " << collaQty << std::endl
         //<< "refillQty: " << refillQty << std::endl
         //<< "interestsQty: " << interestsQty << std::endl
         //<< "sellQty: " << sellQty << std::endl
         //<< "usdtLoanAmnt: " << collaQty * initCollaLevel * entryPrice << std::endl
         //<< "maximumLoanQty: " << maximumLoanUsdtQty << std::endl;
}

Strategy* StrategyFactory::createStrategy(Argument const& args) {
    switch (args.m_strategyType) {
        case Strategy::Type::StockOnly: {
            return new StockOnlyStrategy(args);
        }
        case Strategy::Type::StockPledge: {
            return new StockPledgeStrategy(args);
        }
        case Strategy::Type::Unknown:
        default:
            throw "Invalid strategy type.\n";
    }
}
