#ifndef FACE3D_H
#define FACE3D_H
#include "point.h"
namespace Entities
{
class Face3d : public Entity
{
public:
    Face3d();
    Face3d(const Point&p1,const Point&p2,const Point&p3,const Point&p4,double thickNess);
    Face3d(const Point pts[4],double thickNess);
    Face3d(const Face3d& face3d);
    ~Face3d();
private:
    /*! Thickness */
    double m_thickness;
    /*! Points */
    Point m_pts[4];
public:
    virtual EntityType GetType(){return EntityType::Face3dType;}
    virtual void Draw(QPainter& painter);
    virtual Entity* Clone();
    virtual void Transform(double*params,int size=9);
    virtual void Scale(double ratio);
    virtual void Transfer(double dx,double dy,double dz);
    virtual void Rotate(double angle,double cx,double cy,double cz);
    virtual const std::string  ToString(){return "Face3d";}
    virtual void CorrectCoord(double bx,
                              double by,
                              double bz,
                              double sx,
                              double sy,
                              double sz,
                              double rotaAngle);
public:
    double GetThickess()const{return m_thickness;}
    const Point * GetPts()const {return m_pts;}
};
}


#endif // FACE3D_H
