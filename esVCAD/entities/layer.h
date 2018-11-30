#ifndef LAYER_H
#define LAYER_H
#include <string>
#include <vector>
#include <entities/entity.h>
namespace Entities
{
class Layer
{
public:
    Layer(const std::string& name,int flags,bool off);
    ~Layer();
private:
    /** Layer name. */
    std::string m_name;
    /** Layer flags. (1 = frozen, 2 = frozen by default, 4 = locked) */
    int m_flags;
    /** Layer is off */
    bool m_off;
    EntityContainer m_entities;
public :
    const std::string & GetName()const {return m_name;}
    int GetFlags(){return m_flags;}
    bool IsOff(){return m_off;}
    void AddBlock(Entity *entity){m_entities.push_back(entity->Clone());}
    const EntityContainer& GetBlocks()const {return m_entities;}
};
}
#endif // LAYER_H
