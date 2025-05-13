#pragma once
#include<graphics.h>
#include"scene.h"
#include"currentplaylist.h"
#include"nextbutton.h"
#include"playbutton.h"
#include"prebutton.h"
#include"addmusicbutton.h"
#include"progressbar.h"
#include"togglecurrentplaylist.h"
#include"switcheditlist.h"
#include"scenemanager.h"
#include"playlistmanager.h"
#include"editlist.h"
#include"addtobutton.h"
#include"addlistbutton.h"
#include"editplaylist.h"
#include"musicinfo.h"
#include"lyrics.h"
#include"volumebar.h"
#define test std::cout<<"1";
extern scenemanager scene_manager;
extern nextbutton* next_button;
extern playbutton* play_button;
extern prebutton* pre_button;
extern addmusicbutton* add_music_button;
extern currentplaylist* current_playlist;
extern progressbar* progress_bar;
extern togglecurrentplaylist* toggle_list;
extern switcheditlist* switch_edit_list;
extern playlistmanager* playlist_manager;
extern editlist* edit_list;
extern addtobutton* add_to_button;
extern addlistbutton* add_list_button;
extern editplaylist* edit_play_list;
extern musicinfo* music_info;
extern lyrics* lyrics_show;
extern volumebar* volume_bar;
extern IMAGE background_img;
class listscene:public Scene{
public:
	listscene(){
		submenu=0;
	}
	~listscene(){
	}
	void process_msg(ExMessage& msg){
		if(((submenu>>1)&1)==1){
			progress_bar->process_drag(msg);
			volume_bar->process_drag(msg);
			if(msg.message==WM_MOUSEMOVE){
			}else
				if(msg.message==WM_LBUTTONDOWN){
					next_button->process_click();
					pre_button->process_click();
					play_button->process_click();
					music_info->process_click();
				}else{
					if(msg.message==WM_MOUSEWHEEL){
					}else
						if(msg.message==WM_LBUTTONDBLCLK){

						}

					
				}
		}else
			if((submenu&1)==0){
				progress_bar->process_drag(msg);
				volume_bar->process_drag(msg);
				if(msg.message==WM_MOUSEMOVE){
					current_playlist->process_mouse_move();
				}else
					if(msg.message==WM_LBUTTONDOWN){
						current_playlist->process_click();
						next_button->process_click();
						pre_button->process_click();
						add_music_button->process_click();
						toggle_list->process_click();
						play_button->process_click();
						switch_edit_list->process_click();
						music_info->process_click();
					}else{
						if(msg.message==WM_MOUSEWHEEL){
							current_playlist->process_wheel(msg.wheel);
						}else
							if(msg.message==WM_LBUTTONDBLCLK){

							}

						
					}
			}else
				if((submenu&1)==1){
					progress_bar->process_drag(msg);
					volume_bar->process_drag(msg);
					if(msg.message==WM_MOUSEMOVE){
						edit_list->process_mouse_move();
					}else
						if(msg.message==WM_LBUTTONDOWN){
							next_button->process_click();
							pre_button->process_click();
							play_button->process_click();
							playlist_manager->process_click();
							switch_edit_list->process_click();
							add_to_button->process_click();
							add_list_button->process_click();
							edit_list->process_click();
							edit_play_list->process_click();
							music_info->process_click();
						}else{
							if(msg.message==WM_MOUSEWHEEL){
								edit_list->process_wheel(msg.wheel);
								playlist_manager->process_wheel(msg.wheel);
							}else
								if(msg.message==WM_LBUTTONDBLCLK){

								}

							
						}
				}
		
	}
	void draw(){
		if(((submenu>>1)&1)==1){
			putimage(0,0,&background_img);
			next_button->draw();
			play_button->draw();
			pre_button->draw();
			progress_bar->draw();
			music_info->draw();
			lyrics_show->draw();
			volume_bar->draw();
		}else
			if((submenu&1)==0){
				putimage(0,0,&background_img);
				current_playlist->draw();
				putimage(0,400,720,80,&background_img,0,400);
				putimage(150,0,510,50,&background_img,150,0);
				next_button->draw();
				play_button->draw();
				pre_button->draw();
				add_music_button->draw();
				progress_bar->draw();
				toggle_list->draw();
				switch_edit_list->draw();
				music_info->draw();
				volume_bar->draw();
			}else
				if((submenu&1)==1){
					putimage(0,0,&background_img);
					playlist_manager->draw();
					edit_list->draw();
					putimage(0,0,150,100,&background_img,0,0);
					putimage(0,400,720,80,&background_img,0,400);
					putimage(150,0,510,50,&background_img,150,0);
					next_button->draw();
					play_button->draw();
					pre_button->draw();
					progress_bar->draw();
					switch_edit_list->draw();
					add_to_button->draw();
					add_list_button->draw();
					edit_play_list->draw();
					music_info->draw();
					volume_bar->draw();
				}
		
	}
	void update(){
		current_playlist->update();
		if((submenu&1)==1)
			edit_list->update();
	}
	int subscene=0;
};