/*
 * @file Dxf_CreationClass.cpp
 */

#include "dxf_creationClass.h"
#include <iostream>
#include <entities/point.h>
#include <entities/line.h>
#include <entities/circle.h>
#include <entities/polyline.h>
#include <entities/ellipse.h>
#include <entities/arc.h>
#include <entities/spline.h>
#include <entities/xline.h>
#include <entities/ray.h>
#include <entities/face3d.h>
#include <entities/block.h>
#include <qdebug.h>

Dxf_CreationClass::Dxf_CreationClass()
{

}

Dxf_CreationClass::~Dxf_CreationClass()
{
    for(int i=0;i<m_blocks.size();++i)
    {
        if(m_blocks[i])
        {
            delete m_blocks[i];
            m_blocks[i]=NULL;
        }
    }
}
//处理组码
void Dxf_CreationClass::processCodeValuePair(unsigned int code, const std::string& value)
{
    static bool bFindExtMinOrMax=false;
    if(value=="$EXTMIN"||value=="$EXTMAX")
    {
        bFindExtMinOrMax=true;
        return;
    }
    if(bFindExtMinOrMax)
    {
        if(m_extMinAndMax.size()<6)
        {
            m_extMinAndMax.push_back(atof(value.c_str()));
        }
        else
        {
            bFindExtMinOrMax=false;
        }
    }
}

void Dxf_CreationClass::endSection()
{

}
//图层数据
void Dxf_CreationClass::addLayer(const DL_LayerData& data) {
    //printf("LAYER: %s flags: %d\n", data.name.c_str(), data.flags);
    GetAttributes();
}

//点数据
void Dxf_CreationClass::addPoint(const DL_PointData& data)
{

    int size=m_blocks.size();
    if(size>0)
    {
        Entity * pt=new Point(data.x,data.y,data.z);
        pt->SetAttributes(GetAttributes());
        Block* block=m_blocks[size-1];
        block->push_back(pt);

    }


}

//线数据
void Dxf_CreationClass::addLine(const DL_LineData& data)
{
    int size=m_blocks.size();
    if(size>0)
    {
        Point p1(data.x1, data.y1, data.z1);
        Point p2(data.x2, data.y2, data.z2);
        Entity * line=new Line(p1,p2);
        line->SetAttributes(GetAttributes());
        Block* block=m_blocks[size-1];
        block->push_back(line);

    }
}

//圆弧数据
void Dxf_CreationClass::addArc(const DL_ArcData& data)
{
    int size=m_blocks.size();
    if(size>0)
    {
        Point center(data.cx, data.cy, data.cz);
        Entity * arc=new Arc(center,data.radius,data.angle1,data.angle2);
        arc->SetAttributes(GetAttributes());
        Block* block=m_blocks[size-1];
        block->push_back(arc);

    }
}

//圆数据
void Dxf_CreationClass::addCircle(const DL_CircleData& data)
{
    int size=m_blocks.size();
    if(size>0)
    {
        Point center(data.cx, data.cy, data.cz);
        Entity * circle=new Circle(center,data.radius);
        circle->SetAttributes(GetAttributes());
        Block* block=m_blocks[size-1];
        block->push_back(circle);

    }
}

//椭圆数据
void Dxf_CreationClass::addEllipse(const DL_EllipseData& data)
{
    int size=m_blocks.size();
    if(size>0)
    {
        Point center(data.cx, data.cy, data.cz);
        Point majorPos(data.mx+data.cx, data.my+data.cy, data.mz+data.cz);
        Entity * ellipse=new Ellipse(center,majorPos,data.ratio,data.angle1,data.angle2);
        ellipse->SetAttributes(GetAttributes());
        Block* block=m_blocks[size-1];
        block->push_back(ellipse);

    }
}

//折线段数据
void Dxf_CreationClass::addPolyline(const DL_PolylineData& data)
{  
    int size=m_blocks.size();
    if(size>0)
    {
        Entity *polyline=new Polyline(data.number,
                                      data.m,
                                      data.n,
                                      data.flags,
                                      data.elevation);
        polyline->SetAttributes(GetAttributes());
        Block* block=m_blocks[size-1];
        block->push_back(polyline);

    }
}


//顶点数据
void Dxf_CreationClass::addVertex(const DL_VertexData& data)
{
    int size=m_blocks.size();
    if(size>0)
    {
        Block* block=m_blocks[size-1];
        if(!block->IsEmpty())
        {
            Entity* elemEntity=block->ElementAt(block->GetElementSize()-1);
            if(elemEntity->GetType()==EntityType::PolylineType)
            {
                Polyline *polyline=dynamic_cast<Polyline *>(elemEntity);
                Point vertex(data.x, data.y, data.z, data.bulge);
                vertex.SetAttributes(GetAttributes());
                polyline->AddVertex(vertex);
            }
        }

    }
}

//3d面数据
void Dxf_CreationClass::add3dFace(const DL_3dFaceData& data)
{
    int size=m_blocks.size();
    if(size>0)
    {
        Point pts[4];
        for (int i=0; i<4; i++) {
            pts[i].SetX(data.x[i]);
            pts[i].SetY(data.y[i]);
            pts[i].SetZ(data.z[i]);
        }
        Entity *face3d=new Face3d(pts,data.thickness);
        face3d->SetAttributes(GetAttributes());
        Block* block=m_blocks[size-1];
        block->push_back(face3d);
    }

}
//无限直线
void Dxf_CreationClass::addXLine(const DL_XLineData& data)
{
    int size=m_blocks.size();
    if(size>0)
    {
        Entity *xLine=new XLine(Point(data.bx,data.by,data.bz),
                                Point(data.dx,data.dy,data.dz));
        xLine->SetAttributes(GetAttributes());
        Block* block=m_blocks[size-1];
        block->push_back(xLine);
    }
}
//射线
void Dxf_CreationClass::addRay(const DL_RayData& data)
{ 
    int size=m_blocks.size();
    if(size>0)
    {
        Entity *ray=new Ray(Point(data.bx,data.by,data.bz),
                            Point(data.dx,data.dy,data.dz));
        ray->SetAttributes(GetAttributes());
        Block* block=m_blocks[size-1];
        block->push_back(ray);
    }
}
//样条曲线
void Dxf_CreationClass::addSpline(const DL_SplineData& data)
{ 
    int size=m_blocks.size();
    if(size>0)
    {
        Point startPoint(data.tangentStartX,data.tangentStartY,data.tangentStartZ);
        Point endPoint(data.tangentEndX,data.tangentEndY,data.tangentEndZ);
        Entity * spline=new Spline(data.degree,
                                   data.nKnots,
                                   data.nControl,
                                   data.nFit,
                                   data.flags,
                                   startPoint,
                                   endPoint);
        spline->SetAttributes(GetAttributes());
        Block* block=m_blocks[size-1];
        block->push_back(spline);
    }
}
//控制点
void Dxf_CreationClass::addControlPoint(const DL_ControlPointData& data)
{
    int size=m_blocks.size();
    if(size>0)
    {
        Block* block=m_blocks[size-1];
        if(!block->IsEmpty())
        {
            Entity* elemEntity=block->ElementAt(block->GetElementSize()-1);
            if(elemEntity->GetType()==EntityType::SplineType)
            {
                Spline *spline=dynamic_cast<Spline *>(elemEntity);
                Point controlPt(data.x, data.y, data.z, data.w);
                controlPt.SetAttributes(GetAttributes());
                spline->AddControlPts(dynamic_cast<Point*>(controlPt.Clone()));
            }
        }


    }
}
//拟合点
void Dxf_CreationClass::addFitPoint(const DL_FitPointData& data)
{
    int size=m_blocks.size();
    if(size>0)
    {
        Block* block=m_blocks[size-1];
        if(!block->IsEmpty())
        {
            Entity* elemEntity=block->ElementAt(block->GetElementSize()-1);
            if(elemEntity->GetType()==EntityType::SplineType)
            {
                Spline *spline=dynamic_cast<Spline*>(elemEntity);
                Point fitPt(data.x, data.y, data.z);
                fitPt.SetAttributes(GetAttributes());
                spline->AddFitPts(dynamic_cast<Point*>(fitPt.Clone()));
            }
        }


    }
}
//节点矢量
void Dxf_CreationClass::addKnot(const DL_KnotData& data)
{
    int size=m_blocks.size();
    if(size>0)
    {
        Block* block=m_blocks[size-1];
        if(!block->IsEmpty())
        {
            Entity* elemEntity=block->ElementAt(block->GetElementSize()-1);
            if(elemEntity->GetType()==EntityType::SplineType)
            {
                Spline *spline=dynamic_cast<Spline*>(elemEntity);
                spline->AddKnots(data.k);
            }
        }

    }
}

void Dxf_CreationClass::endEntity()
{

}
void Dxf_CreationClass::addInsert(const DL_InsertData& data)
{
    int size=m_blocks.size();
    if(size>0)
    {
        Block* block=m_blocks[size-1];
        block->SetName(data.name);
        block->SetInsertPoint(Point(data.ipx,data.ipy,data.ipz));
        block->SetAngle(data.angle);
        block->SetScalePoint(Point(data.sx,data.sy,data.sz));
        block->SetCols(data.cols);
        block->SetRows(data.rows);
        block->SetColSp(data.colSp);
        block->SetRowSp(data.rowSp);
        block->SetIsUse(true);
        block->SetAttributes(GetAttributes());

    }

}
void Dxf_CreationClass::addBlock(const DL_BlockData& data)
{
    Block *block=new Block();
    block->SetName(data.name);
    block->SetInsertPoint(Point(data.bpx,data.bpy,data.bpz));
    block->SetAttributes(GetAttributes());
    m_blocks.push_back(block);
}

void Dxf_CreationClass::endBlock()
{

}
Entities::Attributes& Dxf_CreationClass::GetAttributes() {
    m_attributes.layer_name=attributes.getLayer();//QString::fromStdString(attributes.getLayer());
    if (attributes.getColor()==256)
    {
        m_attributes.layer_block_color_flag=0;
        //printf("BYLAYER");
    }
    else if (attributes.getColor()==0)
    {
        m_attributes.layer_block_color_flag=1;
        //printf("BYBLOCK");
    } else
    {
        //printf("%d", attributes.getColor());
        m_attributes.layer_block_color_flag=2;
        m_attributes.color=attributes.getColor();
    }

    if (attributes.getWidth()==-1)
    {
        m_attributes.layer_block_color_width=0;
        //printf("BYLAYER");
    }
    else if (attributes.getWidth()==-2)
    {
        //printf("BYBLOCK");
        m_attributes.layer_block_color_width=1;
    }
    else if (attributes.getWidth()==-3)
    {
        //printf("DEFAULT");
        m_attributes.layer_block_color_width=2;
    } else
    {
        m_attributes.layer_block_color_width=3;
        //printf("%d", attributes.getWidth());
        m_attributes.line_width=attributes.getWidth();
    }
    //printf(" Type: %s\n", attributes.getLinetype().c_str());
    m_attributes.line_type=attributes.getLinetype();//QString::fromStdString(attributes.getLinetype());
    return m_attributes;
}
Rect  Dxf_CreationClass::GetCoordRange()
{
    if(m_extMinAndMax.size()==6)
    {
        Point leftTop(m_extMinAndMax[0],m_extMinAndMax[1],m_extMinAndMax[2]);
        Point rightBottom(m_extMinAndMax[3],m_extMinAndMax[4],m_extMinAndMax[5]);
        return Rect(leftTop,rightBottom);
    }
}

// EOF
