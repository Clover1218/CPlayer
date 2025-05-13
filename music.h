#pragma once
#include<string>
class music{
public:
	music(int i,std::string n,std::string p){
		id=i;
		name=n;
		path=p;
		status=false;
	}
	~music()=default;
	int id=-1;
	std::string name;
	std::string path;
	bool status=false;
};