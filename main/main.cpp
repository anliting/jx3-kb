#include<iostream>
#include<thread>
#include<windows.h>
#include"..\lib\interception.h"
#include"..\lib\utils.h"
namespace scanCode{
    unsigned char
        esc=    0x01,
        n7=     0x08,
        n8=     0x09,
        n9=     0x0A,
        n0=     0x0B,
        y=      0x15,
        f=      0x21,
        x=      0x2D,
        f9=     0x43,
        f10=    0x44,
        f11=    0x57
    ;
}
bool jiaoHuStatus,qieYaoZhuiStatus;
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
    stroke.state=INTERCEPTION_KEY_UP;
    interception_send(
        context,
        device,
        (InterceptionStroke*)&stroke,
        1
    );
}
void jiaoHu(
    InterceptionContext context,
    InterceptionDevice device,
    InterceptionKeyStroke stroke
){
    for(;jiaoHuStatus;){
        press(context,device,stroke,scanCode::f);
        Sleep(1);
    }
}
void qieYaoZhui(
    InterceptionContext context,
    InterceptionDevice device,
    InterceptionKeyStroke stroke
){
    int marginA=150,marginB=50;
    press(context,device,stroke,scanCode::n7);
    Sleep(marginA);
    press(context,device,stroke,scanCode::n7);
    Sleep(marginB);
    press(context,device,stroke,scanCode::n8);
    Sleep(marginA);
    press(context,device,stroke,scanCode::n8);
    Sleep(marginB);
    press(context,device,stroke,scanCode::n9);
    Sleep(marginA);
    press(context,device,stroke,scanCode::n9);
    Sleep(marginB);
    press(context,device,stroke,scanCode::n0);
    qieYaoZhuiStatus=0;
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
        if(stroke.code==scanCode::f9&&!jiaoHuStatus){
            jiaoHuStatus=1;
            std::thread(jiaoHu,context,device,stroke).detach();
        }
        if(stroke.code==scanCode::f10)
            jiaoHuStatus=0;
        if(stroke.code==scanCode::f11&&!qieYaoZhuiStatus){
            qieYaoZhuiStatus=1;
            std::thread(qieYaoZhui,context,device,stroke).detach();
        }
        interception_send(context,device,(InterceptionStroke*)&stroke,1);
    }
    interception_destroy_context(context);
}
