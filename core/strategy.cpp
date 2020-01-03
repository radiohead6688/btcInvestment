#include "strategy.h"
#include "trade.h"
#include "argument.h"

#include <iostream>

StockOnlyStrategy::StockOnlyStrategy() {
    double btcQty = ARGs.m_btcQty;
    double usdtQty = ARGs.m_usdtQty;
    std::unique_ptr<TradeBase> platform = TradeFactory::createTrade(ARGs.m_trade.platform);

    m_stock = std::make_unique<Stock>(std::move(platform), btcQty, usdtQty);
}

StockPledgeStrategy::StockPledgeStrategy() {
    double entryPrice = ARGs.m_entryPrice;
    double btcQty = ARGs.m_btcQty;
    double usdtQty = ARGs.m_usdtQty;
    double elecUsdtQty = ARGs.m_elecUsdtQty;

    std::unique_ptr<TradeBase> tPlatform = TradeFactory::createTrade(ARGs.m_trade.platform);

    std::unique_ptr<PledgeBase> pPlatform = PledgeFactory::createPledge(ARGs.m_pledge.platform);
    double pledgeTerm = ARGs.m_pledge.durationInDays;
    unsigned short netRefillTimesLimit = ARGs.m_pledge.netRefillTimesLimit;
    double initCollaLevel = pPlatform->getInitCollaLevel();

    // TODO: add 2 refills support, for now supports ONLY 1 refill
    double reservedRefillCollaRatio = pPlatform->getRefillCollaRatio(netRefillTimesLimit - 1);
    switch (ARGs.m_pledge.refillCollaType) {
        case RefillCollaType::FullyReserved:
            break;
        case RefillCollaType::SellAndBuyBackAtRefillPrice:
            int tradeTimes = 2;
            reservedRefillCollaRatio *= pPlatform->getRefillPriceRatio(netRefillTimesLimit - 1);
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

    double stockBtcQty = remainQty + sellQty + refillQty + interestsQty;
    m_stock = std::make_unique<Stock>(std::move(tPlatform), stockBtcQty, usdtQty);

    m_pledge = std::make_unique<Pledge>(std::move(pPlatform), entryPrice, collaQty,
            netRefillTimesLimit, pledgeTerm);

    std::cout.precision(4);
    std::cout << std::fixed
         << "entryPrice: " << entryPrice << std::endl
         << "quantity: " << btcQty << std::endl
         << "elecUsdtQty: " << elecUsdtQty << std::endl
         << "initCollaLevel: " <<  initCollaLevel << std::endl
         << "reservedRefillCollaRatio: " << reservedRefillCollaRatio << std::endl
         << "collaQty: " << collaQty << std::endl
         << "refillQty: " << refillQty << std::endl
         << "interestsQty: " << interestsQty << std::endl
         << "sellQty: " << sellQty << std::endl
         << "usdtLoanAmnt: " << collaQty * initCollaLevel * entryPrice << std::endl
         << "tradeAmnt: " << sellQty << std::endl
         << "maximumLoanQty: " << maximumLoanUsdtQty << std::endl;


    //m_initCollaQty = ARGs.m_pledge.qty;
    //if (m_initCollaQty > m_portfolio->getBtcBal()) {
        //cout << "Failed to initiate pledgeCtrl. Insufficient balance." << std::endl;
        //exit(-1);
    //}

    //m_portfolio->decrBtcBal(m_initCollaQty);
    //m_collaQty = m_initCollaQty;
    //m_loanUsdtAmnt = m_platform->getInitCollaLevel() * m_initCollaQty * m_entryPrice;
    //m_portfolio->incrUsdtBal(m_loanUsdtAmnt);

    //m_refillPrice = m_entryPrice *
            //m_platform->getRefillPriceRatio(m_refilledTimes - m_refundedTimes);

    //m_pledge = std::make_unique<Pledge>(std::move(platform), btcQty, usdtQty);
}

Strategy* StrategyFactory::createStrategy() {
    switch (ARGs.m_strategyType) {
        case Strategy::Type::StockOnly: {
            return new StockOnlyStrategy();
        }
        case Strategy::Type::StockPledge: {
            return new StockPledgeStrategy();
        }
        case Strategy::Type::Unknown:
        default:
            throw "Invalid strategy type.\n";
    }
}


//Strategy::Strategy() {
    //double elecProp = 0.78;
    //double entryPrice = 7050;
    //double quantity = 38.4615;
    //double tProp = 0.576923;
    //double pProp = 0.338462;
    //double cProp = 0;
    //PledgePlatform pledgePlatform = PledgePlatform::BabelPledge;
    //double durationInDays = 90;
    //double tradeFee = 0;
    //double leverage = 1;
    //unsigned short netRefillTimesLimit = 1;
    //ContractSide contractSide = ContractSide::SellShort;

    //m_c = new Controller();

    //double refPrices[] = {4000, 4556, 5400, 6075, 7500, 8100, 9135, 10000, 12000, 14000,
                          //18000, 20000, 22400, 24000, 26000, 30000, 50000, 80000};
    //unsigned refPricesSize = sizeof(refPrices) / sizeof(double);
    //m_refPrices.insert(m_refPrices.end(), &refPrices[0], &refPrices[refPricesSize]);
//}

//Strategy::~Strategy() {
    //delete m_c;
//}

//void Strategy::run() {
    //cout << "Price\t\tQuantity" << endl;

    //for (auto &i : m_refPrices) {
        //double quantity = m_c->getQty(i);
        //cout << i << "\t\t" << quantity << endl;
    //}
//}

//double Strategy::getQty(double price) const {
    //return m_c->getQty(price);
//}
