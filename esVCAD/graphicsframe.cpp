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
void GraphicsFrame::PaintEntities(std::vector<Block*>& blocks)
{
    int width = this->width();
    int height = this->height();
    m_Image=QImage(QSize(width,height),QImage::Format_ARGB32);
    QPainter painter(&m_Image);
    int count=blocks.size();
    if(count>0)
    {
        //设置反锯齿
        painter.setRenderHint(QPainter::Antialiasing, true);
       //背景黑色,擦除图形
        painter.fillRect(0,0,width,height,QBrush(Qt::black));
        //绘制图元
        for(int i=0;i<blocks.size();++i)
        {
            blocks[i]->Draw(painter);
        }
        this->update();
    }

}
