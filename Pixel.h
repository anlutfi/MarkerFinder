/**
Classe Pixel
O pixel serve para desenhar uma seção quadrada de uma malha de triangulos (classe Mesh),
logo, alem da cor, cada pixel possui as informações sobre o intervalo que cobre no
sistema de coordenadas da malha.
*/

#ifndef _PIXEL_H_
#define _PIXEL_H_

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "ExceptionMessages.h"
 
using namespace cv;
using namespace std;

/**
Classe Pixel
O pixel serve para desenhar uma seção quadrada de uma malha de triangulos (classe Mesh),
logo, alem da cor, cada pixel possui as informações sobre o intervalo que cobre no
sistema de coordenadas da malha.
*/

class Pixel
{
public:
	/**
	*valor inicial do intervalo horizontal coberto pelo pixel,
	no sistema de coordenadas da malha
	*/
	float xbegin;
	
	/**
	*valor final do intervalo horizontal coberto pelo pixel,
	no sistema de coordenadas da malha
	*/
	float xend;

	/**
	*valor inicial do intervalo vertical coberto pelo pixel,
	no sistema de coordenadas da malha
	*/
	float ybegin;

	/**
	*valor final do intervalo vertical coberto pelo pixel,
	no sistema de coordenadas da malha
	*/
	float yend;

	/**
	*coordenada z do centro do pixel
	Basicamente, coordenada z do ponto da malha que, qdo projetado em 2d,
	coincide com o centro do pixel.
	*/
	float centerz;

	/**
	*cor RBGA do pixel
	*/
	Vec4b* color;

	/**
	*Método construtor da classe Pixel

	float xbegin, float xend são os valores delimitadores do intervalo horizontal
		coberto pelo pixel,	no sistema de coordenadas da malha
	
	float ybegin, float yend são os valores delimitadores do intervalo vertical
		coberto pelo pixel,	no sistema de coordenadas da malha
	
	Vec4b* color é a cor RBGA inicial do pixel
	*/
	Pixel(float xbegin, float xend, float ybegin, float yend, Vec4b* color, float z);

	/**
	*coordenadas (X,Y,Z) do centro do pixel
	*/
	Vec3f* center3d();

	/**
	*coordenadas (X,Y) do centro do pixel (projecao bidimensional)
	*/
	Vec2f* center2d();
};

#endif