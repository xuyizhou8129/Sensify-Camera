#include <opencv2/opencv.hpp>
using namespace cv;

int main() {
    VideoCapture cap(0); // Open the default camera
    if (!cap.isOpened()) {
        return -1;
    }

    Mat frame;
    while (true) {
        cap >> frame; // Capture a new frame
        if (frame.empty()) {
            break;
        }
        imshow("Camera", frame); // Display the frame
        if (waitKey(30) >= 0) {
            break;
        }
    }
    return 0;
}