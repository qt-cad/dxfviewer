#ifndef LAYER_H
#define LAYER_H
#include <string>
#include <vector>
namespace Entities
{
class Layer
{
public:
    Layer();
    Layer(const std::string& name,int flags,bool off);
    ~Layer();
    Layer(const Layer &layer);
private:
    /** Layer name. */
    std::string m_name;
    /** Layer flags. (1 = frozen, 2 = frozen by default, 4 = locked) */
    int m_flags;
    /** Layer is off */
    bool m_off;
public :
    const std::string & GetName()const {return m_name;}
    int GetFlags()const{return m_flags;}
    bool IsOff()const{return m_off;}
    Layer* Clone();
public:
    Layer& operator=(const Layer&layer);
};
}
#endif // LAYER_H
