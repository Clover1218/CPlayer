#pragma once
#include<graphics.h>
#include"playlistmanager.h"
#include"musicidlist.h"
#include"util.h"
#include"selectwindow.h"
#include"utility"
extern playlistmanager* playlist_manager;
extern IMAGE add_img;
extern IMAGE delete_img;
extern IMAGE rename_img;
extern IMAGE play_icon_img;
extern IMAGE up_img;
extern IMAGE down_img;
extern currentplaylist* current_playlist;
class editlist{
public:
	editlist(int x,int y,int w,int h,int th,musicidlist* bl){
		posx=x;posy=y;width=w;height=h;viewy=0;
		bindlist=bl;
		texth=textheight("L");		
	}
	void draw(){
		if(!isshow) return;
		settextstyle(20,0,"Consolas");
		int inity=posy-viewy,i=0;
		for(musicidlistitem e:bindlist->data){
			settextcolor(BLACK);
			const char* sn=e.name.c_str();
			outtextxy(posx+texth,inity,sn);
			if(i==currentin){
				putImageAlpha(posx+width-texth,inity,&delete_img);
				putImageAlpha(posx+width-2*texth,inity,&add_img);
				putImageAlpha(posx+width-3*texth,inity,&rename_img);
				putImageAlpha(posx+width-4*texth,inity,&play_icon_img);
				putImageAlpha(posx+width-5*texth,inity,&down_img);
				putImageAlpha(posx+width-6*texth,inity,&up_img);
			}
			inity+=textheight(sn);
			i++;
		}
	}
	void process_mouse_move(){
		if(!isshow) return;
		if(posx<=mousex&&mousex<=posx+width&&posy<=mousey&&mousey<=posy+height){
			int dy=mousey-posy+viewy;
			int n=dy/texth;
			if(n<bindlist->data.size()){
				currentin=n;
			}
		}else{
			currentin=-1;
		}
	}
	void process_click(){
		if(posx<=mousex&&mousex<=posx+width&&posy<=mousey&&mousey<=posy+height){
			if(posx+width-texth<=mousex&&mousex<=posx+width&&posy<=mousey&&mousey<=posy+height){
				if(bindlist==current_playlist->bindlist){
					if(currentin>=0&&currentin<=(int)bindlist->data.size()){
						current_playlist->del(currentin);
					}
				}
				else{
					bindlist->data.erase(bindlist->data.begin()+currentin);
				}
			}else
				if(posx+width-2*texth<=mousex&&mousex<=posx+width-texth&&posy<=mousey&&mousey<=posy+height){
					selectwindow* s=new selectwindow();
					int ans=s->work("将该歌曲添加至...");
					delete s;
					if(ans!=-1)
						playlist_manager->data[ans]->data.push_back(bindlist->data[currentin]);
				}else
					if(posx+width-3*texth<=mousex&&mousex<=posx+width-texth*2&&posy<=mousey&&mousey<=posy+height){
						CHAR a[300]={'#'};
						InputBox(a,200,"输入当前音乐新名字","CPlayer",bindlist->data[currentin].name.c_str(),0,0,false);
						if(a[0]!='#'){
							std::string pa=a;
							bindlist->data[currentin].name=pa;

						}
					}else
						if(posx+width-4*texth<=mousex&&mousex<=posx+width-texth*3&&posy<=mousey&&mousey<=posy+height){
							if(bindlist==current_playlist->bindlist){
								current_playlist->play_button->play(current_playlist->bindlist->data[currentin].id,currentin);
								return;
							}
							current_playlist->bindlist->data.push_back(bindlist->data[currentin]);
							current_playlist->play_button->play(current_playlist->bindlist->data[current_playlist->bindlist->data.size()-1].id,(int)current_playlist->bindlist->data.size()-1);
						}else
							if(posx+width-5*texth<=mousex&&mousex<=posx+width-texth*4&&posy<=mousey&&mousey<=posy+height){
								//down
								int downid=(currentin+1)%(int)bindlist->data.size();
								std::swap(bindlist->data[downid],bindlist->data[currentin]);
							}else
								if(posx+width-6*texth<=mousex&&mousex<=posx+width-texth*5&&posy<=mousey&&mousey<=posy+height){
									int upid=(currentin-1+(int)bindlist->data.size())%(int)bindlist->data.size();
									std::swap(bindlist->data[upid],bindlist->data[currentin]);
								}
					
		}
	}
	void process_wheel(int wheel){
		if(!isshow) return;
		if(posx<=mousex&&mousex<=posx+width&&posy<=mousey&&mousey<=posy+height){
			if((int)bindlist->data.size()*texth>height){
				viewy-=wheel/4;
				if(viewy<0)
					viewy=0;
				if(viewy>(int)bindlist->data.size()*texth-height)
					viewy=(int)bindlist->data.size()*texth-height;
			}
		}
	}
	void update(){
		if(bindlist!=playlist_manager->data[playlist_manager->currentselect]){
			bindlist=playlist_manager->data[playlist_manager->currentselect];
			viewy=0;
		}

	}
	std::vector<musicidlist*> data;
	musicidlist* bindlist;
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