#include<iostream>
#include<thread>
#include<unistd.h>
bool f=0;
void function0(){
    usleep(1000*1000);
    std::cout<<f<<"\n";
    f=1;
}
void function1(){
    usleep(2000*1000);
    std::cout<<f<<"\n";
}
int main(){
    std::thread thread0(function0);
    std::thread thread1(function1);
    thread0.join();
    thread1.join();
}
