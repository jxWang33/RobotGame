#include"map.h"
#include"pic.h"
#include"basicthing.h"
#include"define.h"
#include"windows.h"
#include"effect.h"
#ifndef HERO_H
#define HERO_H

extern int addnum;
int  dietime=-2;//感觉应该用long int，不，是long long int
class arrow:public basicthing
{
public:
	bool ex;
	bool dis;
	float prex,prey;

	int mode,now;
	void Show(float cx,float cy,float cw,float ch)
	{
		if(mode==0){PicEdit::GetInstance()->Blt(PIC_HUOQIU,(x-cx)*core_w/cw,(y-cy)*core_h/ch,w*core_w/cw,h*core_h/ch,0,0,128,128);}
		if(mode==1)
		{
			if(dir==0)
			{
				if(now<1){PicEdit::GetInstance()->BBlt(PIC_HRO_1,(x-cx)*core_w/cw,(y-cy)*core_h/ch,w*core_w/cw,h*core_h/ch,290+65*4,180,20,20);}
				else if(now<2){PicEdit::GetInstance()->BBlt(PIC_HRO_1,(x-cx)*core_w/cw,(y-cy)*core_h/ch,w*core_w/cw,h*core_h/ch,290+65*3,180,20,20);}
				else if(now<3){PicEdit::GetInstance()->BBlt(PIC_HRO_1,(x-cx)*core_w/cw,(y-cy)*core_h/ch,w*core_w/cw,h*core_h/ch,290+65*2,180,20,20);}
				else if(now<4){PicEdit::GetInstance()->BBlt(PIC_HRO_1,(x-cx)*core_w/cw,(y-cy)*core_h/ch,w*core_w/cw,h*core_h/ch,290+65*1,180,20,20);}
				else if(now<=20){PicEdit::GetInstance()->BBlt(PIC_HRO_1,(x-cx)*core_w/cw,(y-cy)*core_h/ch,w*core_w/cw,h*core_h/ch,290+65*0,180,20,20);}
				else if(now<32){PicEdit::GetInstance()->BBlt(PIC_HRO_1,(x-cx)*core_w/cw,(y-cy)*core_h/ch,w*core_w/cw,h*core_h/ch,290+65*0,35,20,20);}
				else if(now<34){PicEdit::GetInstance()->BBlt(PIC_HRO_1,(x-cx)*core_w/cw,(y-cy)*core_h/ch,w*core_w/cw,h*core_h/ch,290+65*1,35,20,20);}
				else if(now<36){PicEdit::GetInstance()->BBlt(PIC_HRO_1,(x-cx)*core_w/cw,(y-cy)*core_h/ch,w*core_w/cw,h*core_h/ch,290+65*2,35,20,20);}
				else if(now<38){PicEdit::GetInstance()->BBlt(PIC_HRO_1,(x-cx)*core_w/cw,(y-cy)*core_h/ch,w*core_w/cw,h*core_h/ch,290+65*3,35,20,20);}
			}
			if(dir==1)
			{
				if(now<1){PicEdit::GetInstance()->BBlt(PIC_HRO_1,(x-cx+w)*core_w/cw,(y-cy)*core_h/ch,-w*core_w/cw,h*core_h/ch,290+65*4,180,20,20);}
				else if(now<2){PicEdit::GetInstance()->BBlt(PIC_HRO_1,(x-cx+w)*core_w/cw,(y-cy)*core_h/ch,-w*core_w/cw,h*core_h/ch,290+65*3,180,20,20);}
				else if(now<3){PicEdit::GetInstance()->BBlt(PIC_HRO_1,(x-cx+w)*core_w/cw,(y-cy)*core_h/ch,-w*core_w/cw,h*core_h/ch,290+65*2,180,20,20);}
				else if(now<4){PicEdit::GetInstance()->BBlt(PIC_HRO_1,(x-cx+w)*core_w/cw,(y-cy)*core_h/ch,-w*core_w/cw,h*core_h/ch,290+65*1,180,20,20);}
				else if(now<=20){PicEdit::GetInstance()->BBlt(PIC_HRO_1,(x-cx+w)*core_w/cw,(y-cy)*core_h/ch,-w*core_w/cw,h*core_h/ch,290+65*0,180,20,20);}
				else if(now<32){PicEdit::GetInstance()->BBlt(PIC_HRO_1,(x-cx+w)*core_w/cw,(y-cy)*core_h/ch,-w*core_w/cw,h*core_h/ch,290+65*0,35,20,20);}
				else if(now<34){PicEdit::GetInstance()->BBlt(PIC_HRO_1,(x-cx+w)*core_w/cw,(y-cy)*core_h/ch,-w*core_w/cw,h*core_h/ch,290+65*1,35,20,20);}
				else if(now<36){PicEdit::GetInstance()->BBlt(PIC_HRO_1,(x-cx+w)*core_w/cw,(y-cy)*core_h/ch,-w*core_w/cw,h*core_h/ch,290+65*2,35,20,20);}
				else if(now<38){PicEdit::GetInstance()->BBlt(PIC_HRO_1,(x-cx+w)*core_w/cw,(y-cy)*core_h/ch,-w*core_w/cw,h*core_h/ch,290+65*3,35,20,20);}
			}
			if(now<20){now++;}
		}prex=x;prey=y;
		Move();
		for(int i=0;i<4;i++){if(!allow[i]){ex=false;}}
		if((prex-x==0&&prey-y==0)){ex=false;}
	}
	arrow(int gx,int gy,map* amap,int gdir,int gw=20,int gh=20,int gVx=8,int gVy=0,int gmode=0):basicthing(gx,gy,gw,gh,gVx,gVy,amap)
	{ex=true;dir=gdir;if(dir==0||(dir==2&&pdir==0)){Vx=-gVx;}if(dir==1||(dir==2&&pdir==1)){Vx=gVx;}mode=gmode;now=0;prex=prey=0;}

	bool ifboom(float gx,float gy, float gw,float gh)
	{
		if(gy+gh<y||gy>y+h||gx>x+h||gx+gw<x)
		{
			return false;
		}
		else{return true;}
	}
};

class hero: public basicthing
{
private:
	DWORD  tPre,tNow;
	bool  adown,sdown,wdown,ddown;
	int still;
	bool sw_still[2];
	void  ValAll()
	{
//////////////////////////////////////////////分身逻辑////////////////////////////////////////////////////////
		if(dbling&&(x-js.x>150||x-js.x<-150||y-js.y>150||y-js.y<-150)){if(!backing){back();}}
		if(backing)
		{
			float lv=20;float lall=sqrt(xsback*xsback+ysback*ysback);
			if(x-js.x<(lv*xsback/lall)&&x-js.x>-(lv*xsback/lall)){}else if(x>js.x){x-=(lv*xsback/lall);}else{x+=(lv*xsback/lall);}
			if(y-js.y<(lv*ysback/lall)&&y-js.y>-(lv*ysback/lall)){}else if(y>js.y){y-=(lv*ysback/lall);}else{y+=(lv*ysback/lall);}
			if(x-js.x<=(lv*xsback/lall)&&x-js.x>=-(lv*xsback/lall)&&y-js.y<=(lv*ysback/lall)&&y-js.y>=-(lv*ysback/lall))
			{
				x=js.x,y=js.y,w=js.w,h=js.h;fuel=js.fuel,hp=js.hp;
				OnGround=js.OnGround;
				backing=false;sw_move=true;dbling=false;
			}
			return;
		}
//////////////////////////////////////////////落地逻辑///////////////////////////////////////////////////////////////
		if(mapon->CrashJud(x,y+1,w,h))
		{
			if(Vy>0)
			{
				if(Vy>10){effect::call(x,y+h*3/4,w,20,PIC_EFF1,40,Vx);effect::call(x+5,y+h*3/4-5,w,20,PIC_EFF1,40,Vx);effect::call(x-5,y+h*3/4-5,w,20,PIC_EFF1,40,Vx);}
				SodEdit::GetInstance()->Sod[SOD_FALL]->SetVolume(Vy/50.00);SodEdit::GetInstance()->Play(SOD_FALL,0);Vy=0;
			}
			still=10;OnGround=true;
			if(nipped){downhp(0,-1);}
			if(dead()){now=0;return;}
		}
		else{if(still<=1){OnGround=false;}}
		if(still>0){still--;}		if(OnGround){djump=true;}
///////////////////////////////////////////飞行逻辑//////////////////////////////////////////////////////////////////////////
		if(mapon->CrashJud(x,y-1,w,h))
		{
			if(!fly&&Vy<0)
			{Vy=0.5;effect::call(x,y-10,w,20,PIC_EFF1);}
		}
		if(fly&&fuel&&!OnGround){fuel-=w/100.00;if(1){effect::call(x+w/4,y+h,h/4,h/4,PIC_EFF1);}}
		else if(fuel<10&&sw_fly)	 {fuel+=0.03;}
		if(fuel<=0)	 {fly=false;fuel=0;}
		if(fuel>10)	 {fuel=10;}
		if(fly)
		{
			Vy-=wa;if(wa>0&&Vy<-5){wa-=0.2;if(wa<0){wa=0;}}
			if(Vy>-5){wa=1;}
		}
		else
		{
			if(allow[1]||(still<=0&&!sw_still[1])){if(Vy<15){Vy+=0.5;}}
			else if(still<0&&!sw_still[0])	{if(Vy>0){Vy=0;}}
		}if(!sw_fly){fly=false;}
/////////////////////////////////////////////方向逻辑///////////////////////////////////////////////////////////
		if(dir!=2){pdir=dir;}if(Vx>0){dir=0;}if(Vx<0){dir=1;}if(Vx==0){dir=2;}
		if(dir!=pdir&&dir!=2){now=0;}
		if(dir==2&&Vy==0&&!stop){stop=true;now=0;}
		if((dir!=2||Vy!=0)&&stop){stop=false;now=0;}
	}

public:
	arrow *biu;
	struct jstate
	{
		float x,y,w,h,fuel,magic;
		int hp;
		bool OnGround;
	}js;
	bool		dbling,sw_dbl;
	float   fuel,magic,hp,xsback,ysback;
	bool   sw_fly,sw_jud,sw_move,fly,backing;
	bool   stop,djump,OnGround,die;
	bool   attack,sw_attack;int attackcount;
	bool   sw_ctrl,sw_size;
	int      wd,now,pdir,dir,mode;
	
	bool sw_djump;
	hero(int gx,int gy,int gw,int gh,map* amap,int gfuel,int gmagic,int ghp,bool canfly,int gmode=PIC_HRO_2):basicthing(gx,gy,gw,gh,0,0,amap)
	{
		sw_fly=false;sw_dbl=false;sw_size=false;sw_attack=false;
		fly=canfly;x=gx,y=gy,w=gw,h=gh;Vx=0;Vy=0;wa=0;djump=true;die=false;backing=false;
		pdir=dir=0;now=0;mapon=amap;tPre=tNow=0;still=10;sw_still[0]=false;sw_still[1]=true;sw_move=true;
		adown=sdown=wdown=ddown=false;OnGround=false;
		mode=gmode;stop=true;fuel=gfuel;hp=ghp,magic=gmagic;wd=0;
		dbling=false;sw_jud=true;attack=false;attackcount=0;biu=NULL;
		sw_djump=true;wa=1;sw_ctrl=true;dietime++;
	}
	~hero(){}

	void back()
	{
		sw_move=false;
		xsback=x-js.x,ysback=y-js.y;
		if(xsback<0){xsback=-xsback;}if(ysback<0){ysback=-ysback;}
		if(xsback==0&&ysback==0){sw_ctrl=true;sw_move=true;dbling=false;return;}
		backing=true;
		SodEdit::GetInstance()->Play(SOD_UNDBL,0);
	}
	bool  downhp(int reser=0,int num=1)
	{	
		if(dbling)
		{
			if(!backing){back();}
			return false;
		}
		if(num==-1){num=hp;}
		if(wd){return false;}wd=50;hp-=num;
		if(reser)reser=reser-x;
		if(hp<=0){now=1;return true;}
		if(reser==0)
		{
			if(dir==0){if(allow[2])x-=w/2;}if(dir==1){if(allow[3])x+=w/2;}
			if(dir==2){if(pdir==0){if(allow[2])x-=w/2;}if(pdir==1){if(allow[3])x+=w/2;}}
		}
		else
		{
			if(reser<0){if(allow[3])x+=w/2;}if(reser>0){if(allow[2])x-=w/2;}
		}
		return true;
	}
	bool  dead()
	{
		if(mapon){if(hp<=0){return true;}}
		return false;
	}
	void  stand()
	{wdown=sdown=adown=ddown=false;Vx=Vy=0;fly=false;}

	void	 virtual Show(float cx,float cy,float cw,float ch)
	{
		float yfwyw=56,yfwyh=76;float hjj=10,ljj=2;float cjj=(yfwyw-ljj*2-25)/2;
		if(dbling){PicEdit::GetInstance()->Blt(SQ_WHITE,(js.x+js.w/2-cx-150)*core_w/cw,(js.y+js.h/2-cy-150)*core_h/ch,300*core_w/cw,300*core_h/ch,0,0,0,0,0.3);}
		if(biu&&biu->ex)
		{biu->Show(cx,cy,cw,ch);}
		else if(biu)
		{effect::call(biu->x,biu->y,biu->w,biu->h,PIC_EFF3);delete biu; biu=NULL;}

		if(dead())
		{
			if(Player->dbling)
			{
				sw_jud=true;fly=false;
				return;
			}
			delete biu; biu=NULL;
			if(!die){effect::call(x,y,w+cjj*w*2/(yfwyw-2*ljj-2*cjj),h+hjj*h/yfwyh,PIC_EFF3);die=true;}
			return;
		}

		if(wd>0){wd--;}
		if(wd<0){wd=0;}
		if(wd>0&&wd%7>=3){if(attack){attackcount++;}goto bq_jud;}
		else
		{			
			float jw=w,jh=h;float jx=x,jy=y;
			float jjw=js.w,jjh=js.h;float jjx=js.x,jjy=js.y;

			x-=cjj*w/(yfwyw-2*ljj-2*cjj);
			w=w+cjj*w*2/(yfwyw-2*ljj-2*cjj);
			h=h+hjj*h/yfwyh;
			
			js.x-=cjj*js.w/(yfwyw-2*ljj-2*cjj);
			js.w=js.w+cjj*js.w*2/(yfwyw-2*ljj-2*cjj);
			js.h=js.h+hjj*js.h/yfwyh;

			x*=core_w/cw;w*=core_w/cw;js.x*=core_w/cw;js.w*=core_w/cw;float wx=cx*core_w/cw;
			y*=core_h/ch;h*=core_h/ch;js.y*=core_h/ch;js.h*=core_h/ch;float wy=cy*core_h/ch;
			if(attack)
			{
				if(dir==1||(dir==2&&pdir==1))
				{
					if(attackcount<3){PicEdit::GetInstance()->BBlt(mode,x-wx,y-wy,w,h,(yfwyw)*5+ljj,(yfwyh),yfwyw,yfwyh);if(dbling){PicEdit::GetInstance()->BBlt(mode+1,js.x-wx,js.y-wy,js.w,js.h,(yfwyw)*5+ljj,(yfwyh),yfwyw,yfwyh);}}
					else if(attackcount<6){PicEdit::GetInstance()->BBlt(mode,x-wx,y-wy,w,h,(yfwyw)*6+ljj,(yfwyh),yfwyw,yfwyh);if(dbling){PicEdit::GetInstance()->BBlt(mode+1,js.x-wx,js.y-wy,js.w,js.h,(yfwyw)*6+ljj,(yfwyh),yfwyw,yfwyh);}}
					else if(attackcount<10){PicEdit::GetInstance()->BBlt(mode,x-wx,y-wy,w,h,(yfwyw)*7+ljj,(yfwyh),yfwyw,yfwyh);if(dbling){PicEdit::GetInstance()->BBlt(mode+1,js.x-wx,js.y-wy,js.w,js.h,(yfwyw)*7+ljj,(yfwyh),yfwyw,yfwyh);}}
					else if(attackcount<14){PicEdit::GetInstance()->BBlt(mode,x-wx,y-wy,w,h,(yfwyw)*8+ljj,(yfwyh),yfwyw,yfwyh);if(dbling){PicEdit::GetInstance()->BBlt(mode+1,js.x-wx,js.y-wy,js.w,js.h,(yfwyw)*8+ljj,(yfwyh),yfwyw,yfwyh);}}
					else if(attackcount<17){PicEdit::GetInstance()->BBlt(mode,x-wx,y-wy,w,h,(yfwyw)*9+ljj,(yfwyh),yfwyw,yfwyh);if(dbling){PicEdit::GetInstance()->BBlt(mode+1,js.x-wx,js.y-wy,js.w,js.h,(yfwyw)*9+ljj,(yfwyh),yfwyw,yfwyh);}}
					else if(attackcount<20){PicEdit::GetInstance()->BBlt(mode,x-wx,y-wy,w,h,(yfwyw)*10+ljj,(yfwyh),yfwyw,yfwyh);if(dbling){PicEdit::GetInstance()->BBlt(mode+1,js.x-wx,js.y-wy,js.w,js.h,(yfwyw)*10+ljj,(yfwyh),yfwyw,yfwyh);}}
				}
				if(dir==0||(dir==2&&pdir==0))
				{
					if(attackcount<3){PicEdit::GetInstance()->BBlt(mode,x-wx+w,y-wy,-w,h,(yfwyw)*5+ljj,(yfwyh),yfwyw,yfwyh);if(dbling){PicEdit::GetInstance()->BBlt(mode+1,js.x-wx+js.w,js.y-wy,-js.w,js.h,(yfwyw)*5+ljj,(yfwyh),yfwyw,yfwyh);}}
					else if(attackcount<6){PicEdit::GetInstance()->BBlt(mode,x-wx+w,y-wy,-w,h,(yfwyw)*6+ljj,(yfwyh),yfwyw,yfwyh);if(dbling){PicEdit::GetInstance()->BBlt(mode+1,js.x-wx+js.w,js.y-wy,-js.w,js.h,(yfwyw)*6+ljj,(yfwyh),yfwyw,yfwyh);}}
					else if(attackcount<10){PicEdit::GetInstance()->BBlt(mode,x-wx+w,y-wy,-w,h,(yfwyw)*7+ljj,(yfwyh),yfwyw,yfwyh);if(dbling){PicEdit::GetInstance()->BBlt(mode+1,js.x-wx+js.w,js.y-wy,-js.w,js.h,(yfwyw)*7+ljj,(yfwyh),yfwyw,yfwyh);}}
					else if(attackcount<14){PicEdit::GetInstance()->BBlt(mode,x-wx+w,y-wy,-w,h,(yfwyw)*8+ljj,(yfwyh),yfwyw,yfwyh);if(dbling){PicEdit::GetInstance()->BBlt(mode+1,js.x-wx+js.w,js.y-wy,-js.w,js.h,(yfwyw)*8+ljj,(yfwyh),yfwyw,yfwyh);}}
					else if(attackcount<17){PicEdit::GetInstance()->BBlt(mode,x-wx+w,y-wy,-w,h,(yfwyw)*9+ljj,(yfwyh),yfwyw,yfwyh);if(dbling){PicEdit::GetInstance()->BBlt(mode+1,js.x-wx+js.w,js.y-wy,-js.w,js.h,(yfwyw)*9+ljj,(yfwyh),yfwyw,yfwyh);}}
					else if(attackcount<20){PicEdit::GetInstance()->BBlt(mode,x-wx+w,y-wy,-w,h,(yfwyw)*10+ljj,(yfwyh),yfwyw,yfwyh);if(dbling){PicEdit::GetInstance()->BBlt(mode+1,js.x-wx+js.w,js.y-wy,-js.w,js.h,(yfwyw)*10+ljj,(yfwyh),yfwyw,yfwyh);}}
				}
				attackcount++;if(attackcount>=20){attack=false;now=0;attackcount=0;}
				w=jw;h=jh;x=jx;y=jy;
				js.w=jjw;js.h=jjh;js.x=jjx;js.y=jjy;
				goto bq_jud;
			}

			if(OnGround)
			{
				if(dir==1)
				{
					if(now<10)
					{PicEdit::GetInstance()->BBlt(mode,x-wx,y-wy,w,h,(yfwyw)+ljj,0,yfwyw,yfwyh);if(dbling){PicEdit::GetInstance()->BBlt(mode+1,js.x-wx,js.y-wy,js.w,js.h,(yfwyw)+ljj,0,yfwyw,yfwyh);}}
					else if(now<20)
					{PicEdit::GetInstance()->BBlt(mode,x-wx,y-wy,w,h,(yfwyw)*2+ljj,0,yfwyw,yfwyh);if(dbling){PicEdit::GetInstance()->BBlt(mode+1,js.x-wx,js.y-wy,js.w,js.h,(yfwyw)*2+ljj,0,yfwyw,yfwyh);}}
					else if(now<30)
					{PicEdit::GetInstance()->BBlt(mode,x-wx,y-wy,w,h,(yfwyw)*3+ljj,0,yfwyw,yfwyh);if(dbling){PicEdit::GetInstance()->BBlt(mode+1,js.x-wx,js.y-wy,js.w,js.h,(yfwyw)*3+ljj,0,yfwyw,yfwyh);}}
					else if(now<40)
					{PicEdit::GetInstance()->BBlt(mode,x-wx,y-wy,w,h,0+ljj,0,yfwyw,yfwyh);if(dbling){PicEdit::GetInstance()->BBlt(mode+1,js.x-wx,js.y-wy,js.w,js.h,0+ljj,0,yfwyw,yfwyh);}}
					if(dir!=2){now+=1;}if(now>=40){now=0;}
				}
				if(dir==0)//x加w w变负
				{
					if(now<10)
					{PicEdit::GetInstance()->BBlt(mode,x-wx+w,y-wy,-w,h,(yfwyw)+ljj,0,yfwyw,yfwyh);if(dbling){PicEdit::GetInstance()->BBlt(mode+1,js.x-wx+js.w,js.y-wy,-js.w,js.h,(yfwyw)+ljj,0,yfwyw,yfwyh);}}
					else if(now<20)
					{PicEdit::GetInstance()->BBlt(mode,x-wx+w,y-wy,-w,h,(yfwyw)*2+ljj,0,yfwyw,yfwyh);if(dbling){PicEdit::GetInstance()->BBlt(mode+1,js.x-wx+js.w,js.y-wy,-js.w,js.h,(yfwyw)*2+ljj,0,yfwyw,yfwyh);}}
					else if(now<30)
					{PicEdit::GetInstance()->BBlt(mode,x-wx+w,y-wy,-w,h,(yfwyw)*3+ljj,0,yfwyw,yfwyh);if(dbling){PicEdit::GetInstance()->BBlt(mode+1,js.x-wx+js.w,js.y-wy,-js.w,js.h,(yfwyw)*3+ljj,0,yfwyw,yfwyh);}}
					else if(now<40)
					{PicEdit::GetInstance()->BBlt(mode,x-wx+w,y-wy,-w,h,0+ljj,0,yfwyw,yfwyh);if(dbling){PicEdit::GetInstance()->BBlt(mode+1,js.x-wx+js.w,js.y-wy,-js.w,js.h,0+ljj,0,yfwyw,yfwyh);}}
					if(dir!=2){now+=1;}if(now>=40){now=0;}
				}
				if(dir==2)
				{
					if(pdir==0)
					{
						if(now>192)
						{PicEdit::GetInstance()->BBlt(mode,x-wx+w,y-wy,-w,h,(yfwyw)*3+ljj,(yfwyh)*1,yfwyw,yfwyh);if(dbling){PicEdit::GetInstance()->BBlt(mode+1,js.x-wx+js.w,js.y-wy,-js.w,js.h,(yfwyw)*3+ljj,(yfwyh)*1,yfwyw,yfwyh);}}
						else if(now>184)
						{PicEdit::GetInstance()->BBlt(mode,x-wx+w,y-wy,-w,h,(yfwyw)*3+ljj,(yfwyh)*2,yfwyw,yfwyh);if(dbling){PicEdit::GetInstance()->BBlt(mode+1,js.x-wx+js.w,js.y-wy,-js.w,js.h,(yfwyw)*3+ljj,(yfwyh)*2,yfwyw,yfwyh);}}
						else if(now>176)
						{PicEdit::GetInstance()->BBlt(mode,x-wx+w,y-wy,-w,h,(yfwyw)*3+ljj,(yfwyh)*1,yfwyw,yfwyh);if(dbling){PicEdit::GetInstance()->BBlt(mode+1,js.x-wx+js.w,js.y-wy,-js.w,js.h,(yfwyw)*3+ljj,(yfwyh)*1,yfwyw,yfwyh);}}
						else
						{PicEdit::GetInstance()->BBlt(mode,x-wx+w,y-wy,-w,h,(yfwyw)*9+ljj,0,yfwyw,yfwyh);if(dbling){PicEdit::GetInstance()->BBlt(mode+1,js.x-wx+js.w,js.y-wy,-js.w,js.h,(yfwyw)*9+ljj,0,yfwyw,yfwyh);}}
					}
					if(pdir==1)
					{
						if(now>192)
						{PicEdit::GetInstance()->BBlt(mode,x-wx,y-wy,w,h,(yfwyw)*3+ljj,(yfwyh)*1,yfwyw,yfwyh);if(dbling){PicEdit::GetInstance()->BBlt(mode+1,js.x-wx,js.y-wy,js.w,js.h,(yfwyw)*3+ljj,(yfwyh)*1,yfwyw,yfwyh);}}
						else if(now>184)
						{PicEdit::GetInstance()->BBlt(mode,x-wx,y-wy,w,h,(yfwyw)*3+ljj,(yfwyh)*2,yfwyw,yfwyh);if(dbling){PicEdit::GetInstance()->BBlt(mode+1,js.x-wx,js.y-wy,js.w,js.h,(yfwyw)*3+ljj,(yfwyh)*2,yfwyw,yfwyh);}}
						else if(now>176)
						{PicEdit::GetInstance()->BBlt(mode,x-wx,y-wy,w,h,(yfwyw)*3+ljj,(yfwyh)*1,yfwyw,yfwyh);if(dbling){PicEdit::GetInstance()->BBlt(mode+1,js.x-wx,js.y-wy,js.w,js.h,(yfwyw)*3+ljj,(yfwyh)*1,yfwyw,yfwyh);}}
						else		
						{PicEdit::GetInstance()->BBlt(mode,x-wx,y-wy,w,h,(yfwyw)*9+ljj,0,yfwyw,yfwyh);if(dbling){PicEdit::GetInstance()->BBlt(mode+1,js.x-wx,js.y-wy,js.w,js.h,(yfwyw)*9+ljj,0,yfwyw,yfwyh);}}
					}
					if(now>=200){now=0;}now++;
				}
			}
			if(!OnGround)
			{
				if(fly)
				{
					if(dir==1||(pdir==1&&dir==2))
					{
						if(now<10)
						{PicEdit::GetInstance()->BBlt(mode,x-wx,y-wy,w,h,(yfwyw)+ljj,(yfwyh),yfwyw,yfwyh);if(dbling){PicEdit::GetInstance()->BBlt(mode+1,js.x-wx,js.y-wy,js.w,js.h,(yfwyw)+ljj,(yfwyh),yfwyw,yfwyh);}}
						else if(now<20)
						{PicEdit::GetInstance()->BBlt(mode,x-wx,y-wy,w,h,(yfwyw)*2+ljj,(yfwyh),yfwyw,yfwyh);if(dbling){PicEdit::GetInstance()->BBlt(mode+1,js.x-wx,js.y-wy,js.w,js.h,(yfwyw)*2+ljj,(yfwyh),yfwyw,yfwyh);}}
						
						now+=1;if(now>=20){now=0;}
					}
					if(dir==0||(pdir==0&&dir==2))
					{	
						if(now<10)
						{PicEdit::GetInstance()->BBlt(mode,x-wx+w,y-wy,-w,h,(yfwyw)+ljj,(yfwyh),yfwyw,yfwyh);if(dbling){PicEdit::GetInstance()->BBlt(mode+1,js.x-wx+js.w,js.y-wy,-js.w,js.h,(yfwyw)+ljj,(yfwyh),yfwyw,yfwyh);}}
						else if(now<20)
						{PicEdit::GetInstance()->BBlt(mode,x-wx+w,y-wy,-w,h,(yfwyw)*2+ljj,(yfwyh),yfwyw,yfwyh);if(dbling){PicEdit::GetInstance()->BBlt(mode+1,js.x-wx+js.w,js.y-wy,-js.w,js.h,(yfwyw)*2+ljj,(yfwyh),yfwyw,yfwyh);}}
					
						now+=1;if(now>=20){now=0;}
					}
				}
				else
				{
					if(dir==1||(pdir==1&&dir==2))
					{
						if(now<5)
						{PicEdit::GetInstance()->BBlt(mode,x-wx,y-wy,w,h,(yfwyw)*0+ljj,(yfwyh)*2,yfwyw,yfwyh);if(dbling){PicEdit::GetInstance()->BBlt(mode+1,js.x-wx,js.y-wy,js.w,js.h,(yfwyw)*0+ljj,(yfwyh)*2,yfwyw,yfwyh);}}
						else if(now<10)
						{PicEdit::GetInstance()->BBlt(mode,x-wx,y-wy,w,h,(yfwyw)*1+ljj,(yfwyh)*2,yfwyw,yfwyh);if(dbling){PicEdit::GetInstance()->BBlt(mode+1,js.x-wx,js.y-wy,js.w,js.h,(yfwyw)*1+ljj,(yfwyh)*2,yfwyw,yfwyh);}}
						else 
						{PicEdit::GetInstance()->BBlt(mode,x-wx,y-wy,w,h,(yfwyw)*2+ljj,(yfwyh)*2,yfwyw,yfwyh);if(dbling){PicEdit::GetInstance()->BBlt(mode+1,js.x-wx,js.y-wy,js.w,js.h,(yfwyw)*2+ljj,(yfwyh)*2,yfwyw,yfwyh);}}
						
						now+=1;if(now>=10){now=10;}
					}
					if(dir==0||(pdir==0&&dir==2))
					{
						if(now<5)
						{PicEdit::GetInstance()->BBlt(mode,x-wx+w,y-wy,-w,h,(yfwyw)*0+ljj,(yfwyh)*2,yfwyw,yfwyh);if(dbling){PicEdit::GetInstance()->BBlt(mode+1,js.x-wx+js.w,js.y-wy,-js.w,js.h,(yfwyw)*0+ljj,(yfwyh)*2,yfwyw,yfwyh);}}
						else if(now<10)
						{PicEdit::GetInstance()->BBlt(mode,x-wx+w,y-wy,-w,h,(yfwyw)*1+ljj,(yfwyh)*2,yfwyw,yfwyh);if(dbling){PicEdit::GetInstance()->BBlt(mode+1,js.x-wx+js.w,js.y-wy,-js.w,js.h,(yfwyw)*1+ljj,(yfwyh)*2,yfwyw,yfwyh);}}
						else
						{PicEdit::GetInstance()->BBlt(mode,x-wx+w,y-wy,-w,h,(yfwyw)*2+ljj,(yfwyh)*2,yfwyw,yfwyh);if(dbling){PicEdit::GetInstance()->BBlt(mode+1,js.x-wx+js.w,js.y-wy,-js.w,js.h,(yfwyw)*2+ljj,(yfwyh)*2,yfwyw,yfwyh);}}
						
						now+=1;if(now>=10){now=10;}
					}
				}
			}
			w=jw;h=jh;x=jx;y=jy;
			js.w=jjw;js.h=jjh;js.x=jjx;js.y=jjy;
		}
		if(mapon==NULL){return;}
bq_jud:		
		if(sw_jud){Jud();}
	}
	void  ShowState()
	{ 
		for(int i=0;i<hp;i++){PicEdit::GetInstance()->Blt(PIC_HP,i*35,0,32,32,0,0,32,32);}
		if(sw_fly)
		{
			PicEdit::GetInstance()->Blt(PIC_EMFUEL,0,40,223,32);
			PicEdit::GetInstance()->Blt(PIC_FUEL,20,40,185*(fuel/10.000),30,0,0,0,0);
		}
		wchar_t wmm[200];
		swprintf(wmm,sizeof(wmm),L"死亡次数: %d",dietime);
		PicEdit::GetInstance()->TextL(0,70,wmm,20,FT_WRYH,COLOR(255,255,255,1));
	/*	swprintf(wmm,sizeof(wmm),L"%f  %f",Vx,Vy);
		PicEdit::GetInstance()->TextL(0,200,wmm,20,FT_WRYH,COLOR(255,255,255,1));
		swprintf(wmm,sizeof(wmm),L"%d  %d",now,mapon->CrashJud(x,y,w,h));
		PicEdit::GetInstance()->TextL(0,100,wmm,20,FT_WRYH,COLOR(255,255,255,1));
		swprintf(wmm,sizeof(wmm),L"%f  %f",x,y);
		PicEdit::GetInstance()->TextL(0,120,wmm,20,FT_WRYH,COLOR(255,255,255,1));
		swprintf(wmm,sizeof(wmm),L"%d  %d %d %d",on[0],on[1],on[2],on[3]);
		PicEdit::GetInstance()->TextL(0,150,wmm,20,FT_WRYH,COLOR(255,255,255,1));*/
	}

	void   Jud()
	{
		if(y>mapon->h&&sw_move){downhp(0,-1);}int px=x,py=y;
		if(sw_move)
		{
			Move();
			//if(on[1]>0&&mapon->con[on[1]-1]->mode==MAP_21){downhp();}
		}
		if(x==10000||y==10000){x=px,y=py;}

/*		if(mapon->con[685+addnum]->y+mapon->con[685+addnum]->h-y>-100)
		{if(mapon->con[685+addnum]->tr>0){mapon->con[685+addnum]->tr-=0.1;}}
		else
		{if(mapon->con[685+addnum]->tr<1){mapon->con[685+addnum]->tr+=0.1;}}*/
//		if(!(x+w<1300||x+w>1700||y<550||y>990)){downhp(0,-1);}

		ValAll();
	}
	bool  SJud()
	{
		return ((allow[0]||allow[1])&&(allow[2]||allow[3]));
	}
	bool  NoAct()
	{
		return !(wdown||sdown||adown||ddown);
	}

	void Res(UINT mes,LPARAM lp,WPARAM wp)
	{
		if(!sw_ctrl){return;}
		int lv=4;float lup=10+w/15.00-1;
		float ly=y,lx=x,lw=w,lh=h;
		switch(mes)
		{
			case WM_KEYDOWN:
				switch(wp)
				{
				case 0x41: Vx=-lv;adown=true;break;//a
				case 0x44: Vx=lv;ddown=true;break;//d
				case 0x53: sdown=true;break;//s
				case 0x57: //w
					wdown=true;
					if(sw_fly&&fuel){fly=true;now=0;}
					else if(sw_fly){if(!attack)SodEdit::GetInstance()->Play(SOD_WRONG,0);}
					break;
				case 0x4A://j
					if(sw_attack&&!attack&&!biu)
					{
						fly=false;attack=true;now=0;
						biu=new arrow(x,y,mapon,dir);SodEdit::GetInstance()->Play(SOD_BIU,0);
						if(dir==0||(dir==2&&pdir==0)){biu=new arrow(x+w/2,y+h/4,mapon,1,h/2,h/2,8,0,1);}
						if(dir==1||(dir==2&&pdir==1)){biu=new arrow(x+w/2,y+h/4,mapon,0,h/2,h/2,8,0,1);}
					}
					break;
				case 0x4B: //k
					if(!fly&&((OnGround&&Vy>=0)||(djump&&sw_djump))){Vy=-lup;now=0;if(allow[1])djump=false;}
					break;
				case 0x4E://n
					if(!sw_size){break;}
					if(h>=90||w>=100){SodEdit::GetInstance()->Play(SOD_WRONG,0);break;}
					if(allow[3]){if(allow[1]){h+=(h/(w++));}else if(allow[0]){h+=(h/(w++));y-=(h/w);}else{SodEdit::GetInstance()->Play(SOD_WRONG,0);}}
					else if(allow[2]){if(allow[1]){h+=(h/(w++));x--;}else if(allow[0]){h+=(h/(w++));y-=(h/w);x--;}else{SodEdit::GetInstance()->Play(SOD_WRONG,0);}}
					else {SodEdit::GetInstance()->Play(SOD_WRONG,0);}ValAllow();
					if(!SJud()){ y=ly,x=lx,w=lw,h=lh;SodEdit::GetInstance()->Play(SOD_WRONG,0);}
					break;
				case 0x4D://m
					if(!sw_size){break;}
					if(w<15){SodEdit::GetInstance()->Play(SOD_WRONG,0);return;}
					h-=(h/(w--));Player->y++;
					break;
				}
				break;
			case WM_KEYUP:
				switch(wp)
				{
				case 0x41: adown=false;Vx=0;if(ddown){Vx=lv;}break;
				case 0x44: ddown=false;Vx=0;if(adown){Vx=-lv;}break;
				case 0x57: wdown=false;fly=false;now=0;break;
				case 0x4C://l
					if(sw_dbl&&!dbling&&!backing)
					{dbling=true;js.x=x,js.y=y,js.w=w,js.h=h;js.fuel=fuel,js.hp=hp;	js.OnGround=OnGround;SodEdit::GetInstance()->Play(SOD_DBL,0);}
					else if(sw_dbl) {if(!backing){back();}}
					break;
				}
				break;
		}
	}
}
*Player,*Eny,*hand;



#endif