#include "pose.h"
#include <math.h>
#include <algorithm>
/* Constructor takes in x, y in Strategy coordinates! */
Pose::Pose(double x, double y, double theta):
    x_(x),
    y_(y),
    theta_(theta)
{    

}

Pose::Pose()
{
    x_ = 0; y_ = 0; theta_ = 0;
}

double Pose::x() const
{
    return x_;
}

double Pose::y() const
{
    return y_;
}

double Pose::theta() const
{
    return theta_;
}
