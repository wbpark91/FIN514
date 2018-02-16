#ifndef _U_MATH_H_
#define _U_MATH_H_
#include <vector>

#define MAX(x, y)   (((x) > (y)) ? (x) : (y))

/* Just for binomial tree: need to be generalized */
/* order: order of error, default: 1 */
double extrapolate(double x1, double y1, double x2, double y2, int order = 1);

/* Find the closest below and above value */
std::vector<double> findBAValue(std::vector<double> vec, double value);
#endif
