#include<iostream>
#include<thread>
#include<unistd.h>
void function0(){
    //sleep(1000);
    std::cout<<"a";
}
void function1(){
    //sleep(1000);
    std::cout<<"a";
}
int main(){
    std::thread thread0(function0);
    std::thread thread1(function1);
}
