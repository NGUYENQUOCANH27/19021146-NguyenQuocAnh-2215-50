#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <fstream>
#include <iomanip>

using namespace std;

ifstream inp;  //cac toan tu doc va ghi tep du lieu
ofstream outp;

char c[30][21]; //bien de luu tru cac phan tu (pixel) tren man hinh
int n[30][21];  //bien de kiem tra
int highscore;
int contr,tuk=0,score=0,t=0,bt=0,birdx=0,birdy=0; //cac bien khac nhau cho cac thao tac nhat dinh
bool err; //bien boolean de phat hien loi

void game();  //cac ham khac nhau
void screen();
void pipes();
void bird();
bool gameover();
void checkscore();
void help();
void menu();
void endgame();
void credits();

int main()
{
srand(time(0));  //khoi tao so ngau nhien, chung ta se can no sau;
inp.open("/Program Files/FlappyBird/options.txt");  //mo tep trong do luu tru diem cao
if(inp.is_open()) //neu tep mo thanh cong, no doc diem cao
{
    inp>>highscore;
    inp.close();
    err=false;  //loi se la false, vi tep da mo thanh cong
}
else
{
    highscore=0; //neu tep khong ton tai, diem cao se la 0, va loi se la true
    err=true;
}

int a=0,b;
char sl; //bien lua chon
while(1) //vong lap de lap lai cac hanh dong sau moi lan bat dau
{
    if(a==0) goto play; 
    if(a>0)               //neu ban choi khong phai lan dau tien, no se hoi ban co muon choi khong
    {
        score=0;
        cout<<"Do you want to play again? [y/n] ";
        cin>>sl;
        if(sl=='n') goto quit;
        else goto play;
    }
    play:
    menu(); //goi ham menu
    cin>>sl;
    switch(sl) //lua chon trong menu
    {
        case '1':
        {
            game(); //neu ban chon choi, no goi ham game
            break;
        }
        case '2': //cac lua chon khac - cac ham khac
        {
            help(); 
            goto play;
            break;
        }
        case '3':
        {
            credits();
            goto play;
            break;
        }
        case '4':
        {
            goto quit; //thoat tro choi
            break;
        }
        default:
        {
            goto play;
            break;
        }
    }
    a++; //bien de kiem tra ban da choi bao nhieu lan
}
quit:
{
   cout<<"I quit."; //dung tro choi, ung dung dong.
}

return 0;
}

void game()  //ham de choi tro choi
{
    int x,y;
    char s;
    for(y=0;y<21;y++)  //cai dat man hinh
    {
        for(x=0;x<30;x++)
        {
            if(y<20)
            {
            c[x][y]=' ';
            n[x][y]=0;
            }
            if(y==20)
            {
                c[x][y]='-';
                n[x][y]=2;
            }
        }
    }
    c[10][10]='*';  //trong cac toa do nay se la con chim cua chung ta, duoc danh dau *
    screen();      //goi ham de hien thi man hinh
    while(1)       //vong lap bat dau, bat dau thuc te
    {
        s='~';  //bien dieu khien mac dinh
        Sleep(0.2*1000);  //dieu nay thiet lap toc do di chuyen cua moi thu
        t++;              //day la mot bien de luu tru 'thoi gian', hoac so lan vong lap da qua
        if(kbhit()) //neu phim duoc nhan, mot so thao tac nhat dinh duoc thuc hien de con chim di chuyen len.
        {
            s=getch();        //lay phim nao da duoc nhan
            if(s!='~') tuk=1; //neu khong phai mac dinh, thi 'tuk' se bang 1, nghia la con chim se bay len
        }
        for(x=0;x<30;x++) //chi cai dat mat dat
        {
            c[x][20]='-';
            n[x][20]=2;
        }
        bird();                       //goi ham di chuyen con chim
        checkscore();                 //kiem tra diem
        if(gameover()==true) goto gameEnd;   //kiem tra neu con chim dung vao ong, neu co, tro choi ket thuc
        pipes();                             //xuat hien va di chuyen cac ong
        if(score>highscore) highscore=score;  //toi nghi dieu nay la ro rang
        screen();                            //cuoi cung, goi ham de hien thi moi thu.

        if(tuk>0) tuk++;           //neu phim duoc nhan, con chim se bay len 2 lan.
        if(tuk==3) tuk=0;          //sau do, con chim roi xuong
    }
    gameEnd:   //ket thuc tro choi
    {
        if(score>highscore) highscore=score;
        if(err==false)              //neu tep diem cao ton tai, no se ghi diem cao moi cua ban vao do.
        {
            outp.open("/Program Files/FlappyBird/options.txt");
            outp<<highscore;
            outp.close();
        }
        screen();    //hien thi man hinh ket thuc, va tro ve int main
        endgame();
        return;
    }
}

void screen()    //ham de hien thi man hinh
{
    int x,y;
    system("cls");    //xoa man hinh console
    for(y=0;y<21;y++) //hien thi cac phan tu tren toa do cua chung, va diem so cua ban
    {
        for(x=0;x<30;x++)
        {
            if(x<29) cout<<c[x][y];
            if(x==29) cout<<c[x][y]<<endl;
        }
    }
    cout<<""<<endl;
    cout<<"Your Score: "<<score;
}

void pipes()  //ham di chuyen va xuat hien ong
{
    int x,y,r;
    if(t==10)   //neu thoi gian la 10, hoac vong lap da qua 10 lan, no xuat hien mot ong moi
    {
        r=(rand()%11)+5;  //tao ra so ngau nhien, do se la tam cua lo ong
        for(y=0;y<20;y++)  //chi can toa do y
        {
            c[29][y]='|';  //cai dat ong
            n[29][y]=2;    //n se la 2, de kiem tra neu con chim da dung vao no
        }
        c[29][r-1]=' ';  //cai dat lo
        c[29][r]=' ';
        c[29][r+1]=' ';
        n[29][r-1]=0;
        n[29][r]=0;
        n[29][r+1]=0;
        t=0;
        goto mv; //di chuyen cac ong
    }
    else goto mv;
    mv:                 //di chuyen ong
    {
        for(y=0;y<20;y++)  //vong lap de tao toa do
        {
            for(x=0;x<30;x++)
            {
                if(c[x][y]=='|')  //tat ca cac ong se duoc di chuyen sang trai 1 don vi;
                {
                    if(x>0)
                    {
                        c[x-1][y]='|';
                        n[x-1][y]=2;
                        c[x][y]=' ';
                        n[x][y]=0;
                    } 
                    if(x==0)  //neu man hinh ket thuc (x=0) ong se bien mat, de tranh loi
                    {
                        c[x][y]=' ';
                        n[x][y]=0;
                    }
                }
            }
        }
    }
}

void bird()   //ham di chuyen con chim!
{
    int x,y;
    if(tuk>0) //neu phim duoc nhan, con chim di chuyen len
    {
        bt=0;
        for(y=0;y<20;y++)   //vong lap de tim toa do cua con chim
        {
            for(x=0;x<30;x++)
            {
                if(c[x][y]=='*')
                {
                    if(y>0)
                    {
                    c[x][y-1]='*';  //con chim di chuyen len 1 don vi;
                    c[x][y]=' ';
                    birdx=x;        //cai dat toa do x cua con chim
                    birdy=y-1;      //cai dat toa do y cua con chim
                    return;         //tro ve ham game
                    }
                }
            }
        }
    }
    else   //neu khong phim nao duoc nhan, con chim roi xuong
    {
        bt++;
        for(y=0;y<20;y++)
        {
            for(x=0;x<30;x++)
            {
                if(c[x][y]=='*')
                {
                    if(y<20)  //neu con chim khong nam tren mat dat
                    {
                        if(bt<3)   //neu thoi gian cua con chim thap hon 3, no roi xuong 1 pixel
                        {
                            c[x][y+1]='*';
                            c[x][y]=' ';
                            birdx=x;
                            birdy=y+1;
                            return;
                        }
                        else if(bt>2 && bt<5)  //nhieu thoi gian hon da troi qua, con chim roi nhanh hon (gia toc)
                        {
                            c[x][y+2]='*';
                            c[x][y]=' ';
                            birdx=x;
                            birdy=y+2;
                            return;
                        }
                        else if(bt>4)
                        {
                            c[x][y+3]='*';
                            c[x][y]=' ';
                            birdx=x;
                            birdy=y+3;
                            return;
                        }
                    }
                    else
                    {
                        return;  //neu con chim da nam tren mat dat, ham se tro ve de kiem tra tro choi ket thuc.
                    }
                }
            }
        }
    }
}




void checkscore()  //kiem tra neu con chim co diem
{
    int y;
    for(y=0;y<20;y++)
    {
        if(c[birdx][y]=='|')  //neu toa do x cua con chim bang voi toa do cua ong, ban nhan duoc 1 diem
        {
            score++;
            return;
        }
    }
}

bool gameover()  //kiem tra neu con chim da dung vao thu gi do
{
    int x,y,f=0;
    if(birdy>19) //kiem tra neu con chim dung mat dat
    {
        c[birdx][19]='*';  //cai dat lai con chim va mat dat, ngan loi
        c[birdx][20]='-';
        f=1;           //f=1, nghia la ham se tra ve true
        goto quit;
    }
    else
    {     //kiem tra neu con chim dung ong, day la bien 'n' can thiet (toa do n cua ong bang 2 (lon hon 0))
        if(n[birdx][birdy]>0 && (c[birdx][birdy]=='|' || c[birdx][birdy]=='*'))
        {
            c[birdx][birdy]='|';
            c[birdx-1][19]='*';
            f=1;
            goto quit;
        }
    }
    quit:
    if(f==1) return true;
    else return false;
}

void endgame() //chi la mot so man hinh cho cac hanh dong nhat dinh
{
    screen();   //man hinh nay hien len neu tro choi ket thuc
    cout<<""<<endl<<endl;
    cout<<" ------------------------------------------------------------------------- "<<endl;
    cout<<"|    *****      *     *       * ******       ****  *       ****** ****    |"<<endl;
    cout<<"|   *          * *    * *   * * *           *    *  *     * *     *   *   |"<<endl;
    cout<<"|   *  ****   *   *   *  * *  * *****       *    *   *   *  ****  ****    |"<<endl;
    cout<<"|   *  *  *  *******  *   *   * *           *    *    * *   *     * *     |"<<endl;
    cout<<"|    *****  *       * *       * ******       ****      *    ***** *   *   |"<<endl;
    cout<<" ------------------------------------------------------------------------- "<<endl;
    cout<<""<<endl<<endl;
    cout<<"                        Y O U R   S C O R E : "<<score<<endl<<endl;
    cout<<"                        H I G H   S C O R E : "<<highscore<<endl;
    cout<<""<<endl<<endl;
}

void menu()  //hien thi menu
{
    system("cls");
    cout<<""<<endl;
    cout<<" --------------------------------------------------------  "<<endl;
    cout<<"|                                                        | "<<endl;
    cout<<"|   **** *    **** **** **** *   *    ***  * ***  ***    | "<<endl;
    cout<<"|   *    *    *  * *  * *  * *   *    *  * * *  * *  *   | "<<endl;
    cout<<"|   ***  *    **** **** **** *****    ***  * ***  *  *   | "<<endl;
    cout<<"|   *    *    *  * *    *      *      *  * * *  * *  *   | "<<endl;
    cout<<"|   *    **** *  * *    *      *      ***  * *  * ***    | "<<endl;
    cout<<"|                                                  v 1.0 | "<<endl;
    cout<<" --------------------------------------------------------  "<<endl;
    cout<<""<<endl<<endl;
    cout<<"                  High Score:  "<<highscore<<endl<<endl;
    cout<<""<<endl<<endl;
    cout<<"                     M E N U:    "<<endl<<endl;
    cout<<"                  1: Start Game  "<<endl<<endl;
    cout<<"                  2: Help        "<<endl<<endl;
    cout<<"                  3: Credits     "<<endl<<endl;
    cout<<"                  4: Exit        "<<endl<<endl;
}

void credits()
{
    char sel;
    system("cls");
    while(true)
    {
    cout<<""<<endl<<endl;
    cout<<"               Lead programmer: Quocanh2705 "<<endl<<endl;
    cout<<"               Designer: Quocanh2705 "<<endl<<endl;
    cout<<"               Testers: Quocanh2705 "<<endl<<endl;
    cout<<"               Special thanks to: Anh Nguyen (original)"<<endl<<endl;
    cout<<"               Version: 1.0 "<<endl<<endl<<endl;
    cout<<"Go back? [y/n]  ";
    cin>>sel;
    if(sel=='y') return;
    else system("cls");
    }
}

void help()
{
    char sel;
    system("cls");
    while(true)
    {
    cout<<""<<endl<<endl;
    cout<<"                   Controls: Press any key to fly up.         "<<endl<<endl;
    cout<<"             Goal: Fly through the holes between the pipes.   "<<endl;
    cout<<"             When you pass through the hole,you get 1 point.  "<<endl;
    cout<<"                    Try to pass as much as you can.           "<<endl;
    cout<<"            But be careful, don't hit the pipes or the ground!"<<endl<<endl;
    cout<<"                          Are you ready? Go!                  "<<endl<<endl<<endl;
    cout<<"Go back? [y/n]  ";
    cin>>sel;
    if(sel=='y') return;
    else system("cls");
    }
}

