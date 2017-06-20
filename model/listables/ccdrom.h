/*************************************************
 *                                               *
 *   Author: Danilo Carrabino                    *
 *                                               *
 *************************************************/


#ifndef CCDROM_H
#define CCDROM_H

#include "../clistable.h"

class CCdRom : public CListable
{
public:
    CCdRom(std::string name = "");

protected:
    std::string name_;

    // CListable interface
public:
    std::unique_ptr<CListable> clone() const;
    std::string getName() const;
    std::string getType() const;
    std::string toString() const;

    void setName(const std::string &name);
};

#endif // CCDROM_H
