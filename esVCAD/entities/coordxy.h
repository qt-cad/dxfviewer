#ifndef COORDXY_H
#define COORDXY_H
#include "rect.h"
namespace Entities
{
class CoordXY:public Rect
{
public:
    CoordXY();
    ~CoordXY();
    CoordXY(const Point &leftTop,double width,double height);
    CoordXY(const Point &leftTop, const Point &rightBottom);
    CoordXY(const CoordXY& coordXY);
private:
    Point m_origin;//原点
    int m_maxX;
    int m_maxY;
public:
    virtual EntityType GetType(){return EntityType::CoordXYType;}
    virtual void Draw(QPainter& painter);
    virtual Entity* Clone();
    virtual void Transform(double*params,int size=9);
    virtual void Scale(double ratio);
    virtual void Transfer(double dx,double dy,double dz);
    virtual void Rotate(double angle,double cx,double cy,double cz);
    virtual const std::string  ToString(){return "CoordXY";}
    virtual void CorrectCoord(double bx,
                              double by,
                              double bz,
                              double sx,
                              double sy,
                              double sz,
                              double rotaAngle);
};

}

#endif // COORDXY_H
