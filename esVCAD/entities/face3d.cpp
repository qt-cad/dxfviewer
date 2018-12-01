#include "face3d.h"
namespace Entities
{

Face3d::Face3d()
{
 m_thickness=0.0;
}

Face3d::Face3d(const Point&p1,const Point&p2,const Point&p3,const Point&p4,double thickNess)
{
      m_pts[0]=p1;
      m_pts[1]=p2;
      m_pts[2]=p3;
      m_pts[3]=p4;
      m_thickness=thickNess;
}
Face3d::Face3d(const Point pts[4],double thickNess)
{
    m_pts[0]=pts[0];
    m_pts[1]=pts[1];
    m_pts[2]=pts[2];
    m_pts[3]=pts[3];
    m_thickness=thickNess;
}
Face3d::Face3d(const Face3d& face3d)
{
  const Point *pts=face3d.GetPts();
  m_pts[0]=pts[0];
  m_pts[1]=pts[1];
  m_pts[2]=pts[2];
  m_pts[3]=pts[3];
  m_thickness=face3d.GetThickess();
  SetAttributes(face3d.GetAttributes());
}
Face3d::~Face3d()
{

}

void Face3d::Draw(QPainter& painter)
{

}

Entity* Face3d::Clone()
{
    Entity *face3d=new Face3d(*this);
    return face3d;
}

void Face3d::Transform(double*params,int size)
{

}

void Face3d::Scale(double ratio)
{

}

void Face3d::Transfer(double dx,double dy,double dz)
{

}

void Face3d::Rotate(double angle,double cx,double cy,double cz)
{

}
void Face3d:: CorrectCoord(double bx,
                          double by,
                          double bz,
                          double sx,
                          double sy,
                          double sz,
                          double rotaAngle)
{
    for(int i=0;i<4;++i)
    {
        m_pts[i].CorrectCoord(bx,by,bz,sx,sy,sz,rotaAngle);
    }
}

}
