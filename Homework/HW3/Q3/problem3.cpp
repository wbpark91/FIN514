#include <iostream>
#include <fstream>
#include <iomanip>
#include "continuous_barrier_option.h"
#include "marketvariable.h"

int main(int argc, char **argv) {
    std::ofstream barrierOut;

    ContinuousBarrierOption option(100, 95, 0.5, Call, DO);
    MarketVariable mktVar(100, 0.1, 0.0, 0.3);
    option.setMarketVariable(mktVar);

    barrierOut.open(argv[1], std::ios::app);
    barrierOut << "STEPS" << "," << "ERROR" << "," << "LAMBDA" << std::endl;

    double bsp = option.bsprice();

    int minStep = 50;
    int maxStep = 1000;

    for (int i = minStep; i <= maxStep; ++i) {
        barrierOut << i << "," << (option.bntprice(i, CRR) - bsp) << "," << option.getLambda(option.getBarrier(), i, i, CRR) << std::endl;
    }
    std::cout << "Error calculation completed successfully." << std::endl;

    barrierOut.close();
    return 0;
}
