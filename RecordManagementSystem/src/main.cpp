#include <iostream>
#include "FileStorage.h"
#include "RecordManager.h"
#include "Menu.h"

int main() {
    try {
        FileStorage storage("data/records.dat");
        RecordManager manager(storage);
        manager.load();

        Menu menu(manager);
        menu.run();
    }
    catch (const std::exception& ex) {
        std::cerr << "Fatal error: " << ex.what() << "\n";
        return 1;
    }
    catch (...) {
        std::cerr << "Unknown fatal error occurred.\n";
        return 1;
    }

    return 0;
}