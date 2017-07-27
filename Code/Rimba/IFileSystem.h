#pragma once

#include <string>
#include <vector>
#include <memory>

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
	virtual std::string GetPath() = 0;
	//virtual std::string GetRPath() = 0;

	/**
	\return The Extension of the file.
	*/
	virtual std::string GetExtension() = 0;

	/**
	\return The Parent Directory of the file.
	*/
	virtual std::shared_ptr<IDir> GetParent() = 0;
};

class IFileSearch;

class IDir
{
public:
	/**
	\return The Absolute Path of the directory.
	*/
	virtual std::string GetPath() = 0;
	//virtual std::string GetRPath() = 0;

	/**
	\return The name of the directory.
	*/
	virtual std::string GetName() = 0;

	/**
	\return The parent directory.
	*/
	virtual std::shared_ptr<IDir> GetParent() = 0;

	/**
	Function for get all directories in the directory.
	\return Vector of directories.
	*/
	virtual std::vector<std::shared_ptr<IDir>> GetDirs() = 0;

	/**
	Function for get all files in the directory.
	\return Vector of files.
	*/
	virtual std::vector<std::shared_ptr<IFile>> GetFiles() = 0;

	virtual IFileSearch * Search(std::string reg) = 0;


};


class IFileSearch
{
public:
	virtual std::vector<std::shared_ptr<IFile>> * GetResult() = 0;
};


class IFileSystem
{
public:

	virtual std::shared_ptr<IDir> GetRoot() = 0;

	virtual std::shared_ptr<IFile> GetFile(std::string path) = 0;

	virtual std::shared_ptr<IDir> GetDir(std::string path) = 0;
	
	virtual IFileSearch * GetLastSearchResult() = 0;

	virtual IFileSearch * Search(std::string reg)= 0;

};