#pragma once
#include"playbutton.h"
extern int mousex,mousey;
class volumebar{
public:
	volumebar(int px,int py,int w,int h,int g,IMAGE* i){
		posx=px;posy=py;width=w;height=h;gap=g;
		settextstyle(20,0,_T("Consolas"));
		image=i;
		iconlength=30;
	}
	void draw(){
		char pos[100]={'#'};
		settextstyle(20,0,_T("Consolas"));
		putImageAlpha(posx,posy,image);
		setlinecolor(BLACK);
		line(posx+iconlength+gap,posy+height/2,posx+width,posy+height/2);
		setlinecolor(WHITE);
		line(posx+iconlength+gap,posy+height/2,posx+iconlength+gap+current*(width-gap-iconlength)/total,posy+height/2);
	}
	void process_drag(ExMessage& msg){
		int changevolume=(mousex-posx-iconlength-gap)*total/(width-iconlength-gap);
		if(msg.message==WM_LBUTTONUP){
			if(isdrag){
				isdrag=false;
				setvolume(changevolume);
			}
		}else
			if(msg.message==WM_MOUSEMOVE){
				if(isdrag&&posx+iconlength+gap<=mousex&&mousex<=posx+width)
					setvolume(changevolume);
			}
		if(posx+iconlength+gap<=mousex&&mousex<=posx+width&&posy<=mousey&&mousey<=posy+height){
			if(msg.message==WM_LBUTTONDOWN){
				if(!isdrag)
					setvolume(changevolume);
				isdrag=true;
			}
		}
	}
	void setvolume(int v){
		char a[100];
		current=v;
		sprintf_s(a,"setaudio music volume to %d",v);
		mciSendString(a,0,0,0);
	}
	int getvolume(){
		char a[100];
		mciSendString("status music volume", a, 100, 0);
		int b=atoi(a);
		return b%1000+200;
	}
	int current=500;
private:
	int posx,posy;
	int width,height;
	int iconlength;
	int total=1000;
	int gap;
	bool isdrag=false;
	IMAGE* image;
};