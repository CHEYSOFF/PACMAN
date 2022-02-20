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

// #include "headers/game/threads/door.h"
// #include "headers/game/threads/cherry.h"
// // #include "headers/game/threads/ghosts.h"
// #include "headers/game/threads/player.h"
// #include "headers/game/screen.h"
// // #include "headers/startvar.h"
// #include "headers/point.h"


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
int dir;
int curscore=0;
int onesleft=299;
const int he = 31;
const int wi = 28;
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
int char_he=7;
int char_wi=5;
int col_k=0;
string let_col[4]={BLU, RED, YEL, GRE};
string num_col[3]={RED, YEL, GRE};
static atomic< bool > menuContinue = true;
int x_ch=2;//коэффицент растяжения букв по горизонтали (при изменение коэффицента с 2 все ломается :( )
int y_ch=1;//коэффицент растяжения букв по вертикали
int x_nu=5;
int y_nu=3;


vector< vector< bool > > char_w={   {0, 0, 0, 0, 0},
                                    {1, 0, 1, 0, 1},
                                    {1, 0, 1, 0, 1},
                                    {1, 0, 1, 0, 1},
                                    {1, 0, 1, 0, 1},
                                    {0, 1, 0, 1, 0},
                                    {0, 0, 0, 0, 0}
                                };

vector< vector< bool > > char_a={   {0, 0, 0, 0, 0},
                                    {0, 0, 1, 0, 0},
                                    {0, 1, 0, 1, 0},
                                    {0, 1, 1, 1, 0},
                                    {0, 1, 0, 1, 0},
                                    {0, 1, 0, 1, 0},
                                    {0, 0, 0, 0, 0}
                                };

vector< vector< bool > > char_s={   {0, 0, 0, 0, 0},
                                    {0, 1, 1, 1, 0},
                                    {0, 1, 0, 0, 0},
                                    {0, 1, 1, 1, 0},
                                    {0, 0, 0, 1, 0},
                                    {0, 1, 1, 1, 0},
                                    {0, 0, 0, 0, 0}
                                };
                                
vector< vector< bool > > char_d={   {0, 0, 0, 0, 0},
                                    {0, 1, 1, 0, 0},
                                    {0, 1, 0, 1, 0},
                                    {0, 1, 0, 1, 0},
                                    {0, 1, 0, 1, 0},
                                    {0, 1, 1, 0, 0},
                                    {0, 0, 0, 0, 0}
                                };

vector< vector< vector< bool > > > nums={

                                    {
                                        {0, 0, 0, 0, 0},
                                        {0, 0, 0, 1, 0},
                                        {0, 0, 1, 1, 0},
                                        {0, 1, 0, 1, 0},
                                        {0, 0, 0, 1, 0},
                                        {0, 0, 0, 1, 0},
                                        {0, 0, 0, 0, 0}
                                    },

                                    {
                                        {0, 0, 0, 0, 0},
                                        {0, 0, 1, 0, 0},
                                        {0, 1, 0, 1, 0},
                                        {0, 0, 0, 1, 0},
                                        {0, 0, 1, 0, 0},
                                        {0, 1, 1, 1, 0},
                                        {0, 0, 0, 0, 0}
                                    },

                                    {
                                        {0, 0, 0, 0, 0},
                                        {0, 1, 1, 1, 0},
                                        {0, 0, 0, 1, 0},
                                        {0, 1, 1, 1, 0},
                                        {0, 0, 0, 1, 0},
                                        {0, 1, 1, 1, 0},
                                        {0, 0, 0, 0, 0}
                                    }


};

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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

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

void dopen(){
    for(int j=11;j<=16;j++) arr[12][j]=0;
}

void dclose(){
    for(int j=11;j<=16;j++) arr[12][j]=1;
}

void door_time(){
    while(gameContinue){

        dopen();
        Sleep(dop);
        if(curtime<cycle*3) curtime+=dop;
        
        dclose();
        Sleep(dcl);
        if(curtime<cycle*3) curtime+=dcl;



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
                    }
                    
                    break;
                // case 219:
                // case 251:
                case 83:
                case 115:
                    if(arr[gam.i+1][gam.j]!=1){
                        dir=2;
                    }
                    
                    break;
                // case 212:
                // case 244:
                // case 192:
                case 65:
                case 97:
                    if( (gam.j>=0 && arr[gam.i][gam.j-1]!=1) || (gam.i==14 && gam.j==0 )  ){
                        dir=3;
                    }
                    
                    break;
                // case 194:
                // case 226:
                case 68:
                case 100:
                    if( (gam.j+1<wi && arr[gam.i][gam.j+1]!=1) || (gam.i==14 && gam.j==wi-1) ){
                        dir=1;
                    }
                    
                    break;
                case 27:
                    gameContinue=0;
                    death=-1;
                    break;
            }


    }
}

bool cango(point p){
    if( (arr[p.i][p.j]!=1 && !(p.i==12 && p.j>=11 && p.j<=16) ) || (p.i==14 && ( p.j==-1 || p.j==wi )  ) ) return true;
    return false;
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
}

void pacmandeath(){
    if(se_mon==gam || fi_mon==gam){
        gameContinue=0;
        death=1;

        
        return;
    }
}

bool valid(point a){
    if(a.i<he && a.i>=0 && a.j<wi && a.j>=0 && arr[a.i][a.j]!=1) return 1;
    else return 0; 
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

void character(){
    dir=1; //0 вверх | 1 вправо | 2 вниз | 3 влево

    while (gameContinue){
        
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


        Sleep(wait_gamer);
    }
    return;
}

int margin(string s){
    return (win_wi/pix_char-s.size())/2;
}

void cen_out(string s){

    int ot= margin(s);
    for(int i=0;i<ot;i++){
        cout<<" ";
    }

    cout<<s;


}

void updateScreen(){
    int i, j;
    
    for(i=0;i<he+4+3;i++) cout<<UP;

    cout<<GRA;
    cout<<" +=";
    for(int i=0; i<wi*2-1; i++) cout<<'=';
    cout<<"=+ ";
    cout<<'\n';
    for(i=0;i<he;i++){

        cout<<GRA<<mar_left;
        for(j=0;j<wi;j++){
            cout<<GRA;
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
            if(!outed){


                if(arr[i][j]==0) cout<<GRA<<"."<<" ";
                else if(arr[i][j]==1) cout<<PUR<<"H"<<" "; 
                else if(arr[i][j]==2) cout<<GRE<<"*"<<" ";
                else if(arr[i][j]==5) cout<<RED<<BOLD<<"6"<<" ";


            }
            
            
        }
        cout<<GRA<<"| ";
        cout<<'\n';
    }
    
    cout<<GRA;
    cout<<GRA<<" +=";
    for(int i=0; i<2*wi-1; i++) cout<<'=';
    cout<<"=+ ";

    cout<<'\n';
    cout<<GRA<<mar_left;
    cout<<'\n';
    cout<<GRA<<mar_left;
    cout<<YEL;
    string ys="YOUR SCORE="+to_string(curscore);
    cen_out(ys);
    cout<<'\n';
    cout<<GRA<<mar_left;
    string ll="LIVES LEFT: "+to_string(lives);
    cout<<RED;
    cen_out(ll);

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
}

void scr_upd_tim(){
    while(gameContinue){
        updateScreen();
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

point fastest_way(point s, point e){
    queue< point > q;
    q.push (s);
    point tmp_p;
    tmp_p.i=0;
    tmp_p.j=0;
    if(s==e) return tmp_p;
    
    vector< vector<point> > used(he, vector< point >(wi, u) );

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




string space_suf_del(string s){
    int k=s.size();
    for(int i=s.size()-1;i>=0;i--){
        if(s[i]==' '){
            k=i;
        }
        else{
            break;
        }
    }
    s=s.substr(0, k);
    return s;
}

void leader_board(string p_name){
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE) );
    ifstream fin;
    
    fin.open("leaderboard.txt");
    
    
    
    vector< pair< int, string >  > results;
    string s;
    while(getline(fin, s)){
        string name;
        int score;
        string rev=s;
        reverse(rev.begin(), rev.end());
        auto tm=rev.find(' ');
        if(tm==std::string::npos) continue;
        int ind_sp=s.size()-tm-1;
        name=s.substr(0, ind_sp);
        cout<<ind_sp<<" "<<name<<endl;
        try{
            score=stoi(s.substr(ind_sp+1, s.size()-ind_sp-1));
        } catch( std::invalid_argument ){
            continue;
        }
        
        results.push_back({score, name});

    }
    fin.close();
    results.push_back( {curscore, p_name} );

    vector< pair< int, string >  > results_tmp;

    for(int i=0; i<results.size(); i++){
        string tmstr=results[i].second;
        if(tmstr.size()>=3 && tmstr.substr( tmstr.size()-3, 3 ) == "..." ){
            tmstr=tmstr.substr(0, tmstr.size()-3);
        }
        tmstr=space_suf_del(tmstr);
        results[i].second=tmstr;
        if(results[i].second.size()!=0){
            results_tmp.push_back(results[i]);
        }
    }

    results=results_tmp;
    

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

    cout<<BLU;
    string eyn="ENTER YOUR NAME:";
    cen_out(eyn);
    string ut10s="(up to 10 symbols)";
    cout<<'\n';
    cout<<YEL;
    cen_out(ut10s);
    cout<<BLU;
    cout<<'\n';
    int name_mar=margin(eyn);
    for(int i=0;i<name_mar;i++) cout<<' ';
    cout<<flush;
    string p_name;
    getline(cin, p_name);
    

    while(p_name.size()==0){

        string nits="Name is too short";
        system("cls");
        cout<<RED;
        cen_out(nits);
        cout<<'\n';
        cout<<BLU;
        string eyn="ENTER YOUR NAME:";
        cen_out(eyn);
        string ut10s="(up to 10 symbols)";
        cout<<'\n';
        cout<<YEL;
        cen_out(ut10s);
        cout<<BLU;
        cout<<'\n';
        int name_mar=margin(eyn);
        for(int i=0;i<name_mar;i++) cout<<' ';
        cout<<flush;
        getline(cin, p_name);
        if(p_name.size()>=10){
            p_name = p_name.substr( 0, 10 )+"...";
        }
        
    }


    if(p_name.size()>=10){
        p_name = p_name.substr( 0, 10 )+"...";
    }
    leader_board(p_name);
    system("cls");

    string go="GAME OVER";
    cout<<RED;
    cen_out(go);
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
    cen_out(cl);
    int mar_lb=margin(cl);

    cout<<'\n'<<'\n';


    int malen=0;

    for(int i=0;i<lbsize;i++){
        malen=max(malen, int( lbscore[i].first.size() )  );
    }

    for(int i=0;i<lbsize;i++){
        for(int i=0;i<mar_lb; i++) cout<<' ';
        cout<<BLU<<lbscore[i].first;

        for(int j=0;j<malen-lbscore[i].first.size(); j++){
            cout<<" ";
        }

        cout<<"   "<<GRE<<lbscore[i].second<<'\n';
    }

    cout<<'\n';
    cout<<'\n';

    cout<<flush;



    getch();
    

}

void threads_game(){

    thread cha(character);
    thread inp(input_key);
    thread door(door_time);
    thread screen(scr_upd_tim);
    thread mon(mon_thr);
    thread cherry(cherry_spawn);

    screen.join();
    cherry.detach();
    door.detach();
    cha.detach();
    inp.detach();
    mon.detach();

}

void var_reset(){
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE) );
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

void wait_for_input(){

    if(getch()){
        menuContinue=false;
        return;
    }

}

void letters_print(){

    

    for(int i=0;i<char_he;i++){
        string www="";
        for(int j=0;j<char_wi;j++){
            if(char_w[i][j]==1){
                for(int tt=0;tt<x_ch;tt++) www+="*";
            }
            else for(int tt=0;tt<x_ch;tt++) www+=" ";
        }
        cout<<let_col[col_k%4];
        for(int kkk=0; kkk<y_ch;kkk++){
            for(int j=0;j<23;j++) cout<<" ";
            cout<<www;
            cout<<'\n';
        }
        
        
    }

    for(int i=0;i<char_he;i++){

        string aaa="";
        for(int j=0;j<char_wi;j++){
            if(char_a[i][j]==1){
                for(int tt=0;tt<x_ch;tt++) aaa+="*";
            }
            else for(int tt=0;tt<x_ch;tt++) aaa+=" ";
        }
        

        string sss="";
        for(int j=0;j<char_wi;j++){
            if(char_s[i][j]==1){
                for(int tt=0;tt<x_ch;tt++) sss+="*";
            }
            else for(int tt=0;tt<x_ch;tt++) sss+=" ";
        }
        


        string ddd="";
        for(int j=0;j<char_wi;j++){
            if(char_d[i][j]==1){
                for(int tt=0;tt<x_ch;tt++) ddd+="*";
            }
            else for(int tt=0;tt<x_ch;tt++) ddd+=" ";
        }
        
        for(int kkk=0; kkk<y_ch;kkk++){
            cout<<let_col[(col_k+1)%4];
            for(int j=0;j<11;j++) cout<<" ";
            cout<<aaa;
            cout<<"  ";
            cout<<let_col[(col_k+2)%4];
            cout<<sss;
            cout<<"  ";
            cout<<let_col[(col_k+3)%4];
            cout<<ddd;
            cout<<'\n';
        }
        

    }
    cout<<'\n';



    cout<<flush;
    Sleep(500);

}

void text_print(){

    while(menuContinue){
        system("cls");
        cout<<'\n';
        cout<<'\n';
        string pabts="Press any button to start";
        string C="CONTROLS";
        cout<<RED;
        cen_out(pabts);
        cout<<'\n';
        cout<<'\n';
        cout<<'\n';
        cout<<CYA;
        cen_out(C);
        cout<<'\n';
        cout<<'\n';
        letters_print();
        col_k++;
        col_k%=4;
    }
    
}

void threads_menu(){
    
    thread txt(text_print);
    thread inp(wait_for_input);

    inp.join();
    txt.detach();

}

void transition(){

    for(int kt=2;kt>=0;kt--){
        updateScreen();

        for(int i=0;i<32;i++){
            cout<<UP;
        }

        for(int i=0;i<char_he;i++){
            string nu="";
            for(int j=0;j<char_wi;j++){
                if(nums[kt][i][j]==1){
                    for(int tt=0;tt<x_nu;tt++) nu+="@";
                }
                else for(int tt=0;tt<x_nu;tt++) nu+=RIG;
            }
            cout<<num_col[kt];
            for(int kkk=0; kkk<y_nu;kkk++){
                for(int j=0;j<18;j++) cout<<RIG;
                cout<<nu;
                cout<<'\n';
            }
            cout<<flush;
            
            
        }
        Sleep(1000);
    }
    

    

}

void start_menu(){

    
    threads_menu();


}

int main(){
    
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

    // убирает скролл бар
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
    //

    // задает размер окна
    HWND hwnd = GetConsoleWindow();
    ShowScrollBar(hwnd, SB_BOTH, 0);
    RECT ConsoleRect;
    GetWindowRect(hwnd, &ConsoleRect);
    MoveWindow(hwnd, ConsoleRect.left, ConsoleRect.top, win_wi, win_he, TRUE);
    //
    
    var_reset();
    start_menu();
    
    while(lives!=0){
        var_reset();
        transition();
        var_reset();

        system("cls");
        cout<<flush;
        updateScreen();
        
        
        
        
        threads_game();

        if(death==-1){
            break;
        }

        lives--;

        for(int i=0;i<5;i++) cout<<UP;
        cout<<'\n';
        cout<<'\n';
        
        string yd="YOU DIED";
        cout<<GRA<<mar_left;
        cout<<RED;
        cen_out(yd);
        cout<<"     ";//чтобы закрыть предыдущий текст :(
        cout<<'\n';
        cout<<GRA<<mar_left;
        cout<<RED;
        string ll="LIVES LEFT: "+to_string(lives);
        cen_out(ll);
        cout<<'\n';
        cout<<flush;
        Sleep(1000);

    }
    system("cls");
    leave();
    
    return 0;

    



    
    /*
      119-W
      97-A
      115-S
      100-D
      27-ESC
    */

    


    
    return 0;


}