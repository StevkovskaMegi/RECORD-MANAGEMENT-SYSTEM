#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <iostream>

class Book {
private:
    std::string id;
    std::string title;
    std::string author;
    int year{0};

public:
    Book() = default;
    Book(std::string id, std::string title, std::string author, int year)
        : id(std::move(id)), title(std::move(title)), author(std::move(author)), year(year) {}

    // Getters & Setters
    const std::string& getId() const { return id; }
    void setId(const std::string& v) { id = v; }

    const std::string& getTitle() const { return title; }
    void setTitle(const std::string& v) { title = v; }

    const std::string& getAuthor() const { return author; }
    void setAuthor(const std::string& v) { author = v; }

    int getYear() const { return year; }
    void setYear(int y) { year = y; }

    // Serialization helpers
    void writeToStream(std::ostream& os) const;
    void readFromStream(std::istream& is);
};

#endif // BOOK_H