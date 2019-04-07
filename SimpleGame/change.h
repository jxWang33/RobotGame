#ifndef CHANGE_H
#define CHANGE_H

extern int core_w;
extern int core_h;
extern bool edited;



DWORD WINAPI else_QInit(LPVOID param);
DWORD WINAPI else_WInit(LPVOID param);
DWORD WINAPI else_EInit(LPVOID param);
DWORD WINAPI else_GUIInit(LPVOID param);

void  Loading(DWORD WINAPI init(LPVOID));
void E_Clean();
void W_Clean();
void Q_Clean();
void GUI_Clean();
void All_Init(HWND);


#endif