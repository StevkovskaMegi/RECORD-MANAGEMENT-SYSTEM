#include "RecordManager.h"
#include <algorithm>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

RecordManager::RecordManager(IStorage& s) : storage(s) {}

void RecordManager::load() {
    storage.load(records);
}

void RecordManager::save() {
    storage.save(records);
}

bool RecordManager::idExists(const std::string& id) const {
    return std::any_of(records.begin(), records.end(),
                       [&](const Book& b){ return b.getId() == id; });
}

bool RecordManager::addRecord(const Book& book) {
    if (idExists(book.getId())) return false;
    records.push_back(book);
    save();
    return true;
}

Book* RecordManager::findById(const std::string& id) {
    auto it = std::find_if(records.begin(), records.end(),
                           [&](const Book& b){ return b.getId() == id; });
    if (it != records.end()) return &(*it);
    return nullptr;
}

bool RecordManager::deleteById(const std::string& id) {
    auto it = std::remove_if(records.begin(), records.end(),
                             [&](const Book& b){ return b.getId() == id; });
    if (it != records.end()) {
        records.erase(it, records.end());
        save();
        return true;
    }
    return false;
}

bool RecordManager::updateById(const std::string& id, const Book& updated) {
    for (auto& b : records) {
        if (b.getId() == id) {
            b = updated; // full replace
            save();
            return true;
        }
    }
    return false;
}

void RecordManager::sortByTitle() {
    std::sort(records.begin(), records.end(),
              [](const Book& a, const Book& b){ return a.getTitle() < b.getTitle(); });
    save();
}

void RecordManager::sortByYear() {
    std::sort(records.begin(), records.end(),
              [](const Book& a, const Book& b){ return a.getYear() < b.getYear(); });
    save();
}

bool RecordManager::exportCSV(const std::string& path) const {
    try {
        fs::path p(path);
        if (!p.parent_path().empty()) {
            fs::create_directories(p.parent_path());
        }

        std::ofstream ofs(path);
        if (!ofs) return false;

        ofs << "ID,Title,Author,Year\n";

        auto csvEscape = [](const std::string& s) {
            std::string out = "\"";
            for (char c : s) {
                if (c == '\"') out += "\"\"";  // double quotes inside fields
                else out += c;
            }
            out += "\"";
            return out;
        };

        for (const auto& b : records) {
            ofs << csvEscape(b.getId())     << ','
                << csvEscape(b.getTitle())  << ','
                << csvEscape(b.getAuthor()) << ','
                << b.getYear()              << '\n';
        }
        return true;
    } catch (...) {
        return false;
    }
}
