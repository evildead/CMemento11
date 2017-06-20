/*************************************************
 *                                               *
 *   Author: Danilo Carrabino                    *
 *                                               *
 *************************************************/


#include "cdvd.h"
#include <sstream>

using namespace std;

CDvd::CDvd(string name)
{
    this->name_ = name;
}

void CDvd::setName(const std::string &name)
{
    name_ = name;
}

std::unique_ptr<CListable> CDvd::clone() const
{
    return make_unique<CDvd>(*this);
}

std::string CDvd::getType() const
{
    return "DVD";
}

std::string CDvd::getName() const
{
    return this->name_;
}

std::string CDvd::toString() const
{
    std::stringstream mySStream;
    mySStream << getType() << ":\n" << getName();

    return mySStream.str();
}
