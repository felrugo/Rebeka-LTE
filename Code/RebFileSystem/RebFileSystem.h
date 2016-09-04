#ifndef REBFILESYSTEM_H
#define REBFILESYSTEM_H

#include "../Rimba/IFileSystem.h"
#include "../RebSupport/RebGDC.h"



#ifdef _WIN32
#include <Windows.h>
#elif __linux__
#endif


#include <regex>
#include <fstream>


enum PathType {PT_ABS_DIR, PT_REL_DIR, PT_ABS_FILE, PT_REL_FILE};

class RebDir;

/**
Basic file struct, used for file path search.
*/
class RebFile : public IFile
{
	std::string APath; /**< The Absolute path of the file. */
	IDir * Par; /**< The parent directory of the file*/

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
	IDir * GetParent();
};


class RebDir : public IDir
{
	std::vector<IDir*> dirs;
	std::vector<IFile*> files;
	std::string APath;
	IDir * Par;

public:

	/**
	Contructor for RebDir
	\param abspath Absolute path of the director.
	\param spar Pointer to the parent directory.
	*/
	RebDir(std::string abspath, RebDir * spar = 0);

	/**
	\return The Absolute Path of the directory.
	*/
	std::string GetAPath();
	std::string GetRPath();

	/**
	\return The name of the directory.
	*/
	std::string GetName();

	/**
	\return The parent directory.
	*/
	IDir * GetParent();

	/**
	Function for search files in the directory.
	\param name Name of the file we are looking for, wildcrads enabled.
	\return Vector of matching files.
	*/
	std::vector<IFile*> Search(std::string name);

	/**
	Function for search directories in the directory.
	\param name Name of the directory we are looking for, wildcards enabled.
	\return Vector of matching directories.
	*/
	std::vector<IDir*> SearchDir(std::string name);

	/**
	Function for get all files from the directory and sub-directories.
	\return Vector of files.
	*/
	std::vector<IFile*> GetAllFiles();

	/**
	Function for get all directories in the directory.
	\return Vector of directories.
	*/
	std::vector<IDir*> * GetDirs();

	/**
	Function for get all files in the directory.
	\return Vector of files.
	*/
	std::vector<IFile*> * GetFiles();

};


class RebFileSystem : public IFileSystem
{
	IDir * Root;

	PathType GetPT(std::string path);

	std::string SDPathUp(std::string path);

	void GetRootAdress();
public:

	RebFileSystem(RebGDC * gdc);

	std::vector<IFile*> Search(std::string name);

	std::vector<IDir*> SearchDir(std::string name);

	std::vector<IFile*> GetAllFiles();
};




#endif