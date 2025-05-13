#pragma once
#include<graphics.h>
#include"scene.h"
extern Scene* list_scene;
class scenemanager{
public:
	scenemanager(){
	}
	~scenemanager()=default;
	void setbynumber(int cur){
		if(cur==1)
			current_scene=list_scene;
	}
	void setbyscene(Scene* cur){
		current_scene=cur;
				
	}
	void process_msg(ExMessage& msg){
		current_scene->process_msg(msg);
	}
	void draw(){
		current_scene->draw();
	}
	void update(){
		current_scene->update();
	}
private:
	Scene* current_scene=nullptr;
	int state;//0-list 1-play
};
