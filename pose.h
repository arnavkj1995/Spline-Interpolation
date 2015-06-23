#ifndef POSE_H
#define POSE_H
#include <queue>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>

class Pose
{
    double x_, y_, theta_;
public:

    double x() const; // returns in strategy coordinate system
    double y() const; // returns in strategy coordinate system
    double theta() const; // already in strategy coordinates 
    Pose(double x, double y, double theta);    // takes in Strategy coordinates!
    Pose();
    void setx(double newx) { x_ = newx; }
    void sety(double newy) { y_ = newy; }
    void setTheta(double newtheta) {theta_ = newtheta;}   // will add setX and setY if/when needed    
};

inline double dist(Pose p1, Pose p2) {
    return sqrt((double)(p1.x()-p2.x())*(p1.x()-p2.x()) + (p1.y()-p2.y())*(p1.y()-p2.y()));
}

inline double distSq(Pose p1, Pose p2) {
    return (double)(p1.x()-p2.x())*(p1.x()-p2.x()) + (p1.y()-p2.y())*(p1.y()-p2.y());
}

#endif // POSE_H
