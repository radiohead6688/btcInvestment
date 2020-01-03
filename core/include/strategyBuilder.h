#pragma once

#include "miningFarm.h"
#include "miner.h"
#include "strategy.h"
#include "trade.h"
#include "pledge.h"
#include "contract.h"
#include "log.h"

void calculateStrategyByFixedElecFee(double elecFeeUsdt);

void calculateStrategyByFixedQuantity(double quantity, double elecQty);

void getCollaQtyByFixedLoan(double elecFeeUsdt, double entryPrice, unsigned short duration,
        unsigned short netRefillTimesLimit);

void testStrategy();

double getDailyElecFeeCNY(double power, double elecFeePerKwh);

double getDailyIncomeCNY(double hashrate, double dailyIncomeCNYPerTHS);

double getElecProp(double elecFeeCNY, double dailyIncomeCNY);

double calculateElecFeeCNY(double usdtCNYRate, double price);
