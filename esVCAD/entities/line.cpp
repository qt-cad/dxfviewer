#include "line.h"
#include <QPen>
#include <QBrush>
namespace Entities
{

Line::Line()
{
}

Line::Line(const Point&p1,const Point&p2)
{
    m_startPoint=p1;
    m_endPoint=p2;
}

Line::Line(const Line& line)
{
    m_startPoint=line.GetStartPoint();
    m_endPoint=line.GetEndPoint();
    SetAttributes(line.GetAttributes());
}

Line::~Line()
{

}

void Line::Draw(QPainter& painter)
{

       QPen pen;
       pen.setColor(Qt::white);
       pen.setWidth(2);
       pen.setStyle(Qt::SolidLine);
       painter.setPen(pen);
       QPoint p1(round(m_startPoint.GetDrawableX()),round(m_startPoint.GetDrawableY()));
       QPoint p2(m_endPoint.GetDrawableX(),m_endPoint.GetDrawableY());
       painter.drawLine(p1,p2);
}

Entity* Line::Clone()
{
    Entity* line=new Line(*this);
    return line;
}

void Line::Transform(double*params,int size)
{
      m_startPoint.Transform(params,size);
      m_endPoint.Transform(params,size);
}

void Line::Scale(double ratio)
{
    m_startPoint.Scale(ratio);
    m_endPoint.Scale(ratio);
}

void Line::Transfer(double dx,double dy,double dz)
{
    m_startPoint.Transfer(dx,dy,dz);
    m_endPoint.Transfer(dx,dy,dz);
}

void Line::Rotate(double angle,double cx,double cy,double cz)
{

}

void  Line::mouseDoubleClickEvent(QMouseEvent *event)
{

}

void Line::mouseMoveEvent(QMouseEvent *event)
{

}

void Line::mousePressEvent(QMouseEvent *event)
{

}

void Line::mouseReleaseEvent(QMouseEvent *event)
{

}

void Line::dragEnterEvent(QDragEnterEvent *event)
{

}

void Line::dragMoveEvent(QDragMoveEvent *event)
{

}

void Line::dragLeaveEvent(QDragLeaveEvent *event)
{

}

void Line::dropEvent(QDropEvent *event)
{

}

void Line:: wheelEvent(QWheelEvent*event)
{

}

}
