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
    m_isUse(false),
    m_bEndBlock(false)
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
    m_bEndBlock=false;
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
    m_isUse=block.IsUse();
    m_bEndBlock=block.IsEndBlock();
    for(int k=0;k<block.GetElementSize();++k)
    {
        m_entities.push_back(block.ElementAt(k)->Clone());
    }
    SetAttributes(block.GetAttributes());
}

Block::~Block()
{
    DELETE_OBJS(m_entities);
}

void Block::Draw(QPainter& painter)
{
    for(int i=0;i<m_entities.size();++i)
    {
        Layer *layer=m_entities[i]->GetLayer();
        //没有图层，直接显示图形
        if(layer==NULL) continue;
        int flags=layer->GetFlags();
        if(!layer->IsOff()
                ||flags==4
                ||flags==0)//图层关闭不显示
        {
            m_entities[i]->Draw(painter);
        }

    }
}

Block* Block::Clone()
{
    Block* block=new Block(*this);
    return block;
}

void Block::Transform(std::vector<Layer*>& layers,double*params,int size)
{
    for(int i=0;i<m_entities.size();++i)
    {
        std::string layerName=m_entities[i]->GetAttributes().layer_name;
        Layer *layer=FindLayerByName(layerName,layers);
        m_entities[i]->SetLayer(layer);
        m_entities[i]->Transform(params,size);
    }
}
Layer*Block::FindLayerByName(std::string& name,std::vector<Layer*>& layers)
{
    for(int i=0;i<layers.size();++i)
    {
        if(layers[i]->GetName()==name)
        {
            return layers[i];
            break;
        }
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

void Block::CorrectCoord()
{
    for(int i=0;i<m_entities.size();++i)
    {
        m_entities[i]->CorrectCoord(m_insertPoint.GetX(),
                                    m_insertPoint.GetY(),
                                    m_insertPoint.GetZ(),
                                    m_scalePoint.GetX(),
                                    m_scalePoint.GetY(),
                                    m_scalePoint.GetZ(),
                                    m_angle);
    }
}

}

