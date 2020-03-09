#include "../include/head.h"
using namespace std;

const string text = "-- SCORES --";
const string score = "-      -";
const string over = "Game Over!";
const string start = "          ";
_Scoreboard::_Scoreboard(_Screen* S){
    pScreen = S;
    for(int i = 0; i < 12; i++)
        Text[i] = Pixel(4, i + 74, CB_word);
    for (int i = 0; i < 12; i++)
        Text[i].p.ch = text[i],
        (*pScreen) << Text[i];
    for(int i = 0; i < 8; i++)
        Score[i] = Pixel(6, i + 76, CB_word);
    for(int i = 0; i < 8; i++)
        Score[i].p.ch = score[i];
    for(int i = 0; i < 10; i++)
        Over[i] = Pixel(9, i + 75, CB_word);
    for(int i = 0; i < 10; i++)
        Over[i].p.ch = start[i];
    for(int i = 0; i < 10; i++)
        (*pScreen) << Over[i];
    Formatscore(0);
}

void _Scoreboard::Formatscore(const int& _s){
    static char str[6];
    int s, p, len; s = _s;
    sprintf(str, "%d", s);
    len = strlen(str);
    p = (4 - len + 1)/2;
    for(int i = 0; i < len; i++)
        Score[p + i + 2].p.ch = str[i];
    if(len & 1) Score[p + 2 - 1].p.ch = "0";
    for (int i = 0; i < 8; i++)
        (*pScreen) << Score[i];
}
void _Scoreboard::Update(const _Snake& Snake){
    Formatscore(Snake.Getlength());
}
void _Scoreboard::Gameover(){
    for(int i = 0; i < 10; i++)
        Over[i] = Pixel(9, i + 75, RB_word);
    for(int i = 0; i < 10; i++)
        Over[i].p.ch = over[i];
    for(int i = 0; i < 10; i++)
        (*pScreen) << Over[i];
}