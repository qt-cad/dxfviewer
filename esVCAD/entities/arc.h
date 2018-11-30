#ifndef ARC_H
#define ARC_H
#include "point.h"
namespace Entities
{
class Arc : public Entity
{
public:
    Arc();
    Arc(const Point& center,double radius,double startAngle,double endAngle);
    Arc(const Arc& arc);
    ~Arc();
private:
    //Center of arc.
    Point m_center;
    // Radius of arc.
    double m_radius;
    // Startangle of arc in degrees.
    double m_startAngle;
    // Endangle of arc in degrees.
    double m_endAngle;
private:
    double m_drawableRadius;
public:
    virtual void Draw(QPainter& painter);
    virtual Entity* Clone();
    virtual void Transform(double*params,int size=9);
    virtual void Scale(double ratio);
    virtual void Transfer(double dx,double dy,double dz);
    virtual void Rotate(double angle,double cx,double cy,double cz);
    virtual const std::string  ToString(){return "Arc";}
public:
    void SetCenter(const Point& center){m_center=center;}
    const Point& GetCenter()const{return m_center;}

    void SetRadius(double radius){m_radius=radius;}
    double GetRadius()const{return m_radius;}

    void SetStartAngle(double startAngle){m_startAngle=startAngle;}
    double GetStartAngle()const{return m_startAngle;}

    void SetEndAngle(double endAngle){m_endAngle=endAngle;}
    double GetEndAngle()const{return m_endAngle;}

};
}


#endif // ARC_H
