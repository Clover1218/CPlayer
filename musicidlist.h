#pragma once
#include<string>
#include<vector>
class musicidlistitem{
public:
	musicidlistitem()=default;
	~musicidlistitem()=default;
	int id;
	int status=0;
	std::string name;
};
class musicidlist{
public:
	musicidlist(std::string n,int i){
		listname=n;
		id=i;
	}
	void add(int id,std::string n){
		data.push_back({id,false,n});
	}
	int id;
	std::vector<musicidlistitem> data;	
	std::string listname;
private:


};