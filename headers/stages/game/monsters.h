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
            

            if( (to==e || valid(to)) && used[to.i][to.j]==u){
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

point secfir_fastest_way(point s, point e){
    // map< point, int > ways;
    static std::uniform_int_distribution<int> secfir(0, 1);
    bool first=secfir(rng);
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

            if(to==e && first){
                first=0;
                continue;
            }

            if( (to==e || valid(to)) && used[to.i][to.j]==u){
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

    point mon_dir=fastest_way( fi_mon, gam );
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

point bfs(point s, point e){
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

point th_mon_bfs(point s, point e){
    // map< point, int > ways;
    int dist=0;
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

                        dist++;

                        if(nev==u) return u;
                        
                        if(used[nev.i][nev.j]==s){
                            point ans=nev-s;
                            if(energAct==0 && dist>8){
                                return(ans); 
                            }
                            else{
                                
                                point l_d_corner;
                                l_d_corner.i=he-1-1;
                                l_d_corner.j=1;

                                return bfs(s, l_d_corner); 
                                
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

void mon_corner(){
    point mon_dir=th_mon_bfs( th_mon, gam );
    if(mon_dir==u){
        return;
    }
    point newpos=th_mon+mon_dir;
    th_mon=newpos;
    pacmandeath();
}

void fo_mon_point_mod(point &a){
    if(a.i>=he) a.i=he-1;
    if(a.j>=wi) a.j=wi-1;
    if(a.i<=0) a.i=1;
    if(a.j<=0) a.j=1;
}

void mon_hard(){

    // point half_otr=gam-fo_mon;
    // point otr=half_otr*2;
    // point addon;
    // point destination=fo_mon+(fi_mon+se_mon+th_mon+fo_mon+gam*4)/7;
    // point destination=fo_mon+otr;
    // if(destination.i<fo_mon.i) destination.i-=2;
    // else if(destination.i>fo_mon.i) destination.i+=2;
    // if(destination.j<fo_mon.j) destination.j-=2;
    // else if(destination.j>fo_mon.j) destination.j+=2;
    // fo_mon_point_mod(destination);
    point mon_dir=secfir_fastest_way( fo_mon, gam );
    if(mon_dir==u){
        return;
    }
    point newpos=fo_mon+mon_dir;
    fo_mon=newpos;
    pacmandeath();

}

void mon_thr(){
    
    int m_l_dir=0;//0 вверх | 1 вправо | 2 вниз | 3 влево
    while(gameContinue){
        moncol++;
        moncol=moncol%2;
        if( curtime >= (cycle)*0 ){
            if( !monplaced[1] ){
                fi_mon=fi_mon_start;
                monplaced[1]=1;
            }
            
            mon_bfs();
        }
        
        if( curtime >= (cycle)*1 ){

            if( !monplaced[2] ){
                se_mon=se_mon_start;
                monplaced[2]=1;
            }
            
            mon_left(m_l_dir);
            
        } 

        if( curtime >= (cycle)*2 ){
            if( !monplaced[3] ){
                th_mon=th_mon_start;
                monplaced[3]=1;
            }
            mon_corner();
        }

        if( curtime >= (cycle)*3 ){
            if( !monplaced[4] ){
                fo_mon=fo_mon_start;
                monplaced[4]=1;
            }
            mon_hard();
        }


        Sleep(wait_ghost);
        

    }

}