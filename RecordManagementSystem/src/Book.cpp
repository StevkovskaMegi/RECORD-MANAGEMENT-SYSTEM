#include "Book.h"
#include <stdexcept>

static void writeString(std::ostream& os, const std::string& s) {
    size_t len = s.size();
    os.write(reinterpret_cast<const char*>(&len), sizeof(len));
    os.write(s.c_str(), len);
}

static void readString(std::istream& is, std::string& s) {
    size_t len = 0;
    is.read(reinterpret_cast<char*>(&len), sizeof(len));
    if (!is) throw std::runtime_error("Error reading string length");
    s.resize(len);
    is.read(&s[0], len);
    if (!is) throw std::runtime_error("Error reading string data");
}

void Book::writeToStream(std::ostream& os) const {
    writeString(os, id);
    writeString(os, title);
    writeString(os, author);
    os.write(reinterpret_cast<const char*>(&year), sizeof(year));
}

void Book::readFromStream(std::istream& is) {
    readString(is, id);
    readString(is, title);
    readString(is, author);
    is.read(reinterpret_cast<char*>(&year), sizeof(year));
    if (!is) throw std::runtime_error("Error reading year");
}