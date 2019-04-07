#ifndef CURSOR_H
#define CURSOR_H

#include<windows.h>
int csrmode=0, FPScount=0,FPS=0;
float FPS1=0,FPS2=0;
void cursor()
{
	ShowCursor(false);
}
void Ccsrmode(int x)
{
	csrmode=x;
}
int csrset(int x,int y)
{
	wchar_t fpsString[20];
	FPScount++;FPS1=timeGetTime()*0.001f;
	if(FPS1-FPS2>1.0f)
	{
		FPS=FPScount/(FPS1-FPS2);
		FPS2=FPS1;
		FPScount=0;
	}
	swprintf(fpsString,sizeof(fpsString),L"FPS: %d",FPS);
	PicEdit::GetInstance()->TextL(700,0, fpsString,20,FT_WRYH,COLOR(1,1,1,1));
	PicEdit::GetInstance()->Blt(PIC_MG,x,y,20,20);
	return csrmode;
}
#endif