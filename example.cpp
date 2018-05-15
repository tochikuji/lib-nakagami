#include <opencv2/opencv.hpp>
#include <bits/stdc++.h>
#include "nakagami_cv.hpp"
#include <iostream>

int main(int, char** argv){
  std::string filename = argv[1];
  cv::Mat img = cv::imread(filename, 0);
  cv::Mat nakagami;
  nakagami::calc(img, 10, nakagami);
  cv::imshow("src", img);
  cv::imshow("nakagami", nakagami);
  cv::waitKey(-1);
}
