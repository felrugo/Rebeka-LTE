#ifndef REBFILESYSTEM_H
#define REBFILESYSTEM_H

#include <string>
#include <vector>

#ifdef _WIN32
#include <Windows.h>
#elif __linux__
#endif

#include <fstream>


enum PathType {PT_ABS_DIR, PT_REL_DIR, PT_ABS_FILE, PT_REL_FILE};

class RebFile
{
	std::string APath;

public:

	RebFile(std::string abspath);

	std::string GetName();
	std::string GetAPath();
	std::string GetRPath();
	std::string GetExtension();
};


class RebDir
{
	std::vector<RebDir*> dirs;
	std::vector<RebFile*> files;
	std::string APath;

public:
	RebDir(std::string abspath);

	std::string GetAPath();
	std::string GetRPath();
	std::string GetName();

	std::vector<RebFile*> Search(std::string name);
	std::vector<RebDir*> SearchDir(std::string name);

	std::vector<RebFile*> GetAllFiles();

	std::vector<RebDir*> * GetDirs();
	std::vector<RebFile*> * GetFiles();

};


class RebFileSystem
{
	RebDir * Root;

	PathType GetPT(std::string path);

	std::string SDPathUp(std::string path);

	void GetRootAdress();
public:

	RebFileSystem();

	std::vector<RebFile*> Search(std::string name);

	std::vector<RebDir*> SearchDir(std::string name);

	std::vector<RebFile*> GetAllFiles();
};




#endif