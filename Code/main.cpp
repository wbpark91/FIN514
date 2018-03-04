#include "callable_buffered_ran.h"
#include "marketvariable.h"
#include <iostream>
#include <vector>

int main(void) {

    MarketVariable mktVar(100, 0.027078, 0.01322, 0.2018);
    std::vector<double> cpnSchedule = {20, 40, 62, 84, 103, 126, 147, 167, 188
                                    , 209, 228, 250, 270, 290, 312, 333, 353
                                    , 376, 396, 417, 439, 458, 478, 499, 519
                                    , 541, 563, 583, 604, 626, 647, 668, 688
                                    , 709, 729, 749, 769, 791, 812, 833, 854
                                    , 875, 897, 918, 938, 959, 979, 1000, 1020
                                    , 1042, 1062, 1084, 1105, 1126, 1148, 1168
                                    , 1189, 1210, 1228, 1250};

    CallableBufferedRAN CBRAN(1000, 0.05, 5, cpnSchedule, 80, 0.2);
    CBRAN.setMarketVariable(mktVar);
    double price = CBRAN.bntprice(1250, CRR);
    std::cout << "Price: " << price << std::endl;
    return 0;
}
