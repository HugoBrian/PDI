# Processamento Digital de Imagem

Hugo Brian de Carvalho Cortez - hugo_brian@hotmail.com

---

> Esta página tem o objetivo de documentar os exercícios e projetos desenvolvidos durante a disciplina DCA0445 - Processamento Digital de Imagem(PDI) ministrada pelo professor Agostinho Brito Jr. no período 2020.6 da Universidade Federal do Rio Grande do Norte(UFRN).

O tutorial do professor sobre o Processamento Digital de Imagem que contém as propostas de exercícios aqui desenvolvidos podem ser encontrados em:

[Introdução ao processamento digital de imagens com OpenCV](https://agostinhobritojr.github.io/tutorial/pdi/)

## Exercício 2.2 a)

O exercício pede, utilizando o exemplo *pixels.cpp* fornecido no tutorial, para implementar um programa chamado *regions.cpp* que deverá solicitar ao usuário as coordenadas de dois pontos P1 e P2 localizados dentro dos limites do tamanho da imagem e exibir que lhe for fornecida. A região definida pelo retângulo de vértices opostos definidos pelos pontos P1 e P2 será exibida com o negativo da imagem na região correspondente.

O programa *regions.cpp* completo é apresentado a seguir:

```cpp
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
```

A imagem utilizada *Einstein.jpg* possui tamanho de 500x500 pixels. O resultado do programa é demonstrado na Figura 1.

![Processamento%20Digital%20de%20Imagem%20beb13c7019a14e51ab036322c65d94a9/exercicio_2_2.png](Processamento%20Digital%20de%20Imagem%20beb13c7019a14e51ab036322c65d94a9/exercicio_2_2.png)

Figura 1. Resultado do programa regions.cpp

Os vértices do retângulo passados para o programa foram P1.x = 100, P1.y = 200 e P2.x = 400, P1.y = 400. Como se pode notar, a área desse retângulo teve sua imagem invertida.

### Descrição do programa *regions.cpp*

O cabeçalho inicial contém a inclusão da biblioteca padrão e a biblioteca *opencv*

```cpp
#include <iostream>
#include <opencv2/opencv.hpp>
```

Em seguida foi definida uma *struct* para representar um ponto que possui o dois *unsigned* representando as coordenadas x e y dele.

```cpp
struct point {
    unsigned x;
    unsigned y;
};
```

No início da função *main* é instanciado um objeto da classe **Mat** pertencente a *opencv* e duas variáveis do tipo **point.** Logo em seguida é requerido ao usuário as coordenadas dos vértices do retângulo

```cpp
int main() {
    cv::Mat image;
    point P1, P2;

    std::cout << "Coordenadas de P1: ";
    std::cin >> P1.x >> P1.y;
    std::cout << std::endl;
    std::cout << "Coordenadas de P2: ";
    std::cin >> P2.x >> P2.y;
```

Após o usuário inserir as coordenadas, o programa faz a leitura da imagem Einstein.jpg através da função *imread* do *opencv* e a converte para escala de cinza caso ela seja colorida. Há ainda uma verificação se a imagem foi lida corretamente e se os pontos passados estão dentro da imagem. Se lida corretamente, a imagem é mostrada em uma janela através da função *imshow* do *opencv.* 

```cpp
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
```

Para inverter uma imagem basicamente se deve atualizar o valor de cada *pixel* subtraindo o seu valor atual do valor máximo que ele poderia ter.

$$Pixel_{invertido} = Valor_{máximo} - Pixel_{atual}$$

Essa solução foi implementada para cada *pixel* do retângulo no trecho de código abaixo.

```cpp
for (int i = P1.x; i < P2.x; i++) {
        for (int j = P1.y; j < P2.y; j++) {
            image.at<uchar>(i, j) = 256 - image.at<uchar>(i, j);
        }
    }
```

Por fim, o programa é finalizado exibindo a imagem com a sub-região invertida e com a função *waitkey* do *opencv* que espera uma tecla ser pressionada para encerra o programa.

 

```cpp
		cv::imshow("imagem com negativo", image);
    cv::waitKey();
    return 0;
```

---

## Exercício 2.2 b)

O segundo exercício proposto é a implementação de um programa chamado *trocaregioes.cpp*. O programa basicamente deverá trocar os quadrantes diagonalmente opostos na imagem.

A seguir é exposto o programa completo:

```cpp
#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    cv::Mat image1,image2;
    
    image1 = cv::imread("lena.jpg", cv::IMREAD_GRAYSCALE);
    if (!image1.data)
        std::cout << "nao abriu o .jpg" << std::endl;

    image2 = image1.clone();

    cv::imshow("imagem original", image1);

    int rows = image1.rows;
    int cols = image1.cols;

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
```

Utilizando a imagem *lena.jpg,* o resultado do programa é demonstrado na Figura 2.

![Processamento%20Digital%20de%20Imagem%20beb13c7019a14e51ab036322c65d94a9/exercicio_2_2_b.png](Processamento%20Digital%20de%20Imagem%20beb13c7019a14e51ab036322c65d94a9/exercicio_2_2_b.png)

Figura 2. Resultado do programa trocaregioes.cpp

---

### Descrição do programa *trocaregioes.cpp*

Após a inclusão da biblioteca padrão e da biblioteca *opencv*, no início da função *main* são instanciados dois objetos da classe **Mat** para armazenar a imagem original e a imagem com as regiões trocadas.

A imagem *lena.jpg* é atribuída ao objeto *image1* que é convertida para escala através da função *imread*. Após uma verificação de leitura, a *image1* é clonada para *image2* através da função *clone()* da própria classe *Mat* para que os objetos possam ter as mesmas características como número de linhas e colunas. Em seguida a imagem lida é mostrada.

```cpp
    cv::Mat image1,image2;
    
    image1 = cv::imread("lena.jpg", cv::IMREAD_GRAYSCALE);
    if (!image1.data)
        std::cout << "nao abriu o .jpg" << std::endl;

    image2 = image1.clone();

    cv::imshow("imagem original", image1);
```

Para trocar os quadrantes foram realizados quatro laços para percorrer cada quadrante atribuindo no objeto *image2* os quadrantes diagonalmente opostos do objeto *image1*. Para evitar a busca do número de linhas e colunas dentro de *image1* a cada iteração, foram declaradas duas variáveis inteiras para armazenar tais valores.

```cpp
		int rows = image1.rows;
    int cols = image1.cols;

    // 1 quadrante
    for (int i = 0; i < rows / 2; i++) {
        for (int j = 0; j < cols / 2; j++) {
            image2.at<uchar>(i, j+cols/2) = image1.at<uchar>(i + rows / 2, j);
        }
    }
```

Por fim, através da função *imshow* é mostrada segunda imagem com os quadrantes trocados.

```cpp
cv::imshow("imagem com quadrantes trocados", image2);
    cv::waitKey();
    return 0;
```

---

## Exercício 3.2

O exercício propõe o desenvolvimento de um programa de identificação e contagem de regiões com e sem buracos internos que existem na cena. O programa não conta as figuras das bordas pois não se sabe se elas possuem furos ou não. 

A seguir, é apresentado o programa completo, nele são mostradas em tela várias imagens com o objetivo de demonstrar o processo mas que não são necessárias para a contagem das figuras.

```cpp
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
```

O resultado do programa é apresentado pelas 5 figuras através do *gif* abaixo.

![Processamento%20Digital%20de%20Imagem%20beb13c7019a14e51ab036322c65d94a9/gif.gif](Processamento%20Digital%20de%20Imagem%20beb13c7019a14e51ab036322c65d94a9/gif.gif)

Figura animada 1. Resultado do programa *contador_figuras.cpp*

A primeira imagem *figuras* é o arquivo original; a segunda imagem *sem figuras margens* mostra a cena após a retirada das figuras que tocam as margens; a terceira imagem *figuras rotuladas* mostra a cena após o processo de rotulação; a quarta imagem *fundo branco* mostra a cena com o fundo branco para melhor visualização das figuras; a quinta e última imagem *figuras sem furos* mostra a cena após a exclusão das figuras com furo.

O resultado da contagem é apresentado ao fim do programa como podemos ver na figura a seguir.

![Processamento%20Digital%20de%20Imagem%20beb13c7019a14e51ab036322c65d94a9/contagem.png](Processamento%20Digital%20de%20Imagem%20beb13c7019a14e51ab036322c65d94a9/contagem.png)

Figura 4. Contagem do programa *contador_figuras.cpp*

---

### Descrição do programa *contador_figuras.cpp*

No início do programa são instanciados dois objetos da biblioteca *opencv, um da classe* Mat para armazenar a imagem a ser tratada e outro da classe Point. Também são declaradas variáveis inteiras *width e height* para armazenar a largura e altura da imagem, e a variável *nobjects* que guardará a quantidade de objetos a serem contados.

```cpp
    cv::Mat image;
		cv::Point p;
    int width, height;
    int nobjects;
```

Logo após, faz-se a leitura da imagem, atribui-se as dimensões dela as variáveis correspondentes e imprimimos no programa tais dimensões e a imagem.

```cpp
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
```

Em seguida, depois de inicializar as coordenadas do objeto da classe *Point* com zeros, percorre-se cada uma das bordas da imagem. Caso seja encontrado algum pixel de valor 255, ou seja, da cor branca, o atribuímos a variável *p* que será a semente para a função *floodfill*. A função do *opencv* *floodfill* faz um preenchimento de uma região com um valor passado como parâmetro dado uma semente também passada por parâmetro. Assim, preenchendo as regiões das bordas de cor branca(255) para a cor preta(0), apaga-se todas as figuras da borda. É mostrado a seguir apenas o tratamento da borda superior.

    

```cpp
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
```

O trecho de código a seguir faz o processo conhecido como rotulação que consiste em percorrer a imagem atribuindo um rótulo(valor inteiro) a cada uma das regiões encontradas. A variável *nobjects* será responsável por atribuir tais rótulos com um incremento a cada região encontrada. Ao fim do processo a variável *nobjects* conterá a quantidade total de figuras na imagem.

```cpp
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
```

Para tornar melhor a visualização das figuras, o fundo da cena é preenchido com a cor branca.

```cpp
		// preenche o fundo com branco
    p.x = 0;
    p.y = 0;
    cv::floodFill(image, p, 255);
    cv::imshow("fundo branco", image);
    cv::waitKey();
```

Neste estágio do programa as únicas regiões que possuem o valor de seus pixels igual a zero são os buracos dentro das figuras. Assim, a contagem das figuras com buracos é feita percorrendo a imagem, "apagando" e contando as regiões em preto e "apagando" também a região um pixel anterior a ela pois pertence a figura que foi rotulada porém possui furo.

```cpp
// contando figuras com buracos
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
```

Por último, é apresentado as contagens finais, a cena com as figuras que não possuem furos e é escrito essa imagem resultante em outro arquivo png através da função *imwrite* do *opencv*.

```cpp
	std::cout << "a cena tem " << totalObjects << " figura que nao tocam margens\n";
    std::cout << "a cena tem " << nobjects << " figura com buracos\n";
    std::cout << "a cena tem " << totalObjects - nobjects << " figura sem buracos\n";
    cv::imshow("figuras sem furos", image);
    cv::imwrite("labeling.png", image);
    cv::waitKey();
    return 0;
```

Após a exibição de cada cena, a função *waitkey() do opencv* faz com que o programa aguarde o pressionamento de qualquer tecla para continuar.

---

## Exercício 4.2 a)

O programa *equalize.cpp* tem o objetivo de receber as imagens capturadas da câmera padrão do dispositivo, realizar a equalização do histograma de cada imagem capturada e mostrar as imagens equalizadas em uma janela. Na listagem 4 podemos observar o programa completo.

```cpp
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
```

O resultado do vídeo com a imagem equalizada em relação ao original é um contraste maior. Porém a vantagem dessa técnica se mostra quando temos cenas capturadas com brilho intenso ou com falta de luminosidade. A Figura 5 mostra esse efeito em uma imagem apenas usando o mesmo algoritmo.

![Processamento%20Digital%20de%20Imagem%20beb13c7019a14e51ab036322c65d94a9/lena_equalizada.png](Processamento%20Digital%20de%20Imagem%20beb13c7019a14e51ab036322c65d94a9/lena_equalizada.png)

Figura 5. Resultado do algoritmo *equalize.cpp*

É possível perceber um grande melhora para o olho humano após a equalização da imagem, porém também é possível notar o efeito de falso contorno causado pelo algoritmo. 

### Descrição do programa *equalize.cpp*

No início do programa são declaradas as variáveis que serão usadas ao longo dele como os objetos da classe **Mat** *image* e *histGray* que armazenam a imagem atual capturada pela câmera e o seu histograma respectivamente. O objeto *cap* da classe **VideoCapture** que pode abrir um fluxo de vídeo e outras variáveis que serão utilizadas e descritas posteriormente.

```cpp
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
```

Em seguida a câmera é aberta. Verifica-se se a abertura foi realizada corretamente e setamos e mostramos a largura e altura das imagens capturada.

```cpp
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
```

Dentro do loop infinito capturamos e convertemos para escala de cinza o a imagem da câmera.

```cpp
		cap >> image;
		cv::cvtColor(image, image, CV_BGR2GRAY);
```

De posse da imagem, utilizamos a função *calcHist* do *opencv* para armazenar o histograma da imagem atual no objeto *histGray* que possui 256 posições com um *range* de 0 a 255, uniformemente espaçados e não acumulado.

```cpp
		 cv::calcHist(&image, 1, 0, cv::Mat(), histGray, 1,
									 &nbins, &histrange,
				           uniform, acummulate);
```

Então calculamos o histograma acumulado e em seguida normalizamos através da função *normalize* do *opencv.*

```cpp
		float accumulator = 0;
    for (int i = 0; i < 256; i++) {
	       histGray.at<float>(i) = accumulator + histGray.at<float>(i);
    }
		cv::normalize(histGray, histGray, 0, 256, cv::NORM_MINMAX, -1, cv::Mat());
```

Em seguida, percorre-se a imagem com atualizando os valores com o do histograma acumulado.

```cpp
		for (int i = 0; i < height; i++) {
         for (int j = 0; j < width; j++) {
              image.at<uchar>(i, j) = histGray.at<float>(image.at<uchar>(i, j));
          }
    }
```

Por fim, a imagem equalizada é exibida e espera-se o usuário pressionar a tecla ESC para encerrar o programa.

```cpp
		cv::imshow("imagem equalizada", image);
    key = cv::waitKey(30);
    if (key == 27) break;
```

O *opencv* possui uma função específica que implementa a equalização de uma imagem passando como parâmetros uma imagem de origem e uma outra de destino. Um exemplo de chamada dessa função é *equalizeHist(src, dst);*
