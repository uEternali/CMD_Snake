#include "../include/head.h"
using namespace std;

_Screen::_Screen(){
    hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT rc = {0, 0, 99, 29}; // 坐标位置结构体初始化
    SetConsoleWindowInfo(hOutput, true, &rc);
    COORD dSiz = {100, 30};
    SetConsoleScreenBufferSize(hOutput, dSiz);
    CONSOLE_CURSOR_INFO cur = {1, 0};
    SetConsoleCursorInfo(hOutput, &cur); 
}
_Screen::~_Screen(){
    CloseHandle(hOutput);
}
void _Screen::Cursorgoto(int x, int y){
    COORD pos = {(short)x, (short)y};
    SetConsoleCursorPosition(hOutput, pos);
}

void _Screen::operator << (const Pixel &rtm){
    Map[rtm.y][rtm.x] = rtm.p;
}
void _Screen::Display(){
    Cursorgoto(0, 0);
    for(int yi = 0; yi < 30; yi++){
        for(int xi = 0; xi < 100; xi++){
            SetConsoleTextAttribute(hOutput, Map[yi][xi].Fcolor | Map[yi][xi].Bcolor);
            //cout << Map[yi][xi].ch << endl;
            //printf("%s", Map[yi][xi].ch.c_str());
            WriteConsole(hOutput, Map[yi][xi].ch.c_str(), strlen(Map[yi][xi].ch.c_str()), NULL, 0);
        }
        if(yi < 29) WriteConsole(hOutput, "\n", strlen("\n"), NULL, 0);
    }
    SetConsoleTextAttribute(hOutput, Fwhite | Bblack);
}
void _Screen::Fillblank(const int& y, const int& x){
    (*this) << Pixel(y, x, blank);
}
int _Screen::Check(const Pixel& rtm){
    const Pattern check_point = Map[rtm.y][rtm.x];
    if(check_point == border) return 1;
    else if(check_point == body) return 1;
    else if(check_point == candy) return 2;
    else if(check_point == blank) return 0;
    return -1;
}
void _Screen::Initscreen(){
    for(int yi = 0; yi < 30; yi++)
        for(int xi = 0; xi < 100; xi++)
            (*this) << Pixel(yi, xi, blank);
    
}
void _Screen::Initmap(){
    for(int yi = 0; yi < 30; yi++)
        for(int xi = 0; xi < 60; xi++)
            (*this) << Pixel(yi, xi, blank);
    for(int xi = 0; xi < 60; xi++)
        (*this) << Pixel(0, xi, border),
        (*this) << Pixel(29, xi, border);
    for(int yi = 0; yi < 30; yi++)
        (*this) << Pixel(yi, 0, border),
        (*this) << Pixel(yi, 1, border),
        (*this) << Pixel(yi, 58, border),
        (*this) << Pixel(yi, 59, border);
}