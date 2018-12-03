#include "spline.h"
#define CONTROL_TYPE 8
#define FIT_TYPE   1064
#include "include/tinyspline/tinysplinecpp.h"
namespace Entities
{
Spline::Spline(uint degree,
               uint nKnots,
               uint nControl,
               uint nFit,
               int flags,
               const Point&startPoint,
               const Point&endPoint)
{
    m_degree=degree;
    m_nKnots=nKnots;
    m_nControl=nControl;
    m_nFit=nFit;
    m_flags=flags;
    m_tangentStartPoint=startPoint;
    m_tangentEndPoint=endPoint;
}

Spline::Spline(const Spline& spline)
{
    m_degree=spline.m_degree;
    m_nKnots=spline.m_nKnots;
    m_nControl=spline.m_nControl;
    m_nFit=spline.m_nFit;
    m_flags=spline.m_flags;
    m_tangentStartPoint=spline.m_tangentStartPoint;
    m_tangentEndPoint=spline.m_tangentEndPoint;
    std::vector<Point*> _controlPts=spline.GetControlPts();
    std::vector<Point*> _fitPts=spline.GetFitPts();
    std::vector<double> _knotPts=spline.GetKnotPts();
    std::vector<Point*> _drawablePoints=spline.GetDrawablePoints();
    for(int i=0;i<_controlPts.size();++i)
    {
        m_controlPts.push_back(dynamic_cast<Point*>(_controlPts[i]->Clone()));
    }
    for(int i=0;i<_fitPts.size();++i)
    {
        m_fitPts.push_back(dynamic_cast<Point*>(_fitPts[i]->Clone()));
    }
    for(int i=0;i<_knotPts.size();++i)
    {
        m_knotPts.push_back(_knotPts[i]);
    }
    for(int i=0;i<_drawablePoints.size();++i)
    {
        m_drawabelPoints.push_back(dynamic_cast<Point*>(_drawablePoints[i]->Clone()));
    }

    SetAttributes(spline.GetAttributes());
}
Spline::~Spline()
{
    DeleteObjects();
    DeleteDrawableObjects();
}

void Spline::Draw(QPainter& painter)
{
    QPen pen;
    pen.setColor(Qt::white);
    pen.setWidth(2);
    pen.setStyle(Qt::SolidLine);
    painter.setPen(pen);
    for(int i=0;i<m_drawabelPoints.size()-1;i++)
    {
        painter.drawLine(m_drawabelPoints[i]->GetDrawableX(),m_drawabelPoints[i]->GetDrawableY(),
                         m_drawabelPoints[i+1]->GetDrawableX(),m_drawabelPoints[i+1]->GetDrawableY());
    }
}

Entity* Spline::Clone()
{
    Entity *spline=new Spline(*this);
    return spline;
}

void Spline::Transform(double*params,int size)
{
    for(int i=0;i<m_controlPts.size();++i)
    {
        Entity *entity=m_controlPts[i];
        entity->Transform(params,4);
    }
    ExportSpline();
}
void Spline::Scale(double ratio)
{
    for(int i=0;i<m_controlPts.size();++i)
    {
        Entity *entity=m_controlPts[i];
        entity->Scale(ratio);
    }
    ExportSpline();
}

void Spline::Transfer(double dx,double dy,double dz)
{
    for(int i=0;i<m_controlPts.size();++i)
    {
        Entity *entity=m_controlPts[i];
        entity->Transfer(dx,dy,dz);
    }
    ExportSpline();
}

void Spline::Rotate(double angle,double cx,double cy,double cz)
{

}
void Spline::AddKnots(double k)
{
    m_knotPts.push_back(k);
}
void Spline::AddControlPts(Point* pt)
{
    m_controlPts.push_back(pt);
}
void Spline::AddFitPts(Point* pt)
{
    m_fitPts.push_back(pt);
}
void Spline::DeleteObjects()
{
    DELETE_OBJS(m_controlPts);
    DELETE_OBJS(m_fitPts);
    m_knotPts.clear();
}
void Spline:: DeleteDrawableObjects()
{
    DELETE_OBJS(m_drawabelPoints);
}

void Spline::CalXMinMax(std::vector<Point*>&controlPts,double &xMin,double&xMax)
{
    std::vector<double> vx;
    for(int i=0;i<controlPts.size();++i)
    {
        vx.push_back(controlPts[i]->GetDrawableX());
    }
    xMin=*std::min_element(vx.begin(),vx.end());
    xMax=*std::max_element(vx.begin(),vx.end());
}
void Spline::ExportSpline()
{
    DeleteDrawableObjects();
    if(m_nControl==2)
    {
        Point *pt0=new Point;
        Point *pt1=new Point;
        pt0->SetDrawableX(m_controlPts[0]->GetDrawableX());
        pt0->SetDrawableY(m_controlPts[0]->GetDrawableY());
        pt1->SetDrawableX(m_controlPts[1]->GetDrawableX());
        pt1->SetDrawableY(m_controlPts[1]->GetDrawableY());
        m_drawabelPoints.push_back(pt0);
        m_drawabelPoints.push_back(pt1);
    }
    else if(m_nControl>2)//二阶
    {
        tinyspline::BSpline *spline;
        if(m_nControl==3)
        {
            spline=new tinyspline::BSpline(m_nControl,2,2);
        }
        else if(m_nControl>3)
        {
            spline=new tinyspline::BSpline(m_nControl);
        }
        std::vector<tinyspline::real> ctrlpts = spline->controlPoints();
        for(int i=0;i<m_nControl;++i)
        {
            double x=m_controlPts[i]->GetDrawableX();
            double y=m_controlPts[i]->GetDrawableY();
            ctrlpts[2*i]=x;
            ctrlpts[2*i+1]=y;
        }
        spline->setControlPoints(ctrlpts);
        std::vector<tinyspline::real> result;
        double xMin=0.0,xMax=0.0;
        CalXMinMax(m_controlPts,xMin,xMax);
        double u=0;
        double du=1.0/(abs(xMax-xMin))*4;
        double endU=1.0;
        for(;u<=endU;u+=du)
        {
            result = spline->eval(u).result();
            if(result.size()==0)continue;
            Point point;
            point.SetDrawableX(round(result[0]));
            point.SetDrawableY(round(result[1]));
            m_drawabelPoints.push_back(dynamic_cast<Point*>(point.Clone()));
            result.clear();
        }
        delete spline;
        spline=NULL;
    }

}
void Spline:: CorrectCoord(double bx,
                           double by,
                           double bz,
                           double sx,
                           double sy,
                           double sz,
                           double rotaAngle)
{
    for(int i=0;i<m_controlPts.size();++i)
    {
        m_controlPts[i]->CorrectCoord(bx,by,bz,sx,sy,sz,rotaAngle);
    }
}

}

