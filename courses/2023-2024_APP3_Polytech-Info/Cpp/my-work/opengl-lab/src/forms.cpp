#include <cmath>
#include <SDL2/SDL_opengl.h>
#include <GL/GLU.h>
#include "forms.h"


void Form::update(double delta_t)
{
    // Nothing to do here, animation update is done in child class method
}


void Form::render()
{
    // Point of view for rendering
    // Common for all Forms
    Point org = anim.getPos();
    glTranslated(org.x, org.y, org.z);
    glColor3f(col.r, col.g, col.b);
    glRotated(getAnim().getPhi(), 0, 1, 0);
    glRotated(getAnim().getTheta(), 1, 0, 0);

    /*
    On ne peut pas permuter n'importe comment, car d'une part les produits
    matriciels ne sont pas commutatifs, et d'autre part, il est clair
    que la rotation autour de Y d'un objet loin de cet axe sera radicalement different
    d'une rotation proche de l'origine.
    */
}


Sphere::Sphere(double r, Color cl)
{
    radius = r;
    col = cl;
}


void Sphere::update(double delta_t)
{
    // Complete this part
}


void Sphere::render()
{
    GLUquadric *quad;

    quad = gluNewQuadric();

    // Complete this part

    gluDeleteQuadric(quad);
}


Cube_face::Cube_face(Vector v1, Vector v2, Point org, double l, double w, Color cl)
{
    vdir1 = 1.0 / v1.norm() * v1;
    vdir2 = 1.0 / v2.norm() * v2;
    anim.setPos(org);
    length = l;
    width = w;
    col = cl;
}


void Cube_face::update(double delta_t)
{
    //printf("; phi B : %f", this->anim.getPhi());
    this->anim.setPhi((this->anim.getPhi()+1));
    this->anim.setTheta((this->anim.getTheta()+1));
    //printf("; phi A : %f", this->anim.getPhi());
}


void Cube_face::render()
{
    Point p1 = Point();
    Point p2 = p1, p3, p4 = p1;
    p2.translate(length*vdir1);
    p3 = p2;
    p3.translate(width*vdir2);
    p4.translate(width*vdir2);

    Form::render();

    glBegin(GL_QUADS);
    {
        glVertex3d(p1.x, p1.y, p1.z);
        glVertex3d(p2.x, p2.y, p2.z);
        glVertex3d(p3.x, p3.y, p3.z);
        glVertex3d(p4.x, p4.y, p4.z);
    }
    glEnd();
}

Cube::Cube(Point org, double l, Color cl)
{
    length = l;
    col = cl;
    faces[0] = Cube_face(Vector(1,0,0), Vector(0,1,0), org, l, l, BLUE);
    faces[1] = Cube_face(Vector(1,0,0), Vector(0,0,1), org, l, l, YELLOW);
    faces[2] = Cube_face(Vector(0,1,0), Vector(0,0,1), org, l, l, GREEN);
    faces[3] = Cube_face(Vector(1,0,0), Vector(0,1,0), Point(org.x,org.y,org.z+l), l, l, WHITE);
    faces[4] = Cube_face(Vector(1,0,0), Vector(0,0,1), Point(org.x-1,org.y-1,org.z) , l, l, ORANGE);
    faces[5] = Cube_face(Vector(0,1,0), Vector(0,0,1), Point(org.x+l,org.y+l,org.z-l), l, l, RED);
}

void Cube::update(double delta_t)
{
    //ne pas update les animations des faces
    //mais les animations du cube, qui se répercuteront sur les faces
    this->anim.setPhi((this->anim.getPhi()+1));
    this->anim.setTheta((this->anim.getTheta()+1));
}

void Cube::render()
{
    Point org = anim.getPos();
    glTranslated(org.x, org.y, org.z);
    glColor3f(col.r, col.g, col.b);
    glRotated(getAnim().getPhi(), 0, 1, 0);
    glRotated(getAnim().getTheta(), 1, 0, 0);
    for (int i = 0; i < 6; i++)
    {   
        faces[i].render();
    }
}

