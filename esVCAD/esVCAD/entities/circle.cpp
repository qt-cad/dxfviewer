#include "circle.h"
namespace Entities
{

Circle::Circle():
    m_radius(0.0),
    m_center(0.0,0.0,0.0),
    m_drawableRadius(0.0)
{

}

Circle::Circle(const Point &center,double radius)
{
    m_center=center;
    m_radius=radius;
    m_drawableRadius=0.0;
}

Circle::Circle(const Circle &circle)
{
    m_center=circle.m_center;
    m_radius=circle.m_radius;
    m_drawableRadius=circle.GetDrawableRadius();
    SetAttributes(circle.GetAttributes());
}

Circle::~Circle()
{

}

void Circle::Draw(QPainter& painter)
{
    QPen pen;
    pen.setColor(Qt::white);
    pen.setWidth(2);
    pen.setStyle(Qt::SolidLine);
    painter.setPen(pen);
    double centerX=m_center.GetDrawableX();
    double centerY=m_center.GetDrawableY();
    QPoint point(round(centerX),round(centerY));
    int radius=round(m_drawableRadius);
    painter.drawEllipse(point,radius,radius);

}

Entity*Circle::Clone()
{
    Entity *circle=new Circle(*this);
    return circle;
}

void Circle::Transform(double*params,int size)
{
    if(size>0)
    {

      double scale=params[0];
      m_center.Transform(params,size);
      m_drawableRadius=m_radius/scale;
    }
}
void Circle::Scale(double ratio)
{
    m_center.Scale(ratio);
    m_drawableRadius*=ratio;
}

void Circle::Transfer(double dx,double dy,double dz)
{
    m_center.Transfer(dx,dy,dz);
}

void Circle::Rotate(double angle,double cx,double cy,double cz)
{

}

}
