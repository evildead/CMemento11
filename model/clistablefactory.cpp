/*************************************************
 *                                               *
 *   Author: Danilo Carrabino                    *
 *                                               *
 *************************************************/


#include "clistablefactory.h"

CListableFactory::CListableFactory()
{

}

// Factory Method
unique_ptr<CListable> CListableFactory::createListable(listable_t listableId, const std::string& name)
{
    switch(listableId) {
    case BOOK:
        return make_unique<CBook>(name);

    case CDROM:
        return make_unique<CCdRom>(name);

    case DVD:
        return make_unique<CDvd>(name);

    default:
        return unique_ptr<CListable>(nullptr);
    }
}
