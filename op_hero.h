//op_hero.h
#ifndef OP_HERO_H
#define OP_HERO_H

class op_hero{
    public:
        int get(const char attr_name[]) const;
        void set_entity(const entity e);
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

#endif