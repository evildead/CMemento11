/*************************************************
 *                                               *
 *   Author: Danilo Carrabino                    *
 *                                               *
 *************************************************/


#ifndef CLISTABLE_H
#define CLISTABLE_H

#include <memory>
#include <string>
#include "utilities/cutility.h"

// Abstract class CListable
class CListable
{
public:
    virtual std::string getTitle() const {
        std::string title = getType();
        title.append(" - ").append(getName());

        return title;
    }

    virtual std::unique_ptr<CListable> clone() const = 0;
    virtual std::string getName() const = 0;
    virtual std::string getType() const = 0;
    virtual std::string toString() const = 0;
};

#endif // CLISTABLE_H
