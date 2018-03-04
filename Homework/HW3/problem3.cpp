#include <iostream>
#include <fstream>
#include <iomanip>
#include "continuous_barrier_option.h"
#include "marketvariable.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cout << "Input error!" << std::endl;
        std::cout << "Usage: " << argv[0] << "  filename.csv" << std::endl;
        exit(1);
    }
    
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
