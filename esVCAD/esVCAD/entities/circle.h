#ifndef CIRCLE_H
#define CIRCLE_H
#include "point.h"
namespace Entities
{
class Circle : public Entity
{
private:
    Point m_center;
    double m_radius;
private:
    double m_drawableRadius;
public:
    Circle();
    Circle(const Point &center,double radius);
    Circle(const Circle &circle);
    ~Circle();
public:
    virtual EntityType GetType(){return EntityType::CircleType;}
    virtual void Draw(QPainter& painter);
    virtual Entity* Clone();
    virtual void Transform(double*params,int size=9);
    virtual void Scale(double ratio);
    virtual void Transfer(double dx,double dy,double dz);
    virtual void Rotate(double angle,double cx,double cy,double cz);
    virtual const std::string  ToString(){return "Circle";}
public:
    void SetCenter(Point& point){m_center=point;}
    const Point& GetCenter(){return m_center;}

    void SetRadius(double radius){m_radius=radius;}
    double GetRadius()const {return m_radius;}

    double GetDrawableRadius()const {return m_drawableRadius;}
};

}

#endif // CIRCLE_H
