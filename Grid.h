/**
Classe Grid, que representa um array bidimensional de pixels (classe Pixel)
e gera uma imagem png a partir dele.
*/

#ifndef _GRID_H_
#define _GRID_H_

#include "Pixel.h"

class Grid
{
public:
	/**
	numero de pixels de altura (dimens�o vertical da matriz)
	*/
	int h;

	/**
	numero de pixels de largura (dimens�o horizontal da matriz)
	*/
	int w;

	/**
	matriz de h * w pixels
	*/
	Pixel*** matrix;

	/**
	coordenada z inicial dos pixels
	*/
	float defaultpixelz;
	
	/**
	tamanho do lado do pixel, no sistema de coordenadas usado
	*/
	float pixelsize;

	/**
	area do pixel (pixelsize * pixelsize)
	*/
	float pixelarea;
	
	/**
	M�todo construtor da classe Grid

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
	Grid(int h, int w, float Pixelsize, float xmin, float ymin,
	     Vec4b* defaultcolor, float defaultz);
	
	/**
	atribui a cor color ao pixel matrix[i][j]
	*/
	void setColor(int i, int j, Vec4b* color);
	
	/**
	Gera a imagem png
	*/
	Mat image();
};

#endif