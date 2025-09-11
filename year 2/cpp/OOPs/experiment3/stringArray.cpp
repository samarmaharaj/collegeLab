#include <bits/stdc++.h>
using namespace std;

int main() {
    char string[] = "Hello World!";
    char string2[] = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!', '\0'};
    int i = 0;
    while(string[i] != '\0') {
        cout << string[i];
        i++;
    }

    return 0;
}