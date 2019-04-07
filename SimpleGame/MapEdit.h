#include"map.h"
#include"camera.h"
extern Tag TGame,PT;
extern FILE *fp;
#ifndef MAPEDIT_H
#define MAPEDIT_H

bool shiftdown=false;
bool tabdown=false;

void fputi(int put,FILE *fp)//最多五位，末尾空格
{
	fprintf(fp,"%d ",put);
}

class EMap
{
public:
	int power;//权利,1为管理，0为玩家
	int x,y,w,h,ID;
	float cx,cy,cw,ch;//内置摄像头
	map *what;
	char *name;

	int bex,bey;int enx,eny;
	bool puting;

	void EMap_Paint()
	{
		if(power==1)
		{
			what->Show(cx,cy,cw,ch);
			if(!shiftdown&&!tabdown){PicEdit::GetInstance()->Blt(ID,x-cx,y-cy,w,h);}//不改变大小，注意...
			for(int i=0;i<what->BoxNum;i++)
			{PicEdit::GetInstance()->Blt(SQ_WHITE,what->bcon[i]->x-cx,what->bcon[i]->y-cy,what->bcon[i]->w,what->bcon[i]->h,0,0,0,0,0.3);}
			if(puting&&tabdown){PicEdit::GetInstance()->Blt(SQ_WHITE,bex-cx,bey-cy,enx-bex,eny-bey,0,0,0,0,0.3);}
			wchar_t www[200];
			swprintf(www,L"%d %d %d %d %d %d",x,y,w,h,ID);//反馈编号
			PicEdit::GetInstance()->TextL(0,100,www,50,FT_WRYH,COLOR(255,255,255,1));

			float jx=cx,jy=cy;
	
			if(x<cx+50&&x>what->left()){cx-=(50-x+cx);}
			if(x>cx+core_w-50&&x<what->right()){cx+=(x-core_w+50-cx);}
			if(y<cy+50&&y>what->up()){cy-=(50-y+cy);}
			if(y>cy+core_h-50&&y<what->down()){cy+=(y-core_h+50-cy);}
	
			if(cx<what->left()){cx=what->left();}
			if(cx>what->right()-cw){cx=what->right()-cw;}
			if(cy<what->up()){cy=what->up();}
			if(cy>what->down()-ch){cy=what->down()-ch;}
	
			x+=(cx-jx),y+=(cy-jy);
	
		/*	if(GetKeyState(VK_SHIFT)>0){shiftdown=true;}
			else{shiftdown=false;innum=0;}*/
			if(GetKeyState(VK_TAB)<=0){tabdown=true;}
			else{tabdown=false;}
		}
	}
	int    EMap_Res(UINT mes,LPARAM lp,WPARAM wp)
	{
		float jx,jy;
		switch(mes)
		{
		case WM_CHAR:
			if(wp==26)
			{
				if(what->BoxNum>0&&tabdown){delete what->bcon[--what->BoxNum];}
				else if(what->GeziNum>0&&!tabdown){delete what->con[--what->GeziNum];}
			}
			break;
		case WM_MOUSEWHEEL:	
			if((int)wp>0)
			{	
				if(GetKeyState(VK_CONTROL)<0){w+=5,h+=5;if(w>300){w-=5,h-=5;}}
				else{ID++;if(ID==21){ID=1;}}
			}
			else
			{	
				if(GetKeyState(VK_CONTROL)<0){w-=5,h-=5;if(w<5){w+=5,h+=5;}}
				else{ID--;if(ID==0){ID=20;}}
			}
			break;
		case WM_MOUSEMOVE:
			jx=x,jy=y;
			y=HIWORD(lp)+cy;y-=y%5;	
			x=LOWORD(lp)+cx;x-=x%5;
			if(tabdown&&puting)
			{enx=x,eny=y;}
			break;
		case WM_LBUTTONDOWN:
			if(power==1)
			{
				if(tabdown)
				{
					if(!puting){puting=true;bex=enx=x,bey=eny=y;}
					break;
				}
				what->AddGezi(x,y,w,h,ID);
			}
			break;
		case WM_LBUTTONUP:
			if(tabdown)
			{
				if(puting&&(bex!=enx&&bey!=eny))
				{
					if(bex>enx){int ttt=bex;bex=enx,enx=ttt;}
					if(bey>eny){int ttt=bey;bey=eny,eny=ttt;}
					what->AddBox(bex,bey,enx-bex,eny-bey);
				}puting=false;
			}
			break;
		case WM_RBUTTONDOWN:
			if(power==1)
			{
				for(int i=0;i<what->GeziNum;i++)
				{
					if(x>(what->con[i]->x)&&x<(what->con[i]->x)+(what->con[i]->w)&&y>(what->con[i]->y)&&y<(what->con[i]->y)+(what->con[i]->h))
					{
						delete what->con[i];
						for(int j=i+1;j<what->GeziNum;j++){what->con[j-1]=what->con[j];}
						what->GeziNum--;
					}
				}
			}	
			break;
		}
		return 0;
	}

	void EMap_Save()
	{
		if(IDOK==MessageBox(NULL,L"Want Save?",L"GMGM",MB_OKCANCEL))
		{
			fp=fopen(name,"w");
			fputc(32,fp);
			fputi((what->GeziNum),fp);fputi((what->BoxNum),fp);
			for(int i=0;i<what->GeziNum*5;i++)
			{
				if(i==0||i%5==0){fputi((what->con[i/5]->x),fp);}
				if(i%5==1){fputi((what->con[i/5]->y),fp);}
				if(i%5==2){fputi((what->con[i/5]->w),fp);}
				if(i%5==3){fputi((what->con[i/5]->h),fp);}
				if(i%5==4){fputi((what->con[i/5]->mode),fp);}
			}
			for(int i=0;i<what->BoxNum*4;i++)
			{
				if(i==0||i%4==0){fputi((what->bcon[i/4]->x),fp);}
				if(i%4==1){fputi((what->bcon[i/4]->y),fp);}
				if(i%4==2){fputi((what->bcon[i/4]->w),fp);}
				if(i%4==3){fputi((what->bcon[i/4]->h),fp);}
			}
			MessageBox(NULL,L"ok!",L"GMGM",MB_OKCANCEL);
			fclose(fp);
		}
	}
	EMap(int gpower,map *amap,char *file)
	{
		power=gpower;what=amap;name=file;
		cx=0,cy=0;cw=800;ch=600;ID=1;
		w=h=50;puting=false;
	} 
	
}*GodMap;
#endif



