#include <iostream>
#include <fstream>
#include <iomanip>
#include "american_option.h"
#include "marketvariable.h"
#include "u_math.h"

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

    /* Calculate American Option Value */
    for (int i = minStep; i <= maxStep; ++i) {
        crrrbout << i << "," << (option.bntprice(i, CRR) - value) << "," << (option.bntprice(i, BD) - value) << std::endl;
        if (i % 2 != 0) {
            lrout << i << "," << (option.bntprice(i, LR) - value) << std::endl;
        }
    }
    std::cout << "Calculation of American option value completed successfully." << std::endl;

    /* Calculate Exercise Bound */
    std::vector<double> bound = option.exerciseBound(100, CRR);
    for (int i = 0; i < bound.size(); ++i) {
        exerout << i+1 << "," << bound[bound.size() - (i+1)] << std::endl;
    }

    std::cout << "Calculation of exercise bound completed successfully." << std::endl;

    /* Calculate Extrapolation */
    std::ofstream crrBdExtra, lrExtra;
    crrBdExtra.open(argv[4], std::ios::app);
    lrExtra.open(argv[5],std::ios::app);
    crrBdExtra << "N, M, CRR, BD" << std::endl;
    lrExtra << "N, M, LR" << std::endl;
    int stepSize1 = 25;                             /* Step size for CRR and RB */
    int stepSize2 = 50;                             /* Step size for LR */
    for (int i = 1; i <= 25; ++i) {
        double crrValue1 = option.bntprice(i * stepSize1, CRR);
        double crrValue2 = option.bntprice(2 * i * stepSize1, CRR);
        double bdValue1 = option.bntprice(i * stepSize1, BD);
        double bdValue2 = option.bntprice(2 * i * stepSize1, BD);
        double crrExtraValue = extrapolate(i * stepSize1, crrValue1, 2 * i * stepSize1, crrValue2);
        double bdExtraValue = extrapolate(i * stepSize1, bdValue1, 2 * i * stepSize1, bdValue2);
        crrBdExtra << i * stepSize1 << "," << 2 * i * stepSize1 << "," << (crrExtraValue - value) << "," << (bdExtraValue - value) << std::endl;
    }

    for (int i = 1; i <= 10; ++i) {
        double lrValue1 = option.bntprice(i * stepSize2 + 1, LR);
        double lrValue2 = option.bntprice(2 * i * stepSize2 + 1, LR);
        double lrExtraValue = extrapolate(i * stepSize2 + 1, lrValue1, 2 * i * stepSize2 + 1, lrValue2);
        lrExtra << i * stepSize2 + 1 << "," << 2 * i * stepSize2 + 1 << "," << (lrExtraValue - value) << std::endl;
    }

    std::cout << "Extrpolation completed successfully." << std::endl;

    crrBdExtra.close();
    lrExtra.close();
    crrrbout.close();
    lrout.close();
    exerout.close();
    return 0;
}
