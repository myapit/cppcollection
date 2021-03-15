#include <iostream>

// This is how one brings a name into the current scope.  In this case, it's
// bringing them into global scope.
using std::cout;
using std::endl;

namespace box1 {
    int box_side = 4;
}

namespace box2 {
    int box_side = 12;
}

int main() {
    int box_side = 42;
    cout << box1::box_side << endl;  // Outputs 4.
    cout << box2::box_side << endl;  // Outputs 12.
    cout << box_side << endl;  // Outputs 42.
}
