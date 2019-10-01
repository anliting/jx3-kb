#include<iostream>
#include<thread>
#include<windows.h>
#include"interception.h"
#include"utils.h"
namespace scanCode{
    unsigned char
        esc=    0x01,
        n7=     0x08,
        y=      0x15,
        x=      0x2D,
        f9=     0x43,
        f10=    0x44,
        f11=    0x85  // result seems to be not
    ;
}
bool status=0;
std::thread thread0;
void function0(){
    for(;;){
        if(status){
            std::cout<<"7\n";
            Sleep(100);
            std::cout<<"8\n";
            Sleep(100);
            std::cout<<"9\n";
            Sleep(100);
            std::cout<<"0\n";
            Sleep(100);
            status=0;
        }else
            Sleep(1);
    }
}
int main(){
    InterceptionContext context;
    InterceptionDevice device;
    InterceptionKeyStroke stroke;
    raise_process_priority();
    context=interception_create_context();
    interception_set_filter(
        context,
        interception_is_keyboard,
        INTERCEPTION_FILTER_KEY_DOWN|INTERCEPTION_FILTER_KEY_UP
    );
    while(
        interception_receive(
            context,
            device=interception_wait(context),
            (InterceptionStroke*)&stroke,
            1
        )>0
    ){
        std::cout<<stroke.code<<"\n";
        if(stroke.code==scanCode::f9){
            if(!status){
                status=1;
                thread0=std::thread(function0);
            }
        }
        interception_send(context,device,(InterceptionStroke*)&stroke,1);
    }
    interception_destroy_context(context);
}
