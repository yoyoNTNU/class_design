//monster.h
#ifndef MONSTER_H
#define MOMSTER_H

class monster{
    public:
        int get(const char attr_name[]) const;
        void set_entity(const entity e);
        void Set_all_dis(player a);
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
        int dis_my_base=0;
        int dis_op_bsae=0;
        void set(const char attr_name[],int val);
        int dis_my_hero[3]={};
        int dis_op_hero[3]={};

};

#endif