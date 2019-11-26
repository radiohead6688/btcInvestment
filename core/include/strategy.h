#pragma once

#include <vector>

#include "controller.h"

class Strategy {
public:
    Strategy();
    ~Strategy();

    void run();
private:
    std::vector<double> m_refPrices;

    Controller* m_c = nullptr;

};
