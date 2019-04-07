#include"things.h"
#include"camera.h"

savepoint *WSave;
map* map_two;
trap* dici;

DWORD WINAPI else_WInit(LPVOID param)
{
	PicEdit::GetInstance()->Load(L"res/map/E.png",PIC_E);
	PicEdit::GetInstance()->Load(L"res/map/F.png",PIC_F);
	PicEdit::GetInstance()->Load(L"res/map/q/bg3.png",BG_3);

	SodEdit::GetInstance()->Load("res/bg2.ogg",SOD_TWOBG);

	map_two=new map(3000,600);
	map_two->Load("map_two.ini");	map_two->AddBG(BG_3,5);
	map_two->AddSC(PIC_E,0,335,200,100);map_two->AddSC(PIC_F,2485,115,100,200);
	Player=new hero(0,360,18,47,map_two,0,1000,3,false,PIC_HRO_1);Player->sw_attack=true;
	cam= new camera(map_two);cam->SetCenter(Player->x,Player->y);
	dici=new trap(530,545,18,5,MAP_21,530,545,190,5);

	dapao[0]=new bigboom(340,510,1,map_two);
	dapao[1]=new bigboom(130,230,1,map_two);
	dapao[2]=new bigboom(975,420,0,map_two);
	dapao[3]=new bigboom(1435,210,0,map_two);
	dapao[4]=new bigboom(1225,310,1,map_two);
	dapao[5]=new bigboom(1885,360,0,map_two);
	dapao[6]=new bigboom(1575,260,1,map_two);
	dapao[7]=new bigboom(1790,260,0,map_two);
	dapao[8]=new bigboom(2660,160,0,map_two);
	GodMap=new EMap(1,map_two,"map_two.ini");
	WSave=new savepoint(map_two,40,40);WSave->add(1180,160);WSave->add(2260,510);

	GG[1]=new GGP(1,540,290,L"在你的子弹消失前，你将无法射出第二发");
	GG[2]=new GGP(3,2350,425,L"变大后将会跳的更高");
	loading=false;
	SodEdit::GetInstance()->Play(SOD_TWOBG,1);SodEdit::GetInstance()->Sod[SOD_TWOBG]->SetVolume(0.2);
	return 0;
}

void W_Clean()
{
	for(int i=0;i<9;i++){delete dapao[i];}
	delete GodMap;delete map_two;
	delete WSave;delete dici;
	delete GG[1];delete GG[2];

	PicEdit::GetInstance()->Delete(PIC_E);
	PicEdit::GetInstance()->Delete(PIC_F);
	PicEdit::GetInstance()->Delete(BG_3);
	SodEdit::GetInstance()->Delete(SOD_TWOBG);
}
void W_Jud()
{
	if(Player->x>2050){Player->sw_size=true;}
	if(Player->x+Player->w>=2990)
	{
		W_Clean();
		Loading(else_EInit);
		PT=TGame;TGame=E;
	}
	if(gameover()){SodEdit::GetInstance()->Stop(SOD_TWOBG);}
}
void W_RS()
{
	for(int i=0;i<9;i++){delete dapao[i];}
	dapao[0]=new bigboom(340,510,1,map_two);
	dapao[1]=new bigboom(130,230,1,map_two);
	dapao[2]=new bigboom(975,420,0,map_two);
	dapao[3]=new bigboom(1435,210,0,map_two);
	dapao[4]=new bigboom(1225,310,1,map_two);
	dapao[5]=new bigboom(1885,360,0,map_two);
	dapao[6]=new bigboom(1575,260,1,map_two);
	dapao[7]=new bigboom(1790,260,0,map_two);
	dapao[8]=new bigboom(2660,160,0,map_two);
	delete Player;
	if(WSave->value==0){Player=new hero(0,360,18,47,map_two,0,1000,3,false,PIC_HRO_1);}
	else	
	{
		Player=new hero(WSave->rex(),WSave->rey(),18,47,map_two,0,1000,3,false,PIC_HRO_1);
	}
	Player->sw_attack=true;
	SodEdit::GetInstance()->Play(SOD_TWOBG,1);
}
void W_Paint()
{
	map_two->ShowBG(cam->x,cam->y,cam->w,cam->h);
	WSave->Show(cam->x,cam->y,cam->w,cam->h);
	Player->Show(cam->x,cam->y,cam->w,cam->h);
	for(int i=0;i<9;i++)
	{
		dapao[i]->show(cam->x,cam->y,cam->w,cam->h);
	}
	map_two->ShowThings(cam->x,cam->y,cam->w,cam->h);
	cam->ShowEff();
	dici->Show(cam->x,cam->y,cam->w,cam->h);
	cam->Show();
	GG[1]->Show(cam->x,cam->y,cam->w,cam->h);
	GG[2]->Show(cam->x,cam->y,cam->w,cam->h);
	cam->FrontShow();

	W_Jud();
}
void W_Res(UINT mes,LPARAM lp,WPARAM wp)
{
	Player->Res(mes,lp,wp);	
	if(mes==WM_KEYDOWN&&wp==0x52)//r
	{
		W_RS();SodEdit::GetInstance()->Stop(SOD_GAMEOVER);
		cam->SetCenter(Player->x,Player->y);
	}

	return;
}
