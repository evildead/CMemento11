/*************************************************
 *                                               *
 *   Author: Danilo Carrabino                    *
 *                                               *
 *************************************************/


#include "cbook.h"
#include <sstream>

using namespace std;

CBook::CBook(string name)
{
    this->name_ = name;
}

void CBook::setName(const std::string &name)
{
    name_ = name;
}

std::unique_ptr<CListable> CBook::clone() const
{
    return make_unique<CBook>(*this);
}

std::string CBook::getType() const
{
    return "BOOK";
}

std::string CBook::getName() const
{
    return this->name_;
}

std::string CBook::toString() const
{
    std::stringstream mySStream;
    mySStream << getType() << ":\n" << getName();

    return mySStream.str();
}
