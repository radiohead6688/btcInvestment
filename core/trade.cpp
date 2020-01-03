#include "trade.h"

#include <iostream>
#include <cassert>

double TradeBase::getUsdtNeeded(double price, double tartgetQty) const {
    return price * tartgetQty / (1 - m_feeRate);
}

double TradeBase::getBuyableQty(double price, double usdtAmnt) const {
    return (usdtAmnt / price) * (1 - m_feeRate);
}

std::unique_ptr<TradeBase> TradeFactory::createTrade(Platform platform) {
    switch (platform) {
        case Platform::Offline:
            return std::make_unique<OfflineTrade>();
        case Platform::Unknown:
        default:
            throw "Invalid trade platform.\n";
    }
}

Stock::Stock(std::unique_ptr<TradeBase> platform, double btcQty, double usdtQty)
        : m_platform(std::move(platform)),
          m_btcQty(btcQty),
          m_usdtQty(usdtQty) {
}

double Stock::getUsdtValueInBtc(double price, double usdtQty) const {
    return m_platform->getBuyableQty(price, usdtQty);
}

void Stock::incrBtcQty(double qty) {
    m_btcQty += qty;
}

void Stock::decrBtcQty(double qty) {
    if (m_btcQty < qty) {
        std::cout << "Insufficient btc balance!\n";
        return;
    }

    m_btcQty -= qty;
}

void Stock::incrUsdtQty(double qty) {
    m_usdtQty += qty;
}

void Stock::purchaseBtc(double price, double netQty) {
    // TODO:insanity check
    assert(netQty > 0);

    double usdtRequired = m_platform->getUsdtNeeded(price, netQty);

    if (usdtRequired < m_usdtQty) {
        std::cout << "Failed to purchase btc. Insufficient usdt balance!\n"
             << "Need: " << usdtRequired << " usdt\n"
             << "USDT Balance: " << m_usdtQty << " usdt\n";

        return;
    }

    m_usdtQty -= usdtRequired;
    m_btcQty += netQty;

    std::cout << "Purchased " << netQty << " btc at price " << price
         << " using " << usdtRequired * price << " usdt.\n";
}


//void Stock::sellBtc(double price, double targetQty) {
    //if (targetQty == 0) {
        //return;
    //}

    //double quantity = m_platform->getTradeQty(targetQty);
    //if (quantity > m_btcQty) {
        //cout << "Failed to sell btc at the desired quantity. Insufficient balance!\n"
             //<< "Need: " << quantity << endl
             //<< "Balance: " << m_balance << endl;
        //exit(-1);
    //}

    //m_balance -= quantity;
    //m_usdtBalance += targetQty * price;

    //cout << "Sold " << quantity << " btc at price " << price
         //<< " for " << targetQty * price << " usdt.\n";
//}

double Stock::evaluateQty(double price) {
    return m_btcQty + getUsdtValueInBtc(price, m_usdtQty);
}
