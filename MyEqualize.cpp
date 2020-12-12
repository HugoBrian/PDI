#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char** argv) {
    cv::Mat image;
    int width, height;
    cv::VideoCapture cap;
    cv::Mat histGray;
    int nbins = 256;
    float range[] = { 0, 255 };
    const float* histrange = { range };
    bool uniform = true;
    bool acummulate = true;
    int key;
    
    cap.open(0);

    if (!cap.isOpened()) {
        std::cout << "cameras indisponiveis";
        return -1;
    }

    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
    width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
    height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);

    std::cout << "largura = " << width << std::endl;
    std::cout << "altura  = " << height << std::endl;

    while (1) {
        cap >> image;
        cv::cvtColor(image, image, CV_BGR2GRAY);

        cv::calcHist(&image, 1, 0, cv::Mat(), histGray, 1,
            &nbins, &histrange,
            uniform, acummulate);

        float accumulator = 0;
        for (int i = 0; i < 256; i++) {
            histGray.at<float>(i) = accumulator + histGray.at<float>(i);
        }

        cv::normalize(histGray, histGray, 0, 256, cv::NORM_MINMAX, -1, cv::Mat());


        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {

                image.at<uchar>(i, j) = histGray.at<float>(image.at<uchar>(i, j));
            }
        }
       
        cv::imshow("imagem equalizada", image);
        key = cv::waitKey(30);
        if (key == 27) break;
    }
    return 0;
}