#ifndef FUNCTIONS
#define FUNCTIONS

#include <cocos2d.h>

template <typename T>
std::string to_string(T value)
{
	std::ostringstream stream;
	stream << value ;
	return stream.str() ;
}
struct unorderedhash
{
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1, T2> & p) const
	{
        unsigned int hash1 = std::hash<T1>{}(p.first);
        unsigned int hash2 = std::hash<T2>{}(p.second);
        return hash1 ^ hash2;  
    }
};
std::string hash(const cocos2d::Data & data);

#endif