/*Implementação dos métodos da classe Pixel
*/

#include "ExceptionMessages.h"
#include "Pixel.h"


/*Método construtor
float xbegin, float xend são os valores delimitadores do intervalo horizontal
	coberto pelo pixel,	no sistema de coordenadas da malha
	
float ybegin, float yend são os valores delimitadores do intervalo vertical
	coberto pelo pixel,	no sistema de coordenadas da malha
	
Vec4b* color é a cor RBGA inicial do pixel
*/
Pixel::Pixel(float xbegin, float xend, float ybegin, float yend, Vec4b* color, float z)
{
	/*assertivas para garantir consistência do pixel
	*/
	if(xbegin >= xend)
	{
		throw ExceptionMessage::PIXEL_INVALID_X_INTERVAL_MSSG;
	}
	if(ybegin >= yend)
	{
		throw ExceptionMessage::PIXEL_INVALID_Y_INTERVAL_MSSG;
	}
	if(xend - xbegin != yend - ybegin)
	{
		throw ExceptionMessage::PIXEL_NOT_SQUARE_MSSG;
	}
	if(color == NULL)
	{
		throw ExceptionMessage::PIXEL_NULL_COLOR_PTR_MSSG;
	}
	

	this->xbegin = xbegin;
	this->xend = xend;
	this->ybegin = ybegin;
	this->yend = yend;
	this->color = color;
	this->centerz = z;
}

/*coordenadas (X,Y,Z) do centro do pixel
*/
Vec3f* Pixel::center3d()
{
	return new Vec3f( (this->xend + this->xbegin)/2, (this->yend + this->ybegin)/2, centerz );
}

/*coordenadas (X,Y) do centro do pixel (projecao bidimensional)
*/
Vec2f* Pixel::center2d()
{
	return new Vec2f( (this->xend + this->xbegin)/2, (this->yend + this->ybegin)/2 );
}