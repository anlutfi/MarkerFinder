/*Implementa��o dos m�todos da classe ImageMaker
*/

#include "ExceptionMessages.h"
#include "ImageMaker.h"

/*M�todo construtor
Mesh* mesh � a malha de triangulos a ser usada

Vec4b* defaultcolor � a cor de inicializa��o dos pixels

float trianglesperpixel � o n�mero m�dio desejado de triangulos
	da malha contidos em cada pixel de grid.
*/
ImageMaker::ImageMaker(Mesh* mesh, Vec4b* defaultcolor, float trianglesperpixel)
{
	/*assertivas para garantir a consistencia do ImageMaker
	*/
	if(trianglesperpixel <= 0)
	{
		throw ExceptionMessage::IMAGEMAKER_INVALID_TPP_NUM_MSSG;
	}
	if(mesh == NULL)
	{
		throw ExceptionMessage::IMAGEMAKER_NULL_MESH_POINTER_MSSG;
	}
	if(defaultcolor == NULL)
	{
		throw ExceptionMessage::IMAGEMAKER_NULL_COLOR_POINTER_MSSG;
	}


	this->mesh = mesh;

	/*calcula a �rea do pixel a partir da �rea m�dia dos tri�ngulos em mesh
	e da quantidade m�dia de triangulos por pixel desejada
	*/
	cout << "calculating area...";
	float pixelarea = (mesh->area2d() / mesh->trianglecount) * trianglesperpixel;
	cout << "done - ";

	/*calcula o comprimento do lado do pixel
	*/
	float pixelsize = pow(pixelarea, 0.5F);

	/*instancia vari�veis de minimas e m�ximas coordenadas X e Y da malha
	*/
	float xmin, xmax, ymin, ymax;
	
	/*instancia variaveis para apura��o da coordenada Z m�dia da malha
	*/
	float z_acc;
	int i;
	
	/*apura os valores de xmin, xmax, ymin, ymax
	e acumula os valores das coordenadas Z em z_acc para o c�lculo da m�dia
	*/
	cout << "calculating bounds...";
	for(i=1,
		xmin = xmax = this->mesh->vertices[0]->position->val[X],
		ymin = ymax = this->mesh->vertices[0]->position->val[Y],
		z_acc = this->mesh->vertices[0]->position->val[Z];
		i < this->mesh->vertexcount;
		i++
	   )
	{
		xmin = min(xmin, this->mesh->vertices[i]->position->val[X]);
		xmax = max(xmax, this->mesh->vertices[i]->position->val[X]);
		ymin = min(ymin, this->mesh->vertices[i]->position->val[Y]);
		ymax = max(ymax, this->mesh->vertices[i]->position->val[Y]);
		z_acc += this->mesh->vertices[i]->position->val[Z];
	}
	cout << "done - ";

	/*determina largura w, em pixels, do grid
	*/
	float mesh_w = xmax - xmin;
	int w = (int)ceil(mesh_w/pixelsize);

	/*determina altura h, em pixels, do grid
	*/
	float mesh_h = ymax - ymin;
	int h = (int)ceil(mesh_h/pixelsize);
	
	/*determina a coordenada z m�dia dos v�rtices da mesh
	*/
	float z_avg = z_acc/(float)i;

	/*instancia o grid com os parametros obtidos
	*/
	this->grid = new Grid(w, h, pixelsize, xmin, ymin, defaultcolor, z_avg);

	/*calcula a cor de cada um dos pixels do grid
	*/
	cout << "calculating pixels' colors...";
	for(int u = 0; u<this->mesh->trianglecount; u++)
	{
		Triangle* t = this->mesh->triangles[u];
		
		/*determina a bounding box m�nima de pixels que contenha o triangulo t
		*/
		float txmin, txmax, tymin, tymax;
		txmin = min( min(t->a->position->val[X], t->b->position->val[X]), t->c->position->val[X] );
		
		txmax = max( max(t->a->position->val[X], t->b->position->val[X]), t->c->position->val[X] );

		tymin = min( min(t->a->position->val[Y], t->b->position->val[Y]), t->c->position->val[Y] );
															   
		tymax = max( max(t->a->position->val[Y], t->b->position->val[Y]), t->c->position->val[Y] );

		/*para cada pixel p da bounding box obtida, calcula a contribui��o do triangulo t
		para a cor de p, se houver alguma
		*/
		for(int pix_i = (int)floor( (tymin-ymin)/pixelsize );
			pix_i <= ( (int)ceil( (tymax-ymin)/pixelsize ) - 1 );
			pix_i++
		   )
		{
			for(int pix_j = (int)floor( (txmin-xmin)/pixelsize );
			    pix_j <= ( (int)ceil( (txmax-xmin)/pixelsize ) - 1 );
			    pix_j++
		       )
			{
				Pixel* p = this->grid->matrix[pix_i][pix_j];
				Vec2f* pcenter = p->center2d();
				
				/*se a proje��o 2D do triangulo t contiver o centro pcenter do pixel p,
				ent�o a cor de p � a cor de t,
				e a coordenada z de pcenter � calculada
				*/
				if( ImageMaker::pointInTriangle(pcenter, t) )
				{
					Vec3f* ba = new Vec3f( (t->b->position->val[X] - t->a->position->val[X]), (t->b->position->val[Y] - t->a->position->val[Y]), (t->b->position->val[Z] - t->a->position->val[Z]) );

					Vec3f* ca = new Vec3f( (t->c->position->val[X] - t->a->position->val[X]), (t->c->position->val[Y] - t->a->position->val[Y]), (t->c->position->val[Z] - t->a->position->val[Z]) );

					/*calcula a coordenada z de pcenter de acordo com a coordenada z
					do ponto do triangulo t que, quando projetado no pixel p,
					coincide com pcenter
					*/
					Vec3f* normal = new Vec3f();
					*normal = ba->cross(*ca);
					
					Vec3f* a = t->a->position;
					
					p->centerz = a->val[Z] + ((-1)*( ( (pcenter->val[X] - a->val[X])*normal->val[X] + (pcenter->val[Y] - a->val[Y])*normal->val[Y] ) / normal->val[Z] ));

					/*atribui a cor do triangulo t ao pixel p
					*/
					p->color = t->color();

				}
			}
		}
	}
	cout << "done - ";
}

/*verifica se dois pontos -p1 e p2- est�o do mesmo lado da reta a b
*/
bool ImageMaker::sameSide(Vec2f* p1, Vec2f* p2, Vec2f* a, Vec2f* b)
{
	/*assertivas
	*/
	if(p1 == NULL)
	{
		throw ExceptionMessage::IMAGEMAKER_NULL_P1_POINTER_MSSG;
	}
	if(p2 == NULL)
	{
		throw ExceptionMessage::IMAGEMAKER_NULL_P2_POINTER_MSSG;
	}
	if(a == NULL)
	{
		throw ExceptionMessage::IMAGEMAKER_NULL_A_POINTER_MSSG;
	}
	if(b == NULL)
	{
		throw ExceptionMessage::IMAGEMAKER_NULL_B_POINTER_MSSG;
	}
	if(p1 == p2)
	{
		throw ExceptionMessage::IMAGEMAKER_IDENTICAL_P1_P2_MSSG;
	}
	if(a == b)
	{
		throw ExceptionMessage::IMAGEMAKER_IDENTICAL_A_B_MSSG;
	}


	Vec3f* ba = new Vec3f(b->val[X] - a->val[X], b->val[Y] - a->val[Y], 0);
	Vec3f* p1a = new Vec3f(p1->val[X] - a->val[X], p1->val[Y] - a->val[Y], 0);
	Vec3f* p2a = new Vec3f(p2->val[X] - a->val[X], p2->val[Y] - a->val[Y], 0);

	Vec3f* cp1 = new Vec3f();
	*cp1 = ba->cross(*p1a);

	Vec3f* cp2 = new Vec3f();
	*cp2 = ba->cross(*p2a);

	if(  ( (cp1->val[X] * cp2->val[X]) + (cp1->val[Y] * cp2->val[Y]) + (cp1->val[Z] * cp2->val[Z]) ) >=0  )
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*verifica se um ponto p est� dentro do tri�ngulo t (em 2D)
*/
bool ImageMaker::pointInTriangle(Vec2f* p, Triangle* t)
{
	/*assertivas
	*/
	if(p == NULL)
	{
		throw ExceptionMessage::IMAGEMAKER_NULL_P_POINTER_MSSG;
	}
	if(p == NULL)
	{
		throw ExceptionMessage::IMAGEMAKER_NULL_T_POINTER_MSSG;
	}


	Vec2f* a = new Vec2f(t->a->position->val[X], t->a->position->val[Y]);
	Vec2f* b = new Vec2f(t->b->position->val[X], t->b->position->val[Y]);
	Vec2f* c = new Vec2f(t->c->position->val[X], t->c->position->val[Y]);
	
	if( ImageMaker::sameSide(p, a, b, c) && ImageMaker::sameSide(p, b, a, c) && ImageMaker::sameSide(p, c, a, b) )
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*gera e retorna a imagem png
*/
Mat ImageMaker::image()
{
	return this->grid->image();
}
