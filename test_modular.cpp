#include <iostream>
using namespace std;
int mod(int a, int m)
{
    int c= (a % m + m) % m;
    return c;
}
 main()
 {
    if(mod(7,5) == 2)
        cout << "Mod Test Passed";
    else
        cout << "Mod Test Failed";
}
