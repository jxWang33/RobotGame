#ifndef  DEFINE_H
#define DEFINE_H


#define DELAY(P)	g_tNow = GetTickCount();if(g_tNow-g_tPre <= P)	{Sleep(1);continue;}g_tPre = GetTickCount();
#define COLOR(r,g,b,tr)  D2D1::ColorF(r,g,b, tr)
#define RAND(x,y)      x=rand();if(x<=0){x=-x;}if(y!=0){x=x%y;}

//////////////////////////////////////////////////////////////////////////////////////
#define SOD_GUI				1
#//define SOD_GUIONBTN	2

#define SOD_ONEBG			2
#define SOD_TWOBG			3
#define SOD_THREEBG      4

//#define SOD_BTNON			3

#define SOD_GGPRMD		10
#define SOD_SHOW			11

#define SOD_SHOOT			50
#define SOD_EFFECT			51
#define SOD_GAMEOVER	100
#define SOD_WRONG        101
#define SOD_GO				102
#define SOD_FALL				103
#define SOD_DBL				104
#define SOD_UNDBL			105
#define SOD_BIU				106
//////////////////////////////////////////////////////////////////////////////////////
#define  MAP_1					1
#define  MAP_2					2
#define  MAP_3					3
#define  MAP_4					4
#define  MAP_5					5
#define  MAP_6					6
#define  MAP_7					7
#define  MAP_8					8
#define  MAP_9					9
#define  MAP_10				10
#define  MAP_11				11
#define  MAP_12				12
#define  MAP_13				13
#define  MAP_14				14
#define  MAP_15				15
#define  MAP_16				16
#define  MAP_17				17
#define  MAP_18				18
#define  MAP_19				19
#define  MAP_20				20
#define  MAP_21				21

#define PIC_FIN					30

#define  BG_1						40
#define  BG_2						41
#define  BG_3						42
#define  PIC_Q					43
#define  PIC_A						44
#define  PIC_B						45
#define  PIC_C						46
#define  PIC_D					47
#define  PIC_E						48
#define  PIC_F						49
#define  PIC_G					50
#define  PIC_H					51
#define  PIC_HRO_1			55//5
#define  PIC_HRO_2			60
#define  PIC_HRO_3			65
#define  BG_4						66
#define  BG_5						67
#define  BG_6						68

#define PIC_DIEBOOM		70//6

#define PIC_SAVEPOINT		76//9

#define  PIC_GUICL_1			90
#define  PIC_GUICL_2			91
#define  PIC_GUICL_3			92
#define  PIC_GUICL_4			93
#define  PIC_GUICL_5			94
#define  PIC_GUICL_6			95
#define  PIC_GUICL_7			96
#define  PIC_GUICL_8			97
#define  PIC_GUICL_9			98

#define PIC_DAPAO			99
#define PIC_HUOQIU			100
#define PIC_HP					101

#define PIC_LZ1					102//Á£×Ó
#define PIC_LZ2					103
#define PIC_LZ3					104
#define PIC_LZ4					105
#define PIC_WATER			106
#define PIC_EMFUEL			107
#define PIC_FUEL				108

#define  PIC_BTN_1_1			110//1Õý³£2ÐüÍ£3°´ÏÂ
#define  PIC_BTN_1_2			111
#define  PIC_BTN_1_3			112
#define  PIC_BTN_2_1			113
#define  PIC_BTN_2_2			114
#define  PIC_BTN_2_3			115
#define  PIC_BTN_3_1			116
#define  PIC_BTN_3_2			117
#define  PIC_BTN_3_3			118
#define  PIC_LEVELBTN		119

#define  PIC_EFF1				150
#define  PIC_EFF2				151//9
#define  PIC_EFF3				160//6
#define  PIC_EFF4				166
#define  PIC_EFF5				167
#define  PIC_EFF6				168
#define  PIC_EFF7				169

#define  PIC_GGP				200
#define  PIC_GGPRMD		203

#define  PIC_GUILIGHT		220
#define  PIC_GUITS				221

#define  PIC_GUIBG			300
#define  PIC_MG					301

#define  SQ_WHITE				400
#define  SQ_RED					401
///////////////////////////////////////////////////////////////////////////////////////
#define  FT_YY					L"Ó×Ô²"			
#define  FT_WRYH				L"Î¢ÈíÑÅºÚ"  
//#define  FT_YY 1
//#define  FT_YY 1
//#define  FT_YY 1
//#define  FT_YY 1

#define  BRS_WHITE			1
#define  BRS_BLACK			2
///////////////////////////////////////////////////////////////////////////////////////



#endif