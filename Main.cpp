/*Módulo principal do projeto MarkerFinder
*/

#include "ImageMaker.h"
#include <time.h>

namespace
{
    /*Nomes das janelas e das trackbars
	*/
    const std::string windowName = "Circle Detection";
    const std::string cannyThresholdTrackbarName = "Canny threshold";
    const std::string accumulatorThresholdTrackbarName = "Accumulator Threshold";
	const std::string bigradiustb = "Large circle radius";
	const std::string bigtresholdtb =  "Large radius treshold";
	const std::string smallradiustb = "Small circle radius";
	const std::string smalltresholdtb =  "Small radius treshold";

    /*valores iniciais e máximos dos parâmetros relevantes
	*/
    const int cannyThresholdInitialValue = 200;
    const int accumulatorThresholdInitialValue = 50;
    const int maxAccumulatorThreshold = 200;
    const int maxCannyThreshold = 255;
	const int maxbigradius = 255;
	const int maxsmallradius = 255;
	const int maxbigradiustreshold = 255;
	const int maxsmallradiustreshold = 255;

    /*Função que recebe uma imagem png e retorna uma lista de círculos detectados nela
	pelo algorítmo de detecção de Hough
	*/
	std::vector<Vec3f> HoughDetection(const Mat& src_gray,
						const Mat& src_display,
						int cannyThreshold,
						int accumulatorThreshold,
						int bigradius,
						int bigtreshold,
						int smallradius,
						int smalltreshold)
    {
        /*listas que guardarão os círculos detectados
		*/
        std::vector<Vec3f> circles;
		std::vector<Vec3f> bigcircles;
		std::vector<Vec3f> smallcircles;
        
		/*detecta os círculos maiores na imagem e os guarda em bigcircles
		*/
        HoughCircles( src_gray, bigcircles, CV_HOUGH_GRADIENT, 1, src_gray.rows/8,
					  cannyThreshold, accumulatorThreshold,
					  max(0, (bigradius - bigtreshold)),
					  min(maxbigradius, (bigradius + bigtreshold)) );

		/*detecta os círculos menores na imagem e os guarda em smallcircles
		*/
        HoughCircles( src_gray, smallcircles, CV_HOUGH_GRADIENT, 1, src_gray.rows/8,
					  cannyThreshold, accumulatorThreshold,
					  max(0, (smallradius - smalltreshold)),
					  min(maxsmallradius, (smallradius + smalltreshold)) );

        /*copia a imagem original para exibição em janela
		*/
        Mat display = src_display.clone();

		/*desenha os círculos menores na imagem copiada*/
        for( size_t i = 0; i < smallcircles.size(); i++ )
        {
            Point center(cvRound(smallcircles[i][X]), cvRound(smallcircles[i][Y]));
            int radius = cvRound(smallcircles[i][2]);
            
			/*desenha o centro do círculo
			*/
            circle( display, center, 1, Scalar(0,255,0), -2, 8, 0 );
            
			/*desenha a circunferencia do círculo
			*/
            circle( display, center, radius, Scalar(0,0,255), 2, 8, 0 );
        }

		/*desenha os círculos maiores na imagem copiada*/
		for( size_t i = 0; i < bigcircles.size(); i++ )
        {
            Point center(cvRound(bigcircles[i][X]), cvRound(bigcircles[i][Y]));
            int radius = cvRound(bigcircles[i][2]);
            
			/*desenha o centro do círculo
			*/
            circle( display, center, 1, Scalar(0,0,255), -2, 8, 0 );
            
			/*desenha a circunferencia do círculo
			*/
            circle( display, center, radius, Scalar(255,0,0), 2, 8, 0 );
        }

        /*exibe a imagem com os círculos detectados
		*/
        imshow( windowName, display);
		
		/*insere todos os circulos encontrados - pequenos e grandes - em circles
		e retorna circles
		*/
		circles.reserve(smallcircles.size() + bigcircles.size());
		circles.insert(circles.end(), smallcircles.begin(), smallcircles.end());
		circles.insert(circles.end(), bigcircles.begin(), bigcircles.end());
		return circles;
    }
}


int main(int argc, char** argv)
{
    assert(("Main.cpp - function main() - Application requires a filename as parameter and received none",
			argc < 2
		  ));
	
	cout << " -  - ";
	
	/*instancia a mesh que conterá a malha recebida de entrada
	*/
	Mat src, src_gray;

    /*inicia a contagem de tempo de processamento da geração da imagem
	e exibe na tela
	*/
	time_t begin = time(NULL);
	printf("Process began at: %02d:%02d:%02d (GMT) -  - ",
		   (int(begin) % 86400) / 3600, (int(begin) % 3600) / 60, int(begin) % 60);
	
	/*instancia um ImageMaker imk, com a malha recebida de entrada
	*/
	Mesh* m = new Mesh(argv[1]);
	ImageMaker* imk = new ImageMaker(m, new Vec4b(255, 0, 255, 0), 2);
	
	/*calcula e guarda, em src, a imagem gerada por imk
	*/
	cout << "generating image...";
	src = imk->image();
	cout << "done -  - ";
	
	/*afere e exibe na tela o tempo de processamento gasto na geração da imagem
	*/
	time_t end = time(NULL);
	double diff = difftime(end, begin);
	printf("Process completed at: %02d:%02d:%02d (GMT) - ",
		   (int(end) % 86400) / 3600, (int(end) % 3600) / 60, int(end) % 60);
	printf("Elapsed time: %02d:%02d:%02d -  - ",
		   (int(diff) % 86400) / 3600, (int(diff) % 3600) / 60, int(diff) % 60);
	
    /*converte a imagem src para tons de cinza e a guarda em src_gray
	*/
    cvtColor( src, src_gray, COLOR_BGR2GRAY );

    /*Reduz ruido da imagem para evitar falsa detecção de círculos
	*/
    GaussianBlur( src_gray, src_gray, Size(9, 9), 2, 2 );

    /*declara a inicializa os parametros mutáveis pelas trackbars da janela de display
	*/
    int cannyThreshold = cannyThresholdInitialValue;
    int accumulatorThreshold = accumulatorThresholdInitialValue;
	int bigradius = 10;
	int bigtreshold = 3;
	int smallradius = 5;
	int smalltreshold = 3;

    /*cria a janela e as trackbars
	*/
    namedWindow( windowName, WINDOW_NORMAL);
    createTrackbar(cannyThresholdTrackbarName, windowName, &cannyThreshold,maxCannyThreshold);
    createTrackbar(accumulatorThresholdTrackbarName, windowName, &accumulatorThreshold, maxAccumulatorThreshold);
	createTrackbar(bigradiustb, windowName, &bigradius, maxbigradius);
	createTrackbar(bigtresholdtb, windowName, &bigtreshold, maxbigradiustreshold);
	createTrackbar(smallradiustb, windowName, &smallradius, maxsmallradius);
	createTrackbar(smalltresholdtb, windowName, &smalltreshold, maxsmallradiustreshold);

    /*enquanto o usuário não pressionar q ou Q, exibe os resultados da detecção e aguarda
	mudança de parametros das trackbars para nova detecção
	*/
    int key = 0;
    std::vector<Vec3f> circles;
	while(key != 'q' && key != 'Q')
    {
        /*os parametros não podem ser zero
		*/
        cannyThreshold = std::max(cannyThreshold, 1);
        accumulatorThreshold = std::max(accumulatorThreshold, 1);

        /*roda a detecção e exibe os resultados
		*/
        circles = HoughDetection(src_gray, src, cannyThreshold,
								 accumulatorThreshold,
								 bigradius, bigtreshold, smallradius, smalltreshold);

        /*trata input do usuário
		*/
        key = waitKey(10);
    }
	
	/*uma vez que o usuário esteja satisfeito com a detecção de circulos,
	lista na tela as coordenadas XYZ dos centros dos círculos e seus raios
	*/
	cout<<"X  Y  Z  Radius - ";
	for( size_t i = 0; i < circles.size(); i++ )
	{
		Vec3f* circleCenter = imk->grid->matrix[ (int)floor(circles[i][Y]) ]
											   [ (int)floor(circles[i][X]) ]->center3d();
		
		cout<<circleCenter->val[X]<<" "<<circleCenter->val[Y]
			<<" "<<circleCenter->val[Z]<<" "<<circles[i][2]<<" - ";
	}
	
	/*aguarda pressionamento de tecla do usuário para finalizar execuçao da aplicação
	*/
	waitKey(0);
	return 0;
}