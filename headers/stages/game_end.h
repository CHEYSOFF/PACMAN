#pragma once
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

#include "../variables.h"
#include "../leaderboard.h"
#include "../screen.h"

using namespace std;

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