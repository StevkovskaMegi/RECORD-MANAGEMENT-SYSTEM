#ifndef RECORDMANAGER_H
#define RECORDMANAGER_H

#include <vector>
#include <string>
#include "Book.h"
#include "IStorage.h"

class RecordManager {
private:
    std::vector<Book> records;
    IStorage& storage;

public:
    explicit RecordManager(IStorage& s);

    void load();
    void save();

    // CRUD
    bool addRecord(const Book& book);               // returns false if ID exists
    Book* findById(const std::string& id);
    bool deleteById(const std::string& id);
    bool updateById(const std::string& id, const Book& updated);

    // Retrieval helpers
    const std::vector<Book>& getAll() const { return records; }

    // Sorting
    void sortByTitle();
    void sortByYear();

    // Export
    bool exportCSV(const std::string& path) const;

    // Validation
    bool idExists(const std::string& id) const;
};

#endif // RECORDMANAGER_H