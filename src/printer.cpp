#include <printer.h>
#include <fstream>
#include <iostream>

void ConsolePrinter::print(const CommandsWithTime& container) {
    std::string output = BULK_OUT + "_" + std::to_string(container.id);
    for (auto& command : container.commands) {
        output += " " + command + ",";
    }
    output.pop_back();
    std::cout << output << std::endl;
}


void FilePrinter::print(const CommandsWithTime& container) {
    std::string output = BULK_OUT;
    for (auto& command : container.commands) {
        output += " " + command + ",";
    }

    output.pop_back();

    std::string filename = "bulk" + std::to_string(container.startTime) + "_" + std::to_string(container.id) + ".log";
    std::ofstream ofs(filename);

    if (ofs.is_open()) {
        ofs << output;
        ofs.close();
    }
}