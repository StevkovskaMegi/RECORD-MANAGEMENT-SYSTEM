#include "Menu.h"
#include "Utils.h"
#include <iostream>

void Menu::run() {
    int choice = 0;
    do {
        std::cout << "\n====== RECORD MANAGEMENT SYSTEM ======\n"
                  << "1. Add new book\n"
                  << "2. Display all books\n"
                  << "3. Search book by ID\n"
                  << "4. Delete book by ID\n"
                  << "5. Update book by ID\n"
                  << "6. Sort books\n"
                  << "7. Export to CSV\n"
                  << "8. Exit\n"
                  << "Choose an option: ";
        if (!(std::cin >> choice)) {
            std::cout << "Invalid input.\n";
            Utils::clearInputBuffer();
            continue;
        }
        Utils::clearInputBuffer();

        switch (choice) {
            case 1: addRecord();   break;
            case 2: displayAll();  break;
            case 3: searchById();  break;
            case 4: deleteById();  break;
            case 5: updateById();  break;
            case 6: sortMenu();    break;
            case 7: exportCSV();   break;
            case 8: std::cout << "Exiting...\n"; break;
            default: std::cout << "Invalid option.\n"; break;
        }
    } while (choice != 8);
}

void Menu::addRecord() {
    std::cout << "\n--- Add New Book ---\n";
    std::string id = Utils::getNonEmpty("Enter ID: ");
    if (manager.idExists(id)) {
        std::cout << "ID already exists!\n";
        return;
    }
    std::string title  = Utils::getNonEmpty("Enter Title: ");
    std::string author = Utils::getNonEmpty("Enter Author: ");
    int year = Utils::getInt("Enter Year: ", 0, 3000);

    Book b(id, title, author, year);
    if (manager.addRecord(b)) {
        std::cout << "Book added successfully.\n";
    } else {
        std::cout << "Failed to add book.\n";
    }
}

void Menu::displayAll() {
    std::cout << "\n--- All Books ---\n";
    const auto& all = manager.getAll();
    if (all.empty()) {
        std::cout << "No records found.\n";
        return;
    }
    for (const auto& b : all) {
        std::cout << "ID: " << b.getId() << " | Title: " << b.getTitle()
                  << " | Author: " << b.getAuthor() << " | Year: " << b.getYear() << "\n";
    }
}

void Menu::searchById() {
    std::cout << "\n--- Search Book by ID ---\n";
    std::string id = Utils::getNonEmpty("Enter ID to search: ");
    Book* b = manager.findById(id);
    if (b) {
        std::cout << "Found: ID: " << b->getId() << " | Title: " << b->getTitle()
                  << " | Author: " << b->getAuthor() << " | Year: " << b->getYear() << "\n";
    } else {
        std::cout << "Book not found.\n";
    }
}

void Menu::deleteById() {
    std::cout << "\n--- Delete Book by ID ---\n";
    std::string id = Utils::getNonEmpty("Enter ID to delete: ");
    if (manager.deleteById(id)) {
        std::cout << "Book deleted.\n";
    } else {
        std::cout << "Book not found.\n";
    }
}

void Menu::updateById() {
    std::cout << "\n--- Update Book by ID ---\n";
    std::string id = Utils::getNonEmpty("Enter ID to update: ");
    Book* b = manager.findById(id);
    if (!b) {
        std::cout << "Book not found.\n";
        return;
    }

    std::cout << "Current values (press Enter to keep the same):\n";
    std::cout << "Title [" << b->getTitle() << "]: ";
    std::string title; std::getline(std::cin, title);
    if (!title.empty()) b->setTitle(title);

    std::cout << "Author [" << b->getAuthor() << "]: ";
    std::string author; std::getline(std::cin, author);
    if (!author.empty()) b->setAuthor(author);

    std::cout << "Year [" << b->getYear() << "]: ";
    std::string yearStr; std::getline(std::cin, yearStr);
    if (!yearStr.empty()) {
        try {
            int y = std::stoi(yearStr);
            if (y < 0 || y > 3000) throw std::out_of_range("year range");
            b->setYear(y);
        } catch (...) {
            std::cout << "Invalid year. Keeping old value.\n";
        }
    }

    // After editing the object, save to storage
    // (we can reuse updateById to keep code consistent, although object is already updated)
    if (manager.updateById(id, *b)) {
        std::cout << "Book updated.\n";
    } else {
        std::cout << "Failed to update book.\n";
    }
}

void Menu::sortMenu() {
    std::cout << "\n--- Sort Books ---\n"
              << "1. By Title\n"
              << "2. By Year\n"
              << "Choose: ";

    int opt = 0;
    if (!(std::cin >> opt)) {
        std::cout << "Invalid input.\n";
        Utils::clearInputBuffer();
        return;
    }
    Utils::clearInputBuffer();

    switch (opt) {
        case 1: manager.sortByTitle(); std::cout << "Sorted by title.\n"; break;
        case 2: manager.sortByYear();  std::cout << "Sorted by year.\n";  break;
        default: std::cout << "Invalid option.\n"; break;
    }
}

void Menu::exportCSV() {
    std::cout << "\n--- Export to CSV ---\n";
    std::string path = Utils::getNonEmpty("Enter output CSV path (e.g., export/books_export.csv): ");
    if (manager.exportCSV(path)) {
        std::cout << "Exported successfully to: " << path << "\n";
    } else {
        std::cout << "Export failed.\n";
    }
}