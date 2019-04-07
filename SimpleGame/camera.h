#include"map.h"
#include"hero.h"
#ifndef CAMERA_H
#define CAMERA_H

bool firstshow=false,firstshowQ=false;
float Qtr=0;int Qtrdir=0;

class camera
{
public:
	float	x,y,w,h;
	float    vx,vy;
	int    zbj,ybj,sbj,xbj;//上下左右边界

	map *mapon;
	bool locked;

	void Show()
	{
		mapon->Show(x,y,w,h);
	/*	wchar_t wmm[200];
		swprintf(wmm,sizeof(wmm),L"%d %d",x,y);
		PicEdit::GetInstance()->TextL(0,20,wmm,20,FT_WRYH,COLOR(255,255,255,1));*/

	}
	void FrontShow()
	{
		Player->ShowState();
		jud();
	}
	void ShowEff()
	{
		for(int i=0;i<effect::all;i++)
		{Effect[i]->Show(x,y,w,h,i);	}
	}
	void ShowCamEff()
	{
		//for(int i=0;i<effect::all;i++)
		//{Effect[i]->Show(x,y,w,h,i);	}
	}

	void Set(int gx,int gy)
	{
		if(gx>zbj&&gx<ybj){x=gx;}
		if(gy>sbj&&gy<xbj){y=gy;}
	}
	void SetCenter(int gx,int gy)
	{
		x=gx-w/2;
		y=gy-h/2;
		if(x<zbj){x=zbj;}if(x+w>ybj){x=ybj-w;}
		if(y<sbj){y=sbj;}if(y+h>xbj){y=xbj-h;}
	}
	void CenterPoint(int gx,int gy)
	{
		float ljz=10;
		if(gx>x+w/2&&x+w<ybj)
		{
			if(vx<ljz){vx=(gx-x-w/2)/5;}
		//	if(gx<x+w/2){x=gx-w/2;vx-=0.5;}
		}
		else if(gx<w/2+x&&x>zbj)
		{
			if(vx>-ljz){vx=(gx-x-w/2)/5;}
			//if(gx>x+w/2){x=gx-w/2;vx-=0.5;}
		}
		if(x+vx<zbj){x=zbj;vx=0;}if(x+w+vx>ybj){x=ybj-w;vx=0;}

		if(gy>y+h/2&&y+h<xbj)
		{
			if(vy<ljz){vy=(gy-y-h/2)/5;}
			//if(gy<y+h/2){y=gy-h/2;vy-=0.5;}
		}
		else if(gy<h/2+y&&y>sbj)
		{
			if(vy>-ljz){vy=(gy-y-h/2)/5;}
			//if(gy>y+h/2){y=gy-h/2;vy-=0.5;}
		}
		if(y+vy<sbj){y=sbj;vy=0;}if(y+h+vy>xbj){y=xbj-h;vy=0;}
	}
	void jud()
	{
		zbj=mapon->vleft(),ybj=mapon->vright();sbj=mapon->vup();xbj=mapon->vdown();
		if(locked)
		{
			CenterPoint(Player->x+Player->w/2,Player->y+Player->h/2);
			if(Player->backing){CenterPoint(Player->js.x+Player->js.w/2,Player->js.y+Player->js.h/2);}
		}
		else
		{
			/*if(x<sx){if(sx-x<5){x=sx;}else{x+=5;}}
			else if(x>sx){if(sx-x>-5){x=sx;}else{x-=5;}}
			if(y<sy){if(sy-y<5){y=sy;}else{y+=5;}}
			else if(y>sy){if(sy-y>-5){y=sy;}else{y-=5;}}
			if(Player->backing){CPmove(Player->js.x,Player->js.y);}*/
		}
		x+=vx;y+=vy;
	}

	bool ifon(int gx,int gy)
	{
		return (gx>x&&gx<x+800&&gy>y&&gy<y+600);
	}

	void  CSize(int gw,int gh){w=gw,h=gh;}
	void faraway(float value)
	{
		float bz=(float)core_h/(float)core_w;float jw=w,jh=h;
		w+=value;h+=value*bz;
		if(w>mapon->vright()-mapon->vleft()||h>mapon->vdown()-mapon->vup())
		{w=jw,h=jh;}
	}

	
	camera(map *amap)
	{
		mapon=amap;w=core_w,h=core_h;
		x=0;y=0;vx=vy=0;
		zbj=mapon->vleft(),ybj=mapon->vright();sbj=mapon->vup();xbj=mapon->vdown();
		locked=true;
	}
	~camera(){}
}*cam;//唯一摄像头


#endif