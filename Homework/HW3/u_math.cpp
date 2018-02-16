#include "u_math.h"
#include <iostream>

double extrapolate(double x1, double y1, double x2, double y2) {
    return (y2 * x2 - y1 * x1) / (x2 - x1);
}

std::vector<double> findBAValue(std::vector<double> vec, double value) {
    /* Input vector vec should be reverse - sorted */

    std::vector<double> result;
    for (int i = 0; i < vec.size() - 1; ++i) {
        if (value < vec[i] && value >= vec[i+1]) {
            result.push_back(vec[i+1]);
            result.push_back(vec[i]);
            return result;
        }
    }
    std::cout << "Cannot find the closest below and above value." << std::endl;
    exit(1);
}
