#pragma once

#include "strategy.h"
#include "trade.h"
#include "pledge.h"
#include "contract.h"
#include "log.h"


struct Configs {
    struct {
        Trade* ptr = nullptr;
        double quantity = 0;
    } trade;

    struct {
        Pledge* ptr = nullptr;
        double quantity = 0;
        unsigned short duration = 0;
        unsigned short netRefillTimesLimits = 0;
    } pledge;

    struct {
        Contract* ptr = nullptr;
        double quantity = 0;
    } contract;

    double usdtLoanAmnt = 0;
    double entryPrice = 0;
    double elecProp = 0;
    double elecFee = 0;
};

void calculateStrategy(double elecFeeUsdt);

void getCollaQtyByFixedLoan(double elecFeeUsdt, double entryPrice, unsigned short duration,
        unsigned short netRefillTimesLimit);

void testStrategy();

double getDailyElecFeeCNY(double power, double elecFeePerKwh);

double getDailyIncomeCNY(double hashrate, double dailyIncomeCNYPerTHS);

double getElecProp(double elecFeeCNY, double dailyIncomeCNY);
