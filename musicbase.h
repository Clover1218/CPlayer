#pragma once
#include"music.h"
#include<vector>
#include<string>
#include<iostream>
#include<taglib/tag.h>
#include<taglib/fileref.h>
#include<taglib/mpegfile.h>
#include<taglib/id3v2tag.h>
#include<taglib/id3v2frame.h>
#include<taglib/id3v2framefactory.h>
#include<taglib/attachedpictureframe.h>
#include<fstream>
class musicbase{
public:
	musicbase()=default;
	~musicbase()=default;
	void pathConvert_Single2Double(std::string& s){
		std::string::size_type pos = 0;
		while((pos=s.find('\\',pos))!=std::string::npos){
			s.insert(pos,"\\");
			pos=pos+2;
		}	
	}
    bool extractCover(std::string path){
        TagLib::MPEG::File file(path.c_str());
        TagLib::ID3v2::Tag *tag = file.ID3v2Tag();
        if(!file.isValid())
            return false;

        if(!tag)
            return false;
        TagLib::ID3v2::FrameList frameList = tag->frameList("APIC");
        if(frameList.isEmpty())
            return false;
        TagLib::ID3v2::AttachedPictureFrame* pictureFrame = 
            dynamic_cast<TagLib::ID3v2::AttachedPictureFrame*>(frameList.front());
        if(!pictureFrame)
            return false;
        size_t l=path.length();
        path[l-1]='g';path[l-2]='p';path[l-3]='j';
        std::ofstream out(path.c_str(),std::ios::binary);
        if(!out)
            return false;
        out.write(pictureFrame->picture().data(), pictureFrame->picture().size());
        out.close();
        return true;

    }
    void extractArtist(std::string path){

    }
	int add(std::string name,std::string path){
		pathConvert_Single2Double(path);
        if(extractCover(path)){
            std::cout<<"!\n";
        }		
        music te(int(base.size()),name,path);
		base.emplace_back(te);
		std::cout<<path<<std::endl;
		return (int)base.size()-1;

	}
	void print(){
		for(music m:base){
			std::cout<<m.id<<" "<<m.name<<" "<<m.path<<std::endl;
		}
	}
	std::vector<music> base;
	
};
