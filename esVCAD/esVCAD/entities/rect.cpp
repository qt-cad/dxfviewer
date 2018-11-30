#include "rect.h"
namespace Entities
{

Rect::Rect()
{

}

Rect::Rect(const Point &leftTop,double width,double height)
{
    m_leftTop=leftTop;
    m_rightBottom=Point(leftTop.GetX()+width,leftTop.GetY()+height,0.0);
}
Rect::Rect(const Point &leftTop, const Point &rightBottom)
{
    m_leftTop=leftTop;
    m_rightBottom=rightBottom;
}

Rect::Rect(const Rect& rect)
{
    m_leftTop=rect.GetLeftTop();
    m_rightBottom=rect.GetRightBottom();
    SetAttributes(rect.GetAttributes());
}

Rect::~Rect()
{

}

void Rect::Draw(QPainter& painter)
{

}

Entity* Rect::Clone()
{
    Entity* rect =new Rect(*this);
    return rect;
}

void Rect::Transform(double*params,int size)
{

}
void Rect::Scale(double ratio)
{

}

void Rect::Transfer(double dx,double dy,double dz)
{

}

void Rect::Rotate(double angle,double cx,double cy,double cz)
{

}
bool Rect::IsPtInRect(const Point& pt)
{
    int x=pt.GetX();
    int y=pt.GetY();
    if(x>=m_leftTop.GetX()
            &&x<=m_rightBottom.GetX()
            &&y>=m_leftTop.GetY()
            &&y<=m_rightBottom.GetY())
    {
        return true;
    }
    return false;
}

}
