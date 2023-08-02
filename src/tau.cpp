#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
using namespace cv::ml;

int main(void)
{
  VideoCapture cap(0);
  Mat current_frame;
  vector<Point> track;

  HOGDescriptor hog;
  hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());

  while (true)
  {
    cap >> current_frame;

    if (current_frame.empty())
    {
      cerr << "Video stream ended or bad frame." << endl;
      return 1;
    }

    Mat img = current_frame.clone();
    resize(img, img, Size(img.cols * 2, img.rows * 2));

    vector<Rect> found;
    vector<double> weights;

    hog.detectMultiScale(img, found, weights);

    // Draw detections
    for (size_t i = 0; i < found.size(); i++)
    {
      Rect r = found[i];
      rectangle(img, found[i], cv::Scalar(0, 0, 255), 3);

      track.push_back(Point(
        found[i].x + found[i].width / 2,
        found[i].y + found[i].height / 2
      ));
    }

    // Plot the track
    for (size_t i = 1; i < track.size(); i++)
    {
      line(img, track[i - 1], track[i], Scalar(255, 255, 0), 2);
    }

    // Present
    imshow("Targets", img);
    waitKey(1);
  }

  return 0;
}
