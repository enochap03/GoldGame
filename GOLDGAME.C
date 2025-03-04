#include<math.h>
#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<stdlib.h>
#include<process.h>
#include<dos.h>
#ifdef __cplusplus
    #define __CPPARGS
#else
    #define __CPPARGS
#endif
void *buf,*buf1;
int count=0,de,stop,level,no;
float bright=450;
void inti_val_set(int i,float a,float b);
void check(int i,float getx,float gety);
void game_start();
void change_speed(int i);
void re_draw();
void erase(int i);
void end();
void put_highscore();
void main_screen();
void take_name();
void help();
void show_mouse();
void getmousepos(int *x,int *y,int *button);
void print_highscore();
union REGS in,ou;
void click(int condition,int x1,int y1,int x2,int y2);
int init_mouse();
void  hide_mouse();
void cal_moveg(int i);
void gold_erase(int i);
void scenary();
void gold_move(int i);
void gold_catch(int i);
void draw(int i);
void cal_move(int i);
float generate_rangex(float x20);
float generate_rangey(float y20);
void fun1();
void collision_detect(int i);
float  generate_goldx();
float tempx,tempy;
struct bullet
{
	float x1,x2,y1,y2,dx,dy,steps,i;
	float xinc,yinc;
};
struct bullet b[5];
struct gold
{
	float gx1,gx2,gy1,dx,dy,steps,i,xinc,yinc;
	int go;
};
struct gold g[2];
struct highest
{
	char name[25];
	int score;
};
struct highest h;
struct highest h1;
void bar_move()
{

	if(bright<=430)
	{
		setfillstyle(SOLID_FILL,2);
		if(bright<200)
		bright+=60;
		else
		bright+=20;
		bar(70,430,bright,440);
	}

}
void bar_erase()
{
	setfillstyle(SOLID_FILL,1);
	bar(70,430,450,440);
}
void put_highscore()
{
	FILE *fp;
	fp=fopen("score.txt","r");
	if(filelength(fileno(fp))>0)
	{
		fread(&h1,sizeof(h1),1,fp);
		if(h.score>h1.score)
		{
			fclose(fp);
			fp=fopen("score.txt","w");
			fwrite(&h,sizeof(h),1,fp);
			fclose(fp);
		}
	}
	else
	{
		fp=fopen("score.txt","w");
		fwrite(&h,sizeof(h),1,fp);
		fclose(fp);
	}

}
void bar_reduce()
{
	if(bright>=70)
	{
		bright-=1.39;
		setfillstyle(SOLID_FILL,2);
		bar(70,430,bright,440);
	}
	else
	{
		put_highscore();
		stop=1;
	}
}
float  generate_goldx()
{
	float sendx;
	while(1)
	{
		sendx=random(450);
		if((sendx>=73)&&(sendx<=447))
		return sendx;
	}
}
void gold_move(int i)
{
	setcolor(15);
	ellipse(g[i].gx1,g[i].gy1,0,360,3,3);
	setfillstyle(SOLID_FILL,14);
	fillellipse(g[i].gx1,g[i].gy1,3,3);
}
void gold_erase(int i)
{
	setcolor(1);
	ellipse(g[i].gx1,g[i].gy1,0,360,3,3);
	setfillstyle(SOLID_FILL,0);
	g[i].i+=1;
	fillellipse(g[i].gx1,g[i].gy1,3,3);
	g[i].gx1+=g[i].xinc;
	g[i].gy1+=g[i].yinc;
}
int init_mouse()
{
	in.x.ax=0;
	int86(0x33,&in,&ou);
	return (ou.x.ax);
}
void  hide_mouse()
{
	in.x.ax=2;
	int86(0x33,&in,&ou);
}
void help()
{
	 int x,y,button;
	 hide_mouse();
	 setlinestyle(SOLID_LINE, 1, 3);
	 setcolor(14);
	 rectangle(0,0,640,480);
	 setfillstyle(SOLID_FILL,1);
	 bar(1,1,639,479);
	 setfillstyle(SOLID_FILL,12);
	 bar(150,150,500,370);
	 outtextxy(280,180,"GAME HELP");
	 outtextxy(200,220,"IN THIS GAME YOU MUST ESCAPE");
	 outtextxy(200,240,"FROM THE BULLETS THAT IS ");
	 outtextxy(200,260,"STRIKING UPON YOU (USING ARROWS");
	 outtextxy(200,280,"KEYS) FOR EVERY SECOND FOR SURVIVAL");
	 outtextxy(200,300,"YOU GAIN TWO POINTS(SCORE),ENERGY");
	 outtextxy(200,320,"LEVEL DECREASES FOR EVERY SECOND,");
	 outtextxy(200,340,"TO KEEP THE ENERGY LEVEL INCREASE");
	 outtextxy(200,360,"CATCH THE GOLD.");
	 setfillstyle(SOLID_FILL,7);
	 bar(480,380,530,400);
	 click(0,480,380,530,400);
	 outtextxy(500,387,"OK");
	 show_mouse();
	 while(1)
	 {
		getmousepos(&x,&y,&button);
		if((x>480)&&(y>380)&&(x<530)&&(y<400)&&(button==1))
		{
			click(1,480,380,530,400);
			delay(100);
			click(0,480,380,530,400);
			main_screen();
			break;
		}
	 }

}

void show_mouse()
{
	in.x.ax=1;
	int86(0x33,&in,&ou);
}
void getmousepos(int *x,int *y,int *button)
{
	in.x.ax=3;
	int86(0x33,&in,&ou);
	*button=ou.x.bx;
	*x=ou.x.cx;
	*y=ou.x.dx;
}
void about()
{
	 int x,y,button;
	 hide_mouse();
	 setlinestyle(SOLID_LINE, 1, 3);
	 setcolor(14);
	 rectangle(0,0,640,480);
	 setfillstyle(SOLID_FILL,1);
	 bar(1,1,639,479);
	 setfillstyle(SOLID_FILL,12);
	 bar(150,150,450,350);
	 outtextxy(240,180,"DEVELOPED BY");
	 outtextxy(195,240,"1) HAIRHARAN.A");
		 setfillstyle(SOLID_FILL,7);
	 bar(480,380,530,400);
	 click(0,480,380,530,400);
	 setcolor(4);
	 outtextxy(495,385,"OK");
	 show_mouse();
	 while(1)
	 {
		getmousepos(&x,&y,&button);
		if((x>480)&&(y>380)&&(x<530)&&(y<400)&&(button==1))
		{
			click(1,480,380,530,400);
			delay(100);
			click(0,480,380,530,400);
			main_screen();
			break;
		}
	 }

}
void print_highscore()
{
	FILE *fp;    char temp[20];
	int x,y,button,sam;
	hide_mouse();
	cleardevice();
	setfillstyle(SOLID_FILL,15);
	bar(150,150,350,300);
	setbkcolor(3);
	setcolor(7);
	outtextxy(170,200,"NAME:");
	outtextxy(170,220,"SCORE:");
	if((fp=fopen("score.txt","r"))!=NULL)
	{
		if(filelength(fileno(fp))>0)
		{
			fread(&h1,sizeof(h1),1,fp);
			outtextxy(220,200,h1.name);
			sam=h1.score;
			itoa(sam,temp,10);
			outtextxy(220,220,temp);

		}
		else
		{
			outtextxy(220,200,"NULL");
			outtextxy(220,220,"NULL");
		}
	}
	else
	{
		outtextxy(220,200,"NULL");
		outtextxy(220,220,"NULL");
	}
	setfillstyle(SOLID_FILL,7);
	bar(280,260,330,280);
	click(0,280,260,330,280);
	setcolor(4);
	outtextxy(300,265,"OK");
	show_mouse();
	while(1)
	{
		getmousepos(&x,&y,&button);
		if((x>280)&&(y>260)&&(x<330)&&(y<280)&&(button==1))
		{
			click(1,280,260,330,280);
			delay(100);
			click(0,280,260,330,280);
			main_screen();
			break;
		}
	}
}
void click(int condition,int x1,int y1,int x2,int y2)
{
	int first,next;
	if(condition==0)
	{
		first=15;
		next=0;
	}
	else
	{
		first=0;
		next=15;
	}
	setcolor(first);
	line(x1,y1,x2,y1);
	line(x1,y1,x1,y2);
	setcolor(next);
	line(x1,y2,x2,y2);
	line(x2,y1,x2,y2);
}
void main_screen()
{

	hide_mouse();
	cleardevice();
	setfillstyle(SOLID_FILL,9);
	bar(1,1,640,480);
	setpalette(GREEN,15);
	setlinestyle(SOLID_LINE, 1, 3);
	setcolor(YELLOW);
	rectangle(0,0,635,479);
	setlinestyle(0,0,1);
	setfillstyle(1,GREEN);
	bar(1,1,634,478);
	setfillstyle(1,BLUE);
	bar(5,5,630,25);
	outtextxy(260,10,"GOLD GAME");
	setfillstyle(SOLID_FILL,7);
	bar(25,100,115,120);
	click(0,25,100,115,120);
	setcolor(4);
	outtextxy(40,105,"NEW GAME");
	bar(120,150,210,170);
	click(0,120,150,210,170);
	setcolor(4);
	outtextxy(127,155,"HIGH SCORE");
	bar(215,200,305,220);
	click(0,215,200,305,220);
	setcolor(4);
	outtextxy(240,205,"HELP");
	bar(310,250,400,270);
	click(0,310,250,400,270);
	setcolor(4);
	outtextxy(335,255,"ABOUT");
	bar(405,300,495,320);
	click(0,405,300,495,320);
	setcolor(4);
	outtextxy(435,305,"EXIT");
	show_mouse();
}

void scenary()
{
	int i;
	cleardevice();
	setbkcolor(1);
		setcolor(6);
	for(i=0;i<=50;i++)
	{
		arc(400-i,250,160,190,400);
		line(25-i,479,6-i,321);

	}
	setcolor(2);
	for(i=0;i<=200;i++)
	{
		arc(50-i,80,234,360,50);
		arc(70-i,45,300,80,50);
	}
	setcolor(6);
	for(i=0;i<=55;i++)
	{
		arc(970-i,250,160,230,400);
		arc(110+i,250,230,20,400);
	}
	for(i=0;i<=80;i++)
	line(500+i,380,480+i,479);
	for(i=0;i<=40;i++)
	line(560+i,420,560+i,479);
	setcolor(2);
	for(i=0;i<=250;i++)
	{
		arc(500+i,60,120,270,60);
		arc(470+i,1,180,270,60);
	}
}
struct man
{
	float cx,cy,left,right,bottom,top;
};
struct man m1;
void init_man()
{
		m1.cx=80;m1.cy=380;
		m1.left=75;m1.top=385;m1.right=85;m1.bottom=396;
}
float getposy()
{
	return m1.bottom;
}
float getposx()
{
	return m1.cx;
}
void move_man()
{
	int i;
	putimage(m1.cx-7,m1.cy-7,buf,0);

}
void erase_man()
{
	putimage(m1.cx-7,m1.cy-7,buf1,0);
}
void interrupt Keyboard_ISR(__CPPARGS);    /* NEW interrupt prototype */
void interrupt (*OldInterrupt)(__CPPARGS);         /* Old interrupt function pointer */
int key_table[300];
void interrupt Keyboard_ISR()
{
 int key,i;
 asm{ sti
      in al,0x60
      xor ah,ah
      mov key,ax
      in al,0x61
      or al,0x82
      out 0x61,al
      and al,0x7f
      out 0x61,al
      mov al,0x20
      out 0x20,al
      cli
    }
 if(key < 84)
   {key_table[key]=1;
   }
 else if(key < 212)
   {key_table[key-128]=0;
   }
   if((key_table[72]==1)||(key_table[77]==1)||(key_table[75]==1)||(key_table[80]==1)||(key_table[1]==1))
   {
	fun1();
   }

}
void fun1()
{
	int i,j;           char ch;
	if (key_table[72]==1)
		{

			if(m1.top>=165)
			{
				erase_man();
				m1.top-=3;
				m1.bottom-=3;
				m1.cy-=3;
				move_man();

			}
		}
		if(key_table[75]==1)
		{

			if(m1.left>=74)
			{
				erase_man();
				m1.left-=3;
				m1.right-=3;
				m1.cx-=3;
				move_man();
			}

		}
		if(key_table[77]==1)
		{
			if(m1.right<=446)
			{
				erase_man();
				m1.left+=3;
				m1.right+=3;
				m1.cx+=3;
				move_man();
			}

		}
		if(key_table[80]==1)
		{
			if(m1.bottom<=395)
			{
				erase_man();
				m1.top+=3;
				m1.bottom+=3;
				m1.cy+=3;
				move_man();
			}

		}
			if(key_table[1]==1)
			{
				_dos_setvect(0x09,OldInterrupt);
				put_highscore();
				stop=1;
			}

}
void take_name()
{
	int x,y,button,i=-1;
	char gname[25],ch;
	level=-1;
	hide_mouse();
	cleardevice();
	setfillstyle(SOLID_FILL,14);
	bar(150,150,450,300);
	setfillstyle(SOLID_FILL,0);
	bar(300,190,440,210);
	setfillstyle(SOLID_FILL,0);
	bar(300,220,440,240);
	setbkcolor(1);
	setcolor(7);
	outtextxy(170,200,"ENTER YOUR NAME:");
	outtextxy(170,230,"ENTER THE LEVEL:");
	setfillstyle(SOLID_FILL,7);
	bar(280,260,330,280);
	click(0,280,260,330,280);
	setcolor(4);
	outtextxy(300,265,"OK");
	while(1)
	{
		setcolor(15);
		gotoxy(39,13);
		ch=getchar();
		i++;
		gname[i]=ch;
		if(ch=='\n')
		{
			gname[i]='\0';
			strcpy(h.name,gname);
			break;
		}
	}
	while(1)
	{
		gotoxy(39,15);
		ch=getchar();
		if(ch!='\n')
		{
			ch-=48;
			level=ch;
			if((level>3)||(level==0))
			{
				level=-1;
				setfillstyle(SOLID_FILL,0);
				bar(300,220,440,240);
				gotoxy(39,15);
			}
		}
		else if((ch=='\n')&&(level>-1))
			break;

	}
	show_mouse();
	while(1)
	{
		getmousepos(&x,&y,&button);
		if((x>280)&&(y>260)&&(x<330)&&(y<280)&&(button==1))
		{
			click(1,280,260,330,280);
			delay(100);
			click(0,280,260,330,280);
			break;
		}
	}
}

void end()
{
	bar(150,150,400,250);
	outtextxy(165,190,"GAME IS OVER PRESS ANY KEY");
	delay(1000);
}

float generate_rangex(float x20)
{
	float send;
	while(1)
	{

		send=random(x20+2);
		if((send>=x20)&&(send<=450))
		return send;
	}
}
void  collision_detect(int i)
{
	if((b[i].x1+5>=m1.left)&&(b[i].y1+3>=m1.top-10)&&(b[i].x1-5<=m1.right)&&(b[i].y1+3<=m1.bottom))
	{
		put_highscore();
		stop=1;
	}
}
float generate_rangey(float y20)
{
	float y01,y02,tempy1;
	y01=y20-20;
	y02=y20+20;
	while(1)
	{
		tempy1=random(y02);
		if((tempy1<y02)&&(tempy1>y01)&&(tempy1<395)&&(tempy1>=153))
		return tempy1;
	}
}

void inti_val_set(int i,float a,float tr)
{
	b[i].x1=73;b[i].y1=155;
	b[i].x2=a; b[i].y2=tr;
}
void gold_end(int i)
{
	if(g[i].gy1>=397)
	{
		g[i].go=0;
		gold_erase(i);

	}
}
void cal_moveg(int i)
{

	g[i].go=1;
	g[i].i=0;
	g[i].gy1=153;
	g[i].dx=g[i].gx2-g[i].gx1;g[i].dy=250;
	if(fabs(g[i].dx)>fabs(g[i].dy))
		g[i].steps=fabs(g[i].dx);
	else
		g[i].steps=fabs(g[i].dy);
	g[i].xinc=g[i].dx/g[i].steps;
	g[i].yinc=g[i].dy/g[i].steps;
}
void cal_move(int i)
{
	b[i].i=0;
	b[i].dx=b[i].x2-b[i].x1;b[i].dy=b[i].y2-b[i].y1;
	if(fabs(b[i].dx)>fabs(b[i].dy))
		b[i].steps=fabs(b[i].dx);
	else
		b[i].steps=fabs(b[i].dy);
	b[i].xinc=b[i].dx/b[i].steps;
	b[i].yinc=b[i].dy/b[i].steps;
}
void draw(int i)
{
	setcolor(15);
	ellipse(b[i].x1,b[i].y1,0,360,3,5);
	setfillstyle(SOLID_FILL,3);
	fillellipse(b[i].x1,b[i].y1,3,5);
}
void erase(int i)
{
  //	scenary();
	setcolor(1);
	ellipse(b[i].x1,b[i].y1,0,360,3,5);
	setfillstyle(SOLID_FILL,0);
	fillellipse(b[i].x1,b[i].y1,3,5);
	b[i].x1+=b[i].xinc;
	b[i].y1+=b[i].yinc;
	b[i].i+=1;
}
void check(int i,float getx,float gety)
{
	if(b[i].i>=b[i].steps)
	{
		tempx=generate_rangex(getx);
		tempy=generate_rangey(gety);
		inti_val_set(i,tempx,tempy);
		cal_move(i);
	}
}
void gold_catch(i)
{
	if((g[i].gx1+3>=m1.left)&&(g[i].gy1+3>=m1.top-10)&&(g[i].gx1-3<=m1.right)&&(g[i].gy1+3<=m1.bottom))
	{
		gold_erase(i);
		g[i].go=0;
		bar_erase();
		bar_move();
	}

}
void change_speed(int i)
{
	if(i==1)
	{
		de=5;
		no=3;
	}
	else if(i==2)
	{
		de=3;
		no=5;
	}
	else if(i==3)
	{
		de=1;
		no=5;
	}
}
void game_start()
{
	int i,size,count1=0,j;
	char ch[10],ch1[10],ch2[10];
	h.score=0;
	count=0;
	g[0].go=0;
	g[1].go=0;
	bright=450;
	hide_mouse();
	init_man();
	//move_man();
	cleardevice();
	setpalette(GREEN,GREEN);
	setcolor(5);
	setfillstyle(SOLID_FILL,5);
	fillellipse(m1.cx,m1.cy,5,5);
	setfillstyle(SOLID_FILL,5);
	bar(m1.left,m1.top,m1.right,m1.bottom);
	size=imagesize(73,373,87,398);
	buf=malloc(size);
	getimage(73,373,87,398,buf);
	cleardevice();
	setcolor(1);
	setfillstyle(SOLID_FILL,1);
	fillellipse(m1.cx,m1.cy,5,5);
	setfillstyle(SOLID_FILL,1);
	bar(m1.left,m1.top,m1.right,m1.bottom);
	size=imagesize(73,373,87,398);
	buf1=malloc(size);
	getimage(73,373,87,398,buf1);
	cleardevice();
	scenary();
	setcolor(15);
	setlinestyle(SOLID_LINE,1,3);
	rectangle(67,147,453,403);
	setlinestyle(SOLID_LINE,1,1);
	setfillstyle(SOLID_FILL,2);
	outtextxy(198,30,"TIME:");
	outtextxy(75,135,"NAME:");
	outtextxy(115,135,h.name);
	outtextxy(370,135,"SCORE:");
	outtextxy(215,135,"LEVEL:");
	itoa(level,ch2,10);
	outtextxy(280,135,ch2);
	//bar(70,430,450,440);
	for(i=0;i<no;i++)
	{
		tempx=getposx();
		tempy=getposy();
		tempx=generate_rangex(tempx);
		tempy=generate_rangey(tempy);
		inti_val_set(i,tempx,tempy);
		cal_move(i);
	}
	while(1)
	{
		tempx=getposx();
		tempy=getposy();
		for(i=0;i<no;i++)
		{
			tempx=generate_rangex(tempx);
			tempy=generate_rangey(tempy);

			check(i,tempx,tempy);
			collision_detect(i);
			if(stop==1)
			goto terminate;
			draw(i);
		}
		delay(de);
		for(i=0;i<no;i++)
		{
			erase(i);
		}
		count++;
		if(count%60==0)
		{
			bar_erase();
			bar_reduce();
			if(stop==1)
			goto terminate;
		}
		if(count%5==0)
		{

			for(j=0;j<2;j++)
			{
				if(g[j].go==1)
				{
					gold_end(j);
					gold_erase(j);
					if(g[j].go==1)
					{
						gold_catch(j);
						if(g[j].go==1)
						gold_move(j);
					}
				}
			}
		}
		if(count%150==0)
		{
			count1++;
			h.score+=2;
			itoa(count1,ch,10);
			if((level==1)&&(count1==60))
			{
				count1=0;
				level=2;
				change_speed(level);
				itoa(level,ch2,10);
				setfillstyle(SOLID_FILL,1);
				bar(280,125,300,140);
				setcolor(15);
				outtextxy(280,135,ch2);
			}
			if((level==2)&&(count1==30))
			{
				count1=0;
				level=3;
				change_speed(level);
				itoa(level,ch2,10);
				setfillstyle(SOLID_FILL,1);
				bar(280,125,300,140);
				setcolor(15);
				outtextxy(280,135,ch2);
			}
			setcolor(1);
			setfillstyle(SOLID_FILL,1);
			bar(235,20,280,45);
			setcolor(15);
			outtextxy(250,30,ch);
			itoa(h.score,ch1,10);
			setcolor(1);
			setfillstyle(SOLID_FILL,1);
			bar(415,130,450,143);
			setcolor(15);
			outtextxy(425,135,ch1);
			if(count1%10==0)
			{

				for(j=0;j<2;j++)
				{
					g[j].gx1=generate_goldx();
					g[j].gx2=generate_goldx();
					cal_moveg(j);
				}
			}

		}
		terminate:
		if(stop==1)
		break;

	}
	put_highscore();
	end();
	show_mouse();
}
void main()
{
	int gd=VGA,gm=VGAHI,x,y,botton;
	initgraph(&gd,&gm,"..\\bgi");
	randomize();
	main_screen();
	init_mouse();
	show_mouse();
	while(1)
	{
		getmousepos(&x,&y,&botton);
		if((x>25)&&(y>100)&&(x<115)&&(y<120)&&(botton==1))
		{
			click(1,25,100,115,120);
			delay(100);
			click(0,25,100,115,120);
			cleardevice();
			take_name();
			OldInterrupt=_dos_getvect(0x09);
			_dos_setvect(0x09,Keyboard_ISR);
			change_speed(level);
			setfillstyle(SOLID_FILL,6);
			stop=0;
			game_start();
			_dos_setvect(0x09,OldInterrupt);
			main_screen();
		}
		else if((x>120)&&(y>150)&&(x<210)&&(y<170)&&(botton==1))
		{
			click(1,120,150,210,170);
			delay(100);
			click(0,120,150,210,170);
			cleardevice();
			print_highscore();
		}
		else if((x>215)&&(y>200)&&(x<305)&&(y<220)&&(botton==1))
		{
			click(1,215,200,304,220);
			delay(100);
			click(0,215,200,304,220);
			cleardevice();
			help();
		}
		else if((x>310)&&(y>250)&&(x<400)&&(y<270)&&(botton==1))
		{
			click(1,310,250,400,270);
			delay(100);
			click(0,310,250,400,270);
			cleardevice();
			about();
		}
		else if((x>405)&&(y>300)&&(x<495)&&(y<320)&&(botton==1))
		{
			click(1,405,300,495,320);
			delay(100);
			click(0,405,300,495,320);
			exit(0);
		}

	}

}


