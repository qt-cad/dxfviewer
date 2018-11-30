#include "graphicsframe.h"
#include <QPainter>
#include <math.h>
GraphicsFrame::GraphicsFrame(QWidget *parent):
    QFrame(parent)
{

}

GraphicsFrame::~GraphicsFrame()
{

}

void GraphicsFrame::paintEvent( QPaintEvent* event )
{
    QPainter painter(this);
    //背景黑色
    painter.fillRect(0,0,width(),height(),QBrush(Qt::black));
    if(!m_Image.isNull())
    {
        painter.drawImage(0,0,m_Image);
    }
}
//鼠标事件
void GraphicsFrame::mouseDoubleClickEvent(QMouseEvent *event)
{
      event->ignore();
}

void GraphicsFrame::mouseMoveEvent(QMouseEvent *event)
{
      event->ignore();
}

void GraphicsFrame::mousePressEvent(QMouseEvent *event)
{
    event->ignore();
}

void GraphicsFrame::mouseReleaseEvent(QMouseEvent *event)
{
    event->ignore();
}

void GraphicsFrame::wheelEvent(QWheelEvent*event)
{
    if(event->delta())
    {

    }
    else
    {

    }
}

void GraphicsFrame::ClearWindow(QPainter& painter,int w,int h)
{
    //背景黑色
    //设置反锯齿
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillRect(0,0,w,h,QBrush(Qt::black));
}

void GraphicsFrame::DrawCoordXy(QPainter& painter,int w,int h)
{
    QPen pen;
    pen.setColor(Qt::white);
    pen.setWidth(2);
    pen.setStyle(Qt::SolidLine);
    painter.setPen(pen);
    QRect rect(20,h-30,20,20);
    painter.drawRect(rect);
    int centerX=30;
    int centerY=h-20;
    //draw x coord
    painter.drawLine(centerX,centerY,centerX+100,centerY);
    painter.drawText(centerX+50,centerY+15,"X");
    //draw y coord
    painter.drawLine(centerX,centerY,centerX,centerY-100);
    painter.drawText(15,centerY-50,"Y");

    pen.setColor(Qt::green);
    painter.setPen(pen);
    painter.drawLine(centerX,centerY-100,centerX,-1);
    pen.setColor(Qt::red);
    painter.setPen(pen);
    painter.drawLine(centerX+100,centerY,w+1,centerY);
}
void GraphicsFrame::PaintEntities(EntityContainer & entities)
{
    int width = this->width();
    int height = this->height();
    m_Image=QImage(QSize(width,height),QImage::Format_ARGB32);
    QPainter painter(&m_Image);
    ClearWindow(painter,width,height);
    DrawCoordXy(painter,width,height);
    for(int i=0;i<entities.size();++i)
    {
        entities[i]->Draw(painter);
    }
    this->update();
}
