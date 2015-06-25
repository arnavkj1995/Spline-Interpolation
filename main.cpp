#include "opencv2/highgui/highgui.hpp"
#include "opencv2/video/tracking.hpp"
#include <iostream>
#include <stdio.h>
#include <vector>
#include "splines.hpp"

using namespace cv;
using namespace std;

vector<Point> mousePos;

void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
    if ( event == EVENT_MOUSEMOVE )
    {
     // cout << "pushing" << endl;
      Point mouse;
      mouse.x = (float)(1.0*x);
      mouse.y = (float)(1.0*y);
      mousePos.push_back(mouse);
  //  cout << "here " << mousePos.x << " : " << mousePos.y << endl;
     //     cout << "Mouse move over the window - position (" << x << ", " << y << ")" << endl;
    }
}

int main(){
    Mat img(1000, 800, CV_8UC3);
    img = Scalar::all(0);
    vector<Point> mousev,kalmanv;
    mousev.clear();
    kalmanv.clear(); 
    mousePos.clear(); 
    float startThetaX = 0, endThetaX, startThetaY = 0, endThetaY;
    namedWindow("nimble", 1);
    setMouseCallback("nimble", CallBackFunc, NULL);
    int check = 0;
    int numPoints = 5;
    cout << img.cols << endl;
    while(1)
    {
      imshow("nimble", img);
      if(mousePos.size() > numPoints){
        //cout << "hjere1:" << endl; 
        Pose start(mousePos[0].x , mousePos[0].y , 0);
        Pose end(mousePos[numPoints].x, mousePos[numPoints].y, 0);
        vector<Pose> midpoints;
        for(int i = 1; i <numPoints; i++)
          midpoints.push_back(Pose(mousePos[i].x , mousePos[i].y , 0));
        CubicSpline *p = new CubicSpline(start, end, midpoints);
        //cout << "hjere:" << endl;  
        for(int i = 0; i < 1000 ;i++){
           if((p->x(i/1000.) >= 0) && (p->x(i/1000.) < img.rows) && (p->y(i/1000.) >=0) && (p->y(i/1000.) < img.cols))
              img.at<Vec3b>(Point(p->x(i/1000.), p->y(i/1000.))) = 255;
        }
          mousePos.erase(mousePos.begin(), mousePos.begin() + numPoints );
      }
      waitKey(16);
    //  break;
    }
    return 0;
  }

/*int main( )
{ 
 
KalmanFilter KF(4, 2, 0);
 
// intialization of KF...
KF.transitionMatrix = *(Mat_<float>(4, 4) << 1,0,1,0,   0,1,0,1,  0,0,1,0,  0,0,0,1);
Mat_<float> measurement(2,1); measurement.setTo(Scalar(0));
 
KF.statePre.at<float>(0) = mousePos.x;
KF.statePre.at<float>(1) = mousePos.y;
KF.statePre.at<float>(2) = 0;
KF.statePre.at<float>(3) = 0;
setIdentity(KF.measurementMatrix);
setIdentity(KF.processNoiseCov, Scalar::all(1e-4));
setIdentity(KF.measurementNoiseCov, Scalar::all(10));
setIdentity(KF.errorCovPost, Scalar::all(.1));
// Image to show mouse tracking
Mat img(600, 800, CV_8UC3);
vector<Point> mousev,kalmanv;
mousev.clear();
kalmanv.clear();  
 
namedWindow("mouse kalman", 1);
setMouseCallback("mouse kalman", CallBackFunc, NULL);
int check = 0;
while(1)
{
  
 // First predict, to update the internal statePre variable
 Mat prediction = KF.predict();
 Point predictPt(prediction.at<float>(0),prediction.at<float>(1));
              
 // Get mouse point

 measurement(0) = mousePos.x;
 measurement(1) = mousePos.y; 
  
  cout << "vsd" << measurement(0) << endl;
 // The update phase 
 Mat estimated = KF.correct(measurement);
 
 Point statePt(estimated.at<float>(0),estimated.at<float>(1));
 Point measPt(measurement(0),measurement(1));
    // plot points
    imshow("mouse kalman", img);
    img = Scalar::all(0);
 
    mousev.push_back(measPt);
    kalmanv.push_back(statePt);
    drawCross( statePt, Scalar(255,255,255), 5 );
    drawCross( measPt, Scalar(0,0,255), 5 );
 
    for (int i = 0; i < mousev.size()-1; i++) 
     line(img, mousev[i], mousev[i+1], Scalar(255,255,0), 1);
     
    for (int i = 0; i < kalmanv.size()-1; i++) 
     line(img, kalmanv[i], kalmanv[i+1], Scalar(0,155,255), 1);
     
   waitKey(1);  
}                                           
    return 0;
}*/