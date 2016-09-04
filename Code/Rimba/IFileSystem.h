#pragma once

#include <string>
#include <vector>

class IDir;

class IFile
{
public:
	/**
	\return The name of the file + .extension if wex is true.
	*/
	virtual std::string GetName(bool wex = true) = 0;

	/**
	\return The Absolute Path of the file.
	*/
	virtual std::string GetAPath() = 0;
	virtual std::string GetRPath() = 0;

	/**
	\return The Extension of the file.
	*/
	virtual std::string GetExtension() = 0;

	/**
	\return The Parent Directory of the file.
	*/
	virtual IDir * GetParent() = 0;
};


class IDir
{
public:
	/**
	\return The Absolute Path of the directory.
	*/
	virtual std::string GetAPath() = 0;
	virtual std::string GetRPath() = 0;

	/**
	\return The name of the directory.
	*/
	virtual std::string GetName() = 0;

	/**
	\return The parent directory.
	*/
	virtual IDir * GetParent() = 0;

	/**
	Function for search files in the directory.
	\param name Name of the file we are looking for, wildcrads enabled.
	\return Vector of matching files.
	*/
	virtual std::vector<IFile*> Search(std::string name) = 0;

	/**
	Function for search directories in the directory.
	\param name Name of the directory we are looking for, wildcards enabled.
	\return Vector of matching directories.
	*/
	virtual std::vector<IDir*> SearchDir(std::string name) = 0;

	/**
	Function for get all files from the directory and sub-directories.
	\return Vector of files.
	*/
	virtual std::vector<IFile*> GetAllFiles() = 0;

	/**
	Function for get all directories in the directory.
	\return Vector of directories.
	*/
	virtual std::vector<IDir*> * GetDirs() = 0;

	/**
	Function for get all files in the directory.
	\return Vector of files.
	*/
	virtual std::vector<IFile*> * GetFiles() = 0;
};

class IFileSystem
{
public:
	virtual std::vector<IFile*> Search(std::string name) = 0;

	virtual std::vector<IDir*> SearchDir(std::string name) = 0;

	virtual std::vector<IFile*> GetAllFiles() = 0;
};