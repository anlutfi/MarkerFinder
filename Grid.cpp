/*Implementa��o dos m�todos da classe Grid
*/

#include "ExceptionMessages.h"
#include "Grid.h"

/*M�todo construtor
int h � o numero de pixels de altura (dimens�o vertical da matriz)

int w � o numero de pixels de largura (dimens�o horizontal da matriz)

float Pixelsize � o tamanho do lado do pixel,
	no sistema de coordenadas usado

float xmin, float ymin s�o, respectivamente, as menores coordenadas x e y existentes
	no sistema de coordenadas usado. Ou seja, o ponto (xmin, ymin) � a origem do Grid.

Vec4b* defaultcolor � a cor inicial de cada pixel.
	Recomenda-se o uso de magenta (255, 255, 0) (RBG)

float defaultz � a coordenada z inicial dos pixels 
*/
Grid::Grid(int w, int h, float pixelsize, float xmin, float ymin,
	       Vec4b* defaultcolor, float defaultz)
{
	/*assertivas para garantir a consistencia do grid
	*/
	if(w <= 0)
	{
		throw ExceptionMessage::GRID_INVALID_WIDTH_MSSG;
	}
	if(h <= 0)
	{
		throw ExceptionMessage::GRID_INVALID_HEIGHT_MSSG;
	}
	if(pixelsize <= 0)
	{
		throw ExceptionMessage::GRID_INVALID_PIXEL_SIZE_MSSG;
	}
	if(defaultcolor == NULL)
	{
		throw ExceptionMessage::GRID_NULL_COLOR_PTR_MSSG;
	}

	/*atribui valores aos atributos do objeto
	*/
	this->h = h;
	this->w = w;
	this->defaultpixelz = defaultz;
	this->pixelsize = pixelsize;
	this->pixelarea = pow(this->pixelsize, 2);
	this->matrix = new Pixel**[h];
	
	/*instancia cada pixels com a cor padr�o, coordenada z padr�o e
	coordenadas x e y de inicio e fim de acordo com a posi��o do pixel no grid
	*/
	for(int i=0; i<this->h; i++)
	{
		this->matrix[i] = new Pixel*[w];
		
		for(int j=0; j<this->w; j++)
		{
			this->matrix[i][j] = new Pixel( (j*pixelsize) + xmin, ( (j+1)*pixelsize ) + xmin, (i*pixelsize) + ymin, ( (i+1)*pixelsize ) + ymin, defaultcolor, defaultz );
		}
	}
}

/*Gera a imagem png
*/
Mat Grid::image()
{
	/*cria uma imagem de resolu��o h*w com a fun��o do OpenCV
	o padr�o de cor do opencv eh RBGA em vez de RGBA
	*/
	Mat img( this->h, this->w, CV_8UC4, Scalar(255, 0, 255, 0) );
	
	//para cada pixel da imagem, atribui a cor de acordo com o pixel correspondente do grid
	for(int i = 0; i < this->h; i++)
	{
		for(int j = 0; j < this->w; j++)
		{
			img.at<Vec4b>(i,j) = *(this->matrix[i][j]->color);
		}
	}

	return img;
}
