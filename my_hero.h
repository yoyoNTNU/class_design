//my_hero.h
#ifndef MY_HERO_H
#define MY_HERO_H
class my_hero{
    public:
        int get(const char attr_name[]) const;
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
        int dis_op_hero[3]={};
        int dis_my_base=0;
        int dis_op_base=0;
        void set(const char attr_name[],int val);
};

#endif