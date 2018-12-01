#ifndef ELLIPSE_H
#define ELLIPSE_H
#include "point.h"
namespace Entities
{

class Ellipse : public Entity
{
public:
    Ellipse(const Point & center,const Point & majorPos,double ratio ,double startAngle,double endAngle);
    Ellipse();
    Ellipse(const Ellipse& ellipse);
    ~Ellipse();
private:
    //center
    Point m_center;
    //the endpoint of the major axis
    Point m_majorPos;//椭圆时相对于中心点的坐标
    //Ratio of minor axis to major axis
    double m_ratio;
    //Startangle of ellipse in rad
    double m_startAngle;
    //Endangle of ellipse in rad.
    double m_endAngle;
private:
    int m_drawFlag;
    double m_rotaAngle;
    double m_a;//长轴长
    double m_b;//短轴长
    double m_drawableStartAngle;
    double m_drawableEndAngle;
    double m_drawableAngleLen;
    std::vector<Point*> m_rotaEllipsePts;
private:
    void ExportEllipse();
    void CalAB();
    void DeleteObjects();
public:
    virtual void Draw(QPainter& painter);
    virtual Entity* Clone();
    virtual void Transform(double*params,int size=9);
    virtual void Scale(double ratio);
    virtual void Transfer(double dx,double dy,double dz);
    virtual void Rotate(double angle,double cx,double cy,double cz);
    virtual EntityType GetType(){return EntityType::EllipseType;}
    virtual const std::string  ToString(){return "Ellipse";}
    virtual void CorrectCoord(double bx,
                              double by,
                              double bz,
                              double sx,
                              double sy,
                              double sz,
                              double rotaAngle);
public:
    void SetCenter(const Point& center){m_center=center;}
    const Point& GetCenter()const{return m_center;}

    void SetMajorPos(const Point& majorPos){m_majorPos=majorPos;}
    const Point& GetMajorPos()const{return m_majorPos;}

    void SetRatio(double ratio){m_ratio=ratio;}
    double GetRatio()const{return m_ratio;}

    void SetStartAngle(double startAngle){m_startAngle=startAngle;}
    double GetStartAngle()const{return m_startAngle;}

    void SetEndAngle(double endAngle){m_endAngle=endAngle;}
    double GetEndAngle()const{return m_endAngle;}

    double GetRotaAngle()const{return m_rotaAngle;}
    double GetDrawFlag()const{return m_drawFlag;}

    double GetA()const{return m_a;}
    double GetB()const{return m_b;}
    const std::vector<Point*>& GetRotaEllipsePts()const{return m_rotaEllipsePts;}

    double GetDrawableStartAngle()const {return m_drawableStartAngle;}
    double GetDrawableEndAngle()const{return m_drawableEndAngle;}
    double GetDrawableAngleLen()const{return m_drawableAngleLen;}
};

}

#endif // ELLIPSE_H
