#ifndef LIZI_H
#define LIZI_H

#include"map.h"
#include<time.h>

#define LIZE_DOWN 0
#define LIZE_FLOAT 1

class lizi
{
public:
	bool IfShow(float cx,float cy,float cw,float ch,int ID)
	{
		return x[ID]+w>cx&&x[ID]<cw+cx&&y[ID]+h>cy&&y[ID]<cy+ch;
	}
public:
	
	int maindir;
	int vvv;

	float tr[1000];
	int x[1000],y[1000];//地图粒子
	int hx[1000],hy[1000];//前方粒子
	int w,h;
	int all[3];
	int PicID,method;
	map *mapon;
	lizi(map *amap,int PICID,int gmethod)
	{
		PicID=PICID;method=gmethod;vvv=20;
		srand(static_cast<unsigned int>(time(0)));
		int rddd=0;all[0]=all[1]=all[2]=0;for(int i=0;i<1000;i++){tr[i]=1;}
		mapon=amap;w=h=20;
		float bl=0.4;
		RAND(maindir,4);
		for(int i=mapon->left();i<mapon->right();)
		{
			for(int j=mapon->up();j<mapon->down();)
			{
				RAND(rddd,5);
				if(rddd<2&&all[0]<1000){x[all[0]]=i,y[all[0]]=j;all[0]++;}
				RAND(rddd,5);j+=((rddd+8)*10);
			}
			RAND(rddd,5);i+=((rddd+8)*10);
		}
		for(int i=mapon->left();i<mapon->right()*2;)
		{
			for(int j=mapon->up();j<mapon->down()*2;)
			{
				RAND(rddd,5);
				if(rddd<2&&all[2]<1000){hx[all[2]]=i,hy[all[2]]=j;all[2]++;}
				RAND(rddd,5);j+=((rddd+8)*10);
			}
			RAND(rddd,5);i+=((rddd+8)*10);
		}
	}
	void FloatShow(float cx,float cy,float cw,float ch)
	{
		int rddd=0,rdd=0;
////////////////////////////////////////////////////////////////////////////////////
		for(int i=0;i<all[0];i++)
		{
			RAND(rddd,10);RAND(rdd,3);
			if(IfShow(cx,cy,cw,ch,i)){PicEdit::GetInstance()->Blt(PicID,(x[i]-cx)*core_w/cw,(y[i]-cy)*core_h/ch,w*core_w/cw,h*core_h/ch,0,0,0,0,tr[i]);}
			if(rddd<5&&tr[i]<1){tr[i]+=0.05;}
			else if(rddd<10&&tr[i]>0){tr[i]-=0.05;}
			switch(maindir)
			{
				case 3:
					switch(rddd)
					{
					case 0:			   x[i]-=rdd;break;
					case 1:case 2: y[i]+=rdd;break;
					case 3:case 4: y[i]-=rdd;break;
					default:           x[i]+=rdd;break;
					}break;
				case 2:
					switch(rddd)
					{
					case 0:				x[i]+=rdd;break;
					case 1:case 2:	y[i]+=rdd;break;
					case 3:case 4:	y[i]-=rdd;break;
					default:			x[i]-=rdd;break;
					}break;
				case 1:
					switch(rddd)
					{
					case 0:				y[i]-=rdd;break;
					case 1:case 2:	x[i]-=rdd;break;
					case 3:case 4:	x[i]+=rdd;break;
					default:			y[i]+=rdd;break;
					}break;
				case 0:
					switch(rddd)
					{
					case 0:				y[i]+=rdd;break;
					case 1:case 2:	x[i]-=rdd;break;
					case 3:case 4:	x[i]+=rdd;break;
					default:			y[i]-=rdd;break;
					}break;
				}
				if(x[i]<mapon->left()||x[i]>mapon->right()||y[i]<mapon->up()||y[i]>mapon->down())
				{
					RAND(rddd,mapon->right()-mapon->left());
					RAND(rdd,mapon->down()-mapon->up());
					switch(maindir)
					{
					case 0:	y[i]=mapon->down(),x[i]=rddd;break;
					case 1:	y[i]=mapon->up(),x[i]=rddd;break;
					case 2:	x[i]=mapon->right(),y[i]=rdd;break;
					case 3:	x[i]=mapon->left(),y[i]=rdd;break;
					}
				}
			}
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
		for(int i=0;i<all[2];i++)
		{
			RAND(rddd,10);RAND(rdd,3);
			PicEdit::GetInstance()->Blt(PicID,(hx[i]-cx*2)*core_w/cw,(hy[i]-cy*2)*core_h/ch,(w*3/2)*core_w/cw,(h*3/2)*core_w/cw,0,0,0,0,tr[i]);
			if(rddd<5&&tr[i]<1){tr[i]+=0.05;}
			else if(rddd<10&&tr[i]>0){tr[i]-=0.05;}
			switch(maindir)
			{
				case 3:
					switch(rddd)
					{
					case 0:				hx[i]-=rdd;break;
					case 1:case 2:	hy[i]+=rdd;break;
					case 3:case 4:	hy[i]-=rdd;break;
					default:			hx[i]+=rdd;break;
					}break;
				case 2:
					switch(rddd)
					{
					case 0:				hx[i]+=rdd;break;
					case 1:case 2:	hy[i]+=rdd;break;
					case 3:case 4:	hy[i]-=rdd;break;
					default:			hx[i]-=rdd;break;
					}break;
				case 1:
					switch(rddd)
					{
					case 0:				hy[i]-=rdd;break;
					case 1:case 2:	hx[i]-=rdd;break;
					case 3:case 4:	hx[i]+=rdd;break;
					default:			hy[i]+=rdd;break;
					}break;
				case 0:
					switch(rddd)
					{
					case 0:				hy[i]+=rdd;break;
					case 1:case 2:	hx[i]-=rdd;break;
					case 3:case 4:	hx[i]+=rdd;break;
					default:			hy[i]-=rdd;break;
					}break;
				}
				if(hx[i]<mapon->left()||hx[i]>mapon->right()*2||hy[i]<mapon->up()||hy[i]>mapon->down()*2)
				{
					RAND(rddd,mapon->right()*2-mapon->left()*2);
					RAND(rdd,mapon->down()*2-mapon->up()*2);
					switch(maindir)
					{
					case 0:	hy[i]=mapon->down()*2,hx[i]=rddd;break;
					case 1:	hy[i]=mapon->up()*2,hx[i]=rddd;break;
					case 2:	hx[i]=mapon->right()*2,hy[i]=rdd;break;
					case 3:	hx[i]=mapon->left()*2,hy[i]=rdd;break;
					}
				}
			}
/////////////////////////////////////////////////////////////////////////
	}
	void DownShow(float cx,float cy,float cw,float ch)
	{
			int rdd=0,rddd=0;
////////////////////////////////////////////////////////////////////////////////////
		for(int i=0;i<all[0];i++)
		{
			RAND(rdd,5);RAND(rddd,5);
			if(IfShow(cx,cy,cw,ch,i))
			{PicEdit::GetInstance()->Blt(PicID,(x[i]-cx)*core_w/cw,(y[i]-cy)*core_h/ch,w*core_w/cw,h*core_h/ch,0,0,0,0,0.5);}
			y[i]+=(rdd+vvv);
			x[i]+=(rddd-2);
			if(x[i]<mapon->left()||x[i]>mapon->right()||y[i]<mapon->up()||y[i]>mapon->down())
			{
					RAND(rddd,mapon->right()-mapon->left());
					y[i]=mapon->up(),x[i]=rddd;
			}
		}
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
		for(int i=0;i<all[2];i++)
		{
			RAND(rddd,5);RAND(rdd,5);
			PicEdit::GetInstance()->Blt(PicID,(hx[i]-cx*2)*core_w/cw,(hy[i]-cy*2)*core_h/ch,(w*3/2)*core_w/cw,(h*3/2)*core_w/cw,0,0,0,0,0.7);
			hy[i]+=(rdd+vvv);
			hx[i]+=(rddd-2);
			if(hx[i]<mapon->left()||hx[i]>mapon->right()*2||hy[i]<mapon->up()||hy[i]>mapon->down()*2)
			{
				RAND(rddd,mapon->right()*2-mapon->left()*2);
				hy[i]=mapon->up()*2,hx[i]=rddd;
			}
		}
/////////////////////////////////////////////////////////////////////////
	}

	void Show(float cx,float cy,float cw,float ch)
	{
		switch(method)
		{
		case LIZE_DOWN:
			DownShow(cx,cy,cw,ch);
			break;
		case LIZE_FLOAT:
			FloatShow(cx,cy,cw,ch);
			break;
		}
	}
};


#endif