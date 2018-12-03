#include "layer.h"
namespace Entities
{

Layer::Layer(const std::string& name,int flags,bool off)
{
    m_name=name;
    m_flags=flags;
    m_off=off;
}

Layer::~Layer()
{
}

}
