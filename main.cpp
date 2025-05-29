/*
写在前面:
该作业使用C++编写  
是一个简易的本地音乐播放器
有基本的从本地导入音乐、歌单、播放、歌词等功能
功能不全 系统结构混乱 有修改余地 产出BUG 轻喷
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
#include"musiccover.h"

#pragma comment(lib,"winmm.lib")
IMAGE background_img;
IMAGE next_button_img;
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
IMAGE cd_img;
IMAGE mask2_img;
IMAGE lyrics_down_img;
IMAGE lyrics_up_img;
IMAGE export_img;
int mousex,mousey;
musicbase database;
Scene* list_scene=nullptr;
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
musiccover* music_cover;
void ImportImage(){
	loadimage(&background_img,"resource/background.jpg");
	loadimage(&next_button_img,"resource/next.png",60,60);
	loadimage(&pre_img,"resource/pre.png",60,60);
	loadimage(&play_img,"resource/play.png",60,60);
	loadimage(&pause_img,"resource/pause.png",60,60);
	loadimage(&add_music_img,"resource/add_music.png",50,50);
	loadimage(&toggle_list_img,"resource/toggle_list.png",50,50);
	loadimage(&music_edit_img,"resource/music_edit.png",50,50);
	loadimage(&add_to_button_img,"resource/add_to.png",30,30);
	loadimage(&add_list_button_img,"resource/add_list.png",30,30);
	loadimage(&add_img,"resource/add.png",30,30);
	loadimage(&delete_img,"resource/delete.png",30,30);
	loadimage(&rename_img,"resource/rename.png",30,30);
	loadimage(&mask_img,"resource/mask.png",960,640);
	loadimage(&mask2_img,"resource/mask.png",100,100);
	loadimage(&volume_img,"resource/volume.png",25,25);
	loadimage(&play_icon_img,"resource/play_icon.png",30,30);
	loadimage(&up_img,"resource/up.png",30,30);
	loadimage(&down_img,"resource/down.png",30,30);
	loadimage(&cd_img,"resource/cd.png",100,100);
	loadimage(&lyrics_down_img,"resource/lyrics_down.png",100,100);
	loadimage(&lyrics_up_img,"resource/lyrics_up.png",100,100);
	loadimage(&export_img,"resource/export.png",30,30);
}
int main(){
	initgraph(960,640);//640/4=160
	setbkcolor(0xffffff);
	cleardevice();
	BeginBatchDraw();
	ImportImage();
	settextcolor(BLACK);
	settextstyle(20,0,_T("Consolas"),0,0,0,false,false,false,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,ANTIALIASED_QUALITY,DEFAULT_PITCH);
	setbkmode(TRANSPARENT);
	ExMessage msg;
	playlist_manager=new playlistmanager(0,100,200,300,30);
	lyrics_show=new lyrics(480,0,960,640,30);
	play_button=new playbutton(100,560,&play_img,&pause_img,lyrics_show);
	current_playlist=new currentplaylist(200,100,760,420-30,30,15,playlist_manager->data[0]);
	current_playlist->play_button=play_button;
	next_button=new nextbutton(180,560,&next_button_img,current_playlist);
	pre_button=new prebutton(20,560,&pre_img,current_playlist);
	add_music_button=new addmusicbutton(500,400,&add_music_img,current_playlist);
	progress_bar=new progressbar(380,580,400,20,10,20 ,5);
	toggle_list=new togglecurrentplaylist(600,400,&toggle_list_img,current_playlist);
	switch_edit_list=new switcheditlist(0,0,&music_edit_img);
	add_to_button=new addtobutton(0,60,&add_to_button_img);
	edit_list=new editlist(200,100,760,420-30,30,15,playlist_manager->data[0]);
	add_list_button=new addlistbutton(30,60,&add_list_button_img);
	edit_play_list=new editplaylist(230,30,630,50,30);
	music_info=new musicinfo(380,530,200,50,30,play_button,current_playlist);
	volume_bar=new volumebar(50,520,155,25,5,10,&volume_img);
	music_cover=new musiccover(260,530,100,100,play_button,current_playlist);
	list_scene=new listscene();
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

