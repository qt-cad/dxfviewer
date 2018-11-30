#ifndef POLYLINE_H
#define POLYLINE_H
#include "point.h"
#include <vector>
namespace Entities
{
class Polyline : public Entity
{
private:
    std::vector<Point*> m_vertexes;
    int m_flag;//折线段是否闭合
    uint m_number;    /*! Number of vertices in this polyline. */
    uint m_m;    /*! Number of vertices in m direction if polyline is a polygon mesh. */
    uint m_n;    /*! Number of vertices in n direction if polyline is a polygon mesh. */
    double m_elevation;  /*! elevation of the polyline. */
public:
    Polyline(std::vector<Point*>& vertexes,uint m=0, uint n=0, int flag=0,double elevation=0.0);
    Polyline(uint number,uint m, uint n, int flag,double elevation=0.0);
    Polyline();
    Polyline(const Polyline& ployline);
    ~Polyline();
public:
    virtual EntityType GetType(){return EntityType::PolylineType;}
    virtual void Draw(QPainter& painter);
    virtual Entity* Clone();
    virtual void Transform(double*params,int size=9);
    virtual void Scale(double ratio);
    virtual void Transfer(double dx,double dy,double dz);
    virtual void Rotate(double angle,double cx,double cy,double cz);
    virtual const std::string  ToString(){return "Polyline";}
public:
    const std::vector<Point*>& GetVertexes() const;
    void  AddVertex(Point& vertex);
    uint GetM(){return m_m;}
    uint GetN(){return m_n;}
    int GetFlag(){return m_flag;}
    void SetFlag(int flag){m_flag=flag;}
    uint GetNumber(){return m_number;}
    double GetElevation(){return m_elevation;}
private:
    void DeleteObjects();
};
}
#endif // POLYLINE_H
