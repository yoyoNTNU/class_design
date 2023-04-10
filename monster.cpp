//monster.cpp
#include <string.h>
#include <stdio.h>
#include "entity.h"
#include "monster.h"
#include "player.h"

int monster::get(const char attr_name[]) const{
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
        fprintf(stderr,"Sorry,this attribute doesn't exist.\n");
        return;
    }
}

void monster::set_entity(const entity e){
    for(int i=0;i<11;++i){
        set(entity::attr[i],e.get(entity::attr[i]));
    }
}

void monster::Set_all_dis( player a )
{
    dis_my_base = sqrt( pow( x - my_base_x , 2 ) + pow ( y - my_base_y , 2 ) ); 
    dis_op_base = sqrt( pow( x - op_base_x , 2 ) + pow ( y - op_base_y , 2 ) );
    for(int i=0;i<3;++i)
    {
        dis_my_hero[i] = sqrt( pow( x - a.mh[i].Get_x() , 2 ) + pow ( y - a.mh[i].Get_y() , 2 ) );
        dis_op_hero[i] = sqrt( pow( x - a.op[i].Get_x() , 2 ) + pow ( y - a.op[i].Get_y() , 2 ) );
    }

}

