#ifndef REBFILESYSTEM_H
#define REBFILESYSTEM_H

#include <string>
#include <vector>

#ifdef _WIN32
#include <Windows.h>
#elif __linux__
#endif



#include <fstream>

class RebFile
{
public:
	std::string raw;
	std::string fname;
	std::string path;
	std::string type;
	std::string rpath;

	RebFile();

	std::string GetFileName();

	std::string GetEnginePath();

	RebFile(std::string file);
};


class RebFileSystem
{
	std::vector<RebFile> Files;
	std::vector<RebFile> Objects;
	std::vector<RebFile> Entities;
	std::vector<RebFile> Shaders;

public:
	RebFileSystem();

	void CreateDirSystem();

	void CreateDir(std::string dirname, std::string path);

	RebFile Search(std::string filename, std::string dir = "");

	std::string GetRootAdress();

	void GetAllFiles(std::string dir = "\\");

	std::vector<RebFile> * GetObjects();

	std::vector<RebFile> * GetEntities();

	void Categorize();

	bool RebFileSystem::GetFile(std::string name, RebFile* out);

	static std::vector<std::string> Read(std::string path);

	static void Write(std::vector<std::string> writable, std::string path);
};




#endif