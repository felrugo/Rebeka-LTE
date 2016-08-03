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

/**
Basic file struct, used for file path search.
*/
class RebFile
{
	std::string APath; /**< The Absolute path of the file. */
	RebDir * Par; /**< The parent directory of the file*/

public:
	/**
	The constructor
	\param abspath String of the file absolute path.
	\param spar Set the parent directory.
	*/
	RebFile(std::string abspath, RebDir * spar = 0);

	/**
	\return The name of the file + .extension if wex is true.
	*/
	std::string GetName(bool wex = true);

	/**
	\return The Absolute Path of the file.
	*/
	std::string GetAPath();
	std::string GetRPath();

	/**
	\return The Extension of the file.
	*/
	std::string GetExtension();

	/**
	\return The Parent Directory of the file.
	*/
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