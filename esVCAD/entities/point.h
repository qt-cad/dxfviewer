#ifndef POINT_H
#define POINT_H
#include"entity.h"
namespace Entities
{
class Point:public Entity
{
public:
    Point();
    Point(double x,double y,double z);
    Point(double x,double y,double z,double bulge);
    Point(const Point&pt);
    ~Point();
    Point& operator =(const Point&pt);
    bool operator ==(const Point&pt);
private:
    double m_x;
    double m_y;
    double m_z;
    double m_bulge;//for Vertex
private:
    double m_drawableX;
    double m_drawableY;
    double m_drawableZ;
    double m_ptRadius;//点的半径大小
public:
    virtual EntityType GetType(){return EntityType::PointType;}
    virtual void Draw(QPainter& painter);
    virtual Entity* Clone();
    virtual void Transform(double*params,int size=9);
    virtual void Scale(double ratio);
    virtual void Transfer(double dx,double dy,double dz);
    virtual void Rotate(double angle,double cx,double cy,double cz);
    virtual const std::string  ToString(){return "Point";}
public:
    void SetX(double x){m_x=x;}
    double GetX() const{return m_x;}

    void SetY(double y){m_y=y;}
    double GetY() const{return m_y;}

    void SetZ(double z){m_z=z;}
    double GetZ() const{return m_z;}

    void SetBulge(double bulge){m_bulge=bulge;}
    double GetBulge() const{return m_bulge;}

    void SetRadius(double radius){m_ptRadius=radius;}
    double GetRadius() const{return m_ptRadius;}

    double GetDrawableX() const{return m_drawableX;}

    double GetDrawableY() const{return m_drawableY;}

    double GetDrawableZ() const{return m_drawableZ;}

    void SetDrawableX(double x) { m_drawableX=x;}

    void SetDrawableY(double y) { m_drawableY=y;}

    void SetDrawableZ(double z) { m_drawableZ=z;}

};

}
#endif // POINT_H
