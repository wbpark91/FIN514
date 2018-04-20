#include <iostream>
#include <fstream>
#include <ctime>
#include "cont_cpn_buf.h"
#include "marketvariable.h"
#include "forex.h"

int main(void) {
    std::ofstream output;
    clock_t t1, t2, t3, t4;
    MarketVariable mktVar(100, 0.01635483, 0.035692, 0.1747);
    Forex forex = {0.00001306, 0.0967};
    ContCpnBuf ccbf(1000, 0.07, 3.75, 87, 0.12, Month);
    ccbf.setMarketVariable(mktVar);
    ccbf.setForex(forex);
    ccbf.setCorr(0.1711);

    t1 = clock();
    std::cout << "EFDM Price: " << ccbf.fdmprice(30000, 250, Exp, 250) << std::endl;
    t2 = clock();
    std::cout << "EFDM Delta: " << ccbf.fdmdelta() << std::endl;
    std::cout << "EFDM Gamma: " << ccbf.fdmgamma() << std::endl;
    t3 = clock();
    std::cout << "CN Price: " << ccbf.fdmprice(3000, 500, CN, 500) << std::endl;
    t4 = clock();
    std::cout << "CN Delta: " << ccbf.fdmdelta() << std::endl;
    std::cout << "CN Gamma: " << ccbf.fdmgamma() << std::endl;

    std::cout << "EFDM calculation time: " << ((double)(t2 - t1) / CLOCKS_PER_SEC) << std::endl;
    std::cout << "CN calculation time: " << ((double)(t4 - t3) / CLOCKS_PER_SEC) << std::endl;

    // output.open("corr.csv", std::ios::app);
    // output << "Correlation,EFDM,Crank-Nicolson" << std::endl;
    // for (int i = -20; i <= 20; ++i) {
    //     double corr = i / 20.0;
    //     ccbf.setCorr(corr);
    //     output << corr << "," << ccbf.fdmprice(30000, 250, Exp, 250) << ","
    //         << ccbf.fdmprice(3000, 500, CN, 500) << std::endl;
    // }
    // ccbf.setCorr(0.1711);
    // output.close();
    //
    // output.open("div.csv", std::ios::app);
    // output << "Dividend,EFDM,Crank-Nicolson" << std::endl;
    // for (int i = 0; i <= 45; ++i) {
    //     double q = 0.01 + i / 1000.0;
    //     MarketVariable mktVar2(100, 0.01635483, q, 0.1747);
    //     ccbf.setMarketVariable(mktVar2);
    //     output << q << "," << ccbf.fdmprice(30000, 250, Exp, 250) << ","
    //         << ccbf.fdmprice(3000, 500, CN, 500) << std::endl;
    // }
    // ccbf.setMarketVariable(mktVar);
    // output.close();
    //
    // output.open("sigma_s.csv", std::ios::app);
    // output << "Sigma_s,EFDM,Crank-Nicolson" << std::endl;
    // for (int i = 0; i <= 53; ++i) {
    //     double sigmas = 0.1178 + i / 100.0;
    //     MarketVariable mktVar2(100, 0.01635483, 0.035692, sigmas);
    //     ccbf.setMarketVariable(mktVar2);
    //     output << sigmas << "," << ccbf.fdmprice(30000, 250, Exp, 250) << ","
    //         << ccbf.fdmprice(3000, 500, CN, 500) << std::endl;
    // }
    // ccbf.setMarketVariable(mktVar);
    // output.close();
    //
    // output.open("sigma_f.csv", std::ios::app);
    // output << "Sigma_f,EFDM,Crank-Nicolson" << std::endl;
    // for (int i = 0; i <= 18; ++i) {
    //     double sigmaf = 0.072 + i / 200.0;
    //     Forex forex2 = {0.00001306, sigmaf};
    //     ccbf.setForex(forex2);
    //     output << sigmaf << "," << ccbf.fdmprice(30000, 250, Exp, 250) << ","
    //         << ccbf.fdmprice(3000, 500, CN, 500) << std::endl;
    // }
    // ccbf.setForex(forex);
    // output.close();


    return 0;
}
