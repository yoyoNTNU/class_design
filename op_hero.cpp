//op_hero.cpp
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "entity.h"
#include "op_hero.h"
#include "player.h"

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