#include "alglib/interpolation.h"
#include <cmath>
#include <functional>
#include <queue>
#include "splines.hpp"

CubicSpline::CubicSpline(Pose start, Pose end, std::vector<Pose> midPoints)
{
    double d = sqrt((start.x() - end.x())*(start.x() - end.x()) + (start.y() - end.y())*(start.y() - end.y()));
    d = d;
    double x1 = start.x();
    double x2 = end.x();
    double y1 = start.y();
    double y2 = end.y();
    double th1 = (start.theta());
    double th2 = (end.theta());
    {
        using namespace alglib;
        double n = midPoints.size()+2; // number of points to interpolate on
        vector<double> x(n,0), y(n,0), u(n,0);
        x[0] = x1;
        x[n-1] = x2;
        y[0] = y1;
        y[n-1] = y2;
        for (int i = 0; i < n; i++) {
            u[i] = i/(double)(n-1);
        }
        for (int i = 1; i < n-1; i++ ) {
            x[i] = midPoints[i-1].x();
            y[i] = midPoints[i-1].y();
        }
        spline1dfitreport repX, repY ;
        //double vX, vY;
        alglib::real_1d_array AU, AY, AX;
        ae_int_t infoX, infoY;
        AU.setcontent(u.size(), &(u[0]));
        AY.setcontent(y.size(), &(y[0]));
        AX.setcontent(x.size(), &(x[0]));
        double rho = 3.0;     //3.0  and M = 30 
        spline1dfitpenalized(AU, AX, 3*n, rho, infoX, splineX, repX);
        spline1dfitpenalized(AU, AY, 3*n, rho, infoY, splineY, repY);
        //spline1dbuildcubic(AU, AX, splineX);
        //spline1dbuildcubic(AU, AY, splineY);
    }
}

double CubicSpline::x(double u) const
{
    double s, ds, d2s;
    alglib::spline1ddiff(splineX, u, s, ds, d2s);
    return s;
}

double CubicSpline::y(double u) const
{
    double s, ds, d2s;
    alglib::spline1ddiff(splineY, u, s, ds, d2s);
    return s;
}