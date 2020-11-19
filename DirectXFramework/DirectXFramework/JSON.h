#pragma once
#include "Singleton.h"
#include "JSON/rapidjson/document.h"
#include "JSON/rapidjson/filereadstream.h"
#include "JSON/rapidjson/filewritestream.h"

using namespace rapidjson;

#define gJSON JSON::GetInstance()

class JSON : public Singleton<JSON>
{
public:
	void LoadJSON(string FileName);
	void WriteJSON(string FileName);
	void PrintJSON()
	{
		
	}
private:
	Document doc;
};

