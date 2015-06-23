#ifndef SPLINES_H
#define SPLINES_H
#include "alglib/interpolation.h"
#include <vector>
#include "pose.h"

using namespace std;

class CubicSpline: public Spline{
protected:
  alglib::spline1dinterpolant splineX, splineY;
public:
  // midPoints is an array of points through which the path should be interpolated.
  // NOTE: only x, y coordinates of midPoints are used, theta is ignored.
  CubicSpline(Pose start, Pose end, std::vector<Pose> midPoints = std::vector<Pose>());
  virtual double x(double u) const;
  virtual double y(double u) const;
};

#endif // SPLINES_H
