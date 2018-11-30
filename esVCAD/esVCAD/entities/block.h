#ifndef BLOCK_H
#define BLOCK_H
#include "point.h"
namespace Entities
{
class Block:public Entity
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

    void SetName(const std::string &name){ m_name=name;}
    void SetInsertPoint(const Point& insertPoint){ m_insertPoint=insertPoint;}
    void SetScalePoint(const Point& scalePoint){ m_scalePoint=scalePoint;}
    void SetAngle(double angle){ m_angle=angle;}

    void SetCols(int cols){ m_cols=cols;}
    void SetRows(int rows){ m_rows=rows;}
    void SetColSp(double colSp){m_colSp=colSp;}
    void SetRowSp(double rowSp){m_rowSp=rowSp;}
    bool IsEmpty(){return m_entities.size()==0;}
    void push_back(Entity* entity){m_entities.push_back(entity);}
public:
    virtual EntityType GetType(){return EntityType::BlockType;}
    virtual void Draw(QPainter& painter);
    virtual Entity* Clone();
    virtual void Transform(double*params,int size=9);
    virtual void Scale(double ratio);
    virtual void Transfer(double dx,double dy,double dz);
    virtual void Rotate(double angle,double cx,double cy,double cz);
    virtual const std::string  ToString(){return "Block";}
};

}

#endif // BLOCK_H
