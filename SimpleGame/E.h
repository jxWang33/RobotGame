#include"things.h"
#include"camera.h"
#include"lizi.h"

savepoint *ESave;
map* map_three;
trap* water[2];
int     count_water[2]={0,0};
float count_jd=0;
int	count_w=0,count_h=0;
lizi	*lizi2;

bool Ein=false;

void InitMove()
{
	map_three->AddAnm(2065,1830,50,50,MAP_7,200,0,2,-2);
	map_three->AddAnm(2065,1880,50,50,MAP_7,200,0,2,-2);
	map_three->AddAnm(2065,1930,50,50,MAP_7,200,0,2,-2);

	map_three->AddAnm(2115,1625,50,50,MAP_7,0,-450,0,0,2,-2);
	map_three->AddAnm(2165,1625,50,50,MAP_7,0,-450,0,0,2,-2);
	map_three->AddAnm(2215,1625,50,50,MAP_7,0,-450,0,0,2,-2);
	map_three->AddAnm(2265,1625,50,50,MAP_7,0,-450,0,0,2,-2);
	map_three->AddAnm(2115,1175,50,50,MAP_7,0,450,0,0,2,-2);
	map_three->AddAnm(2165,1175,50,50,MAP_7,0,450,0,0,2,-2);
	map_three->AddAnm(2215,1175,50,50,MAP_7,0,450,0,0,2,-2);
	map_three->AddAnm(2265,1175,50,50,MAP_7,0,450,0,0,2,-2);

	map_three->AddAnm(2615,1175,50,50,MAP_7,0,250,0,0,5,-2);
	map_three->AddAnm(2665,1175,50,50,MAP_7,0,250,0,0,5,-2);
	map_three->AddAnm(2715,1175,50,50,MAP_7,0,250,0,0,5,-2);
	map_three->AddAnm(2765,1175,50,50,MAP_7,0,250,0,0,5,-2);
	map_three->AddAnm(2815,1175,50,50,MAP_7,0,250,0,0,5,-2);
	
	map_three->AddAnm(2815,825,50,50,MAP_7,1100,0,5,-5);
	map_three->AddAnm(2815,875,50,50,MAP_7,1100,0,5,-5);
	map_three->AddAnm(2815,925,50,50,MAP_7,1100,0,5,-5);
	map_three->AddAnm(2815,975,50,50,MAP_7,1100,0,5,-5);
	map_three->AddAnm(3915,825,50,50,MAP_7,-1100,0,5,-5);
	map_three->AddAnm(3915,875,50,50,MAP_7,-1100,0,5,-5);
	map_three->AddAnm(3915,925,50,50,MAP_7,-1100,0,5,-5);
	map_three->AddAnm(3915,975,50,50,MAP_7,-1100,0,5,-5);
	map_three->AddAnm(3915,825,50,50,MAP_7,-1100,0,2,-2);
	map_three->AddAnm(3915,875,50,50,MAP_7,-1100,0,2,-2);
	map_three->AddAnm(3915,925,50,50,MAP_7,-1100,0,2,-2);
	map_three->AddAnm(3915,975,50,50,MAP_7,-1100,0,2,-2);

	for(int i=0;i<21;i++)
	{map_three->AddAnm(2715+i*50,575,50,50,MAP_7,0,150,0,0,2,-2);}
	
	for(int i=0;i<10;i++)
	{map_three->AddAnm(2115,225+i*50,50,50,MAP_7,400,0,5,-5);}
	for(int i=0;i<10;i++)
	{map_three->AddAnm(2515,225+i*50,50,50,MAP_7,-400,0,5,-5);}
	for(int i=0;i<9;i++)
	{map_three->AddAnm(2115+i*50,275,50,50,MAP_7,0,400,0,0,5,-5);}

}
void Initdapao()
{
	dapao[0]=new bigboom(250,1290,1,map_three,40);
	dapao[1]=new bigboom(250,1140,1,map_three,50);
	dapao[2]=new bigboom(250,990,1,map_three,60);
	dapao[3]=new bigboom(250,840,1,map_three,70);
	dapao[4]=new bigboom(1280,740,0,map_three);
	dapao[5]=new bigboom(900,840,1,map_three);
	dapao[6]=new bigboom(1280,990,0,map_three);
	dapao[7]=new bigboom(900,1090,1,map_three);
	dapao[8]=new bigboom(900,1240,1,map_three);
	dapao[9]=new bigboom(1280,1340,0,map_three);
	dapao[10]=new bigboom(900,1490,1,map_three);
	dapao[11]=new bigboom(1280,1590,0,map_three);
	dapao[12]=new bigboom(900,1890,1,map_three);
	dapao[13]=new bigboom(3965,135,0,map_three);
	dapao[14]=new bigboom(2525,1235,0,map_three);
	dapao[15]=new bigboom(2360,1340,1,map_three);
	dapao[16]=new bigboom(2525,1435,0,map_three);
}

DWORD WINAPI else_EInit(LPVOID param)
{
	SodEdit::GetInstance()->Load("res/bg3.ogg",SOD_THREEBG);SodEdit::GetInstance()->Sod[SOD_THREEBG]->SetVolume(0.5);
	SodEdit::GetInstance()->Load("res/show.wav",SOD_SHOW);
	PicEdit::GetInstance()->Load(L"res/map/q/bg4.png",BG_4);
	PicEdit::GetInstance()->Load(L"res/map/q/bg5.png",BG_5);
	PicEdit::GetInstance()->Load(L"res/map/q/bg6.png",BG_6);
	PicEdit::GetInstance()->Load(L"res/map/G.png",PIC_G);
	PicEdit::GetInstance()->Load(L"res/map/H.png",PIC_H);
	PicEdit::GetInstance()->Load(L"res/final.png",PIC_FIN,true);

	map_three=new map(4000,2000);
	map_three->Load("map_three.ini");map_three->AddSC(PIC_G,400,1730,100,200);map_three->AddSC(PIC_H,1610,1810,200,100);
	map_three->AddBG(BG_4,1);map_three->AddBG(BG_5,8);map_three->AddBG(BG_6,15);
	ESave=new savepoint(map_three,40,40);
	ESave->add(255,990);ESave->add(855,340);ESave->add(1270,1940);ESave->add(2315,1140);
	ESave->add(2720,985);ESave->add(3920,735);ESave->add(2670,185);
	InitMove();
	Initdapao();
	GG[1]=new GGP(1,535,1605,L"注意左上角油量剩余");
	GG[2]=new GGP(2,205,740,L"千万别跳下去");
	GG[3]=new GGP(3,810,795,L"在油量耗尽时使用二段跳争取时间是明智的决定,利用跳跃的冲力起飞也是");
	GG[4]=new GGP(4,2470,1940,L"受伤或超出边界都会强制复位");
	GG[5]=new GGP(5,2360,1590,L"要靠脑子，而不是运气");
	GG[6]=new GGP(6,3220,485,L"迷宫尽头什么也没有，所以你不必去");
	GG[7]=new GGP(7,3920,485,L"真的什么也没有=_=");
	GG[8]=new GGP(8,2320,1735,L"小体积会更加灵活,并且耗油量会更少");
	Player=new hero(0,1900,18,47,map_three,0,1000,3,false,PIC_HRO_1);Player->sw_attack=true;Player->sw_size=true;Player->sw_fly=true;
	cam= new camera(map_three);cam->SetCenter(Player->x,Player->y);//cam->CSize(1600,1200);
	GodMap=new EMap(1,map_three,"map_three.ini");
	water[0]=new trap(0,0,0,0,-1,0,830,200,600,-1);
	water[1]=new trap(0,0,0,0,-1,2910,1680,1090,300,-1);
	lizi2=new lizi(map_three,PIC_LZ2,LIZE_FLOAT);

	SodEdit::GetInstance()->Play(SOD_THREEBG,1);
	loading=false;
	return 0;
}
void E_Clean()
{
	for(int i=0;i<17;i++){delete dapao[i];}
	for(int i=1;i<9;i++){delete GG[i];}
	delete GodMap;delete map_three;
	delete water[0];delete water[1];
	delete lizi2;delete ESave;

	SodEdit::GetInstance()->Delete(SOD_THREEBG);
	SodEdit::GetInstance()->Delete(SOD_SHOW);
	PicEdit::GetInstance()->Delete(PIC_G);
	PicEdit::GetInstance()->Delete(PIC_H);
	PicEdit::GetInstance()->Delete(BG_4);
	PicEdit::GetInstance()->Delete(BG_5);
	PicEdit::GetInstance()->Delete(BG_6);
	PicEdit::GetInstance()->Delete(PIC_FIN);
}
void E_Jud()
{
	//if(Player->x>2050){Player->sw_size=true;}
	if(Player->x+Player->w>=1320)
	{
		Player->sw_dbl=true;
		if(!Ein){Ein=true;SodEdit::GetInstance()->Play(SOD_SHOW,0);}
		if(Player->x<2070&&cam->w<1600){cam->faraway(5);}
	}
	if(Player->x>2070&&cam->w>800){cam->faraway(-5);}
	if(Player->x<=2000&&Player->y<=1260&&Player->x>=1370)
	{Player->stand();Player->sw_ctrl=false;count_w+=10;count_h+=10;}
	if(count_w>6000)
	{
		PicEdit::GetInstance()->TextL(600,500,L"Fin",50,FT_WRYH,COLOR(1,1,1,1));
		count_h=count_w=6000;
	}
	if(gameover()){}
}
void E_RS()
{
	delete Player;
	for(int i=0;i<17;i++){delete dapao[i];}
	Initdapao();
	if(ESave->value==0){Player=new hero(0,1900,18,47,map_three,0,1000,3,false,PIC_HRO_1);}
	else	
	{Player=new hero(ESave->rex(),ESave->rey(),18,47,map_three,0,1000,3,false,PIC_HRO_1);}
	Player->sw_attack=true;Player->sw_size=true;Player->sw_fly=true;
	cam->SetCenter(Player->x,Player->y);
}
void E_Paint()
{
	map_three->ShowBG(cam->x,cam->y,cam->w,cam->h);
	ESave->Show(cam->x,cam->y,cam->w,cam->h);
	for(int i=0;i<17;i++){dapao[i]->show(cam->x,cam->y,cam->w,cam->h);}
	Player->Show(cam->x,cam->y,cam->w,cam->h);
	cam->ShowEff();

	//water//
	water[0]->Show(cam->x,cam->y,cam->w,cam->h);
	water[1]->Show(cam->x,cam->y,cam->w,cam->h);
	PicEdit::GetInstance()->Blt(SQ_RED,(0-cam->x)*core_w/cam->w,(830-cam->y)*core_h/cam->h,200*core_w/cam->w,600*core_h/cam->h,0,0,0,0,0.3);
	PicEdit::GetInstance()->Blt(PIC_WATER,(0-cam->x)*core_w/cam->w,(830-cam->y)*core_h/cam->h,200*core_w/cam->w,600*core_h/cam->h,
	count_water[0],0,200,600,0.5);
	PicEdit::GetInstance()->Blt(SQ_RED,(2910-cam->x)*core_w/cam->w,(1680-cam->y)*core_h/cam->h,1090*core_w/cam->w,300*core_h/cam->h,0,0,0,0,0.3);
	PicEdit::GetInstance()->Blt(PIC_WATER,(2910-cam->x)*core_w/cam->w,(1680-cam->y)*core_h/cam->h,1090*core_w/cam->w,300*core_h/cam->h,
	count_water[1],0,1090,300,0.5);
	count_water[0]++;if(count_water[0]+200>=2000){count_water[0]=1000-200;}
	count_water[1]++;if(count_water[1]+1090>=3000){count_water[1]=2000-1090;}
	//water//

	cam->Show();
	for(int i=1;i<9;i++){GG[i]->Show(cam->x,cam->y,cam->w,cam->h);}
	map_three->ShowThings(cam->x,cam->y,cam->w,cam->h);
	lizi2->Show(cam->x,cam->y,cam->w,cam->h);
	cam->FrontShow();
	
	//
	PicEdit::GetInstance()->BBlt(PIC_FIN,(1470-cam->x-count_w/2)*core_w/cam->w,(760-cam->y-count_h/2)*core_h/cam->h,(500+count_w)*core_w/cam->w,(500+count_h)*core_h/cam->h
		,0,0,500,500,count_jd,(1470-cam->x+250)*core_w/cam->w,(760-cam->y+250)*core_h/cam->h);
	count_jd+=1;if(count_jd>=360){count_jd=0;}
	//
	E_Jud();
}
void E_Res(UINT mes,LPARAM lp,WPARAM wp)
{
	Player->Res(mes,lp,wp);	
	if(mes==WM_KEYDOWN&&wp==0x52)//r
	{
		E_RS();SodEdit::GetInstance()->Stop(SOD_GAMEOVER);
		cam->CenterPoint(Player->x,Player->y);
	}

	return;
}
