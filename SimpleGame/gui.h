#include <windows.h>
#include"pic.h"
#include<imm.h>
#include"sound.h"
#include"things.h"
#include"change.h"
#include"camera.h"
#include"MapEdit.h"

#pragma comment(lib,"imm32.lib")
#ifndef GUI_H
#define GUI_H

extern DWORD		    g_tPre,g_tNow;
extern bool				loading;
map *map_gui;
DWORD WINAPI else_GUIInit(LPVOID param)
{
	SodEdit::GetInstance()->Load("res/GUI/GUI.ogg",SOD_GUI);
	PicEdit::GetInstance()->Load(L"res/GUI/GUI.png",PIC_GUIBG);
	PicEdit::GetInstance()->Load(L"res/GUI/light.png",PIC_GUILIGHT);
	PicEdit::GetInstance()->Load(L"res/GUI/TS.png",PIC_GUITS);
	map_gui=new map(480,360);map_gui->Load("map_gui.ini");
	map_gui->AddBG(PIC_GUIBG,1);//map_gui->AddAnm(200,250,50,50,MAP_1);
	Player=new hero(345,150,18,47,map_gui,0,1000,3,false,PIC_HRO_1);
	cam= new camera(map_gui);cam->SetCenter(Player->x+Player->w/2,Player->y+Player->h/2);cam->CSize(480,360);
	GodMap=new EMap(1,map_gui,"map_gui.ini");	
	if(!(SodEdit::GetInstance()->IsPlaying(SOD_GUI))){SodEdit::GetInstance()->Play(SOD_GUI,1);}
	loading=false;	TGame=GUI;
	return 0;
}

void GUI_Paint()
{
	map_gui->ShowBG(cam->x,cam->y,cam->w,cam->h);
	Player->Show(cam->x,cam->y,cam->w,cam->h);
	cam->Show();
	cam->ShowEff();
	cam->FrontShow();

	PicEdit::GetInstance()->Blt(PIC_GUITS,30,330,100,50);
	PicEdit::GetInstance()->Blt(PIC_GUILIGHT,0,0,800,600,0,0,0,0,0.3);
	PicEdit::GetInstance()->TextS(500,500,300,500,L"游戏说明：wsad移动，空格为功能键 , Tab 添加地图块,esc退出",20, FT_WRYH,COLOR(255,255,255,1));//动态加载字体，一些字体加载效率低
}
void GUI_Clean()
{
	SodEdit::GetInstance()->Delete(SOD_GUI);PicEdit::GetInstance()->Delete(PIC_GUIBG);
	PicEdit::GetInstance()->Delete(PIC_GUILIGHT);PicEdit::GetInstance()->Delete(PIC_GUITS);
	delete map_gui;delete Player;delete cam;delete GodMap;
	loading=true;
}
void GUI_Res(UINT mes,LPARAM lp,WPARAM wp)
{
/*	int rrr=BStart->Res(lp,mes);//响应按钮
	if(rrr==3){GUIend=true;SodEdit::GetInstance()->Pause(SOD_GUI);}
	if(rrr==1){if(!played){if(!SodEdit::GetInstance()->IsPlaying(SOD_GUIONBTN)){SodEdit::GetInstance()->Play(SOD_GUIONBTN,0);}played=true;}}
	if(rrr==0){played=false;}*/
	if(Player->x==0){GUI_Clean();PT=TGame;TGame=Q;Loading(else_QInit);}
	Player->Res(mes,lp,wp);	
}




#endif