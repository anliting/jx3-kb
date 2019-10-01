#include<iostream>
#include<thread>
#include<windows.h>
#include"interception.h"
#include"utils.h"
namespace scanCode{
    unsigned char
        esc=    0x01,
        n7=     0x08,
        n8=     0x09,
        n9=     0x0A,
        n0=     0x0B,
        y=      0x15,
        x=      0x2D,
        f9=     0x43,
        f10=    0x44,
        f11=    0x85  // result seems to be not
    ;
}
bool status=0;
void press(
    InterceptionContext context,
    InterceptionDevice device,
    InterceptionKeyStroke stroke,
    char key
){
    stroke.code=key;
    stroke.state=INTERCEPTION_KEY_DOWN;
    interception_send(
        context,
        device,
        (InterceptionStroke*)&stroke,
        1
    );
    Sleep(20);
    stroke.state=INTERCEPTION_KEY_UP;
    interception_send(
        context,
        device,
        (InterceptionStroke*)&stroke,
        1
    );
}
void function0(
    InterceptionContext context,
    InterceptionDevice device,
    InterceptionKeyStroke stroke
){
        press(context,device,stroke,scanCode::n7);
        Sleep(100);
        press(context,device,stroke,scanCode::n7);
        Sleep(100);
        press(context,device,stroke,scanCode::n8);
        Sleep(100);
        press(context,device,stroke,scanCode::n8);
        Sleep(100);
        press(context,device,stroke,scanCode::n9);
        Sleep(100);
        press(context,device,stroke,scanCode::n9);
        Sleep(100);
        press(context,device,stroke,scanCode::n0);
        Sleep(100);
        press(context,device,stroke,scanCode::n0);
        status=0;
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
                std::thread(function0,context,device,stroke).detach();
            }
        }
        interception_send(context,device,(InterceptionStroke*)&stroke,1);
    }
    interception_destroy_context(context);
}
