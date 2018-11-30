#ifndef XLINE_H
#define XLINE_H
#include "point.h"
namespace Entities
{

class XLine : public Entity
{
public:
    XLine();
    XLine(const Point&basePoint,const Point& dirVector);
    XLine(const XLine& xLine);
    ~XLine();
protected:
    Point m_basePoint;
    Point m_dirVector;//直线方向
private:
    Point m_drawablePoint1;
    Point m_drawablePoint2;
    double m_xMax;
    double m_yMax;
public:
    const Point &GetBasePoint()const{return m_basePoint;}
    const Point &GetDirVector()const{return m_dirVector;}

    const Point &GetDrawablePoint1()const{return m_drawablePoint1;}
    const Point &GetDrawablePoint2()const{return m_drawablePoint2;}
    double GetXMax()const {return m_xMax;}
    double GetYMax()const {return m_yMax;}
public:
    virtual EntityType GetType(){return EntityType::XLineType;}
    virtual void Draw(QPainter& painter);
    virtual Entity* Clone();
    //dxf cad坐标转换为窗口坐标
    virtual void Transform(double*params,int size=9);
    virtual void Scale(double ratio);
    virtual void Transfer(double dx,double dy,double dz);
    virtual void Rotate(double angle,double cx,double cy,double cz);
    virtual const std::string  ToString(){return "XLine";}
private:
    void ExportXLine();
};

}
#endif // XLINE_H
