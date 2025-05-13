/*
写在前面:
当前版本v0.1
该作业使用C++编写  
是一个简易的本地音乐播放器
功能不全 系统结构混乱 轻喷
注意事项
1.因为用到了STL的filesystem库，所以需要C++17及以上才可运行
2.图形库采用easyX
3.多媒体主要使用Windows API的mcisendstring函数及其他 所以不支持.m4a .flac等比较新的音频格式
4.作者已经被宽字符逼疯 所以请手动改成“使用多字符集”
5.添加本地文件音乐文件夹函数会递归遍历文件夹 请不要作死嵌套过多文件夹或者直接拿大盘添加 否则后果自负
*/
#include<graphics.h>
#include<stdio.h>
#include<vector>
#include<Windows.h>
#include<mmsystem.h>
#include"musicbase.h"
#include"scene.h"
#include"listscene.h"
#include"playscene.h"
#include"editscene.h"
#include"playbutton.h"
#include"currentplaylist.h"
#include"nextbutton.h"
#include"prebutton.h"
#include"scenemanager.h"
#include"playlistmanager.h"
#include"togglecurrentplaylist.h"
#include"switcheditlist.h"
#include"editlist.h"
#include"addtobutton.h"
#include"addlistbutton.h"
#include"editplaylist.h"
#include"musicinfo.h"
#include"volumebar.h"

#pragma comment(lib,"winmm.lib")
IMAGE background_img;
IMAGE next_button_img;
IMAGE next_img;
IMAGE pre_img;
IMAGE play_img;
IMAGE pause_img;
IMAGE add_music_img;
IMAGE toggle_list_img;
IMAGE music_edit_img;
IMAGE add_to_button_img;
IMAGE add_list_button_img;
IMAGE add_img;
IMAGE delete_img;
IMAGE rename_img;
IMAGE mask_img;
IMAGE volume_img;
IMAGE play_icon_img;
IMAGE up_img;
IMAGE down_img;
int mousex,mousey;
musicbase database;
Scene* list_scene=nullptr;
Scene* player_scene=nullptr;
Scene* edit_scene=nullptr;
scenemanager scene_manager;
currentplaylist* current_playlist;
playlistmanager* playlist_manager;
playbutton* play_button;
nextbutton* next_button;
prebutton* pre_button;
addmusicbutton* add_music_button;
progressbar* progress_bar;
togglecurrentplaylist* toggle_list;
switcheditlist* switch_edit_list;
editlist* edit_list;
addtobutton* add_to_button;
addlistbutton* add_list_button;
editplaylist* edit_play_list;
musicinfo* music_info;
lyrics* lyrics_show;
volumebar* volume_bar;
void ImportImage(){
	loadimage(&background_img,"resource/background.jpg");
	loadimage(&next_button_img,"resource/nextbutton.png",100,100);
	loadimage(&next_img,"resource/next.png",50,50);
	loadimage(&pre_img,"resource/pre.png",50,50);
	loadimage(&play_img,"resource/play.png",50,50);
	loadimage(&pause_img,"resource/pause.png",50,50);
	loadimage(&add_music_img,"resource/add_music.png",50,50);
	loadimage(&toggle_list_img,"resource/toggle_list.png",50,50);
	loadimage(&music_edit_img,"resource/music_edit.png",50,50);
	loadimage(&add_to_button_img,"resource/add_to.png",30,30);
	loadimage(&add_list_button_img,"resource/add_list.png",30,30);
	loadimage(&add_img,"resource/add.png",20,20);
	loadimage(&delete_img,"resource/delete.png",20,20);
	loadimage(&rename_img,"resource/rename.png",20,20);
	loadimage(&mask_img,"resource/mask.png",720,480);
	loadimage(&volume_img,"resource/volume.png",20,20);
	loadimage(&play_icon_img,"resource/play_icon.png",20,20);
	loadimage(&up_img,"resource/up.png",20,20);
	loadimage(&down_img,"resource/down.png",20,20);
}
int main(){
	initgraph(720,480);
	BeginBatchDraw();
	ImportImage();
	settextcolor(BLACK);
	settextstyle(20,0,_T("Consolas"),0,0,0,false,false,false,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,ANTIALIASED_QUALITY,DEFAULT_PITCH);
	setbkmode(TRANSPARENT);
	ExMessage msg;
	playlist_manager=new playlistmanager(0,100,200,300,20);
	lyrics_show=new lyrics(360,175,200,300,20);
	play_button=new playbutton(100,400,&play_img,&pause_img,lyrics_show);
	current_playlist=new currentplaylist(200,50,300,350,20,playlist_manager->data[0]);
	current_playlist->play_button=play_button;
	next_button=new nextbutton(180,400,&next_img,current_playlist);
	pre_button=new prebutton(20,400,&pre_img,current_playlist);
	add_music_button=new addmusicbutton(500,400,&add_music_img,current_playlist);
	progress_bar=new progressbar(250,450,200,20,10);
	toggle_list=new togglecurrentplaylist(600,400,&toggle_list_img,current_playlist);
	switch_edit_list=new switcheditlist(0,0,&music_edit_img);
	add_to_button=new addtobutton(0,60,&add_to_button_img);
	edit_list=new editlist(150,50,300,350,20,playlist_manager->data[0]);
	add_list_button=new addlistbutton(30,60,&add_list_button_img);
	edit_play_list=new editplaylist(150,0,300,50,20);
	music_info=new musicinfo(250,400,200,50,30,play_button,current_playlist);
	volume_bar=new volumebar(50,450,155,20,5,&volume_img);
	list_scene=new listscene();
	edit_scene=new editscene();
	scene_manager.setbynumber(1);
	while(true){
		scene_manager.draw();
		while(peekmessage(&msg)){
			if(msg.message==WM_MOUSEMOVE){
				mousex=msg.x,mousey=msg.y;		
			}
			scene_manager.process_msg(msg);
		}
		scene_manager.update();
		FlushBatchDraw();
		cleardevice();
	}
	EndBatchDraw();
	closegraph();
	return 0;
}

