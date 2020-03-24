#ifndef BIN_MANIP_H
#define BIN_MANIP_H

#include <stdint.h>
#include <iostream>
#include <fstream>

class write_le_int32 {
public:
    write_le_int32(int32_t x);
    std::ostream& operator () (std::ostream& os) const;

private:
    int32_t value;
};

std::ostream& operator << (std::ostream& os, const write_le_int32& x);

class read_le_int32 {
public:
    read_le_int32(int32_t& x);
    std::istream& operator () (std::istream& is) const;

private:
    int32_t& value;
};

std::istream& operator >> (std::istream& is, const read_le_int32& x);

class write_bool {
public:
    write_bool(bool b);
    std::ostream& operator () (std::ostream& os) const;

private:
    bool boolean;
};

std::ostream& operator << (std::ostream& os, const write_bool& b);

class read_bool {
public:
    read_bool(bool &b);
    std::istream& operator () (std::istream& is) const;
private:
    bool& boolean;
};

std::istream& operator >> (std::istream& is, const read_bool& b);



class write_c_str {
public:
    write_c_str(const char* c);
    std::ostream& operator () (std::ostream& os) const;
private:
    const char* str;
};

std::ostream& operator << (std::ostream& os, const write_c_str& c);

class read_c_str {
public:
    read_c_str(char* c, size_t size);
    std::istream& operator () (std::istream& is) const;
private:
    char* str;
    size_t cnt;
};

std::istream& operator >> (std::istream& is, const read_c_str& b);

#endif