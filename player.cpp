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
    ++declare_count;
    base.op_base_x=abs(base.my_base_x-17630);
    base.op_base_y=abs(base.my_base_y-9000);
    return base;
}

void player::init_mh_oh_mos(){
    visible_mos_count=0;
    visible_op_count=0;
    target_my_base_mos_count=0;
    entity e;
    for(int i=0;i<hero_per_player;++i){
        mh[i].set_entity(e);
        oh[i].set_entity(e);
    }
    for(int i=0;i<max_mos_count;++i){
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
    ++round;
    init_mh_oh_mos();
    set_base_hp_mp();
    int entity_count=0;
    scanf("%d",&entity_count);
    int my_hero_count=0;
    for(int i=0;i<entity_count;++i){
        entity e;
        e=input_entity();
        switch (e.type){
            case Monster:
                mos[visible_mos_count].set_entity(e);
                ++visible_mos_count;
                if(e.near_base==1&&e.threat_for==1){
                    ++target_my_base_mos_count;
                }
                break;
            case My_Hero:
                mh[my_hero_count].set_entity(e);
                ++my_hero_count;
                break;
            case Op_Hero:
                oh[visible_op_count].set_entity(e);
                ++visible_op_count;
                break;
        }
    }
    for(int i=0;i<my_hero_count;++i){
        mh[i].set_all_dis(*this);
    }
    for(int i=0;i<visible_op_count;++i){
        oh[i].set_all_dis(*this);
    }
    for(int i=0;i<visible_mos_count;++i){
        mos[i].set_all_dis(*this);
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
    }
    printf("MOVE %d %d\n",x,y);
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
void player::print_my_hero_info() const {
    ///// my hero ///////
    fprintf(stderr,"==========================\nmy_hero:");
    for(int i=0;i<entity::hero_attr_num;++i){
        fprintf(stderr,"\n%s\t",entity::attr[i]);
        if(i<4){
                fprintf(stderr,"\t");
        }
        for(int j=0;j<hero_per_player;++j){
            fprintf(stderr,"%d\t",get_my_hero_attr(j,entity::attr[i]));
        }
    }
    fprintf(stderr,"\ndis_op_hero_1\t");
    for(int i=0;i<hero_per_player;++i){
        if(int temp=get_my_hero_dis(i,"op_hero_1");temp==-1){
            fprintf(stderr,"invisible\t");
            break;
        }
        else{
            fprintf(stderr,"%d\t",temp);
        }
    }
    fprintf(stderr,"\ndis_op_hero_2\t");
    for(int i=0;i<hero_per_player;++i){
        if(int temp=get_my_hero_dis(i,"op_hero_2");temp==-1){
            fprintf(stderr,"invisible\t");
            break;
        }
        else{
            fprintf(stderr,"%d\t",temp);
        }
    }
    fprintf(stderr,"\ndis_op_hero_3\t");
    for(int i=0;i<hero_per_player;++i){
        if(int temp=get_my_hero_dis(i,"op_hero_3");temp==-1){
            fprintf(stderr,"invisible\t");
            break;
        }
        else{
            fprintf(stderr,"%d\t",temp);
        }
    }
    fprintf(stderr,"\ndis_my_base\t");
    for(int i=0;i<hero_per_player;++i){
        fprintf(stderr,"%d\t",get_my_hero_dis(i,"my_base"));
    }
    fprintf(stderr,"\ndis_op_base\t");
    for(int i=0;i<hero_per_player;++i){
        fprintf(stderr,"%d\t",get_my_hero_dis(i,"op_base"));
    }
    fprintf(stderr,"\n==========================\n");
}

void player::print_op_hero_info() const {
    ///// op hero ///////
    fprintf(stderr,"\n==========================\nop_hero:");
    for(int i=0;i<entity::hero_attr_num;++i){
        fprintf(stderr,"\n%s\t",entity::attr[i]);
        if(i<4){
                fprintf(stderr,"\t");
        }
        for(int j=0;j<visible_op_count;++j){
            fprintf(stderr,"%d\t",get_op_hero_attr(j,entity::attr[i]));
        }
    }
    fprintf(stderr,"\ndis_my_base\t");
    for(int i=0;i<visible_op_count;++i){
        fprintf(stderr,"%d\t",get_op_hero_dis(i,"my_base"));
    }
    fprintf(stderr,"\ndis_op_base\t");
    for(int i=0;i<visible_op_count;++i){
        fprintf(stderr,"%d\t",get_op_hero_dis(i,"op_base"));
    }
    fprintf(stderr,"\n==========================\n");
}

void player::print_monster_info() const {
    ///////// monster ///////////
    fprintf(stderr,"\n==========================\nmonster:");
    for(int i=0;i<entity::attr_num;++i){
        fprintf(stderr,"\n%s\t",entity::attr[i]);
        if(i<4||(i<=8&&i>6)){
                fprintf(stderr,"\t");
        }
        for(int j=0;j<visible_mos_count;++j){
            fprintf(stderr,"%d\t",get_monster_attr(j,entity::attr[i]));
        }
    }
    fprintf(stderr,"\ndis_my_hero_1\t");
    for(int i=0;i<visible_mos_count;++i){
        fprintf(stderr,"%d\t",get_monster_dis(i,"my_hero_1"));
    }
    fprintf(stderr,"\ndis_my_hero_2\t");
    for(int i=0;i<visible_mos_count;++i){
        fprintf(stderr,"%d\t",get_monster_dis(i,"my_hero_2"));
    }
    fprintf(stderr,"\ndis_my_hero_3\t");
    for(int i=0;i<visible_mos_count;++i){
        fprintf(stderr,"%d\t",get_monster_dis(i,"my_hero_3"));
    }
    fprintf(stderr,"\ndis_op_hero_1\t");
    for(int i=0;i<visible_mos_count;++i){
        if(int temp=get_monster_dis(i,"op_hero_1");temp==-1){
            fprintf(stderr,"invisible\t");
            break;
        }
        else{
            fprintf(stderr,"%d\t",temp);
        }
    }
    fprintf(stderr,"\ndis_op_hero_2\t");
    for(int i=0;i<visible_mos_count;++i){
        if(int temp=get_monster_dis(i,"op_hero_2");temp==-1){
            fprintf(stderr,"invisible\t");
            break;
        }
        else{
            fprintf(stderr,"%d\t",temp);
        }
    }
    fprintf(stderr,"\ndis_op_hero_3\t");
    for(int i=0;i<visible_mos_count;++i){
        if(int temp=get_monster_dis(i,"op_hero_3");temp==-1){
            fprintf(stderr,"invisible\t");
            break;
        }
        else{
            fprintf(stderr,"%d\t",temp);
        }
    }
    fprintf(stderr,"\ndis_my_base\t");
    for(int i=0;i<visible_mos_count;++i){
        fprintf(stderr,"%d\t",get_monster_dis(i,"my_base"));
    }
    fprintf(stderr,"\ndis_op_base\t");
    for(int i=0;i<visible_mos_count;++i){
        fprintf(stderr,"%d\t",get_monster_dis(i,"op_base"));
    }
    fprintf(stderr,"\n==========================\n");
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

int player::get_my_hero_attr(const int i,const char attr_name[]) const{
    if(my_hero_checkInput(i)){
        return mh[i].get_attr(attr_name);
    }
    return -1;
}

int player::get_my_hero_dis(const int i,const char target[]) const{
    if(my_hero_checkInput(i)){
        return mh[i].get_dis(target);
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

int player::get_monster_attr(const int i,const char attr_name[]) const{
    if(monster_checkInput(i,visible_mos_count)){
        return mos[i].get_attr(attr_name);
    }
    return -1;
}

int player::get_monster_dis(const int i,const char target[]) const{
    if(monster_checkInput(i,visible_mos_count)){
        return mos[i].get_dis(target);
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

int player::get_op_hero_attr(const int i,const char attr_name[]) const{
    if(op_hero_checkInput(i,visible_op_count)){
        return oh[i].get_attr(attr_name);
    }
    return -1;
}

int player::get_op_hero_dis(const int i,const char target[]) const{
    if(op_hero_checkInput(i,visible_op_count)){
        return oh[i].get_dis(target);
    }
    return -1;
}

void player::sec_sort(const int sec_priority,const int start,const int end){
    int temp=start;
    switch(sec_priority){
        case First_Far:
            for(int i=start;i<end;++i){
                for(int j=i+1;j<end;++j){
                    if(mos[i].get_dis("my_base")<mos[j].get_dis("my_base")){
                        swap_mos(mos[i],mos[j]);
                    }
                }
            }
            break;
        case First_Near:
            for(int i=start;i<end;++i){
                for(int j=i+1;j<end;++j){
                    if(mos[i].get_dis("my_base")>mos[j].get_dis("my_base")){
                        swap_mos(mos[i],mos[j]);
                    }
                }
            }
            break;
        case FIRST_SHIELD_Far:
            for(int i=start;i<end;++i){
                if(mos[i].get_attr("shield_life")!=0){
                    swap_mos(mos[i],mos[temp]);
                    ++temp;
                }
            }
            for(int i=start;i<temp;++i){
                for(int j=i+1;j<temp;++j){
                    if(mos[i].get_dis("my_base")<mos[j].get_dis("my_base")){
                        swap_mos(mos[i],mos[j]);
                    }
                }
            }
            for(int i=temp;i<end;++i){
                for(int j=i+1;j<end;++j){
                    if(mos[i].get_dis("my_base")<mos[j].get_dis("my_base")){
                        swap_mos(mos[i],mos[j]);
                    }
                }
            }
            break;
        case FIRST_SHIELD_Near:
            for(int i=start;i<end;++i){
                if(mos[i].get_attr("shield_life")!=0){
                    swap_mos(mos[i],mos[temp]);
                    ++temp;
                }
            }
            for(int i=start;i<temp;++i){
                for(int j=i+1;j<temp;++j){
                    if(mos[i].get_dis("my_base")>mos[j].get_dis("my_base")){
                        swap_mos(mos[i],mos[j]);
                    }
                }
            }
            for(int i=temp;i<end;++i){
                for(int j=i+1;j<end;++j){
                    if(mos[i].get_dis("my_base")>mos[j].get_dis("my_base")){
                        swap_mos(mos[i],mos[j]);
                    }
                }
            }
    }
}



int player::prime_sort(const int cur_prime_priority,const int sec_priority,const int current){
    int NB=0,TF=0;//儲存對應priority的nearbase and threatfor
    switch(cur_prime_priority){
        case Target_Me:             NB=1;TF=1;break;
        case Eventually_Reach_Me:   NB=0;TF=1;break;
        case Never_Reach_Base:      NB=0;TF=0;break;
        case Eventually_Reach_Op:   NB=0;TF=2;break;
        case Target_Op:             NB=1;TF=2;break;
    }
    int cc=current;
    for(int i=current;i<visible_mos_count;++i){
        if(mos[i].get_attr("near_base")==NB && mos[i].get_attr("threat_for")==TF){
            swap_mos(mos[current],mos[i]);
            ++cc;
        }
    }
    sec_sort(sec_priority,current,cc);
    return cc;

}

void player::sort_mos(const int* prime_priority,const int sec_priority){
    int current=0;
    for(int i=0;i<5;++i){
        current=prime_sort(prime_priority[i],sec_priority,current);
    }
}


/*
//增加小組中 是否需要有防護罩優先  0:不需要考慮  1:有盾優先  2:無盾優先
//小組中排序 若上述為 0 則 0:距離短到長 1:距離長到短 
//若有盾優先 則會在有盾的小組中 按距離排 沒盾的小組中 按距離排(有0或1可選)
//若無盾優先 則會在沒盾的小組中 按距離排 有盾的小組中 按距離排(有0或1可選)
int player::subsort_dis_hero(int hero,int priority,int current){
    int NB,TF;//儲存對應priority的nearbase and threatfor
    switch(priority){
        case 0: NB=1;TF=1;break;
        case 1: NB=0;TF=1;break;
        case 2: NB=0;TF=0;break;
        case 3: NB=0;TF=2;break;
        case 4: NB=1;TF=2;break;
    }
    int cc=current;
    for(int i=current;i<=mos_count;i++){
        if(dis_hero[hero][i][7]==NB && dis_hero[hero][i][8]==TF){
            for(int j=0;j<11;j++){
                swap(dis_hero[hero][current][j],dis_hero[hero][i][j]);
            }
            current++;
        }
    }
    for(int i=cc;i<current;i++){
        for(int j=i+1;j<current;j++){
            if(dis_hero[hero][j][9]<dis_hero[hero][i][9]){
                for(int k=0;k<11;k++){
                    swap(dis_hero[hero][i][k],dis_hero[hero][j][k]);
                     //fprintf(stderr,"q=%d k=%d he_q=%d he_k=%d\n",c,j,dis_hero[i][q][m],dis_hero[i][k][m]);
                }
            }
        }
    }
    return current;

}
*/

