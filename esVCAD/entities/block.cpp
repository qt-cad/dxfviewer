#include "block.h"
namespace Entities
{

Block::Block():
    m_name(""),
    m_angle(0.0),
    m_cols(0),
    m_rows(0),
    m_colSp(0.0),
    m_rowSp(0.0),
    m_isUse(false)
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
    m_isUse=false;
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
    m_isUse=false;
    for(int k=0;k<block.GetElementSize();++k)
    {
        m_entities.push_back(block.ElementAt(k)->Clone());
    }
    SetAttributes(block.GetAttributes());
}

Block::~Block()
{
    for(int k=0;k<m_entities.size();++k)
    {
        delete m_entities[k];
        m_entities[k]=NULL;
    }
    m_entities.clear();
}

void Block::Draw(QPainter& painter)
{
    for(int i=0;i<m_entities.size();++i)
    {
          m_entities[i]->Draw(painter);
    }
}

Block* Block::Clone()
{
    Block* block=new Block(*this);
    return block;
}

void Block::Transform(double*params,int size)
{
    m_scalePoint.Transform(params,size);
    for(int i=0;i<m_entities.size();++i)
    {
          m_entities[i]->Transform(params,size);
    }
}

void Block::Scale(double ratio)
{
    for(int i=0;i<m_entities.size();++i)
    {
          m_entities[i]->Scale(ratio);
    }
}

void Block::Transfer(double dx,double dy,double dz)
{
    for(int i=0;i<m_entities.size();++i)
    {
          m_entities[i]->Transfer(dx,dy,dz);
    }
}

void Block::Rotate(double angle,double cx,double cy,double cz)
{

}

}

