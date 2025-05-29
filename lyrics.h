#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<string>
#include"playbutton.h"
#include"currentplaylist.h"
#include"util.h"
extern musicbase database;
static int stringtoint(int l,int r,std::string& s){
    int base=0;
    for(int i=l+1;i<=r-1;i++)
        base=base*10+s[i]-'0';
    return base;
}
class lyrics{
public:
	lyrics(int x,int y,int w,int h,int th){
		posx=x;posy=y;width=w;height=h;viewy=0;texth=th;
		texth=th;
	}
	void draw(){
        //return;
        settextstyle(texth,0,_T("Consolas"));
        if(state==false){
            outtextxy(posx-(textwidth("��ǰ�޸��,�뽫������ͬ����.lrc�ļ�������������ͬ��Ŀ¼���Ա�ʶ��"))/2,posy,"��ǰ�޸��,�뽫������ͬ����.lrc�ļ�������������ͬ��Ŀ¼���Ա�ʶ��");
            return;
        }		
        char pos[100];
        mciSendString("status music position",pos,100,0);//2 2 4 4 5 5 5 7 7
        int key=atoi(pos),nowpos=0,nowms=0;
        for(int i=0;i<data.size();i++){
            if(key<=data[i].first){
                nowpos=i;
                break;
            }
            if(i==data.size()-1){
                nowpos=data.size();
            }
        }
        if(nowpos==0)   nowpos++;
        nowpos--;
        nowms=data[nowpos].first;
        while(nowpos>0&&data[nowpos-1].first==nowms)  nowpos--;
        int inity=posy+height/2-nowpos*texth-2*texth;
        for(int i=0;i<data.size();i++){
            //if(data[i].first<=key)
            //    continue;
            settextcolor(BLACK);
            if(nowms==data[i].first){
                settextcolor(RED);
            }
            outtextxy(posx-(textwidth(data[i].second.c_str()))/2,inity,data[i].second.c_str());
            inity+=texth;
        }
        /*if(nowpos-1>=0)
            outtextxy(posx-(textwidth(data[nowpos-1].second.c_str()))/2,posy,data[nowpos-1].second.c_str());
        settextstyle(texth*3/2,0,_T("Consolas"));
        outtextxy(posx-(textwidth(data[nowpos].second.c_str()))/2,posy+texth*3/2,data[nowpos].second.c_str());
        settextstyle(texth,0,_T("Consolas"));
        if(nowpos+1<(int)data.size())
            outtextxy(posx-(textwidth(data[nowpos+1].second.c_str()))/2,posy+7*texth/2,data[nowpos+1].second.c_str());*/
	}
	void process_wheel(int wheel){
	}
	void process_click(){
	} 
	void update(){

	}
    void getlyrics(int id){
        data.clear();
        std::string in=database.base[id].path;size_t n=in.size();
        in[n-1]='c';in[n-2]='r';in[n-3]='l';
        std::ifstream inf(in,std::ios::binary);
        if(!inf.is_open()){
            state=false;
            return;
        }
        std::string line;
        while(std::getline(inf,line)){
            int leftb=-1,rightb=-1,colon=-1,point=-1;
            int i=0;
            for(auto c:line){//[xx:ww.ss]
                if(c=='[')
                    leftb=i;
                if(c==']'){
                    rightb=i;
                    break;
                }
                if(c==':')
                    colon=i;
                if(c=='.')
                    point=i;
                i++;
            }

            if(leftb!=-1&&rightb!=-1&&colon!=-1&&point!=-1){
                int time=1000*(stringtoint(leftb,colon,line)*60+stringtoint(colon,point,line))+stringtoint(point,rightb,line)*(int)pow(10,3-(rightb-point));
                data.push_back({time,utf8ToGbk(line.substr(rightb+1))});
            }
        }
        sort(data.begin(),data.end(),[](std::pair<int,std::string> a,std::pair<int,std::string> b)->bool{return a.first<b.first;});
        state=true;
    }
    int findpos(int ms){
        int l=0,r=(int)data.size()-1;
        while(l<=r){
            int mid=(l+r)>>1;
            if(data[mid].first==ms){
                return mid;
            }
            if(data[mid].first<ms){
                l=mid+1;
            }else{
                r=mid-1;
            }
        }
        return r;

    }
	int posx;
	int posy;
	int width;
	int height;	
	int viewy;
	int texth;
	int gap=2;
	bool state=false;
    std::vector<std::pair<int,std::string>> data;
  
};
