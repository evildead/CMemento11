/*************************************************
 *                                               *
 *   Author: Danilo Carrabino                    *
 *                                               *
 *************************************************/


#include "ccdrom.h"
#include <sstream>

using namespace std;

CCdRom::CCdRom(string name)
{
    this->name_ = name;
}

void CCdRom::setName(const std::string &name)
{
    name_ = name;
}

std::unique_ptr<CListable> CCdRom::clone() const
{
    return make_unique<CCdRom>(*this);
}

std::string CCdRom::getType() const
{
    return "CD-ROM";
}

std::string CCdRom::getName() const
{
    return this->name_;
}

std::string CCdRom::toString() const
{
    std::stringstream mySStream;
    mySStream << getType() << ":\n" << getName();

    return mySStream.str();
}
