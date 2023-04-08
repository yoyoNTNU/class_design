class entity
{
    friend void player::each_round_read();
    friend entity player::input_entity();
    public:
    private:
        int id;
        int type;
        int x;
        int y;
        int shield_life;
        int is_controlled;
        int health;
        int vx;
        int vy;
        int near_base;
        int threat_for;
};


class base_loc{
    friend class player;
    private:
        int my_base_x=0;
        int my_base_y=0;
        int op_base_x=17630;
        int op_base_y=9000; 
}

//輸出指令
    //基本輸入
    //每回合輸入
//獲取hero monster資訊
//debug message
    //input計算回合數 回傳
    //排序

class player{

    public:
        void each_round_read();
        const int my_hero_get();
        // 輸出指令
        const void MOVE(const int x, const int y);
        const void WAIT();
        const void WIND(const int x, const int y);
        const void CONTROL(const int id, const int x, const int y);
        const void SHIELD(const int id);

        //獲取資訊: hero
        const int my_hero_get_id(const int i);
        const int my_hero_get_x(const int i);
        const int my_hero_get_y(const int i);
        const int my_hero_get_shield_life(const int i);
        const int my_hero_get_is_controlled(const int i);

        const int op_hero_get_id(const int i);
        const int op_hero_get_x(const int i);
        const int op_hero_get_y(const int i);
        const int op_hero_get_shield_life(const int i);
        const int op_hero_get_is_controlled(const int i);

        //獲取資訊: monster
        const int monster_get_id(const int i);
        const int monster_get_x(const int i);
        const int monster_get_y(const int i);
        const int monster_get_shield_life(const int i);
        const int monster_get_is_controlled(const int i);
        const int monster_get_health(const int i);
        const int monster_get_vx(const int i);
        const int monster_get_vy(const int i);
        const int monster_get_near_base(const int i);
        const int monster_get_threat_for(const int i);

        //debug message
        const void DEBUG();
    private:
        static constexpr int max_mos_count=100;
        static int declare_count=0;//用來提醒使用者宣告了超過1個player 設置基地x,y會讀取錯誤
        const base_loc base=set_base_loc();

        int my_hp=3;
        int my_mp=0;
        int op_hp=3;
        int op_mp=0;
        my_hero mh[3]={};
        op_hero oh[3]={};
        monster mos[max_mos_count]={};
        void set_base_hp_mp();    
        base_loc set_base_loc();
        entity input_entity();
        void set_mos_dis(){mos[i].Set_all_dis(this)};

}

void player::set_base_hp_mp(){
    scanf("%d %d %d %d",&my_hp,&my_mp,&op_hp,&op_mp);
    return;
}

base_loc player::set_base_loc(){
    base_loc base;
    if(declare_count){
        fprintf(stderr,"You have declared 'class player' multiple times which will lead to read error. Please fix");
    }
    int heros_per_plaer;
    scanf("%d %d %d",&base.my_base_x,&base.my_base_y,&heros_per_plaer);
    declare_count+=1;
    base.op_base_x=abs(base.my_base_x-17630);
    base.op_base_y=abs(base.my_base_y-9000);
    return base;
}

entity player::input_entity(){
    eneity e;
    scanf("%d%d%d%d%d%d%d%d%d%d%d",&e.id,&e.type,&e.x,&e.y,&e.shield_life,&e.is_controlled,&e.health,&e.vx,&e.vy,&e.near_base,&e.threat_for);
    return e;
}

// 輸出指令
{
    const void player::MOVE(const int x, const int y){
        cout << "MOVE " << x << " " << y << endl; 
    }
    const void player::WAIT(){
        cout << "WAIT" << endl;
    }
    const void player::WIND(const int x, const int y){
        cout << "WIND " << x << " " << y << endl;
    }
    const void player::CONTROL(const int id, const int x, const int y){
        cout << "CONTROL " << id << " " << x << " " << y << endl;
    }
    const void player::SHIELD(const int id){
        cout << "SHIELD " << id << endl;
    }
}
//獲取資訊: my_hero
{
    const int my_hero_get_id(const int i){
        if(my_hero_checkInput(i)){
            return mh[i].Get_id();
        }
        else
            return -1;
    }
    const int my_hero_get_x(const int i){
        if(my_hero_checkInput(i)){
            return mh[i].Get_x();
        }
        else
            return -1;
    }
    const int my_hero_get_y(const int i){
        if(my_hero_checkInput(i)){
            return mh[i].Get_y();
        }
        else
            return -1;
    }
    const int my_hero_get_shield_life(const int i){
        if(my_hero_checkInput(i)){
            return mh[i].Get_shield_life();
        }
        else
            return -1;
    }
    const int my_hero_get_is_controlled(const int i){
        if(my_hero_checkInput(i)){
            return mh[i].Get_is_conrtolled();
        }
        else
            return -1;
    }
    const int my_hero_checkInput(const int input){
        if(input < 0 || input > 2){
            cerr << "ERR(my_hero): The key/id is out of the range." << endl; 
            return 0;
        }
        else 
            return 1;
    }
}

//獲取資訊: op_hero
{
    const int op_hero_get_id(const int i){
        if(op_hero_checkInput(i)){
            return oh[i].Get_id();
        }
        else{
            return -1;
        }
            
    }
    const int op_hero_get_x(const int i){
        if(op_hero_checkInput(i)){
            return oh[i].Get_x();
        }
        else
            return -1;
    }
    const int op_hero_get_y(const int i){
        if(op_hero_checkInput(i)){
            return oh[i].Get_y();
        }
        else
            return -1;
    }
    const int op_hero_get_shield_life(const int i){
        if(op_hero_checkInput(i)){
            return oh[i].Get_shield_life();
        }
        else
            return -1;
    }
    const int op_hero_get_is_controlled(const int i){
        if(op_hero_checkInput(i)){
            return oh[i].Get_is_conrtolled();
        }
        else
            return -1;
    }
    const int op_hero_checkInput(const int input){
        if(oh[input]){
            return 1;
        }
        else if(input >= 0 && input <= 2){
            cerr << "ERR: There is no enemy near you." << endl;
            return 0;
        }
        else{
            cerr << "ERR(op_hero): The key is out of the range." << endl;
            return 0;
        }
    }
}

//獲取資訊: monster
{
    const int monster_get_id(const int i){
        if(monster_checkInput(i)){
            return mos[i].Get_id();
        }
        else{
            return -1;
        }
    }
    const int monster_get_x(const int i){
        if(monster_checkInput(i)){
            return mos[i].Get_x();
        }
        else{
            return -1;
        }
    }
    const int monster_get_y(const int i){
        if(monster_checkInput(i)){
            return mos[i].Get_y();
        }
        else{
            return -1;
        }
    }
    const int monster_get_shield_life(const int i){
        if(monster_checkInput(i)){
            return mos[i].Get_shield_life();
        }
        else{
            return -1;
        }
    }
    const int monster_get_is_controlled(const int i){
        if(monster_checkInput(i)){
            return mos[i].Get_is_conrtolled();
        }
        else{
            return -1;
        }
    }
    const int monster_get_health(const int i){
        if(monster_checkInput(i)){
            return mos[i].Get_health();
        }
        else{
            return -1;
        }
    }
    const int monster_get_vx(const int i){
        if(monster_checkInput(i)){
            return mos[i].Get_vx();
        }
        else{
            return -1;
        }
    }
    const int monster_get_vy(const int i){
        if(monster_checkInput(i)){
            return mos[i].Get_vy();
        }
        else{
            return -1;
        }
    }
    const int monster_get_near_base(const int i){
        if(monster_checkInput(i)){
            return mos[i].Get_near_base();
        }
        else{
            return -1;
        }
    }
    const int monster_get_threat_for(const int i){
        if(monster_checkInput(i)){
            return mos[i].Get_threat_for();
        }
        else{
            return -1;
        }
    }

    const int monster_checkInput(const int input){
        if(mos[input]){
            return 1;
        }
        else{
            cerr << "ERR: There isn't monster you want to access." << endl;
            return 0;
        }
    }

}

//debug message
const void player::DEBUG(){
    ///// my hero ///////
    cerr << "==========================" << endl;
    cerr << "my_hero:" << endl;
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

//計算距離
class monster{
    public:
        //GET
        int Get_id() const{ return id; }
        int Get_type() const{ return type; }
        int Get_x() const { return x; }
        int Get_y() const { return y; }
        int Get_shield_life() const { return shield_life; }
        int Get_is_conrtolled() const { return is_controlled; }
        int Get_health() const { return health; }
        int Get_vx() const { return vx; }
        int Get_vy() const { return vy; }
        int Get_near_base() const { return near_base; }
        int Get_threat_for() const { return threat_for; }
        //SET
        void Set_id( int num ) { id = num; }
        void Set_type( int num ) { type = num; }
        void Set_x( int num ) { x = num; }
        void Set_y( int num ) { y = num; }
        void Set_shield_life( int num ) { shield_life = num; }
        void Set_is_controlled( int num ) { is_controlled = num; }
        void Set_health( int num ) { health = num; }
        void Set_vx( int num ) { vx = num; }
        void Set_vy( int num ) { vy = num; }
        void Set_near_base( int num ) { near_base = num; }
        void Set_threat_for( int num ) { threat_for = num; }
        void Set_all_dis(player a);
    private:
        int id;
        int type;
        int x;
        int y;
        int shield_life;
        int is_controlled;
        int health;
        int vx;
        int vy;
        int near_base;
        int threat_for;
        int dis_my_base;
        int dis_op_bsae;
        int dis_my_hero[3];
        int dis_op_hero[3];

}

//hero上回合的動作
//get

class my_hero{
    public:
        int Get_id() const{ return id; }
        int Get_type() const{ return type; }
        int Get_x() const { return x; }
        int Get_y() const { return y; }
        int Get_shield_life() const { return shield_life; }
        int Get_is_conrtolled() const { return is_controlled; }
        int Get_health() const { return health; }
        int Get_vx() const { return vx; }
        int Get_vy() const { return vy; }
        int Get_near_base() const { return near_base; }
        int Get_threat_for() const { return threat_for; }
        //SET
        void Set_id( int num ) { id = num; }
        void Set_type( int num ) { type = num; }
        void Set_x( int num ) { x = num; }
        void Set_y( int num ) { y = num; }
        void Set_shield_life( int num ) { shield_life = num; }
        void Set_is_controlled( int num ) { is_controlled = num; }
        void Set_health( int num ) { health = num; }
        void Set_vx( int num ) { vx = num; }
        void Set_vy( int num ) { vy = num; }
        void Set_near_base( int num ) { near_base = num; }
        void Set_threat_for( int num ) { threat_for = num; }
        void Set_all_dis();
    private:
        int id;
        int type;
        int x;
        int y;
        int shield_life;
        int is_controlled;
        int health;
        int vx;
        int vy;
        int near_base;
        int threat_for;
        int dis_op_hero=[3];
}

class op_hero{
    public:
        int Get_id() const{ return id; }
        int Get_type() const{ return type; }
        int Get_x() const { return x; }
        int Get_y() const { return y; }
        int Get_shield_life() const { return shield_life; }
        int Get_is_conrtolled() const { return is_controlled; }
        int Get_health() const { return health; }
        int Get_vx() const { return vx; }
        int Get_vy() const { return vy; }
        int Get_near_base() const { return near_base; }
        int Get_threat_for() const { return threat_for; }
        //SET
        void Set_id( int num ) { id = num; }
        void Set_type( int num ) { type = num; }
        void Set_x( int num ) { x = num; }
        void Set_y( int num ) { y = num; }
        void Set_shield_life( int num ) { shield_life = num; }
        void Set_is_controlled( int num ) { is_controlled = num; }
        void Set_health( int num ) { health = num; }
        void Set_vx( int num ) { vx = num; }
        void Set_vy( int num ) { vy = num; }
        void Set_near_base( int num ) { near_base = num; }
        void Set_threat_for( int num ) { threat_for = num; }
        //void Set_all_dis();
    private:
        int id;
        int type;
        int x;
        int y;
        int shield_life;
        int is_controlled;
        int health;
        int vx;
        int vy;
        int near_base;
        int threat_for;
}
