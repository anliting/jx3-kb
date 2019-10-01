#include<iostream>
#include<thread>
#include<windows.h>
#include"interception.h"
#include"utils.h"
namespace scanCode{
    unsigned char
        esc=    0x01,
        y=      0x15,
        x=      0x2D,
        f11=    0x85
    ;
}
bool status=0;
void function0(){
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
            device = interception_wait(context),
            (InterceptionStroke *)&stroke,
            1
        )>0
    ){
        if(stroke.code==scanCode::f11)
            status=1;
        interception_send(context,device,(InterceptionStroke *)&stroke,1);
        /*if(stroke.code==SCANCODE_ESC)
            break;*/
    }
    interception_destroy_context(context);
}
void function1(){
    for(;;){
        if(status){
            std::cout<<"F11\n";
            status=0;
        }else
            Sleep(1);
    }
}
int main(){
    std::thread thread0(function0);
    std::thread thread1(function1);
    thread0.join();
    thread1.join();
}
