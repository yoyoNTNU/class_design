#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

class player;

class entity
{
    friend class player;

    public:

    static constexpr int attr_num=11; 
    static constexpr int hero_attr_num=6; 
    static const  char* const attr[attr_num];
    
    int get(const char attr_name[]) const;
    private:
        int id=0;
        int type=0;
        int x=0;
        int y=0;
        int shield_life=0;
        int is_controlled=0;
        int health=0;
        int vx=0;
        int vy=0;
        int near_base=0;
        int threat_for=0;
};

const char* const entity::attr[attr_num]={"id","type","x","y","shield_life","is_controlled","health","vx","vy","near_base","threat_for"};

class monster{
    public:
        int  get_attr(const char attr_name[]) const;
        int  get_dis (const char target[]) const; 
        void set_entity(const entity e);
        void set_all_dis(const player a);
    private:
        int id=0;
        int type=0;
        int x=0;
        int y=0;
        int shield_life=0;
        int is_controlled=0;
        int health=0;
        int vx=0;
        int vy=0;
        int near_base=0;
        int threat_for=0;
        int dis_my_hero[3]={-1,-1,-1};
        int dis_op_hero[3]={-1,-1,-1};
        int dis_my_base=0;
        int dis_op_base=0;
        void set(const char attr_name[],int val);
};

class my_hero{
    public:
        int  get_attr(const char attr_name[]) const;
        int  get_dis (const char target[]) const; 
        void set_entity(const entity e);
        void set_all_dis(const player a);
    private:
        int id=0;
        int type=0;
        int x=0;
        int y=0;
        int shield_life=0;
        int is_controlled=0;
        int health=-1;
        int vx=-1;
        int vy=-1;
        int near_base=-1;
        int threat_for=-1;
        int dis_op_hero[3]={-1,-1,-1};
        int dis_my_base=0;
        int dis_op_base=0;
        void set(const char attr_name[],int val);
};

class op_hero{
    public:
        int  get_attr(const char attr_name[]) const;
        int  get_dis (const char target[]) const;
        void set_entity(const entity e);
        void set_all_dis(const player a);
    private:
        int id=0;
        int type=0;
        int x=0;
        int y=0;
        int shield_life=0;
        int is_controlled=0;
        int health=-1;
        int vx=-1;
        int vy=-1;
        int near_base=-1;
        int threat_for=-1;
        int dis_my_base=0;
        int dis_op_base=0;
        void set(const char attr_name[],int val);
};

enum Entity_Type{Monster,My_Hero,Op_Hero};
//分別對應的(nearbase,threatfor)為 (1,1),(0,1),(0,0),(0,2),(1,2)
enum Sort_Priority_Prime{Target_Me,Eventually_Reach_Me,Never_Reach_Base,Eventually_Reach_Op,Target_Op};
enum Sort_Priority_Secindary{First_Far,First_Near,FIRST_SHIELD_Far,FIRST_SHIELD_Near};

enum Roaming_Type{Around_Me,Wild_Area,Around_Op};
void swap_mos(monster &a, monster &b){monster temp=a;a=b;b=temp;}

class base_loc{
    friend class player;
    private:
        int my_base_x=0;
        int my_base_y=0;
        int op_base_x=17630;
        int op_base_y=9000; 
};

class player{

    public:
        //此函式可以讀入單回合所有參數，並將實體存入mh,oh,mos中
        void each_round_read();

        //排序函式
        //prime為5個區域的排列順序
        //sec可選各區域中 [遠到近] [近到遠] [有盾優先(遠到近)][有盾優先(近到遠)]
        void sort_mos(const int* prime_priority,const int sec_priority);

        //獲取各種回傳值
        int get_visible_op_count() const {return visible_op_count;}
        int get_visible_mos_count() const {return visible_mos_count;}
        int get_target_my_base_mos_count() const {return target_my_base_mos_count;}
        int get_round() const {return round;}
        int get_my_hero_attr(const int i,const char attr_name[]) const;
        int get_op_hero_attr(const int i,const char attr_name[]) const;
        int get_monster_attr(const int i,const char attr_name[]) const;
        int get_my_hero_dis (const int i,const char target[]) const;
        int get_op_hero_dis (const int i,const char target[]) const;
        int get_monster_dis (const int i,const char target[]) const;
        int get_my_base_x() const {return base.my_base_x;}
        int get_my_base_y() const {return base.my_base_y;}
        int get_op_base_x() const {return base.op_base_x;}
        int get_op_base_y() const {return base.op_base_y;}
        int get_my_hp() const {return my_hp;}
        int get_my_mp() const {return my_mp;}
        int get_op_hp() const {return op_hp;}
        int get_op_mp() const {return op_mp;}

        // 輸出指令
        void MOVE(const int x, const int y) const ;//移動到x,y
        void ROAMING(int type) const ; //根據type類型遊蕩
        void WAIT() const ;//停止
        void WIND(const int x, const int y) const ;//往x,y吹風
        void CONTROL(const int id, const int x, const int y) const ;//控制該id角色去x,y
        void SHIELD(const int id) const ;//給該id角色護盾

        //debug message
        void print_my_hero_info()const;
	    void print_op_hero_info()const;
        void print_monster_info()const;

        static constexpr int hero_per_player=3;

    private:
        static constexpr int max_mos_count=100;
        static int declare_count;//用來提醒使用者宣告了超過1個player 設置基地x,y會讀取錯誤
        const base_loc base=set_base_loc();

        int my_hp=3;
        int my_mp=0;
        int op_hp=3;
        int op_mp=0;
        int visible_op_count=0;
        int visible_mos_count=0;
        int target_my_base_mos_count=0;
        my_hero mh[3]={};
        op_hero oh[3]={};
        monster mos[max_mos_count]={};
        void set_base_hp_mp();    
        base_loc set_base_loc();
        entity input_entity();
        int round=0;
        void init_mh_oh_mos();
        int prime_sort(const int cur_prime_priority,const int sec_priority,const int current);
        void sec_sort  (const int sec_priority,const int start,const int end);
};

int player::declare_count=0;

int entity::get(const char attr_name[]) const{
    if(strcmp(attr_name,"id")==0) {return id;}
    else if(strcmp(attr_name,"type")==0) {return type;}
    else if(strcmp(attr_name,"x")==0) {return x;}
    else if(strcmp(attr_name,"y")==0) {return y;}
    else if(strcmp(attr_name,"shield_life")==0) {return shield_life;}
    else if(strcmp(attr_name,"is_controlled")==0) {return is_controlled;}
    else if(strcmp(attr_name,"health")==0) {return health;}
    else if(strcmp(attr_name,"vx")==0) {return vx;}
    else if(strcmp(attr_name,"vy")==0) {return vy;}
    else if(strcmp(attr_name,"near_base")==0) {return near_base;}
    else if(strcmp(attr_name,"threat_for")==0) {return threat_for;}
    else {
        fprintf(stderr,"Sorry,this attribute doesn't exist.\n");
        return -1;
    }
}

int monster::get_attr(const char attr_name[]) const{
    if(strcmp(attr_name,"id")==0) {return id;}
    else if(strcmp(attr_name,"type")==0) {return type;}
    else if(strcmp(attr_name,"x")==0) {return x;}
    else if(strcmp(attr_name,"y")==0) {return y;}
    else if(strcmp(attr_name,"shield_life")==0) {return shield_life;}
    else if(strcmp(attr_name,"is_controlled")==0) {return is_controlled;}
    else if(strcmp(attr_name,"health")==0) {return health;}
    else if(strcmp(attr_name,"vx")==0) {return vx;}
    else if(strcmp(attr_name,"vy")==0) {return vy;}
    else if(strcmp(attr_name,"near_base")==0) {return near_base;}
    else if(strcmp(attr_name,"threat_for")==0) {return threat_for;}
    else {
        fprintf(stderr,"Sorry,this attribute doesn't exist in monster.\n");
        return -1;
    }
}

int monster::get_dis(const char target[]) const{
    if(strcmp(target,"op_hero_1")==0) {return dis_op_hero[0];}
    else if(strcmp(target,"op_hero_2")==0){return dis_op_hero[1];}
    else if(strcmp(target,"op_hero_3")==0){return dis_op_hero[2];}
    else if(strcmp(target,"my_hero_1")==0) {return dis_my_hero[0];}
    else if(strcmp(target,"my_hero_2")==0){return dis_my_hero[1];}
    else if(strcmp(target,"my_hero_3")==0){return dis_my_hero[2];}
    else if(strcmp(target,"my_base")==0){return dis_my_base;}
    else if(strcmp(target,"op_base")==0){return dis_op_base;}
    else {
        fprintf(stderr,"Sorry,this target doesn't exist.\n");
        return -1;
    }
}

void monster::set(const char attr_name[],int val){
    if(strcmp(attr_name,"id")==0) {id=val;}
    else if(strcmp(attr_name,"type")==0) {type=val;}
    else if(strcmp(attr_name,"x")==0) {x=val;}
    else if(strcmp(attr_name,"y")==0) {y=val;}
    else if(strcmp(attr_name,"shield_life")==0) {shield_life=val;}
    else if(strcmp(attr_name,"is_controlled")==0) {is_controlled=val;}
    else if(strcmp(attr_name,"health")==0) {health=val;}
    else if(strcmp(attr_name,"vx")==0) {vx=val;}
    else if(strcmp(attr_name,"vy")==0) {vy=val;}
    else if(strcmp(attr_name,"near_base")==0) {near_base=val;}
    else if(strcmp(attr_name,"threat_for")==0) {threat_for=val;}
    else {
        fprintf(stderr,"Sorry,this attribute doesn't exist in monster.\n");
        return;
    }
}

void monster::set_entity(const entity e){
    for(int i=0;i<entity::attr_num;++i){
        set(entity::attr[i],e.get(entity::attr[i]));
    }
}

void monster::set_all_dis( player a ){
    {
        int count=a.get_visible_op_count();
        for(int i=0;i<player::hero_per_player;++i){
            dis_my_hero[i] = sqrt( pow( x - a.get_my_hero_attr(i,"x") , 2 ) + pow ( y - a.get_my_hero_attr(i,"y") , 2 ) );
            if(i>=count){
                dis_op_hero[i] =-1;
            }
            else {
                dis_op_hero[i] = sqrt( pow( x - a.get_op_hero_attr(i,"x") , 2 ) + pow ( y - a.get_op_hero_attr(i,"y") , 2 ) );
            }
        }
    }
    dis_my_base=sqrt( pow( x - a.get_my_base_x() , 2 ) + pow ( y - a.get_my_base_y() , 2 ) );
    dis_op_base=sqrt( pow( x - a.get_op_base_x() , 2 ) + pow ( y - a.get_op_base_y() , 2 ) );
}


int my_hero::get_attr(const char attr_name[]) const{
    if(strcmp(attr_name,"id")==0) {return id;}
    else if(strcmp(attr_name,"type")==0) {return type;}
    else if(strcmp(attr_name,"x")==0) {return x;}
    else if(strcmp(attr_name,"y")==0) {return y;}
    else if(strcmp(attr_name,"shield_life")==0) {return shield_life;}
    else if(strcmp(attr_name,"is_controlled")==0) {return is_controlled;}
    else {
        fprintf(stderr,"Sorry,this attribute doesn't exist in my_hero.\n");
        return -1;
    }
}

int my_hero::get_dis(const char target[]) const{
    if(strcmp(target,"op_hero_1")==0) {return dis_op_hero[0];}
    else if(strcmp(target,"op_hero_2")==0){return dis_op_hero[1];}
    else if(strcmp(target,"op_hero_3")==0){return dis_op_hero[2];}
    else if(strcmp(target,"my_base")==0){return dis_my_base;}
    else if(strcmp(target,"op_base")==0){return dis_op_base;}
    else {
        fprintf(stderr,"Sorry,this target doesn't exist.\n");
        return -1;
    }
}

void my_hero::set(const char attr_name[],int val){
    if(strcmp(attr_name,"id")==0) {id=val;}
    else if(strcmp(attr_name,"type")==0) {type=val;}
    else if(strcmp(attr_name,"x")==0) {x=val;}
    else if(strcmp(attr_name,"y")==0) {y=val;}
    else if(strcmp(attr_name,"shield_life")==0) {shield_life=val;}
    else if(strcmp(attr_name,"is_controlled")==0) {is_controlled=val;}
    else if(strcmp(attr_name,"health")==0) {health=val;}
    else if(strcmp(attr_name,"vx")==0) {vx=val;}
    else if(strcmp(attr_name,"vy")==0) {vy=val;}
    else if(strcmp(attr_name,"near_base")==0) {near_base=val;}
    else if(strcmp(attr_name,"threat_for")==0) {threat_for=val;}
    else {
        fprintf(stderr,"Sorry,this attribute doesn't exist in my_hero.\n");
        return;
    }
}

void my_hero::set_entity(const entity e){
    for(int i=0;i<entity::attr_num;++i){
        set(entity::attr[i],e.get(entity::attr[i]));
    }
}

void my_hero::set_all_dis(const player a ){
    {
        int count=a.get_visible_op_count();
        for(int i=0;i<count;++i){
            dis_op_hero[i] = sqrt( pow( x - a.get_op_hero_attr(i,"x") , 2 ) + pow ( y - a.get_op_hero_attr(i,"y") , 2 ) );
        }
        for(int i=count;i<player::hero_per_player;++i){
            dis_op_hero[i] = -1;
        }
    }
    dis_my_base=sqrt( pow( x - a.get_my_base_x() , 2 ) + pow ( y - a.get_my_base_y() , 2 ) );
    dis_op_base=sqrt( pow( x - a.get_op_base_x() , 2 ) + pow ( y - a.get_op_base_y() , 2 ) );
}


int op_hero::get_attr(const char attr_name[]) const{
    if(strcmp(attr_name,"id")==0) {return id;}
    else if(strcmp(attr_name,"type")==0) {return type;}
    else if(strcmp(attr_name,"x")==0) {return x;}
    else if(strcmp(attr_name,"y")==0) {return y;}
    else if(strcmp(attr_name,"shield_life")==0) {return shield_life;}
    else if(strcmp(attr_name,"is_controlled")==0) {return is_controlled;}
    else {
        fprintf(stderr,"Sorry,this attribute doesn't exist in op_hero.\n");
        return -1;
    }
}

int op_hero::get_dis(const char target[]) const{
    if(strcmp(target,"my_base")==0){return dis_my_base;}
    else if(strcmp(target,"op_base")==0){return dis_op_base;}
    else {
        fprintf(stderr,"Sorry,this target doesn't exist.\n");
        return -1;
    }
}

void op_hero::set(const char attr_name[],int val){
    if(strcmp(attr_name,"id")==0) {id=val;}
    else if(strcmp(attr_name,"type")==0) {type=val;}
    else if(strcmp(attr_name,"x")==0) {x=val;}
    else if(strcmp(attr_name,"y")==0) {y=val;}
    else if(strcmp(attr_name,"shield_life")==0) {shield_life=val;}
    else if(strcmp(attr_name,"is_controlled")==0) {is_controlled=val;}
    else if(strcmp(attr_name,"health")==0) {health=val;}
    else if(strcmp(attr_name,"vx")==0) {vx=val;}
    else if(strcmp(attr_name,"vy")==0) {vy=val;}
    else if(strcmp(attr_name,"near_base")==0) {near_base=val;}
    else if(strcmp(attr_name,"threat_for")==0) {threat_for=val;}
    else {
        fprintf(stderr,"Sorry,this attribute doesn't exist in op_hero.\n");
        return;
    }
}

void op_hero::set_entity(const entity e){
    for(int i=0;i<entity::attr_num;++i){
        set(entity::attr[i],e.get(entity::attr[i]));
    }
}

void op_hero::set_all_dis(const player a ){
    dis_my_base=sqrt( pow( x - a.get_my_base_x() , 2 ) + pow ( y - a.get_my_base_y() , 2 ) );
    dis_op_base=sqrt( pow( x - a.get_op_base_x() , 2 ) + pow ( y - a.get_op_base_y() , 2 ) );
}

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
            swap_mos(mos[cc],mos[i]);
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

int main()
{
    player a;

    while (1) {
        a.each_round_read();
        a.WAIT();
        a.WAIT();
        a.WAIT();
    }

    return 0;
}