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
    QPen pen;
    pen.setColor(Qt::white);
    pen.setWidth(2);
    pen.setStyle(Qt::SolidLine);
    painter.setPen(pen);
    painter.drawLine(m_drawablePoint1.GetDrawableX(),m_drawablePoint1.GetDrawableY(),
                     m_drawablePoint2.GetDrawableX(),m_drawablePoint2.GetDrawableY());
}

Entity* Ray::Clone()
{
    Entity* ray=new Ray(*this);
    return ray;
}
void Ray::Transform(double*params,int size)
{
    if(size>4)
    {
        m_basePoint.Transform(params,size);
        m_yMax=params[1]+1;
        m_xMax=params[4]+1;
        ExportRay();
    }
}
void Ray::Scale(double ratio)
{
    m_basePoint.Scale(ratio);
    ExportRay();
}
void Ray::Transfer(double dx,double dy,double dz)
{
    m_basePoint.Transfer(dx,dy,dz);
    ExportRay();
}
void Ray::Rotate(double angle,double cx,double cy,double cz)
{
    m_basePoint.Rotate(angle,cx,cy,cz);
    ExportRay();
}

void Ray::ExportRay()
{
    int dx=(int)m_dirVector.GetX();
    int dy=(int)m_dirVector.GetY();
    m_drawablePoint1.SetDrawableX(m_basePoint.GetDrawableX());
    m_drawablePoint1.SetDrawableY(m_basePoint.GetDrawableY());
    if(dx==1&&dy==0)
    {
        m_drawablePoint2.SetDrawableX(m_xMax);
        m_drawablePoint2.SetDrawableY(m_basePoint.GetDrawableY());
    }
    else if(dx==-1&&dy==0)
    {
        m_drawablePoint2.SetDrawableX(0);
        m_drawablePoint2.SetDrawableY(m_basePoint.GetDrawableY());
    }
    else if(dx==0&&dy==1)
    {
        m_drawablePoint2.SetDrawableX(m_basePoint.GetDrawableX());
        m_drawablePoint2.SetDrawableY(0);
    }
    else if(dx==0&&dy==-1)
    {
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
            if(m_dirVector.GetY()<0)
            {
                m_drawablePoint2.SetDrawableX(0);
                m_drawablePoint2.SetDrawableY(b);
            }
            else
            {
                m_drawablePoint2.SetDrawableX(-b/k);
                m_drawablePoint2.SetDrawableY(0);
            }

        }
        else
        {
             if(m_dirVector.GetY()<0)
             {
                 m_drawablePoint2.SetDrawableX((m_yMax-b)/k);
                 m_drawablePoint2.SetDrawableY(m_yMax);
             }
             else
             {
                 m_drawablePoint2.SetDrawableX(0);
                 m_drawablePoint2.SetDrawableY(b);
             }

        }

    }
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
