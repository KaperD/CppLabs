#include "bin_manip.h"

int BYTE = 8;

write_le_int32::write_le_int32(int32_t x) : value(x) {}

std::ostream& write_le_int32::operator () (std::ostream &os) const {
    for (int k = 0; k < 4; ++k) {
        unsigned char c = (value >> BYTE * k) & 0xFF;
        os.write(reinterpret_cast<char*>(&c), 1);
    }
    return os;
}

std::ostream& operator << (std::ostream& os, const write_le_int32& x) {
    return x(os);
}



read_le_int32::read_le_int32(int32_t& x) : value(x) {}

std::istream& read_le_int32::operator () (std::istream& is) const {
    uint8_t bytes[4];
    is.read(reinterpret_cast<char*>(bytes), 4);
    value = 0;
    for (int k = 3; k >= 0; --k) {
        value |= bytes[k];
        if (k != 0) value = value << BYTE;
    }
    return is;
}

std::istream& operator >> (std::istream& is, const read_le_int32& x) {
    return x(is);
}


//----------------------------------------------------------------


write_bool::write_bool(bool b) : boolean(b) {}

std::ostream& write_bool::operator () (std::ostream& os) const {
    os.put((boolean ? '\1' : '\0'));
    return os;
}

std::ostream& operator << (std::ostream& os, const write_bool& b) {
    return b(os);
}



read_bool::read_bool(bool &b) : boolean(b) {}

std::istream& read_bool::operator () (std::istream& is) const {
    char c;
    is.get(c);
    boolean = (c == '\0' ? false : true);
    return is;
}

std::istream& operator >> (std::istream& is, const read_bool& b) {
    return b(is);
}


//----------------------------------------------------------------


write_c_str::write_c_str(const char* c) : str(c) {}

std::ostream& write_c_str::operator () (std::ostream& os) const {
    const char* c = str;
    while (*c != '\0') {
        os.put(*c);
        ++c;
    }
    os.put('\0');
    return os;
}

std::ostream& operator << (std::ostream& os, const write_c_str& c) {
    return c(os);
}



read_c_str::read_c_str(char* c, size_t size) : str(c), cnt(size) {}

std::istream& read_c_str::operator () (std::istream& is) const {
    char c = '1';
    size_t k = 0;
    is.get(c);
    while (k < cnt && c != '\0') {
        str[k] = c;
        ++k;
        is.get(c);
    }
    str[k] = '\0';
    if (k == cnt) {
        is.clear(std::ios_base::failbit);
    }
    
    return is;
}

std::istream& operator >> (std::istream& is, const read_c_str& b) {
    return b(is);
}