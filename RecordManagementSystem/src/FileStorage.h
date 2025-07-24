#ifndef FILESTORAGE_H
#define FILESTORAGE_H

#include "IStorage.h"
#include <string>

class FileStorage : public IStorage {
private:
    std::string filename;
public:
    explicit FileStorage(std::string filename);
    void load(std::vector<Book>& out) override;
    void save(const std::vector<Book>& data) override;
};

#endif // FILESTORAGE_H