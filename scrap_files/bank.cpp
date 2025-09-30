#include <thread>
#include <iostream>


using std::cout;
using std::endl;

int balance = 0;

void deposit(int count, int amount){
    for(int i = 0; i< count; ++i){
        balance += amount;
    }
    cout << balance <<endl;
}

void withdraw(int count, int amount){
    for(int i = 0; i< count; ++i){
        balance -= amount;
    }
    cout << balance <<endl;
}

int main(){
    std::thread t1(deposit, 1000, 1);
    std::thread t2(withdraw, 1000, 1);
    t1.join();
    t2.join();
}
