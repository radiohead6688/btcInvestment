import matplotlib.pyplot as plt
import numpy as np
import math

# def drawChart(entryPrice, quantity, icl):
    # liqPrice = entryPrice * icl / 0.9
    # high = 180000
    # t = np.arange(liqPrice, high, 10)

    # slope = (quantity-icl*quantity*entryPrice/high) / (high - liqPrice)
    # print(slope)
    # idealRedeemPrice = math.sqrt(icl*quantity*entryPrice / slope)
    # print(idealRedeemPrice)

    # # plt.plot(t, 40+t-t, 'r--', t, 100-0.6*100*7200/t, 'b-')
    # plt.axhline(y=quantity * (1 - icl), color='r', linestyle='--')
    # plt.plot(t, quantity-icl*quantity*entryPrice/t, 'b-')      # 50, 7200

    # # plt.axis([0,20000,0,20000])
    # plt.xlabel('BTC/USDT')
    # plt.ylabel('Quantity')
    # plt.show()

# def drawPledgeBtcValue(collaQty, entryPrice):
    # low = 6000
    # high = 15000
    # prices = np.arange(low, high, 100)

    # plt.plot(prices, collaQty - collaQty * entryPrice * 0.6 / prices, 'b-')
    # # plt.plot(prices, collaQty * 0.4 + (1/entryPrice - 1/prices) * collaQty * 0.4 * entryPrice * 3, 'g-')

    # plt.axhline(collaQty - collaQty * 0.6, color='r', linestyle='--', label='10000')
    # plt.xlabel('BTC/USDT')
    # plt.ylabel('Quantity')
    # plt.legend()
    # plt.grid()
    # plt.show()
    # return

# def drawBtcValue(entryPrice, collaQty, btcQty, usdtQty):
    # low = 6000
    # high = 12000
    # prices = np.arange(low, high, 100)

    # plt.plot(prices, (collaQty+btcQty) + (usdtQty - collaQty * entryPrice * 0.6) / prices, 'b-')

    # plt.axhline((collaQty+btcQty) + (usdtQty - collaQty * entryPrice * 0.6) / entryPrice, color='r', linestyle='--', label=str(entryPrice))

    # plt.xlabel('BTC/USDT')
    # plt.ylabel('Quantity')
    # plt.legend()
    # plt.grid()
    # plt.show()
    # return

def simulation():
    entryPrice = 8100
    collaBal = 50
    btcBal = 0.5134
    usdtBal = 203281.4339

    compareBtcBal = 45.1033

    elecCnyQty = 560000
    usdtCnyPrice = 7.0
    payElecPrice = 9500

    compareBtcQty = elecCnyQty / usdtCnyPrice / payElecPrice * 1.01
    compareBtcBal1 = compareBtcBal - compareBtcQty

    # pay elec with usdt only
    btcQty = 0
    usdtQty = elecCnyQty / usdtCnyPrice - btcQty * payElecPrice * 0.993
    btcBal1 = btcBal - btcQty
    usdtBal1 = usdtBal - usdtQty

    # pay elec with usdt and btc
    # btcQty = 0.5134
    # usdtQty = elecCnyQty / usdtCnyPrice - btcQty * payElecPrice * 0.993
    # btcBal2 = btcBal - btcQty
    # usdtBal2 = usdtBal - usdtQty

    elecCnyQty = 560000
    usdtCnyPrice = 7.0
    payElecPrice = 8500

    compareBtcQty = elecCnyQty / usdtCnyPrice / payElecPrice * 1.01
    compareBtcBal2 = compareBtcBal - compareBtcQty

    # pay elec with usdt only
    btcQty = 0
    usdtQty = elecCnyQty / usdtCnyPrice - btcQty * payElecPrice * 0.993
    btcBal2 = btcBal - btcQty
    usdtBal2 = usdtBal - usdtQty

    elecCnyQty = 560000
    usdtCnyPrice = 7.0
    payElecPrice = 10500

    compareBtcQty = elecCnyQty / usdtCnyPrice / payElecPrice * 1.01
    compareBtcBal3 = compareBtcBal - compareBtcQty

    # pay elec with usdt only
    btcQty = 0
    usdtQty = elecCnyQty / usdtCnyPrice - btcQty * payElecPrice * 0.993
    btcBal3 = btcBal - btcQty
    usdtBal3 = usdtBal - usdtQty

    low = 6000
    high = 15000
    prices = np.arange(low, high, 10)

    plt.axhline(compareBtcBal3, color='g', linestyle='--', label='10500')
    plt.plot(prices, (collaBal+btcBal3) + (usdtBal3-243000) / prices, 'y-')

    plt.axhline(compareBtcBal1, color='b', linestyle='--', label='9500')
    plt.plot(prices, (collaBal+btcBal1) + (usdtBal1-243000) / prices, 'y-')

    plt.axhline(compareBtcBal2, color='r', linestyle='--', label='8500')
    plt.plot(prices, (collaBal+btcBal2) + (usdtBal2-243000) / prices, 'y-')

    plt.xlabel('BTC/USDT')
    plt.ylabel('Quantity')

    xTicks = np.arange(low, high, 1000)
    yTicks = np.arange(30, 45, 0.5)
    plt.xticks(xTicks)
    plt.yticks(yTicks)

    plt.legend()
    # plt.grid()
    plt.show()


def drawExample(prices, entryPrice, collaQty, btcQty, usdtQty):
    plt.plot(prices, (collaQty+btcQty) + (usdtQty - collaQty * entryPrice * 0.6) / prices, 'b-')
    plt.axhline((collaQty+btcQty) + (usdtQty - collaQty * entryPrice * 0.6) / entryPrice, color='b', linestyle='--', label=str(entryPrice))
    return

def compareBuyBackAndFullyReserved(entryPrice):
    low = 6000
    high = 15000
    prices = np.arange(low, high, 100)
    icl = 0.6

    # fully reserved
    # collaQty = 53.8374
    # btcQty = 0.7368
    # usdtQty = 129673.1
    # initQty = (collaQty+btcQty) + (usdtQty - collaQty * entryPrice * icl) / entryPrice
    # plt.plot(prices, (collaQty+btcQty) + (usdtQty - collaQty * entryPrice * icl) / prices - initQty, 'b-')

    # sell and buy back
    collaQty = 53.2766
    btcQty = 13.5076 + 0.7291
    usdtQty = 0.0
    initQty = (collaQty+btcQty) + (usdtQty - collaQty * entryPrice * icl) / entryPrice
    plt.plot(prices, (collaQty+btcQty) + (usdtQty - collaQty * entryPrice * icl) / prices - initQty, 'g-')

    plt.axhline(0.0, color='r', linestyle='--')

    xTicks = np.arange(low, high, 1000)
    yTicks = np.arange(-20, 15, 1)
    plt.xticks(xTicks)
    plt.yticks(yTicks)

    plt.xlabel('BTC/USDT')
    plt.ylabel('Quantity')
    plt.grid()
    plt.show()
    return

def main():
    # drawChart(7200, 50, 0.6)
    # simulation()
    # drawPledgeBtcValue(1, 10000)
    compareBuyBackAndFullyReserved(9500)

if __name__ == "__main__":
    main()
