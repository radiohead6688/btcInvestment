#include "portfolio.h"

#include <iostream>

using std::cout;
using std::endl;

//Portfolio* PortfolioFactory::createPortfolio(Type type) {
    //switch (type) {
        //case Type::StockOnly:
            //return new StockOnlyPortfolio();
        //case Type::StockPledge:
            //return new StockPledgePortfolio();
        //case Type::Unknown:
        //default:
            //throw "Invalid controller type.\n";
    //}
//}

void Portfolio::updateKline(Kline const& kline) {
    m_priceLow = kline.getLow();
}

double Portfolio::getUsdtValueInBtc(double usdtQty) const {
    return m_stock->getUsdtValueInBtc(m_priceLow, usdtQty);
}

StockOnlyPortfolio::StockOnlyPortfolio(std::unique_ptr<Stock> stock)
        : Portfolio(std::move(stock)) {
}

StockPledgePortfolio::StockPledgePortfolio(std::unique_ptr<Stock> stock,
        std::unique_ptr<Pledge> pledge)
        : Portfolio(std::move(stock)), m_pledge(std::move(pledge)) {
}

double StockPledgePortfolio::evaluateQty() const {
    return m_stock->evaluateQty(m_priceLow) + m_pledge->evaluateQty();
}

void StockPledgePortfolio::onUpdate() {
    m_pledge->update(m_priceLow);
    m_stock->update(m_priceLow);
}

//void Controller::decrBtcBal(double btcAmnt) {
    //if (m_btcBal <= btcAmnt) {
        //std::cout << "Insufficient btc balance." << std::endl;
        //return;
    //}
    //m_btcBal -= btcAmnt;
//}

//void Controller::decrUsdtBal(double usdtAmnt) {
    //if (m_usdtBal <= usdtAmnt) {
        //std::cout << "Insufficient usdt balance." << std::endl;
        //return;
    //}
    //m_usdtBal -= usdtAmnt;
//}

//void Controller::purchaseBtc(double qty) {
    //double price = m_op->getPrice();
    //double usdtAmnt = m_trade->getUsdtNeeded(price, qty);

    //decrUsdtBal(usdtAmnt);
    //incrBtcBal(qty);
//}

//double Controller::getQty() const {
    //double price = m_op->getPrice();
    //return m_btcBal + m_trade->getBuyableQty(price, m_usdtBal);
//}


//ct::ct()
        //: m_entryPrice(ARGs.m_entryPrice), m_initQty(ARGs.m_quantity), m_elecQty(ARGs.m_elecQty),
        //m_pledgeDuration(ARGs.m_pledge.durationInDays),
        //m_netRefillTimesLimit(ARGs.m_pledge.netRefillTimesLimit)
//{
    //m_balance += m_initQty;

    //[> initiate m_trade <]
    //switch (ARGs.m_trade.platform) {
        //case TradePlatform::OfflineTrade:
            //m_trade = new OfflineTrade();
            //break;
        //default:
            //break;
    //}

    //sell(m_initQty * ARGs.m_trade.prop, m_entryPrice);

    //[> initiate m_pledge <]
    //switch (ARGs.m_pledge.platform) {
        //case PledgePlatform::BabelPledge:
            //m_pledge = new BabelPledge();
            //break;
        //case PledgePlatform::GateioPledge:
            //m_pledge = new GateioPledge();
            //break;
        //case PledgePlatform::MatrixportPledge:
            //break;
        //default:
            //break;
    //}

    //double pledgeQty = ARGs.m_pledge.prop * m_initQty;
    //if (pledgeQty > m_balance) {
        //cout << "Failed to initiate pledge. Insufficient balance" << endl
             //<< "Need: " << pledgeQty << endl
             //<< "Balance: " << m_balance << endl;
        //exit(-1);
    //}
    //m_balance -= pledgeQty;
    //m_pledgeQty = pledgeQty;
    //m_initPledgeQty = m_pledgeQty;
    //m_usdtBalance += m_pledge->getInitCollaLevel() * m_pledgeQty * m_entryPrice;

    //[> initiate m_contract<]
    //switch (ARGs.m_contract.platform) {
        //case ContractPlatform::BitmexContract:
            //m_contract = new BitmexContract(ARGs.m_contract.leverage, ARGs.m_contract.side);
            //break;
        //default:
            //break;
    //}

    //double contractQty = ARGs.m_contract.prop * m_initQty;
    //if (contractQty > m_balance) {
        //cout << "Failed to initiate contract. Insufficient balance" << endl
             //<< "Need: " << contractQty << endl
             //<< "Balance: " << m_balance << endl;
        //exit(-1);
    //}
    //m_balance -= contractQty;
    //m_contractQty = contractQty;

    //payElecFee();

    //cout << "Balance: " << m_balance << endl;

    ////TODO: change m_pledge to real days
    //m_pledgePast = m_pledgeDuration;
//}

//ct::~ct() {
    //delete m_trade;
    //delete m_pledge;
    //delete m_contract;
//}

//// Trade interface
//void ct::initTrade(double tProp, double tradeFee) {
    //TradePlatform tPlatform = TradePlatform::OfflineTrade;
    //switch (tPlatform) {
        //case TradePlatform::OfflineTrade:
            //m_trade = new OfflineTrade();
            //break;
        //default:
            //break;
    //}

    //sell(m_initQty * tProp, m_entryPrice);
//}

//// Pledge interface
//void ct::initPledge(double pProp, PledgePlatform pPlatform) {
    //switch (pPlatform) {
        //case PledgePlatform::BabelPledge:
            //m_pledge = new BabelPledge();
            //break;
        //case PledgePlatform::GateioPledge:
            //m_pledge = new GateioPledge();
            //break;
        //case PledgePlatform::MatrixportPledge:
            //break;
        //default:
            //break;
    //}

    //double pledgeQty = pProp * m_initQty;
    //if (pledgeQty > m_balance) {
        //cout << "Failed to initiate pledge. Insufficient balance" << endl
             //<< "Need: " << pledgeQty << endl
             //<< "Balance: " << m_balance << endl;
        //exit(-1);
    //}
    //m_balance -= pledgeQty;
    //m_pledgeQty = pledgeQty;
    //m_initPledgeQty = m_pledgeQty;
    //m_usdtBalance += m_pledge->getInitCollaLevel() * m_pledgeQty * m_entryPrice;
//}

//double ct::getRefillPriceRatio() const {
    //return m_pledge->getRefillPriceRatio(m_refilledTimes - m_refundedTimes);
//}

//double ct::getLiqPriceRatio() const {
    //return m_pledge->getLiqPriceRatio(m_refilledTimes - m_refundedTimes);
//}

//double ct::getPledgeQty(double price) {
    //if (m_pledgeQty == 0.0) {
        //return 0.0;
    //}

    //double priceRatio = price / m_entryPrice;
    //if (priceRatio <= getRefillPriceRatio() &&
            //m_refilledTimes - m_refundedTimes < m_netRefillTimesLimit) {
        //refillPledge();
    //}

    //if (priceRatio <= getLiqPriceRatio()) {
        //m_pledge = 0;
        //m_pledgeLiquidated = true;
        //cout << "Pledge liquidated :(" << endl;
        //return 0;
    //}

    //return m_pledge->getQty(m_entryPrice, price, m_pledgeQty, m_initPledgeQty, m_pledgePast,
            //m_refilledTimes - m_refundedTimes);
//}

//void ct::refillPledge() {
    //if (m_refilledTimes - m_refundedTimes > m_netRefillTimesLimit) {
        //cout << "Unable to refill. Reached net refill times limit: "
             //<< m_netRefillTimesLimit << endl;
        //return;
    //}

    //double refillQty = m_initPledgeQty *
        //m_pledge->getRefillCollaRatio(m_refilledTimes - m_refundedTimes);

    //increasePledge(refillQty);
    //m_refilledTimes += 1;
    //cout << "Refilled pledge with " << refillQty << " btc." << endl;
//}

//void ct::endPledge(double price) {
    //if (m_pledgeQty == 0) {
        //return;
    //}

    //double quantity = m_pledge->getQty(m_entryPrice, price, m_pledgeQty, m_initPledgeQty,
            //m_pledgePast, m_refilledTimes - m_refundedTimes);
    //m_pledgeQty = 0;
    //m_balance += quantity;
    //cout << "Ended pledge. Get " << quantity << " btc back." << endl;
//}

//void ct::increasePledge(double quantity) {
    //if (quantity > m_balance) {
        //cout << "Failed to increase pledge. Insufficient balance" << endl
             //<< "Need: " << quantity << endl
             //<< "Balance: " << m_balance << endl;
        //return;
    //}
    //m_balance -= quantity;
    //m_pledgeQty += quantity;
//}

//// Contract interface
//void ct::initContract(double cProp, double leverage, ContractSide side) {
    //ContractPlatform cPlatform = ContractPlatform::BitmexContract;
    //switch (cPlatform) {
        //case ContractPlatform::BitmexContract:
            //m_contract = new BitmexContract(leverage, side);
            //break;
        //default:
            //break;
    //}

    //double contractQty = cProp * m_initQty;
    //if (contractQty > m_balance) {
        //cout << "Failed to initiate contract. Insufficient balance" << endl
             //<< "Need: " << contractQty << endl
             //<< "Balance: " << m_balance << endl;
        //exit(-1);
    //}
    //m_balance -= contractQty;
    //m_contractQty = contractQty;
//}

//double ct::getQty(double price) {
    //return m_balance
         //+ evaluateQty(price, m_usdtBalance)
         //+ getPledgeQty(price)
         //+ m_contractQty * m_contract->getROEPct(m_entryPrice, price);
//}

//void ct::payElecFee() {
    //double elecFee = m_elecQty * m_entryPrice;
    //if (elecFee > m_usdtBalance) {
        //cout << "Failed to pay electricity fee. Insufficient usdt balance" << endl
             //<< "Need: " << elecFee << endl
             //<< "USDT Balance: " << m_usdtBalance << endl;
        //exit(-1);
    //}
    //m_usdtBalance -= elecFee;
    //cout << "Paid electricity fee of " << elecFee << " usdt" << endl;
//}

//double ct::evaluateQty(double price, double usdtAmnt) const {
    //return m_trade->getBuyableQty(price, usdtAmnt);
//}
