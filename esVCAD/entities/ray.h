#ifndef RAY_H
#define RAY_H
#include "xline.h"
namespace Entities
{
class Ray : public XLine
{
public:
    Ray();
    Ray(const Point&basePoint,const Point& dirVector);
    Ray(const Ray& ray);
    ~Ray();
public:
    virtual EntityType GetType(){return EntityType::RayType;}
    virtual void Draw(QPainter& painter);
    virtual Entity* Clone();
    //dxf cad坐标转换为窗口坐标
    virtual void Transform(double*params,int size=9);
    virtual void Scale(double ratio);
    virtual void Transfer(double dx,double dy,double dz);
    virtual void Rotate(double angle,double cx,double cy,double cz);
    virtual const std::string  ToString(){return "Ray";}
    virtual void CorrectCoord(double bx,
                              double by,
                              double bz,
                              double sx,
                              double sy,
                              double sz,
                              double rotaAngle);
private:
    void ExportRay();
};
}
#endif // RAY_H

