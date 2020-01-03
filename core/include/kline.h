#pragma once

class Kline {
public:
    Kline(double open, double close, double high, double low);

    double getLow() const { return m_low; }

private:
    double m_open;
    double m_close;
    double m_high;
    double m_low;
};
