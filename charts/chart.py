import matplotlib.pyplot as plt
import numpy as np
import math

def drawChart(entryPrice, quantity, icl):
    liqPrice = entryPrice * icl / 0.9
    high = 180000
    t = np.arange(liqPrice, high, 10)

    slope = (quantity-icl*quantity*entryPrice/high) / (high - liqPrice)
    print(slope)
    idealRedeemPrice = math.sqrt(icl*quantity*entryPrice / slope)
    print(idealRedeemPrice)

    # plt.plot(t, 40+t-t, 'r--', t, 100-0.6*100*7200/t, 'b-')
    plt.axhline(y=quantity * (1 - icl), color='r', linestyle='--')
    plt.plot(t, quantity-icl*quantity*entryPrice/t, 'b-')      # 50, 7200

    # plt.axis([0,20000,0,20000])
    plt.xlabel('BTC/USDT')
    plt.ylabel('Quantity')
    plt.show()

def main():
    drawChart(7200, 50, 0.6)

if __name__ == "__main__":
    main()
