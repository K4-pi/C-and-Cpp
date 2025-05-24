#include <iostream>
#include <sys/types.h>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {

    vector<string> names;
    names.push_back("Kacper");
    names.push_back("Miłosz");

    unordered_map<string, string> map;
    
    for (u_int8_t i = 0; i < names.size(); i++) {
        if (names[i] == "Kacper") map[names[i]] = "Zoła";
        if (names[i] == "Miłosz") map[names[i]] = "Kowalski";
    }

    if (map.find("Kacper") != map.end()) cout << "Kacper " << map["Kacper"] << endl;
    if (map.find("Miłosz") != map.end()) cout << "Miłosz " << map["Miłosz"] << endl;

    return 0;
}
