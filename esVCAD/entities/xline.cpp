#include "xline.h"
namespace Entities
{

XLine::XLine()
{
    m_xMax=0.0;
    m_yMax=0.0;
}

XLine::~XLine()
{

}

XLine::XLine(const Point&basePoint,const Point& dirVector)
{
    m_basePoint=basePoint;
    m_dirVector=dirVector;
}

XLine::XLine(const XLine& xLine)
{
    m_basePoint=xLine.GetBasePoint();
    m_dirVector=xLine.GetDirVector();
    m_drawablePoint1=xLine.GetDrawablePoint1();
    m_drawablePoint2=xLine.GetDrawablePoint2();
    m_xMax=xLine.GetXMax();
    m_yMax=xLine.GetYMax();
    SetAttributes(xLine.GetAttributes());
}
void XLine::Draw(QPainter& painter)
{
    QPen pen;
    pen.setColor(Qt::white);
    pen.setWidth(2);
    pen.setStyle(Qt::SolidLine);
    painter.setPen(pen);
    painter.drawLine(m_drawablePoint1.GetDrawableX(),m_drawablePoint1.GetDrawableY(),
                     m_drawablePoint2.GetDrawableX(),m_drawablePoint2.GetDrawableY());
}

Entity* XLine::Clone()
{
    Entity* xLine=new XLine(*this);
    return xLine;
}

void XLine::Transform(double*params,int size)
{
    if(size>4)
    {
        m_basePoint.Transform(params,size);
        m_yMax=params[1]+1;
        m_xMax=params[4]+1;
        ExportXLine();
    }

}

void XLine::ExportXLine()
{
    int dx=abs((int)m_dirVector.GetX());
    int dy=abs((int)m_dirVector.GetY());
    if(dx==1&&dy==0)
    {
        m_drawablePoint1.SetDrawableX(-1);
        m_drawablePoint1.SetDrawableY(m_basePoint.GetDrawableY());
        m_drawablePoint2.SetDrawableX(m_xMax);
        m_drawablePoint2.SetDrawableY(m_basePoint.GetDrawableY());
    }
    else if(dx==0&&dy==1)
    {
        m_drawablePoint1.SetDrawableX(m_basePoint.GetDrawableX());
        m_drawablePoint1.SetDrawableY(-1);
        m_drawablePoint2.SetDrawableX(m_basePoint.GetDrawableX());
        m_drawablePoint2.SetDrawableY(m_yMax);
    }
    else
    {
        double k=-m_dirVector.GetY()/m_dirVector.GetX();
        double baseX=m_basePoint.GetDrawableX();
        double baseY=m_basePoint.GetDrawableY();
        double b=baseY-k*baseX;
        //y=kx+b
        if(k<0)
        {
            m_drawablePoint1.SetDrawableX(0);
            m_drawablePoint1.SetDrawableY(b);
            m_drawablePoint2.SetDrawableX(-b/k);
            m_drawablePoint2.SetDrawableY(0);
        }
        else
        {
            m_drawablePoint1.SetDrawableX(0);
            m_drawablePoint1.SetDrawableY(b);
            m_drawablePoint2.SetDrawableX((m_yMax-b)/k);
            m_drawablePoint2.SetDrawableY(m_yMax);
        }

    }
}

void XLine::Scale(double ratio)
{
    m_basePoint.Scale(ratio);
    ExportXLine();
}

void XLine::Transfer(double dx,double dy,double dz)
{
    m_basePoint.Transfer(dx,dy,dz);
    ExportXLine();
}

void XLine::Rotate(double angle,double cx,double cy,double cz)
{

}
void XLine:: CorrectCoord(double bx,
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
