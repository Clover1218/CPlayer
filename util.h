#pragma once
#include<conio.h>
#include<graphics.h>
#include<filesystem>
#include<string>
namespace fs=std::filesystem;
#pragma comment(lib, "MSIMG32.LIB")
static void drawAlpha(IMAGE* picture, int  picture_x, int picture_y) //xΪ����ͼƬ��X���꣬yΪY����
{

	// ������ʼ��
	DWORD *dst = GetImageBuffer();    // GetImageBuffer()���������ڻ�ȡ��ͼ�豸���Դ�ָ�룬EASYX�Դ�
	DWORD *draw = GetImageBuffer(); 
	DWORD *src = GetImageBuffer(picture); //��ȡpicture���Դ�ָ��
	int picture_width = picture->getwidth(); //��ȡpicture�Ŀ�ȣ�EASYX�Դ�
	int picture_height = picture->getheight(); //��ȡpicture�ĸ߶ȣ�EASYX�Դ�
	int graphWidth = getwidth();       //��ȡ��ͼ���Ŀ�ȣ�EASYX�Դ�
	int graphHeight = getheight();     //��ȡ��ͼ���ĸ߶ȣ�EASYX�Դ�
	int dstX = 0;    //���Դ������صĽǱ�

	// ʵ��͸����ͼ ��ʽ�� Cp=��p*FP+(1-��p)*BP �� ��Ҷ˹���������е���ɫ�ĸ��ʼ���
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //���Դ������صĽǱ�
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA��͸����
			int sr = ((src[srcX] & 0xff0000) >> 16); //��ȡRGB���R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + picture_x) + (iy + picture_y) * graphWidth; //���Դ������صĽǱ�
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //��ʽ�� Cp=��p*FP+(1-��p)*BP  �� ��p=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //��p=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //��p=sa/255 , FP=sb , BP=db
			}
		}
	}
}
static void flip_image(IMAGE* src,IMAGE* dst){
	int h=src->getheight(),w=src->getwidth();
	Resize(dst,h,w);
	DWORD* srcb=GetImageBuffer(src);
	DWORD* dstb=GetImageBuffer(dst);
	for(int y=0;y<h;y++){
		for(int x=0;x<w;x++){
			dstb[y*w+x]=srcb[y*w+w-x-1];
		}
	}
}
static void putImageAlpha(int x, int y, IMAGE* img) {
	int w = img->getwidth();
	int h = img->getheight();

	//auto cameraX = Camera::getCamera().getPostion().x;
	//auto cameraY = Camera::getCamera().getPostion().y;
	AlphaBlend(GetImageHDC(nullptr), x , y , w, h,
		GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255, AC_SRC_ALPHA });
	
}
static std::string utf8ToGbk(const std::string& utf8Str) {
    int wideLen=MultiByteToWideChar(CP_UTF8,0,utf8Str.c_str(),-1,nullptr,0);
    std::wstring wideStr(wideLen, 0);
    MultiByteToWideChar(CP_UTF8,0,utf8Str.c_str(),-1,&wideStr[0],wideLen);
    int gbkLen=WideCharToMultiByte(CP_ACP,0,wideStr.c_str(),-1,nullptr,0,nullptr,nullptr);
    std::string gbkStr(gbkLen, 0);
    WideCharToMultiByte(CP_ACP,0,wideStr.c_str(),-1,&gbkStr[0],gbkLen,nullptr,nullptr);
    gbkStr.pop_back();
    return gbkStr;
}
