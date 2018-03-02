#include <iostream>
#include <vector>
#include "straddle.h"
#include "marketvariable.h"

int main(void) {
    std::vector<double> vol = {0.20, 0.30, 0.40, 0.50};
    MarketVariable mktVar(100, 0.0, 0.0, 0.20);
    Straddle strad(100, 1.0);

    for (int i = 0; i < vol.size(); ++i) {
        mktVar.setVol(vol[i]);
        strad.setMarketVariable(mktVar);
        std::vector<double> result = strad.hedgeSimulation(10000, 500, 0.07);
        std::cout << "=======" << "Vol: " << vol[i] << "======" << std::endl;
        std::cout << "Analytic Payoff: " << strad.expectedPayoff(0.07) << std::endl;
        std::cout << "Expected Payoff: " << result[0] << std::endl;
        std::cout << "Standard Deviation: " << result[1] << std::endl;
    }
    return 0;
}
