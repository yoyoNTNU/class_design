//player.cpp
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "player.h"

base_loc player::set_base_loc(){
    base_loc base;
    if(declare_count){
        fprintf(stderr,"You have declared 'class player' multiple times which will lead to read error. Please fix");
    }
    int heros_per_player=-1;
    scanf("%d %d %d",&base.my_base_x,&base.my_base_y,&heros_per_player);
    declare_count+=1;
    base.op_base_x=abs(base.my_base_x-17630);
    base.op_base_y=abs(base.my_base_y-9000);
    return base;
}

void player::init_mh_oh_mos(){
    visible_mos_count=0;
    visible_op_count=0;
    target_my_base_mos_count=0;
    entity e;
    for(int i=0;i<3;++i){
        mh[i].set_entity(e);
        oh[i].set_entity(e);
    }
    for(int i=0;i<max_mos_count;i++){
        mos[i].set_entity(e);
    }
}

void player::set_base_hp_mp(){
    scanf("%d%d%d%d",&my_hp,&my_mp,&op_hp,&op_mp);
    return;
}

entity player::input_entity(){
    entity e;
    scanf("%d%d%d%d%d%d%d%d%d%d%d",&e.id,&e.type,&e.x,&e.y,&e.shield_life,&e.is_controlled,&e.health,&e.vx,&e.vy,&e.near_base,&e.threat_for);
    return e;
}


void player::each_round_read(){
    round+=1;
    init_mh_oh_mos();
    set_base_hp_mp();
    int entity_count=0;
    scanf("%d",entity_count);
    int my_hero_count=0;
    for(int i=0;i<entity_count;++i){
        entity e;
        e=input_entity();
        switch (e.type){
            case Monster:
                mos[visible_mos_count].set_entity(e);
                visible_mos_count+=1;
                if(e.near_base==1&&e.threat_for==1){
                    target_my_base_mos_count+=1;
                }
                break;
            case My_Hero:
                mh[my_hero_count].set_entity(e);
                my_hero_count+=1;
                break;
            case Op_Hero:
                oh[visible_op_count].set_entity(e);
                visible_op_count+=1;
                break;
        }
    }
}


// 輸出指令
void player::MOVE(const int x, const int y) const {
    printf("MOVE %d %d\n",x,y);
}
void player::ROAMING(int type) const {
    srand(time(NULL));
    int x=0,y=0;
    switch(type){
        case Around_Me:
            x=rand()%5000;
            y=rand()%5000;
            x=abs(base.my_base_x-x);
            y=abs(base.my_base_y-y);
            break;
        case Wild_Area:
            x=rand()%17630;
            y=rand()%9000;
            while((x<5000&&y<5000)||(x>12630&&y>4000)){
                x=rand()%17630;
                y=rand()%9000;
            }
            x=abs(base.my_base_x-x);
            y=abs(base.my_base_y-y);
            break;
        case Around_Op:
            x=rand()%5000;
            y=rand()%5000;
            x=abs(base.op_base_x-x);
            y=abs(base.op_base_y-y);
            break;

        printf("MOVE %d %d\n",x,y);
    }
}
void player::WAIT() const {
    printf("WAIT\n");
}
void player::WIND(const int x, const int y) const {
    printf("SPELL WIND %d %d\n",x,y);
}
void player::CONTROL(const int id, const int x, const int y) const {
    printf("SPELL CONTROL %d %d %d\n",id,x,y);
}
void player::SHIELD(const int id) const {
    printf("SPELL SHIELD %d\n",id);
}






//debug message
const void player::DEBUG(){
    ///// my hero ///////
    fprintf(stderr,"==========================\nmy_hero:\n");
    for(int i=0;i<6;++i){
        fprintf(stderr,"%s\t",entity::attr[i]);
    }
    for(int i=0;i<3;++i){
        fprintf(stderr,"dis_op_hero_%d\t",i);
    }
    for(int i=0;i<3;++i){
        fprintf(stderr,"\n");
        for(int j=0;j<6;++j){
            fprintf(stderr,"%d\t",get_my_hero(i,entity::attr[j]));
        }
        for(int j=0;j<3;++j){
            if(get)//這邊要寫getmy_hero的dis_op_hero 可添加my_hero 的get函式
        }
    }
    cerr << "id\t" << "x\t" << "y\t" << "shield_life\t" << "is_controlled\t" << "distance between enemy" << endl;
    for(int i = 0;i<3;++i){
        cerr << mh[i].Get_id() << "\t" << mh[i].Get_x() << "\t" << mh[i].Get_y() << "\t" << mh[i].Get_shield_life() << "\t" << mh[i].Get_is_controlled() << "\t";
        for(int j = 0;dis_op_hero[j];++j){
            cerr << dis_op_hero[j] << " / ";
        }
    }
    cerr << endl;
    ///////// op hero ///////////
    cerr << "==========================" << endl;
    cerr << "op_hero:" << endl;
    cerr << "id\t" << "x\t" << "y\t" << "shield_life\t" << "is_controlled\t" << endl;
    for(int i = 0;(oh[i]);++i){
        cerr << oh[i].Get_id() << "\t" << oh[i].Get_x() << "\t" << oh[i].Get_y() << "\t" << oh[i].Get_shield_life() << "\t" << oh[i].Get_is_controlled() << "\t" << endl;
    }
    ///////// monster ///////////
    cerr << "==========================" << endl;
    cerr << "monsters:" << endl;
    cerr << "id\t" << "x\t" << "y\t" << "shield_life\t" << "is_controlled\t" << "health\t" << "vx\t" << "vy\t" << "near_base\t" << "threat_for\t" 
    << "Distance(my_base)\t" << "Distance(op_base)\t" << "Distance(my_hero)\t\t" << "Distance(enemy)\t" << endl;
    for(int i = 0;(mos[i]);++i){
        cerr << mos[i].Get_id() << "\t" << mos[i].Get_x() << "\t" << mos[i].Get_y() << "\t" << mos[i].Get_shield_life() << "\t" << mos[i].Get_is_controlled() << "\t" 
        << mos[i].Get_health() << "\t" << mos[i].Get_vx() << "\t" << mos[i].Get_vy() << "\t" << mos[i].Get_near_base() << "\t" << mos[i].Get_threat_for() << "\t" 
        << mos[i].Get_dis_my_base << "\t" << mos[i].Get_dis_op_base << "\t";
        for(int j = 0;j<3;j++){
            cerr << mos[i].Get_dis_my_hero[j] << " / ";
        }
        cerr << "\t";
        for(int j = 0;mos[i].Get_dis_op_hero[j];j++){
            cerr << mos[i].Get_dis_op_hero[j] << " / ";
        }
    }
    cerr << endl;

}

//獲取資訊: my_hero
bool my_hero_checkInput (const int input){
    if(input < 0 || input >= 3){
        fprintf(stderr,"ERR(my_hero): The key/id is out of the range.\n"); 
        return false;
    }
    else{
        return true;
    } 
            
}

int player::get_my_hero(const int i,const char attr_name[]) const{
    if(my_hero_checkInput(i)){
        return mh[i].get(attr_name);
    }
    return -1;
}


//獲取資訊: monster

bool monster_checkInput (const int input,const int visible_mos_count){
    if(input < 0 || input >= visible_mos_count){
        fprintf(stderr,"ERR(monster): The key/id is out of the range.\n"); 
        return false;
    }
    else{
        return true;
    }
}

int player::get_monster(const int i,const char attr_name[]) const{
    if(monster_checkInput(i,visible_mos_count)){
        return mos[i].get(attr_name);
    }
    return -1;
}

//獲取資訊: op_hero
bool op_hero_checkInput (const int input,const int visible_op_count){
    if(input < 0 || input >= visible_op_count){
        fprintf(stderr,"ERR(op_hero): The key/id is out of the range.\n"); 
        return false;
    }
    else{ 
        return true;
    }
}

int player::get_op_hero(const int i,const char attr_name[]) const{
    if(op_hero_checkInput(i,visible_op_count)){
        return oh[i].get(attr_name);
    }
    return -1;
}