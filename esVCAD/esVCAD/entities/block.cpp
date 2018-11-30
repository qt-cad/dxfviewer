#include "block.h"
namespace Entities
{

Block::Block()
{

}
Block::Block(const std::string&name,
             const Point& insertPoint,
             const Point&scalePoint,
             double angle,
             int cols,
             int rows,
             double colSp,
             double rowSp)
{
    m_name=name;
    m_insertPoint=insertPoint;
    m_scalePoint=scalePoint;
    m_angle=angle;
    m_cols=cols;
    m_rows=rows;
    m_colSp=colSp;
    m_rowSp=rowSp;
}

Block::Block(const Block& block)
{
    m_name=block.GetName();
    m_insertPoint=block.GetInsertPoint();
    m_scalePoint=block.GetScalePoint();
    m_angle=block.GetAngle();
    m_cols=block.GetCols();
    m_rows=block.GetRows();
    m_colSp=block.GetColSp();
    m_rowSp=block.GetRowSp();
    SetAttributes(block.GetAttributes());
}

Block::~Block()
{

}

void Block::Draw(QPainter& painter)
{

}

Entity* Block::Clone()
{
    Entity* block=new Block(*this);
    return block;
}

void Block::Transform(double*params,int size)
{
    m_scalePoint.Transform(params,size);
    for(int i=0;i<m_entities.size();++i)
    {

    }
}

void Block::Scale(double ratio)
{

}

void Block::Transfer(double dx,double dy,double dz)
{

}

void Block::Rotate(double angle,double cx,double cy,double cz)
{

}

}

