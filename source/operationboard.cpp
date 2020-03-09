#include "../include/head.h"
using namespace std;

const string newgame = "   New Game   ";
const string se[2] =  {"    SE:OFF    ",
                       "    SE: ON    "};
const string exit_ =   "     Exit     ";

_Operationboard::_Operationboard(_Screen* S){
    pScreen = S;
    for(int i = 0; i < 14; i++)
        Option[0][i] = Pixel(24, i + 73, CB_word);
    for(int i = 0; i < 14; i++)
        Option[0][i].p.ch = newgame[i];
    for(int i = 0; i < 14; i++)
        (*pScreen) << Option[0][i];

    for(int i = 0; i < 14; i++)
        Option[1][i] = Pixel(26, i + 73, CB_word);
    for(int i = 0; i < 14; i++)
        Option[1][i].p.ch = se[_SE_][i];
    for(int i = 0; i < 14; i++)
        (*pScreen) << Option[1][i];

    for(int i = 0; i < 14; i++)
        Option[2][i] = Pixel(28, i + 73, CB_word);
    for(int i = 0; i < 14; i++)
        Option[2][i].p.ch = exit_[i];
    for(int i = 0; i < 14; i++)
        (*pScreen) << Option[2][i];
    k = 1;
    Highlight(1);
}
void _Operationboard::Highlight(const bool& fg){
    static string str; str = "";
    for(int i = 0; i < 14; i++)
        str += Option[k][i].p.ch;
    for(int i = 0; i < 14; i++)
        Option[k][i].p = (fg? RB_word:CB_word);
    for(int i = 0; i < 14; i++)
        Option[k][i].p.ch = str[i];
    for(int i = 0; i < 14; i++)
        (*pScreen) << Option[k][i];
}
void _Operationboard::Change(const char& c){
    static int _k; 
    if((c == 119 || c == 72) && k != 0) _k = k - 1;
    else if((c == 115 || c == 80) && k != 2) _k = k + 1;
    else return;
    if(k == _k) return;
    Highlight(0);
    k = _k;
    Highlight(1);
}
int _Operationboard::Trigger(const char& c){
    if(c == 13 || c == 32){
        if(k == 0) return 0;
        else if(k == 1){
            _SE_ ^= 1;
            for(int i = 0; i < 14; i++)
                Option[1][i].p.ch = se[_SE_][i];
            for(int i = 0; i < 14; i++)
                (*pScreen) << Option[1][i];
            return 1;
        }
        else if(k == 2) return 2;
        else return -1;
    }
    return 3;
}