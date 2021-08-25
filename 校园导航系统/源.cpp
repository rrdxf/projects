#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<Windows.h>
#include<string.h>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXEDGE 20
#define MAXVEX 10
#define INFINITY 999999
#define MAX_PATHS_BETWEEN_TWO_NODES_NUM (MAXVEX+10)
#define REACHABLE 1
typedef int Status;    /* Status是函数的类型*/

typedef struct
{
    int vexs[MAXVEX];//点的序号 
    int arc[MAXVEX][MAXVEX];//邻边矩阵 
    int numVertexes, numEdges;//点数，边数 
    int visited[MAXVEX];//访问标志 
}MGraph;
struct Path
{
	int size;
	int nodes[MAXVEX];
};

typedef int Patharc[MAXVEX][MAXVEX];
typedef int ShortPathTable[MAXVEX][MAXVEX];
//地图结构体
typedef struct pecture
{
	IMAGE P;
	int x;
	int y;
}MAP;
//存储路径坐标
typedef struct path
{
	int x;
	int y;
	struct path *next;
}PATH;
//存储各个景点坐标信息
typedef struct sen
{
	wchar_t name[20];
	wchar_t intro[50];
	int x;
	int y;
}SENCE;
//鼠标指针结构体
typedef struct mouse
{
	IMAGE P;
	IMAGE P1;
	int sign;
}MUSE;
//存储每条路径端点结构体
typedef struct terminal
{
	int sen1;//路径起点
	int sen2;//路径终点
}TERMINAl;
int c[MAXVEX];//景点代号多个景点的最优路径要用
TERMINAl sen[26];
MAP map1,map2;
MUSE muse;
IMAGE f;//初始界面
IMAGE guide,guide1;//路牌图片
int patsign=0;//路线端点数量标记	
SENCE sence_pit[10];
int pah[13];//存储路径的数组
PATH *path[26];//存储路线的链表头指针函数
int m;//求关节点的全局变量
int txx(MOUSEMSG p,int mx);
int tyy(MOUSEMSG p,int my);
void point(SENCE point);
void drawpath(PATH *path);
void guideboard(int x,int y)
{
	
	putimage(x,y,&guide1,NOTSRCERASE);
	putimage(x,y,&guide,SRCINVERT);
}
//存储每条路径的端点函数
void loadter()
{
	//窦->校史馆
	sen[0].sen1=0;
	sen[0].sen2=1;
	//校史馆->窦
	sen[1].sen1=1;
	sen[1].sen2=0;
	//校史馆->柏林
	sen[2].sen1=1;
	sen[2].sen2=2;
	//柏林->校史馆
	sen[3].sen1=2;
	sen[3].sen2=1;
	//校史馆->铁路
	sen[4].sen1=1;
	sen[4].sen2=3;
	//铁路->校史馆
	sen[5].sen1=3;
	sen[5].sen2=1;
	//柏林->二龙
	sen[6].sen1=2;
	sen[6].sen2=4;
	//二龙->柏林
	sen[7].sen1=4;
	sen[7].sen2=2;
	//二龙->四食堂
	sen[8].sen1=4;
	sen[8].sen2=5;
	//四食堂->二龙
	sen[9].sen1=5;
	sen[9].sen2=4;
	//四食堂->铁路
	sen[10].sen1=5;
	sen[10].sen2=3;
	//铁路->四食堂
	sen[11].sen1=3;
	sen[11].sen2=5;
	//铁路->行知广场
	sen[12].sen1=3;
	sen[12].sen2=6;
	//行知广场->铁路
	sen[13].sen1=6;
	sen[13].sen2=3;
	//四食堂->图书
	sen[14].sen1=5;
	sen[14].sen2=7;
	//图书->四食堂
	sen[15].sen1=7;
	sen[15].sen2=5;
	//图书->行知
	sen[16].sen1=7;
	sen[16].sen2=6;
	//行知->图书
	sen[17].sen1=6;
	sen[17].sen2=7;
	//龙山->行知
	sen[18].sen1=9;
	sen[18].sen2=6;
	//行知->龙山
	sen[19].sen1=6;
	sen[19].sen2=9;
	//游泳->图书
	sen[20].sen1=8;
	sen[20].sen2=7;
	//图书->游泳
	sen[21].sen1=7;
	sen[21].sen2=8;
	//游泳->龙山
	sen[22].sen1=8;
	sen[22].sen2=9;
	//龙山->游泳
	sen[23].sen1=9;
	sen[23].sen2=8;
	//铁路->柏林
	sen[24].sen1=3;
	sen[24].sen2=2;
	//柏林->铁路
	sen[25].sen1=2;
	sen[25].sen2=3;
}
//端点匹配路径之后输出
void teradpath(int sen1,int sen2)
{
	int k;
	for(k=0;k<26;k++)
	{
		if((sen1==sen[k].sen1)&&(sen2==sen[k].sen2))
			break;
	}
	if(k<26)
		drawpath(path[k]);
}
//建立路径的链表
struct path *creatpath(struct path *path,int x,int y)
{
	PATH *p,*q;
	p=(PATH *)malloc(sizeof(struct path));
	p->next=NULL;
	p->x=x;
	p->y=y;
	if(path==NULL)
	{
		path=p;
	}
	else
	{
		q=path;
		while(q->next)
		{
			q=q->next;
		}
		q->next=p;
	}
	return path;
}
void loadpath()
{	
	path[0]=creatpath(path[0],302,1179);
	path[0]=creatpath(path[0],386,1239);
	path[0]=creatpath(path[0],522,1360);
	path[0]=creatpath(path[0],594,1377);
	path[0]=creatpath(path[0],629,1379);
	path[0]=creatpath(path[0],629,1341);
	path[0]=creatpath(path[0],530,1349);
	path[0]=creatpath(path[0],497,1322);
	path[0]=creatpath(path[0],489,1179);
	path[1]=creatpath(path[1],489,1179);
	path[1]=creatpath(path[1],497,1322);
	path[1]=creatpath(path[1],530,1349);
	path[1]=creatpath(path[1],629,1341);
	path[1]=creatpath(path[1],629,1379);
	path[1]=creatpath(path[1],594,1377);
	path[1]=creatpath(path[1],522,1360);
	path[1]=creatpath(path[1],386,1239);
	path[1]=creatpath(path[1],302,1179);
	path[2]=creatpath(path[2],489,1179);
	path[2]=creatpath(path[2],488,1075);
	path[2]=creatpath(path[2],505,1045);
	path[2]=creatpath(path[2],602,1028);
	path[2]=creatpath(path[2],601,965);
	path[2]=creatpath(path[2],613,933);
	path[2]=creatpath(path[2],600,920);
	path[2]=creatpath(path[2],600,895);
	path[2]=creatpath(path[2],517,917);
	path[3]=creatpath(path[3],517,917);
	path[3]=creatpath(path[3],600,895);
	path[3]=creatpath(path[3],600,920);
	path[3]=creatpath(path[3],613,933);
	path[3]=creatpath(path[3],601,965);
	path[3]=creatpath(path[3],602,1028);
	path[3]=creatpath(path[3],505,1045);
	path[3]=creatpath(path[3],488,1075);
	path[3]=creatpath(path[3],489,1179);
	path[4]=creatpath(path[4],489,1179);
	path[4]=creatpath(path[4],488,1075);
	path[4]=creatpath(path[4],505,1045);
	path[4]=creatpath(path[4],602,1029);
	path[4]=creatpath(path[4],601,965);
	path[4]=creatpath(path[4],613,933);
	path[4]=creatpath(path[4],852,892);
	path[4]=creatpath(path[4],983,881);
	path[4]=creatpath(path[4],990,907);
	path[5]=creatpath(path[5],990,907);
	path[5]=creatpath(path[5],983,881);
	path[5]=creatpath(path[5],852,892);
	path[5]=creatpath(path[5],613,933);
	path[5]=creatpath(path[5],601,965);
	path[5]=creatpath(path[5],602,1029);
	path[5]=creatpath(path[5],505,1045);
	path[5]=creatpath(path[5],488,1179);
	path[5]=creatpath(path[5],489,1179);
	path[6]=creatpath(path[6],517,917);
	path[6]=creatpath(path[6],600,895);
	path[6]=creatpath(path[6],587,599);
	path[6]=creatpath(path[6],497,600);
	path[7]=creatpath(path[7],497,600);
	path[7]=creatpath(path[7],587,599);
	path[7]=creatpath(path[7],600,895);
	path[7]=creatpath(path[7],517,917);
	path[8]=creatpath(path[8],497,600);
	path[8]=creatpath(path[8],587,599);
	path[8]=creatpath(path[8],653,586);
	path[8]=creatpath(path[8],834,586);
	path[8]=creatpath(path[8],839,622);
	path[9]=creatpath(path[9],839,622);
	path[9]=creatpath(path[9],834,586);
	path[9]=creatpath(path[9],653,586);
	path[9]=creatpath(path[9],587,599);
	path[9]=creatpath(path[9],497,600);
	path[10]=creatpath(path[10],839,622);
	path[10]=creatpath(path[10],839,843);
	path[10]=creatpath(path[10],852,892);
	path[10]=creatpath(path[10],983,881);
	path[10]=creatpath(path[10],990,907);
	path[11]=creatpath(path[11],990,907);
	path[11]=creatpath(path[11],983,881);
	path[11]=creatpath(path[11],852,892);
	path[11]=creatpath(path[11],839,843);
	path[11]=creatpath(path[11],839,622);
	path[12]=creatpath(path[12],990,907);
	path[12]=creatpath(path[12],1426,833);
	path[12]=creatpath(path[12],1425,777);
	path[13]=creatpath(path[13],1425,777);
	path[13]=creatpath(path[13],1426,833);
	path[13]=creatpath(path[13],990,907);
	path[14]=creatpath(path[14],839,622);
	path[14]=creatpath(path[14],834,586);
	path[14]=creatpath(path[14],1117,547);
	path[14]=creatpath(path[14],1234,536);
	path[15]=creatpath(path[15],1234,536);
	path[15]=creatpath(path[15],1117,547);
	path[15]=creatpath(path[15],834,586);
	path[15]=creatpath(path[15],839,622);
	path[16]=creatpath(path[16],1234,536);
	path[16]=creatpath(path[16],1320,530);
	path[16]=creatpath(path[16],1348,781);
	path[16]=creatpath(path[16],1425,777);
	path[17]=creatpath(path[17],1425,777);
	path[17]=creatpath(path[17],1348,781);
	path[17]=creatpath(path[17],1320,530);
	path[17]=creatpath(path[17],1234,536);
	path[18]=creatpath(path[18],1984,268);
	path[18]=creatpath(path[18],1994,512);
	path[18]=creatpath(path[18],1480,528);
	path[18]=creatpath(path[18],1494,775);
	path[18]=creatpath(path[18],1429,776);
	path[19]=creatpath(path[19],1429,776);
	path[19]=creatpath(path[19],1494,775);
	path[19]=creatpath(path[19],1480,528);
	path[19]=creatpath(path[19],1994,512);
	path[19]=creatpath(path[19],1984,268);
	path[20]=creatpath(path[20],1269,309);
	path[20]=creatpath(path[20],1276,367);
	path[20]=creatpath(path[20],1314,408);
	path[20]=creatpath(path[20],1320,530);
	path[20]=creatpath(path[20],1234,536);
	path[21]=creatpath(path[21],1234,536);
	path[21]=creatpath(path[21],1320,530);
	path[21]=creatpath(path[21],1314,408);
	path[21]=creatpath(path[21],1276,367);
	path[21]=creatpath(path[21],1269,309);
	path[22]=creatpath(path[22],1269,309);
	path[22]=creatpath(path[22],1647,277);
	path[22]=creatpath(path[22],1984,268);
	path[23]=creatpath(path[23],1984,268);
	path[23]=creatpath(path[23],1647,277);
	path[23]=creatpath(path[23],1269,309);
	path[24]=creatpath(path[24],990,907);
	path[24]=creatpath(path[24],990,883);
	path[24]=creatpath(path[24],861,893);
	path[24]=creatpath(path[24],751,909);
	path[24]=creatpath(path[24],621,933);
	path[24]=creatpath(path[24],610,919);
	path[24]=creatpath(path[24],609,895);
	path[24]=creatpath(path[24],517,917);
	path[25]=creatpath(path[25],517,917);
	path[25]=creatpath(path[25],609,895);
	path[25]=creatpath(path[25],610,919);
	path[25]=creatpath(path[25],621,933);
	path[25]=creatpath(path[25],751,909);
	path[25]=creatpath(path[25],861,893);
	path[25]=creatpath(path[25],990,883);
	path[25]=creatpath(path[25],990,907);

}
//计算路线在地图上的坐标
struct path* push1(struct path *path,MOUSEMSG m,int x,int y)
{
	PATH *p;
	int ix,iy;
	if(m.mkLButton)
	{
		ix=txx(m,x);
		iy=tyy(m,y);
	}
	else
	{
		ix=0;
		iy=0;
	}
	p=path;
	while(p)
	{
		p->x=p->x-ix;
		p->y=p->y-iy;
		p=p->next;
	}
	return path;
}
//计算拖拽地图后各点的坐标
void push2(MOUSEMSG m,int x,int y)
{
	int ix,iy;
	if(m.mkLButton)
	{
		ix=txx(m,x);
		iy=tyy(m,y);
	}
	else
	{
		ix=0;
		iy=0;
	}
	for(int i=0;i<10;i++)
	{
		sence_pit[i].x-=ix;
		sence_pit[i].y-=iy;
	}
}
//在地图上画出对应的线路
void drawpath(PATH *path)
{
	PATH *p;
	p=path;
	setbkmode(TRANSPARENT);//设置背景为透明的
	setlinestyle(PS_SOLID | PS_JOIN_ROUND, 3);//实线接线处圆弧，像素为五
	while(p->next)
	{
		setlinecolor(HSLtoRGB(rand()%360,1,0.5));
		line(p->x, p->y, p->next->x, p->next->y);
		p=p->next;
	}
}
//存储各个景点的信息
void sence()
{
	//窦大夫
	sence_pit[0].x=301;
	sence_pit[0].y=1177;
	//校史馆
	sence_pit[1].x=489;
	sence_pit[1].y=1179;
	//柏林园
	sence_pit[2].x=517;
	sence_pit[2].y=917;
	//铁路公园
	sence_pit[3].x=990;
	sence_pit[3].y=907;
	//二龙山
	sence_pit[4].x=497;
	sence_pit[4].y=600;
	//四食堂
	sence_pit[5].x=839;
	sence_pit[5].y=622;
	//行知广场
	sence_pit[6].x=1425;
	sence_pit[6].y=777;
	//图书馆
	sence_pit[7].x=1234;
	sence_pit[7].y=536;
	//游泳馆
	sence_pit[8].x=1269;
	sence_pit[8].y=309;
	//龙山餐厅
	sence_pit[9].x=1984;
	sence_pit[9].y=268;
}
//在地图上输出各景点位置
void point(SENCE point)
{
	setfillstyle(BS_SOLID);
	setfillcolor(HSLtoRGB(rand()%360,1,0.5));
	solidcircle(point.x,point.y,5);//画圆
}
//计算鼠标相对位置的x值
int txx(MOUSEMSG p,int mx)
{
	int tx;
	tx=mx-p.x;
	return tx;
}
int tyy(MOUSEMSG p,int my)	//计算鼠标相对位置的y值
{
	int ty;
	ty=my-p.y;
	return ty;
}

//实现地图的拖拽功能
void push(MOUSEMSG m,int x,int y)
{
	int ix,iy;
	if(m.mkLButton)
	{
		ix=txx(m,x);
		iy=tyy(m,y);
	}
	else
	{
		ix=0;
		iy=0;
	}
	map2.x=map2.x-ix;
	map2.y=map2.y-iy;
}

//判断输出鼠标人形箭头
void child(MOUSEMSG m,int mx,int my)
{
	int ix;
	ix=mx-m.x;
	if(ix>0)
		muse.sign=-1;
	else if(ix==0)
		muse.sign=muse.sign;
	else if(ix<0)
		muse.sign=1;
	if(muse.sign==1)
	{
		loadimage(&muse.P,_T("针.jpg"));
		loadimage(&muse.P1,_T("针罩图.jpg"));
	}
	else if(muse.sign==-1)
	{
		loadimage(&muse.P,_T("反向针.jpg"));
		loadimage(&muse.P1,_T("反向针罩图.jpg"));
	}
	putimage(m.x,m.y,&muse.P1,NOTSRCERASE);
	putimage(m.x,m.y,&muse.P,SRCINVERT);
}
//鼠标圆形区域判断
int  circlejuge(MOUSEMSG m)
{
	int i;
	for(i=0;i<10;i++)
	{
		if(((m.x-sence_pit[i].x)*(m.x-sence_pit[i].x)+(m.y-sence_pit[i].y)*(m.y-sence_pit[i].y))<=100)
			break;
	}
	if(i<10)
	{
		patsign++;//路线端点数量标记	
		return i;	
	}
}

//任意两点所有路径
void AllPaths(int map[MAXVEX][MAXVEX],int n ,int start,int end,int NodeUsed[],struct Path paths[],int * pathsNum)
{
	int i,j;
	struct Path tempPaths[MAX_PATHS_BETWEEN_TWO_NODES_NUM]; 
	int tempPathsNum ;
// 标记当前起点不可用 
	NodeUsed[start] = TRUE;
	for(i=0;i<n;i++)
	{
	// 节点不在路径中，且可以到达 
		if(NodeUsed[i] == FALSE && map[start][i]== REACHABLE) 
		{
			// 当前起点能直接到达终点 
			if(i == end)
			{
				paths[(*pathsNum)].size = 2;
				paths[(*pathsNum)].nodes[0] = end;
				paths[(*pathsNum)].nodes[1] = start;
				(*pathsNum)++; 
			}
		// 当前起点能不能直接到达终点，尝试当前节点通过其他节点达到终点 
			else
			{
				// 递归计算从当前起点到达终点的所有路径 
				tempPathsNum = 0;
				AllPaths(map,n,i,end,NodeUsed,tempPaths,&tempPathsNum);
				// 处理找到的，从当前起点到达终点的所有路径 
				for(j=0;j<tempPathsNum;j++)
				{
				// 在当前起点到达终点的所有路径中，添加当前起点 
					tempPaths[j].nodes[tempPaths[j].size] = start;
					tempPaths[j].size ++;	
				// 合并到最终的路径中 
					paths[(*pathsNum)] = tempPaths[j];
					(*pathsNum)++; 
				} 
			} 
		} 
	}
	NodeUsed[start] = FALSE;
}
void print_AllPaths(int s,int e)
{
	int map[MAXVEX][MAXVEX];
	int NodeUsed[MAXVEX];
	struct Path paths[MAX_PATHS_BETWEEN_TWO_NODES_NUM];
	int pathsNum;	
	int i,j;
	int start,end;
	int a,b;
	int n,m;
	// 读取点数，路径数 
	n=10;
	m=13;
	// 初始化图 
		for(i=0;i<n;i++)
		{
			NodeUsed[i] = FALSE;
			for(j=0;j<n;j++)
			{
				map[i][j] = INFINITY;
			} 
		}
			// 标记 a b 间有路径，注意是无向图，标记两次 
			map[0][1] = REACHABLE; 
			map[1][0] = REACHABLE;
			map[1][2] = REACHABLE;
			map[2][1] = REACHABLE;
			map[1][3] = REACHABLE;
			map[3][1] = REACHABLE;
			map[2][3] = REACHABLE;
			map[3][2] = REACHABLE;
			map[4][5] = REACHABLE;
			map[5][4] = REACHABLE;
			map[3][5] = REACHABLE;
			map[5][3] = REACHABLE;
			map[3][6] = REACHABLE;
			map[6][3] = REACHABLE;
			map[5][7] = REACHABLE;
			map[7][5] = REACHABLE;
			map[6][7] = REACHABLE;
			map[7][6] = REACHABLE;
			map[7][8] = REACHABLE;
			map[8][7] = REACHABLE;
			map[8][9] = REACHABLE;
			map[9][8] = REACHABLE;
			map[6][9] = REACHABLE;
			map[9][6] = REACHABLE;
			map[2][4] = REACHABLE;
			map[4][2] = REACHABLE; 
		// 要连接的两个点
		start=s;
		end=e;
		// 查找点 start 到点 end 的所有路径
		pathsNum = 0;
		AllPaths(map,n,start,end,NodeUsed,paths,&pathsNum); 
		// 打印点 start 到点 end 的所有路径
		for(i=0;i<pathsNum;i++)
		{
			for(j=paths[i].size;j>1;j--)
			{
				teradpath(paths[i].nodes[j],paths[i].nodes[j-1]);
			}
			teradpath(paths[i].nodes[j],paths[i].nodes[j-1]);
		}
	
}


//输出任意两节点最短路径以及存储各节点信息
void f1()
{
	int l=0;//计时器
	int pat[2];//确定路线代号
	wchar_t SEN1[10],SEN2[10];
	char control;
	int i=0;//计时器
	int mx=0,my=0;//零时存放鼠标位置
	int tx,ty;//存放鼠标相对位置的值
	MOUSEMSG m;
	map2.x=-756;
	map2.y=-542;
	muse.sign=1;
	patsign=0;
	m=GetMouseMsg();
	BeginBatchDraw();
	while(true)
	{
		mx=m.x;
		my=m.y;
		m=GetMouseMsg();
		push(m,mx,my);
		for(int j=0;j<26;j++)
		{
			path[j]=push1(path[j],m,mx,my);
		}
		push2(m,mx,my);
		putimage(map2.x,map2.y,&map2.P);
		//鼠标移至景点时输出介绍
		settextstyle(25,0,_T("微软雅黑"));
		setbkmode(TRANSPARENT);
		if((m.x-sence_pit[0].x)*(m.x-sence_pit[0].x)+(m.y-sence_pit[0].y)*(m.y-sence_pit[0].y)<=1000)
		{
			if(m.mkLButton)
			{
				if(patsign==0)
				{
					pat[patsign]=0;
					patsign++;
				}
				else
				{
					if(pat[0]!=0)
					{
						pat[1]=0;
						patsign++;
					}
				}
				
			}
			guideboard(sence_pit[0].x-125,sence_pit[0].y-241);
			settextcolor(HSLtoRGB(rand()%360,1,0.5));
			outtextxy(sence_pit[0].x-120,sence_pit[1].y-203,_T("窦大夫祠："));
			outtextxy(sence_pit[0].x-120,sence_pit[1].y-170,_T("窦大夫祠又称英济祠、烈石神"));
			outtextxy(sence_pit[0].x-100,sence_pit[1].y-140,_T("祠，是祀奉春秋时晋国大"));
			outtextxy(sence_pit[0].x-100,sence_pit[1].y-110,_T("夫窦犨的祠庙。"));
		}
		else if((m.x-sence_pit[1].x)*(m.x-sence_pit[1].x)+(m.y-sence_pit[1].y)*(m.y-sence_pit[1].y)<=1000)
		{
			if(m.mkLButton)
			{
				if(patsign==0)
				{
					pat[patsign]=1;
					patsign++;
				}
				else
				{
					if(pat[0]!=1)
					{
						pat[patsign]=1;
						patsign++;
					}
				}
			}
			guideboard(sence_pit[1].x-125,sence_pit[1].y-241);
			settextcolor(HSLtoRGB(rand()%360,1,0.5));
			outtextxy(sence_pit[1].x-120,sence_pit[1].y-203,_T("校史馆："));
			outtextxy(sence_pit[1].x-120,sence_pit[1].y-170,_T("这里存放着中北大学建校近八"));
			outtextxy(sence_pit[1].x-100,sence_pit[1].y-140,_T("十年的历史。"));
		}
		else if((m.x-sence_pit[2].x)*(m.x-sence_pit[2].x)+(m.y-sence_pit[2].y)*(m.y-sence_pit[2].y)<=1000)
		{
			if(m.mkLButton)
			{
				if(patsign==0)
				{
					pat[patsign]=2;
					patsign++;
				}
				else
				{
					if(pat[0]!=2)
					{
						pat[1]=2;
						patsign++;
					}
				}
			}
			guideboard(sence_pit[2].x-125,sence_pit[2].y-241);
			settextcolor(HSLtoRGB(rand()%360,1,0.5));
			outtextxy(sence_pit[2].x-120,sence_pit[2].y-203,_T("柏林园:"));
			outtextxy(sence_pit[2].x-120,sence_pit[2].y-170,_T("这里绿树成荫，景色宜人，是"));
			outtextxy(sence_pit[2].x-100,sence_pit[2].y-140,_T("约会的好地方。"));
		}
		else if((m.x-sence_pit[3].x)*(m.x-sence_pit[3].x)+(m.y-sence_pit[3].y)*(m.y-sence_pit[3].y)<=1000)
		{
			if(m.mkLButton)
			{
				if(patsign==0)
				{
					pat[patsign]=3;
					patsign++;
				}
				else
				{
					if(pat[0]!=3)
					{
						pat[1]=3;
						patsign++;
					}
				}
			}
			guideboard(sence_pit[3].x-125,sence_pit[3].y-241);
			settextcolor(HSLtoRGB(rand()%360,1,0.5));
			outtextxy(sence_pit[3].x-120,sence_pit[3].y-203,_T("铁路公园："));
			outtextxy(sence_pit[3].x-120,sence_pit[3].y-170,_T("在全国的大学中，也仅仅只有"));
			outtextxy(sence_pit[3].x-100,sence_pit[3].y-140,_T("它一个。"));
		}
		else if((m.x-sence_pit[4].x)*(m.x-sence_pit[4].x)+(m.y-sence_pit[4].y)*(m.y-sence_pit[4].y)<=1000)
		{
				if(m.mkLButton)
			{
				if(patsign==0)
				{
					pat[patsign]=4;
					patsign++;
				}
				else
				{
					if(pat[0]!=4)
					{
						pat[1]=4;
						patsign++;
					}
				}
			}
			guideboard(sence_pit[4].x-125,sence_pit[4].y-241);
			settextcolor(HSLtoRGB(rand()%360,1,0.5));
			outtextxy(sence_pit[4].x-120,sence_pit[4].y-203,_T("二龙山："));
			outtextxy(sence_pit[4].x-120,sence_pit[4].y-170,_T("山上风景秀丽，能够登高远眺。"));
			outtextxy(sence_pit[4].x-100,sence_pit[4].y-140,_T("，俯瞰整个中北"));
		}
		else if((m.x-sence_pit[5].x)*(m.x-sence_pit[5].x)+(m.y-sence_pit[5].y)*(m.y-sence_pit[5].y)<=1000)
		{
			if(m.mkLButton)
			{
				if(patsign==0)
				{
					pat[0]=5;
					patsign++;
				}
				else
				{
					if(pat[0]!=5)
					{
						pat[patsign]=5;
						patsign++;
					}
				}
			}
			guideboard(sence_pit[5].x-125,sence_pit[5].y-241);
			settextcolor(HSLtoRGB(rand()%360,1,0.5));
			outtextxy(sence_pit[5].x-120,sence_pit[5].y-203,_T("第四食堂："));
			outtextxy(sence_pit[5].x-120,sence_pit[5].y-170,_T("这里有中北最可口的饭菜"));
		}
		else if((m.x-sence_pit[6].x)*(m.x-sence_pit[6].x)+(m.y-sence_pit[6].y)*(m.y-sence_pit[6].y)<=1000)
		{
				if(m.mkLButton)
			{
				if(patsign==0)
				{
					pat[0]=6;
					patsign++;
				}
				else
				{
					if(pat[0]!=6)
					{
						pat[patsign]=6;
						patsign++;
					}
				}
			}
			guideboard(sence_pit[6].x-125,sence_pit[6].y-241);
			settextcolor(HSLtoRGB(rand()%360,1,0.5));
			outtextxy(sence_pit[6].x-120,sence_pit[6].y-203,_T("行知广场："));
			outtextxy(sence_pit[6].x-120,sence_pit[6].y-170,_T("每天早上都有升旗仪式嗷。"));
		}
		else if((m.x-sence_pit[7].x)*(m.x-sence_pit[7].x)+(m.y-sence_pit[7].y)*(m.y-sence_pit[7].y)<=1000)
		{
				if(m.mkLButton)
			{
				if(patsign==0)
				{
					pat[patsign]=7;
					patsign++;
				}
				else
				{
					if(pat[0]!=7)
					{
						pat[1]=7;
						patsign++;
					}
				}
			}
			guideboard(sence_pit[7].x-125,sence_pit[7].y-241);
			settextcolor(HSLtoRGB(rand()%360,1,0.5));
			outtextxy(sence_pit[7].x-120,sence_pit[7].y-203,_T("图书馆："));
			outtextxy(sence_pit[7].x-120,sence_pit[7].y-170,_T("这里珍藏了中北具有巨大价值的书籍。"));
		}
		else if((m.x-sence_pit[8].x)*(m.x-sence_pit[8].x)+(m.y-sence_pit[8].y)*(m.y-sence_pit[8].y)<=1000)
		{
			if(m.mkLButton)
			{
				if(patsign==0)
				{
					pat[patsign]=8;
					patsign++;
				}
				else
				{
					if(pat[0]!=8)
					{
						pat[1]=8;
						patsign++;
					}
				}
			}
			guideboard(sence_pit[8].x-125,sence_pit[8].y-241);
			settextcolor(HSLtoRGB(rand()%360,1,0.5));
			outtextxy(sence_pit[8].x-120,sence_pit[8].y-203,_T("游泳馆："));
			outtextxy(sence_pit[8].x-120,sence_pit[8].y-170,_T("这里可以游泳。"));
		}
		else if((m.x-sence_pit[9].x)*(m.x-sence_pit[9].x)+(m.y-sence_pit[9].y)*(m.y-sence_pit[9].y)<=10000)
		{
			if(m.mkLButton)
			{
				if(patsign==0)
				{
					pat[patsign]=9;
					patsign++;
				}
				else
				{
					if(pat[0]!=9)
					{
						pat[1]=9;
						patsign++;
					}
				}
			}
			guideboard(sence_pit[9].x-125,sence_pit[9].y-241);
			settextcolor(HSLtoRGB(rand()%360,1,0.5));
			outtextxy(sence_pit[9].x-120,sence_pit[9].y-203,_T("龙山餐厅："));
			outtextxy(sence_pit[9].x-120,sence_pit[9].y-170,_T("龙山餐厅时中北最大最豪华的"));
			outtextxy(sence_pit[9].x-100,sence_pit[9].y-140,_T("餐厅。"));
		}
		if(patsign==2)
		{
			print_AllPaths(pat[0],pat[1]);
			patsign=0;
			pat[0]=-1;
			pat[1]=-1;
		}
		for(int r=0;r<10;r++)
			point(sence_pit[r]);
		child(m,mx,my);
		FlushMouseMsgBuffer();
		
		FlushBatchDraw();
		Sleep(100);
	}
	EndBatchDraw();
}



//提供校园图中多个景点的最佳访问路线查询，即求途经这多个景点的最佳路径。
void CreateMGraph(MGraph *G)
{
    int i, j;
    /* printf("请输入边数和顶点数:"); */
    G->numEdges=13;
    G->numVertexes=10;

    for (i = 0; i < G->numVertexes; i++)/* 初始化图 */
    {
        G->vexs[i]=i;
    }

    for (i = 0; i < G->numVertexes; i++)/* 初始化图 */
    {
        for ( j = 0; j < G->numVertexes; j++)
        {
            if (i==j)
                G->arc[i][j]=0;
            else
                G->arc[i][j] = G->arc[j][i] = INFINITY;
        }
    }
    G->arc[0][1]=561;
    G->arc[1][2]=343; 
    G->arc[1][3]=466; 
    G->arc[2][4]=314; 
    G->arc[2][3]=457; 
    G->arc[5][3]=347; 
    G->arc[4][5]=262; 
    G->arc[5][7]=333; 
    G->arc[3][6]=476; 
    G->arc[6][7]=241;
    G->arc[7][8]=414;
    G->arc[8][9]=706; 
    G->arc[6][9]=948; 
    for(i = 0; i < G->numVertexes; i++)
    {
        for(j = i; j < G->numVertexes; j++)
        {
            G->arc[j][i] =G->arc[i][j];
        }
    }

}
/* Floyd算法，求网图G中各顶点v到其余顶点w的最短路径P[v][w]及带权长度D[v][w]。 */ 
void ShortestPath_Floyd(MGraph G, Patharc *P, ShortPathTable *D)
{ 
    int v,w,k; 
    for(v=0; v<G.numVertexes; v++) /* 初始化D与P */ 
    { 
        for(w=0; w<G.numVertexes; w++) 
        {
            (*D)[v][w]=G.arc[v][w];    /* D[v][w]值即为对应点间的权值 */
            (*P)[v][w]=w;   
					             /* 初始化P */
        }
    }
    for(k=0; k<G.numVertexes; k++) 
    {
        for(v=0; v<G.numVertexes; v++) 
        { 
            for(w=0; w<G.numVertexes; w++) 
            {
                if ((*D)[v][w]>(*D)[v][k]+(*D)[k][w] )
                {/* 如果经过下标为k顶点路径比原两点间路径更短 */
                    (*D)[v][w]=(*D)[v][k]+(*D)[k][w];/* 将当前两点间权值设为更小的一个 */
                    (*P)[v][w]=(*P)[v][k];/* 路径设置为经过下标为k的顶点 */
            	}
            }
        }
    }
}
int print_floyd(int a,int b,int c,int t)
{
	int v,w,k; 
    MGraph G; 
    Patharc P; 
    ShortPathTable D; /* 求某点到其余各点的最短路径 */ 
	
    CreateMGraph(&G);
    ShortestPath_Floyd(G,&P,&D);  
    v = a;
    w = b;
//           printf("v%d-v%d  ",v,w);
            k=P[v][w];
			if(c==1)                /* 获得第一个路径顶点下标 */
            	pah[0]=v; 
								/* 打印源点 */
            while(k!=w)                /* 如果路径顶点下标不是终点 */
            {
                pah[t]=k;    /* 打印路径顶点 */
                k=P[k][w];	/* 获得下一个路径顶点下标 */
				
				t++;
            }
            pah[t]=w;    /* 打印终点 */
			t++;
			return t;
}
void bestpath(int i)
{	
    int v,w,k; 
    int flag = 1;
    MGraph G; 
    Patharc P; 
	int t=1;
    ShortPathTable D; /* 求某点到其余各点的最短路径 */  
	for(int i=0;i<13;i++)
	{
		pah[i]=-1;
	}
	for(v=1;v<i;v++)
	{
		t=print_floyd(c[v-1],c[v],flag,t);
		flag = 0;
	}
}
//功能2
void f2()
{
	int mx=0,my=0;//零时存放鼠标位置
	wchar_t ss[22];
	int a,b;
	InputBox(ss,20,_T("请输入您要参观的景点数量"));
	a=_wtoi(ss);

	for(int i=0;i<a;i++)
	{
		InputBox(ss,20,_T("单个景点的代号"),_T("请输入您要参观的景点代号"));
		c[i]=_wtoi(ss);
	}
	bestpath(a);//多点有序找最优路 
	MOUSEMSG m;
	map2.x=-756;
	map2.y=-542;
	muse.sign=1;
	patsign=0;
	m=GetMouseMsg();
	while(true)
	{
		BeginBatchDraw();
		mx=m.x;
		my=m.y;
		m=GetMouseMsg();
		putimage(map2.x,map2.y,&map2.P);
		push(m,mx,my);
		for(int j=0;j<26;j++)
		{
			path[j]=push1(path[j],m,mx,my);
		}
		push2(m,mx,my);
				settextstyle(25,0,_T("微软雅黑"));
		setbkmode(TRANSPARENT);
		//只是输出介绍
		if((m.x-sence_pit[0].x)*(m.x-sence_pit[0].x)+(m.y-sence_pit[0].y)*(m.y-sence_pit[0].y)<=1000)
		{
			
			guideboard(sence_pit[0].x-125,sence_pit[0].y-241);
			settextcolor(HSLtoRGB(rand()%360,1,0.5));
			outtextxy(sence_pit[0].x-120,sence_pit[1].y-203,_T("窦大夫祠："));
			outtextxy(sence_pit[0].x-120,sence_pit[1].y-170,_T("窦大夫祠又称英济祠、烈石神"));
			outtextxy(sence_pit[0].x-100,sence_pit[1].y-140,_T("祠，是祀奉春秋时晋国大"));
			outtextxy(sence_pit[0].x-100,sence_pit[1].y-110,_T("夫窦犨的祠庙。"));
		}
		else if((m.x-sence_pit[1].x)*(m.x-sence_pit[1].x)+(m.y-sence_pit[1].y)*(m.y-sence_pit[1].y)<=1000)
		{
			
			guideboard(sence_pit[1].x-125,sence_pit[1].y-241);
			settextcolor(HSLtoRGB(rand()%360,1,0.5));
			outtextxy(sence_pit[1].x-120,sence_pit[1].y-203,_T("校史馆："));
			outtextxy(sence_pit[1].x-120,sence_pit[1].y-170,_T("这里存放着中北大学建校近八"));
			outtextxy(sence_pit[1].x-100,sence_pit[1].y-140,_T("十年的历史。"));
		}
		else if((m.x-sence_pit[2].x)*(m.x-sence_pit[2].x)+(m.y-sence_pit[2].y)*(m.y-sence_pit[2].y)<=1000)
		{
			
			guideboard(sence_pit[2].x-125,sence_pit[2].y-241);
			settextcolor(HSLtoRGB(rand()%360,1,0.5));
			outtextxy(sence_pit[2].x-120,sence_pit[2].y-203,_T("柏林园:"));
			outtextxy(sence_pit[2].x-120,sence_pit[2].y-170,_T("这里绿树成荫，景色宜人，是"));
			outtextxy(sence_pit[2].x-100,sence_pit[2].y-140,_T("约会的好地方。"));
		}
		else if((m.x-sence_pit[3].x)*(m.x-sence_pit[3].x)+(m.y-sence_pit[3].y)*(m.y-sence_pit[3].y)<=1000)
		{
			
			guideboard(sence_pit[3].x-125,sence_pit[3].y-241);
			settextcolor(HSLtoRGB(rand()%360,1,0.5));
			outtextxy(sence_pit[3].x-120,sence_pit[3].y-203,_T("铁路公园："));
			outtextxy(sence_pit[3].x-120,sence_pit[3].y-170,_T("在全国的大学中，也仅仅只有"));
			outtextxy(sence_pit[3].x-100,sence_pit[3].y-140,_T("它一个。"));
		}
		else if((m.x-sence_pit[4].x)*(m.x-sence_pit[4].x)+(m.y-sence_pit[4].y)*(m.y-sence_pit[4].y)<=1000)
		{
			
			guideboard(sence_pit[4].x-125,sence_pit[4].y-241);
			settextcolor(HSLtoRGB(rand()%360,1,0.5));
			outtextxy(sence_pit[4].x-120,sence_pit[4].y-203,_T("二龙山："));
			outtextxy(sence_pit[4].x-120,sence_pit[4].y-170,_T("山上风景秀丽，能够登高远眺。"));
			outtextxy(sence_pit[4].x-100,sence_pit[4].y-140,_T("，俯瞰整个中北"));
		}
		else if((m.x-sence_pit[5].x)*(m.x-sence_pit[5].x)+(m.y-sence_pit[5].y)*(m.y-sence_pit[5].y)<=1000)
		{
			
			guideboard(sence_pit[5].x-125,sence_pit[5].y-241);
			settextcolor(HSLtoRGB(rand()%360,1,0.5));
			outtextxy(sence_pit[5].x-120,sence_pit[5].y-203,_T("第四食堂："));
			outtextxy(sence_pit[5].x-120,sence_pit[5].y-170,_T("这里有中北最可口的饭菜"));
		}
		else if((m.x-sence_pit[6].x)*(m.x-sence_pit[6].x)+(m.y-sence_pit[6].y)*(m.y-sence_pit[6].y)<=1000)
		{
			
			guideboard(sence_pit[6].x-125,sence_pit[6].y-241);
			settextcolor(HSLtoRGB(rand()%360,1,0.5));
			outtextxy(sence_pit[6].x-120,sence_pit[6].y-203,_T("行知广场："));
			outtextxy(sence_pit[6].x-120,sence_pit[6].y-170,_T("每天早上都有升旗仪式嗷。"));
		}
		else if((m.x-sence_pit[7].x)*(m.x-sence_pit[7].x)+(m.y-sence_pit[7].y)*(m.y-sence_pit[7].y)<=1000)
		{
				
			guideboard(sence_pit[7].x-125,sence_pit[7].y-241);
			settextcolor(HSLtoRGB(rand()%360,1,0.5));
			outtextxy(sence_pit[7].x-120,sence_pit[7].y-203,_T("图书馆："));
			outtextxy(sence_pit[7].x-120,sence_pit[7].y-170,_T("这里珍藏了中北具有巨大价值的书籍。"));
		}
		else if((m.x-sence_pit[8].x)*(m.x-sence_pit[8].x)+(m.y-sence_pit[8].y)*(m.y-sence_pit[8].y)<=1000)
		{
			
			guideboard(sence_pit[8].x-125,sence_pit[8].y-241);
			settextcolor(HSLtoRGB(rand()%360,1,0.5));
			outtextxy(sence_pit[8].x-120,sence_pit[8].y-203,_T("游泳馆："));
			outtextxy(sence_pit[8].x-120,sence_pit[8].y-170,_T("这里可以游泳。"));
		}
		else if((m.x-sence_pit[9].x)*(m.x-sence_pit[9].x)+(m.y-sence_pit[9].y)*(m.y-sence_pit[9].y)<=10000)
		{
			
			guideboard(sence_pit[9].x-125,sence_pit[9].y-241);
			settextcolor(HSLtoRGB(rand()%360,1,0.5));
			outtextxy(sence_pit[9].x-120,sence_pit[9].y-203,_T("龙山餐厅："));
			outtextxy(sence_pit[9].x-120,sence_pit[9].y-170,_T("龙山餐厅时中北最大最豪华的"));
			outtextxy(sence_pit[9].x-100,sence_pit[9].y-140,_T("餐厅。"));
		}
		for(int j=0;j<9;j++)
				teradpath(pah[j],pah[j+1]);
		for(int r=0;r<10;r++)
			point(sence_pit[r]);
		child(m,mx,my);
		FlushMouseMsgBuffer();
		EndBatchDraw();
		Sleep(20);
	}
}


//求关节点
void dfs(MGraph *G,int numVertexes,int count,int j)
{
	
	int i,k;
	G->visited[numVertexes] = 1;//该点被访问 
//	printf("num%d ",numVertexes);
	count = m;
	count++;          //计数 
//	printf("count %d\n",count);
	for(i = 0;i<G->numVertexes;i++)//去掉相对应的边 
	{
			G->arc[i][j] = 0;
			G->arc[j][i] = 0;
	}
	for(i = 0;i<G->numVertexes;i++)
	{
		if( G->visited[i]==0 && G->arc[numVertexes][i]!=INFINITY)  //未曾遍历且有边可遍历 
		{
			dfs(G,i,count,j);//递归 
//			if(j!=0)
//				count++;
		}
		if(m<count)//将递归最深的count取出 
		m = count;
	}
//		printf("qweqwww%d\n",count);
}
void sencejuge(int j)
{
	if(j==0)
	{
		outtextxy(62,170,_T("关节点是："));
		outtextxy(80,200,_T("窦大夫祠"));
	}
	else if(j==1)
	{
		outtextxy(62,170,_T("关节点是："));
		outtextxy(80,200,_T("校史馆"));
	}
	else if(j==2)
	{
		outtextxy(62,170,_T("关节点是："));
		outtextxy(80,200,_T("柏林园"));
	}
	else if(j==3)
	{
		outtextxy(62,170,_T("关节点是："));
		outtextxy(80,200,_T("铁路主题公园"));
	}
	else if(j==4)
	{
		outtextxy(62,170,_T("关节点是："));
		outtextxy(80,200,_T("二龙山"));
	}
	else if(j==5)
	{
		outtextxy(62,170,_T("关节点是："));
		outtextxy(80,200,_T("第四食堂"));
	}
	else if(j==6)
	{
		outtextxy(62,170,_T("关节点是："));
		outtextxy(80,200,_T("行知广场"));
	}
	else if(j==7)
	{
		outtextxy(62,170,_T("关节点是："));
		outtextxy(80,200,_T("图书馆"));
	}
	else if(j==8)
	{
		outtextxy(62,170,_T("关节点是："));
		outtextxy(80,200,_T("游泳馆"));
	}
	else if(j==9)
	{
		outtextxy(62,170,_T("关节点是："));
		outtextxy(80,200,_T("龙山餐厅"));
	}

}
void cutpoint(MGraph *G)
{
	int j,i;
	int count;
	for(j = 0;j<10;j++)//循环遍历，如果有割点，则不能到达部分点，导致count小于总点数减一 
	{
		count = 0;
		CreateMGraph(G);
		G->visited[j] = 1;//将该点除去
		i = 0; 
		if(j==i)
		{
			i = 1;
		}
		dfs(G,i,count,j);
//		printf("test%d\n",m);
//		printf("###############\n");
		if(m<9)
		{
			settextstyle(30,0,_T("微软雅黑"));
			setbkmode(TRANSPARENT);
			settextcolor(BLACK);
			sencejuge(j);
			Sleep(1000);
			break;
		}
		m = 0;//重置 
	
	}
		
}

void f3()
{
	MGraph G;
	cutpoint(&G);
}
int main()
{
	
	initgraph(1024,709);
	loadimage(&f,_T("界面.jpg"));
	loadimage(&guide,_T("路牌.jpg"));
	loadimage(&guide1,_T("路牌罩图.jpg"));
	loadimage(&map2.P,_T("地图2.jpg"));
	sence();
	loadpath();
	loadter();
	
	//f1();
	while(1)
	{
		putimage(0,0,&f);
		char a=getch();
		fflush(stdin);
		switch(a)
		{
			case '1':{f1();break;}
			case '2':{f2();break;}
			case '3':{f3();break;}
		}
	}//初始界面
	return 0;
}