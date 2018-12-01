#include "polyline.h"
namespace Entities
{

Polyline::Polyline():
    m_flag(0),
    m_number(0),
    m_m(0),
    m_n(0),
    m_elevation(0)
{

}

Polyline::Polyline(std::vector<Point*>& vertexes,uint m, uint n, int flag,double elevation)
{
    for(int i=0;i<vertexes.size();++i)
    {
        m_vertexes.push_back(dynamic_cast<Point*>(vertexes[i]->Clone()));
    }
    m_flag=flag;
    m_number=vertexes.size();
    m_m=m;
    m_n=n;
    m_elevation=elevation;
}

Polyline::Polyline(uint number,uint m, uint n, int flag,double elevation)
{
    m_flag=flag;
    m_number=number;
    m_m=m;
    m_n=n;
    m_elevation=elevation;
}

Polyline::Polyline(const Polyline& ployline)
{
    m_flag=ployline.m_flag;
    m_number=ployline.m_number;
    m_m=ployline.m_m;
    m_n=ployline.m_n;
    m_elevation=ployline.m_elevation;
    std::vector<Point*> vertexes= ployline.GetVertexes();
    for(int i=0;i<vertexes.size();++i)
    {
        m_vertexes.push_back(dynamic_cast<Point*>(vertexes[i]->Clone()));
    }
    SetAttributes(ployline.GetAttributes());
}

Polyline::~Polyline()
{
    DeleteObjects();
}

void Polyline::Draw(QPainter& painter)
{
    QPen pen;
    pen.setColor(Qt::white);
    pen.setWidth(2);
    pen.setStyle(Qt::SolidLine);
    painter.setPen(pen);
    int ptSize=m_vertexes.size();
    for(int i=0;i<ptSize-1;++i)
    {
        Point *pt1=dynamic_cast<Point *>(m_vertexes[i]);
        Point *pt2=dynamic_cast<Point *>(m_vertexes[i+1]);
        QPoint startPt(pt1->GetDrawableX(),pt1->GetDrawableY());
        QPoint endPt(pt2->GetDrawableX(),pt2->GetDrawableY());
        painter.drawLine(startPt,endPt);
    }
    if(ptSize>2&&m_flag!=0&&m_flag!=8)//8是三维多线段,1是圆环，Point.GetBulge
    {
        Point *pt1=dynamic_cast<Point *>(m_vertexes[0]);
        Point *pt2=dynamic_cast<Point *>(m_vertexes[ptSize-1]);
        QPoint startPt(pt1->GetDrawableX(),pt1->GetDrawableY());
        QPoint endPt(pt2->GetDrawableX(),pt2->GetDrawableY());
        painter.drawLine(startPt,endPt);
    }
}

Entity* Polyline::Clone()
{
    Entity* polyline=new Polyline(*this);
    return polyline;
}

void Polyline::Transform(double*params,int size)
{
    if(size>=4)
    {
        for(int i=0;i<m_vertexes.size();++i)
        {
            Entity *entity=m_vertexes[i];
            entity->Transform(params,4);
        }
    }
}

void Polyline::Scale(double ratio)
{
    for(int i=0;i<m_vertexes.size();++i)
    {
        Entity *entity=m_vertexes[i];
        entity->Scale(ratio);
    }
}

void Polyline::Transfer(double dx,double dy,double dz)
{
    for(int i=0;i<m_vertexes.size();++i)
    {
        Entity *entity=m_vertexes[i];
        entity->Transfer(dx,dy,dz);
    }
}

void Polyline::Rotate(double angle,double cx,double cy,double cz)
{

}
const std::vector<Point*>& Polyline::GetVertexes()const
{
    return m_vertexes;
}

void  Polyline::AddVertex(Point& vertex)
{
    Point *pt=dynamic_cast<Point*>(vertex.Clone());
    m_vertexes.push_back(pt);
}

void Polyline::DeleteObjects()
{
    DELETE_OBJS(m_vertexes);
}
void Polyline:: CorrectCoord(double bx,
                          double by,
                          double bz,
                          double sx,
                          double sy,
                          double sz,
                          double rotaAngle)
{
    for(int i=0;i<m_vertexes.size();++i)
    {
        m_vertexes[i]->CorrectCoord(bx,by,bz,sx,sy,sz,rotaAngle);
    }
}

}
