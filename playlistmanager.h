#pragma once
#include"musicidlist.h"
#include<vector>
class playlistmanager{
public:
	playlistmanager(int x,int y,int w,int h,int th){
		data.push_back(new musicidlist("默认列表",0));
		data.push_back(new musicidlist("中文歌",1));
		data.push_back(new musicidlist("英文歌",2));
		data.push_back(new musicidlist("日文歌",3));
		data.push_back(new musicidlist("纯音乐",4));
		texth=textheight("L");
		posx=x;posy=y;width=w;height=h;viewy=0;
	}
	void add(std::string name){
		data.push_back(new musicidlist(name,(int)data.size()));
	}
	
	void draw(){
		if(!isshow) return;
		settextstyle(20,0,"Consolas");
		int inity=posy-viewy,i=0;
		POINT tr[3];
		for(auto e:data){
			tr[0]={posx+gap,inity+gap};
			tr[1]={posx+texth-gap,inity+texth/2};
			tr[2]={posx+gap,inity+texth-gap};
			const char* sn=e->listname.c_str();
			settextcolor(BLACK);
			if(i==currentselect){
				setlinecolor(BLACK);
				polygon(tr,3);
			}
			outtextxy(posx+texth,inity,sn);
			inity+=textheight(sn);
			i++;
		}
	}
	void process_wheel(int wheel){
		if(!isshow) return;
		if(posx<=mousex&&mousex<=posx+width&&posy<=mousey&&mousey<=posy+height){
			if((int)data.size()*texth>height){
				viewy-=wheel/4;
				if(viewy<0)
					viewy=0;
				if(viewy>(int)data.size()*texth-height)
					viewy=(int)data.size()*texth-height;
			}
		}
	}
	void process_click(){
		if(!isshow) return;
		if(posx<=mousex&&mousex<=posx+width&&posy<=mousey&&mousey<=posy+height){
			int dy=mousey-posy+viewy;
			int n=dy/texth;
			if(n<(int)data.size()){
				currentselect=n;
			}

		}

		return;
	} 
	void process_mouse_move(){
		if(!isshow) return;
		if(posx<=mousex&&mousex<=posx+width&&posy<=mousey&&mousey<=posy+height){
			int dy=mousey-posy+viewy;
			int n=dy/texth;
		} 
	}
	std::vector<musicidlist*> data;
	int posx;
	int posy;
	int width;
	int height;	
	int viewy;
	int texth;
	int gap=2;
	int currentselect=0;
	bool isshow=true;
};