#include<iostream>
#include<thread>
#include<windows.h>
#include"../lib/interception/interception.h"
#include"main/scanCode.cpp"
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
bool jiaoHuStatus,qieYaoZhuiStatus,loop7890Status;
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
void loop7890(
    InterceptionContext context,
    InterceptionDevice device,
    InterceptionKeyStroke stroke
){
    int margin=50;
    for(;qieYaoZhuiStatus;){
        press(context,device,stroke,scanCode::n7);
        Sleep(margin);
        press(context,device,stroke,scanCode::n8);
        Sleep(margin);
        press(context,device,stroke,scanCode::n9);
        Sleep(margin);
    }
}
char mode=0;
void edit(){
    InterceptionContext context;
    InterceptionDevice device;
    InterceptionKeyStroke stroke;
    SetPriorityClass(GetCurrentProcess(),HIGH_PRIORITY_CLASS);
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
        switch(mode){
            case 0:
                if(stroke.code==scanCode::f11&&!qieYaoZhuiStatus){
                    qieYaoZhuiStatus=1;
                    std::thread(qieYaoZhui,context,device,stroke).detach();
                }
            break;
            case 1:
                if(stroke.code==scanCode::f11&&!jiaoHuStatus){
                    jiaoHuStatus=1;
                    std::thread(jiaoHu,context,device,stroke).detach();
                }
                if(stroke.code==scanCode::f12)
                    jiaoHuStatus=0;
            break;
            case 2:
                if(stroke.code==scanCode::f11)
                    loop7890Status=0;
                if(stroke.code==scanCode::f12&&!loop7890Status){
                    loop7890Status=1;
                    std::thread(loop7890,context,device,stroke).detach();
                }
            break;
        }
        interception_send(context,device,(InterceptionStroke*)&stroke,1);
    }
    interception_destroy_context(context);
}
int main(){
    std::thread(edit).detach();
    std::cout<<"0：F11→7788990"<<std::endl;
    std::cout<<"1：F11→F鍵連點；F12→中止"<<std::endl;
    std::cout<<"2：F11→7890循環；F12→中止"<<std::endl;
    for(char c;c=getchar();){
        if(c=='0')
            mode=0;
        if(c=='1')
            mode=1;
        if(c=='2')
            mode=2;
    }
}
