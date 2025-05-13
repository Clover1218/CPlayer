#pragma once
#include"playbutton.h"
extern int mousex,mousey;
class progressbar{
public:
	progressbar(int px,int py,int w,int h,int g){
		posx=px;posy=py;width=w;height=h;gap=g;
		settextstyle(20,0,_T("Consolas"));
		timelength=textwidth("00:00");
	}
	void draw(){
		char pos[100]={'#'};
		if(mciSendString("status music mode",pos,100,0)==0&&!isdrag){
			mciSendString("status music position",pos,100,0);
			currenttime=atoi(pos);
			mciSendString("status music length",pos,100,0);
			totaltime=atoi(pos);
		}
		settextstyle(20,0,_T("Consolas"));
		settextcolor(BLACK);
		outtextxy(posx,posy,tommss(currenttime).c_str());

		outtextxy(posx+width-timelength,posy,tommss(totaltime).c_str());
		setlinecolor(BLACK);
		line(posx+timelength+gap,posy+height/2,posx+width-timelength-gap,posy+height/2);
		setlinecolor(WHITE);
		line(posx+timelength+gap,posy+height/2,posx+timelength+gap+(int)((double)(width-2*timelength-2*gap)/totaltime*currenttime),posy+height/2);
		

	}
	void process_drag(ExMessage& msg){
		if(posx+timelength+gap<=mousex&&mousex<=posx+width-timelength-gap&&posy<=mousey&&mousey<=posy+height){
			int changetime=(int)((double)(mousex-posx-timelength-gap)/(width-2*timelength-2*gap)*totaltime);
			if(msg.message==WM_LBUTTONDOWN){
				if(!isdrag)
					mciSendString("pause music",0,0,0);
				currenttime=changetime;
				isdrag=true;
			}else
				if(msg.message==WM_MOUSEMOVE){
					currenttime=changetime;
				}else
					if(msg.message==WM_LBUTTONUP){
						isdrag=false;
						char command[100];
						sprintf_s(command,"seek music to %d",changetime);
						mciSendString(command,0,0,0);
						mciSendString("play music",0,0,0);
					}
		}
	}
	std::string tommss(int t){
		int mm=t/1000/60,ss=t/1000%60; 
		std::string out;
		if(mm<10)
			out+='0';
		out+=std::to_string(mm);
		out+=':';
		if(ss<10)
			out+='0';
		out+=std::to_string(ss);
		return out;
	}
private:
	int posx,posy;
	int width,height;
	int timelength;
	int currenttime=0;
	int totaltime=0;
	int gap;
	bool isdrag=false;
};