#include"pic.h"
#include"sound.h"
#include"define.h"
#include"cursor.h"
#include"lizi.h"
#include"change.h"
#include"map.h"
#include"hero.h"
#include<windows.h>
#include<time.h>
#ifndef THINGS_H
#define THINGS_H


bool jud[10]={false};bool   loading=true;
enum Tag{GUI,Q,W,E,R,T,Y,U,I,O,P,MAPEDIT,OVER,SWITCH,WAIT,WIN};
Tag TGame=GUI;
Tag PT=TGame;

class GGP//¹«¸æÅÆ
{
public:
	int ID;
	int mode;
	int ran;
	bool played;
	int x,y,w,h;
	LPCWSTR con;
	bool looking;float ltr;
	void Show(float cx,float cy,float cw,float ch)
	{
		if(mode==1)PicEdit::GetInstance()->Blt(PIC_GGP,(x-cx)*core_w/cw,(y-cy)*core_h/ch,w*core_w/cw,h*core_h/ch,0,0,250,240);
		if(mode==2)PicEdit::GetInstance()->Blt(PIC_GGP,(x-cx)*core_w/cw,(y-cy)*core_h/ch,w*core_w/cw,h*core_h/ch,0,0,250,240);
		if(ifnear(Player))
		{	 
			if(!played)SodEdit::GetInstance()->Play(SOD_GGPRMD,0);played=true;
			if(ltr<1){ltr+=0.02;}
			if(ID==3){Player->sw_djump=true;}
		}
		else{if(ltr>0){ltr-=0.02;}else{ltr=0;}}int lx=x-cx,ly=y-cy,lw=180,lh=500;
		if(lx>800-lw&&ltr==0){lw=-lw;lx=x-cx-100+w;}//if(ly>600-lh){lh=-lh;}
		lw=PicEdit::GetInstance()->TextS(lx*core_w/cw,ly*core_h/ch,lw,lh,con,20,FT_WRYH,COLOR(0,0,0,ltr),true);lh=lw%10000;;lw/=10000;
		PicEdit::GetInstance()->Blt(SQ_WHITE,lx*core_w/cw+w*core_w/cw,ly*core_h/ch,lw,lh,0,0,0,0,ltr);
		PicEdit::GetInstance()->TextS(lx*core_w/cw+w*core_w/cw,ly*core_h/ch,180,500,con,20,FT_WRYH,COLOR(0,0,0,ltr));
	}
	bool ifnear(hero *ahero)
	{
		for(int i=ahero->x;i<=ahero->x+ahero->w;i+=4){for(int j=ahero->y;j<=ahero->y+ahero->h;j+=4){if(ifnear(i,j)){return true;}}}
		ran=rand();played=false;
		return false;
	}
	bool ifnear(int rx,int ry)
	{
		return (rx>=x&&rx<=(x+w)&&y<=ry&&(y+h)>=ry);
	}
	void Res(UINT mes,LPARAM lp,WPARAM wp)
	{
		/*switch(mes)
		{
		case WM_KEYDOWN:
			if(looking){looking=false;}
			switch(wp)
			{
			case VK_SPACE:
				if(ifnear(Player)){looking=true;}
				break;
			}
			break;
		case WM_LBUTTONDOWN:
			if(looking){looking=false;}
			break;
		}*/
	}
	void ChangeCon(LPCWSTR gcon)
	{con=gcon;srand(static_cast<unsigned int>(time(0)));}
	GGP(int gID,int gx,int gy,LPCWSTR gcon,int gmode=1,int gw=40,int gh=40)
	{
		ID=gID;x=gx,y=gy;con=gcon;w=gw;h=gh;
		mode=gmode;looking=false;
		played=false;ltr=0.0f;
	}
	void  Clean(){delete this;}
};
class savepoint
{
public:
	int value,all;
	int x[10],y[10],w,h;
	int now[10],dir[10];
	map *mapon;

	bool in[10];

	savepoint(map *amap,int gw=50,int gh=50)
	{
		w=gw;h=gh;
		mapon=amap;value=0;all=0;
		for(int i=0;i<10;i++)
		{x[i]=-100,y[i]=-100;in[i]=false;now[i]=0;dir[i]=0;}
	}
	bool ifnear(hero *ahero,int gID)
	{
		if(ahero->y+ahero->h<y[gID]||ahero->y>y[gID]+h||ahero->x>x[gID]+w||ahero->x+ahero->w<x[gID]){return false;}
		return true;
	}
	void Show(float cx,float cy,float cw,float ch)
	{
		for(int i=1;i<=all;i++)
		{
			PicEdit::GetInstance()->Blt(PIC_SAVEPOINT+now[i]/10,(x[i]-cx)*core_w/cw,(y[i]-cy)*core_h/ch,w*core_w/cw,h*core_h/ch,0,0,150,50);
			if(value>=i){now[i]++;}if(now[i]>=89){now[i]=89;}
		}
		for(int i=1;i<=all;i++)
		{
			if(ifnear(Player,i))
			{
				if(!SodEdit::GetInstance()->IsPlaying(SOD_GO)&&!in[i]){SodEdit::GetInstance()->Play(SOD_GO,0);}
				in[i]=true;if(i>value){value=i;}
			}
			else{in[i]=false;}
		}
	}
	int    rex(){return x[value];}int   rey(){return y[value];}

	void CValue(int num){value=num;}
	void add(int gx,int gy){all++;x[all]=gx,y[all]=gy;}
};
class bigboom
{
public:
	int x,y,w,h;
	int shoot,list[10];
	int allow,dir,count;
	map *mapon;
	bool ex;
	arrow *hq[10];
	bool ifeat()
	{	
		if(Player->y+Player->h<y||Player->y>y+h||Player->x>x+w||Player->x+Player->w<x){return false;}
		return true;
	}
	void show(int cx,int cy,float cw,float ch)
	{
		if(!ex){return;}
		if(ifeat()){Player->downhp(x);}
		if(allow<=0&&shoot<10)
		{
			if(dir==0){hq[list[shoot]]=new arrow(x-20,y+4,mapon,dir);shoot++;}
			if(dir==1){hq[list[shoot]]=new arrow(x+w,y+4,mapon,dir);shoot++;}
			SodEdit::GetInstance()->Play(SOD_SHOOT,0);
			if(dir==1){effect::call(x+w,y,w,h*3/4,PIC_EFF2,40,0,0);}
			if(dir==0)
			{effect::call(x,y,-w,h*3/4,PIC_EFF2,40,0,0);}
		}
		for(int i=0;i<shoot;i++)
		{
			if(hq[list[i]]->ex){hq[list[i]]->Show(cx,cy,cw,ch);if(hq[list[i]]->ifboom(Player->x,Player->y,Player->w,Player->h)){if(Player->downhp(x)){hq[list[i]]->ex=false;}}}
			else{	effect::call(hq[list[i]]->x,hq[list[i]]->y,hq[list[i]]->w,hq[list[i]]->h,PIC_EFF3);delete hq[list[i]];int jl=list[i];for(int j=i;j<9;j++){list[j]=list[j+1];}list[9]=jl;shoot--;}
		}if(x-cx<-200||x-cx>cw+200){allow=1;return;}
		if(dir==0)PicEdit::GetInstance()->BBlt(PIC_DAPAO,(x-cx)*core_w/cw,(y-cy)*core_h/ch,w*core_w/cw,h*core_h/ch,2,5,45,42);
		if(dir==1)PicEdit::GetInstance()->BBlt(PIC_DAPAO,(x-cx+w)*core_w/cw,(y-cy)*core_h/ch,-w*core_w/cw,h*core_h/ch,2,5,45,42);
		if(Player->biu&&Player->biu->ex)
		{
			if(Player->biu->ifboom(x,y,w,h))
			{
				ex=false;Player->biu->ex=false;
				effect::call(x,y,w,h,PIC_EFF3);
			}
		}
		allow--;if(allow<0){allow=count;}
	}
	bigboom(int gx,int gy,int gdir,map* amap,int time=60,int gw=40,int gh=40)
	{
		mapon=amap;
		x=gx,y=gy,w=gw,h=gh;ex=true;shoot=0;count=allow=time;dir=gdir;
		for(int i=0;i<10;i++){list[i]=i;}
	}
	~bigboom(){for(int i=0;i<shoot;i++){delete hq[list[i]];}}
};

class trap
{
public:
	int x,y,w,h;
	int fx,fy,fw,fh;
	int dam;
	bool ex;int PicID;
	void Show(float cx,float cy,float cw,float ch)
	{
		if(!ex){return;}
		if(ifeat()){Player->downhp(0,dam);}
		if(PicID==-1){return;}
		int nnn=fw/w;
		for(int i=0;i<nnn;i++)
		{PicEdit::GetInstance()->Blt(PicID,(x-cx+i*w)*core_w/cw,(y-cy)*core_h/ch,w*core_w/cw,h*core_h/ch);}
		PicEdit::GetInstance()->Blt(PicID,(x-cx+nnn*w)*core_w/cw,(y-cy)*core_h/ch,(fw-w*nnn)*core_w/cw,h*core_h/ch);	
	}
	bool ifeat()
	{
		if(Player->y+Player->h<fy||Player->y>fy+fh||Player->x>fx+fw||Player->x+Player->w<fx){return false;}
		return true;
	}
	trap(int gx,int gy,int gw,int gh,int gPicID,int gfx=0,int gfy=0,int gfw=0,int gfh=0,int gdam=1)
	{
		x=gx,y=gy,w=gw,h=gh;ex=true;dam=gdam;
		fx=gfx,fy=gfy,fw=gfw,fh=gfh;
		PicID= gPicID;
	}
	~trap(){}
};


bool gameover()
{
	if(Player->dead())
	{
		if(TGame!=OVER){SodEdit::GetInstance()->Play(SOD_GAMEOVER,0);PT=TGame;TGame=OVER;}
		Player->stand();
		PicEdit::GetInstance()->TextL(300,200,L"GAME OVER",50,FT_WRYH,COLOR(255,200,0,1));
		PicEdit::GetInstance()->TextL(400,260,L"r¼üÖØÐÂ¿ªÊ¼",20,FT_WRYH,COLOR(0,0,0,1));
		for(int i=0;i<10;i++){jud[i]=false;}return true;
	}
	return false;
}
void All_Init(HWND hwnd)
{	
	ImmDisableIME(0);//ÆÁ±ÎÊäÈë·¨
	SodEdit::GetInstance()->Load("res/wrong.wav",SOD_WRONG);
	PicEdit::Init(hwnd);
	PicEdit::GetInstance()->Load(L"res/°´Å¥/1 (1).png",PIC_BTN_1_1);
	PicEdit::GetInstance()->Load(L"res/°´Å¥/1 (2).png",PIC_BTN_1_2);
	PicEdit::GetInstance()->Load(L"res/°´Å¥/1 (3).png",PIC_BTN_1_3);
	PicEdit::GetInstance()->Load(L"res/GUI/³ÝÂÖ/0.png",PIC_GUICL_1);
	PicEdit::GetInstance()->Load(L"res/GUI/³ÝÂÖ/1.png",PIC_GUICL_2);
	PicEdit::GetInstance()->Load(L"res/GUI/³ÝÂÖ/2.png",PIC_GUICL_3);
	PicEdit::GetInstance()->Load(L"res/GUI/³ÝÂÖ/3.png",PIC_GUICL_4);
	PicEdit::GetInstance()->Load(L"res/GUI/³ÝÂÖ/4.png",PIC_GUICL_5);
	PicEdit::GetInstance()->Load(L"res/GUI/³ÝÂÖ/5.png",PIC_GUICL_6);
	PicEdit::GetInstance()->Load(L"res/GUI/³ÝÂÖ/6.png",PIC_GUICL_7);
	PicEdit::GetInstance()->Load(L"res/GUI/³ÝÂÖ/7.png",PIC_GUICL_8);
	PicEdit::GetInstance()->Load(L"res/GUI/³ÝÂÖ/8.png",PIC_GUICL_9);
	PicEdit::GetInstance()->Load(L"res/°´Å¥/emfuel.png",PIC_EMFUEL);
	PicEdit::GetInstance()->Load(L"res/°´Å¥/fuel.png",PIC_FUEL);
	PicEdit::GetInstance()->Load(L"res/hero/hero (3).png",PIC_HRO_1,1);
	PicEdit::GetInstance()->Load(L"res/hero/hero(3).png",PIC_HRO_1+1,1);
	PicEdit::GetInstance()->Load(L"res/square/white.png",SQ_WHITE);
	PicEdit::GetInstance()->Load(L"res/square/red.png",SQ_RED);
	PicEdit::GetInstance()->Load(L"res/mg.png", PIC_MG, true);
	PicEdit::GetInstance()->Load(L"res/map/q/200.png",PIC_GGP,true);

	PicEdit::GetInstance()->Load(L"res/map/q/1.png",MAP_1);
	PicEdit::GetInstance()->Load(L"res/map/q/2.png",MAP_2);
	PicEdit::GetInstance()->Load(L"res/map/q/3.png",MAP_3);
	PicEdit::GetInstance()->Load(L"res/map/q/4.png",MAP_4);
	PicEdit::GetInstance()->Load(L"res/map/q/5.png",MAP_5);
	PicEdit::GetInstance()->Load(L"res/map/q/6.png",MAP_6);
	PicEdit::GetInstance()->Load(L"res/map/q/7.png",MAP_7);
	PicEdit::GetInstance()->Load(L"res/map/q/8.png",MAP_8);
	PicEdit::GetInstance()->Load(L"res/map/q/9.png",MAP_9);
	PicEdit::GetInstance()->Load(L"res/map/q/10.png",MAP_10);
	PicEdit::GetInstance()->Load(L"res/map/q/11.png",MAP_11);
	PicEdit::GetInstance()->Load(L"res/map/q/12.png",MAP_12);
	PicEdit::GetInstance()->Load(L"res/map/q/13.png",MAP_13);
	PicEdit::GetInstance()->Load(L"res/map/q/14.png",MAP_14);
	PicEdit::GetInstance()->Load(L"res/map/q/15.png",MAP_15);
	PicEdit::GetInstance()->Load(L"res/map/q/16.png",MAP_16);
	PicEdit::GetInstance()->Load(L"res/map/q/17.png",MAP_17);
	PicEdit::GetInstance()->Load(L"res/map/q/18.png",MAP_18);
	PicEdit::GetInstance()->Load(L"res/map/q/19.png",MAP_19);
	PicEdit::GetInstance()->Load(L"res/map/q/20.png",MAP_20);
	PicEdit::GetInstance()->Load(L"res/map/µØ´Ì.png",MAP_21);

	PicEdit::GetInstance()->Load(L"res/effect/dust.png",PIC_EFF1);

	SodEdit::GetInstance()->Load("res/over.wav",SOD_GAMEOVER);
	SodEdit::GetInstance()->Load("res/°´Å¥/GGPTG.wav",SOD_GGPRMD);SodEdit::GetInstance()->Sod[SOD_GGPRMD]->SetVolume(0.2);
	SodEdit::GetInstance()->Load("res/eff.wav",SOD_EFFECT);			SodEdit::GetInstance()->Sod[SOD_EFFECT]->SetVolume(0.5);
	SodEdit::GetInstance()->Load("res/¿ªÅÚ.wav",SOD_SHOOT);		SodEdit::GetInstance()->Sod[SOD_SHOOT]->SetVolume(0.05);
	SodEdit::GetInstance()->Load("res/go.wav",SOD_GO);					SodEdit::GetInstance()->Sod[SOD_GO]->SetVolume(0.2);
	SodEdit::GetInstance()->Load("res/fall.wav",SOD_FALL);				SodEdit::GetInstance()->Sod[SOD_FALL]->SetVolume(0.3);
	SodEdit::GetInstance()->Load("res/find.wav",SOD_DBL);				SodEdit::GetInstance()->Sod[SOD_DBL]->SetVolume(0.5);
	SodEdit::GetInstance()->Load("res/lose.wav",SOD_UNDBL);		SodEdit::GetInstance()->Sod[SOD_UNDBL]->SetVolume(0.5);
	SodEdit::GetInstance()->Load("res/biu.wav",SOD_BIU);				SodEdit::GetInstance()->Sod[SOD_BIU]->SetVolume(0.1);
	
	PicEdit::GetInstance()->Load(L"res/Á£×Ó/1.png",PIC_LZ1,true);
	PicEdit::GetInstance()->Load(L"res/Á£×Ó/2.png",PIC_LZ2,true);
	PicEdit::GetInstance()->Load(L"res/Á£×Ó/3.png",PIC_LZ3,true);
	PicEdit::GetInstance()->Load(L"res/Á£×Ó/4.png",PIC_LZ4,true);

	PicEdit::GetInstance()->Load(L"res/eat/savepoint (1).png",PIC_SAVEPOINT);
	PicEdit::GetInstance()->Load(L"res/eat/savepoint (2).png",PIC_SAVEPOINT+1);
	PicEdit::GetInstance()->Load(L"res/eat/savepoint (3).png",PIC_SAVEPOINT+2);
	PicEdit::GetInstance()->Load(L"res/eat/savepoint (4).png",PIC_SAVEPOINT+3);
	PicEdit::GetInstance()->Load(L"res/eat/savepoint (5).png",PIC_SAVEPOINT+4);
	PicEdit::GetInstance()->Load(L"res/eat/savepoint (6).png",PIC_SAVEPOINT+5);
	PicEdit::GetInstance()->Load(L"res/eat/savepoint (7).png",PIC_SAVEPOINT+6);
	PicEdit::GetInstance()->Load(L"res/eat/savepoint (8).png",PIC_SAVEPOINT+7);
	PicEdit::GetInstance()->Load(L"res/eat/savepoint (9).png",PIC_SAVEPOINT+8);
	
	PicEdit::GetInstance()->Load(L"res/°´Å¥/GPicEdit::GetInstance()QP.png",PIC_GGPRMD);
	PicEdit::GetInstance()->Load(L"res/map/q/200.png", PIC_GGPRMD);
	PicEdit::GetInstance()->Load(L"res/map/water.png",PIC_WATER);
	
	PicEdit::GetInstance()->Load(L"res/hero/hero (2).png",PIC_HRO_2,1);
	PicEdit::GetInstance()->Load(L"res/hero/hp.png",PIC_HP);

	PicEdit::GetInstance()->Load(L"res/eat/dapao.png",PIC_DAPAO,1);
	PicEdit::GetInstance()->Load(L"res/eat/smoke (1).png",PIC_EFF2,1);
	PicEdit::GetInstance()->Load(L"res/eat/smoke (2).png",PIC_EFF2+1,1);
	PicEdit::GetInstance()->Load(L"res/eat/smoke (3).png",PIC_EFF2+2,1);
	PicEdit::GetInstance()->Load(L"res/eat/smoke (4).png",PIC_EFF2+3,1);
	PicEdit::GetInstance()->Load(L"res/eat/smoke (5).png",PIC_EFF2+4,1);
	PicEdit::GetInstance()->Load(L"res/eat/smoke (6).png",PIC_EFF2+5,1);
	PicEdit::GetInstance()->Load(L"res/eat/smoke (7).png",PIC_EFF2+6,1);
	PicEdit::GetInstance()->Load(L"res/eat/smoke (8).png",PIC_EFF2+7,1);
	PicEdit::GetInstance()->Load(L"res/eat/smoke (9).png",PIC_EFF2+8,1);

	PicEdit::GetInstance()->Load(L"res/hero/boom (0).png",PIC_EFF3);
	PicEdit::GetInstance()->Load(L"res/hero/boom (1).png",PIC_EFF3+1);
	PicEdit::GetInstance()->Load(L"res/hero/boom (2).png",PIC_EFF3+2);
	PicEdit::GetInstance()->Load(L"res/hero/boom (3).png",PIC_EFF3+3);
	PicEdit::GetInstance()->Load(L"res/hero/boom (4).png",PIC_EFF3+4);
	PicEdit::GetInstance()->Load(L"res/hero/boom (5).png",PIC_EFF3+5);

	PicEdit::GetInstance()->Load(L"res/eat/10.png",PIC_HUOQIU);
	cursor();
}
void Loading(DWORD WINAPI init(LPVOID))
{
	loading=true;
	CreateThread(NULL, 0, init, 0, 0, 0);dietime=-2;
	float dir=0,val=0;
	int     clval=0;
	hand=new hero(600,500,30,76,NULL,10000,0,1,1,PIC_HRO_1);
	srand(static_cast<unsigned int>(time(0)));
	if(rand()%2){hand->OnGround=true;}else{hand->OnGround=false;}
	while(loading)
	{
		PicEdit::GetInstance()->Begin();
		hand->Show(0,0,core_w,core_h);
		PicEdit::GetInstance()->TextL(650,550,L"Linking...",20,FT_WRYH,COLOR(val,val,val,1));if(!dir){val+=0.02;}if(dir){val-=0.02;}
		PicEdit::GetInstance()->Blt(PIC_GUICL_1+clval,0,0,250,188,0,0,0,0);clval++;if(clval==9){clval=0;}
		if(val>1){val=1;dir=1;}if(val<0){val=0;dir=0;}
		PicEdit::GetInstance()->End();
	}
	delete hand;

}

#endif