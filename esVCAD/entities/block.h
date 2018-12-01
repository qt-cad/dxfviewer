#ifndef BLOCK_H
#define BLOCK_H
#include "point.h"
namespace Entities
{
class Block
{
public:
    Block();
    Block(const std::string&name,
          const Point& insertPoint,
          const Point&scalePoint,
          double angle,
          int cols,
          int rows,
          double colSp,
          double rowSp);
    Block(const Block& block);
    ~Block();
private:
    std::string m_name;//块名
    Point m_insertPoint;//插入基点
    Point m_scalePoint;//缩放系数
    double m_angle;//旋转角度
    int m_cols;//块数组x索引,未使用
    int m_rows;//块数组y索引,未使用
    double m_colSp;//x边缘间距,未使用
    double m_rowSp;//y边缘间距,未使用
    bool m_isUse;
    Attributes m_attributes;
    bool m_bEndBlock;
private:
    EntityContainer m_entities;
public:
    const std::string &GetName()const{return m_name;}
    const Point& GetInsertPoint()const{return m_insertPoint;}
    const Point& GetScalePoint()const{return m_scalePoint;}
    double GetAngle()const{return m_angle;}

    int GetCols()const{return m_cols;}
    int GetRows()const{return m_rows;}
    double GetColSp()const{return m_colSp;}
    double GetRowSp()const{return m_rowSp;}
    bool IsUse()const{return m_isUse;}
    bool IsEndBlock()const{return m_bEndBlock;}
    const Attributes GetAttributes()const{return m_attributes;}

    void SetName(const std::string &name){ m_name=name;}
    void SetInsertPoint(const Point& insertPoint){ m_insertPoint=insertPoint;}
    void SetScalePoint(const Point& scalePoint){ m_scalePoint=scalePoint;}
    void SetAngle(double angle){ m_angle=angle;}
    void SetIsUse(bool bUse){m_isUse=bUse;}
    void SetIsEndBlock(bool bEndBlock){m_bEndBlock=bEndBlock;}
    void SetCols(int cols){ m_cols=cols;}
    void SetRows(int rows){ m_rows=rows;}
    void SetColSp(double colSp){m_colSp=colSp;}
    void SetRowSp(double rowSp){m_rowSp=rowSp;}
    void SetAttributes(const Attributes &attributes){m_attributes=attributes;}
    bool IsEmpty(){return m_entities.size()==0;}
    int  GetElementSize()const{return m_entities.size();}
    Entity* ElementAt(int index)const{return m_entities[index];}
    void push_back(Entity* entity){m_entities.push_back(entity);}
    Entity* operator[](int index){return m_entities[index];}
public:
    void CorrectCoord();//矫正块内图元的坐标，包括偏移，比例和角度
public:
    void Draw(QPainter& painter);
    Block* Clone();
    void Transform(double*params,int size=9);
    void Scale(double ratio);
    void Transfer(double dx,double dy,double dz);
    void Rotate(double angle,double cx,double cy,double cz);
    const std::string  ToString(){return "Block";}
};

}

#endif // BLOCK_H
