#include "ray.h"
namespace Entities
{

Ray::Ray()
{

}

Ray::Ray(const Point&basePoint,const Point& dirVector):
    XLine(basePoint,dirVector)
{

}

Ray::Ray(const Ray& ray)
{
    m_basePoint=ray.GetBasePoint();
    m_dirVector=ray.GetDirVector();
    SetAttributes(ray.GetAttributes());
}

Ray::~Ray()
{

}

void Ray::Draw(QPainter& painter)
{

}

Entity* Ray::Clone()
{
    Entity* ray=new Ray(*this);
}
void Ray::Transform(double*params,int size)
{
    XLine::Transform(params,size);
}
void Ray::Scale(double ratio)
{
    XLine::Scale(ratio);
}
void Ray::Transfer(double dx,double dy,double dz)
{
    XLine::Transfer(dx,dy,dz);
}
void Ray::Rotate(double angle,double cx,double cy,double cz)
{
    XLine::Rotate(angle,cx,cy,cz);
}

void Ray::ExportRay()
{

}
void Ray:: CorrectCoord(double bx,
                        double by,
                        double bz,
                        double sx,
                        double sy,
                        double sz,
                        double rotaAngle)
{
    m_basePoint.CorrectCoord(bx,by,bz,sx,sy,sz,rotaAngle);
}

}
