/*
O programa basicamente troca os quadrantes diagonalmente opostos na imagem
*/

#include <iostream>
#include <opencv2/opencv.hpp>


int main() {
    cv::Mat image1,image2;
    
    image1 = cv::imread("lena.jpg", cv::IMREAD_GRAYSCALE);
    if (!image1.data)
        std::cout << "nao abriu o .png" << std::endl;

    image2 = image1.clone();
    int rows = image1.rows;
    int cols = image1.cols;

    cv::imshow("imagem original", image1);

    // 1 quadrante
    for (int i = 0; i < rows / 2; i++) {
        for (int j = 0; j < cols / 2; j++) {
            image2.at<uchar>(i, j+cols/2) = image1.at<uchar>(i + rows / 2, j);
        }
    }
    // 2 quadrante
    for (int i = 0; i < rows / 2; i++) {
        for (int j = 0; j < cols / 2; j++) {
            image2.at<uchar>(i, j) = image1.at<uchar>(i + rows / 2, j + cols / 2);
        }
    }
    // 3 quadrante
    for (int i = 0; i < rows / 2; i++) {
        for (int j = 0; j < cols / 2; j++) {
            image2.at<uchar>(i+rows/2, j) = image1.at<uchar>(i, j + cols / 2);
        }
    }
    // 4 quadrante
    for (int i = 0; i < rows / 2; i++) {
        for (int j = 0; j < cols / 2; j++) {
            image2.at<uchar>(i+rows/2, j+cols/2) = image1.at<uchar>(i, j);
        }
    }

    cv::imshow("imagem com quadrantes trocados", image2);
    cv::waitKey();
    return 0;
}