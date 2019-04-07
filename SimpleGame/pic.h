#include <windows.h>
#include <wincodec.h>
#include <D2D1.h>
#include<DWrite.h>
#define SAFE_RELEASE(P) if(P){P->Release() ; P = NULL ;}
#define PICNUM 1000//max picture number
#define CLSCR_WHITE 1
#define CLSCR_BLACK 2
//依赖项
#pragma comment(lib,"Windowscodecs.lib")

#ifndef PIC_H
#define PIC_H
class PicEdit
{
private:
	static PicEdit *instance;

	ID2D1Factory*				pD2DFactory;
	ID2D1HwndRenderTarget*		pKey;	
	ID2D1BitmapRenderTarget*	pBRT;	
	ID2D1Bitmap*				pPic[PICNUM];
	ID2D1BitmapBrush*			pPicB[PICNUM];
	IDWriteTextFormat*			pFont;
	ID2D1SolidColorBrush*		Brush;
	IWICImagingFactory*			pWICFactory;
	IDWriteFactory*				pWFactory;
	IDWriteTextLayout*			texts;
	void						CPicBrush(int ID){pKey->CreateBitmapBrush(pPic[ID],&pPicB[ID]);}
	void						DPicBrush(int ID){SAFE_RELEASE(pPicB[ID])}
public:
	PicEdit(HWND hWnd,float gx=0,float gy=0,float gw=0,float gh=0)
	{
		pKey=NULL;RECT rc;pWFactory=NULL;texts=NULL;
		D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory);
		CoCreateInstance(CLSID_WICImagingFactory,NULL,
						 CLSCTX_INPROC_SERVER,IID_IWICImagingFactory,
					     reinterpret_cast<void **>(&pWICFactory));
		if(gx==0&&gy==0&&gw==0&&gh==0){GetClientRect(hWnd, &rc);}
		else{rc.left=gx;rc.bottom=gy+gh;rc.right=gx+gw;rc.top=gy;}
		pD2DFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(),
											D2D1::HwndRenderTargetProperties(hWnd, 
											D2D1::SizeU(rc.right - rc.left,rc.bottom - rc.top)), 
											&pKey);
		pKey->CreateCompatibleRenderTarget(&pBRT);
		DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,	__uuidof(IDWriteFactory),
						    reinterpret_cast<IUnknown**>(&pWFactory));

		for(int i=0;i<PICNUM;i++){pPic[i]=NULL;pPicB[i]=NULL;}
		pFont=NULL;Brush=NULL;
	}
	~PicEdit()
	{
		SAFE_RELEASE(pKey);
		SAFE_RELEASE(pD2DFactory);
		SAFE_RELEASE(pWICFactory);
		SAFE_RELEASE(pWFactory);
	}
	static void		  Init(HWND hwnd) { instance = new PicEdit(hwnd); }
	static PicEdit*   GetInstance() { return instance; }
	void        Begin(int mode=CLSCR_WHITE)
	{
		pKey->BeginDraw();
		switch(mode)
		{
		case 1:
			pKey->Clear(D2D1::ColorF(D2D1::ColorF::White));
		case 2:
			pKey->Clear(D2D1::ColorF(D2D1::ColorF::Black));
		}
	}
	void        End()
	{
		 pKey->EndDraw() ;
	}
	bool        Check(int ID){return pPic[ID];}
	HRESULT		Load(LPCWSTR name,int ID,bool ifcreatebrush=false,UINT destinationWidth=0,
									UINT destinationHeight=0)  
{
	HRESULT hr = S_OK;
	ID2D1Bitmap **ppBitmap=&pPic[ID];
	IWICBitmapDecoder *pDecoder = NULL;
	IWICBitmapFrameDecode *pSource = NULL;
	IWICStream *pStream = NULL;
	IWICFormatConverter *pConverter = NULL;
	IWICBitmapScaler *pScaler = NULL;
	hr = pWICFactory->CreateDecoderFromFilename(
		name,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&pDecoder
		);
	if (SUCCEEDED(hr))
	{	// Create the initial frame.
		hr = pDecoder->GetFrame(0, &pSource);
	}

	if (SUCCEEDED(hr))
	{	// Convert the image format to 32bppPBGRA
		// (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
		hr = pWICFactory->CreateFormatConverter(&pConverter);
	}
	if (SUCCEEDED(hr))
	{	// If a new width or height was specified, create an
		// IWICBitmapScaler and use it to resize the image.
		if (destinationWidth != 0 || destinationHeight != 0)
		{
			UINT originalWidth, originalHeight;
			hr = pSource->GetSize(&originalWidth, &originalHeight);
			if (SUCCEEDED(hr))
			{
				if (destinationWidth == 0)
				{
					FLOAT scalar = static_cast<FLOAT>(destinationHeight) / static_cast<FLOAT>(originalHeight);
					destinationWidth = static_cast<UINT>(scalar * static_cast<FLOAT>(originalWidth));
				}
				else if (destinationHeight == 0)
				{
					FLOAT scalar = static_cast<FLOAT>(destinationWidth) / static_cast<FLOAT>(originalWidth);
					destinationHeight = static_cast<UINT>(scalar * static_cast<FLOAT>(originalHeight));
				}

				hr = pWICFactory->CreateBitmapScaler(&pScaler);
				if (SUCCEEDED(hr))
				{
					hr = pScaler->Initialize(
						pSource,
						destinationWidth,
						destinationHeight,
						WICBitmapInterpolationModeCubic
						);
				}
				if (SUCCEEDED(hr))
				{
					hr = pConverter->Initialize(
						pScaler,
						GUID_WICPixelFormat32bppPBGRA,
						WICBitmapDitherTypeNone,
						NULL,
						0.f,
						WICBitmapPaletteTypeMedianCut
						);
				}
			}
		}
		else // Don't scale the image.
		{
			hr = pConverter->Initialize(
				pSource,
				GUID_WICPixelFormat32bppPBGRA,
				WICBitmapDitherTypeNone,
				NULL,
				0.f,
				WICBitmapPaletteTypeMedianCut
				);
		}
	}
	if (SUCCEEDED(hr))
	{
		// Create a Direct2D bitmap from the WIC bitmap.
		hr = pKey->CreateBitmapFromWicBitmap(
			pConverter,
			NULL,
			ppBitmap
			);
	}
	SAFE_RELEASE(pDecoder);
	SAFE_RELEASE(pSource);
	SAFE_RELEASE(pStream);
	SAFE_RELEASE(pConverter);
	SAFE_RELEASE(pScaler);
	if(ifcreatebrush){CPicBrush(ID);}
	return hr;
}
	void		CFont(LPCWSTR font,float size,LPCWSTR bz)
	{
		pWFactory->CreateTextFormat(
					font,		                   // Font family name
					NULL,                          // Font collection(NULL sets it to the system font collection)
					DWRITE_FONT_WEIGHT_REGULAR,    // Weight
					DWRITE_FONT_STYLE_NORMAL,      // Style
					DWRITE_FONT_STRETCH_NORMAL,    // Stretch
					size,                         // Size    
					bz,                      // Local
					&pFont);
	}
	void		CBrush(float r=0,float g=0,float b=0,float tr=1.0f)
	{
		pKey->CreateSolidColorBrush(
		D2D1::ColorF(r,g,b, tr),
		&Brush);
	}
	void		DFont(){SAFE_RELEASE(pFont)}
	void		DBrush(){SAFE_RELEASE(Brush)}
	void		Delete(int ID)
	{
			SAFE_RELEASE(pPic[ID])
			if(pPicB[ID])
			{DPicBrush(ID);}
	}
	void		TextL(float x,float y,LPCWSTR context,int size,LPCWSTR Font,D2D1_COLOR_F color)
	{
		CBrush(color.r,color.g,color.b,color.a);
		LPCWSTR bz=L"hrwh";
		CFont(Font,size,bz);
		pKey->DrawText(
	    context,           // Text to render
	    wcslen(context),				   // Text length
	    pFont,		   // Text format
		D2D1::RectF(x,y,x+size*wcslen(context),y),    // The region of the window where the text will be rendered
	    Brush);			   // The brush used to draw the text
		DBrush();DFont();
	}
	int			TextS(float x,float y,float w,float h,LPCWSTR context,int size,LPCWSTR Font,D2D1_COLOR_F color,bool get=false)
	{
		CBrush(color.r,color.g,color.b,color.a);CFont(Font,size,L"hrwh");if(w<0){w=-w;}if(h<0){h=-h;}
		if(get){pWFactory->CreateTextLayout(context,wcslen(context),pFont,w,h,&texts);
		DWRITE_TEXT_METRICS textw;texts->GetMetrics(&textw);int lh=textw.height,lw=textw.width;
		SAFE_RELEASE(texts);return lw*10000+lh;}
		if(!get){pKey->DrawText(context,wcslen(context),pFont,D2D1::RectF(x,y,x+w,y+h),Brush);}
		DBrush();DFont();
		return 0;
	}
	void		Blt(int ID,
					float x,float y,float w,float h,	//目标区域
					float yx=0,float yy=0,float yw=0,float yh=0,//源区域
					float tr=1.0f					//透明度
					)
	{
		D2D1_RECT_F rq = D2D1::RectF(x,y,x+w,y+h);
		D2D1_RECT_F yj=  D2D1::RectF(yx,yy,yx+yw,yy+yh);
		if(yx==0&&yy==0&&yw==0&&yh==0)
		{pKey->DrawBitmap(pPic[ID],rq,tr,D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);}
		else{pKey->DrawBitmap(pPic[ID],rq,tr,D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,yj);
		}
	}
	void        BBlt(int ID,
					float x,float y,float w,float h,	//目标区域
					float yx,float yy,float yw,float yh,//源区域
					float jd=0,float xx=0,float xy=0
					)
	{	
		pPicB[ID]->SetTransform(D2D1::Matrix3x2F::Scale(w/yw,h/yh,D2D1::Point2F(yx,yy))
			*(D2D1::Matrix3x2F::Translation(D2D1::SizeF(x-yx,y-yy)))
			*(D2D1::Matrix3x2F::Rotation(jd,D2D1::Point2F(xx,xy)))
			);

		ID2D1RectangleGeometry *tarea;
		ID2D1TransformedGeometry *area;
		pD2DFactory->CreateRectangleGeometry(&D2D1::RectF(x,y,x+w,y+h),&tarea);
		pD2DFactory->CreateTransformedGeometry(tarea,(D2D1::Matrix3x2F::Rotation(jd,D2D1::Point2F(xx,xy))),&area);
		//pKey->FillRectangle(D2D1::RectF(x,y,x+w,y+h),pPicB[ID]);
		pKey->FillGeometry(area,pPicB[ID]);
		SAFE_RELEASE(tarea);
		SAFE_RELEASE(area);

		pPicB[ID]->SetTransform(D2D1::Matrix3x2F::Identity());
	}
	void		changeAngle(float jd=0,float xx=0,float xy=0)	//旋转角度及中心
	{
		if(jd!=0)
			pKey->SetTransform(D2D1::Matrix3x2F::Rotation(jd,D2D1::Point2F(xx, xy)));
	}
	void		changeSize(float size=0,float zx=0,float zy=0) //放大倍数及中心
	{if(size!=0)
		{pKey->SetTransform(D2D1::Matrix3x2F::Scale(size,size,D2D1::Point2F(zx, zy)));}
	}
};
PicEdit* PicEdit::instance = NULL;
#endif
						
				