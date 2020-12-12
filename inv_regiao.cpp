/*
O programa solicita ao usuário as coordenadas de dois pontos P1 e P2 localizados dentro dos
limites do tamanho da imagem e exibi que lhe for fornecida. Entretanto, a região definida pelo
retângulo de vértices opostos definidos pelos pontos P1 e P2 será exibida com o negativo da imagem
na região correspondente
*/

#include <iostream>
#include <opencv2/opencv.hpp>


struct point {
    unsigned x;
    unsigned y;
};

int main() {
    cv::Mat image;
    point P1, P2;

    std::cout << "Coordenadas de P1: ";
    std::cin >> P1.x >> P1.y;
    std::cout << std::endl;
    std::cout << "Coordenadas de P2: ";
    std::cin >> P2.x >> P2.y;


    image = cv::imread("Einstein.jpg", cv::IMREAD_GRAYSCALE);
    if (!image.data)
        std::cout << "nao abriu o .png" << std::endl;

    if (P1.x > image.rows || P1.y > image.cols )  {
        std::cout << "Ponto 1 nao corresponde a imagem" << std::endl;
        return 0;
    }
    if (P2.x > image.rows || P2.y > image.cols) {
        std::cout << "Ponto 2 nao corresponde a imagem" << std::endl;
        return 0;
    }

    cv::imshow("imagem original", image);

    for (int i = P1.x; i < P2.x; i++) {
        for (int j = P1.y; j < P2.y; j++) {
            image.at<uchar>(i, j) = 256 - image.at<uchar>(i, j);
        }
    }

    cv::imshow("imagem com negativo", image);
    cv::waitKey();
    return 0;
}