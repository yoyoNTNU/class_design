//player.h
#include "my_hero.h"
#include "op_hero.h"
#include "monster.h"
#include "entity.h"

#ifndef PLAYER_H
#define PLAYER_H
enum Entity_Type{Monster,My_Hero,Op_Hero};
//分別對應的(nearbase,threatfor)為 (1,1),(0,1),(0,0),(0,2),(1,2)
enum Sort_Priority_Prime{Target_Me,Eventually_Reach_Me,Never_Reach_Base,Eventually_Reach_Op,Target_Op};
enum Sort_Priority_Secindary{First_Far,First_Near,FIRST_SHIELD};

enum Roaming_Type{Around_Me,Wild_Area,Around_Op};
void swap(int &a,int &b){int temp=a;a=b;b=temp;}

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
        //sec可選各區域中 [遠到近] [近到遠] [有盾優先(默認近到遠)]
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

};

int player::declare_count=0;

#endif