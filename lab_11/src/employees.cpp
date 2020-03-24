#include "employees.h"
#include "bin_manip.h"
#include <string>
#include <memory>
#include <cassert>


int32_t MAX_NAME_LENGTH = 100;



Employee::Employee(const std::string& name, int32_t const base_salary) : name_(name), base_salary_(base_salary) {}

std::ostream& operator << (std::ostream& os, const Employee& employee) {
    employee.print(os);
    return os;
}

std::istream& operator >> (std::istream& is, Employee& employee) {
    employee.read(is);
    return is;
}


std::ofstream& operator<<(std::ofstream& os, const Employee& employee) {
    employee.printBinary(os);
    return os;
}

std::ifstream& operator>>(std::ifstream& is, Employee& employee) {
    employee.readBinary(is);
    return is;
}


//----------------------------------------------------------------


Developer::Developer(const Developer& dev) : Developer(dev.name_, dev.base_salary_, dev.has_bonus_) {}

Developer::Developer(const std::string& name, int32_t const base_salary, 
                     bool has_bonus) : Employee(name, base_salary), has_bonus_(has_bonus) {}


void Developer::print(std::ostream& os) const {
    os << "Developer\n";
    os << "Name: " << name_ << '\n';
    os << "Base Salary: " << base_salary_ << '\n';
    os << "Has bonus: " << (has_bonus_ ? '+' : '-');
}

void Developer::read(std::istream& is) {
    is >> name_ >> base_salary_ >> has_bonus_;
}


void Developer::printBinary(std::ofstream& os) const {
    os << write_le_int32(static_cast<int32_t>(EmployeeType::Developer));
    os << write_c_str(name_.c_str());
    os << write_le_int32(base_salary_);
    os << write_bool(has_bonus_);
}

void Developer::readBinary(std::ifstream& is) {
    char new_name[101];
    is >> read_c_str(new_name, MAX_NAME_LENGTH);
    name_ = std::string(new_name);
    is >> read_le_int32(base_salary_);
    is >> read_bool(has_bonus_);
}


int Developer::salary() const {
    int salary = base_salary_;
    if (has_bonus_) { salary += 1000; }
    return salary;
}


std::ostream& operator << (std::ostream& os, const Developer& dev) {
    dev.print(os);
    return os;
}


//----------------------------------------------------------------


SalesManager::SalesManager(const SalesManager& sales) : SalesManager(sales.name_, sales.base_salary_,
                                                                     sales.sold_nm_, sales.price_) {}

SalesManager::SalesManager(const std::string& name, 
                           int32_t const base_salary, 
                           int32_t sold_nm, int32_t price) : 
                           Employee(name, base_salary), sold_nm_(sold_nm), price_(price) {} 


void SalesManager::print(std::ostream& os) const {
    os << "Sales Manager\n";
    os << "Name: " << name_ << '\n';
    os << "Base Salary: " << base_salary_ << '\n';
    os << "Sold items: " << sold_nm_ << '\n';
    os << "Item price: " << price_;
}

void SalesManager::read(std::istream& is) {
    is >> name_ >> base_salary_ >> sold_nm_ >> price_;
}


void SalesManager::printBinary(std::ofstream& os) const {
    os << write_le_int32(static_cast<int32_t>(EmployeeType::SalesManager));
    os << write_c_str(name_.c_str());
    os << write_le_int32(base_salary_);
    os << write_le_int32(sold_nm_);
    os << write_le_int32(price_);
}

void SalesManager::readBinary(std::ifstream& is) {
    char new_name[101];
    is >> read_c_str(new_name, MAX_NAME_LENGTH);
    name_ = std::string(new_name);
    is >> read_le_int32(base_salary_);
    is >> read_le_int32(sold_nm_);
    is >> read_le_int32(price_);
}


int SalesManager::salary() const {
    return base_salary_ + sold_nm_ * price_ * 0.01;
}


std::ostream& operator << (std::ostream& os, const SalesManager& sales) {
    sales.print(os);
    return os;
}


//----------------------------------------------------------------


EmployeesArray::~EmployeesArray() {
    for (auto employee : employees_) {
        delete employee;
    }
}


void EmployeesArray::add(Employee *e) {
    assert(e != nullptr);
    employees_.push_back(e);
}


int EmployeesArray::total_salary() const {
    int32_t salary_sum = 0;
    for (auto employee : employees_) {
        salary_sum += employee->salary();
    }
    return salary_sum;
}


void EmployeesArray::read_and_add(std::istream& is) {
    int type = 0;
    is >> type;
    if (type == static_cast<int32_t>(EmployeeType::Developer)) {
        Developer* dev = new Developer;
        is >> *dev;
        this->add(dev);
    } else if (type == static_cast<int32_t>(EmployeeType::SalesManager)) {
        SalesManager* sales = new SalesManager;
        is >> *sales;
        this->add(sales);
    }
}


void EmployeesArray::print_array(std::ostream& os) const {
    for (size_t k = 0; k < employees_.size(); ++k) {
        os << (k + 1) << ". " << *employees_[k] << '\n';
    }
    os << "== Total salary: " << this->total_salary() << '\n';
}

void EmployeesArray::print_binary_array(std::ofstream& os) const {
    os << write_le_int32(employees_.size());
    for (auto employee : employees_) {
        os << *employee;
    }
}


std::ostream& operator << (std::ostream& os, const EmployeesArray& array) {
    array.print_array(os);
    os << '\n';
    return os;
}

std::ofstream& operator << (std::ofstream& os, const EmployeesArray& array) {
    array.print_binary_array(os);
    return os;
}


std::ifstream& operator >> (std::ifstream&is, EmployeesArray& array) {
    int n = 0;
    is >> read_le_int32(n);
    for (int k = 0; k < n; ++k) {
        int type = 0;
        is >> read_le_int32(type);
        if (type == 1) {
            Developer* dev = new Developer;
            is >> (*dev);
            array.add(dev);
        } else if (type == 2) {
            SalesManager* sales = new SalesManager;
            is >> *sales;
            array.add(sales);
        }
    }
    return is;
}
