// array_utils.h
#ifndef ARRAY_UTILS_H
#define ARRAY_UTILS_H
#include <bits/stdc++.h>
using namespace std;

int orfunction(const vector<int>& inputs) {
    for (int input : inputs) {
        if (input == 1) {
            return 1;
        }
    }
    return 0;
}

int andfunction(const vector<int>& inputs) {
    for (int input : inputs) {
        if (input == 0) {
            return 0;
        }
    }
    return 1;
}

int nandfunction(const vector<int>& inputs) {
    for (int input : inputs) {
        if (input == 0) {
            return 1;
        }
    }
    return 0;
}

int norfunction(const vector<int>& inputs) {
    for (int input : inputs) {
        if (input == 1) {
            return 0;
        }
    }
    return 1;
}

int notfunction(int a) {
    return a == 0 ? 1 : 0;
}

int xorfunction(const vector<int>& inputs) {
    int count = 0;
    for (int input : inputs) {
        if (input == 1) {
            count++;
        }
    }
    return count % 2 == 1 ? 1 : 0;
}

int xnorfunction(const vector<int>& inputs) {
    int count = 0;
    for (int input : inputs) {
        if (input == 1) {
            count++;
        }
    }
    return count % 2 == 0 ? 1 : 0;
}

#endif // ARRAY_UTILS_H