#include <iostream>
#include <fstream>
#include <iomanip>
#include "american_option.h"
#include "marketvariable.h"

int main(int argc, char **argv) {
    /* Output stream */
    std::ofstream optionPrice;
    optionPrice.open(argv[1], std::ios::app);
    optionPrice << "STEPS" << "," << "VALUE" << "," << "DIFF" << std::endl;
    MarketVariable mktVar(100, 0.02, 0.0, 0.35);
    AmericanOption option1(95, 1, Put);
    option1.setMarketVariable(mktVar);

    for (int i = 10000; i < 10020; ++i) {
        double price1 = option1.bntprice(i - 1, BD);
        double price2 = option1.bntprice(i, BD);
        optionPrice << i << "," << price2 << "," << (price2 - price1) << std::endl;
        std::cout << i << std::endl;
    }
    return 0;
}
