#pragma once
#include<graphics.h>
class Scene{
public:
	Scene()=default;
	~Scene()=default;
	int submenu;
	void changesubmenu(int c){
		submenu=c;
	}
	virtual void draw(){}
	virtual void update(){}
	virtual void process_msg(ExMessage& msg){}
};