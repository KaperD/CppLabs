#include "my_array.h"
#include <iostream>
#include <cassert>

void f(lab_13::my_array<bool, 100>& a) {
    std::cout << a[99] << std::endl;
}

int main() {
    lab_13::my_array<bool, 100> v;
    v.fill(true);
    f(v);
    v.fill(true);
    assert(v[3] == true && v[8] == true);
    v.fill(false);
    assert(v[3] == false && v[8] == false);
    v[3] = true;
    assert(v[3] == true);
    v[1] = v[1];
    //assert(v[1] != true && v[2] != true && v[3] != true);

    assert(sizeof(v) == 13);

    lab_13::my_array<int, 100> q;
    q.fill(10);
    assert(q[2] == 10);
    q[3] = -10;
    assert(q[3] == -10);
    q[6] = q[5] = q[3];
    assert(q[6] == -10 && q[5] == -10);

    return 0;
}