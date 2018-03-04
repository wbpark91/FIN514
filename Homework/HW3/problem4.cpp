#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include "discrete_barrier_option.h"
#include "marketvariable.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cout << "Input error!" << std::endl;
        std::cout << "Usage: " << argv[0] << "  filename.csv" << std::endl;
        exit(1);
    }

    std::ofstream barrierOut;

    std::vector<double> barrierDate = { 0.04, 0.08, 0.12, 0.16 };
    DiscreteBarrierOption option(100, 95, 0.2, Call, barrierDate, DO);
    MarketVariable mktVar(100, 0.1, 0.0, 0.3);
    option.setMarketVariable(mktVar);

    barrierOut.open(argv[1], std::ios::app);
    barrierOut << "STEPS" << "," << "ERROR" << "," << "LAMBDA" << std::endl;

    double analytic = 5.6711051343; /* Analytic Value */

    int minStep = 5;
    int maxStep = 100;

    for (int i = minStep; i <= maxStep; ++i) {
        /* Get lambda at t = 1.6 */
        barrierOut << i * 10 << "," << (option.bntprice(i * 10, CRR) - analytic) << "," << option.getLambda(option.getBarrier(), i * 10, i * 8, CRR) << std::endl;
    }
    std::cout << "Error calculation completed successfully." << std::endl;

    barrierOut.close();
    return 0;
}
