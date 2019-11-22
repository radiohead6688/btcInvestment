#include <assert.h>
#include "holding.h"

double Holding::getValue(double price, double quantity) const
{
    return price * quantity;
}

double Holding::getSellValue(double price, double quantity) const
{
    return price * quantity * (1 - m_fee);
}

double Holding::getBuyQuantity(double price, double usdtQuantity) const
{
    return (usdtQuantity / price) * (1 - m_fee);
}
