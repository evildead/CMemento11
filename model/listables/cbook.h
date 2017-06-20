/*************************************************
 *                                               *
 *   Author: Danilo Carrabino                    *
 *                                               *
 *************************************************/


#ifndef CBOOK_H
#define CBOOK_H

#include "../clistable.h"

class CBook : public CListable
{
public:
    CBook(std::string name = "");

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

#endif // CBOOK_H
