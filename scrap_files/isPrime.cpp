#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>


bool isPrimeST(uint64_t n){
    uint64_t lim = sqrt(n);
    if(n==2) return true;
    if (n%2 == 0) return false;
    for(uint64_t i = 3; i<=lim; i+=2){
        if (n%i == 0) return false;
    }
    return true;
}

void isPrimeMT(uint64_t a, uint64_t b, uint64_t* count){
    uint64_t c = (a == 2 ? 1 : 0);
    a |= 1;
    for(uint64_t i = a; i<=b; i+=2){
        if(isPrimeST(i)) c++;
    }
    *count = c;
    
}


int main(int argc, char* argv[]){
    uint64_t n = atol(argv[1]);
    uint64_t count1 = 0, count2 = 0;

    std::thread t1(isPrimeMT, 0, n/2, &count1);
    std::thread t2(isPrimeMT, n/2+1, n, &count2);

    t1.join();
    t2.join();

    uint64_t count = count1 + count2;

    std::cout << count << std::endl;
    
}
