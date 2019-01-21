/**
Classe Mesh, que representa uma malha tridimensional de triangulos.

Os triangulos são objetos da classe Triangle
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
	*lista de vértices
	*/
	Vertex** vertices;

	/**
	*quantidade de vértices na lista de vertices
	*/
	int vertexcount;

	/**
	*lista de triângulos
	*/
	Triangle** triangles;

	/**
	*quantidade de triangulos na lista de triangulos
	*/
	int trianglecount;

	/**
	*Metodo construtor da classe Mesh

	string meshfile é um arquivo texto contendo os dados da malha.
	Esse método é responsavel por inicializar todos os vértices (classe Vertex)
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