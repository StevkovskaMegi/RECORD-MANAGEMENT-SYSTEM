#include "FileStorage.h"
#include <fstream>
#include <stdexcept>
#include <filesystem>

FileStorage::FileStorage(std::string filename) : filename(std::move(filename)) {}

void FileStorage::load(std::vector<Book>& out) {
    out.clear();
    std::ifstream ifs(filename, std::ios::binary);
    if (!ifs) {
        // First run: file might not exist, no error
        return;
    }

    while (ifs.peek() != EOF && ifs.good()) {
        Book b;
        std::streampos pos = ifs.tellg();
        try {
            b.readFromStream(ifs);
            if (ifs.good()) {
                out.push_back(std::move(b));
            } else {
                // Partial read or EOF; rewind and break
                ifs.clear();
                ifs.seekg(pos);
                break;
            }
        } catch (...) {
            // Corrupted data; stop reading
            break;
        }
    }
}

void FileStorage::save(const std::vector<Book>& data) {
    // Ensure directory exists
    std::filesystem::path p(filename);
    if (!p.parent_path().empty()) {
        std::filesystem::create_directories(p.parent_path());
    }

    std::ofstream ofs(filename, std::ios::binary | std::ios::trunc);
    if (!ofs) throw std::runtime_error("Cannot open file for writing: " + filename);

    for (const auto& b : data) {
        b.writeToStream(ofs);
    }
}