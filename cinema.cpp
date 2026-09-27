#include<iostream>
#include<vector>
#include <fstream>
#include<sstream>
using namespace std;
class Cinema{
    private:
        string name;
        int numhall;//تعداد سالن ها
    public:
        void value(string n , int m ){
            name = n;
            numhall = m;
        }
        string getnam() const{
            return name;
        }
        int getnumhall() const{
            return numhall;
        }
};
class Halls{
    protected :
        string cinemaname;
        int name;
        int numseats;//تعداد کل صندلی ها
    public :
        void seth(string xx , int nn , int mm){
            cinemaname = xx;
            name = nn;
            numseats = mm;
        }
        string getcinemaname() const { return cinemaname ;}
        int getnumseats() const { return numseats ;}
        int getname() const { return name ;}
};
class viphall : public Halls{
    private :
        int numdesk;//تعداد میز ها
    public :
        void setvip(int mm , string xx){
            name = 0;
            numseats = mm;
            numdesk = mm/2;
            cinemaname = xx;
        }
};
class Person {
    protected:
        string name;
        int password;
    public:
        int getpass() const {
            return password;
        }
};
class Operator:public Person {
    public:
        Operator(){
            password =11111;
        }
};
class Customer:public Person{
    private :
    int wallet;
    struct infotickets{
        string namefilm;
        string namecinema;
        string status;
        int numberhall;
        int numberseat;
        int Year;
        int Mounth;
        int Day;
        int timestart;
    };
    vector<infotickets>historytickets;
    public:
        void value(string n , int m){
            name = n;
            password = m;
        }
        string getname() const {
            return name;
        }
        int getwallet() const { return wallet;}
        void setwallet(int v){
            wallet = v;
        }
        void setstruct(string mm,string m , string n , int s , int i , int year , int mounth , int day , int j){
            infotickets t;
            t.status = mm;
            t.namefilm = m;
            t.namecinema = n;
            t.numberhall = s;
            t.numberseat = i;
            t.Year = year;
            t.Mounth = mounth;
            t.Day = day;
            t.timestart = j;
            historytickets.push_back(t);
        }
        void showTickets(int todayYear , int todayMounth , int todayDay){
            bool yu = false;
            for(const infotickets &t : historytickets){
                bool correctTime = false;
                if(t.status == "buy"){
                    if(t.Year > todayYear){
                        correctTime = true;
                    } else if(t.Year == todayYear && t.Mounth > todayMounth){
                        correctTime = true;
                    }else if(t.Year == todayYear && t.Mounth == todayMounth && t.Day >= todayDay){
                        correctTime = true;
                    }
                    if(correctTime){
                        bool b = false;
                        for(infotickets &r : historytickets){
                            if(r.status == "refund"){
                                if(t.namefilm==r.namefilm && t.namecinema==r.namecinema && t.numberhall==r.numberhall && t.numberseat==r.numberseat && t.timestart==r.timestart){
                                    b = true;
                                }
                            }
                        }
                        if(!b){
                            cout<<"the name of movie :"<<t.namefilm<<"     "<<"cinema :"<<t.namecinema<<endl<<"number of hall :"<<t.numberhall<<"     "<<"number of seat :"<<t.numberseat<<endl;
                            cout<<"date :"<<t.Year<<'/'<<t.Mounth<<'/'<<t.Day<<"     "<<"start time :"<<t.timestart<<endl;
                            yu = true;
                        }
                    }
                }
            } if(!yu){
                cout<<"there are not tickets"<<endl;
            }
        }
        bool CheckingTicketAvailability(string filmnam,string namcinema,int hallnum,int numseats,int year,int mounth,int day,int time){
            bool mm = true;
            for(const infotickets &t : historytickets){
                if(t.status == "buy" && t.namefilm==filmnam && t.namecinema==namcinema && t.numberhall==hallnum &&
                t.numberseat==numseats && t.Year==year && t.Mounth==mounth && t.Day==day&& t.timestart==time){
                    mm = false;
                    bool m = true;
                    for(infotickets &r : historytickets){
                        if(r.status == "refund" && r.namefilm==filmnam && r.namecinema==namcinema && r.numberhall==hallnum &&
                        r.numberseat==numseats && r.Year==year && r.Mounth==mounth && r.Day==day&& r.timestart==time){
                            m = false;
                            return false;
                        }
                    }
                    if(m){return true;}
                }
            }
            if(mm){return false;}
        }
        void addMoney (int add){
            if(add>0){
                wallet+=add;
            }
        }
    friend void updatefile();
};
vector<Customer>memberlist;
vector<Cinema>cinemalist;
vector<viphall>viphalls;
vector<Halls>halls;
void updatefile(){
    fstream f;
    f.open("memberlist.txt",ios::out);
    for(Customer &w :memberlist){
        f<<w.name<<" "<<w.password<<" "<<w.wallet<<" ";
        for(Customer::infotickets &t :w.historytickets){
            f<<t.status<<" "<<t.namefilm<<" "<<t.namecinema<<" "<<t.numberhall<<" "<<t.numberseat<<" "<<t.Year<<" "<<t.Mounth<<" "<<t.Day<<" "<<t.timestart<<" ";
        }
        f<<endl;
    }
    f.close();
}
void createfile(){
    fstream f;
    f.open("memberlist.txt",ios::in);
    string u , m , n , o;
    int y , x , s , i , year , mounth , day , jj;
    string line;
    while(getline(f,line)){
        Customer w;
        stringstream ss(line);
        ss>>u>>y>>x;
        w.value(u,y);
        w.setwallet(x);
        while(ss>>o>>m>>n>>s>>i>>year>>mounth>>day>>jj){
            w.setstruct(o,m,n,s,i,year,mounth,day,jj);
        }
        memberlist.push_back(w);
    }
    f.close();
    //تعریف کردن سینما ها با تعداد سالن هاشون و صندلی های هر سالن
    Cinema z;
    viphall vip;
    Halls j;
    z.value("azadi",4);
    cinemalist.push_back(z);
    vip.setvip(20 , "azadi");
    viphalls.push_back(vip);
    for(int i=1 ; i<z.getnumhall() ; i++){
        j.seth("azadi" , i , 50);
        halls.push_back(j);
    }
    z.value("iranmal",5);
    cinemalist.push_back(z);
    vip.setvip(20 , "iranmal");
    viphalls.push_back(vip);
    for(int i=1 ; i<z.getnumhall() ; i++){
        j.seth("iranmal" , i , 40);
        halls.push_back(j);
    }
    z.value("moeinmal",3);
    cinemalist.push_back(z);
    vip.setvip(20 , "moeinmal");
    viphalls.push_back(vip);
    for(int i=1 ; i<z.getnumhall() ; i++){
        j.seth("moeinmal" , i , 35);
        halls.push_back(j);
    }
    z.value("hadish",3);
    cinemalist.push_back(z);
    vip.setvip(20 , "hadish");
    viphalls.push_back(vip);
    for(int i=1 ; i<z.getnumhall() ; i++){
        j.seth("hadish" , i , 30);
        halls.push_back(j);
    }
    z.value("narsis",4);
    cinemalist.push_back(z);
    vip.setvip(20 , "narsis");
    viphalls.push_back(vip);
    for(int i=1 ; i<z.getnumhall() ; i++){
        j.seth("narsis" , i , 35);
        halls.push_back(j);
    }
    z.value("charso",4);
    cinemalist.push_back(z);
    vip.setvip(20 ,"charso");
    viphalls.push_back(vip);
    for(int i=1 ; i<z.getnumhall() ; i++){
        j.seth("charso" , i , 40);
        halls.push_back(j);
    }
    z.value("farhang",3);
    cinemalist.push_back(z);
    vip.setvip(20 , "farhang");
    viphalls.push_back(vip);
    for(int i=1 ; i<z.getnumhall() ; i++){
        j.seth("farhang" , i , 40);
        halls.push_back(j);
    }
    /////////////
}
void UpdateMovieSchedule(int todayYear ,int todayMounth ,int todayDay){
    fstream f , k;
    int todaydate = todayYear*10000 + todayMounth*100 + todayDay;
    f.open("movieschedule.txt",ios::in);
    k.open("tempmovieschedule.txt",ios::out);
    string d , dd , g;
    int q,ww,r,t,y,u;
    while(f>>d>>dd>>q>>ww>>r>>t>>y>>u){
        getline(f,g);
        int releaseDate = ww*10000 + r*100 +t;
        if(releaseDate >= todaydate){
            k<<d<<" "<<dd<<" "<<q<<" "<<ww<<" "<<r<<" "<<t<<" "<<y<<" "<<u<<g<<endl;
        }
    }
    f.close();
    k.close();
    remove("movieschedule.txt");
    rename("tempmovieschedule.txt","movieschedule.txt");
}
int main(){
    createfile();
    int todayDay ,todayMounth ,todayYear;
    cout<<"please enter today's date .\nyear :"<<endl;
    cin>>todayYear;
    cout<<"mounth :"<<endl;
    cin>>todayMounth;
    cout<<"day :"<<endl;
    cin>>todayDay;
    UpdateMovieSchedule(todayYear,todayMounth,todayDay);
	string a;
    cout<<"are you operator or customer ?\n"<<endl;
    cin>>a;
    if(a=="operator"){
        int b;
        Operator w;
        cout<<"enter your password :"<<endl;
        cin>>b;
        if(b==w.getpass()){
            firstpanel:
            int c;
            cout<<"_______________    operator access list    _______________\nenter 1 : registration of newly released film\nenter 2 : edit the movies section table\nenter 3 : logout"<<endl;
            cin>>c;
            switch(c){
                case(1):/*فیلم جدید اکران شده و میخوایم ثبتش کنیم تو لیست فیلم‌ها*/{
                    fstream f;
                    f.open("filmlist.txt",ios::app);
                    string filmm;
                    cout<<"enter a new film :"<<endl;
                    cin>>filmm;
                    f<<filmm<<endl;
                    f.close();
                    break;
                }
                case(2):/*میخوایم یک فیلم رو در یک سینما و یک سالن مشخص در یک زمان مشخص به جدول پخش فیلم ها برای فروش اضافه کنیم*/{
                    string filmnam,d;
                    cout<<"please enter the name of the  movie :"<<endl;
                    cin>>filmnam;
                    fstream f;
                    f.open("filmlist.txt",ios::in);
                    bool found=false;
                    while(f>>d){
                        if(filmnam==d){
                            found = true;
                        }
                    }
                    f.close();
                    if(found){
                        cout<<"the film is available for screening\n_______________________________________________________"<<endl;
                        string cinemanam;
                        cout<<"please enter the name of cinema where the film will be screen :"<<endl;
                        cin>>cinemanam;
                        bool foundd=false;
                        for(Cinema &e :cinemalist){
                            if(cinemanam == e.getnam()){
                                foundd =true;
                                int h;
                                cout<<"please enter the number of the hall where the film will be screen\nvip : 0"<<endl;
                                cin>>h;
                                if(h>0 && h<e.getnumhall()){
                                    int year,mounth,day,hours,houre;
                                    cout<<"please enter the date the film will be screen :\nyear :\n";
                                    cin>>year;
                                    cout<<"mounth :\n";
                                    cin>>mounth;
                                    cout<<"day :"<<endl;
                                    cin>>day;
                                    cout<<"please enter the time start the film will be screen :(ساعت باید کامل باشه)"<<endl;
                                    cin>>hours;
                                    cout<<"please enter the time end the film will be screen :(ساعت باید کامل باشه)"<<endl;
                                    cin>>houre;
                                    f.open("movieschedule.txt",ios::in);
                                    string d , dd , g;
                                    int q,ww,r,t,y,u;
                                    bool founddd = false;
                                    while(f>>d>>dd>>q>>ww>>r>>t>>y>>u){
                                        getline(f,g);
                                        if(dd==cinemanam && q==h && ww==year && r==mounth && t==day){
                                            if(hours>=y && hours<u){
                                                cout<<"the hall is showing another movie at this time"<<endl;
                                                founddd = true;
                                            }else if(houre>y && houre<=u){
                                                cout<<"the hall is showing another movie at this time"<<endl;
                                                founddd = true;
                                            }
                                            else if(hours<y && houre>u){
                                                cout<<"the hall is showing another movie at this time"<<endl;
                                                founddd = true;
                                            }
                                        }
                                    }
                                    f.close();
                                    if(!founddd){
                                        vector<bool>seats;
                                        for(const Halls &rr : halls){
                                            if(cinemanam == rr.getcinemaname() && h == rr.getname()){
                                                for(int i=0;i<rr.getnumseats();i++){
                                                    seats.push_back(false);
                                                }
                                            }
                                        }
                                        f.open("movieschedule.txt",ios::app);
                                        f<<filmnam<<" "<<cinemanam<<" "<<h<<" "<<year<<" "<<mounth<<" "<<day<<" "<<hours<<" "<<houre<<" "<<seats.size()<<" ";
                                        for(bool b: seats){
                                            f<<b<<" ";
                                        }
                                        f<<endl;
                                        f.close();
                                    }
                                } else if /*vip برای سالن*/ (h == 0){
                                    int year,mounth,day,hours,houre;
                                    cout<<"please enter the date the film will be screen :\nyear :\n";
                                    cin>>year;
                                    cout<<"mounth :\n";
                                    cin>>mounth;
                                    cout<<"day :"<<endl;
                                    cin>>day;
                                    cout<<"please enter the time start the film will be screen :(ساعت باید کامل باشه)"<<endl;
                                    cin>>hours;
                                    cout<<"please enter the time end the film will be screen :(ساعت باید کامل باشه)"<<endl;
                                    cin>>houre;
                                    f.open("movieschedule.txt",ios::in);
                                    string dd , g;
                                    int q,ww,r,t,y,u;
                                    bool founddd = false;
                                    while(f>>d>>dd>>q>>ww>>r>>t>>y>>u){
                                        getline(f,g);
                                        if(dd==cinemanam && q==h && ww==year && r==mounth && t==day){
                                            if(hours>y && hours<u){
                                                cout<<"the hall is showing another movie at this time"<<endl;
                                                founddd = true;
                                            }else if(houre>y && houre<u){
                                                cout<<"the hall is showing another movie at this time"<<endl;
                                                founddd = true;
                                            }
                                        }
                                    }
                                    f.close();
                                    if(!founddd){
                                        vector<bool>seats;
                                        for(const viphall &rr : viphalls){
                                            if(cinemanam == rr.getcinemaname()){
                                                for(int i=0;i<rr.getnumseats();i++){
                                                    seats.push_back(false);
                                                }
                                            }
                                        }
                                        f.open("movieschedule.txt",ios::app);
                                        f<<filmnam<<" "<<cinemanam<<" "<<h<<" "<<year<<" "<<mounth<<" "<<day<<" "<<hours<<" "<<houre<<" "<<seats.size()<<" ";
                                        for(bool b: seats){
                                            f<<b<<" ";
                                        }
                                        f<<endl;
                                        f.close(); 
                                    }

                                }
                            }
                        }
                        if(!foundd){
                            cout<<"there isn't cinema with that name"<<endl;
                        }

                    }else cout<<"the film is not available for screening"<<endl;
                }
                case(3):{
                    goto endprog;
                }
            } goto firstpanel;
        }else cout<<"the password is incorrect"<<endl;
    } else if(a=="customer"){
        cout<<"have you already registered ?\nyes :1\nno :0"<<endl;
        int c;
        cin>>c;
        join: if(c){
            int b;
            Customer w;
            cout<<"enter your password :"<<endl;
            cin>>b;
            bool f = false;
            for(Customer &w : memberlist){
                if(b==w.getpass()){
                    cout<<"hello "<<w.getname()<<endl;
                    f = true;
                    Firstpanel:
                    int d;
                    cout<<"_______________    customer access list    _______________\nenter 1 : buy ticket\nenter 2 : ticket refund\nenter 3 : show tickets\nenter 4 : increase in inventory\nenter 5 : logout"<<endl;
                    cin>>d;
                    switch(d){
                        case(1):{
                            fstream ff;
                            string filmnam;
                            cout<<"please enter the name of the movie you want to watch :"<<endl;
                            cin>>filmnam;
                            ff.open("movieschedule.txt",ios::in);
                            string d , dd , g;
                            int q,ww,r,t,y,u;
                            bool found = false;
                            while(ff>>d>>dd>>q>>ww>>r>>t>>y>>u){
                                getline(ff,g);
                                if(filmnam == d){
                                    cout<<"_______________ list of tickets for the desired movie _______________"<<endl;
                                    cout<<" film name : "<<d<<"    "<<"cinma name : "<<dd<<"    "<<"number hall :"<<q<<"    ";
                                    cout<<"date :"<<ww<<"/"<<r<<"/"<<t<<"    "<<"time :"<<y<<endl;
                                    found = true;
                                } else cout<<"this film wont be released in any cinemas"<<endl;
                            }
                            ff.close();
                            if(found){
                                cout<<"please enter the name of the selected cinema :"<<endl;
                                string namcinema;
                                cin>>namcinema;
                                cout<<"please enter the number of hall :"<<endl;
                                int hallnum;
                                cin>>hallnum;
                                cout<<"please enter the relesead date of the selected movie :"<<endl<<"year :";
                                int year;
                                cin>>year;
                                cout<<"mounth :";
                                int mounth;
                                cin>>mounth;
                                cout<<"day :";
                                int day;
                                cin>>day;
                                cout<<"please enter the time of start film :"<<endl;
                                int time;
                                cin>>time;
                                vector<bool>seats;
                                int p;
                                fstream file;
                                ff.open("movieschedule.txt",ios::in);
                                file.open("tempmovieschedule.txt",ios::out);
                                while(ff>>d>>dd>>q>>ww>>r>>t>>y>>u>>p){
                                    bool bb;
                                    seats.clear();
                                    for(int i = 0; i<p; i++){
                                        ff>>bb;
                                        seats.push_back(bb);
                                    }
                                    if(filmnam == d && namcinema == dd && hallnum == q && year == ww && mounth == r && day ==t && time == y){
                                        bool foundd = false;
                                        for(const bool &gg : seats){
                                            if(!gg){
                                                foundd = true;
                                                break;
                                            }
                                        }
                                        if(foundd){                                    
                                            cout<<"accessible seats : ";
                                            int integer=1;
                                            for(const bool &gg : seats){
                                                if(!gg){
                                                    cout<<integer<<",";
                                                }
                                                integer++;
                                            }cout<<endl;
                                            while(true){
                                                cout<<"please enter your preferred seat number "<<endl;
                                                int selectionseat;
                                                cin>>selectionseat;
                                                if( seats.at(selectionseat -1) == false ){
                                                    if(day ==10 || day ==20 || day ==30)/*این روز ها سینما نیم بها هست*/{
                                                        if(hallnum == 0){
                                                            cout<<"vip ticket price : 200 $"<<endl;
                                                            int money;
                                                            money = w.getwallet();
                                                            if(money>= 200){
                                                                money -= 200;
                                                                w.setwallet(money);
                                                                seats.at(selectionseat -1) = true;
                                                                w.setstruct("buy",filmnam,namcinema,hallnum,selectionseat,year,mounth,day,time);
                                                                updatefile();
                                                                cout<<"this seat has been reserved for you .";
                                                            } else cout<<"your balance is not sufficient "<<endl;
                                                        } else {
                                                            cout<<"ticket price : 90 $"<<endl;
                                                            int money;
                                                            money = w.getwallet();
                                                            if(money>= 90){
                                                                money -= 90;
                                                                w.setwallet(money);
                                                                seats.at(selectionseat -1) = true;
                                                                w.setstruct("buy",filmnam,namcinema,hallnum,selectionseat,year,mounth,day,time);
                                                                updatefile();
                                                                cout<<"this seat has been reserved for you .";
                                                            } else cout<<"your balance is not sufficient "<<endl;
                                                        }
                                                    }else {
                                                        if(hallnum == 0){
                                                            cout<<"vip ticket price : 400 $"<<endl;
                                                            int money;
                                                            money = w.getwallet();
                                                            if(money>= 400){
                                                                money -= 400;
                                                                w.setwallet(money);
                                                                seats.at(selectionseat -1) = true;
                                                                w.setstruct("buy",filmnam,namcinema,hallnum,selectionseat,year,mounth,day,time);
                                                                updatefile();
                                                                cout<<"this seat has been reserved for you .";
                                                            } else cout<<"your balance is not sufficient "<<endl;
                                                        } else {
                                                            cout<<"ticket price : 180 $"<<endl;
                                                            int money;
                                                            money = w.getwallet();
                                                            if(money>= 180){
                                                                money -= 180;
                                                                w.setwallet(money);
                                                                seats.at(selectionseat -1) = true;
                                                                w.setstruct("buy",filmnam,namcinema,hallnum,selectionseat,year,mounth,day,time);
                                                                updatefile();
                                                                cout<<"this seat has been reserved for you .";
                                                            } else cout<<"your balance is not sufficient "<<endl;
                                                            }
                                                    }break;
                                                }else cout<<"this seat is already reserved .";
                                            }
                                        }else cout<<"capacity is full ."<<endl;
                                        file<<d<<" "<<dd<<" "<<q<<" "<<ww<<" "<<r<<" "<<t<<" "<<y<<" "<<u<<" "<<p<<" ";
                                        for(bool b: seats){
                                            file<<b<<" ";
                                        }
                                        file<<endl;                                          
                                    } else {
                                        file<<d<<" "<<dd<<" "<<q<<" "<<ww<<" "<<r<<" "<<t<<" "<<y<<" "<<u<<" "<<p<<" ";
                                        for(bool b: seats){
                                            file<<b<<" ";
                                        }
                                        file<<endl;
                                    }    
                                }
                                ff.close();
                                file.close();
                                remove("movieschedule.txt");
                                rename("tempmovieschedule.txt","movieschedule.txt");
                            }
                            break;
                        }
                        case(2):{
                            cout<<"which ticket you want to refund :"<<endl;
                            w.showTickets(todayYear ,todayMounth ,todayDay);
                            cout<<"enter ticket information :\nname movie :"<<endl;
                            string filmnam;
                            cin>>filmnam;
                            cout<<"name cinema :"<<endl;
                            string namcinema;
                            cin>>namcinema;
                            cout<<"number of hall :"<<endl;
                            int hallnum;
                            cin>>hallnum;
                            cout<<"number of seat :"<<endl;
                            int numseats;
                            cin>>numseats;
                            cout<<"year :"<<endl;
                            int year;
                            cin>>year;
                            cout<<"mounth :"<<endl;
                            int mounth;
                            cin>>mounth;
                            cout<<"day :"<<endl;
                            int day;
                            cin>>day;
                            cout<<"time of start :"<<endl;
                            int time;
                            cin>>time;
                            if(w.CheckingTicketAvailability(filmnam,namcinema,hallnum,numseats,year,mounth,day,time)){
                                w.setstruct("refund",filmnam,namcinema,hallnum,numseats,year,mounth,day,time);
                                if(day ==10 || day ==20 || day ==30){
                                    if(hallnum)/*سالن عادی و وی ای پی 80 درصد برمیگرده*/{
                                        int money;
                                        money = w.getwallet();
                                        money+=72;
                                        w.setwallet(money);
                                        updatefile();
                                        cout<<"the ticket refund has been processed and the ticket amount , minus tax , has been added to your balance"<<endl;
                                    }else {
                                        int money;
                                        money = w.getwallet();
                                        money+=160;
                                        w.setwallet(money);
                                        updatefile();
                                        cout<<"the ticket refund has been processed and the ticket amount , minus tax , has been added to your balance"<<endl;
                                    }
                                }else {
                                    if(hallnum)/*سالن عادی و وی ای پی 80 درصد برمیگرده*/{
                                        int money;
                                        money = w.getwallet();
                                        money+=144;
                                        w.setwallet(money);
                                        updatefile();
                                        cout<<"the ticket refund has been processed and the ticket amount , minus tax , has been added to your balance"<<endl;
                                    }else {
                                        int money;
                                        money = w.getwallet();
                                        money+=320;
                                        w.setwallet(money);
                                        updatefile();
                                        cout<<"the ticket refund has been processed and the ticket amount , minus tax , has been added to your balance"<<endl;
                                    }
                                }
                                string d , dd;
                                int q,ww,r,t,y,u,p;
                                vector<bool>seats;
                                fstream ff ,file;
                                ff.open("movieschedule.txt",ios::in);
                                file.open("tempmovieschedule.txt",ios::out);
                                while(ff>>d>>dd>>q>>ww>>r>>t>>y>>u>>p){
                                    bool bb;
                                    seats.clear();
                                    for(int i = 0; i<p; i++){
                                        ff>>bb;
                                        seats.push_back(bb);
                                    }
                                    if(filmnam == d && namcinema == dd && hallnum == q && year == ww && mounth == r && day ==t && time == y){
                                        seats.at(numseats -1) = false;
                                    }
                                    file<<d<<" "<<dd<<" "<<q<<" "<<ww<<" "<<r<<" "<<t<<" "<<y<<" "<<u<<" "<<p<<" ";
                                    for(bool b: seats){
                                        file<<b<<" ";
                                    }
                                    file<<endl;
                                }
                                ff.close();
                                file.close();
                                remove("movieschedule.txt");
                                rename("tempmovieschedule.txt","movieschedule.txt");
                            } else cout<<"there is no ticket with such information ."<<endl;
                            break;
                        }
                        case(3):{
                            w.showTickets(todayYear ,todayMounth ,todayDay);
                            break;
                        }
                        case(4):{
                            int add;
                            cout<<"please enter the amount of money."<<endl;
                            cin>>add;
                            w.addMoney(add);
                            updatefile();
                            cout<<"your inventory has incerased."<<endl;
                            break;
                        }
                        case(5):{
                            goto endprog;   
                        }
                    }
                    goto Firstpanel;
                }
            }
            if(!f){
                cout<<"the password is incorrect"<<endl;
            }
        } else {
           Customer w;
           string n;
           int m;
           cout<<"enter your name :"<<endl;
           cin>>n;
           cout<<"enter your password"<<endl;
           cin>>m;
            w.value(n,m);
            w.setwallet(0);
            memberlist.push_back(w);
            updatefile();
            c = 1;
            cout<<"\nyour registration was successful\n"<<endl;
            goto join;
        }
    }else cout<<"the input is incorrect"<<endl;
    endprog:;
}