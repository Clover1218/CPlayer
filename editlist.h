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
	editlist(int x,int y,int w,int h,int th,int dw,musicidlist* bl){
		posx=x;posy=y;width=w;height=h;viewy=0;
		bindlist=bl;
		dragwidth=dw;
		texth=th;		
	}
	void draw(){
		if(!isshow) return;
		settextstyle(texth,0,"Consolas");
		int inity=posy-viewy,i=0;
		for(musicidlistitem e:bindlist->data){
			if(i%2==0){
				setfillcolor(0xF5F5F5);
			}else{
				setfillcolor(0xFFFFFF);
			}//EEEEEE
			if(i==currentin){
				setfillcolor(0xEEEEEE);
			}
			solidrectangle(posx+texth,inity,posx+width,inity+texth);
			settextcolor(BLACK);
			const char* sn=e.name.c_str();
			outtextxy(posx+texth,inity,sn);
			if(i==currentin){
				putImageAlpha(posx+width-texth-dragwidth,inity,&delete_img);
				putImageAlpha(posx+width-2*texth-dragwidth,inity,&add_img);
				putImageAlpha(posx+width-3*texth-dragwidth,inity,&rename_img);
				putImageAlpha(posx+width-4*texth-dragwidth,inity,&play_icon_img);
				putImageAlpha(posx+width-5*texth-dragwidth,inity,&down_img);
				putImageAlpha(posx+width-6*texth-dragwidth,inity,&up_img);
			}
			inity+=textheight(sn);
			i++;
		}
		int totalheight=bindlist->data.size()*texth<height?height:bindlist->data.size()*texth;
		setfillcolor(WHITE);
		solidrectangle(posx+width-dragwidth,posy,posx+width,posy+height);
		setfillcolor(0xC2C2C2);
		solidrectangle(posx+width-dragwidth,posy+viewy*height/totalheight,posx+width,posy+(viewy+height)*height/totalheight);
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
	void process_click(ExMessage& msg){
		if(!isshow) return;
		if(msg.message==WM_LBUTTONDOWN){
			if(posx<=mousex&&mousex<=posx+width&&posy<=mousey&&mousey<=posy+height){
				if(posx+width-texth-dragwidth<=mousex&&mousex<=posx+width-dragwidth&&posy<=mousey&&mousey<=posy+height){
					if(bindlist==current_playlist->bindlist){
						if(currentin>=0&&currentin<=(int)bindlist->data.size()){
							current_playlist->del(currentin);
						}
					}
					else{
						bindlist->data.erase(bindlist->data.begin()+currentin);
					}
				}else
					if(posx+width-2*texth-dragwidth<=mousex&&mousex<=posx+width-texth-dragwidth&&posy<=mousey&&mousey<=posy+height){
						selectwindow* s=new selectwindow();
						int ans=s->work("将该歌曲添加至...");
						delete s;
						if(ans!=-1)
							playlist_manager->data[ans]->data.push_back(bindlist->data[currentin]);
					}else
						if(posx+width-3*texth-dragwidth<=mousex&&mousex<=posx+width-texth*2-dragwidth&&posy<=mousey&&mousey<=posy+height){
							CHAR a[300]={'#'};
							InputBox(a,200,"输入当前音乐新名字","CPlayer",bindlist->data[currentin].name.c_str(),0,0,false);
							if(a[0]!='#'){
								std::string pa=a;
								bindlist->data[currentin].name=pa;

							}
						}else
							if(posx+width-4*texth-dragwidth<=mousex&&mousex<=posx+width-texth*3-dragwidth&&posy<=mousey&&mousey<=posy+height){
								if(bindlist==current_playlist->bindlist){
									current_playlist->play_button->play(current_playlist->bindlist->data[currentin].id,currentin);
									return;
								}
								current_playlist->bindlist->data.push_back(bindlist->data[currentin]);
								current_playlist->play_button->play(current_playlist->bindlist->data[current_playlist->bindlist->data.size()-1].id,(int)current_playlist->bindlist->data.size()-1);
							}else
								if(posx+width-5*texth-dragwidth<=mousex&&mousex<=posx+width-texth*4-dragwidth&&posy<=mousey&&mousey<=posy+height){
									//down
									int downid=(currentin+1)%(int)bindlist->data.size();
									std::swap(bindlist->data[downid],bindlist->data[currentin]);
								}else
									if(posx+width-6*texth<=mousex&&mousex<=posx+width-texth*5&&posy<=mousey&&mousey<=posy+height){
										int upid=(currentin-1+(int)bindlist->data.size())%(int)bindlist->data.size();
										std::swap(bindlist->data[upid],bindlist->data[currentin]);
									}
			}else
				if(posx+width-dragwidth<=mousex&&mousex<=posx+width&&posy<=mousey&&mousey<=posy+height){
					int totalheight=bindlist->data.size()*texth<height?height:bindlist->data.size()*texth;
					if(posy+viewy*height/totalheight<=mousey&&mousey<=posy+(viewy+height)*height/totalheight)
						deltadrag=mousey-(posy+viewy*height/totalheight);
					else
						viewy=(mousey-posy)*totalheight/height;
					if(viewy<0)
						viewy=0;
					if(viewy>(int)bindlist->data.size()*texth-height)
						viewy=(int)bindlist->data.size()*texth-height;
					isdrag=true;
				}
			
		}else
			if(msg.message==WM_MOUSEMOVE){
				if(isdrag){
					int totalheight=bindlist->data.size()*texth<height?height:bindlist->data.size()*texth;
					viewy=(mousey-posy-deltadrag)*totalheight/height;
					if(viewy<0)
						viewy=0;
					if(viewy>(int)bindlist->data.size()*texth-height)
						viewy=(int)bindlist->data.size()*texth-height;
					isdrag=true;
				}
			}else
				if(msg.message==WM_LBUTTONUP){
					isdrag=false;
					deltadrag=0;
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
			isdrag=false;
		}
		if(playlist_manager->currentselect==0){
			isshow=false;
		} else
			isshow=true;
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
	int dragwidth;
	bool isdrag=false;
	int deltadrag=0;
};