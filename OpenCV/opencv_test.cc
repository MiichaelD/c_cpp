#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>
#include <sstream>
#include <thread>

using namespace cv;
using namespace std;

// Installation: 
//  - Mac:     https://www.computervision.zone/courses/opencv-cpp-course/lesson/mac/
//  - Windows: https://www.computervision.zone/courses/opencv-cpp-course/lesson/windows/

///////////////// Webcam + Face Detection using another thread //////////////////////
CascadeClassifier faceCascade;
int w, h, fps;

vector<Rect> detectFacesBBoxes(const Mat& img) {
  vector<Rect> faces;
  faceCascade.detectMultiScale(img, faces, 1.1, 10);
  return faces;
}

vector<Rect> drawFacesBBoxes(Mat& img, const vector<Rect>& faces) {
  for (int i = 0; i < faces.size(); i++) {
    rectangle(img, faces[i].tl(), faces[i].br(), Scalar(255, 0, 255), 3);
  }
  return faces;
}

void printFps(Mat &img) {
  stringstream sb;
  sb << "fps: " << fps;
  Scalar color(100, 255, 0);
  Point position(10, h - 30);
  putText(img, sb.str(), position, FONT_HERSHEY_SIMPLEX, 0.5, color, 1, LINE_AA);
}


void updateFaceDetection(Mat *img, vector<Rect> *faces) {
  while (true) {
    *faces = detectFacesBBoxes(*img);
    cout << "Detecting faces" << endl;
  }
}

int main() {
  faceCascade.load("Resources/haarcascade_frontalface_default.xml");
  if (faceCascade.empty()) {
    cerr << "XML file not loaded" << endl;
    return 1;
  }
  VideoCapture cap(0);
  w = cap.get(CAP_PROP_FRAME_WIDTH);
  h = cap.get(CAP_PROP_FRAME_HEIGHT);
  fps = cap.get(CAP_PROP_FPS);

  Mat img;
  vector<Rect> faces;
  thread faceUpdater(updateFaceDetection, &img, &faces);
  for (size_t frame = 0; ; ++frame) {
    auto timer = getTickCount();
    if (!cap.read(img)){
      cerr << "Error while reading capture frame" << endl;
      return 1;
    }
    drawFacesBBoxes(img, faces);
    printFps(img);
    imshow("Image", img);
    fps = getTickFrequency() / (getTickCount() - timer);
    waitKey(1);
  }
  faceUpdater.join();
  return 0;
}

