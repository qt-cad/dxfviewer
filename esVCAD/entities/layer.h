#ifndef LAYER_H
#define LAYER_H
#include <string>
#include <vector>
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
public :
    const std::string & GetName()const {return m_name;}
    int GetFlags(){return m_flags;}
    bool IsOff(){return m_off;}
};
}
#endif // LAYER_H
