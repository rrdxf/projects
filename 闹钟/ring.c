#include<reg51.h>
#define DB P0
sbit ring=P3^0;
sbit RS=P3^5;
sbit RW=P3^6;
sbit EN=P3^4;


sbit k1=P1^0;
sbit k2=P1^1;
sbit k3=P1^2;
sbit k4=P1^3;
sbit k5=P1^4;
sbit k6=P1^5;
sbit k7=P1^6;
sbit k8=P1^7;


unsigned char shield[]={0,0,0,0,0,0,0,0,0,0};


unsigned char count=0;
unsigned char timecount=0;

unsigned char timeflag=0;


unsigned char hour1[]={0,2,3,4,6,1,7,8,9,10};
unsigned char min1[]={1,2,3};

unsigned char hour2[]={0,2,3};
unsigned char min2[]={11,12,22};

unsigned int beetime[]={10,0,0,0,0,0,0,0,0,0};
unsigned int timerbeetime[]={0,0,0};

unsigned char function=0;
unsigned char deda=0;
unsigned char string[]="0123456789";
unsigned char hour=0,sec=0,min=0,date=15,month=6,year=20,week=1;

void delay(unsigned int cnt)
{
 unsigned char i,j;
	for(i=0;i<cnt;i++)
	{
		for(j=0;j<120;j++);
	}
}

void w_com(unsigned char conmmand)
{
	RS=0;
	RW=0;
	EN=0;
	DB=conmmand;
	delay(1);
	EN=1;
	delay(1);
	EN=0;
}
void w_data(unsigned int dat)
{
	RS=1;
	RW=0;
	EN=0;
	DB=dat;
	delay(1);
	EN=1;
	delay(1);
	EN=0;
}
	
void init()
{
	delay(15);
	w_com(0x38);delay(5);
	w_com(0x0c);delay(5);
	w_com(0x06);delay(5);
	w_com(0x01);delay(5);
	w_com(0x80);delay(5);
}
void show()
{
	w_com(0x80+0x00);
		w_data('2');
		w_data('0');
		w_data(string[year/10]);
		w_data(string[year%10]);
		w_data('-');
	
		w_data(string[month/10]);
		w_data(string[month%10]);
		w_data('-');
	
		w_data(string[date/10]);
		w_data(string[date%10]);
		w_data(' ');
		w_data('d');
		w_data('a');
		w_data('y');
		w_data(':');
		w_data(string[week%10]);
	
	w_com(0x80+0x40);
		w_data(' ');
		w_data(' ');
		w_data(' ');
		w_data(' ');
		w_data(string[hour/10]);
		w_data(string[hour%10]);
		w_data(':');
	
		w_data(string[min/10]);
		w_data(string[min%10]);
		w_data(':');
	
		w_data(string[sec/10]);
		w_data(string[sec%10]);
		w_data(' ');
		w_data(' ');
		w_data(' ');
		w_data(' ');
		w_data(' ');

		delay(1);	
		
}

void inter_month()
{
	switch(month)
	{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:if(date==32)
						{
							date=1;
							month++;
							if(month==13)
							{
								month=1;
								year++;
							}
						};
						break;
		case 4:
		case 6:
		case 9:
		case 11:if(date==31)
						{
							date=1;
							month++;
							if(month==13)
							{
								month=1;
								year++;
							}
						};
						break;
		case 2:if(year%4==0)
					{
						if(date==30)
						{
							date=1;
							month++;
						}
					}
					else
					{
						if(date==29)
						{
							date=1;
							month++;
						}
					};
					break;
		default:break;
	}
}

void inter_month1()
{
	switch(month)
	{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:if(date==32)
						{
							date=1;
							
							if(month==13)
							{
								month=1;
								
							}
						};
						break;
		case 4:
		case 6:
		case 9:
		case 11:if(date==31)
						{
							date=1;
							
							if(month==13)
							{
								month=1;
							
							}
						};
						break;
		case 2:if(year%4==0)
					{
						if(date==30)
						{
							date=1;
						
						}
					}
					else
					{
						if(date==29)
						{
							date=1;
							
						}
					};
					break;
		default:break;
	}
}
void conv()
{
	if(sec==60)
	{
		min++;
		sec=0;
		if(min==60)
		{
			min=0;
			hour++;
			if(hour==24)
			{
				hour=0;
				date++;
				inter_month();
				if(month==13)
				{
					year++;
					month=1;
					if(year==100)
						year=0;
				}
			}
		}
	}
}
void init_timer()
{
	TMOD=0x01;
	TH0=(65535-50000)/256;
	TL0=(65535-50000)%256;
	EA=1;
	ET0=1;
	TR0=1;
}


void set_time()
{
	if(!k2)
	{
		delay(150);
		if(!k2)
		{
			year++;
		}
	}
	if(!k3)
	{
		delay(150);
		if(!k3)
		{
			year--;
		}
	}
	if(!k4)
	{
		delay(150);
		if(!k4)
		{
			month++;
			if(month==13)
				month=1;
		}
	}
	if(!k5)
	{
		delay(150);
		if(!k5)
		{
			date++;
			inter_month1();
		}
	}
	if(!k6)
	{
		delay(150);
		if(!k6)
		{
			hour++;
			if(hour==24)
				hour=0;
		}
	}
	if(!k7)
	{
		delay(150);
		if(!k7)
		{
			min++;
			if(min==60)
				min=0;
		}
	}
	if(!k8)
	{
		delay(150);
		if(!k8)
		{
			week++;
			if(week==8)
				week=1;
		}
	}
}


show1()
{
	w_com(0x80+0x00);

	w_data('n');
	w_data('u');
	w_data('m');
	w_data(':');
		w_data(string[count/10]);
		w_data(string[count%10]);
	//	w_data(':');
		w_data(' ');
		w_data(' ');
		w_data(' ');
		w_data(string[hour1[count]/10]);
		w_data(string[hour1[count]%10]);
		w_data(':');

		w_data(string[min1[count]/10]);
		w_data(string[min1[count]%10]);

	w_data(' ');
	w_data(' ');
	
		delay(1);	
	
	w_com(0x80+0x40);
	w_data('t');
	w_data('i');
	w_data('m');
	w_data('e');
	w_data('.');
		w_data(string[beetime[count]/10]);
		w_data(string[beetime[count]%10]);
			w_data(' ');
		w_data('s');
		w_data('h');
		w_data('e');
		w_data('i');
		w_data('l');
		w_data('d');
		w_data('.');
		if(shield==0)
			w_data('N');
		else
			w_data('Y');
		
}
show2()
{
	w_com(0x80+0x00);

	w_data('n');
	w_data('u');
	w_data('m');
	w_data(':');
		w_data(string[timecount/10]);
		w_data(string[timecount%10]);
	//	w_data(':');
		w_data(' ');
		w_data(' ');
		w_data(' ');
		w_data(string[hour2[timecount]/10]);
		w_data(string[hour2[timecount]%10]);
		w_data(':');

		w_data(string[min2[timecount]/10]);
		w_data(string[min2[timecount]%10]);

	w_data(' ');
	w_data(' ');
	
		delay(1);	
	
	w_com(0x80+0x40);
	w_data('t');
	w_data('i');
	w_data('m');
	w_data('e');
	w_data('.');
		w_data(string[timerbeetime[timecount]/10]);
		w_data(string[timerbeetime[timecount]%10]);
			w_data(' ');
			w_data(' ');
			w_data(' ');
			w_data(' ');
			w_data(' ');
			w_data(' ');
			w_data(' ');
			w_data(' ');
			w_data(' ');
		delay(1);
}
void set_bee()
{
	if(timeflag==0)
	{
		if(!k2)
		{
			delay(150);
			if(!k2)
			{
				hour1[count]++;
				if(hour1[count]==24)
					hour1[count]=0;
			}
		}
		if(!k2)
		{
			delay(150);
			if(!k3)
			{
				min1[count]++;
				if(min1[count]==60)
					min1[count]=0;
			}
		}
		if(!k4)
		{
			delay(150);
			if(!k4)
			{
				count++;
				if(count==10)
					count=0;
			}
		}
		if(!k5)
		{
			delay(150);
			if(!k5)
			{
				count--;
				if(count=0)
					count=9;
			}
		}
		if(!k6)
		{
			delay(150);
			if(!k6)
			{
				beetime[count]++;
				if(beetime[count]==61)
					beetime[count]=0;
			}
		}
		if(!k7)
		{
			delay(150);
			if(!k7)
			{
				shield[count]++;
				if(shield[count]==2)
					shield[count]=0;
			}
		}
		if(!k8)
		{
			delay(150);
			if(!k8)
			{
				timeflag++;
				if(timeflag==2)
					timeflag=0;
			}
		}
	}
	else if(timeflag==1)
	{
		if(!k2)
		{
			delay(150);
			if(!k2)
			{
				hour2[timecount]++;
				if(hour2[timecount]==24)
					hour2[timecount]=0;
			}
		}
		if(!k2)
		{
			delay(150);
			if(!k3)
			{
				min2[timecount]++;
				if(min2==60)
					min2[timecount]=0;
			}
		}
		if(!k4)
		{
			delay(150);
			if(!k4)
			{
				timecount++;
				if(timecount==5)
					timecount=0;
			}
		}
		if(!k5)
		{
			delay(150);
			if(!k5)
			{
				timecount--;
				if(timecount==0)
					timecount=2;
			}
		}
		if(!k6)
		{
			delay(150);
			if(!k6)
			{
				timerbeetime[timecount]++;
				if(beetime[timecount]==61)
					timerbeetime[timecount]=0;
			}
		}
		if(!k8)
		{
			delay(150);
			if(!k8)
			{
				timeflag++;
				if(timeflag==2)
					timeflag=0;
			}
		}
	}
}

void compare()
{
	unsigned i;
	unsigned j;
	for(i=0;i<10;i++)
	{
		if(min==min1[i]&&hour==hour1[i]&&sec<=beetime[i]&&week!=6&&week!=7&&shield[i]==0)
		{
					ring=1;delay(80);
		}
		else
			ring=0;
	}
	for(j=0;j<10;j++)
	{
		if(min==min2[j]&&hour==hour2[j]&&sec<=beetime[j]&&week!=6&&week!=7)
		{
					ring=1;delay(80);
				timerbeetime[j]=timerbeetime[j]-sec;
		}
		else
			ring=0;
	}
}
void cls()
{
	w_com(0x80+0x00);
		w_data(' ');
		w_data(' ');
		w_data(' ');
		w_data(' ');
		w_data(' ');
		w_data(' ');
		w_data(' ');
		w_data(' ');
		w_data(' ');
		w_data(' ');
		w_data(' ');
	w_data(' ');
		w_data(' ');
		w_data(' ');
		w_data(' ');
		w_data(' ');
		w_data(' ');
		w_data(' ');
		w_data(' ');
		w_data(' ');
		w_data(' ');
		w_data(' ');
	
	
	w_com(0x80+0x40);
		w_data(' ');
		w_data(' ');
		w_data(' ');
		w_data(' ');
		w_data(' ');
		w_data(' ');
		w_data(' ');
		w_data(' ');
		w_data(' ');
		w_data(' ');
		w_data(' ');
		w_data(' ');
		w_data(' ');
		w_data(' ');
		w_data(' ');
		w_data(' ');
		w_data(' ');
		w_data(' ');
		w_data(' ');
		w_data(' ');
		w_data(' ');
		w_data(' ');
}



void main()
{
	init();
	init_timer();
	delay(200);
	ring=0;
	while(1)
	{
		if(!k1)
		{
			delay(150);
			if(!k1)
			{
				function++;
				if(function==3)
					function=0;
			}
		}
		if(function==0)
		{
			EA=1;
			ET0=1;
			TR0=1;
			show();
		}
		else if(function==1)
		{
			EA=0;
			ET0=0;
			TR0=0;
			set_time();
			show();
		}
		else if(function==2)
		{
			EA=1;
			ET0=1;
			TR0=1;
			set_bee();
			if(timeflag==0)
				show1();
			else
				show2();
		}
		compare();
	}
}
void T0_srv(void)interrupt 1
{
	TH0=(65535-50000)/256;
	TL0=(65535-50000)%256;
	deda++;
	if(deda==20)
	{
		sec++;
		deda=0;
		conv();
	}
}