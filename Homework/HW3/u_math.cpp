#include "u_math.h"

double extrapolate(double x1, double y1, double x2, double y2) {
    return (y2 * x2 - y1 * x1) / (x2 - x1);
}
