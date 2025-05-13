#pragma once
#include<graphics.h>
#include"playlistmanager.h"
#include"util.h"
extern playlistmanager* playlist_manager;
extern IMAGE mask_img;
class selectwindow{
public:
	selectwindow(){

	}
	~selectwindow()=default;
	int work(std::string tip){
		drawAlpha(&mask_img,0,0);
		FlushBatchDraw();
		int mousex=0,mousey=0;
		int posx=235,posy=120;
		int width=200,height=240;
		int texth=20;int gap=4;
		int nowpage=0;int n=(int)playlist_manager->data.size();
		int itemn=8;
		int maxpage=(int)ceil((double)n/itemn);
		int nowpagen=n-nowpage*itemn>itemn?itemn:n-nowpage*itemn;
		settextstyle(texth,0,"Consolas");
		ExMessage msg;
		bool flag=true;
		while(flag){
			while(peekmessage(&msg)){
				if(msg.message==WM_LBUTTONDOWN){
					if(posx+width-texth<=msg.x&&msg.x<=posx+width&&posy<=msg.y&&msg.y<=posy+texth||!(posx<=msg.x&&msg.x<=posx+width&&posy<=msg.y&&msg.y<=posy+height)){
						return -1;
					}else
						if(posx<=msg.x&&msg.x<=posx+width&&posy+2*texth<=msg.y&&msg.y<=posy+(2+nowpagen)*texth){
							return (msg.y-posy-2*texth)/texth+nowpage*itemn;
						}
				}else
					if(msg.message==WM_MOUSEWHEEL){
						if(msg.wheel<0){
							nowpage++;
							if(nowpage>=maxpage)
								nowpage=maxpage-1;
						}
						if(msg.wheel>0){
							nowpage--;
							if(nowpage<0)
								nowpage=0;
						}
					}
			}
			setfillcolor(0xb6dde9);
			solidrectangle(posx,posy,posx+width,posy+height);
			outtextxy(posx,posy,tip.c_str());
			setlinecolor(BLACK);
			line(posx+width-texth+gap,posy+gap,posx+width-gap,posy+texth-gap);
			line(posx+width-texth+gap,posy+texth-gap,posx+width-gap,posy+gap);
			int inity=posy+2*texth;
			for(int i=nowpage*itemn;i<(nowpage+1)*itemn;i++){
				if(i>=n)
					break;
				outtextxy(posx,inity,playlist_manager->data[i]->listname.c_str());
				inity+=texth;
			}
			nowpagen=n-nowpage*itemn>itemn?itemn:n-nowpage*itemn;
			FlushBatchDraw();
		}
		return 1;
	}
};