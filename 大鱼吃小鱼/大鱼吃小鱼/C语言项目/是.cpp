#undef UNICODE
#undef _UNICODE
#include"stdio.h"
#include"conio.h"
#include"graphics.h"
#include<stdlib.h>
#include<time.h>
#include<string.h>
#pragma comment(lib,"Winmm.lib")
 struct efishkind
{
	int fx,fy;
	int v;
	int level;
	int direction;
	int efishwidth;
	int efishheigh;
	struct efishkind *next;
}*h,*p,*q,*q1,*p1,*p2,*p3,*q3,*p4,*q4,*h3,*p5,*p6;
void fisheat();
void controlsize();
void outscore();
void outfishlife();
void controlscore();
void initgraphjudge();
void makeefish();
void showefish();
void efishcontrol();
void loadpcture();
void loadsize();
void mouse();
void game();
void startshow();
void gameback();
void controllife();
int score=0;
int life=3;
int score1,score2;
MOUSEMSG s;
IMAGE m2,m5,m8,m9,m121,m122,m1011,m1012,m1013,m1021,m1022,m1031,m1032,m20;
IMAGE fm1011,fm1012,fm1013,fm1021,fm1022,fm1031,fm1032;
IMAGE m131,m132,m141,m142,m151,m152,m161,m162;
IMAGE fm131,fm132,fm141,fm142,fm151,fm152,fm161,fm162,fm121,fm122,m40,m30;
IMAGE m[10],m1[10],n[10],n1[10],red[10],green[10],zred[10],zgreen[10];
IMAGE fm[10],fm1[10],fn[10],fn1[10],fred[10],fgreen[10],fzred[10],fzgreen[10];
int twidth,theigh;
int x,y;
int i;
int fishwidth=530/10,fishheigh=509/10;
int grow[10];
int number=0;
int protect=0,protect1=0,protect2;
int a=1;
void inti()
{
	score=0;
	life=3;
	game();
}
void inti1()	
{
	score=0;
	life=3;
	startshow();
}
void cow()
{		
		fflush(stdin);
		SetWorkingImage();
		cleardevice();
		loadimage(&m30,"C:\\Users\\10614\\Desktop\\大鱼吃小鱼项目图片\\30.jpg",1000,572);
		putimage(0,0,&m30);
		settextstyle(100,0,_T("黑体"));
		settextcolor(RED);
		setbkmode(TRANSPARENT);
		outtextxy(0,200,"湖塘的鱼都被你吃光了！");
		settextstyle(50,20,_T("黑体"));
		settextcolor(BLACK);
		setbkmode(TRANSPARENT);
		outtextxy(0,0,"按任意键继续");
		FlushBatchDraw();
		fflush(stdin);
		if(kbhit())
			inti1();
}
void hack()
{
	char s[20]="大家下午好！";
	char ss[20];
	InputBox(ss,20,"请输入歪瓜（中文）");
	a=strcmp(s,ss);
	if(a==0)
	{
			loadimage(&m40,"C:\\Users\\10614\\Desktop\\大鱼吃小鱼项目图片\\40.jpg",1000,572);
			putimage(0,0,&m40);
			settextstyle(100,0,_T("黑体"));
			settextcolor(RED);
			setbkmode(TRANSPARENT);
			outtextxy(100,200,"歪瓜验证成功！");
			Sleep(50);
			inti();
	}
	else
	{
			loadimage(&m40,"C:\\Users\\10614\\Desktop\\大鱼吃小鱼项目图片\\40.jpg",1000,572);
			putimage(0,0,&m40);
			settextstyle(100,0,_T("黑体"));
			settextcolor(RED);
			setbkmode(TRANSPARENT);
			outtextxy(100,200,"歪瓜验证失败！");
			Sleep(500);
			startshow();
	}
}
void gameover()
{
		fflush(stdin);
		putimage(0,0,&m20);
		settextstyle(50,0,_T("华文新魏"));
		settextcolor(LIGHTRED);
		setbkmode(TRANSPARENT);
		outtextxy(0,0,"按1再玩一次，按2返回菜单");
		FlushBatchDraw();
		while(1)
		{
			fflush(stdin);
			char b=getch();
			if(b=='1')
				inti();
			else if(b=='2')
				startshow();
				
		}
}
void controllife()
{
	p5=h;
	while(p5)
	{
		if(s.x+twidth>p5->fx&&s.x<p5->fx+p5->efishwidth&&s.y<p5->fy+p5->efishheigh&&s.y+theigh>p5->fy)
		{
			if(twidth<p5->efishwidth)
				life--;
		}
		p5=p5->next;
	}	
}
void fisheat()
{
	p3=h;
	q3=h;
	while(p3)
	{
		if(s.x+twidth>p3->fx&&s.x<p3->fx+p3->efishwidth&&s.y<p3->fy+p3->efishheigh&&s.y+theigh>p3->fy)
		{
			if(twidth>p3->efishwidth)
			{
				p3->fy=rand()%572;
				if(p3->direction==0)
					p3->fx=1000;
				else if(p3->direction==1)
					p3->fx=-400;
				p3->level=rand()%9;
				if(p3->level==0||p3->level==1||p3->level==2)
				{
					p3->efishwidth=35;
					p3->efishheigh=29;
				}
				else if(p3->level==3||p3->level==4)
				{
					p3->efishwidth=90;
					p3->efishheigh=72;
				}
				else if(p3->level==5||p3->level==6)
				{
					p3->efishwidth=200;
					p3->efishheigh=156;
				}
				else if(p3->level==7)
				{
					p3->efishwidth=300;
					p3->efishheigh=202;
				}
				else if(p3->level==8)
				{
					p3->efishwidth=400;
					p3->efishheigh=207;
				}
			}
		}
		p3=p3->next;
	}
}
void fish1()
{
	putimage(x,y,&m[0],NOTSRCERASE);
	putimage(x,y,&m1[0],SRCINVERT);
}
void fish2()
{
	putimage(x,y,&m[1],NOTSRCERASE);
	putimage(x,y,&m1[1],SRCINVERT);
}
void fish3()
{
	putimage(x,y,&m[2],NOTSRCERASE);
	putimage(x,y,&m1[2],SRCINVERT);
}
void fish4()
{
	putimage(x,y,&m[3],NOTSRCERASE);
	putimage(x,y,&m1[3],SRCINVERT);
}
void fish5()
{
	putimage(x,y,&m[4],NOTSRCERASE);
	putimage(x,y,&m1[4],SRCINVERT);
}
void fish6()
{
	putimage(x,y,&m[5],NOTSRCERASE);
	putimage(x,y,&m1[5],SRCINVERT);
}
void fish7()
{
	putimage(x,y,&m[6],NOTSRCERASE);
	putimage(x,y,&m1[6],SRCINVERT);
}
void fish8()
{
	putimage(x,y,&m[7],NOTSRCERASE);
	putimage(x,y,&m1[7],SRCINVERT);
}
void fish9()
{
	putimage(x,y,&m[8],NOTSRCERASE);
	putimage(x,y,&m1[8],SRCINVERT);
}
void zfish1()
{
	putimage(x,y,&n[0],NOTSRCERASE);
	putimage(x,y,&n1[0],SRCINVERT);
}
void zfish2()
{
	putimage(x,y,&n[1],NOTSRCERASE);
	putimage(x,y,&n1[1],SRCINVERT);
}
void zfish3()
{
	putimage(x,y,&n[2],NOTSRCERASE);
	putimage(x,y,&n1[2],SRCINVERT);
}
void zfish4()
{
	putimage(x,y,&n[3],NOTSRCERASE);
	putimage(x,y,&n1[3],SRCINVERT);
}
void zfish5()
{
	putimage(x,y,&n[4],NOTSRCERASE);
	putimage(x,y,&n1[4],SRCINVERT);
}
void zfish6()
{
	putimage(x,y,&n[5],NOTSRCERASE);
	putimage(x,y,&n1[5],SRCINVERT);
}
void zfish7()
{
	putimage(x,y,&n[6],NOTSRCERASE);
	putimage(x,y,&n1[6],SRCINVERT);
}
void zfish8()
{
	putimage(x,y,&n[7],NOTSRCERASE);
	putimage(x,y,&n1[7],SRCINVERT);
}
void zfish9()
{
	putimage(x,y,&n[8],NOTSRCERASE);
	putimage(x,y,&n1[8],SRCINVERT);
}
void redfish1()
{
	putimage(x,y,&m[0],NOTSRCERASE);
	putimage(x,y,&red[0],SRCINVERT);
}
void redfish2()
{
	putimage(x,y,&m[1],NOTSRCERASE);
	putimage(x,y,&red[1],SRCINVERT);
}
void redfish3()
{
	putimage(x,y,&m[2],NOTSRCERASE);
	putimage(x,y,&red[2],SRCINVERT);
}
void redfish4()
{
	putimage(x,y,&m[3],NOTSRCERASE);
	putimage(x,y,&red[3],SRCINVERT);
}
void redfish5()
{
	putimage(x,y,&m[4],NOTSRCERASE);
	putimage(x,y,&red[4],SRCINVERT);
}
void redfish6()
{
	putimage(x,y,&m[5],NOTSRCERASE);
	putimage(x,y,&red[5],SRCINVERT);
}
void redfish7()
{
	putimage(x,y,&m[6],NOTSRCERASE);
	putimage(x,y,&red[6],SRCINVERT);
}
void redfish8()
{
	putimage(x,y,&m[7],NOTSRCERASE);
	putimage(x,y,&red[7],SRCINVERT);
}
void redfish9()
{
	putimage(x,y,&m[8],NOTSRCERASE);
	putimage(x,y,&red[8],SRCINVERT);
}
void zredfish1()
{
	putimage(x,y,&n[0],NOTSRCERASE);
	putimage(x,y,&zred[0],SRCINVERT);
}
void zredfish2()
{
	putimage(x,y,&n[1],NOTSRCERASE);
	putimage(x,y,&zred[1],SRCINVERT);
}
void zredfish3()
{
	putimage(x,y,&n[2],NOTSRCERASE);
	putimage(x,y,&zred[2],SRCINVERT);
}
void zredfish4()
{
	putimage(x,y,&n[3],NOTSRCERASE);
	putimage(x,y,&zred[3],SRCINVERT);
}
void zredfish5()
{
	putimage(x,y,&n[4],NOTSRCERASE);
	putimage(x,y,&zred[4],SRCINVERT);
}
void zredfish6()
{
	putimage(x,y,&n[5],NOTSRCERASE);
	putimage(x,y,&zred[5],SRCINVERT);
}
void zredfish7()
{
	putimage(x,y,&n[6],NOTSRCERASE);
	putimage(x,y,&zred[6],SRCINVERT);
}
void zredfish8()
{
	putimage(x,y,&n[7],NOTSRCERASE);
	putimage(x,y,&zred[7],SRCINVERT);
}
void zredfish9()
{
	putimage(x,y,&n[8],NOTSRCERASE);
	putimage(x,y,&zred[8],SRCINVERT);
}
void greenfish1()
{
	putimage(x,y,&m[0],NOTSRCERASE);
	putimage(x,y,&green[0],SRCINVERT);
}
void greenfish2()
{
	putimage(x,y,&m[1],NOTSRCERASE);
	putimage(x,y,&green[1],SRCINVERT);
}
void greenfish3()
{
	putimage(x,y,&m[2],NOTSRCERASE);
	putimage(x,y,&green[2],SRCINVERT);
}
void greenfish4()
{
	putimage(x,y,&m[3],NOTSRCERASE);
	putimage(x,y,&green[3],SRCINVERT);
}
void greenfish5()
{
	putimage(x,y,&m[4],NOTSRCERASE);
	putimage(x,y,&green[4],SRCINVERT);
}
void greenfish6()
{
	putimage(x,y,&m[5],NOTSRCERASE);
	putimage(x,y,&green[5],SRCINVERT);
}
void greenfish7()
{
	putimage(x,y,&m[6],NOTSRCERASE);
	putimage(x,y,&green[6],SRCINVERT);
}
void greenfish8()
{
	putimage(x,y,&m[7],NOTSRCERASE);
	putimage(x,y,&green[7],SRCINVERT);
}
void greenfish9()
{
	putimage(x,y,&m[8],NOTSRCERASE);
	putimage(x,y,&green[8],SRCINVERT);
}
void zgreenfish1()
{
	putimage(x,y,&n[0],NOTSRCERASE);
	putimage(x,y,&zgreen[0],SRCINVERT);
}
void zgreenfish2()
{
	putimage(x,y,&n[1],NOTSRCERASE);
	putimage(x,y,&zgreen[1],SRCINVERT);
}
void zgreenfish3()
{
	putimage(x,y,&n[2],NOTSRCERASE);
	putimage(x,y,&zgreen[2],SRCINVERT);
}
void zgreenfish4()
{
	putimage(x,y,&n[3],NOTSRCERASE);
	putimage(x,y,&zgreen[3],SRCINVERT);
}
void zgreenfish5()
{
	putimage(x,y,&n[4],NOTSRCERASE);
	putimage(x,y,&zgreen[4],SRCINVERT);
}
void zgreenfish6()
{
	putimage(x,y,&n[5],NOTSRCERASE);
	putimage(x,y,&zgreen[5],SRCINVERT);
}
void zgreenfish7()
{
	putimage(x,y,&n[6],NOTSRCERASE);
	putimage(x,y,&zgreen[6],SRCINVERT);
}
void zgreenfish8()
{
	putimage(x,y,&n[7],NOTSRCERASE);
	putimage(x,y,&zgreen[7],SRCINVERT);
}
void zgreenfish9()
{
	putimage(x,y,&n[8],NOTSRCERASE);
	putimage(x,y,&zgreen[8],SRCINVERT);
}
void ffish1()
{
	putimage(x,y,&fm[0],NOTSRCERASE);
	putimage(x,y,&fm1[0],SRCINVERT);
}
void ffish2()
{
	putimage(x,y,&fm[1],NOTSRCERASE);
	putimage(x,y,&fm1[1],SRCINVERT);
}
void ffish3()
{
	putimage(x,y,&fm[2],NOTSRCERASE);
	putimage(x,y,&fm1[2],SRCINVERT);
}
void ffish4()
{
	putimage(x,y,&fm[3],NOTSRCERASE);
	putimage(x,y,&fm1[3],SRCINVERT);
}
void ffish5()
{
	putimage(x,y,&fm[4],NOTSRCERASE);
	putimage(x,y,&fm1[4],SRCINVERT);
}
void ffish6()
{
	putimage(x,y,&fm[5],NOTSRCERASE);
	putimage(x,y,&fm1[5],SRCINVERT);
}
void ffish7()
{
	putimage(x,y,&fm[6],NOTSRCERASE);
	putimage(x,y,&fm1[6],SRCINVERT);
}
void ffish8()
{
	putimage(x,y,&fm[7],NOTSRCERASE);
	putimage(x,y,&fm1[7],SRCINVERT);
}
void ffish9()
{
	putimage(x,y,&fm[8],NOTSRCERASE);
	putimage(x,y,&fm1[8],SRCINVERT);
}
void fzfish1()
{
	putimage(x,y,&fn[0],NOTSRCERASE);
	putimage(x,y,&fn1[0],SRCINVERT);
}
void fzfish2()
{
	putimage(x,y,&fn[1],NOTSRCERASE);
	putimage(x,y,&fn1[1],SRCINVERT);
}
void fzfish3()
{
	putimage(x,y,&fn[2],NOTSRCERASE);
	putimage(x,y,&fn1[2],SRCINVERT);
}
void fzfish4()
{
	putimage(x,y,&fn[3],NOTSRCERASE);
	putimage(x,y,&fn1[3],SRCINVERT);
}
void fzfish5()
{
	putimage(x,y,&fn[4],NOTSRCERASE);
	putimage(x,y,&fn1[4],SRCINVERT);
}
void fzfish6()
{
	putimage(x,y,&fn[5],NOTSRCERASE);
	putimage(x,y,&fn1[5],SRCINVERT);
}
void fzfish7()
{
	putimage(x,y,&fn[6],NOTSRCERASE);
	putimage(x,y,&fn1[6],SRCINVERT);
}
void fzfish8()
{
	putimage(x,y,&fn[7],NOTSRCERASE);
	putimage(x,y,&fn1[7],SRCINVERT);
}
void fzfish9()
{
	putimage(x,y,&fn[8],NOTSRCERASE);
	putimage(x,y,&fn1[8],SRCINVERT);
}
void fredfish1()
{
	putimage(x,y,&fm[0],NOTSRCERASE);
	putimage(x,y,&fred[0],SRCINVERT);
}
void fredfish2()
{
	putimage(x,y,&fm[1],NOTSRCERASE);
	putimage(x,y,&fred[1],SRCINVERT);
}
void fredfish3()
{
	putimage(x,y,&fm[2],NOTSRCERASE);
	putimage(x,y,&fred[2],SRCINVERT);
}
void fredfish4()
{
	putimage(x,y,&fm[3],NOTSRCERASE);
	putimage(x,y,&fred[3],SRCINVERT);
}
void fredfish5()
{
	putimage(x,y,&fm[4],NOTSRCERASE);
	putimage(x,y,&fred[4],SRCINVERT);
}
void fredfish6()
{
	putimage(x,y,&fm[5],NOTSRCERASE);
	putimage(x,y,&fred[5],SRCINVERT);
}
void fredfish7()
{
	putimage(x,y,&fm[6],NOTSRCERASE);
	putimage(x,y,&fred[6],SRCINVERT);
}
void fredfish8()
{
	putimage(x,y,&fm[7],NOTSRCERASE);
	putimage(x,y,&fred[7],SRCINVERT);
}
void fredfish9()
{
	putimage(x,y,&fm[8],NOTSRCERASE);
	putimage(x,y,&fred[8],SRCINVERT);
}
void fzredfish1()
{
	putimage(x,y,&fn[0],NOTSRCERASE);
	putimage(x,y,&fzred[0],SRCINVERT);
}
void fzredfish2()
{
	putimage(x,y,&fn[1],NOTSRCERASE);
	putimage(x,y,&fzred[1],SRCINVERT);
}
void fzredfish3()
{
	putimage(x,y,&fn[2],NOTSRCERASE);
	putimage(x,y,&fzred[2],SRCINVERT);
}
void fzredfish4()
{
	putimage(x,y,&fn[3],NOTSRCERASE);
	putimage(x,y,&fzred[3],SRCINVERT);
}
void fzredfish5()
{
	putimage(x,y,&fn[4],NOTSRCERASE);
	putimage(x,y,&fzred[4],SRCINVERT);
}
void fzredfish6()
{
	putimage(x,y,&fn[5],NOTSRCERASE);
	putimage(x,y,&fzred[5],SRCINVERT);
}
void fzredfish7()
{
	putimage(x,y,&fn[6],NOTSRCERASE);
	putimage(x,y,&fzred[6],SRCINVERT);
}
void fzredfish8()
{
	putimage(x,y,&fn[7],NOTSRCERASE);
	putimage(x,y,&fzred[7],SRCINVERT);
}
void fzredfish9()
{
	putimage(x,y,&fn[8],NOTSRCERASE);
	putimage(x,y,&fzred[8],SRCINVERT);
}
void fgreenfish1()
{
	putimage(x,y,&fm[0],NOTSRCERASE);
	putimage(x,y,&fgreen[0],SRCINVERT);
}
void fgreenfish2()
{
	putimage(x,y,&fm[1],NOTSRCERASE);
	putimage(x,y,&fgreen[1],SRCINVERT);
}
void fgreenfish3()
{
	putimage(x,y,&fm[2],NOTSRCERASE);
	putimage(x,y,&fgreen[2],SRCINVERT);
}
void fgreenfish4()
{
	putimage(x,y,&fm[3],NOTSRCERASE);
	putimage(x,y,&fgreen[3],SRCINVERT);
}
void fgreenfish5()
{
	putimage(x,y,&fm[4],NOTSRCERASE);
	putimage(x,y,&fgreen[4],SRCINVERT);
}
void fgreenfish6()
{
	putimage(x,y,&fm[5],NOTSRCERASE);
	putimage(x,y,&fgreen[5],SRCINVERT);
}
void fgreenfish7()
{
	putimage(x,y,&fm[6],NOTSRCERASE);
	putimage(x,y,&fgreen[6],SRCINVERT);
}
void fgreenfish8()
{
	putimage(x,y,&fm[7],NOTSRCERASE);
	putimage(x,y,&fgreen[7],SRCINVERT);
}
void fgreenfish9()
{
	putimage(x,y,&fm[8],NOTSRCERASE);
	putimage(x,y,&fgreen[8],SRCINVERT);
}
void fzgreenfish1()
{
	putimage(x,y,&fn[0],NOTSRCERASE);
	putimage(x,y,&fzgreen[0],SRCINVERT);
}
void fzgreenfish2()
{
	putimage(x,y,&fn[1],NOTSRCERASE);
	putimage(x,y,&fzgreen[1],SRCINVERT);
}
void fzgreenfish3()
{
	putimage(x,y,&fn[2],NOTSRCERASE);
	putimage(x,y,&fzgreen[2],SRCINVERT);
}
void fzgreenfish4()
{
	putimage(x,y,&fn[3],NOTSRCERASE);
	putimage(x,y,&fzgreen[3],SRCINVERT);
}
void fzgreenfish5()
{
	putimage(x,y,&fn[4],NOTSRCERASE);
	putimage(x,y,&fzgreen[4],SRCINVERT);
}
void fzgreenfish6()
{
	putimage(x,y,&fn[5],NOTSRCERASE);
	putimage(x,y,&fzgreen[5],SRCINVERT);
}
void fzgreenfish7()
{
	putimage(x,y,&fn[6],NOTSRCERASE);
	putimage(x,y,&fzgreen[6],SRCINVERT);
}
void fzgreenfish8()
{
	putimage(x,y,&fn[7],NOTSRCERASE);
	putimage(x,y,&fzgreen[7],SRCINVERT);
}
void fzgreenfish9()
{
	putimage(x,y,&fn[8],NOTSRCERASE);
	putimage(x,y,&fzgreen[8],SRCINVERT);
}
void fishmouth()
{
	p6=h;
	while(p6)
	{
		if(s.x+twidth>p6->fx&&s.x<p6->fx+p6->efishwidth&&s.y<p6->fy+p6->efishheigh&&s.y+theigh>p6->fy)
		{
			if(twidth>p6->efishwidth)
			{
				protect1=1;
				protect2=5;
			}
		}
		p6=p6->next;
	}
}
void controlbluesize()
{
	if(score<25)
		fish1();
	else if(score>=25&&score<75)
		fish2();
	else if(score>=75&&score<175)
		fish3();
	else if(score>=175&&score<275)
		fish4();
	else if(score>=275&&score<375)
		fish5();
	else if(score>=375&&score<475)
		fish6();
	else if(score>=475&&score<575)
		fish7();
	else if(score>=575&&score<675)
		fish8();
	else if(score>=675)
		fish9();
}
void controlzbluesize()
{
	if(score<25)
		zfish1();
	else if(score>=25&&score<75)
		zfish2();
	else if(score>=75&&score<175)
		zfish3();
	else if(score>=175&&score<275)
		zfish4();
	else if(score>=275&&score<375)
		zfish5();
	else if(score>=375&&score<475)
		zfish6();
	else if(score>=475&&score<575)
		zfish7();
	else if(score>=575&&score<675)
		zfish8();
	else if(score>=675)
		zfish9();
}
void controlredsize()
{
	if(score<25)
		redfish1();
	else if(score>=25&&score<75)
		redfish2();
	else if(score>=75&&score<175)
		redfish3();
	else if(score>=175&&score<275)
		redfish4();
	else if(score>=275&&score<375)
		redfish5();
	else if(score>=375&&score<475)
		redfish6();
	else if(score>=475&&score<575)
		redfish7();
	else if(score>=575&&score<675)
		redfish8();
	else if(score>=675)
		redfish9();
}
void controlzredsize()
{
	if(score<25)
		zredfish1();
	else if(score>=25&&score<75)
		zredfish2();
	else if(score>=75&&score<175)
		zredfish3();
	else if(score>=175&&score<275)
		zredfish4();
	else if(score>=275&&score<375)
		zredfish5();
	else if(score>=375&&score<475)
		zredfish6();
	else if(score>=475&&score<575)
		zredfish7();
	else if(score>=575&&score<675)
		zredfish8();
	else if(score>=675)
		zredfish9();
}
void controlgreensize()
{
	if(score<25)
		greenfish1();
	else if(score>=25&&score<75)
		greenfish2();
	else if(score>=75&&score<175)
		greenfish3();
	else if(score>=175&&score<275)
		greenfish4();
	else if(score>=275&&score<375)
		greenfish5();
	else if(score>=375&&score<475)
		greenfish6();
	else if(score>=475&&score<575)
		greenfish7();
	else if(score>=575&&score<675)
		greenfish8();
	else if(score>=675)
		greenfish9();
}
void controlzgreensize()
{
	if(score<25)
		zgreenfish1();
	else if(score>=25&&score<75)
		zgreenfish2();
	else if(score>=75&&score<175)
		zgreenfish3();
	else if(score>=175&&score<275)
		zgreenfish4();
	else if(score>=275&&score<375)
		zgreenfish5();
	else if(score>=375&&score<475)
		zgreenfish6();
	else if(score>=475&&score<575)
		zgreenfish7();
	else if(score>=575&&score<675)
		zgreenfish8();
	else if(score>=675)
		zgreenfish9();
}
void controlfbluesize()
{
	if(score<25)
		ffish1();
	else if(score>=25&&score<75)
		ffish2();
	else if(score>=75&&score<175)
		ffish3();
	else if(score>=175&&score<275)
		ffish4();
	else if(score>=275&&score<375)
		ffish5();
	else if(score>=375&&score<475)
		ffish6();
	else if(score>=475&&score<575)
		ffish7();
	else if(score>=575&&score<675)
		ffish8();
	else if(score>=675)
		ffish9();
}
void controlfzbluesize()
{
	if(score<25)
		fzfish1();
	else if(score>=25&&score<75)
		fzfish2();
	else if(score>=75&&score<175)
		fzfish3();
	else if(score>=175&&score<275)
		fzfish4();
	else if(score>=275&&score<375)
		fzfish5();
	else if(score>=375&&score<475)
		fzfish6();
	else if(score>=475&&score<575)
		fzfish7();
	else if(score>=575&&score<675)
		fzfish8();
	else if(score>=675)
		fzfish9();
}
void controlfredsize()
{
	if(score<25)
		fredfish1();
	else if(score>=25&&score<75)
		fredfish2();
	else if(score>=75&&score<175)
		fredfish3();
	else if(score>=175&&score<275)
		fredfish4();
	else if(score>=275&&score<375)
		fredfish5();
	else if(score>=375&&score<475)
		fredfish6();
	else if(score>=475&&score<575)
		fredfish7();
	else if(score>=575&&score<675)
		fredfish8();
	else if(score>=675)
		fredfish9();
}
void controlfzredsize()
{
	if(score<25)
		fzredfish1();
	else if(score>=25&&score<75)
		fzredfish2();
	else if(score>=75&&score<175)
		fzredfish3();
	else if(score>=175&&score<275)
		fzredfish4();
	else if(score>=275&&score<375)
		fzredfish5();
	else if(score>=375&&score<475)
		fzredfish6();
	else if(score>=475&&score<575)
		fzredfish7();
	else if(score>=575&&score<675)
		fzredfish8();
	else if(score>=675)
		fzredfish9();
}
void controlfgreensize()
{
	if(score<25)
		fgreenfish1();
	else if(score>=25&&score<75)
		fgreenfish2();
	else if(score>=75&&score<175)
		fgreenfish3();
	else if(score>=175&&score<275)
		fgreenfish4();
	else if(score>=275&&score<375)
		fgreenfish5();
	else if(score>=375&&score<475)
		fgreenfish6();
	else if(score>=475&&score<575)
		fgreenfish7();
	else if(score>=575&&score<675)
		fgreenfish8();
	else if(score>=675)
		fgreenfish9();
}
void controlfzgreensize()
{
	if(score<25)
		fzgreenfish1();
	else if(score>=25&&score<75)
		fzgreenfish2();
	else if(score>=75&&score<175)
		fzgreenfish3();
	else if(score>=175&&score<275)
		fzgreenfish4();
	else if(score>=275&&score<375)
		fzgreenfish5();
	else if(score>=375&&score<475)
		fzgreenfish6();
	else if(score>=475&&score<575)
		fzgreenfish7();
	else if(score>=575&&score<675)
		fzgreenfish8();
	else if(score>=675)
		fzgreenfish9();
}
void fishsize()
{
	if(score<25)
	{
		twidth=530/10;
		theigh=480/10;
	}
	else if(score>=25&&score<75)
	{
		twidth=530/10*2;
		theigh=480/10*2;
	}
	else if(score>=75&&score<175)
	{
		twidth=530/10*3;
		theigh=480/10*3;
	}
	else if(score>=175&&score<275)
	{
		twidth=530/10*4;
		theigh=480/10*4;
	}
	else if(score>=275&&score<375)
	{
		twidth=530/10*5;
		theigh=480/10*5;
	}
	else if(score>=475&&score<575)
	{
		twidth=530/10*6;
		theigh=480/10*6;
	}
	else if(score>=675&&score<775)
	{
		twidth=530/10*7;
		theigh=480/10*7;
	}
	else if(score>=775&&score<875)
	{
		twidth=530/10*8;
		theigh=480/10*8;
	}
	else if(score>=875&&score<975)
	{
		twidth=530/10*9;
		theigh=480/10*9;
	}
}
void outscore()
{
	char s[10];
	settextstyle(30,0,_T("黑体"));
	settextcolor(YELLOW);
	setbkmode(TRANSPARENT);
	outtextxy(0,0,"得分:");
	sprintf(s,"%d",score);
	outtextxy(80,0,_T(s));
}
void outfishlife()
{
	char s[10];
	settextstyle(30,0,_T("黑体"));
	settextcolor(RED);
	setbkmode(TRANSPARENT);
	outtextxy(850,0,"生命:");
	sprintf(s,"%d",life);
	outtextxy(930,0,_T(s));
}
void controlscore()
{
	p1=h;
	while(p1)
	{
		if(s.x+twidth>p1->fx&&s.x<p1->fx+p1->efishwidth&&s.y<p1->fy+p1->efishheigh&&s.y+theigh>p1->fy)
		{
			if(twidth>p1->efishwidth)
			{
				if(p1->level==0||p1->level==1||p1->level==2)
					score=score+10;					
				else if(p1->level==3||p1->level==4)
					score=score+15;
				else if(p1->level==5||p1->level==6)
					score=score+25;
				else if(p1->level==7)
					score=score+40;			
				else if(p1->level==8)
					score=score+60;
			}
		}
		p1=p1->next;
	}	
}
void initgraphjudge()
{
	p4=h;
	q4=h;
	while(p4)
	{
		if(p4->fx>1000||p4->fx<-400)
		{
				p4->fy=rand()%572;
				if(p4->direction==0)
					p4->fx=1000;
				else if(p4->direction==1)
					p4->fx=-400;
				p4->level=rand()%9;
				if(p4->level==0||p4->level==1||p4->level==2)
				{
					p4->efishwidth=35;
					p4->efishheigh=29;
				}
				else if(p4->level==3||p4->level==4)
				{
					p4->efishwidth=90;
					p4->efishheigh=72;
				}
				else if(p4->level==5||p4->level==6)
				{
					p4->efishwidth=200;
					p4->efishheigh=156;
				}
				else if(p4->level==7)
				{
					p4->efishwidth=300;
					p4->efishheigh=202;
				}
				else if(p4->level==8)
				{
					p4->efishwidth=400;
					p4->efishheigh=207;
				}
		}
		p4=p4->next;
	}
}
void makeefish()
{
	if(number<10)
	{
		p=(struct efishkind*)malloc(sizeof(struct efishkind));
		p->next=NULL;
		srand((unsigned) time(NULL));
		p->level=rand()%9;
		srand((unsigned) time(NULL));
		p->direction=rand()%2;
		srand(time(0));
		p->fy=rand()%572;
		if(p->direction==0)
		{
			p->fx=1000;
			if(p->level==0||p->level==1||p->level==2)
			{
				p->v=-5;
				p->efishwidth=35;
				p->efishheigh=29;
			}
			else if(p->level==3||p->level==4)
			{
				p->v=-4;
				p->efishwidth=90;
				p->efishheigh=72;
			}
			else if(p->level==5||p->level==6)
			{
				p->v=-3;
				p->efishwidth=200;
				p->efishheigh=156;
			}
			else if(p->level==7)
			{
				p->v=-2;
				p->efishwidth=300;
				p->efishheigh=202;
			}
			else if(p->level==8)
			{
				p->v=-1;
				p->efishwidth=400;
				p->efishheigh=207;
			}
		}
		else if(p->direction==1)
		{
			p->fx=-400;
			if(p->level==0||p->level==1||p->level==2)
			{
				p->v=5;
				p->efishwidth=35;
				p->efishheigh=29;
			}
			else if(p->level==3||p->level==4)
			{
				p->v=4;
				p->efishwidth=90;
				p->efishheigh=72;
			}
			else if(p->level==5||p->level==6)
			{
				p->v=3;
				p->efishwidth=200;
				p->efishheigh=156;
			}
			else if(p->level==7)
			{
				p->v=2;
				p->efishwidth=300;
				p->efishheigh=202;
			}
			else if(p->level==8)
			{
				p->v=1;
				p->efishwidth=400;
				p->efishheigh=207;
			}
		}
		if(h==NULL)
		{
			h=p;
			q=p;
		}
		else
		{
			q->next=p;
			p=p->next;
			q=q->next;
		}
		number=number+1;
	}
}
void showefish()
{
	p=h;
	while(p)
	{
		if(p->direction==0)
		{
			if(p->level==0||p->level==1||p->level==2)
			{
				putimage(p->fx,p->fy,&m131,NOTSRCERASE);
				putimage(p->fx,p->fy,&m132,SRCINVERT);
			}
			else if(p->level==3||p->level==4)
			{
				putimage(p->fx,p->fy,&m151,NOTSRCERASE);
				putimage(p->fx,p->fy,&m152,SRCINVERT);
			}
			else if(p->level==5||p->level==6)
			{
				putimage(p->fx,p->fy,&m141,NOTSRCERASE);
				putimage(p->fx,p->fy,&m142,SRCINVERT);
			}
			else if(p->level==7)
			{
				putimage(p->fx,p->fy,&m161,NOTSRCERASE);
				putimage(p->fx,p->fy,&m162,SRCINVERT);
			}
			else if(p->level==8)
			{
				putimage(p->fx,p->fy,&m121,NOTSRCERASE);
				putimage(p->fx,p->fy,&m122,SRCINVERT);
			}
		}
		else if(p->direction==1)
		{
			if(p->level==0||p->level==1||p->level==2)
			{
				putimage(p->fx,p->fy,&fm131,NOTSRCERASE);
				putimage(p->fx,p->fy,&fm132,SRCINVERT);
			}
			else if(p->level==3||p->level==4)
			{
				putimage(p->fx,p->fy,&fm151,NOTSRCERASE);
				putimage(p->fx,p->fy,&fm152,SRCINVERT);
			}
			else if(p->level==5||p->level==6)
			{
				putimage(p->fx,p->fy,&fm141,NOTSRCERASE);
				putimage(p->fx,p->fy,&fm142,SRCINVERT);
			}
			else if(p->level==7)
			{
				putimage(p->fx,p->fy,&fm161,NOTSRCERASE);
				putimage(p->fx,p->fy,&fm162,SRCINVERT);
			}
			else if(p->level==8)
			{
				putimage(p->fx,p->fy,&fm121,NOTSRCERASE);
				putimage(p->fx,p->fy,&fm122,SRCINVERT);
			}
		}
		p=p->next;
	}
}
void efishcontrol()
{
	p=h;
	while(p)
	{
		p->fx=p->fx+p->v;
		p=p->next;
	}
}
void loadpcture()
{
	loadimage(&m20,"C:\\Users\\10614\\Desktop\\大鱼吃小鱼项目图片\\20.jpg",1000,572);
	loadimage(&m8,"C:\\Users\\10614\\Desktop\\大鱼吃小鱼项目图片\\8.jpg");
	loadimage(&m1011,"C:\\Users\\10614\\Desktop\\大鱼吃小鱼项目图片\\10.1.1.jpg",fishwidth,fishheigh);
	loadimage(&m1012,"C:\\Users\\10614\\Desktop\\大鱼吃小鱼项目图片\\10.1.2.jpg",fishwidth,fishheigh);
	loadimage(&m131,"C:\\Users\\10614\\Desktop\\大鱼吃小鱼项目图片\\13.1.jpg");
	loadimage(&m132,"C:\\Users\\10614\\Desktop\\大鱼吃小鱼项目图片\\13.2.jpg");
	loadimage(&fm131,"C:\\Users\\10614\\Desktop\\大鱼吃小鱼项目图片\\f13.1.jpg");
	loadimage(&fm132,"C:\\Users\\10614\\Desktop\\大鱼吃小鱼项目图片\\f13.2.jpg");
	loadimage(&m151,"C:\\Users\\10614\\Desktop\\大鱼吃小鱼项目图片\\15.1.jpg");
	loadimage(&m152,"C:\\Users\\10614\\Desktop\\大鱼吃小鱼项目图片\\15.2.jpg");
	loadimage(&fm151,"C:\\Users\\10614\\Desktop\\大鱼吃小鱼项目图片\\f15.1.jpg");
	loadimage(&fm152,"C:\\Users\\10614\\Desktop\\大鱼吃小鱼项目图片\\f15.2.jpg");
	loadimage(&fm141,"C:\\Users\\10614\\Desktop\\大鱼吃小鱼项目图片\\f14.1.jpg");
	loadimage(&fm142,"C:\\Users\\10614\\Desktop\\大鱼吃小鱼项目图片\\f14.2.jpg");
	loadimage(&m141,"C:\\Users\\10614\\Desktop\\大鱼吃小鱼项目图片\\14.1.jpg");
	loadimage(&m142,"C:\\Users\\10614\\Desktop\\大鱼吃小鱼项目图片\\14.2.jpg");
	loadimage(&m161,"C:\\Users\\10614\\Desktop\\大鱼吃小鱼项目图片\\16.1.jpg");
	loadimage(&m162,"C:\\Users\\10614\\Desktop\\大鱼吃小鱼项目图片\\16.2.jpg");
	loadimage(&fm161,"C:\\Users\\10614\\Desktop\\大鱼吃小鱼项目图片\\f16.1.jpg");
	loadimage(&fm162,"C:\\Users\\10614\\Desktop\\大鱼吃小鱼项目图片\\f16.2.jpg");
	loadimage(&fm121,"C:\\Users\\10614\\Desktop\\大鱼吃小鱼项目图片\\f12.1.jpg");
	loadimage(&fm122,"C:\\Users\\10614\\Desktop\\大鱼吃小鱼项目图片\\f12.2.jpg");
	loadimage(&m121,"C:\\Users\\10614\\Desktop\\大鱼吃小鱼项目图片\\12.1.jpg");
	loadimage(&m122,"C:\\Users\\10614\\Desktop\\大鱼吃小鱼项目图片\\12.2.jpg");
}
void loadsize()
{
	for(int j=0;j<10;j++)
	{
		grow[j]=j+1;
		loadimage(&m[j],"C:\\Users\\10614\\Desktop\\大鱼吃小鱼项目图片\\10.1.1.jpg",fishwidth*grow[j],fishheigh*grow[j]);
		loadimage(&m1[j],"C:\\Users\\10614\\Desktop\\大鱼吃小鱼项目图片\\10.1.2.jpg",fishwidth*grow[j],fishheigh*grow[j]);
		loadimage(&n[j],"C:\\Users\\10614\\Desktop\\大鱼吃小鱼项目图片\\21.1.jpg",fishwidth*grow[j],fishheigh*grow[j]);
		loadimage(&n1[j],"C:\\Users\\10614\\Desktop\\大鱼吃小鱼项目图片\\21.2.jpg",fishwidth*grow[j],fishheigh*grow[j]);
		loadimage(&red[j],"C:\\Users\\10614\\Desktop\\大鱼吃小鱼项目图片\\red10.1.2.jpg",fishwidth*grow[j],fishheigh*grow[j]);
		loadimage(&zred[j],"C:\\Users\\10614\\Desktop\\大鱼吃小鱼项目图片\\red21.2.jpg",fishwidth*grow[j],fishheigh*grow[j]);
		loadimage(&green[j],"C:\\Users\\10614\\Desktop\\大鱼吃小鱼项目图片\\green10.1.2.jpg",fishwidth*grow[j],fishheigh*grow[j]);
		loadimage(&zgreen[j],"C:\\Users\\10614\\Desktop\\大鱼吃小鱼项目图片\\green21.2.jpg",fishwidth*grow[j],fishheigh*grow[j]);

		loadimage(&fm[j],"C:\\Users\\10614\\Desktop\\大鱼吃小鱼项目图片\\f10.1.1.jpg",fishwidth*grow[j],fishheigh*grow[j]);
		loadimage(&fm1[j],"C:\\Users\\10614\\Desktop\\大鱼吃小鱼项目图片\\f10.1.2.jpg",fishwidth*grow[j],fishheigh*grow[j]);
		loadimage(&fn[j],"C:\\Users\\10614\\Desktop\\大鱼吃小鱼项目图片\\f21.1.jpg",fishwidth*grow[j],fishheigh*grow[j]);
		loadimage(&fn1[j],"C:\\Users\\10614\\Desktop\\大鱼吃小鱼项目图片\\f21.2.jpg",fishwidth*grow[j],fishheigh*grow[j]);
		loadimage(&fred[j],"C:\\Users\\10614\\Desktop\\大鱼吃小鱼项目图片\\fred10.1.2.jpg",fishwidth*grow[j],fishheigh*grow[j]);
		loadimage(&fzred[j],"C:\\Users\\10614\\Desktop\\大鱼吃小鱼项目图片\\fred21.2.jpg",fishwidth*grow[j],fishheigh*grow[j]);
		loadimage(&fgreen[j],"C:\\Users\\10614\\Desktop\\大鱼吃小鱼项目图片\\fgreen10.1.2.jpg",fishwidth*grow[j],fishheigh*grow[j]);
		loadimage(&fzgreen[j],"C:\\Users\\10614\\Desktop\\大鱼吃小鱼项目图片\\fgreen21.2.jpg",fishwidth*grow[j],fishheigh*grow[j]);
	}
}
void mouse()
{
		if(MouseHit())
			s=GetMouseMsg();
		x=s.x;
		y=s.y;
		if(MouseHit())
			FlushMouseMsgBuffer();
}
void game()
{
	int x1,x2,x3;
	int dream=0;
	loadpcture();
	loadsize();
	protect=0;
	h=NULL;
	s=GetMouseMsg();
	for(i=1;;i++)
	{
		protect1=0;
		BeginBatchDraw();
		if(i==1000)
			i=1;
		fishsize();
		x1=s.x;
		mouse();
		x2=s.x;
		gameback();
		if(i%100==0)
			makeefish();
		showefish();
		efishcontrol();
		fishmouth();
		if(protect1==1)
		{
			mciSendString("close jpmusic1",NULL,0,NULL);
			mciSendString(_T("open C:\\Users\\10614\\Desktop\\大鱼吃小鱼项目图片\\吃东西.mp3 alias jpmusic1"), NULL, 0, NULL);
			mciSendString("play jpmusic1",NULL,0,NULL);
		}
		if(x2-x1>0)
		{
			dream=1;
			if(protect1==1||protect2!=0)
			{
				if(life==3)
					controlzbluesize();
				else if(life==2)
					controlzgreensize();
				else if(life==1)
					controlzredsize();
			}
			else 
			{
				if(life==3)
					controlbluesize();
				else if(life==2)
					controlgreensize();
				else if(life==1)
					controlredsize();
			}
		}
		else if(x2-x1<0)
		{
			dream=0;
			if(protect1==1||protect2!=0)
			{
				if(life==3)
					controlfzbluesize();
				else if(life==2)
					controlfzgreensize();
				else if(life==1)
					controlfzredsize();
			}
			else
			{
				if(life==3)
					controlfbluesize();
				else if(life==2)
					controlfgreensize();
				else if(life==1)
					controlfredsize();
			}
		}
		else if(x2-x1==0)
		{
			if(dream==1)
			{
				if(protect1==1||protect2!=0)
				{
					if(life==3)
						controlzbluesize();
					else if(life==2)
						controlzgreensize();
					else if(life==1)
						controlzredsize();
				}
				else 
				{
					if(life==3)
						controlbluesize();
					else if(life==2)
						controlgreensize();
					else if(life==1)
						controlredsize();
				}
			}
			else if(dream==0)
			{
				if(protect1==1||protect2!=0)
				{
					if(life==3)
						controlfzbluesize();
					else if(life==2)
						controlfzgreensize();
					else if(life==1)
						controlfzredsize();
				}
				else
				{
					if(life==3)
						controlfbluesize();
					else if(life==2)
						controlfgreensize();
					else if(life==1)
						controlfredsize();
				}
			}
		}
		controlscore();
		outscore();
		fisheat();
		outfishlife();
		if(h!=NULL)
			initgraphjudge();
		if(protect==0)
		{
			protect=30;
			if(a!=0)
				controllife();
		}
		if(protect!=0)
			protect--;
		if(protect2!=0)
			protect2--;
		if(life<1)
			gameover();
		if(score>2000)
			cow();
		Sleep(30);
		FlushBatchDraw();
	}
	EndBatchDraw();
}
void startshow()
{
	cleardevice();
	loadimage(&m5,"C:\\Users\\10614\\Desktop\\大鱼吃小鱼项目图片\\5.jpg");
	putimage(0,0,&m5);
	FlushBatchDraw();
	while(1)
	{
		fflush(stdin);
		char a=getch();
		switch(a)
		{
			case '1':{game();break;}
			case '2':{hack();break;}
			case '3':exit(0);
			default:break;
		}
	}
}//初始界面
void gameback()
{
	putimage(0,0,&m8);
}
int main()
{
	initgraph(1000,572);
	mciSendString("open C:\\Users\\10614\\Desktop\\大鱼吃小鱼项目图片\\纯音乐-大海的声音.mp3 alias jpmusic",NULL,0,NULL);
	mciSendString("play jpmusic repeat",NULL,0,NULL);
	startshow();
	return 0;
}
