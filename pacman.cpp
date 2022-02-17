#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <Winuser.h>
#include <time.h>
#include <thread>
#include <string>
#include <queue>
#include <algorithm>
#include <atomic>
#include <chrono>
#include <random>
#include <fstream>

using namespace std;

// https://habr.com/ru/post/119436/
#define PUR "\033[95m"
#define BLU "\033[94m"
#define CYA "\033[96m"
#define GRE "\033[92m"
#define YEL "\033[93m"
#define RED "\033[91m"
#define GRA "\033[0m"
#define BOLD "\033[1m" // не работает в консоли
#define RIG "\033[1C"
#define UP "\033[F"
// #define norm tput sgr0

#define GRAb "\033[47"



mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct point{

    int i, j;

};

point operator+(point a, point b){
    point tmp;
    tmp.i=a.i+b.i;
    tmp.j=a.j+b.j;
    return tmp;
}
point operator-(point a, point b){
    point tmp;
    tmp.i=a.i-b.i;
    tmp.j=a.j-b.j;
    return tmp;
}
bool operator==(point a, point b){
    return (a.i==b.i && a.j==b.j);
}
bool operator!=(point a, point b){
    return (a.i!=b.i || a.j!=b.j);
}



point u;
//300 очков всего
// bool door=1;//0 открыта 1 закрыта
int dir;
int curscore=0;
int onesleft=299;
const int he = 31;//26
const int wi = 28;//26
const int dop=2000;
const int dcl=10000;
atomic< int > curtime=0;
const int cycle=dop+dcl;
const int wait_ghost=400;
const int wait_gamer=300;
const int cherrySleep=40000;
point fi_mon;
point se_mon;
vector< pair< string, int > > lbscore;
int lbsize=10;
int lives=3;
const int mo_co=2;
vector< bool > monplaced(mo_co+1, 0);
int out_le=wi;// для центрирования вывода
string mar_left=" | ";
static atomic< bool > gameContinue = true;
atomic< int > death;//1 съеден монстром || -1 лив || 0 жив
int win_wi=460;
int win_he=650;
int pix_char=8;
point gam;


int arr[he][wi]={   {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                    {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
                    {1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1},
                    {1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1},
                    {1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1},
                    {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
                    {1, 2, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 2, 1},
                    {1, 2, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 2, 1},
                    {1, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 1},
                    {1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1},
                    {1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1},
                    {1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1},
                    {1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1},
                    {1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 0, 0, 0, 0, 0, 0, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1},
           /* 14 */ {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0, 0, 0, 0, 0, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
                    {1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 0, 0, 0, 0, 0, 0, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1},
                    {1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1},
                    {1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1},//16 13
                    {1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1},
                    {1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1},
                    {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
                    {1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1},
                    {1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1},
                    {1, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 1},
                    {1, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 1},
                    {1, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 1},
                    {1, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 1},
                    {1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1},
                    {1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1},
                    {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
                    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    };

int ones[he][wi]={   {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                    {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
                    {1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1},
                    {1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1},
                    {1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1},
                    {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
                    {1, 2, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 2, 1},
                    {1, 2, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 2, 1},
                    {1, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 1},
                    {1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1},
                    {1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1},
                    {1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1},
                    {1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1},
                    {1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 0, 0, 0, 0, 0, 0, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1},
           /* 14 */ {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0, 0, 0, 0, 0, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
                    {1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 0, 0, 0, 0, 0, 0, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1},
                    {1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1},
                    {1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1},
                    {1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1},
                    {1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1},
                    {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
                    {1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1},
                    {1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1},
                    {1, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 1},
                    {1, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 1},
                    {1, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 1},
                    {1, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 1},
                    {1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1},
                    {1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1},
                    {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
                    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    };

int zeroes[he][wi]={   {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                    {1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
                    {1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
                    {1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
                    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                    {1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1},
                    {1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1},
                    {1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
                    {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1},
                    {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1},
                    {1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1},
                    {1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1},
                    {1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1},
           /* 14 */ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1},
                    {1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1},
                    {1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1},
                    {1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1},
                    {1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1},
                    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                    {1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
                    {1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
                    {1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1},
                    {1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1},
                    {1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1},
                    {1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
                    {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
                    {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
                    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    };

int margin(string s){
    return (win_wi/pix_char-s.size())/2;
}

void centerized_out(string s){

    // cout<<mar_left;

    int ot= margin(s);
    for(int i=0;i<ot;i++){
        cout<<" ";
    }

    cout<<s;


}

bool cango(point p){
    if( (arr[p.i][p.j]!=1 && !(p.i==12 && p.j>=11 && p.j<=16) ) || (p.i==14 && ( p.j==-1 || p.j==wi )  ) ) return true;
    return false;
}

void gotoxy(short x, short y) {
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD) { x, y } );
}

void updateScreen(){
    int i, j;
    // cout<<endl;
    
    for(i=0;i<he+4+3;i++) cout<<UP;

    cout<<GRA;
    cout<<" +=";
    for(int i=0; i<wi*2-1; i++) cout<<'=';
    cout<<"=+ ";
    cout<<'\n';
    // string s(he);
    // cout<<'\n';
    for(i=0;i<he;i++){

        cout<<GRA<<mar_left;
        for(j=0;j<wi;j++){
            // tput sgr0;
            cout<<GRA;
            // cout<<"\033[7m";
            bool outed=0;
            point curpo;
            curpo.i=i;
            curpo.j=j;
            if(fi_mon!=u && fi_mon==curpo){
                cout<<CYA<<BOLD<<"@"<<" ";
                outed=1;
                continue;
            }
            else if(se_mon!=u && se_mon==curpo){
                cout<<BLU<<BOLD<<"@"<<" ";
                outed=1;
                continue;
            }
            else if(gam==curpo){
                cout<<YEL<<BOLD<<"C"<<" ";
                outed=1;
                continue;
            }
            // for(int mon_num=0; mon_num<monster_pos.size(); mon_num++){
            //     if(monster_pos[mon_num]==curpo){
            //         cout<<CYA<<"@"<<" ";
            //         outed=1;
            //         break;
            //     }
            // }
            if(!outed){


                if(arr[i][j]==0) cout<<GRA<<"."<<" ";
                else if(arr[i][j]==1) cout<<PUR<<"H"<<" "; 
                else if(arr[i][j]==2) cout<<GRE<<"*"<<" ";
                else if(arr[i][j]==5) cout<<RED<<BOLD<<"6"<<" ";


            }
            
            
        }
        // cout<<"                       ";
        cout<<GRA<<"| ";
        cout<<'\n';
    }
    // cout<<mar_left;
    // cout<<'\n';
    // cout<<'\n';
    
    cout<<GRA;
    // cout<<'\n';
    // cout<<GRA<<mar_left;
    cout<<GRA<<" +=";
    for(int i=0; i<2*wi-1; i++) cout<<'=';
    cout<<"=+ ";

    cout<<'\n';
    cout<<GRA<<mar_left;
    cout<<'\n';
    cout<<GRA<<mar_left;
    cout<<YEL;
    string ys="YOUR SCORE="+to_string(curscore);
    centerized_out(ys);
    cout<<'\n';
    cout<<GRA<<mar_left;
    string ll="LIVES LEFT: "+to_string(lives);
    cout<<RED;
    centerized_out(ll);

    cout<<'\n';
    for(int i=0;i<1;i++){
        cout<<GRA<<mar_left;
        cout<<'\n';
    }
    cout<<GRA;
    cout<<" +=";
    for(int i=0; i<wi*2-1; i++) cout<<'=';
    cout<<"=+ ";

    for(int i=0;i<4;i++) cout<<UP;
    for(int i=0;i<4;i++){
        
        for(int i=0;i<wi*2+mar_left.size()-1;i++) cout<<RIG;
        cout<<GRA<<" | ";
        cout<<'\n';
    }



    cout<<flush;
    // cout<<"YOUR SCORE="<<curscore<<'\n';
    // cout<<flush;
}


void addScore(point p){
    if(arr[p.i][p.j]==2){
        curscore+=1;
        arr[p.i][p.j]=0;
        onesleft--;
        if(onesleft<=0){
            onesleft=299;
            for(int i=0;i<he;i++){
                for(int j=0;j<wi;j++){
                    if(!(i==12 && j>=11 && j<=16) ) arr[i][j]=ones[i][j];
                }
            }
        }
    }
    else if(arr[p.i][p.j]==5){
        curscore+=5;
        arr[p.i][p.j]=0;
    }
    // else if(arr[p.i][p.j]==5)
}

void pacmandeath(){
    if(se_mon==gam || fi_mon==gam){
        gameContinue=0;
        death=1;

        
        return;
    }
}

void goup(){
    
    point p=gam;
    p.i--;

    p.i+=he;
    p.j+=wi;

    p.i%=he;
    p.j%=wi;

    if( cango(p) ){
        addScore(p);
        
        gam=p;
        pacmandeath();
        return;
    }


    
}

void godown(){
    point p=gam;
    p.i++;

    p.i+=he;
    p.j+=wi;

    p.i%=he;
    p.j%=wi;

    if(cango(p) ){
        addScore(p);
          
        gam=p;
        pacmandeath(); 
        return;
    }

}

void goleft(){
    point p=gam;
    p.j--;

    p.i+=he;
    p.j+=wi;

    p.i%=he;
    p.j%=wi;

    if(cango( p ) ){
        
        addScore(p);
        gam=p;
        pacmandeath();
        return;
    }
    


    
}

void goright(){

    point p=gam;
    p.j++;

    p.i+=he;
    p.j+=wi;

    p.i%=he;
    p.j%=wi;

    if(cango( p ) ){
        
        addScore(p);
        gam=p;
        pacmandeath();
        return;


    }

    


    
}

bool valid(point a){
    if(a.i<he && a.i>=0 && a.j<wi && a.j>=0 && arr[a.i][a.j]!=1) return 1;
    else return 0; 
}

point fastest_way(point s, point e){
    queue< point > q;
    q.push (s);
    point tmp_p;
    tmp_p.i=0;
    tmp_p.j=0;
    if(s==e) return tmp_p;
    
    vector< vector<point> > used(he, vector< point >(wi, u) );
    
    // used[s.i][s.j]=0;

    point hod[4];

    point tmp;

    tmp.i=-1;
    tmp.j=0;
    hod[0]=tmp;

    tmp.i=0;
    tmp.j=1;
    hod[1]=tmp;

    tmp.i=1;
    tmp.j=0;
    hod[2]=tmp;

    tmp.i=0;
    tmp.j=-1;
    hod[3]=tmp;


    for(;!q.empty();){

        point from=q.front();
        q.pop();

        for(int kt=0; kt<4;kt++){

            point to=from+hod[kt];
            if( to.i==14 && to.j==-1 ){
                to.j=27;
            }
            else if( to.i==14 && to.j==28 ){
                to.j=0;
            }
            

            if( valid(to) && used[to.i][to.j]==u){
                used[to.i][to.j]=from;
                q.push(to);


                if(to==e){

                    point nev=to;
                    for(;;){
                        
                        if(nev==u) return u;
                        
                        if(used[nev.i][nev.j]==s){
                            point ans=nev-s;
                            return(ans);
                        }

                        nev=used[nev.i][nev.j];
                    }

                }



            }


        }



    }

        
    return u;
}

void mon_bfs(){

    point mon_dir=fastest_way(fi_mon, gam );
    if(mon_dir==u){
        return;
    }
    point newpos=fi_mon+mon_dir;
    fi_mon=newpos;
    if( newpos==gam ){
        gameContinue=0;
        death=1;

        
        return;
    }
    

}

point next_point(int dir){
    point x;
    switch (dir){

        case 0:
            x.i=-1;
            x.j=0;
            break;
        case 1:
            x.i=0;
            x.j=1;
            break;
        case 2:
            x.i=1;
            x.j=0;
            break;
        case 3:
            x.i=0;
            x.j=-1;
            break;



    }
    return x;
}

bool sec_mon_valid(point p){
    if( valid(p) && !(p.i==14 && ( p.j==5 || p.j==22 )) && !(p.i==4 && (p.j==6 || p.j==21) ) && !(p.i==5 && (p.j==5 || p.j==22) ) ) return 1;
    return 0;
}

void mon_left(int &dir){
    
    
    point next=se_mon + next_point(dir);
    if( !sec_mon_valid(next) ){
        dir=(dir-1+4)%4; 
        next=se_mon + next_point(dir);
        if(!sec_mon_valid(next)){
            dir=(dir+2+4)%4; 
        }
    }
    
    


    next=se_mon + next_point(dir);

    se_mon=next;
    if(se_mon==gam){
        gameContinue=0;
        death=1;

        
        return;
    }
    


}

void mon_thr(){
    
    // bool mon2placed=0;
    int m_l_dir=0;//0 вверх | 1 вправо | 2 вниз | 3 влево
    while(gameContinue){
        
        if(curtime >= (cycle)*0 ){
            if( !monplaced[1] ){
                fi_mon.i=14;
                fi_mon.j=12;
                monplaced[1]=1;
            }
            
            mon_bfs();
        }
        
        if(curtime >= (cycle)*1 ){

            if( !monplaced[2] ){
                se_mon.i=14;
                se_mon.j=11;
                monplaced[2]=1;
            }
            
            mon_left(m_l_dir);
            
        } 
        Sleep(wait_ghost);
        

    }

}

void dopen(){
    for(int j=11;j<=16;j++) arr[12][j]=0;
}

void dclose(){
    for(int j=11;j<=16;j++) arr[12][j]=1;
}

void character(){
    // cout<<-1;
    dir=1; //0 вверх | 1 вправо | 2 вниз | 3 влево

    while (gameContinue){
        

        // BYTE helpar[256];
        // for(int i=0;i<256;i++)helpar[i]=0; 
        // GetKeyboardState(helpar);
        // int p;
        // for (int _i = 0; _i < 5; _i++)
        // for(int i=0;i<256;i++){
        //     // cout<<helpar[i]<<" ";
        //     if((int)helpar[i] & 0x8000) p=i;
        // }
        
        // // cout << ((short)GetKeyState('D') & 0x8000) << endl;
        // if ((short)GetKeyState('W') & 0x8000)
        //         goup();
        // else if ((short)GetKeyState('S') & 0x8000)
        //         godown();
        // else if ((short)GetKeyState('A') & 0x8000)
        //         goleft();
        // else if ((short)GetKeyState('D') & 0x8000)
        //         goright();
        // else if ((short)GetKeyState(VK_ESCAPE) & 0x8000)
        // {
        //         gameContinue=0;
        //         return;
        // }
        


        switch(dir){
            case 0:
                goup();
                break;
            case 2:
                godown();
                break;
            case 3:
                goleft();
                break;
            case 1:
                goright();
                break;
        }





        // updateScreen();
        // SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE) ,ENABLE_ECHO_INPUT);
        // BlockInput(true);
        Sleep(wait_gamer);
        // BlockInput(false);
        // SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE) ,ENABLE_ECHO_INPUT);
        // if (!gameContinue.is_lock_free()) return;
    }
    return;
}

void door_time(){
    while(gameContinue){

        dopen();
        // door=0;
        // updateScreen();
        Sleep(dop);
        if(curtime<cycle*3) curtime+=dop;
        
        // door=1;
        dclose();
        // updateScreen();
        Sleep(dcl);
        if(curtime<cycle*3) curtime+=dcl;

        // if (!gameContinue.is_lock_free()) return;


    }
}

void scr_upd_tim(){
    while(gameContinue){
        updateScreen();
        // Sleep(10);
        // if (!gameContinue.is_lock_free()) return;
    }
}

void input_key(){
    while(gameContinue){
        
    
        switch(getch()){
                // case 246:
                // case 214:
                case 87:
                case 119:
                    if(arr[gam.i-1][gam.j]!=1){
                        dir=0;
                        // FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE) );
                    }
                    
                    break;
                // case 219:
                // case 251:
                case 83:
                case 115:
                    if(arr[gam.i+1][gam.j]!=1){
                        dir=2;
                        // FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE) );
                    }
                    
                    break;
                // case 212:
                // case 244:
                // case 192:
                case 65:
                case 97:
                    if( (gam.j>=0 && arr[gam.i][gam.j-1]!=1) || (gam.i==14 && gam.j==0 )  ){
                        dir=3;
                        // FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE) );
                    }
                    
                    break;
                // case 194:
                // case 226:
                case 68:
                case 100:
                    if( (gam.j+1<wi && arr[gam.i][gam.j+1]!=1) || (gam.i==14 && gam.j==wi-1) ){
                        dir=1;
                        // FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE) );
                    }
                    
                    break;
                case 27:
                    gameContinue=0;
                    death=-1;
                    break;
                    // return;
            }

            // if (!gameContinue.is_lock_free()) return;

    }
}

void leader_board(string p_name){
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE) );
    ifstream fin;
    
    fin.open("leaderboard.txt");
    
    
    
    vector< pair< int, string >  > results;
    string s;
    // cout<<"1";
    while(getline(fin, s)){
        string name;
        int score;
        int ind_sp=s.find(' ');
        name=s.substr(0, ind_sp);
        cout<<ind_sp<<" "<<name<<endl;
        score=stoi(s.substr(ind_sp+1, s.size()-ind_sp-1));
        results.push_back({score, name});

        // cout<<name<<" "<<score<<endl;
    }
    fin.close();
    results.push_back( {curscore, p_name} );
    sort( results.begin(), results.end(), greater<pair<int, string> >() );
    int n=results.size();

    ofstream fout;
    fout.open("leaderboard.txt");
    lbsize=min(lbsize, n);
    for(int i=0;i<lbsize; i++ ){
        lbscore.push_back( {results[i].second, results[i].first} );
        fout<<results[i].second<<" "<<results[i].first<<'\n';
    }
    fout.close();
    return;
    
}

void leave(){
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE) );
    system("cls");
    // cout<<mar_left;
    
    // for(int i=0;i<3;i++){
    //     cout<<'\n';
    // }
    // cout<<flush;

    cout<<RED;
    string eyn="ENTER YOUR NAME:";
    centerized_out(eyn);
    cout<<BLU;
    cout<<'\n';
    cout<<flush;
    // cout<<"ENTER YOUR NAME:"<<'\n'<<BLU<<flush;
    int name_mar=margin(eyn);
    // cout<<"|";
    for(int i=0;i<name_mar;i++) cout<<' ';
    cout<<flush;
    // cout<<name_mar;
    string p_name;
    getline(cin, p_name);
    leader_board(p_name);
    system("cls");

    string go="GAME OVER";
    // cout<<RED<<"GAME OVER"<<'\n';
    cout<<RED;
    centerized_out(go);
    cout<<'\n';
    string ys=", YOUR SCORE=";
    string csstr=to_string(curscore);
    int sc_mar=margin(p_name+ys+csstr+csstr);
    cout<<BLU;
    for(int i=0;i<sc_mar+1;i++) cout<<' ';
    cout<<BLU<<p_name<<CYA<<ys<<GRE<<csstr<<'\n';

    cout<<CYA;
    cout<<'\n';
    string cl="CURRENT LEADERBOARD:";
    centerized_out(cl);
    int mar_lb=margin(cl);

    cout<<'\n'<<'\n';

    // cout<<CYA<<'\n'<<"     "<<"CURRENT LEADERBOARD:"<<'\n'<<'\n';

    int malen=0;

    for(int i=0;i<lbsize;i++){
        malen=max(malen, int( lbscore[i].first.size() )  );
    }
    // cout<<malen<<endl;

    for(int i=0;i<lbsize;i++){
        // cout<<"      ";
        for(int i=0;i<mar_lb; i++) cout<<' ';
        // cout<<BLU;
        cout<<BLU<<lbscore[i].first;

        for(int j=0;j<malen-lbscore[i].first.size(); j++){
            cout<<" ";
        }

        cout<<"   "<<GRE<<lbscore[i].second<<'\n';
    }
    cout<<flush;
    

}

void cherry_spawn(){
    
    while(gameContinue){
        Sleep(cherrySleep);
        static std::uniform_int_distribution<int> uidi(1,he-2+1);
        static std::uniform_int_distribution<int> uidj(1,wi-2+1);
        int ib=uidi(rng);
        int jb=uidj(rng);
        for(int i=jb;i<he;i++){
            for(int j=jb;j<wi;j++){
                if(i>=12 && i<=16 && j>=10 && j<=17) continue;
                if(arr[i][j]==0 /*|| arr[i][j]==2*/){
                    arr[i][j]=5;
                    ib=i;
                    jb=j;
                    i=he;
                    j=wi;
                    
                }
            }
        }
        Sleep(cherrySleep);
        arr[ib][jb]=0;
    }
}

void threads_begin(){

    thread cha(character);
    thread inp(input_key);
    thread door(door_time);
    thread screen(scr_upd_tim);
    thread mon(mon_thr);
    thread cherry(cherry_spawn);
    // thread scor(score_check);

    screen.join();
    // scor.detach();
    cherry.detach();
    door.detach();
    cha.detach();
    inp.detach();
    mon.detach();

}

void var_reset(){
    gam.i=17;
    gam.j=13;
    curtime=0;
    gameContinue=1;
    fi_mon=u;
    se_mon=u;
    death=0;
    arr[gam.i][gam.j]=0;
    for( int i=0; i<mo_co+1; i++ ){
        monplaced[i]=0;
    }

    for(int i=0;i<he;i++){
        for(int j=0;j<wi;j++){
            if(arr[i][j]==5) arr[i][j]=0;
        }
    }

    return;

}


int main(){
    // cout<<GRAb;
    
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    // скрывает курсор
    void* handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO structCursorInfo;
    GetConsoleCursorInfo(handle,&structCursorInfo);
    structCursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo( handle, &structCursorInfo );
    //


    srand(time(NULL));
    
    u.i=-1;
    u.j=-1;

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO scrBufferInfo;
    GetConsoleScreenBufferInfo(hOut, &scrBufferInfo);
    short winHeight = scrBufferInfo.srWindow.Bottom - scrBufferInfo.srWindow.Top + 1;
    short scrBufferWidth = scrBufferInfo.dwSize.X;        
    short scrBufferHeight = scrBufferInfo.dwSize.Y;        
    COORD newSize;
    newSize.X = scrBufferWidth;
    newSize.Y = winHeight;
    SetConsoleScreenBufferSize(hOut, newSize);

    HWND hwnd = GetConsoleWindow();
    ShowScrollBar(hwnd, SB_BOTH, 0);
    RECT ConsoleRect;
    GetWindowRect(hwnd, &ConsoleRect);
    MoveWindow(hwnd, ConsoleRect.left, ConsoleRect.top, win_wi, win_he, TRUE);
    // cin.sync();
    
    // cout<<'\n';

    
    // if (!gameContinue.is_lock_free()) return 10;

    
    while(lives!=0){
        var_reset();

        system("cls");
        cout<<flush;
        updateScreen();
        
        
        
        
        threads_begin();

        if(death==-1){
            break;
        }

        lives--;

        for(int i=0;i<5;i++) cout<<UP;
        cout<<'\n';
        cout<<'\n';
        
        string yd="YOU DIED";
        // cout<<"YOU DIED\n";
        cout<<GRA<<mar_left;
        cout<<RED;
        centerized_out(yd);
        cout<<"     ";//чтобы закрыть предыдущий текст :(
        cout<<'\n';
        cout<<GRA<<mar_left;
        cout<<RED;
        string ll="LIVES LEFT: "+to_string(lives);
        centerized_out(ll);
        cout<<'\n';
        // cout<<"Lives left: "<<lives<<'\n';
        cout<<flush;
        Sleep(3000);

    }
    system("cls");
    leave();
    Sleep(100000);
    return 0;

    



    
    /*
      119-W
      97-A
      115-S
      100-D
      27-ESC
    */

    


    
    return 0;


    // mon.detach();
    // t.detach();
}