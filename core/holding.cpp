#include "holding.h"

Holding::Holding()
{
}

double Holding::getValue(double price, double quantity) const
{
    return price * quantity;
}
