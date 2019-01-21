/*M�dulo principal do projeto MarkerFinder
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

    /*valores iniciais e m�ximos dos par�metros relevantes
	*/
    const int cannyThresholdInitialValue = 200;
    const int accumulatorThresholdInitialValue = 50;
    const int maxAccumulatorThreshold = 200;
    const int maxCannyThreshold = 255;
	const int maxbigradius = 255;
	const int maxsmallradius = 255;
	const int maxbigradiustreshold = 255;
	const int maxsmallradiustreshold = 255;

    /*Fun��o que recebe uma imagem png e retorna uma lista de c�rculos detectados nela
	pelo algor�tmo de detec��o de Hough
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
        /*listas que guardar�o os c�rculos detectados
		*/
        std::vector<Vec3f> circles;
		std::vector<Vec3f> bigcircles;
		std::vector<Vec3f> smallcircles;
        
		/*detecta os c�rculos maiores na imagem e os guarda em bigcircles
		*/
        HoughCircles( src_gray, bigcircles, CV_HOUGH_GRADIENT, 1, src_gray.rows/8,
					  cannyThreshold, accumulatorThreshold,
					  max(0, (bigradius - bigtreshold)),
					  min(maxbigradius, (bigradius + bigtreshold)) );

		/*detecta os c�rculos menores na imagem e os guarda em smallcircles
		*/
        HoughCircles( src_gray, smallcircles, CV_HOUGH_GRADIENT, 1, src_gray.rows/8,
					  cannyThreshold, accumulatorThreshold,
					  max(0, (smallradius - smalltreshold)),
					  min(maxsmallradius, (smallradius + smalltreshold)) );

        /*copia a imagem original para exibi��o em janela
		*/
        Mat display = src_display.clone();

		/*desenha os c�rculos menores na imagem copiada*/
        for( size_t i = 0; i < smallcircles.size(); i++ )
        {
            Point center(cvRound(smallcircles[i][X]), cvRound(smallcircles[i][Y]));
            int radius = cvRound(smallcircles[i][2]);
            
			/*desenha o centro do c�rculo
			*/
            circle( display, center, 1, Scalar(0,255,0), -2, 8, 0 );
            
			/*desenha a circunferencia do c�rculo
			*/
            circle( display, center, radius, Scalar(0,0,255), 2, 8, 0 );
        }

		/*desenha os c�rculos maiores na imagem copiada*/
		for( size_t i = 0; i < bigcircles.size(); i++ )
        {
            Point center(cvRound(bigcircles[i][X]), cvRound(bigcircles[i][Y]));
            int radius = cvRound(bigcircles[i][2]);
            
			/*desenha o centro do c�rculo
			*/
            circle( display, center, 1, Scalar(0,0,255), -2, 8, 0 );
            
			/*desenha a circunferencia do c�rculo
			*/
            circle( display, center, radius, Scalar(255,0,0), 2, 8, 0 );
        }

        /*exibe a imagem com os c�rculos detectados
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
	
	/*instancia a mesh que conter� a malha recebida de entrada
	*/
	Mat src, src_gray;

    /*inicia a contagem de tempo de processamento da gera��o da imagem
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
	
	/*afere e exibe na tela o tempo de processamento gasto na gera��o da imagem
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

    /*Reduz ruido da imagem para evitar falsa detec��o de c�rculos
	*/
    GaussianBlur( src_gray, src_gray, Size(9, 9), 2, 2 );

    /*declara a inicializa os parametros mut�veis pelas trackbars da janela de display
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

    /*enquanto o usu�rio n�o pressionar q ou Q, exibe os resultados da detec��o e aguarda
	mudan�a de parametros das trackbars para nova detec��o
	*/
    int key = 0;
    std::vector<Vec3f> circles;
	while(key != 'q' && key != 'Q')
    {
        /*os parametros n�o podem ser zero
		*/
        cannyThreshold = std::max(cannyThreshold, 1);
        accumulatorThreshold = std::max(accumulatorThreshold, 1);

        /*roda a detec��o e exibe os resultados
		*/
        circles = HoughDetection(src_gray, src, cannyThreshold,
								 accumulatorThreshold,
								 bigradius, bigtreshold, smallradius, smalltreshold);

        /*trata input do usu�rio
		*/
        key = waitKey(10);
    }
	
	/*uma vez que o usu�rio esteja satisfeito com a detec��o de circulos,
	lista na tela as coordenadas XYZ dos centros dos c�rculos e seus raios
	*/
	cout<<"X  Y  Z  Radius - ";
	for( size_t i = 0; i < circles.size(); i++ )
	{
		Vec3f* circleCenter = imk->grid->matrix[ (int)floor(circles[i][Y]) ]
											   [ (int)floor(circles[i][X]) ]->center3d();
		
		cout<<circleCenter->val[X]<<" "<<circleCenter->val[Y]
			<<" "<<circleCenter->val[Z]<<" "<<circles[i][2]<<" - ";
	}
	
	/*aguarda pressionamento de tecla do usu�rio para finalizar execu�ao da aplica��o
	*/
	waitKey(0);
	return 0;
}