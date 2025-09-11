#include <iostream>
using namespace std;

class s2;

class s1 {
private:
    int I1 = 7;

public:
    friend class s2;
    friend void compare(s1& t, s2& f);
};

class s2 {

    int I2 = 9;

public:
    void compare(s1& t)
    {
        if (t.I1 > I2) {
            cout << "I1 is greater than I2" << endl;
        } else {
            cout << "I2 is greater than I1" << endl;
        }
    }

    friend void compare(s1& t, s2& f);

};

void compare(s1& t, s2& f)
{
    if (t.I1 > f.I2)
        cout << "I1 is greater than I2" << endl;
    else
        cout << "I2 is greater than I1" << endl;
};

int main()
{
    s1 g;
    s2 fri;
    fri.compare(g);

    compare(g, fri);

    return 0;
}
