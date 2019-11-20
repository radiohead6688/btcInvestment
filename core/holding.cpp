#include "holding.h"

double Holding::getValue(double price, double quantity) const
{
    return price * quantity;
}
