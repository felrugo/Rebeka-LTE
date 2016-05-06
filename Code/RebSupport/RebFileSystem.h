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

class RebDir;

class RebFile
{
	std::string APath;
	RebDir * Par;

public:

	RebFile(std::string abspath, RebDir * spar = 0);

	std::string GetName(bool wex = true);
	std::string GetAPath();
	std::string GetRPath();
	std::string GetExtension();

	RebDir * GetParent();
};


class RebDir
{
	std::vector<RebDir*> dirs;
	std::vector<RebFile*> files;
	std::string APath;
	RebDir * Par;

public:
	RebDir(std::string abspath, RebDir * spar = 0);

	std::string GetAPath();
	std::string GetRPath();
	std::string GetName();

	RebDir * GetParent();

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