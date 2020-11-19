#include "stdafx.h"
#include "JSON.h"

void JSON::LoadJSON(string FileName)
{
	FILE *fp;
	fopen_s(&fp, FileName.c_str(), "rb");

	char buffer[65536];
	FileReadStream is(fp, buffer, sizeof(buffer));
	if(doc.ParseStream(is).HasParseError())
	{
		cout << "Parsing error" << endl;
	}
	fclose(fp);
	cout << buffer;
}

void JSON::WriteJSON(string FileName)
{
	
}
