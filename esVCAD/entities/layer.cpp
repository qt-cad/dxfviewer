#include "layer.h"
namespace Entities
{

Layer::Layer()
{

}
Layer::Layer(const std::string& name,int flags,bool off)
{
    m_name=name;
    m_flags=flags;
    m_off=off;
}

Layer::~Layer()
{
}

Layer::Layer(const Layer &layer)
{
    m_name=layer.GetName();
    m_flags=layer.GetFlags();
    m_off=layer.IsOff();
}

Layer& Layer::operator=(const Layer&layer)
{
    if(&layer!=this)
    {
        m_name=layer.GetName();
        m_flags=layer.GetFlags();
        m_off=layer.IsOff();
    }
    return *this;
}

Layer* Layer::Clone()
{
    Layer *layer=new Layer(*this);
    return layer;
}

}
