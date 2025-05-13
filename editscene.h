//#pragma once
//#include<graphics.h>
//#include"scene.h"
//#include"scenemanager.h"
//extern IMAGE background_img;
//extern scenemanager scene_manager;
//extern switcheditlist* switch_edit_list;
//extern nextbutton* next_button;
//extern playbutton* play_button;
//extern prebutton* pre_button;
//extern addmusicbutton* add_music_button;
//extern currentplaylist* current_playlist;
//extern progressbar* progress_bar;
//extern togglecurrentplaylist* toggle_list;
//extern switcheditlist* switch_edit_list;
//class editscene:public Scene{
//public:
//	editscene(){
//		switch_edit_list_ptr=switch_edit_list;
//	}
//	~editscene()=default;
//	void process_msg(ExMessage& msg){
//		if(msg.message==WM_LBUTTONDOWN){
//			if(switch_edit_list_ptr->process_click()){
//				scene_manager.setbynumber(1);
//		}
//
//		}
//
//	}
//	void draw(){
//		putimage(0,0,&background_img);
//		switch_edit_list_ptr->draw();
//	}
//	void update(){
//			
//	}
//private:
//	switcheditlist* switch_edit_list_ptr=nullptr;
//
//};
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
extern IMAGE background_img;
class editscene:public Scene{
public:
	editscene(){
		next_button_ptr=next_button;
		play_button_ptr=play_button;
		pre_button_ptr=pre_button;
		progress_bar_ptr=progress_bar;
		switch_edit_list_ptr=switch_edit_list;
	}
	~editscene(){
	}
	void process_msg(ExMessage& msg){
		progress_bar_ptr->process_drag(msg);
		if(msg.message==WM_MOUSEMOVE){
		}else
			if(msg.message==WM_LBUTTONDOWN){
				next_button_ptr->process_click();
				pre_button_ptr->process_click();
				play_button_ptr->process_click();


			}else{
				if(msg.message==WM_MOUSEWHEEL){

				}else
					if(msg.message==WM_LBUTTONDBLCLK){

					}

				
			}
	}
	void draw(){
		putimage(0,0,&background_img);
		//putimage(0,400,&mask_bottom_img);
		next_button_ptr->draw();
		play_button_ptr->draw();
		pre_button_ptr->draw();
		progress_bar_ptr->draw();
		switch_edit_list_ptr->draw();
	}
	void update(){
		current_playlist_ptr->update();
	}
private:
	nextbutton* next_button_ptr=nullptr;
	playbutton* play_button_ptr=nullptr;
	prebutton* pre_button_ptr=nullptr;
	addmusicbutton* add_music_button_ptr=nullptr;
	currentplaylist* current_playlist_ptr=nullptr;
	progressbar* progress_bar_ptr=nullptr;
	togglecurrentplaylist* toggle_list_ptr=nullptr;
	switcheditlist* switch_edit_list_ptr=nullptr;

};