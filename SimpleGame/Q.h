#include"things.h"
#include"camera.h"
#include"lizi.h"
#ifndef Q_H
#define Q_H
extern DWORD		    g_tPre,g_tNow;
/////////////////////////////////////////////////////////////////////
GGP *GG[10];
bigboom* dapao[20];
map *map_one;
savepoint *QSave;
lizi *lizi1;
/////////////////////////////////////////////////////////////////////
DWORD WINAPI else_QInit(LPVOID param)
{
	///////////////////////////////////////////////////////////////资源载入///////////////////////////////////////////////////////////////
	SodEdit::GetInstance()->Load("res/bg.ogg",SOD_ONEBG);
	PicEdit::GetInstance()->Load(L"res/map/q/bg.png",BG_1);
	PicEdit::GetInstance()->Load(L"res/map/q/bg1.png",BG_2);

	PicEdit::GetInstance()->Load(L"res/map/A.png",PIC_A);
	PicEdit::GetInstance()->Load(L"res/map/B.png",PIC_B);
	PicEdit::GetInstance()->Load(L"res/map/C.png",PIC_C);
	PicEdit::GetInstance()->Load(L"res/map/D.png",PIC_D);
///////////////////////////////////////////////////////对象创建///////////////////////////////////////////////////////////////////////////////////////
	GG[1]=new GGP(1,415,590,L"一段跳到最高点时再二段跳应该会跳的更高吧");
	GG[2]=new GGP(3,585,950,L"受伤后会有短暂的无敌时间");
	GG[3]=new GGP(4,255,465,L"有些地方会掉下去的");

	map_one=new map(1000,1000);map_one->Load("map_one.ini");
	map_one->AddBG(BG_1,1);map_one->AddBG(BG_2,8);
	map_one->AddSC(PIC_A,0,810,200,100);map_one->AddSC(PIC_C,700,790,200,100);map_one->AddSC(PIC_B,305,630,100,200);
	Player=new hero(10,850,18,47,map_one,0,1000,3,false,PIC_HRO_1);
	QSave=new savepoint(map_one,40,40);QSave->add(455,140);
	cam= new camera(map_one);cam->CSize(400,300);cam->SetCenter(Player->x+Player->w/2,Player->y+Player->h/2);
	GodMap=new EMap(1,map_one,"map_one.ini");
	dapao[0]=new bigboom(860,950,0,map_one);
	lizi1=new lizi(map_one,PIC_LZ1,LIZE_DOWN);
/////////////////////////////////////////参数初始化/////////////////////////////////////////////////////
	loading=false;
	SodEdit::GetInstance()->Play(2,1);//bgm
	return 0;
}

void Q_Jud()
{

	if((Player->x>200||Player->y<800)&&cam->w<800)
	{cam->faraway(2);}

	if(Player->x>=map_one->vright()-Player->w)
	{
		Q_Clean();
		Loading(else_WInit);
		PT=TGame;TGame=W;
	}
	if(gameover()){}
}
void Q_Paint()
{
	map_one->ShowBG(cam->x,cam->y,cam->w,cam->h);
	dapao[0]->show(cam->x,cam->y,cam->w,cam->h);

	QSave->Show(cam->x,cam->y,cam->w,cam->h);
	
	map_one->ShowThings(cam->x,cam->y,cam->w,cam->h);
	Player->Show(cam->x,cam->y,cam->w,cam->h);
	cam->ShowEff();
	cam->Show();
	GG[1]->Show(cam->x,cam->y,cam->w,cam->h);
	GG[2]->Show(cam->x,cam->y,cam->w,cam->h);
	GG[3]->Show(cam->x,cam->y,cam->w,cam->h);
	lizi1->Show(cam->x,cam->y,cam->w,cam->h);
	cam->FrontShow();

	Q_Jud();
}
void Q_Clean()
{
	PicEdit::GetInstance()->Delete(PIC_A);	PicEdit::GetInstance()->Delete(PIC_B);
	PicEdit::GetInstance()->Delete(PIC_C);	PicEdit::GetInstance()->Delete(PIC_D);
	PicEdit::GetInstance()->Delete(BG_1);	PicEdit::GetInstance()->Delete(BG_2);
	SodEdit::GetInstance()->Delete(SOD_ONEBG);
///////////////////////////////////////////////////////对象清理///////////////////////////////////////////////////////////////////////////////////////
	delete GG[1];delete GG[2];delete GG[3];
	delete map_one;	delete Player;
	delete QSave;delete cam;	delete GodMap;
	delete dapao[0];delete lizi1;
}
void Q_RS()
{
	delete Player;delete dapao[0];
	dapao[0]=new bigboom(860,950,0,map_one);
	
	if(QSave->value==0){Player=new hero(10,850,18,47,map_one,0,1000,3,false,PIC_HRO_1);}
	else	{Player=new hero(QSave->rex(),QSave->rey(),18,47,map_one,0,1000,3,false,PIC_HRO_1);}
	
	cam->SetCenter(Player->x+Player->w/2,Player->y+Player->h/2);
	SodEdit::GetInstance()->Play(2,1);
}
void Q_Res(UINT mes,LPARAM lp,WPARAM wp)
{
	Player->Res(mes,lp,wp);	
	if(mes==WM_KEYDOWN&&wp==0x52)//r
	{
		Q_RS();SodEdit::GetInstance()->Stop(SOD_GAMEOVER);
		cam->CenterPoint(Player->x,Player->y);
	}
	return;
}

#endif