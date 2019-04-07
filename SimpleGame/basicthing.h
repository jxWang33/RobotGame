#ifndef BASICTHING_H
#define BASICTHING_H
#include"map.h"
class basicthing
{
public:
	basicthing(float gx,float gy,float gw,float gh,float gVx,float gVy,map *amap,int gID=MAP_8)
	{
		mapon=amap;px=x=gx,py=y=gy,w=gw,h=gh;
		Vx=gVx,Vy=gVy;nipped=false;on[0]=on[1]=on[2]=on[3]=0;
		PicID=gID;
	}
	basicthing(){}
	~basicthing(){}
	map    *mapon;
	float     x,y,w,h,Vx,Vy,wa,px,py;
	bool		allow[4],nipped;
	int        pdir,dir,on[4];
	int        PicID;
	void		Set(float gx,float gy)
	{x=gx,y=gy;}
	void  SetV(float gw,float gh)
	{w=gw,h=gh;}
	void  ValAllow()//更新allow状态
	{
		if(mapon->CrashJud(x+w+1,y)||mapon->CrashJud(x+w+1,y+h)){allow[3]=false;}else{allow[3]=true;}
		if(mapon->CrashJud(x-1,y)||mapon->CrashJud(x-1,y+h)){allow[2]=false;}else{allow[2]=true;}
		if(mapon->CrashJud(x,y+h+1)||mapon->CrashJud(x+w,y+h+1)){allow[1]=false;}else{allow[1]=true;}
		if(mapon->CrashJud(x,y-1)||mapon->CrashJud(x+w,y-1)){allow[0]=false;}else{allow[0]=true;}
	}
	int	 HasPassed()
	{
		return 1;
	}
	void		Move()
	{
		float RcdX=0,RcdY=0;//记录当前坐标
		float des[2]={0,0},finx=0,finy=0;
		for(int i=0;i<4;i++){allow[i]=true;}
		int testcount=32;
		float nx=x,ny=y,should[4]={0,0,0,0};RcdX=nx;
		if(mapon->CrashJud(x,y,w,h))
		{
		while(mapon->CrashJud(nx,ny,w,h))
		{nx+=1;if(nx>mapon->right()||nx-RcdX>testcount){nx=10000;break;}}should[3]=nx-RcdX;nx=RcdX;//计算右偏移量
		while(mapon->CrashJud(nx,ny,w,h))
		{nx-=1;if(nx<mapon->left()||nx-RcdX<-testcount){nx=-10000;break;}}should[2]=RcdX-nx;nx=RcdX;//左偏移量
		if(should[2]>should[3]){nx+=should[3];}else{nx-=should[2];}//最小偏移
		RcdY=ny;
		while(mapon->CrashJud(nx,ny,w,h))
		{ny+=1;if(ny>mapon->down()||ny-RcdY>testcount){ny=10000;break;}}should[1]=ny-RcdY;ny=RcdY;//下偏移量
		while(mapon->CrashJud(nx,ny,w,h))
		{ny-=1;if(ny<mapon->up()||ny-RcdY<-testcount){ny=-10000;break;}}should[0]=RcdY-ny;ny=RcdY;//上偏移量
		if(should[0]>should[1]){ny+=should[1];}else{ny-=should[0];}
		des[0]=(nx-RcdX)*(nx-RcdX)+(ny-RcdY)*(ny-RcdY);//移动距离平方
		finx=nx,finy=ny;
////////////////////////////////先y后x///////////////////////////////////////////////////////////////////////////////
		nx=x,ny=y;for(int i=0;i<4;i++){should[i]=0;}RcdY=ny;
		while(mapon->CrashJud(nx,ny,w,h))
		{ny+=1;if(ny>mapon->down()||ny-RcdY>testcount){ny=10000;break;}}should[1]=ny-RcdY;ny=RcdY;//下偏移量
		while(mapon->CrashJud(nx,ny,w,h))
		{ny-=1;if(ny<mapon->up()||ny-RcdY<-testcount){ny=-10000;break;}}should[0]=RcdY-ny;ny=RcdY;//上偏移量
		if(should[0]>should[1]){ny+=should[1];}else{ny-=should[0];}
		RcdX=nx;
		while(mapon->CrashJud(nx,ny,w,h))
		{nx+=1;if(nx>mapon->right()||nx-RcdX>testcount){nx=10000;break;}}should[3]=nx-RcdX;nx=RcdX;//计算右偏移量
		while(mapon->CrashJud(nx,ny,w,h))
		{nx-=1;if(nx<mapon->left()||nx-RcdX<-testcount){nx=-10000;break;}}should[2]=RcdX-nx;nx=RcdX;//左偏移量
		if(should[2]>should[3]){nx+=should[3];}else{nx-=should[2];}//最小偏移
		des[1]=(nx-RcdX)*(nx-RcdX)+(ny-RcdY)*(ny-RcdY);//移动距离平方
		if(des[1]>=des[0]){nx=finx,ny=finy;}//采取最短偏移

		ValAllow();
		if(nx-x>20&&x-nx>20){nipped=true;return;}
		else if(ny-y>20&&y-ny>20){nipped=true;return;}
		else if((!allow[0])&&(!allow[1])&&(y!=ny))
		{nipped=true;return;}
		else if((!allow[2])&&(!allow[3])&&(x!=nx))
		{nipped=true;return;}

		else {nipped=false;}
////////////////////////////////////////////////////////////////////////////////////d///////////////////////////////
		x=nx;y=ny;
		}
////////////////////////////////先x后y///////////////////////////////////////////////////////////////////////////////
		nx=x,ny=y;for(int i=0;i<4;i++){should[i]=0;}
		nx+=HasPassed()*Vx;RcdX=nx;
		while(mapon->CrashJud(nx,ny,w,h))
		{nx+=1;if(nx>mapon->right()||nx-RcdX>testcount){nx=10000;break;}}should[3]=nx-RcdX;nx=RcdX;//计算右偏移量
		while(mapon->CrashJud(nx,ny,w,h))
		{nx-=1;if(nx<mapon->left()||nx-RcdX<-testcount){nx=-10000;break;}}should[2]=RcdX-nx;nx=RcdX;//左偏移量
		if(should[2]>should[3]){nx+=should[3];}else{nx-=should[2];}//最小偏移
		ny+=HasPassed()*Vy;RcdY=ny;
		while(mapon->CrashJud(nx,ny,w,h))
		{ny+=1;if(ny>mapon->down()||ny-RcdY>testcount){ny=10000;break;}}should[1]=ny-RcdY;ny=RcdY;//下偏移量
		while(mapon->CrashJud(nx,ny,w,h))
		{ny-=1;if(ny<mapon->up()||ny-RcdY<-testcount){ny=-10000;break;}}should[0]=RcdY-ny;ny=RcdY;//上偏移量
		if(should[0]>should[1]){ny+=should[1];}else{ny-=should[0];}
		des[0]=(nx-RcdX)*(nx-RcdX)+(ny-RcdY)*(ny-RcdY);//移动距离平方
		finx=nx,finy=ny;
////////////////////////////////先y后x///////////////////////////////////////////////////////////////////////////////
		nx=x,ny=y;for(int i=0;i<4;i++){should[i]=0;}
		ny+=HasPassed()*Vy; RcdY=ny;
		while(mapon->CrashJud(nx,ny,w,h))
		{ny+=1;if(ny>mapon->down()||ny-RcdY>testcount){ny=10000;break;}}should[1]=ny-RcdY;ny=RcdY;//下偏移量
		while(mapon->CrashJud(nx,ny,w,h))
		{ny-=1;if(ny<mapon->up()||ny-RcdY<-testcount){ny=-10000;break;}}should[0]=RcdY-ny;ny=RcdY;//上偏移量
		if(should[0]>should[1]){ny+=should[1];}else{ny-=should[0];}
		nx+=HasPassed()*Vx;RcdX=nx;
		while(mapon->CrashJud(nx,ny,w,h))
		{nx+=1;if(nx>mapon->right()||nx-RcdX>testcount){nx=10000;break;}}should[3]=nx-RcdX;nx=RcdX;//计算右偏移量
		while(mapon->CrashJud(nx,ny,w,h))
		{nx-=1;if(nx<mapon->left()||nx-RcdX<-testcount){nx=-10000;break;}}should[2]=RcdX-nx;nx=RcdX;//左偏移量
		if(should[2]>should[3]){nx+=should[3];}else{nx-=should[2];}//最小偏移
		des[1]=(nx-RcdX)*(nx-RcdX)+(ny-RcdY)*(ny-RcdY);//移动距离平方
		if(des[1]>=des[0]){nx=finx,ny=finy;}//采取最短偏移
		nipped=false;
		if(nx-x>20&&x-nx>20){nipped=true;return;}
		if(ny-y>20&&y-ny>20){nipped=true;return;}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		x=nx;y=ny;ValAllow();
		on[1]=mapon->CrashJud(x,y+1,w,h);on[2]=mapon->CrashJud(x-1,y,w,h);on[3]=mapon->CrashJud(x+1,y,w,h);
		if(on[1]>=1){x+=mapon->anm[on[1]-1]->Vx;if(mapon->anm[on[1]-1]->Vy>0){y+=mapon->anm[on[1]-1]->Vy;}}
		if(on[2]>=1){if(mapon->anm[on[2]-1]->Vx>0){x+=mapon->anm[on[2]-1]->Vx;}}
		if(on[3]>=1){if(mapon->anm[on[3]-1]->Vx<0){x+=mapon->anm[on[3]-1]->Vx;}}
	}
	void	 virtual Show(float cx,float cy,float cw,float ch)
	{
		PicEdit::GetInstance()->Blt(PicID,(x-cx)*core_w/cw,(y-cy)*core_h/ch,w*core_w/cw,h*core_h/ch);
		Move();
	}
};


#endif