#ifndef EFFECT_H
#define EFFECT_H
#include"pic.h"
class effect
{
public:
	static int all;
	static int list[100];
	static void call(float gx,float gy,float gw,float gh,int gmode,int glast=40,int gvalue1=0,int gvalue2=0)
	{
		if(all<100){Effect[all] = new effect(gx,gy,gw,gh,gmode,glast,gvalue1,gvalue2);all++;}
	}
public:
	float x,y,w,h;
	float yx,yy,yw,yh;
	int count,last;
	int mode;
	int ID;
	int value1,value2;
	float tr;
	effect(float gx,float gy,float gw,float gh,int gmode,int glast=40,int gvalue1=0,int gvalue2=0)
	{
		x=gx,y=gy,w=gw,h=gh,mode=gmode;
		count=0;last=glast;ID=all;value1=gvalue1;value2=gvalue2;
		tr=1.0f;yx=yy=yw=yh=0;
	}
	~effect(){}
	void Show(float cx,float cy,float cw,float ch,int &td)
	{
		int la,lb;
		switch(mode)
		{
		case PIC_EFF1://»Ò³¾
			PicEdit::GetInstance()->Blt(mode,(x-cx)*core_w/cw,(y-cy)*core_h/ch,w*core_w/cw,h*core_h/ch,yx,yy,yw,yh,tr);
			if(value1>0){x-=1;}
			if(value1<0){x+=1;}
			tr=(last-count)/(float)last;
			break;
		case PIC_EFF2://ÅÚ»ð
			yx=0;yy=0;yw=100;yh=80;la=last/8;lb=count/la;
			PicEdit::GetInstance()->BBlt(mode+lb,(x-cx)*core_w/cw,(y-cy)*core_h/ch,w*core_w/cw,h*core_h/ch,yx,yy,yw,yh);
			break;
		case PIC_EFF3://±¬Õ¨
			la=last/5;lb=count/la;
			PicEdit::GetInstance()->Blt(mode+lb,(x-cx)*core_w/cw,(y-cy)*core_h/ch,w*core_w/cw,h*core_h/ch,yx,yy,yw,yh,tr);
			break;
		}

		count++;
		if(count>=last)
		{
			int ls=ID;delete this;
			for(int i=ls;i<all-1;i++)
			{
				Effect[i]=Effect[i+1];
				Effect[i]->ID--;
			}
			ls=all-1;
			all--;td--;
		}
	}
}*Effect[100],*CamEffect[100];
int effect::all = 0;

/*class GIF
{
public:
	GIF(){}
	~GIF(){}
public:
	int num;







};*/





#endif