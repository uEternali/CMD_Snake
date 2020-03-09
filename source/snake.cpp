#include "../include/head.h"
using namespace std;

const int dirc[4][2] = {{-1, 0}, {0, 2}, {1, 0}, {0, -2}};//0 up 1 right 2 down 3 left

_Snake::_Snake(_Screen* S){
    pScreen = S;
    Pixel start1(15, 31, body);
    Pixel start2(15, 30, body);
    P.push_front(start2);
    P.push_front(start1);
    (*pScreen) << start2;
    (*pScreen) << start1;
    Newcandy();
    k = 0; fail = 0; length = 1;
}
_Snake::~_Snake(){
    while(!P.empty()) P.pop_front();
}

void _Snake::Move(){
    static Pixel head1, head2, tail1, tail2;
    head1 = P.front(); P.pop_front();
    head2 = P.front(); P.push_front(head1);
    head1.y += dirc[k][0]; head1.x += dirc[k][1];
    head2.y += dirc[k][0]; head2.x += dirc[k][1];
    P.push_front(head2);
    P.push_front(head1);
    if(fail != 2){
        tail2 = P.back(); P.pop_back();
        tail1 = P.back(); P.pop_back();
        tail2.p = blank; tail1.p = blank;
        (*pScreen) << tail2;
        (*pScreen) << tail1;
    }
    fail = pScreen -> Check(head1);
    (*pScreen) << head2;
    (*pScreen) << head1;
}
void _Snake::Turn(const char& c){
    static int _k;
    if(c == 119 || c == 72) _k = 0;
    else if(c == 100 || c == 77) _k = 1;
    else if(c == 115 || c == 80) _k = 2;
    else if(c == 97 || c == 75) _k = 3;
    else return;
    if(((k ^ _k)&1) == 0) return; //同向
    else k = _k;
}
bool _Snake::Failfeedback(){
    static Pixel head1, head2;
    if(fail == 0) return 0;
    else if(fail == 2){
        if(_SE_) printf("\a");
        length++;
        Newcandy();
        return 0;
    }
    else if(fail == 1){
        head1 = P.front(); P.pop_front();
        head2 = P.front(); P.push_front(head1);
        head1.p = wrong_body;
        head2.p = wrong_body;
        (*pScreen) << head2;
        (*pScreen) << head1;
        return 1;
    }
    return -1;
}
void _Snake::Newcandy(){
    static Pixel newcandy1(0, 0, candy), newcandy2(0, 0, candy);
    static vector<pair<int, int>> L;
    for(int yi = 0; yi < 30; yi++)
        for(int xi = 0; xi < 60; xi+=2)
            if (pScreen->Check(Pixel(yi, xi, blank)) == 0) 
                L.push_back(pair<int, int>(yi, xi));
    int len = L.size();
    int p = rand()%len;
    newcandy1.y = L[p].first;
    newcandy1.x = L[p].second;
    newcandy2.y = newcandy1.y;
    newcandy2.x = newcandy1.x + 1;
    (*pScreen) << newcandy1;
    (*pScreen) << newcandy2;
    while(!L.empty()) L.pop_back(); 
}
int _Snake::Getlength() const{
    return length;
}