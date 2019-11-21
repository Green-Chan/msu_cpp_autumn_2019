#include <iostream>
#include "format.h"

using namespace std;

int main() {
    cout << format("{1} + {1}={0}", 2, "one") << endl;
    cout << format("string without arguments") << endl;
    cout << format("{1} + {1}={2}", 0, 1, 2) << endl;
    cout << format("{0}!={1}", false, true) << endl;
    try {
        cout << format("{1} + {1}={0}", 2);
    } catch(runtime_error& e) {
        cout << "error: " << e.what() << endl;
    }
    try {
        cout << format("{one} + {one}={0}", 2);
    } catch(runtime_error& e) {
        cout << "error: " << e.what() << endl;
    }
    try {
        cout << format("{1} + {1}={0", 2, "one");
    } catch(runtime_error& e) {
        cout << "error: " << e.what() << endl;
    }
}

