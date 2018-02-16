#include <iostream>
#include <fstream>
#include <iomanip>
#include "plainvanilla_option.h"
#include "marketvariable.h"
#include "u_math.h"

/* Problem 1 */
int main(int argc, char **argv) {
    if (argc != 5) {
        std::cout << "Input error!" << std::endl;
        std::cout << "Usage: " << argv[0] << "   CRRRBoutput.csv  LRoutput.csv  CRRRBextrapolation.csv  LRextrapolation.csv" << std::endl;
        exit(1);
    }

    int minStep, maxStep;       /* step of trees */

    /* Set up output stream */
    std::ofstream crrrbout, lrout;
    crrrbout.open(argv[1], std::ios::app);
    lrout.open(argv[2], std::ios::app);

    /* Market Variable */
    MarketVariable mktVar(100, 0.02, 0.0, 0.35);

    /* Option setting */
    PlainVanillaOption option1(95, 1, Put);
    option1.setMarketVariable(mktVar);
    double bsp = option1.bsprice();

    /* Step of tree setting */
    minStep = 50;
    maxStep = 1000;

    crrrbout << "STEPS, CRR, RB" << std::endl;
    lrout << "STEPS, LR" << std::endl;

    /* Calculation for option price using binomial trees */
    for (int i = minStep; i <= maxStep; ++i) {
        double crrprice = option1.bntprice(i, CRR);
        double rbprice = option1.bntprice(i, RB);
        crrrbout << i << "," << (crrprice - bsp) << "," << (rbprice - bsp) << std::endl;
        if (i % 2 != 0) {
            double lrprice = option1.bntprice(i, LR);
            lrout << i << "," << (lrprice - bsp) << std::endl;
        }
    }
    std::cout << "Error Calculation completed successfully." << std::endl;

    /* Close output stream */
    crrrbout.close();
    lrout.close();

    /* Extrapolation Price */

    std::ofstream crrRbExtra, lrExtra;
    crrRbExtra.open(argv[3], std::ios::app);
    lrExtra.open(argv[4],std::ios::app);
    crrRbExtra << "N, M, CRR, RB" << std::endl;
    lrExtra << "N, M, LR" << std::endl;
    int stepSize1 = 25;                             /* Step size for CRR and RB */
    int stepSize2 = 50;                             /* Step size for LR */
    for (int i = 1; i <= 25; ++i) {
        double crrValue1 = option1.bntprice(i * stepSize1, CRR);
        double crrValue2 = option1.bntprice(2 * i * stepSize1, CRR);
        double rbValue1 = option1.bntprice(i * stepSize1, RB);
        double rbValue2 = option1.bntprice(2 * i * stepSize1, RB);
        double crrExtraValue = extrapolate(i * stepSize1, crrValue1, 2 * i * stepSize1, crrValue2);
        double rbExtraValue = extrapolate(i * stepSize1, rbValue1, 2 * i * stepSize1, rbValue2);
        crrRbExtra << i * stepSize1 << "," << 2 * i * stepSize1 << "," << (crrExtraValue - bsp) << "," << (rbExtraValue - bsp) << std::endl;
    }

    for (int i = 1; i <= 10; ++i) {
        double lrValue1 = option1.bntprice(i * stepSize2 + 1, LR);
        double lrValue2 = option1.bntprice(2 * i * stepSize2 + 1, LR);
        double lrExtraValue = extrapolate(i * stepSize2 + 1, lrValue1, 2 * i * stepSize2 + 1, lrValue2, 2);
        lrExtra << i * stepSize2 + 1 << "," << 2 * i * stepSize2 + 1 << "," << (lrExtraValue - bsp) << std::endl;
    }

    std::cout << "Extrpolation completed successfully." << std::endl;

    crrRbExtra.close();
    lrExtra.close();
    return 0;
}
