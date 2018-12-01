#include "arc.h"
namespace Entities
{

Arc::Arc(const Point& center,double radius,double startAngle,double endAngle)
{
    m_center=center;
    m_radius=radius;
    m_startAngle=startAngle;
    m_endAngle=endAngle;
}

Arc::Arc(const Arc& arc)
{
    m_center=arc.GetCenter();
    m_radius=arc.GetRadius();
    m_startAngle=arc.GetStartAngle();
    m_endAngle=arc.GetEndAngle();
    SetAttributes(arc.GetAttributes());
}

Arc::~Arc()
{

}

Arc::Arc()
{

}

void Arc::Draw(QPainter& painter)
{
    QPen pen;
    pen.setColor(Qt::white);
    pen.setWidth(2);
    pen.setStyle(Qt::SolidLine);
    painter.setPen(pen);
    int d=2*m_drawableRadius;
    double centerX=m_center.GetDrawableX();
    double centerY=m_center.GetDrawableY();
    QRect rect(round(centerX-m_drawableRadius),round(centerY-m_drawableRadius),d,d);
    double spanAngle=m_endAngle-m_startAngle;
    if(m_startAngle>m_endAngle)
    {
        spanAngle+=360;
    }
    int startAngle=m_startAngle*16;
    spanAngle*=16;
    painter.drawArc(rect,startAngle,spanAngle);
}

Entity* Arc::Clone()
{
    Entity* arc=new Arc(*this);
    return arc;
}

void Arc::Transform(double*params,int size)
{
    if(size>0)
    {

        double scale=params[0];
        m_center.Transform(params,size);
        m_drawableRadius=m_radius/scale;
    }
}

void Arc::Scale(double ratio)
{
    m_center.Scale(ratio);
    m_drawableRadius*=ratio;
}

void Arc::Transfer(double dx,double dy,double dz)
{
    m_center.Transfer(dx,dy,dz);
}

void Arc::Rotate(double angle,double cx,double cy,double cz)
{

}
void Arc:: CorrectCoord(double bx,
                          double by,
                          double bz,
                          double sx,
                          double sy,
                          double sz,
                          double rotaAngle)
{
   m_center.CorrectCoord(bx,by,bz,sx,sy,sz,rotaAngle);
   m_radius*=sx;
   double angle=rotaAngle/PI*180;
   m_startAngle+=angle;
   m_endAngle+=angle;
}

}

