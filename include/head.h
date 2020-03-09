#include <queue>
#include <ctime>
#include <string>
#include <iostream>
#include <windows.h>
extern int _SE_;
// Color definition intensity
const int Fblack =  0 | FOREGROUND_INTENSITY;
const int Fblack_ = 0;
const int Fgreen =  FOREGROUND_GREEN | FOREGROUND_INTENSITY;
const int Fblue =   FOREGROUND_BLUE | FOREGROUND_INTENSITY;
const int Fred =    FOREGROUND_RED | FOREGROUND_INTENSITY;
const int Fyellow = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
const int Fcyan =   FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
const int Fwhite =  FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;

const int Bblack =  0 | BACKGROUND_INTENSITY;
const int Bred =    BACKGROUND_RED | BACKGROUND_INTENSITY;
const int Byellow = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
const int Bcyan =   BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
const int Bwhite =  BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;

struct Pattern{
    int Fcolor, Bcolor;
    std::string ch;
    Pattern(){};
    Pattern(const int& _Fcolor, const int& _Bcolor, const std::string& _ch):
        Fcolor(_Fcolor), Bcolor(_Bcolor), ch(_ch){}
    bool operator == (const Pattern& rtm) const{
        return Fcolor == rtm.Fcolor && Bcolor == rtm.Bcolor && ch == rtm.ch;
    }
};
// Pattern definition
const Pattern border(Fwhite, Bwhite, "█");
const Pattern blank(Fblack, Bblack, " ");
const Pattern body(Fyellow, Byellow, "█");
const Pattern wrong_body(Fred, Bred, "█");
const Pattern candy(Fcyan, Bcyan, "█");
const Pattern CB_word(Fcyan, Bblack, " ");
const Pattern RB_word(Fred, Bwhite, " ");

struct Pixel
{
    int y, x;
    Pattern p;
    Pixel(){};
    Pixel(const int& _y, const int& _x, const Pattern& _p):
        y(_y), x(_x), p(_p){}
};

class _Screen{
private:
    HANDLE hOutput;
    Pattern Map[30][100];
    void Cursorgoto(int, int);
public:
    _Screen();
    ~_Screen();
    void operator << (const Pixel&);
    void Display();
    void Fillblank(const int& ,const int& );
    int Check(const Pixel&); //0 none; 1 border || body; 2 candy
    void Initscreen();
    void Initmap();
};

class _Snake{//xi 2~57 yi 1 ~ 28
private:
    std::deque<Pixel> P;
    int k, fail, length;
    _Screen* pScreen;
public:
    _Snake(_Screen*);
    ~_Snake();
    void Move();
    void Turn(const char&);
    bool Failfeedback();
    void Newcandy();
    int Getlength() const;
};

class _Scoreboard{
private:
    _Screen* pScreen;
    Pixel Text[12], Score[8], Over[10];
    void Formatscore(const int&);
public:
    _Scoreboard(_Screen*);
    void Update(const _Snake &);
    void Gameover();
};

class _Operationboard{
private:
    _Screen* pScreen;
    Pixel Option[3][14]; // Newgame, SE, Exit
    int k;
public:
    _Operationboard(_Screen*);
    void Highlight(const bool&);
    void Change(const char&);
    int Trigger(const char&);//0 newgame; 1 se 2 exit
};