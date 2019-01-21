/**
Classe Mesh, que representa uma malha tridimensional de triangulos.

Os triangulos s�o objetos da classe Triangle
*/

#ifndef _MESH_H_
#define _MESH_H_

#include <iostream>
#include <fstream>

#include "Triangle.h"

class Mesh
{
public:
	/**
	*lista de v�rtices
	*/
	Vertex** vertices;

	/**
	*quantidade de v�rtices na lista de vertices
	*/
	int vertexcount;

	/**
	*lista de tri�ngulos
	*/
	Triangle** triangles;

	/**
	*quantidade de triangulos na lista de triangulos
	*/
	int trianglecount;

	/**
	*Metodo construtor da classe Mesh

	string meshfile � um arquivo texto contendo os dados da malha.
	Esse m�todo � responsavel por inicializar todos os v�rtices (classe Vertex)
	e todos os triangulos (classe Triangle)
	*/
	Mesh(string meshfile);
	
	/**
	*area total da malha projetada em 2D
	(ignorando a componente Z de todos os triangulos)
	*/
	float area2d();
};

#endif