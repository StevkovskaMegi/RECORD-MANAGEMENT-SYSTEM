#ifndef MENU_H
#define MENU_H

#include "RecordManager.h"

class Menu {
private:
    RecordManager& manager;

    void addRecord();
    void displayAll();
    void searchById();
    void deleteById();
    void updateById();
    void sortMenu();
    void exportCSV();

public:
    explicit Menu(RecordManager& m) : manager(m) {}
    void run();
};

#endif // MENU_H