#include <assert.h>
#include "holding.h"

double Holding::getValue(double price, double quantity) const
{
    return price * quantity;
}

/*
 * @brief Calculate the quantity which takes trading fee into consideration
 * @param targetQty         target quantity
 * @return Returns trade quantity
 */
double Holding::getTradeQty(double targetQty) const
{
    return targetQty / (1 - m_fee);
}
