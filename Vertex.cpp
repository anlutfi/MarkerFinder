/*Implementa��o dos m�todos da classe Vertex
*/

#include "Vertex.h"

/*M�todo construtor:
float x, float y, float z s�o as coordenadas x,y,z da posi��o do v�rtice

uchar r, uchar g, uchar b, uchar a s�o as componentes r, g, b, a da cor do v�rtice
*/
Vertex::Vertex(float x, float y, float z, uchar r, uchar g, uchar b, uchar a)
{
	this->position = new Vec3f(x, y, z);
	this->color = new Vec4b(r, g, b, a);
}

/*Proje��o bidimensional do ponto, ou seja, suas coordenadas (X,Y).
*/
Vec2f* Vertex::bidim (void)
{
	return new Vec2f((float)this->position->val[X], (float)this->position->val[Y]);
}