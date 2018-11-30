#include "point.h"
namespace Entities
{
#define INIT_RADIUS 5
Point::Point():
    m_x(0.0),
    m_y(0.0),
    m_z(0.0),
    m_bulge(0.0),
    m_ptRadius(INIT_RADIUS),
    m_drawableX(0.0),
    m_drawableY(0.0),
    m_drawableZ(0.0)
{

}

Point::Point(double x,double y,double z)
{
    m_x=x;
    m_y=y;
    m_z=z;
    m_bulge=0.0;
    m_ptRadius=INIT_RADIUS;
    m_drawableX=0.0;
    m_drawableY=0.0;
    m_drawableZ=0.0;
}

Point::Point(double x,double y,double z,double bulge)
{
    m_x=x;
    m_y=y;
    m_z=z;
    m_bulge=bulge;
    m_ptRadius=INIT_RADIUS;
    m_drawableX=0.0;
    m_drawableY=0.0;
    m_drawableZ=0.0;
}

Point::Point(const Point&pt)
{
    m_x=pt.GetX();
    m_y=pt.GetY();
    m_z=pt.GetZ();
    m_bulge=pt.GetBulge();
    m_ptRadius=pt.GetRadius();
    m_drawableX=pt.GetDrawableX();
    m_drawableY=pt.GetDrawableY();
    m_drawableZ=pt.GetDrawableZ();
    SetAttributes(pt.GetAttributes());
}

Point::~Point()
{

}
Point& Point::operator =(const Point&pt)
{
    if(&pt!=this)
    {
        m_x=pt.GetX();
        m_y=pt.GetY();
        m_z=pt.GetZ();
        m_bulge=pt.GetBulge();
        m_ptRadius=pt.GetRadius();
        m_drawableX=pt.GetDrawableX();
        m_drawableY=pt.GetDrawableY();
        m_drawableZ=pt.GetDrawableZ();
        SetAttributes(pt.GetAttributes());
    }
    return *this;
}

bool Point::operator ==(const Point&pt)
{
    if(m_x==pt.GetX()
       &&m_y==pt.GetY()
       &&m_z==pt.GetZ()
       &&m_bulge==pt.GetBulge()
       &&m_drawableX==pt.GetDrawableX()
       &&m_drawableY==pt.GetDrawableY()
       &&m_drawableZ==pt.GetDrawableZ()
       )
    {
        return true;
    }
    return false;
}
void Point::Draw(QPainter& painter)
{
    QPen pen;
    pen.setColor(Qt::white);
    pen.setWidth(2);
    pen.setStyle(Qt::SolidLine);
    painter.setPen(pen);
    int d=2*m_ptRadius;
    if(m_ptRadius>5)
    {
        painter.drawEllipse(round(m_drawableX-m_ptRadius),round(m_drawableY-m_ptRadius),d,d);
        painter.drawLine(m_drawableX,m_drawableY,m_drawableX-d,m_drawableY);
        painter.drawLine(m_drawableX,m_drawableY,m_drawableX+d,m_drawableY);
        painter.drawLine(m_drawableX,m_drawableY,m_drawableX,m_drawableY-d);
        painter.drawLine(m_drawableX,m_drawableY,m_drawableX,m_drawableY+d);
    }
    else
    {
       painter.save();
       QBrush brush(Qt::white);
       painter.setBrush(brush);
       painter.drawEllipse(round(m_drawableX-m_ptRadius),round(m_drawableY-m_ptRadius),d,d);
       painter.restore();
    }

}

Entity* Point::Clone()
{
    Entity *pt=new Point(*this);
    return pt;
}

void Point::Transform(double*params,int size)
{
    if(size>=4)
    {

      double scale=params[0];
      double yMax=params[1];
      double dx=params[2];
      double dy=params[3];
      m_drawableX=(m_x-dx)/scale;
      m_drawableY=yMax-((m_y-dy)/scale);
      m_drawableZ=(m_z-dx)/scale;
      //m_ptRadius=m_ptRadius/scale;
    }
}

void Point::Scale(double ratio)
{

    m_drawableX*=ratio;
    m_drawableY*=ratio;
    m_drawableZ*=ratio;
    m_ptRadius*=ratio;
}

void Point::Transfer(double dx,double dy,double dz)
{
    m_drawableX+=dx;
    m_drawableY+=dy;
    m_drawableZ+=dz;
}

void Point::Rotate(double angle,double cx,double cy,double cz)
{
    //rota at org
    //int newX = x*cosValue-y*sinValue;
    //int newY = x*sinValue+y*cosValue;
    //rota at a point (x2,y2)
    //x=(x1-x2)cosθ-(y1-y2)sinθ+x2
    //y=(y1-y2)cosθ+(x1-x2)sinθ+y2
    double cosVal=cos(angle);
    double sinVal=sin(angle);
    m_drawableX=(m_drawableX-cx)*cosVal-(m_drawableY-cy)*sinVal+cx;
    m_drawableY=(m_drawableY-cy)*cosVal+(m_drawableX-cx)*sinVal+cy;
}

}
