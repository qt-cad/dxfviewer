#ifndef SPLINE_H
#define SPLINE_H
#include "point.h"
namespace Entities
{
class Spline : public Entity
{
public:
    Spline(uint degree,
           uint nKnots,
           uint nControl,
           uint nFit,
           int flags,
           const Point&startPoint,
           const Point&endPoint);
    ~ Spline();
    Spline(const Spline& spline);
private:
    /*! Degree of the spline curve. */
    uint m_degree;

    /*! Number of knots. */
    uint m_nKnots;

    /*! Number of control points. */
    uint m_nControl;

    /*! Number of fit points. */
    uint m_nFit;

    /*! Flags */
    int m_flags;

    //    double m_tangentStartX;
    //    double m_tangentStartY;
    //    double m_tangentStartZ;
    //    double m_tangentEndX;
    //    double m_tangentEndY;
    //    double m_tangentEndZ;
    Point m_tangentStartPoint;
    Point m_tangentEndPoint;
    std::vector<double>m_knotPts;
    std::vector<Point*>m_controlPts;
    std::vector<Point*>m_fitPts;
private:
    std::vector<Point*> m_drawabelPoints;
public:
    virtual EntityType GetType(){return EntityType::SplineType;}
    virtual void Draw(QPainter& painter);
    virtual Entity* Clone();
    virtual void Transform(double*params,int size=9);
    virtual void Scale(double ratio);
    virtual void Transfer(double dx,double dy,double dz);
    virtual void Rotate(double angle,double cx,double cy,double cz);
    virtual const std::string  ToString(){return "Spline";}
    virtual void CorrectCoord(double bx,
                              double by,
                              double bz,
                              double sx,
                              double sy,
                              double sz,
                              double rotaAngle);
public:
    void AddKnots(double k);
    void AddControlPts(Point* pt);
    void AddFitPts(Point* pt);
    const std::vector<Point*>& GetControlPts()const{return m_controlPts;}
    const std::vector<Point*>& GetFitPts()const{return m_fitPts;}
    const std::vector<double>& GetKnotPts()const{return m_knotPts ;}
    const std::vector<Point*>& GetDrawablePoints()const{return m_drawabelPoints;}
private:
    void DeleteObjects();
    void DeleteDrawableObjects();
    void ExportSpline();
    void CalXMinMax(std::vector<Point*>&controlPts,double &xMin,double&xMax);
};

}

#endif // SPLINE_H
