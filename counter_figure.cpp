#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv) {
    cv::Mat image;
    cv::Point p;
    int width, height;
    int nobjects;

    image = cv::imread("bolhas2.png", cv::IMREAD_GRAYSCALE);

    if (!image.data) {
        std::cout << "imagem nao carregou corretamente\n";
        return(-1);
    }

    width = image.cols;
    height = image.rows;
    std::cout << width << "x" << height << std::endl;

    cv::imshow("figuras", image);
    cv::waitKey();

    p.x = 0;
    p.y = 0;

    // retira as figura da borda superior
    for (int i = 0; i < 1; i++) {
        for (int j = 0; j < width; j++) {
            if (image.at<uchar>(i, j) == 255) {
                p.x = j;
                p.y = i;
                cv::floodFill(image, p, 0);
            }
        }
    }

    // retira as figura da borda inferior
    for (int i = height - 1; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (image.at<uchar>(i, j) == 255) {
                p.x = j;
                p.y = i;
                cv::floodFill(image, p, 0);
            }
        }
    }

    // retira as figura da borda esquerda
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < 1; j++) {
            if (image.at<uchar>(i, j) == 255) {
                p.x = j;
                p.y = i;
                cv::floodFill(image, p, 0);
            }
        }
    }

    // retira as figura da borda direita
    for (int i = 0; i < height; i++) {
        for (int j = width - 1; j < width; j++) {
            if (image.at<uchar>(i, j) == 255) {
                p.x = j;
                p.y = i;
                cv::floodFill(image, p, 0);
            }
        }
    }

    // cena sem figura nas margens
    cv::imshow("sem figuras margens", image);
    cv::waitKey();

    // busca todos objetos presentes
    nobjects = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (image.at<uchar>(i, j) == 255) {
                // achou um objeto
                nobjects++;
                p.x = j;
                p.y = i;
                // preenche o objeto com o contador
                cv::floodFill(image, p, nobjects);
            }
        }
    }

    // cena com figura rotuladas
    cv::imshow("figuras rotuladas", image);
    cv::waitKey();

    // preenche o fundo com branco
    p.x = 0;
    p.y = 0;
    cv::floodFill(image, p, 255);
    cv::imshow("fundo branco", image);
    cv::waitKey();

    int totalObjects = nobjects;

    // contando figura com buracos
    nobjects = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (image.at<uchar>(i, j) == 0) {
                // achou um objeto
                nobjects++;
                p.x = j;
                p.y = i;
                cv::floodFill(image, p, 255);

                p.x = j;
                p.y = i - 1;
                cv::floodFill(image, p, 255);
            }
        }
    }
    std::cout << "a cena tem " << totalObjects << " figura que nao tocam margens\n";
    std::cout << "a cena tem " << nobjects << " figura com buracos\n";
    std::cout << "a cena tem " << totalObjects - nobjects << " figura sem buracos\n";
    cv::imshow("figuras sem furos", image);
    cv::imwrite("labeling.png", image);
    cv::waitKey();
    return 0;
}