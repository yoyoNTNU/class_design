//entity.h
#ifndef ENTITY_H
#define ENTITY_H



class entity
{
    friend class player;

    public:
    static const  char* const attr[11];
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

const char* const entity::attr[11]={"id","type","x","y","shield_life","is_controlled","health","vx","vy","near_base","threat_for"};

#endif