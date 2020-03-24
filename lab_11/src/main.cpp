#include <iostream>
#include <string>

#include <employees.h>
#include <bin_manip.h>


void save_array_to_file(std::string file_name, EmployeesArray& a) {
    std::ofstream outfile (file_name, std::ofstream::binary);
    outfile << a;
    outfile.close();
}

void load_array_from_file(std::string file_name, EmployeesArray& a) {
    std::ifstream infile (file_name, std::ifstream::binary);
    infile >> a;
    infile.close();
}

int main() {
    std::string command;
    EmployeesArray a;
    while(true) {
        std::cin >> command;
        if (command == "exit") {
            break;
        } else if (command == "load") {
            std::string file_name;
            std::cin >> file_name;
            load_array_from_file(file_name, a);
        } else if (command == "save") {
            std::string file_name;
            std::cin >> file_name;
            save_array_to_file(file_name, a);
        } else if (command == "add") {
            a.read_and_add(std::cin);
        } else if (command == "list") {
            std::cout << a;
        } else {

        }
    }

    return 0;
}
