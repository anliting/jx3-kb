#include<iostream>
#include<thread>
#include<windows.h>
#include<conio.h>
#include"../lib/interception/interception.h"
#include"scanCode/main.cpp"
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
bool jiaoHuStatus,qieYaoZhuiStatus,loop7890Status,shuaGuaiStatus,keepClick1Status,zhiYian0Status,zhiYian2Status,zhiYian3Status;
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
    for(;loop7890Status;){
        press(context,device,stroke,scanCode::n7);
        Sleep(margin);
        press(context,device,stroke,scanCode::n8);
        Sleep(margin);
        press(context,device,stroke,scanCode::n9);
        Sleep(margin);
    }
}
void shuaGuai(
    InterceptionContext context,
    InterceptionDevice device,
    InterceptionKeyStroke stroke
){
    int margin=50;
    for(;shuaGuaiStatus;){
        for(int i=0;shuaGuaiStatus&&i<40;i++){
            press(context,device,stroke,scanCode::tab);
            Sleep(margin);
            press(context,device,stroke,scanCode::n1);
            Sleep(3000);
        }
        stroke.state=INTERCEPTION_KEY_DOWN;
        stroke.code=scanCode::lalt;
        interception_send(
            context,
            device,
            (InterceptionStroke*)&stroke,
            1
        );
        stroke.code=scanCode::n4;
        interception_send(
            context,
            device,
            (InterceptionStroke*)&stroke,
            1
        );
        stroke.state=INTERCEPTION_KEY_UP;
        stroke.code=scanCode::lalt;
        interception_send(
            context,
            device,
            (InterceptionStroke*)&stroke,
            1
        );
        stroke.code=scanCode::n4;
        interception_send(
            context,
            device,
            (InterceptionStroke*)&stroke,
            1
        );
    }
}
void keepClick1(
    InterceptionContext context,
    InterceptionDevice device,
    InterceptionKeyStroke stroke
){
    for(;keepClick1Status;){
        press(context,device,stroke,scanCode::n1);
        Sleep(1);
    }
}
void zhiYian0(
    InterceptionContext context,
    InterceptionDevice device,
    InterceptionKeyStroke stroke
){
/*
    Caplock（大小寫切換鍵）
    延遲200毫秒
    數字鍵1
    延遲400毫秒
    數字鍵2
    延遲1880毫秒
    ×9
    Caplock
    延遲200毫秒
    數字鍵4
    延遲400毫秒
    數字鍵2
    延遲1880毫秒
*/
    for(;zhiYian0Status;){
        press(context,device,stroke,scanCode::capsLock);
        Sleep(200);
        press(context,device,stroke,scanCode::n1);
        Sleep(400);
        press(context,device,stroke,scanCode::n2);
        Sleep(1880);
        for(int i=0;zhiYian0Status&&i<9;i++){
            press(context,device,stroke,scanCode::capsLock);
            Sleep(200);
            press(context,device,stroke,scanCode::n4);
            Sleep(400);
            press(context,device,stroke,scanCode::n2);
            Sleep(1880);
        }
    }
}
void zhiYian2(
    InterceptionContext context,
    InterceptionDevice device,
    InterceptionKeyStroke stroke
){
/*
    ×1
    Caplock（大小寫切換鍵）
    延遲200毫秒
    數字鍵1
    延遲400毫秒
    數字鍵2
    延遲1880毫秒
    ×16
    Caplock
    延遲200毫秒
    數字鍵4
    延遲400毫秒
    數字鍵2
    延遲1880毫秒

    數字鍵0
    延遲8120毫秒
*/
    for(;zhiYian2Status;){
        press(context,device,stroke,scanCode::capsLock);
        Sleep(200);
        press(context,device,stroke,scanCode::n1);
        Sleep(400);
        press(context,device,stroke,scanCode::n2);
        Sleep(1880);
        for(int i=0;zhiYian2Status&&i<16;i++){
            press(context,device,stroke,scanCode::capsLock);
            Sleep(200);
            press(context,device,stroke,scanCode::n4);
            Sleep(400);
            press(context,device,stroke,scanCode::n2);
            Sleep(1880);
            press(context,device,stroke,scanCode::n0);
            Sleep(8120);
        }
    }
}
void zhiYian3(
    InterceptionContext context,
    InterceptionDevice device,
    InterceptionKeyStroke stroke
){
/*
    F1鍵
    延遲300毫秒

    x20
    7鍵（數字7）
    延遲300毫秒

    x3
    Caplock（大小寫切換鍵）
    延遲200毫秒
    數字鍵2
    延遲800毫秒
*/
    for(;zhiYian3Status;){
        press(context,device,stroke,scanCode::f1);
        Sleep(300);
        for(int i=0;zhiYian3Status&&i<20;i++){
            press(context,device,stroke,scanCode::n7);
            Sleep(300);
        }
        for(int i=0;zhiYian3Status&&i<3;i++){
            press(context,device,stroke,scanCode::capsLock);
            Sleep(200);
            press(context,device,stroke,scanCode::n2);
            Sleep(800);
        }
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
                if(stroke.code==scanCode::f11&&!loop7890Status){
                    loop7890Status=1;
                    std::thread(loop7890,context,device,stroke).detach();
                }
                if(stroke.code==scanCode::f12)
                    loop7890Status=0;
            break;
            case 3:
                if(stroke.code==scanCode::f11&&!shuaGuaiStatus){
                    shuaGuaiStatus=1;
                    std::thread(shuaGuai,context,device,stroke).detach();
                }
                if(stroke.code==scanCode::f12)
                    shuaGuaiStatus=0;
            break;
            case 4:
                if(stroke.code==scanCode::f11&&!keepClick1Status){
                    keepClick1Status=1;
                    std::thread(keepClick1,context,device,stroke).detach();
                }
                if(stroke.code==scanCode::f12)
                    keepClick1Status=0;
            break;
            case 5:
                if(stroke.code==scanCode::f11&&!zhiYian0Status){
                    zhiYian0Status=1;
                    std::thread(zhiYian0,context,device,stroke).detach();
                }
                if(stroke.code==scanCode::f12)
                    zhiYian0Status=0;
            break;
            case 6:
                if(stroke.code==scanCode::f11&&!zhiYian2Status){
                    zhiYian2Status=1;
                    std::thread(zhiYian2,context,device,stroke).detach();
                }
                if(stroke.code==scanCode::f12)
                    zhiYian2Status=0;
            break;
            case 7:
                if(stroke.code==scanCode::f11&&!zhiYian3Status){
                    zhiYian3Status=1;
                    std::thread(zhiYian3,context,device,stroke).detach();
                }
                if(stroke.code==scanCode::f12)
                    zhiYian3Status=0;
            break;
        }
        interception_send(context,device,(InterceptionStroke*)&stroke,1);
    }
    interception_destroy_context(context);
}
int main(){
    std::thread(edit).detach();
    std::cout<<0<<std::flush;
    for(;;){
        char c=getch();
        if('0'<=c&&c<='7'){
            mode=c-'0';
            std::cout<<"\r"<<(int)mode<<std::flush;
        }
    }
}
