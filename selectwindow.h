#pragma once
#include<graphics.h>
#include"playlistmanager.h"
#include"util.h"
extern playlistmanager* playlist_manager;
extern IMAGE mask_img;
//extern int mousex,mousey;
class selectwindow{
public:
	selectwindow(){

	}
	~selectwindow()=default;
	int work(std::string tip){
		drawAlpha(&mask_img,0,0);
		FlushBatchDraw();
		int posx=280,posy=140;
		int width=400,height=360;
		int texth=30;int gap=4;
		int nowpage=0;int n=(int)playlist_manager->data.size();
		int itemn=8;
		int maxpage=(int)ceil((double)n/itemn);
		int nowpagen=n-nowpage*itemn>itemn?itemn:n-nowpage*itemn;
		int currentin=-1;
		settextstyle(texth,0,"Consolas");
		ExMessage msg;
		bool flag=true;
		while(flag){
			while(peekmessage(&msg)){
				if(msg.message==WM_LBUTTONDOWN){
					if(posx+width-texth<=msg.x&&msg.x<=posx+width&&posy<=msg.y&&msg.y<=posy+texth||!(posx<=msg.x&&msg.x<=posx+width&&posy<=msg.y&&msg.y<=posy+height)){
						return -1;
					} else
						if(posx<=msg.x&&msg.x<=posx+width&&posy+2*texth<=msg.y&&msg.y<=posy+(2+nowpagen)*texth){
							return (msg.y-posy-2*texth)/texth+nowpage*itemn;
						}
				} else
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
					} else
						if(msg.message==WM_MOUSEMOVE){
							if(posx<=msg.x&&msg.x<=posx+width&&posy+2*texth<=msg.y&&msg.y<=posy+height){
								int dy=msg.y-posy-2*texth;
								int n=dy/texth;
								if(n<itemn){
									currentin=n;
								} 
								if(n<0){
									currentin=-1;
								}

							}else
								currentin=-1;
							std::cout<<currentin;
						}
					setfillcolor(0xffffff);
					solidrectangle(posx,posy,posx+width,posy+height);
					settextcolor(BLACK);
					outtextxy(posx,posy,tip.c_str());
					setlinecolor(BLACK);
					line(posx+width-texth+gap,posy+gap,posx+width-gap,posy+texth-gap);
					line(posx+width-texth+gap,posy+texth-gap,posx+width-gap,posy+gap);
					int inity=posy+2*texth;
					for(int i=nowpage*itemn,k=0;i<(nowpage+1)*itemn;i++,k++){
						if(i>=n)
							break;
						settextcolor(BLACK);
						if(k==currentin){
							settextcolor(GREEN);
						}
						
						outtextxy(posx,inity,playlist_manager->data[i]->listname.c_str());
						inity+=texth;
					}
					nowpagen=n-nowpage*itemn>itemn?itemn:n-nowpage*itemn;
					FlushBatchDraw();
			}
		}
	}
};