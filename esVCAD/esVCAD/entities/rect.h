#ifndef RECT_H
#define RECT_H
#include "point.h"
namespace Entities
{
class Rect : public Entity
{
public:
    Rect();
    Rect(const Point &leftTop,double width,double height);
    Rect(const Point &leftTop, const Point &rightBottom);
    Rect(const Rect& rect);
    ~Rect();
protected:
    Point m_leftTop;
    Point m_rightBottom;
public:
    virtual EntityType GetType(){return EntityType::RectType;}
    virtual void Draw(QPainter& painter);
    virtual Entity* Clone();
    virtual void Transform(double*params,int size=9);
    virtual void Scale(double ratio);
    virtual void Transfer(double dx,double dy,double dz);
    virtual void Rotate(double angle,double cx,double cy,double cz);
    virtual const std::string  ToString(){return "Rect";}
public:
    const Point &GetLeftTop()const{return m_leftTop;}
    const Point &GetRightBottom()const{return m_rightBottom;}
    double GetWidth()const{return (m_rightBottom.GetX()-m_leftTop.GetX());}
    double GetHeihgt()const{return (m_rightBottom.GetY()-m_leftTop.GetY());}
    bool IsPtInRect(const Point& pt);
};

}
#endif // RECT_H
