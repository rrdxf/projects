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
typedef int Status;    /* Status�Ǻ���������*/

typedef struct
{
    int vexs[MAXVEX];//������ 
    int arc[MAXVEX][MAXVEX];//�ڱ߾��� 
    int numVertexes, numEdges;//���������� 
    int visited[MAXVEX];//���ʱ�־ 
}MGraph;
struct Path
{
	int size;
	int nodes[MAXVEX];
};

typedef int Patharc[MAXVEX][MAXVEX];
typedef int ShortPathTable[MAXVEX][MAXVEX];
//��ͼ�ṹ��
typedef struct pecture
{
	IMAGE P;
	int x;
	int y;
}MAP;
//�洢·������
typedef struct path
{
	int x;
	int y;
	struct path *next;
}PATH;
//�洢��������������Ϣ
typedef struct sen
{
	wchar_t name[20];
	wchar_t intro[50];
	int x;
	int y;
}SENCE;
//���ָ��ṹ��
typedef struct mouse
{
	IMAGE P;
	IMAGE P1;
	int sign;
}MUSE;
//�洢ÿ��·���˵�ṹ��
typedef struct terminal
{
	int sen1;//·�����
	int sen2;//·���յ�
}TERMINAl;
int c[MAXVEX];//������Ŷ�����������·��Ҫ��
TERMINAl sen[26];
MAP map1,map2;
MUSE muse;
IMAGE f;//��ʼ����
IMAGE guide,guide1;//·��ͼƬ
int patsign=0;//·�߶˵��������	
SENCE sence_pit[10];
int pah[13];//�洢·��������
PATH *path[26];//�洢·�ߵ�����ͷָ�뺯��
int m;//��ؽڵ��ȫ�ֱ���
int txx(MOUSEMSG p,int mx);
int tyy(MOUSEMSG p,int my);
void point(SENCE point);
void drawpath(PATH *path);
void guideboard(int x,int y)
{
	
	putimage(x,y,&guide1,NOTSRCERASE);
	putimage(x,y,&guide,SRCINVERT);
}
//�洢ÿ��·���Ķ˵㺯��
void loadter()
{
	//�->Уʷ��
	sen[0].sen1=0;
	sen[0].sen2=1;
	//Уʷ��->�
	sen[1].sen1=1;
	sen[1].sen2=0;
	//Уʷ��->����
	sen[2].sen1=1;
	sen[2].sen2=2;
	//����->Уʷ��
	sen[3].sen1=2;
	sen[3].sen2=1;
	//Уʷ��->��·
	sen[4].sen1=1;
	sen[4].sen2=3;
	//��·->Уʷ��
	sen[5].sen1=3;
	sen[5].sen2=1;
	//����->����
	sen[6].sen1=2;
	sen[6].sen2=4;
	//����->����
	sen[7].sen1=4;
	sen[7].sen2=2;
	//����->��ʳ��
	sen[8].sen1=4;
	sen[8].sen2=5;
	//��ʳ��->����
	sen[9].sen1=5;
	sen[9].sen2=4;
	//��ʳ��->��·
	sen[10].sen1=5;
	sen[10].sen2=3;
	//��·->��ʳ��
	sen[11].sen1=3;
	sen[11].sen2=5;
	//��·->��֪�㳡
	sen[12].sen1=3;
	sen[12].sen2=6;
	//��֪�㳡->��·
	sen[13].sen1=6;
	sen[13].sen2=3;
	//��ʳ��->ͼ��
	sen[14].sen1=5;
	sen[14].sen2=7;
	//ͼ��->��ʳ��
	sen[15].sen1=7;
	sen[15].sen2=5;
	//ͼ��->��֪
	sen[16].sen1=7;
	sen[16].sen2=6;
	//��֪->ͼ��
	sen[17].sen1=6;
	sen[17].sen2=7;
	//��ɽ->��֪
	sen[18].sen1=9;
	sen[18].sen2=6;
	//��֪->��ɽ
	sen[19].sen1=6;
	sen[19].sen2=9;
	//��Ӿ->ͼ��
	sen[20].sen1=8;
	sen[20].sen2=7;
	//ͼ��->��Ӿ
	sen[21].sen1=7;
	sen[21].sen2=8;
	//��Ӿ->��ɽ
	sen[22].sen1=8;
	sen[22].sen2=9;
	//��ɽ->��Ӿ
	sen[23].sen1=9;
	sen[23].sen2=8;
	//��·->����
	sen[24].sen1=3;
	sen[24].sen2=2;
	//����->��·
	sen[25].sen1=2;
	sen[25].sen2=3;
}
//�˵�ƥ��·��֮�����
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
//����·��������
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
//����·���ڵ�ͼ�ϵ�����
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
//������ק��ͼ����������
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
//�ڵ�ͼ�ϻ�����Ӧ����·
void drawpath(PATH *path)
{
	PATH *p;
	p=path;
	setbkmode(TRANSPARENT);//���ñ���Ϊ͸����
	setlinestyle(PS_SOLID | PS_JOIN_ROUND, 3);//ʵ�߽��ߴ�Բ��������Ϊ��
	while(p->next)
	{
		setlinecolor(HSLtoRGB(rand()%360,1,0.5));
		line(p->x, p->y, p->next->x, p->next->y);
		p=p->next;
	}
}
//�洢�����������Ϣ
void sence()
{
	//���
	sence_pit[0].x=301;
	sence_pit[0].y=1177;
	//Уʷ��
	sence_pit[1].x=489;
	sence_pit[1].y=1179;
	//����԰
	sence_pit[2].x=517;
	sence_pit[2].y=917;
	//��·��԰
	sence_pit[3].x=990;
	sence_pit[3].y=907;
	//����ɽ
	sence_pit[4].x=497;
	sence_pit[4].y=600;
	//��ʳ��
	sence_pit[5].x=839;
	sence_pit[5].y=622;
	//��֪�㳡
	sence_pit[6].x=1425;
	sence_pit[6].y=777;
	//ͼ���
	sence_pit[7].x=1234;
	sence_pit[7].y=536;
	//��Ӿ��
	sence_pit[8].x=1269;
	sence_pit[8].y=309;
	//��ɽ����
	sence_pit[9].x=1984;
	sence_pit[9].y=268;
}
//�ڵ�ͼ�����������λ��
void point(SENCE point)
{
	setfillstyle(BS_SOLID);
	setfillcolor(HSLtoRGB(rand()%360,1,0.5));
	solidcircle(point.x,point.y,5);//��Բ
}
//����������λ�õ�xֵ
int txx(MOUSEMSG p,int mx)
{
	int tx;
	tx=mx-p.x;
	return tx;
}
int tyy(MOUSEMSG p,int my)	//����������λ�õ�yֵ
{
	int ty;
	ty=my-p.y;
	return ty;
}

//ʵ�ֵ�ͼ����ק����
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

//�ж����������μ�ͷ
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
		loadimage(&muse.P,_T("��.jpg"));
		loadimage(&muse.P1,_T("����ͼ.jpg"));
	}
	else if(muse.sign==-1)
	{
		loadimage(&muse.P,_T("������.jpg"));
		loadimage(&muse.P1,_T("��������ͼ.jpg"));
	}
	putimage(m.x,m.y,&muse.P1,NOTSRCERASE);
	putimage(m.x,m.y,&muse.P,SRCINVERT);
}
//���Բ�������ж�
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
		patsign++;//·�߶˵��������	
		return i;	
	}
}

//������������·��
void AllPaths(int map[MAXVEX][MAXVEX],int n ,int start,int end,int NodeUsed[],struct Path paths[],int * pathsNum)
{
	int i,j;
	struct Path tempPaths[MAX_PATHS_BETWEEN_TWO_NODES_NUM]; 
	int tempPathsNum ;
// ��ǵ�ǰ��㲻���� 
	NodeUsed[start] = TRUE;
	for(i=0;i<n;i++)
	{
	// �ڵ㲻��·���У��ҿ��Ե��� 
		if(NodeUsed[i] == FALSE && map[start][i]== REACHABLE) 
		{
			// ��ǰ�����ֱ�ӵ����յ� 
			if(i == end)
			{
				paths[(*pathsNum)].size = 2;
				paths[(*pathsNum)].nodes[0] = end;
				paths[(*pathsNum)].nodes[1] = start;
				(*pathsNum)++; 
			}
		// ��ǰ����ܲ���ֱ�ӵ����յ㣬���Ե�ǰ�ڵ�ͨ�������ڵ�ﵽ�յ� 
			else
			{
				// �ݹ����ӵ�ǰ��㵽���յ������·�� 
				tempPathsNum = 0;
				AllPaths(map,n,i,end,NodeUsed,tempPaths,&tempPathsNum);
				// �����ҵ��ģ��ӵ�ǰ��㵽���յ������·�� 
				for(j=0;j<tempPathsNum;j++)
				{
				// �ڵ�ǰ��㵽���յ������·���У���ӵ�ǰ��� 
					tempPaths[j].nodes[tempPaths[j].size] = start;
					tempPaths[j].size ++;	
				// �ϲ������յ�·���� 
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
	// ��ȡ������·���� 
	n=10;
	m=13;
	// ��ʼ��ͼ 
		for(i=0;i<n;i++)
		{
			NodeUsed[i] = FALSE;
			for(j=0;j<n;j++)
			{
				map[i][j] = INFINITY;
			} 
		}
			// ��� a b ����·����ע��������ͼ��������� 
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
		// Ҫ���ӵ�������
		start=s;
		end=e;
		// ���ҵ� start ���� end ������·��
		pathsNum = 0;
		AllPaths(map,n,start,end,NodeUsed,paths,&pathsNum); 
		// ��ӡ�� start ���� end ������·��
		for(i=0;i<pathsNum;i++)
		{
			for(j=paths[i].size;j>1;j--)
			{
				teradpath(paths[i].nodes[j],paths[i].nodes[j-1]);
			}
			teradpath(paths[i].nodes[j],paths[i].nodes[j-1]);
		}
	
}


//����������ڵ����·���Լ��洢���ڵ���Ϣ
void f1()
{
	int l=0;//��ʱ��
	int pat[2];//ȷ��·�ߴ���
	wchar_t SEN1[10],SEN2[10];
	char control;
	int i=0;//��ʱ��
	int mx=0,my=0;//��ʱ������λ��
	int tx,ty;//���������λ�õ�ֵ
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
		//�����������ʱ�������
		settextstyle(25,0,_T("΢���ź�"));
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
			outtextxy(sence_pit[0].x-120,sence_pit[1].y-203,_T("�������"));
			outtextxy(sence_pit[0].x-120,sence_pit[1].y-170,_T("������ֳ�Ӣ��������ʯ��"));
			outtextxy(sence_pit[0].x-100,sence_pit[1].y-140,_T("����������ʱ������"));
			outtextxy(sence_pit[0].x-100,sence_pit[1].y-110,_T("���ߵ�����"));
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
			outtextxy(sence_pit[1].x-120,sence_pit[1].y-203,_T("Уʷ�ݣ�"));
			outtextxy(sence_pit[1].x-120,sence_pit[1].y-170,_T("���������б���ѧ��У����"));
			outtextxy(sence_pit[1].x-100,sence_pit[1].y-140,_T("ʮ�����ʷ��"));
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
			outtextxy(sence_pit[2].x-120,sence_pit[2].y-203,_T("����԰:"));
			outtextxy(sence_pit[2].x-120,sence_pit[2].y-170,_T("�����������񣬾�ɫ���ˣ���"));
			outtextxy(sence_pit[2].x-100,sence_pit[2].y-140,_T("Լ��ĺõط���"));
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
			outtextxy(sence_pit[3].x-120,sence_pit[3].y-203,_T("��·��԰��"));
			outtextxy(sence_pit[3].x-120,sence_pit[3].y-170,_T("��ȫ���Ĵ�ѧ�У�Ҳ����ֻ��"));
			outtextxy(sence_pit[3].x-100,sence_pit[3].y-140,_T("��һ����"));
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
			outtextxy(sence_pit[4].x-120,sence_pit[4].y-203,_T("����ɽ��"));
			outtextxy(sence_pit[4].x-120,sence_pit[4].y-170,_T("ɽ�Ϸ羰�������ܹ��Ǹ�Զ����"));
			outtextxy(sence_pit[4].x-100,sence_pit[4].y-140,_T("����������б�"));
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
			outtextxy(sence_pit[5].x-120,sence_pit[5].y-203,_T("����ʳ�ã�"));
			outtextxy(sence_pit[5].x-120,sence_pit[5].y-170,_T("�������б���ɿڵķ���"));
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
			outtextxy(sence_pit[6].x-120,sence_pit[6].y-203,_T("��֪�㳡��"));
			outtextxy(sence_pit[6].x-120,sence_pit[6].y-170,_T("ÿ�����϶���������ʽ໡�"));
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
			outtextxy(sence_pit[7].x-120,sence_pit[7].y-203,_T("ͼ��ݣ�"));
			outtextxy(sence_pit[7].x-120,sence_pit[7].y-170,_T("����������б����о޴��ֵ���鼮��"));
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
			outtextxy(sence_pit[8].x-120,sence_pit[8].y-203,_T("��Ӿ�ݣ�"));
			outtextxy(sence_pit[8].x-120,sence_pit[8].y-170,_T("���������Ӿ��"));
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
			outtextxy(sence_pit[9].x-120,sence_pit[9].y-203,_T("��ɽ������"));
			outtextxy(sence_pit[9].x-120,sence_pit[9].y-170,_T("��ɽ����ʱ�б�����������"));
			outtextxy(sence_pit[9].x-100,sence_pit[9].y-140,_T("������"));
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



//�ṩУ԰ͼ�ж���������ѷ���·�߲�ѯ������;��������������·����
void CreateMGraph(MGraph *G)
{
    int i, j;
    /* printf("����������Ͷ�����:"); */
    G->numEdges=13;
    G->numVertexes=10;

    for (i = 0; i < G->numVertexes; i++)/* ��ʼ��ͼ */
    {
        G->vexs[i]=i;
    }

    for (i = 0; i < G->numVertexes; i++)/* ��ʼ��ͼ */
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
/* Floyd�㷨������ͼG�и�����v�����ඥ��w�����·��P[v][w]����Ȩ����D[v][w]�� */ 
void ShortestPath_Floyd(MGraph G, Patharc *P, ShortPathTable *D)
{ 
    int v,w,k; 
    for(v=0; v<G.numVertexes; v++) /* ��ʼ��D��P */ 
    { 
        for(w=0; w<G.numVertexes; w++) 
        {
            (*D)[v][w]=G.arc[v][w];    /* D[v][w]ֵ��Ϊ��Ӧ����Ȩֵ */
            (*P)[v][w]=w;   
					             /* ��ʼ��P */
        }
    }
    for(k=0; k<G.numVertexes; k++) 
    {
        for(v=0; v<G.numVertexes; v++) 
        { 
            for(w=0; w<G.numVertexes; w++) 
            {
                if ((*D)[v][w]>(*D)[v][k]+(*D)[k][w] )
                {/* ��������±�Ϊk����·����ԭ�����·������ */
                    (*D)[v][w]=(*D)[v][k]+(*D)[k][w];/* ����ǰ�����Ȩֵ��Ϊ��С��һ�� */
                    (*P)[v][w]=(*P)[v][k];/* ·������Ϊ�����±�Ϊk�Ķ��� */
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
    ShortPathTable D; /* ��ĳ�㵽�����������·�� */ 
	
    CreateMGraph(&G);
    ShortestPath_Floyd(G,&P,&D);  
    v = a;
    w = b;
//           printf("v%d-v%d  ",v,w);
            k=P[v][w];
			if(c==1)                /* ��õ�һ��·�������±� */
            	pah[0]=v; 
								/* ��ӡԴ�� */
            while(k!=w)                /* ���·�������±겻���յ� */
            {
                pah[t]=k;    /* ��ӡ·������ */
                k=P[k][w];	/* �����һ��·�������±� */
				
				t++;
            }
            pah[t]=w;    /* ��ӡ�յ� */
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
    ShortPathTable D; /* ��ĳ�㵽�����������·�� */  
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
//����2
void f2()
{
	int mx=0,my=0;//��ʱ������λ��
	wchar_t ss[22];
	int a,b;
	InputBox(ss,20,_T("��������Ҫ�ι۵ľ�������"));
	a=_wtoi(ss);

	for(int i=0;i<a;i++)
	{
		InputBox(ss,20,_T("��������Ĵ���"),_T("��������Ҫ�ι۵ľ������"));
		c[i]=_wtoi(ss);
	}
	bestpath(a);//�������������· 
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
				settextstyle(25,0,_T("΢���ź�"));
		setbkmode(TRANSPARENT);
		//ֻ���������
		if((m.x-sence_pit[0].x)*(m.x-sence_pit[0].x)+(m.y-sence_pit[0].y)*(m.y-sence_pit[0].y)<=1000)
		{
			
			guideboard(sence_pit[0].x-125,sence_pit[0].y-241);
			settextcolor(HSLtoRGB(rand()%360,1,0.5));
			outtextxy(sence_pit[0].x-120,sence_pit[1].y-203,_T("�������"));
			outtextxy(sence_pit[0].x-120,sence_pit[1].y-170,_T("������ֳ�Ӣ��������ʯ��"));
			outtextxy(sence_pit[0].x-100,sence_pit[1].y-140,_T("����������ʱ������"));
			outtextxy(sence_pit[0].x-100,sence_pit[1].y-110,_T("���ߵ�����"));
		}
		else if((m.x-sence_pit[1].x)*(m.x-sence_pit[1].x)+(m.y-sence_pit[1].y)*(m.y-sence_pit[1].y)<=1000)
		{
			
			guideboard(sence_pit[1].x-125,sence_pit[1].y-241);
			settextcolor(HSLtoRGB(rand()%360,1,0.5));
			outtextxy(sence_pit[1].x-120,sence_pit[1].y-203,_T("Уʷ�ݣ�"));
			outtextxy(sence_pit[1].x-120,sence_pit[1].y-170,_T("���������б���ѧ��У����"));
			outtextxy(sence_pit[1].x-100,sence_pit[1].y-140,_T("ʮ�����ʷ��"));
		}
		else if((m.x-sence_pit[2].x)*(m.x-sence_pit[2].x)+(m.y-sence_pit[2].y)*(m.y-sence_pit[2].y)<=1000)
		{
			
			guideboard(sence_pit[2].x-125,sence_pit[2].y-241);
			settextcolor(HSLtoRGB(rand()%360,1,0.5));
			outtextxy(sence_pit[2].x-120,sence_pit[2].y-203,_T("����԰:"));
			outtextxy(sence_pit[2].x-120,sence_pit[2].y-170,_T("�����������񣬾�ɫ���ˣ���"));
			outtextxy(sence_pit[2].x-100,sence_pit[2].y-140,_T("Լ��ĺõط���"));
		}
		else if((m.x-sence_pit[3].x)*(m.x-sence_pit[3].x)+(m.y-sence_pit[3].y)*(m.y-sence_pit[3].y)<=1000)
		{
			
			guideboard(sence_pit[3].x-125,sence_pit[3].y-241);
			settextcolor(HSLtoRGB(rand()%360,1,0.5));
			outtextxy(sence_pit[3].x-120,sence_pit[3].y-203,_T("��·��԰��"));
			outtextxy(sence_pit[3].x-120,sence_pit[3].y-170,_T("��ȫ���Ĵ�ѧ�У�Ҳ����ֻ��"));
			outtextxy(sence_pit[3].x-100,sence_pit[3].y-140,_T("��һ����"));
		}
		else if((m.x-sence_pit[4].x)*(m.x-sence_pit[4].x)+(m.y-sence_pit[4].y)*(m.y-sence_pit[4].y)<=1000)
		{
			
			guideboard(sence_pit[4].x-125,sence_pit[4].y-241);
			settextcolor(HSLtoRGB(rand()%360,1,0.5));
			outtextxy(sence_pit[4].x-120,sence_pit[4].y-203,_T("����ɽ��"));
			outtextxy(sence_pit[4].x-120,sence_pit[4].y-170,_T("ɽ�Ϸ羰�������ܹ��Ǹ�Զ����"));
			outtextxy(sence_pit[4].x-100,sence_pit[4].y-140,_T("����������б�"));
		}
		else if((m.x-sence_pit[5].x)*(m.x-sence_pit[5].x)+(m.y-sence_pit[5].y)*(m.y-sence_pit[5].y)<=1000)
		{
			
			guideboard(sence_pit[5].x-125,sence_pit[5].y-241);
			settextcolor(HSLtoRGB(rand()%360,1,0.5));
			outtextxy(sence_pit[5].x-120,sence_pit[5].y-203,_T("����ʳ�ã�"));
			outtextxy(sence_pit[5].x-120,sence_pit[5].y-170,_T("�������б���ɿڵķ���"));
		}
		else if((m.x-sence_pit[6].x)*(m.x-sence_pit[6].x)+(m.y-sence_pit[6].y)*(m.y-sence_pit[6].y)<=1000)
		{
			
			guideboard(sence_pit[6].x-125,sence_pit[6].y-241);
			settextcolor(HSLtoRGB(rand()%360,1,0.5));
			outtextxy(sence_pit[6].x-120,sence_pit[6].y-203,_T("��֪�㳡��"));
			outtextxy(sence_pit[6].x-120,sence_pit[6].y-170,_T("ÿ�����϶���������ʽ໡�"));
		}
		else if((m.x-sence_pit[7].x)*(m.x-sence_pit[7].x)+(m.y-sence_pit[7].y)*(m.y-sence_pit[7].y)<=1000)
		{
				
			guideboard(sence_pit[7].x-125,sence_pit[7].y-241);
			settextcolor(HSLtoRGB(rand()%360,1,0.5));
			outtextxy(sence_pit[7].x-120,sence_pit[7].y-203,_T("ͼ��ݣ�"));
			outtextxy(sence_pit[7].x-120,sence_pit[7].y-170,_T("����������б����о޴��ֵ���鼮��"));
		}
		else if((m.x-sence_pit[8].x)*(m.x-sence_pit[8].x)+(m.y-sence_pit[8].y)*(m.y-sence_pit[8].y)<=1000)
		{
			
			guideboard(sence_pit[8].x-125,sence_pit[8].y-241);
			settextcolor(HSLtoRGB(rand()%360,1,0.5));
			outtextxy(sence_pit[8].x-120,sence_pit[8].y-203,_T("��Ӿ�ݣ�"));
			outtextxy(sence_pit[8].x-120,sence_pit[8].y-170,_T("���������Ӿ��"));
		}
		else if((m.x-sence_pit[9].x)*(m.x-sence_pit[9].x)+(m.y-sence_pit[9].y)*(m.y-sence_pit[9].y)<=10000)
		{
			
			guideboard(sence_pit[9].x-125,sence_pit[9].y-241);
			settextcolor(HSLtoRGB(rand()%360,1,0.5));
			outtextxy(sence_pit[9].x-120,sence_pit[9].y-203,_T("��ɽ������"));
			outtextxy(sence_pit[9].x-120,sence_pit[9].y-170,_T("��ɽ����ʱ�б�����������"));
			outtextxy(sence_pit[9].x-100,sence_pit[9].y-140,_T("������"));
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


//��ؽڵ�
void dfs(MGraph *G,int numVertexes,int count,int j)
{
	
	int i,k;
	G->visited[numVertexes] = 1;//�õ㱻���� 
//	printf("num%d ",numVertexes);
	count = m;
	count++;          //���� 
//	printf("count %d\n",count);
	for(i = 0;i<G->numVertexes;i++)//ȥ�����Ӧ�ı� 
	{
			G->arc[i][j] = 0;
			G->arc[j][i] = 0;
	}
	for(i = 0;i<G->numVertexes;i++)
	{
		if( G->visited[i]==0 && G->arc[numVertexes][i]!=INFINITY)  //δ���������б߿ɱ��� 
		{
			dfs(G,i,count,j);//�ݹ� 
//			if(j!=0)
//				count++;
		}
		if(m<count)//���ݹ������countȡ�� 
		m = count;
	}
//		printf("qweqwww%d\n",count);
}
void sencejuge(int j)
{
	if(j==0)
	{
		outtextxy(62,170,_T("�ؽڵ��ǣ�"));
		outtextxy(80,200,_T("�����"));
	}
	else if(j==1)
	{
		outtextxy(62,170,_T("�ؽڵ��ǣ�"));
		outtextxy(80,200,_T("Уʷ��"));
	}
	else if(j==2)
	{
		outtextxy(62,170,_T("�ؽڵ��ǣ�"));
		outtextxy(80,200,_T("����԰"));
	}
	else if(j==3)
	{
		outtextxy(62,170,_T("�ؽڵ��ǣ�"));
		outtextxy(80,200,_T("��·���⹫԰"));
	}
	else if(j==4)
	{
		outtextxy(62,170,_T("�ؽڵ��ǣ�"));
		outtextxy(80,200,_T("����ɽ"));
	}
	else if(j==5)
	{
		outtextxy(62,170,_T("�ؽڵ��ǣ�"));
		outtextxy(80,200,_T("����ʳ��"));
	}
	else if(j==6)
	{
		outtextxy(62,170,_T("�ؽڵ��ǣ�"));
		outtextxy(80,200,_T("��֪�㳡"));
	}
	else if(j==7)
	{
		outtextxy(62,170,_T("�ؽڵ��ǣ�"));
		outtextxy(80,200,_T("ͼ���"));
	}
	else if(j==8)
	{
		outtextxy(62,170,_T("�ؽڵ��ǣ�"));
		outtextxy(80,200,_T("��Ӿ��"));
	}
	else if(j==9)
	{
		outtextxy(62,170,_T("�ؽڵ��ǣ�"));
		outtextxy(80,200,_T("��ɽ����"));
	}

}
void cutpoint(MGraph *G)
{
	int j,i;
	int count;
	for(j = 0;j<10;j++)//ѭ������������и�㣬���ܵ��ﲿ�ֵ㣬����countС���ܵ�����һ 
	{
		count = 0;
		CreateMGraph(G);
		G->visited[j] = 1;//���õ��ȥ
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
			settextstyle(30,0,_T("΢���ź�"));
			setbkmode(TRANSPARENT);
			settextcolor(BLACK);
			sencejuge(j);
			Sleep(1000);
			break;
		}
		m = 0;//���� 
	
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
	loadimage(&f,_T("����.jpg"));
	loadimage(&guide,_T("·��.jpg"));
	loadimage(&guide1,_T("·����ͼ.jpg"));
	loadimage(&map2.P,_T("��ͼ2.jpg"));
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
	}//��ʼ����
	return 0;
}