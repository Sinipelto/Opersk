#include <iostream>
#include <regex>

using namespace std;

int main() {
    regex reg("[[:space:]]*[[:digit:]{1,2}]+\\.[[:digit:]]{1,2}+\\.[[:digit:]]{1,4}+[[:space:]]*");
    string s("       5.11.2017 ");

    if (regex_match(s,reg)) {
        cout << "toimii" << endl;
    }

    return 0;
}
