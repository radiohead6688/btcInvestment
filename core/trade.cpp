#include <assert.h>
#include "trade.h"

double Trade::getValue(double price, double quantity) const {
    return price * quantity;
}

/*
 * @brief Calculate the quantity which takes trading fee into consideration
 * @param targetQty         target quantity
 * @return Returns trade quantity
 */
double Trade::getTradeQty(double targetQty) const {
    return targetQty / (1 - m_fee);
}
