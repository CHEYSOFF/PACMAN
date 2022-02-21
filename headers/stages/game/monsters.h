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
#include <map>

#include "../../point.h"
#include "../../variables.h"
#include "player.h"

using namespace std;


bool valid(point a){
    if(a.i<he && a.i>=0 && a.j<wi && a.j>=0 && arr[a.i][a.j]!=1) return 1;
    else return 0; 
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
    // map< point, int > ways;
    
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
    // ways[tmp]=0;

    tmp.i=0;
    tmp.j=1;
    hod[1]=tmp;
    // ways[tmp]=1;

    tmp.i=1;
    tmp.j=0;
    hod[2]=tmp;
    // ways[tmp]=2;

    tmp.i=0;
    tmp.j=-1;
    hod[3]=tmp;
    // ways[tmp]=3;


    for(;!q.empty();){

        point from=q.front();
        q.pop();

        for(int kt=0; kt<4;kt++){

            point to=from+hod[kt];
            to.j+=wi;
            to.j%=wi;
            // if( to.i==14 && to.j==-1 ){
            //     to.j=27;
            // }
            // else if( to.i==14 && to.j==28 ){
            //     to.j=0;
            // }
            

            if( valid(to) && used[to.i][to.j]==u){
                used[to.i][to.j]=from;
                q.push(to);


                if(to==e){

                    point nev=to;
                    for(;;){
                        
                        if(nev==u) return u;
                        
                        if(used[nev.i][nev.j]==s){
                            point ans=nev-s;
                            if(energAct==0){
                                return(ans); 
                            }
                            else{
                                int hod_nu;/*=(ways[ans]+2)%4;*/
                                for(int i=0;i<4;i++){
                                    if(ans==hod[i]){
                                        hod_nu=i;
                                        break;
                                    }
                                }
                                hod_nu+=2;
                                hod_nu%=4;
                                point next_p=s+hod[hod_nu];
                                next_p.j+=wi;
                                next_p.j%=wi;
                                if(valid(next_p)){
                                    return hod[hod_nu];
                                }
                                else{
                                    hod_nu++;
                                    hod_nu%=4;
                                    next_p=s+hod[hod_nu];
                                    next_p.j+=wi;
                                    next_p.j%=wi;
                                    if(valid(next_p)){
                                        return hod[hod_nu];
                                    }
                                    else{
                                        hod_nu+=2;
                                        hod_nu%=4;
                                        next_p=s+hod[hod_nu];
                                        next_p.j+=wi;
                                        next_p.j%=wi;
                                        if(valid(next_p)){
                                            return hod[hod_nu];
                                        }
                                        else{
                                            return ans;
                                        }
                                    }
                                }
                                
                            }
                            
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
    pacmandeath();
    

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
    pacmandeath();
    


}



void mon_corner(){

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