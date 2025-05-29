#pragma once
#include"music.h"
#include"musicbase.h"
#include"musicidlist.h"
#include"playbutton.h"
#include"playlistmanager.h"
#include"selectwindow.h"
#include<utility>
#include<vector>
#include<iostream>
#include<graphics.h>
extern musicbase database;
extern int mousex,mousey;
extern IMAGE delete_img;
extern IMAGE up_img;
extern IMAGE down_img;
extern IMAGE add_img;
extern IMAGE rename_img;
extern playlistmanager* playlist_manager;
class currentplaylist{
public:
	currentplaylist(int x,int y,int w,int h,int th,int dw,musicidlist* bl){
		posx=x;posy=y;width=w;height=h;viewy=0;texth=th;bindlist=bl;dragwidth=dw;
		texth=th;
	}
	void draw(){
		if(!isshow) return;
		
		if(bindlist->data.size()==0){
			settextstyle(texth,0,"Consolas");
			outtextxy(posx,posy,"默认列表无音乐");
			outtextxy(posx,posy+texth,"请点击进度条右侧的按钮添加音乐");
			outtextxy(posx,posy+2*texth,"或点击左上角从歌单导入");
			outtextxy(posx,posy+3*texth,"点击进度条上方的音乐名可以查看歌词");
		}
		settextstyle(texth,0,"Consolas");
		int inity=posy-viewy,i=0;
		POINT tr[3];
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
			tr[0]={posx+gap,inity+gap};
			tr[1]={posx+texth-gap,inity+texth/2};
			tr[2]={posx+gap,inity+texth-gap};
			const char* sn=e.name.c_str();
			outtextxy(posx+texth,inity,sn);
			settextcolor(BLACK);
			if(i==currentselect){
				setlinecolor(BLACK);
				polygon(tr,3);
			}
			if(bindlist->data[i].id==play_button->playcurid&&i==play_button->playcurrentselect){
				setfillcolor(BLACK);
				solidpolygon(tr,3);
			}
			if(i==currentin){
				setlinecolor(BLACK);
				putImageAlpha(posx+width-texth-dragwidth,inity,&delete_img);
				putImageAlpha(posx+width-2*texth-dragwidth,inity,&add_img);
				putImageAlpha(posx+width-3*texth-dragwidth,inity,&rename_img);
				putImageAlpha(posx+width-4*texth-dragwidth,inity,&down_img);
				putImageAlpha(posx+width-5*texth-dragwidth,inity,&up_img);
				polygon(tr,3);
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
	void process_wheel(int wheel){
		if(!isshow) return;
		if(posx<=mousex&&mousex<=posx+width&&posy<=mousey&&mousey<=posy+height){
			if((int)bindlist->data.size()*texth>height){
				viewy-=wheel/2;
				if(viewy<0)
					viewy=0;
				if(viewy>(int)bindlist->data.size()*texth-height)
					viewy=(int)bindlist->data.size()*texth-height;
			}
		}
	}
	void del(int cur){
		if(currentin<0||bindlist->data.size()<=0) return;
		bindlist->data.erase(bindlist->data.begin()+cur);
		if(bindlist->data.size()<=0){
			play_button->play(-1,-1);
			return;
		}
		if(cur==play_button->playcurrentselect){
			if(cur>=bindlist->data.size()){
				currentin=currentselect=cur=0;
			}
			play_button->play(bindlist->data[cur].id,cur);
		}
		if(cur<currentselect){
			currentselect--;
			play_button->playcurrentselect--;
		}
	}
	void process_click(ExMessage& msg){
		if(!isshow) return;
		if(msg.message==WM_LBUTTONDOWN){
			if(posx<=mousex&&mousex<=posx+width-dragwidth&&posy<=mousey&&mousey<=posy+height){
				if(posx+width-texth-dragwidth<=mousex&&mousex<=posx+width-dragwidth&&posy<=mousey&&mousey<=posy+height){
					del(currentin);
				}else
					if(posx+width-2*texth-dragwidth<=mousex&&mousex<=posx+width-texth-dragwidth&&posy<=mousey&&mousey<=posy+height){							
						selectwindow* s=new selectwindow();
						int ans=s->work("将该歌曲添加至...");
						delete s;
						if(ans!=-1)
							playlist_manager->data[ans]->data.push_back(bindlist->data[currentin]);
					}else
						if(posx+width-3*texth-dragwidth<=mousex&&mousex<=posx+width-2*texth-dragwidth&&posy<=mousey&&mousey<=posy+height){
							CHAR a[300]={'#'};
							InputBox(a,200,"输入当前音乐新名字","CPlayer",bindlist->data[currentin].name.c_str(),0,0,false);
							if(a[0]!='#'){
								std::string pa=a;
								bindlist->data[currentin].name=pa;

							}							
						}else
							if(posx+width-4*texth-dragwidth<=mousex&&mousex<=posx+width-3*texth-dragwidth&&posy<=mousey&&mousey<=posy+height){
								int downid=(currentin+1)%(int)bindlist->data.size();
								if(currentin==play_button->playcurrentselect){
								std::swap(bindlist->data[downid],bindlist->data[currentin]);
								play_button->playcurrentselect=currentselect=downid;
								}else
									if(downid==play_button->playcurrentselect){
										std::swap(bindlist->data[downid],bindlist->data[currentin]);
										play_button->playcurrentselect=currentselect=currentin;
									}else{
										std::swap(bindlist->data[downid],bindlist->data[currentin]);
									}			
							}else
								if(posx+width-5*texth-dragwidth<=mousex&&mousex<=posx+width-4*texth-dragwidth&&posy<=mousey&&mousey<=posy+height){
									int upid=(currentin-1+(int)bindlist->data.size())%(int)bindlist->data.size();
									if(currentin==play_button->playcurrentselect){
										std::swap(bindlist->data[upid],bindlist->data[currentin]);
										play_button->playcurrentselect=currentselect=upid;
									}else
										if(upid==play_button->playcurrentselect){
											std::swap(bindlist->data[upid],bindlist->data[currentin]);
											play_button->playcurrentselect=currentselect=currentin;
										}else{
											std::swap(bindlist->data[upid],bindlist->data[currentin]);
										}
								
								}else{
									int dy=mousey-posy+viewy;
									int n=dy/texth;
									if(n==currentselect){
										play_button->play(bindlist->data[currentselect].id,currentselect);
									}else{
										if(n<bindlist->data.size())
											currentselect=n;
									}
						}
					if(currentselect*texth<viewy)
						viewy=currentselect*texth+texth;
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
		return;
	} 
	void process_mouse_move(){
		if(!isshow) return;
		if(posx<=mousex&&mousex<=posx+width-dragwidth&&posy<=mousey&&mousey<=posy+height){
			int dy=mousey-posy+viewy;
			int n=dy/texth;
			if(n<bindlist->data.size()){
					currentin=n;
			}
		} else{
			currentin=-1;
		}
	}
	void add(int id,std::string name){
		bindlist->data.push_back({id,false,name});
	}
	void play_next(){
		if(bindlist->data.size()<=0) return;
		int cur=currentselect;
		cur=(cur+1)%(int)bindlist->data.size();
		currentselect=cur;
		play_button->play(bindlist->data[currentselect].id,currentselect);
	}
	void play_pre(){
		if(bindlist->data.size()<=0) return;
		int cur=currentselect;
		cur=(cur-1+(int)bindlist->data.size())%(int)bindlist->data.size();
		currentselect=cur;
		play_button->play(bindlist->data[currentselect].id,currentselect);
	}
	void update(){
		char ans[100]={'#','#'};
		if(mciSendString("status music mode",ans,100,0)==0){
			if(ans[1]=='t'){
				play_button->playcurrentselect=play_button->playcurid=-1;
				mciSendString("close music",0,0,0);
				play_next();
			}
		}
		if(playlist_manager->currentselect==0){
			isshow=true;
		}else
			isshow=false;
	}
	int currentselect=-1;
	int currentin=-1;
	musicidlist* bindlist=nullptr;
	playbutton* play_button=nullptr;
	int posx;
	int posy;
	int width;
	int height;	
	int viewy;
	int texth;
	int gap=2;
	int dragwidth;
	int deltadrag=0;
	bool isshow=true;
	bool isdrag=false;

};