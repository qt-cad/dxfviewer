#include "coordxy.h"
namespace Entities
{

CoordXY::CoordXY()
{

}

CoordXY::~CoordXY()
{

}

CoordXY::CoordXY(const Point &leftTop,double width,double height):
    Rect(leftTop,width,height)
{

}

CoordXY::CoordXY(const Point &leftTop, const Point &rightBottom):
    Rect(leftTop,rightBottom)
{

}

CoordXY::CoordXY(const CoordXY& coordXY)
{
  m_leftTop=coordXY.GetLeftTop();
  m_rightBottom=coordXY.GetRightBottom();
  SetAttributes(coordXY.GetAttributes());
}

void CoordXY::Draw(QPainter& painter)
{
    int w=GetWidth();
    int h=GetHeihgt();
    QPen pen;
    pen.setColor(Qt::white);
    pen.setWidth(2);
    pen.setStyle(Qt::SolidLine);
    painter.setPen(pen);
    QRect rect(20,h-30,20,20);
    painter.drawRect(rect);
    int centerX=30;
    int centerY=h-20;
    //draw x coord
    painter.drawLine(centerX,centerY,centerX+100,centerY);
    painter.drawText(centerX+50,centerY+15,"X");
    //draw y coord
    painter.drawLine(centerX,centerY,centerX,centerY-100);
    painter.drawText(15,centerY-50,"Y");

    pen.setColor(Qt::green);
    painter.setPen(pen);
    painter.drawLine(centerX,centerY-100,centerX,-1);
    pen.setColor(Qt::red);
    painter.setPen(pen);
    painter.drawLine(centerX+100,centerY,w+1,centerY);
}

Entity* CoordXY:: Clone()
{
   Entity *coordXY=new CoordXY(*this);
   return coordXY;
}

void CoordXY::Transform(double*params,int size)
{
    m_leftTop.Transform(params,size);
    m_rightBottom.Transform(params,size);
}

void CoordXY::Scale(double ratio)
{
    m_leftTop.Scale(ratio);
    m_rightBottom.Scale(ratio);
}

void CoordXY::Transfer(double dx,double dy,double dz)
{
    m_leftTop.Transfer(dx,dy,dz);
    m_rightBottom.Transfer(dx,dy,dz);
}

void CoordXY::Rotate(double angle,double cx,double cy,double cz)
{

}

}
