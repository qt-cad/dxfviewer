#ifndef ENTITY_H
#define ENTITY_H
#include<string>
#include<vector>
#include<QPainter>
namespace Entities
{
class Entity;
typedef std::vector<Entities::Entity*> EntityContainer;

#define DELETE_OBJS(entities)  \
    for(int i=0;i<entities.size();++i)\
    {                          \
        if(entities[i])        \
        {                      \
            delete entities[i];\
            entities[i]=NULL;  \
        }                      \
    }                          \
    entities.clear();

//图元类型
enum EntityType
{
    BaseType,
    PointType,
    LineType,
    CircleType,
    EllipseType,
    ArcType,
    RectType,
    SplineType,
    PolylineType,
    XLineType,
    RayType,
    CoordXYType,
    Face3dType,
    BlockType,
    Total

};
//图元属性
//绘制状态
enum DrawState
{
    Normal,
    Drawing,
    Select,
    Hover
};
typedef uchar byte;
typedef  unsigned int uint;
#define PI 3.141592653589793
struct Attributes
{
    Attributes():layer_name(""),
        layer_block_color_flag(-1),
        color(-1),
        layer_block_color_width(-1),
        line_width(0),
        line_type("")
    {}
    std::string layer_name;//图层名
    byte layer_block_color_flag;//判断是layer、block,还是颜色值
    int color;
    byte layer_block_color_width;//判断是layer、block、default,还是width
    int line_width;
    std::string line_type;//线型
};
//图元基类
class Entity
{
public:
    Entity(){}
    virtual ~Entity(){}
public:
    virtual EntityType GetType(){return EntityType::BaseType;}
    virtual void Draw(QPainter& painter){}
    virtual Entity* Clone(){ Entity *entity=new Entity;entity->SetAttributes(m_attributes);return entity;}
    virtual void Transform(double*params,int size=9){}
    virtual void Scale(double ratio){}
    virtual void Transfer(double dx,double dy,double dz){}
    virtual void Rotate(double angle,double cx,double cy,double cz){}
    virtual bool IsPickUp(double x,double y,double z){return false;}
    virtual const std::string  ToString(){return "BaseEntity";}
    const Attributes& GetAttributes() const {return m_attributes;}
    void SetAttributes(const Attributes& attributes){
        m_attributes.layer_name=attributes.layer_name;
        m_attributes.layer_block_color_flag=attributes.layer_block_color_flag;
        m_attributes.color=attributes.color;
        m_attributes.layer_block_color_width=attributes.layer_block_color_width;
        m_attributes.line_width=attributes.line_width;
        m_attributes.line_type=attributes.line_type;
    }
    virtual const DrawState  GetDrawState()const{return m_drawState;}
    virtual void SetDrawState(DrawState drawState){m_drawState= drawState;}
protected:
    Attributes  m_attributes;
    DrawState  m_drawState;
};

}
#endif // ENTITY_H
