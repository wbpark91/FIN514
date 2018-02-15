#include <iostream>
#include <fstream>
#include <iomanip>
#include "american_option.h"
#include "marketvariable.h"

int main(int argc, char **argv) {
    /* Output stream */
    std::ofstream crrrbout, lrout, exerout;

    /* Parameter setting */
    MarketVariable mktVar(100, 0.02, 0.0, 0.35);
    AmericanOption option(95, 1.0, Put);
    option.setMarketVariable(mktVar);

    /* Real value from calualting 10000 steps */
    double value = 10.3762;

    int minStep = 50;
    int maxStep = 1000;

    crrrbout.open(argv[1], std::ios::app);
    lrout.open(argv[2], std::ios::app);
    exerout.open(argv[3], std::ios::app);

    crrrbout << "STEP" << "," << "CRR" << "," << "BD" << std::endl;
    lrout << "STEP" << "," << "LR" << std::endl;
    exerout << "STEP" << "," << "Boundary" << std::endl;
    for (int i = minStep; i <= maxStep; ++i) {
        crrrbout << i << "," << (option.bntprice(i, CRR) - value) << "," << (option.bntprice(i, BD) - value) << std::endl;
        if (i % 2 != 0) {
            lrout << i << "," << (option.bntprice(i, LR) - value) << std::endl;
        }
    }

    std::vector<double> bound = option.exerciseBound(100, CRR);
    for (int i = 0; i < bound.size(); ++i) {
        exerout << i+1 << "," << bound[bound.size() - (i+1)] << std::endl;
    }
    std::cout << bound.size() << std::endl;

    std::cout << "Calculation completed successfully." << std::endl;
    crrrbout.close();
    lrout.close();
    exerout.close();
    return 0;
}
