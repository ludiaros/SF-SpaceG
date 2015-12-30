#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <cmath>
#include <SFML/Graphics.hpp>
using namespace std;

int main() {

    /*list<bool> lst;
    lst.push_back(false);
    lst.push_back(true);
    lst.push_back(false);
    lst.push_back(false);

    cout << lst.at(1); << endl;

    cout << lst.size() << endl << endl;

    for (typename list<Rock>::iterator b=lst.begin(); b!=lst.end(); ++b) {
        cout << b->rangle << ", " << endl;
    }*/

    /*vector<int> lst;
    lst.push_back(0);
    lst.push_back(1);
    lst.push_back(3);
    lst.push_back(5);
    lst.push_back(7);
    lst.push_back(9);
    lst.push_back(2);
    for (unsigned int i=0; i<lst.size(); ++i) {
        cout << i << " of " << lst.size() << ": " << lst[i] << endl;
    }
    cout << endl;

    lst.pop_back();
    for (unsigned int i=0; i<lst.size(); ++i) {
        cout << i << " of " << lst.size() << ": " << lst[i] << endl;
    }
    cout << endl;

    lst.clear();
    cout << lst.size() << endl;
    cout << endl;*/

    /*map <int, int> lst;
    lst[0] = 5;
    lst[2] = 4;
    lst[4] = 8;
    lst[6] = 9;
    lst[8] = 1;

    for (unsigned int i=0; i<lst.size(); ++i) {
        cout << i << " of " << lst.size() << ": " << lst[i] << endl;
    }*/

    vector<int*> lst;

    lst.push_back(new int(0));
    lst.push_back(new int(4));
    lst.push_back(new int(3));
    lst.push_back(new int(5));
    lst.push_back(new int(2));

    for (unsigned int i=0; i<lst.size(); ++i) {
        cout << i << " of " << lst.size() << ": " << *lst[i] << endl;
    }
    cout << "null - " << lst[6] << endl;
}
