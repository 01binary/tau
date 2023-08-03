#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
using namespace cv::ml;

int main(void)
{
  VideoCapture cap(0);
  Mat current_frame;

  HOGDescriptor hog;
  hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());

  int frames = 0;
  double time = 0;
  int fps = 0;
  char fpsText[8] = {0};

  //namedWindow("tau", WINDOW_NORMAL);
  //setWindowProperty("tau", WND_PROP_FULLSCREEN, WINDOW_FULLSCREEN);

  while (true)
  {
    clock_t beginFrame = clock();

    cap >> current_frame;

    if (current_frame.empty())
    {
      cerr << "Video stream ended or bad frame." << endl;
      return 1;
    }

    Mat img = current_frame.clone();
    resize(img, img, Size(img.cols / 4, img.rows / 4));

    vector<Rect> found;
    vector<double> weights;

    hog.detectMultiScale(img, found, weights);

    // Draw detections
    for (size_t i = 0; i < found.size(); i++)
    {
      Rect r = found[i];
      rectangle(img, found[i], cv::Scalar(0, 0, 255), 3);
    }

    // Draw FPS
    putText(
      img,
      fpsText,
      Point(340, 20),
      FONT_HERSHEY_DUPLEX,
      1,
      Scalar(200, 200, 200, 255)
    );

    // Present
    imshow("tau", img);
    
    // FPS counter
    clock_t endFrame = clock();
    clock_t delta = endFrame - beginFrame;
    double milliseconds = delta * 1000.0 / CLOCKS_PER_SEC;

    frames++;
    time = time + milliseconds;

    if (time >= 1000.0)
    {
      fps = frames * 1000.0 / time;
      frames = 0;
      time = 0.0;

      sprintf(fpsText, "%d FPS", fps);
    }

    waitKey(1);
  }

  return 0;
}
