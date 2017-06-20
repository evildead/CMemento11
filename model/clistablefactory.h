/*************************************************
 *                                               *
 *   Author: Danilo Carrabino                    *
 *                                               *
 *************************************************/


#ifndef CLISTABLEFACTORY_H
#define CLISTABLEFACTORY_H

#include <memory>
#include "clistable.h"
#include "listables/cbook.h"
#include "listables/ccdrom.h"
#include "listables/cdvd.h"

using namespace std;


class CListableFactory
{
public:
    enum listable_t {
        BOOK    = 1,
        CDROM   = 2,
        DVD     = 3
    };

public:
    CListableFactory();

    // Factory Method
    static unique_ptr<CListable> createListable(listable_t listableId, const std::string& name);
};

#endif // CLISTABLEFACTORY_H
