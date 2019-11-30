#pragma once

#include "trade.h"
#include "pledge.h"
#include "contract.h"

class Controller {
public:
    Controller(double elecProp, double entryPrice, double quantity, double tProp, double pProp,
            double cProp, PledgePlatform pPlatform, unsigned short days, double tradeFee, double leverage,
            ContractSide contractSide, double netRefillTimesLimit);

    ~Controller();

    /* Trade interface */
    void initTrade(double tProp, double tradeFee);
    void sell(double quantity, double price);
    void purchase(double quantity, double price);

    /* Pledge interface */
    void initPledge(double pProp, PledgePlatform pPlatform);
    double getPledgeQty(double price);
    double getRefillPriceRatio() const;
    double getLiqPriceRatio() const;
    void refillPledge();
    void endPledge(double price);

    /* Contract interface */
    void initContract(double cProp, double leverage, ContractSide side);

    double getQty(double price);
    void payElecFee();

private:
    void increasePledge(double quantity);

private:
    const double m_initQty;
    const double m_elecProp;
    const double m_elecQty;
    const double m_entryPrice;
    const unsigned short m_pledgeDuration;
    const unsigned short m_netRefillTimesLimit;

    Trade* m_trade = nullptr;
    Contract* m_contract = nullptr;
    Pledge* m_pledge = nullptr;

    double m_contractQty= 0;

    double m_pledgeQty = 0;
    double m_initPledgeQty = 0;;
    unsigned short m_pledgePast = 0;
    unsigned short m_refilledTimes = 0;
    unsigned short m_refundedTimes = 0;
    bool m_pledgeLiquidated = false;

    double m_balance = 0;

    double m_usdtBalance = 0;
};

