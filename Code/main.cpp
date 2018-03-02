#include <iostream>
#include <numeric>
#include <vector>
#include <cmath>

double mean(std::vector<double> vec) {
    double result = std::accumulate(vec.begin(), vec.end(), 0.0 / vec.size());
    return result / vec.size();
}

double stdev(std::vector<double> vec) {
    double average = mean(vec);
    double result = 0;
    for (int i = 0; i < vec.size(); ++i) {
        result += (vec[i] - average) * (vec[i] - average);
    }
    return sqrt(result / vec.size());
}

int main(void) {
    std::vector<double> vec = { 1.0, 2, 3, 4, 5 };
    std::cout << "mean: " << mean(vec) << std::endl;
    std::cout << "St.dev: " << stdev(vec) << std::endl;
    return 0;
}
