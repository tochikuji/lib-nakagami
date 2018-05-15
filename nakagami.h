#ifndef _NAKAGAMI_CV_H_
#define _NAKAGAMI_CV_H_

#include <cstdint>
#include <cmath>
#include <opencv2/opencv.hpp>
#include <iostream>


namespace nakagami {

  void calc(cv::InputArray img_, unsigned int neighbor, cv::OutputArray dst)
  {
    cv::Mat img;
    img_.getMat().convertTo(img, CV_32F); 
    img /= 255.;

    cv::Mat img_p2;
    cv::pow(img, 2, img_p2);

    const auto h = img.rows;
    const auto w = img.cols;
    const int window_size = 2 * neighbor + 1;

    cv::Mat dstmat = cv::Mat(h - 2 * neighbor, w - 2 * neighbor, CV_32FC1);

    dst.create(cv::Size(w - 2 * neighbor, h - 2 * neighbor), CV_32FC1);

    // validate input 
    if(img.channels() != 1){
      CV_Error(cv::Error::BadNumChannels, "image must have only 1 channel "
                                          "(grayscaled)");
    }
    
    int iy = neighbor;

    while(iy < h - window_size) {
      int ix = neighbor;

      while(ix < w - window_size) {
        const cv::Rect roi_rect(ix, iy, window_size, window_size);
        cv::Mat roi_p2 = img_p2(roi_rect);
        std::cout << roi_p2 << std::endl;

        cv::Scalar mean, dev;
        cv::meanStdDev(roi_p2, mean, dev);

        const double mw = (mean.val[0] * mean.val[0]) / std::pow(dev.val[0], 4);
        std::cout << mw << ' ' << mean.val[0] << ' ' << std::pow(dev.val[0], 4) << std::endl;

        double* p = dstmat.ptr<double>(iy);
        p[ix] = mw;

        ++ix;
      }

      ++iy;
    }

    dstmat.copyTo(dst);
  }

}

#endif // #ifnded _NAKAGAMI_CV_H_
