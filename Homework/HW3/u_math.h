#ifndef _U_MATH_H_
#define _U_MATH_H_

#define MAX(x, y)   (((x) > (y)) ? (x) : (y))

/* Just for binomial tree: need to be generalized */
double extrapolate(double x1, double y1, double x2, double y2);

/* Find the closest below and above value */
std::vector<double> findValue(std::vector<double>, double)
#endif
