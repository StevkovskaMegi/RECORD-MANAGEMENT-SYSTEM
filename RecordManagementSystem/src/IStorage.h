#ifndef ISTORAGE_H
#define ISTORAGE_H

#include <vector>
#include "Book.h"

class IStorage {
public:
    virtual ~IStorage() = default;
    virtual void load(std::vector<Book>& out) = 0;
    virtual void save(const std::vector<Book>& data) = 0;
};

#endif // ISTORAGE_H