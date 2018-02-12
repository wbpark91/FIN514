#include <iostream>
#include <fstream>
#include <iomanip>
#include "plainvanilla_option.h"
#include "marketvariable.h"

int main(int argc, char **argv) {
    if (argc != 3) {
        std::cout << "Input error!" << std::endl;
        std::cout << "Usage: ./filename   CRRRBoutput.csv  LRoutput.csv" << std::endl;
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
    std::cout << "Calculation completed successfully." << std::endl;

    /* Close output stream */
    crrrbout.close();
    lrout.close();
    return 0;
}
