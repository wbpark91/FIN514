#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include "autocall_yieldnote_least_perform.h"
#include "marketvariable.h"
#include "forex.h"

int main(void) {
    std::ofstream price;
    std::ofstream autocall;

    int numPath = 100000;

    std::vector<double> schedule{0.5, 0.75, 1, 1.25};
    ACYNLeastPerform asset(1000, 1.25, 0.08, QUARTER, 63.7, schedule, 3);
    Forex forex = {-0.00248, 0.0515};

    MarketVariable mktVar1(100, 0.0247, 0.01279, 0.1901);
    MarketVariable mktVar2(100, 0.0247, 0.00485, 0.2802);
    MarketVariable mktVar3(100, forex, 0.05219, 0.1736, -0.2084);

    asset.addMarketVariable(mktVar1);
    asset.addMarketVariable(mktVar2);
    asset.addMarketVariable(mktVar3);

    asset.setCov(0.0137, 0, 1);
    asset.setCov(0.0084, 0, 2);
    asset.setCov(0.0070, 1, 2);

    asset.setMCDiscount(0.0247);

    std::pair< std::vector<double>, std::vector<int> > result = asset.mcPrice(numPath);
    std::cout << "MCPrice: " << result.first[0] << std::endl;
    std::cout << "St.Dev: " << result.first[1] << std::endl;

    std::cout << "======Autocall Probabilities======" << std::endl;
    for (int i = 0; i < result.second.size(); ++i) {
        std::cout << "Autocall at " << schedule[i] << ": ";
        std::cout << ((double)(result.second[i]) / numPath) << std::endl;
    }

    // price.open("price_russell_sx5e.csv", std::ios::app);
    // autocall.open("autocall_russell_sx5e.csv", std::ios::app);
    //
    // /* COV: RUSSELL EURO */
    // price << "COV(RUSSELL & SX5E),PRICE" << std::endl;
    // autocall << "COV(RUSSELL & SX5E),AC1,AC2,AC3,AC4" << std::endl;
    //
    // for (int i = 0; i <= 31; ++i) {
    //     double cov = -0.01558 + (i / 1000.0);
    //     asset.setCov(cov, 0, 2);
    //     std::pair< std::vector<double>, std::vector<int> > result = asset.mcPrice(numPath);
    //     price << cov << "," << result.first[0] << std::endl;
    //     autocall << cov << ",";
    //     for (int j = 0; j < result.second.size(); ++j) {
    //         autocall << ((double)(result.second[j]) / numPath) << ",";
    //     }
    //     autocall << std::endl;
    // }
    //
    // asset.setCov(0.0084, 0, 2);
    // price.close();
    // autocall.close();
    //
    // /* COV: RUSSELL ETF */
    // price.open("price_russell_etf.csv", std::ios::app);
    // autocall.open("autocall_russell_etf.csv", std::ios::app);
    //
    // price << "COV(RUSSELL & ETF),PRICE" << std::endl;
    // autocall << "COV(RUSSELL & ETF),AC1,AC2,AC3,AC4" << std::endl;
    //
    // for (int i = 0; i <= 38; ++i) {
    //     double cov = -0.019673 + (i / 1000.0);
    //     asset.setCov(cov, 0, 1);
    //     std::pair< std::vector<double>, std::vector<int> > result = asset.mcPrice(numPath);
    //     price << cov << "," << result.first[0] << std::endl;
    //     autocall << cov << ",";
    //     for (int j = 0; j < result.second.size(); ++j) {
    //         autocall << ((double)(result.second[j]) / numPath) << ",";
    //     }
    //     autocall << std::endl;
    // }
    //
    // asset.setCov(0.0137, 0, 1);
    // price.close();
    // autocall.close();
    //
    // /* COV: ETF EUROSTOXX */
    // price.open("price_etf_sx5e.csv", std::ios::app);
    // autocall.open("autocall_etf_sx5e.csv", std::ios::app);
    //
    // price << "COV(ETF & SX5E),PRICE" << std::endl;
    // autocall << "COV(ETF & SX5E),AC1,AC2,AC3,AC4" << std::endl;
    //
    // for (int i = 0; i <= 25; ++i) {
    //     double cov = -0.012722 + (i / 1000.0);
    //     asset.setCov(cov, 1, 2);
    //     std::pair< std::vector<double>, std::vector<int> > result = asset.mcPrice(numPath);
    //     price << cov << "," << result.first[0] << std::endl;
    //     autocall << cov << ",";
    //     for (int j = 0; j < result.second.size(); ++j) {
    //         autocall << ((double)(result.second[j]) / numPath) << ",";
    //     }
    //     autocall << std::endl;
    // }
    //
    // asset.setCov(0.0070, 1, 2);
    // price.close();
    // autocall.close();

    // /* CORRELATOIN BETWEEN FOREX AND EUROSTOXX */
    // price << "CORR(SX5E & FOREX),PRICE" << std::endl;
    // autocall << "CORR(SX5E & FOREX),AC1,AC2,AC3,AC4" << std::endl;
    // for (int i = 0; i <= 40; ++i) {
    //     double rho = -1 + i / 20.0;
    //     MarketVariable mktVar31(100, forex, 0.05219, 0.1736, rho);
    //     asset.setMarketVariable(mktVar31, 2);
    //     std::pair< std::vector<double>, std::vector<int> > result = asset.mcPrice(numPath);
    //     price << rho << "," << result.first[0] << std::endl;
    //     autocall << rho << ",";
    //     for (int j = 0; j < result.second.size(); ++j) {
    //         autocall << ((double)(result.second[j]) / numPath) << ",";
    //     }
    //     autocall << std::endl;
    // }
    // asset.setMarketVariable(mktVar3, 2);
    //
    // price.close();
    // autocall.close();

    // /* RUSSELL */
    // price << "DIV(RUSSELL),PRICE" << std::endl;
    // autocall << "DIV(RUSSELL),AC1,AC2,AC3,AC4" << std::endl;
    // for (int i = 0; i < 15; ++i) {
    //     double add = i / 1000.0;
    //     MarketVariable mktVar11(100, 0.0247, 0.006395 + add, 0.1901);
    //     asset.setMarketVariable(mktVar11, 0);
    //     std::pair< std::vector<double>, std::vector<int> > result = asset.mcPrice(numPath);
    //     price << (0.006395 + add) << "," << result.first[0] << std::endl;
    //     autocall << (0.006395 + add) << ",";
    //     for (int j = 0; j < result.second.size(); ++j) {
    //         autocall << ((double)(result.second[j]) / numPath) << ",";
    //     }
    //     autocall << std::endl;
    // }
    // asset.setMarketVariable(mktVar1, 0);
    //
    // price.close();
    // autocall.close();
    //
    // /* ETF */
    // price.open("price_etfdiv.csv", std::ios::app);
    // autocall.open("autocall_etfdiv.csv", std::ios::app);
    //
    // price << "DIV(ETF),PRICE" << std::endl;
    // autocall << "DIV(ETF),AC1,AC2,AC3,AC4" << std::endl;
    // for (int i = 0; i < 12; ++i) {
    //     double add = i / 2000.0;
    //     MarketVariable mktVar21(100, 0.0247, 0.002425 + add, 0.2802);
    //     asset.setMarketVariable(mktVar21, 1);
    //     std::pair< std::vector<double>, std::vector<int> > result = asset.mcPrice(numPath);
    //     price << (0.002425 + add) << "," << result.first[0] << std::endl;
    //     autocall << (0.002425 + add) << ",";
    //     for (int j = 0; j < result.second.size(); ++j) {
    //         autocall << ((double)(result.second[j]) / numPath) << ",";
    //     }
    //     autocall << std::endl;
    // }
    // asset.setMarketVariable(mktVar2, 1);
    //
    // price.close();
    // autocall.close();
    //
    //
    // /* EuroStoxx */
    // price.open("price_eurostoxxdiv.csv", std::ios::app);
    // autocall.open("autocall_eurostoxxdiv.csv", std::ios::app);
    //
    // price << "DIV(SX5E),PRICE" << std::endl;
    // autocall << "DIV(SX5E),AC1,AC2,AC3,AC4" << std::endl;
    //
    // for (int i = 0; i < 60; ++i) {
    //     double add = i / 1000.0;
    //     MarketVariable mktVar31(100, forex, 0.026095 + add, 0.1736, -0.2084);
    //     asset.setMarketVariable(mktVar31, 2);
    //     std::pair< std::vector<double>, std::vector<int> > result = asset.mcPrice(numPath);
    //     price << (0.026095 + add) << "," << result.first[0] << std::endl;
    //     autocall << (0.026095 + add) << ",";
    //     for (int j = 0; j < result.second.size(); ++j) {
    //         autocall << ((double)(result.second[j]) / numPath) << ",";
    //     }
    //     autocall << std::endl;
    // }
    // asset.setMarketVariable(mktVar3, 2);
    //
    // price.close();
    // autocall.close();


    // /* RUSSELL */
    // price << "VOL(RUSSELL),PRICE" << std::endl;
    // autocall << "VOL(RUSSELL),AC1,AC2,AC3,AC4" << std::endl;
    // for (int i = 0; i < 40; ++i) {
    //     double add = i / 100.0;
    //     MarketVariable mktVar11(100, 0.0247, 0.01279, 0.1395 + add);
    //     asset.setMarketVariable(mktVar11, 0);
    //     std::pair< std::vector<double>, std::vector<int> > result = asset.mcPrice(numPath);
    //     price << (0.1395 + add) << "," << result.first[0] << std::endl;
    //     autocall << (0.1395 + add) << ",";
    //     for (int j = 0; j < result.second.size(); ++j) {
    //         autocall << ((double)(result.second[j]) / numPath) << ",";
    //     }
    //     autocall << std::endl;
    // }
    // asset.setMarketVariable(mktVar1, 0);
    //
    // price.close();
    // autocall.close();
    //
    // /* ETF */
    // price.open("price_etf.csv", std::ios::app);
    // autocall.open("autocall_etf.csv", std::ios::app);
    //
    // price << "VOL(ETF),PRICE" << std::endl;
    // autocall << "VOL(ETF),AC1,AC2,AC3,AC4" << std::endl;
    // for (int i = 0; i < 40; ++i) {
    //     double add = i / 100.0;
    //     MarketVariable mktVar21(100, 0.0247, 0.00485, 0.2329 + add);
    //     asset.setMarketVariable(mktVar21, 1);
    //     std::pair< std::vector<double>, std::vector<int> > result = asset.mcPrice(numPath);
    //     price << (0.2329 + add) << "," << result.first[0] << std::endl;
    //     autocall << (0.2329 + add) << ",";
    //     for (int j = 0; j < result.second.size(); ++j) {
    //         autocall << ((double)(result.second[j]) / numPath) << ",";
    //     }
    //     autocall << std::endl;
    // }
    // asset.setMarketVariable(mktVar2, 1);
    //
    // price.close();
    // autocall.close();
    //
    // /* EuroStoxx */
    // price.open("price_eurostoxx.csv", std::ios::app);
    // autocall.open("autocall_eurostoxx.csv", std::ios::app);
    //
    // price << "VOL(SX5E),PRICE" << std::endl;
    // autocall << "VOL(SX5E),AC1,AC2,AC3,AC4" << std::endl;
    //
    // for (int i = 0; i < 35; ++i) {
    //     double add = i / 100.0;
    //     MarketVariable mktVar31(100, forex, 0.05219, (0.1236 + add), -0.2084);
    //     asset.setMarketVariable(mktVar31, 2);
    //     std::pair< std::vector<double>, std::vector<int> > result = asset.mcPrice(numPath);
    //     price << (0.1236 + add) << "," << result.first[0] << std::endl;
    //     autocall << (0.1236 + add) << ",";
    //     for (int j = 0; j < result.second.size(); ++j) {
    //         autocall << ((double)(result.second[j]) / numPath) << ",";
    //     }
    //     autocall << std::endl;
    // }
    // asset.setMarketVariable(mktVar3, 2);
    //
    // price.close();
    // autocall.close();
    return 0;
}
