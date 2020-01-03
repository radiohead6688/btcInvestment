#pragma once

#include "trade.h"
#include "pledge.h"
#include "contract.h"
#include "kline.h"

#include <memory>

class Portfolio {
public:
    virtual ~Portfolio() = default;

    double getBtcBal() const { return m_stock->getBtyQty(); }

    double getUsdtBal() const { return m_stock->getUsdtQty(); }

    double getUsdtValueInBtc(double usdtQty) const;

    //double getPrice() const;

    void purchaseBtc(double netQty) { m_stock->purchaseBtc(m_priceLow, netQty); }

    //void sellBtc(double qty) { m_stock->sellBtc(); }

    void decrBtcBal(double qty) { m_stock->decrBtcQty(qty); }

    void incrBtcBal(double qty) { m_stock->incrBtcQty(qty); }

    void incrUsdtBal(double qty) { m_stock->incrUsdtQty(qty); }

    // TODO: change to event-driven
    void updateKline(Kline const& kline);

public:
    double getTradeFee() const { return m_stock->getTradeFee(); }

public:
    virtual double evaluateQty() const = 0;

    virtual void onUpdate() = 0;

protected:
    Portfolio(std::unique_ptr<Stock> stock) : m_stock(std::move(stock)) { };

    std::unique_ptr<Stock> m_stock = nullptr;

    double m_priceLow;
};

class StockOnlyPortfolio : public Portfolio {
public:
    StockOnlyPortfolio(std::unique_ptr<Stock> stock);

    double evaluateQty() const override { return m_stock->evaluateQty(m_priceLow); }

    void onUpdate() override { m_stock->update(m_priceLow); }
};

class StockPledgePortfolio : public Portfolio {
public:
    StockPledgePortfolio(std::unique_ptr<Stock> stock, std::unique_ptr<Pledge> pledge);

    double evaluateQty() const override;

    void onUpdate() override;

protected:
    std::unique_ptr<Pledge> m_pledge = nullptr;
};

//class PortfolioFactory {
//public:
    //enum class Type : uint16_t {
        //StockOnly               = 0x01,
        //StockPledge             = 0x02,
        //[> Add new platform <]

        //Unknown = 0xFFFF,
    //};

    //static Portfolio* createPortfolio(Type type);
//};

//class Controller {
//public:
    //Controller() = default;

    //~Controller() = default;

    //double getBtcBal() const { return m_btcBal; }

    //double getUsdtBal() const { return m_usdtBal; }

    //double getPrice() const;

    //void purchaseBtc(double qty) { m_stock->purchaseBtc(); }

    //void sellBtc(double qty) { m_stock->sellBtc(); }

     //Trade interface 
    //void initTrade(double tProp, double tradeFee);
    //void sell(double quantity, double price);
    //void purchase(double quantity, double price);

     //Pledge interface 
    //void initPledge(double pProp, PledgePlatform pPlatform);
    //double getPledgeQty(double price);
    //double getRefillPriceRatio() const;
    //double getLiqPriceRatio() const;
    //void refillPledge();
    //void endPledge(double price);

     //Contract interface 
    //void initContract(double cProp, double leverage, ContractSide side);

    //double evaluateQty(double price, double usdtAmnt) const;
    //double getQty(double price);
    //void payElecFee();

//private:
    //std::unique_ptr<Pledge> m_pledge;

    //std::unique_ptr<Stock> m_stock;
//};
