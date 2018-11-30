#include "ellipse.h"
#define USE_QT_DRAW 0
#define USE_CUSTOM_DRAW 1
namespace Entities
{
Ellipse::Ellipse()
{
    m_drawFlag=0;
    m_rotaAngle=0.0;
    m_ratio=0.0;
    m_startAngle=0.0;
    m_endAngle=0.0;
    m_a=0.0;
    m_b=0.0;
    m_drawableStartAngle=0.0;
    m_drawableEndAngle=0.0;
    m_drawableAngleLen=0.0;
}
Ellipse::Ellipse(const Point & center,const Point & majorPos,double ratio ,double startAngle,double endAngle)
{
    m_center=center;
    m_majorPos=majorPos;
    m_ratio=ratio;
    m_startAngle=startAngle;
    m_endAngle=endAngle;
    m_drawFlag=0;
    m_rotaAngle=0.0;
    m_a=0.0;
    m_b=0.0;
    m_drawableStartAngle=0.0;
    m_drawableEndAngle=0.0;
    m_drawableAngleLen=0.0;
}

Ellipse::Ellipse(const Ellipse& ellipse)
{
    m_center=ellipse.GetCenter();
    m_majorPos=ellipse.GetMajorPos();
    m_ratio=ellipse.GetRatio();
    m_startAngle=ellipse.GetStartAngle();
    m_endAngle=ellipse.GetEndAngle();
    m_drawFlag=ellipse.GetDrawFlag();
    m_rotaAngle=ellipse.GetRotaAngle();
    m_a=ellipse.GetA();
    m_b=ellipse.GetB();
    m_drawableStartAngle=ellipse.GetDrawableStartAngle();
    m_drawableEndAngle=ellipse.GetDrawableEndAngle();
    m_drawableAngleLen=ellipse.GetDrawableAngleLen();
    std::vector<Point*> rotaEllipsePts=ellipse.GetRotaEllipsePts();
    for(int i=0;i<rotaEllipsePts.size();++i)
    {
        m_rotaEllipsePts.push_back(dynamic_cast<Point*>(rotaEllipsePts[i]->Clone()));
    }
    SetAttributes(ellipse.GetAttributes());
}

Ellipse::~Ellipse()
{
    DeleteObjects();
}
void Ellipse::DeleteObjects()
{
    DELETE_OBJS(m_rotaEllipsePts);
}
void Ellipse::Draw(QPainter& painter)
{
    QPen pen;
    pen.setColor(Qt::white);
    pen.setWidth(2);
    pen.setStyle(Qt::SolidLine);
    painter.setPen(pen);
    double centerX=m_center.GetDrawableX();
    double centerY=m_center.GetDrawableY();
    int majorPosXFlag=m_center.GetX()-m_majorPos.GetX();
    if(m_drawFlag==USE_QT_DRAW)//椭圆或者圆弧没有旋转,用qt绘制
    {
        double w=m_a;
        double h=m_b;
        if(majorPosXFlag==0)
        {
            std::swap(w,h);
        }
        QRect outRect(centerX-w,centerY-h,w*2,h*2);
        painter.drawArc(outRect,m_drawableStartAngle,m_drawableAngleLen);

    }
    else if(m_drawFlag==USE_CUSTOM_DRAW)//有旋转角度，自己绘制
    {
        for(int i=0;i<m_rotaEllipsePts.size()-1;++i)
        {
            int x1=round(m_rotaEllipsePts[i]->GetDrawableX());
            int y1=round(m_rotaEllipsePts[i]->GetDrawableY());
            int x2=round(m_rotaEllipsePts[i+1]->GetDrawableX());
            int y2=round(m_rotaEllipsePts[i+1]->GetDrawableY());
            painter.drawLine(x1,y1,x2,y2);
        }
    }



}

void Ellipse::CalAB()
{
    double centerX=m_center.GetDrawableX();
    double centerY=m_center.GetDrawableY();
    double majorX=m_majorPos.GetDrawableX();
    double majorY=m_majorPos.GetDrawableY();
    m_a=sqrt((majorX-centerX)*(majorX-centerX)+(majorY-centerY)*(majorY-centerY));
    m_b=m_a*m_ratio;
}
void Ellipse::ExportEllipse()
{
    //待优化
    DeleteObjects();
    double centerX=m_center.GetDrawableX();
    double centerY=m_center.GetDrawableY();
    double stepAngle=PI/90;
    double cosValue=cos(m_rotaAngle) ;
    double sinValue=sin(m_rotaAngle) ;
    double startAngle=m_drawableStartAngle*PI/2880;
    double endAngle=m_drawableEndAngle*PI/2880;
    for(double angle=startAngle;angle<=endAngle;angle+=stepAngle)
    {
        double x=m_a*cos(angle);
        double y=m_b*sin(angle);
        double newX =x*cosValue-y*sinValue;
        double newY =x*sinValue+y*cosValue;
        Point point;
        point.SetDrawableX(newX+centerX);
        point.SetDrawableY(centerY-newY);
        m_rotaEllipsePts.push_back(dynamic_cast<Point*>(point.Clone()));
    }
    //中点画圆


    //Bresenham


}
Entity* Ellipse::Clone()
{
    Entity* ellipse=new Ellipse(*this);
    return ellipse;
}

void Ellipse::Transform(double*params,int size)
{
    m_center.Transform(params,size);
    m_majorPos.Transform(params,size);

    CalAB();

    int majorPosXFlag=m_majorPos.GetX()-m_center.GetX();
    int majorPosYFlag=m_majorPos.GetY()-m_center.GetY();
    if((majorPosXFlag==0&&majorPosYFlag!=0)
            ||(majorPosXFlag!=0&&majorPosYFlag==0))
    {
        m_drawFlag=USE_QT_DRAW;
        double rotaAngle=0.0;
        if(majorPosXFlag==0&&majorPosYFlag>0)
        {
           rotaAngle=PI*0.5;
        }
        else if(majorPosXFlag==0&&majorPosYFlag<0)
        {
            rotaAngle=PI*1.5;
        }
        else if(majorPosYFlag==0&&majorPosXFlag>0)
        {
            rotaAngle=0.0;
        }
        else if(majorPosYFlag==0&&majorPosXFlag<0)
        {
            rotaAngle=PI;
        }
        m_drawableStartAngle=((m_startAngle+rotaAngle)/PI)*2880;//180*16
        m_drawableEndAngle=((m_endAngle+rotaAngle)/PI)*2880;
        m_drawableAngleLen=m_drawableEndAngle-m_drawableStartAngle;
    }
    else if(majorPosXFlag!=0&&majorPosYFlag!=0)//有旋转
    {
        //计算旋转角度
        double dy=m_majorPos.GetY()-m_center.GetY();
        double dx=m_majorPos.GetX()-m_center.GetX();
        double k=dy/dx;
        m_rotaAngle=atan(k);
        if(dx<0)
        {
            m_rotaAngle=PI+m_rotaAngle;
        }
        else if(dx>0)
        {
            m_rotaAngle=PI*2+m_rotaAngle;
        }
        m_drawableStartAngle=(m_startAngle/PI)*2880;//180*16
        m_drawableEndAngle=(m_endAngle/PI)*2880;
        m_drawableAngleLen=m_drawableEndAngle-m_drawableStartAngle;
        m_drawFlag=USE_CUSTOM_DRAW;
        //产生椭圆上的点
        ExportEllipse();
    }
}
void Ellipse::Scale(double ratio)
{
    m_center.Scale(ratio);
    m_majorPos.Scale(ratio);
    CalAB();
    if(m_drawFlag==USE_CUSTOM_DRAW)
    {
        ExportEllipse();
    }
}

void Ellipse::Transfer(double dx,double dy,double dz)
{
    m_center.Transfer(dx,dy,dz);
    m_majorPos.Transfer(dx,dy,dz);
    CalAB();
    if(m_drawFlag==USE_CUSTOM_DRAW)
    {
        ExportEllipse();
    }
}

void Ellipse::Rotate(double angle,double cx,double cy,double cz)
{

}

}
