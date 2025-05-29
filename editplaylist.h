#pragma once
#include<graphics.h>
#include"playlistmanager.h"
#include"musicidlist.h"
#include"util.h"
#include"selectwindow.h"
extern playlistmanager* playlist_manager;
extern IMAGE add_img;
extern IMAGE delete_img;
extern IMAGE rename_img;
extern int mousex,mousey;
class editplaylist{
public:
	editplaylist(int x,int y,int w,int h,int th){
		posx=x;posy=y;width=w;height=h;
		texth=th;		
	}
	void draw(){
		if(!isshow) return;
		settextstyle(height,0,"Consolas");
		outtextxy(posx,posy,playlist_manager->data[playlist_manager->currentselect]->listname.c_str());
		putImageAlpha(posx+width-texth,posy,&delete_img);
		putImageAlpha(posx+width-2*texth,posy,&add_img);
		putImageAlpha(posx+width-3*texth,posy,&rename_img);
	}
	void process_click(){
		if(posx<=mousex&&mousex<=posx+width&&posy<=mousey&&mousey<=posy+height){
			if(posx+width-texth<=mousex&&mousex<=posx+width&&posy<=mousey&&mousey<=posy+height){
		//				bindlist->data.erase(bindlist->data.begin()+cur);
		//if(cur==play_button->playcurrentselect){
		//	if(cur>=bindlist->data.size()){
		//		currentin=currentselect=0;
		//	}
		//	play_button->play(bindlist->data[cur].id,cur);
		//}
		//if(cur<currentselect){
		//	currentselect--;
		//	play_button->playcurrentselect--;
			currentin=playlist_manager->currentselect;
			if(currentin==0)	return;
			delete playlist_manager->data[currentin];
			playlist_manager->data.erase(playlist_manager->data.begin()+currentin);
			if(currentin>=(int)playlist_manager->data.size())
				playlist_manager->currentselect--;
			}else
				if(posx+width-2*texth<=mousex&&mousex<=posx+width-texth&&posy<=mousey&&mousey<=posy+height){
					selectwindow* s=new selectwindow();
					int ans=s->work("将该歌单添加至...");
					delete s;
					if(ans!=-1&&ans!=playlist_manager->currentselect){
						for(auto m:playlist_manager->data[playlist_manager->currentselect]->data){
							playlist_manager->data[ans]->add(m.id,m.name);
						}
					}
				}else
					if(posx+width-3*texth<=mousex&&mousex<=posx+width-texth*2&&posy<=mousey&&mousey<=posy+height){
						CHAR a[300]={'#'};
						InputBox(a,200,"输入当前歌单新名字","CPlayer",playlist_manager->data[playlist_manager->currentselect]->listname.c_str(),0,0,false);
						if(a[0]!='#'){
							std::string pa=a;
							playlist_manager->data[playlist_manager->currentselect]->listname=pa;

						}
					}
		}
	}
	int posx;
	int posy;
	int width;
	int height;	
	int viewy;
	int texth;
	int gap=2;
	int currentin;
	bool isshow=true;

	
};