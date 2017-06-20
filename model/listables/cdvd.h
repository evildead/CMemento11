/*************************************************
 *                                               *
 *   Author: Danilo Carrabino                    *
 *                                               *
 *************************************************/


#ifndef CDVD_H
#define CDVD_H

#include "../clistable.h"

class CDvd : public CListable
{
public:
    CDvd(std::string name = "");

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

#endif // CDVD_H
