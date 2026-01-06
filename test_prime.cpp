#include <iostream>
using namespace std;
bool isPrime(int n)
 {
    if(n < 2) 
    return false;
    for(int i=2;i*i<=n;i++)
    {
        if(n%i==0)
        return false;
    }
    return true;
}
main()
 {
    if(isPrime(13) && !isPrime(15))
        cout << "Prime Test Passed";
    else
        cout << "Prime Test Failed";
}
