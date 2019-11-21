#include <assert.h>
#include "holding.h"

double Holding::getValue(double price) const
{
    return price * m_balance;
}

double Holding::sell(double price, double quantity)
{
    assert(quantity <= m_balance);

    m_balance -= quantity;
    return price * quantity * (1 - m_fee);
}

double Holding::buy(double quantity)
{
    m_balance += quantity * (1 - m_fee);
    return m_balance;
}
