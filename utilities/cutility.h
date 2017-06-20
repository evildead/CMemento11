/*************************************************
 *                                               *
 *   Author: Danilo Carrabino                    *
 *                                               *
 *************************************************/


#ifndef CUTILITY_H
#define CUTILITY_H

#include <memory>

#ifdef __MINGW32__
template<typename T, typename... Ts>
std::unique_ptr<T> make_unique(Ts&&... params)
{
    return std::unique_ptr<T>(new T(std::forward<Ts>(params)...));
}
#endif

class CUtility
{
public:
    CUtility();
};

#endif // CUTILITY_H
