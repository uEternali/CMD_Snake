#include <conio.h>
#include "../include/head.h"
using namespace std;
int _SE_ = 1;
int main(){
    system("chcp 65001");
    SetConsoleTitleA("Snake🐍!");
    srand(time(NULL));
    _Screen Screen;
    Screen.Initscreen(); //初始化屏幕
    Screen.Initmap();
    _Operationboard Operationboard(&Screen);
    int triggerfeedback = 3;
    while(1){
        Screen.Display();
        if(kbhit()){//按键触发
                int c = _getch();
                if(c == 0 || c == 0xE0) c = _getch();
                //printf("The user presses a key.[%c %d]\n", c, c);
                Operationboard.Change(c); //按键触发后转向
                triggerfeedback = Operationboard.Trigger(c);
        }
        if(triggerfeedback == 0){
            triggerfeedback = 3;
            Screen.Initmap();
            Operationboard.Highlight(0);
            _Snake Snake(&Screen);//生成位于屏幕上的🐍和🍬
            _Scoreboard Scoreboard(&Screen);//生成位于屏幕上的计分板
            bool endfg = 0;
            while(1){
                endfg = Snake.Failfeedback();//响应上一步移动后的反馈（撞墙，撞身体，吃糖）
                Scoreboard.Update(Snake);//更新计分板
                if(endfg) Scoreboard.Gameover();//打印失败
                Screen.Display();        //打印画面
                if(endfg) break;//游戏结束
                if(kbhit()){//按键触发
                    int c = _getch();
                    if(c == 0 || c == 0xE0) c = _getch();
                    //printf("The user presses a key.[%c %d]\n", c, c);
                    Snake.Turn(c);//按键触发后转向
                }
                Sleep(30);
                Snake.Move();//🐍向预定方向移动
            }
            Operationboard.Highlight(1);
        }
        else if(triggerfeedback == 2) break;
    }
    return 0;
}