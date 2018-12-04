#include "coordxy.h"
#define RECT_SIZE 10
namespace Entities
{

CoordXY::CoordXY():Rect()
{
    m_maxX=0.0;
    m_maxY=0.0;
}

CoordXY::~CoordXY()
{

}

CoordXY::CoordXY(const Point &leftTop,double width,double height):
    Rect(leftTop,width,height)
{
    m_maxX=0.0;
    m_maxY=0.0;
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

    int centerX=m_origin.GetDrawableX();
    int centerY=m_origin.GetDrawableY();
    if(centerX<RECT_SIZE) centerX=RECT_SIZE;
    if(centerY<RECT_SIZE) centerY=RECT_SIZE;
    if(centerX>=m_maxX-RECT_SIZE) centerX=m_maxX-RECT_SIZE;
    if(centerY>=m_maxY-RECT_SIZE) centerY=m_maxY-RECT_SIZE;

    QPen pen;
    pen.setColor(Qt::white);
    pen.setWidth(2);
    pen.setStyle(Qt::SolidLine);
    painter.setPen(pen);


    pen.setColor(Qt::green);
    painter.setPen(pen);
    painter.drawLine(centerX,centerY,centerX,0);
    pen.setColor(Qt::red);
    painter.setPen(pen);
    painter.drawLine(centerX,centerY,m_maxX,centerY);

    pen.setColor(Qt::blue);
    painter.setPen(pen);
    QRect rect(centerX-RECT_SIZE,centerY-RECT_SIZE,RECT_SIZE<<1,RECT_SIZE<<1);
    painter.drawRect(rect);

    pen.setColor(Qt::white);
    painter.setPen(pen);
    //draw x coord
    painter.drawLine(centerX,centerY,centerX+100,centerY);
    painter.drawText(centerX+50,centerY+25,"X");
    //draw y coord
    painter.drawLine(centerX,centerY,centerX,centerY-100);
    painter.drawText(centerX-25,centerY-50,"Y");
}

Entity* CoordXY:: Clone()
{
    Entity *coordXY=new CoordXY(*this);
    return coordXY;
}

void CoordXY::Transform(double*params,int size)
{
    //计算原点坐标
    if(size>4)
    {
        m_maxY=params[1];
        m_maxX=params[4];
        m_leftTop.Transform(params,size);
        m_rightBottom.Transform(params,size);
        m_origin.Transform(params,size);
    }

}

void CoordXY::Scale(double ratio)
{
    m_origin.Scale(ratio);
    //m_leftTop.Scale(ratio);
    //m_rightBottom.Scale(ratio);
}

void CoordXY::Transfer(double dx,double dy,double dz)
{
    m_origin.Transfer(dx,dy,dz);
    //m_leftTop.Transfer(dx,dy,dz);
    //m_rightBottom.Transfer(dx,dy,dz);
}

void CoordXY::Rotate(double angle,double cx,double cy,double cz)
{

}

void CoordXY:: CorrectCoord(double bx,
                            double by,
                            double bz,
                            double sx,
                            double sy,
                            double sz,
                            double rotaAngle)
{

}

}
