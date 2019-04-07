#include<stdio.h>
#include"pic.h"
#include"define.h"
#include"change.h"

#ifndef MAP_H
#define MAP_H
FILE *fp;

int fgeti(FILE *fp)//小于五位
{
		int pos=0,fin=0;
		int jilu[5]={0,0,0,0,0};
		char c=fgetc(fp);
		while(c!=32&&pos<5)
		{
			if(c>=48&&c<=57)
			{
				for(int j=0;j<pos;j++){jilu[j]*=10;}
				jilu[pos]=c-'0';pos++;
			}
			c=fgetc(fp);
		}
		for(int j=0;j<pos;j++)
		{fin+=jilu[j];}
		return fin;
}

class gezi //显示格
{
public:
	float tr;
	float x,y,w,h;
	int ID;
public:
	bool IfShow(float cx,float cy,float cw,float ch)
	{
		if(cy+ch<y||cy>y+h||cx>x+w||cx+cw<x){return false;}
		return true;
	}
	void Show(float cx,float cy,float cw,float ch)
	{
		PicEdit::GetInstance()->Blt(mode,(x-cx)*core_w/cw,(y-cy)*core_h/ch,w*(core_w/cw),h*(core_h/ch),0,0,0,0,tr);
	}
	void Jud()
	{

	}
	int    mode;//picID
	int	maybe;

	gezi(float gx,float gy,float gw,float gh,int gmode,int gID,float gtr=1.0f)
	{
		ID=gID;
		mode=gmode;
		x=gx,y=gy,w=gw,h=gh;tr=gtr;
	}
	~gezi(){}
};

class box//碰撞格
{
public:
	float x,y,w,h;
	int ID;
public:
	box(float gx,float gy,float gw,float gh,int gID)
	{ID=gID;x=gx,y=gy,w=gw,h=gh;}
	int CrashJud(float gx,float gy, float gw,float gh)
	{
		if(gy+gh<y||gy>y+h||gx>x+w||gx+gw<x){return 0;}
		return -1;
	}
	bool CrashJud(float rx,float ry)
	{
		return (rx>=x&&rx<=(x+w)&&y<=ry&&(y+h)>=ry);
	}
};

class Anm
{
public:
	float x,y,w,h,tr;
	float startx,starty;
	float Vx,Vy;
	int ID;
	int xrange,yrange;
	int govx,backvx,govy,backvy;
	int    mode;//picID
public:
	Anm(float gx,float gy,float gw,float gh,int gmode,int gID,int movex=0,int movey=0,int ggovx=0,int gbackvx=0,int ggovy=0,int gbackvy=0)
	{
		ID=gID;x=gx,y=gy,w=gw,h=gh;mode=gmode;Vx=Vy=0;tr=1;
		xrange=movex,yrange=movey;
		govx=ggovx,govy=ggovy;
		backvx=gbackvx,backvy=gbackvy;
		Vx=govx,Vy=govy;startx=x,starty=y;
	}
	int CrashJud(float gx,float gy, float gw,float gh)
	{
		if(gy+gh<y||gy>y+h||gx>x+w||gx+gw<x){return 0;}
		return ID;
	}
	bool CrashJud(float rx,float ry)
	{
		return (rx>=x&&rx<=(x+w)&&y<=ry&&(y+h)>=ry);
	}
	bool IfShow(float cx,float cy,float cw,float ch)
	{
		if(cy+ch<y||cy>y+h||cx>x+w||cx+cw<x){return false;}
		return true;
	}
	void Show(float cx,float cy,float cw,float ch)
	{
		PicEdit::GetInstance()->Blt(mode,(x-cx)*core_w/cw,(y-cy)*core_h/ch,w*(core_w/cw),h*(core_h/ch),0,0,0,0,tr);
		int sma,big;
		if(xrange>0){sma=startx,big=xrange+startx;}
		else{sma=startx+xrange,big=startx;}
		if(x>=big){Vx=backvx;}
		if(x<=sma){Vx=govx;}

		if(yrange>0){sma=starty,big=yrange+starty;}
		else{sma=starty+yrange,big=starty;}
		if(y>=big){Vy=backvy;}
		if(y<=sma){Vy=govy;}

		x+=Vx,y+=Vy;
	}
};

class map
{
public:
	int w,h,vsw,vsh;
	int vsx,vsy;
	gezi *con[10000];
	box *bcon[10000];
	Anm *anm[100];
	int GeziNum,BoxNum,AnmNum;
	int maybe,maybedir;

	//均为静止,移动起来较麻烦
	int bgnum,bgdep[10],bgPic[10];//越大越近，最多10层
	int scnum,scdep[100],scpic[100],scx[100],scy[100],scw[100],sch[100];//地图上零散物品

	~map()
	{
		for(int i=0;i<GeziNum;i++){delete con[i];}
		for(int i=0;i<BoxNum;i++){delete bcon[i];}
		for(int i=0;i<AnmNum;i++){delete anm[i];}
	}
	map(int gw=4000,int gh=1000)
	{
		vsw=w=gw;vsh=h=gh;vsx=vsy=0;
		AnmNum=BoxNum=GeziNum=0;maybe=0;maybedir=0;
		bgnum=scnum=0;
	}
	void Load(char *name)
	{
		fp=fopen(name,"r");
		fgetc(fp);bool boxing=false;
		float jx,jy,jw,jh;int jmode;
		int geziall=fgeti(fp);
		int boxall=fgeti(fp);
		for(int i=0;GeziNum<geziall;i++)
		{
			if(i==0||i%5==0){jx=fgeti(fp);}
			if(i%5==1){jy=fgeti(fp);}
			if(i%5==2){jw=fgeti(fp);}
			if(i%5==3){jh=fgeti(fp);}
			if(i%5==4){jmode=fgeti(fp);AddGezi(jx,jy,jw,jh,jmode);}
		}
		for(int i=0;BoxNum<boxall;i++)
		{
			if(i==0||i%4==0){jx=fgeti(fp);}
			if(i%4==1){jy=fgeti(fp);}
			if(i%4==2){jw=fgeti(fp);}
			if(i%4==3){jh=fgeti(fp);AddBox(jx,jy,jw,jh);}
		}
		fclose(fp);
	}
	void ShowBG(float cx,float cy,float cw,float ch)
	{
		for(int i=0;i<bgnum;i++)
		{PicEdit::GetInstance()->Blt(bgPic[i],0,0,core_w,core_h,cx/50*bgdep[i],cy/50*bgdep[i],core_w+(cw-core_w)/50,core_h+(ch-core_h)/50);}
	}
	void ShowThings(float cx,float cy,float cw,float ch)
	{
		for(int i=0;i<scnum;i++)
		{PicEdit::GetInstance()->Blt(scpic[i],(scx[i]-cx)*(core_w/cw),(scy[i]-cy)*(core_h/ch),scw[i]*(core_w/cw),sch[i]*(core_h/ch));}
	}
	void Show(float cx,float cy,float cw,float ch)
	{
		for(int i=0;i<AnmNum;i++)
		{
			//if(anm[i]->IfShow(cx,cy,cw,ch)){
			anm[i]->Show(cx,cy,cw,ch);
			//}
		}
		for(int i=0;i<GeziNum;i++)
		{if(con[i]->IfShow(cx,cy,cw,ch)){con[i]->Show(cx,cy,cw,ch);}}

//		Jud();
	}
	void AddGezi(float gx,float gy,float gw,float gh,int gmode)
	{
		con[GeziNum]=new gezi(gx,gy,gw,gh,gmode,GeziNum);
		GeziNum++;
	}
	void AddAnm(float gx,float gy,float gw,float gh,int gmode,int movex=0,int movey=0,int ggovx=0,int gbackvx=0,int ggovy=0,int gbackvy=0)
	{
		anm[AnmNum]=new Anm(gx,gy,gw,gh,gmode,GeziNum,movex,movey,ggovx,gbackvx,ggovy,gbackvy);
		AnmNum++;
	}
	void AddBox(float gx,float gy,float gw,float gh)
	{
		bcon[BoxNum]=new box(gx,gy,gw,gh,BoxNum);
		BoxNum++;
	}
	void AddBG(int PICID,int depth)
	{
		bgPic[bgnum]=PICID;bgdep[bgnum]=depth;bgnum++;
	}
	void AddSC(int PICID,int gx,int gy,int gw,int gh,int depth=1)
	{
		scpic[scnum]=PICID;scdep[scnum]=depth;
		scx[scnum]=gx;scy[scnum]=gy;scw[scnum]=gw;sch[scnum]=gh;
		scnum++;
	}

	void CSize(float gw,float gh)
	{
		vsw=gw,vsh=gh;
	}
	void resize(int gID,float gw,float gh)
	{
		con[gID]->w=gw;
		con[gID]->h=gh;
	}

	bool CrashJud(float rx,float ry)
	{
		for(int i=0;i<BoxNum;i++)
		{
			if(bcon[i]->CrashJud(rx,ry))
			{
				return true;
			}
		}
		for(int i=0;i<AnmNum;i++)
		{
			if(anm[i]->CrashJud(rx,ry))
			{
				return true;
			}
		}
		if(rx<left()||rx>right()||ry>down()||ry<up())
		{return true;}
		return false;
	}
	int CrashJud(float gx,float gy, float gw,float gh)
	{
		for(int i=AnmNum-1;i>=0;i--)
		{
			if(anm[i]->CrashJud(gx,gy,gw,gh))
			{return i+1;}
		}
		for(int i=BoxNum-1;i>=0;i--)
		{
			if(bcon[i]->CrashJud(gx,gy,gw,gh))
			{return -1;}
		}
		if(gx<left()||gx+gw>right()||gy+gh>down()||gy<up())
		{return -1;}
		return 0;
	}
	bool AllIn(float gx,float gy, float gw,float gh)
	{
		if(!CrashJud(gx,gy)){return false;}
		if(!CrashJud(gx,gy+gh)){return false;}
		if(!CrashJud(gx+gw,gy)){return false;}
		if(!CrashJud(gx+gw,gy+gh)){return false;}
		return true;
	}

//可视边界
	int vleft(){return vsx;}
	int vright(){return vsw;}
	int vup(){return vsy;}
	int vdown(){return vsh;}
//真实边界
	int left(){return 0;}
	int right(){return w;}
	int up(){return 0;}
	int down(){return h+100;}//死亡透支
};

#endif