#ifndef LAB11_EMPLOYEES_H_INCLUDED
#define LAB11_EMPLOYEES_H_INCLUDED

#include <stdint.h>
#include <string.h>
#include <utility>
#include <iostream>
#include <vector>


enum class EmployeeType {
    Developer = 1,
    SalesManager = 2,
};


class Employee {
public:
    Employee() = default;
    Employee(const std::string& name, int32_t const base_salary);
    virtual ~Employee() = default;

    virtual void print(std::ostream& os) const = 0;
    virtual void read(std::istream& is) = 0;

    virtual void printBinary(std::ofstream& os) const = 0;
    virtual void readBinary(std::ifstream& is) = 0;

    virtual int salary() const  = 0;

protected:
    std::string name_;
    int32_t base_salary_ = 0;
};


class Developer : public Employee {
public:
    Developer() = default;
    Developer(const std::string& name, int32_t const base_salary, bool has_bonus);
    explicit Developer(const Developer& dev);
    ~Developer() = default;

    void print(std::ostream& os) const override;
    void read(std::istream& is) override;

    void printBinary(std::ofstream& os) const override;
    void readBinary(std::ifstream& is) override;

    int salary() const override;

protected:
    bool has_bonus_;
};


class SalesManager : public Employee {
public:
    SalesManager() = default;
    SalesManager(const std::string& name, int32_t const base_salary, int32_t sold_nm, int32_t price);
    explicit SalesManager(const SalesManager& sales);  
    ~SalesManager() = default; 
    
    void print(std::ostream& os) const override;
    void read(std::istream& is) override;

    void printBinary(std::ofstream& os) const override;
    void readBinary(std::ifstream& is) override;

    int salary() const override;

protected:
    int32_t sold_nm_ = 0;
    int32_t price_ = 0;
};


class EmployeesArray {
public:
    EmployeesArray() = default;
    ~EmployeesArray();

    void add(Employee *e);

    int total_salary() const;

    void read_and_add(std::istream& is);

    void print_array(std::ostream& os) const;
    void print_binary_array(std::ofstream& os) const;

private:
    std::vector<Employee*> employees_ = {};
};


std::ostream& operator << (std::ostream& os, const EmployeesArray& array);
std::ostream& operator << (std::ostream& os, const Employee& employee);

std::ofstream& operator << (std::ofstream& os, const Employee& employee);
std::ofstream& operator << (std::ofstream& os, const EmployeesArray& array);

std::istream& operator >> (std::istream& is, Employee& employee);
//std::istream& operator >> (std::istream& is, EmployeesArray& employee); для симметричности

std::ifstream& operator >> (std::ifstream&is, Employee& employee);
std::ifstream& operator >> (std::ifstream&is, EmployeesArray& array);

#endif
