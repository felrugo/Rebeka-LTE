#pragma once

#include "../Rimba/IFileSystem.h"
#include "../RebSupport/RebGDC.h"
#include <Windows.h>
#include <ktmw32.h>
#include <map>
#include <regex>


class RebDirN;
class RebFileSystemN;

class RebFileN : public IFile
{
	std::string Path;

	RebFileSystemN * fs;
public:
	RebFileN(std::string path, RebFileSystemN * fs);

	bool Exists();

	std::string GetName(bool wex);

	std::string GetExtension();

	std::string GetPath();

	std::string GetRPath();

	std::shared_ptr<IDir> GetParent();

};

class RebFileSearchN;

class RebDirN : public IDir
{
	std::string Path;

	RebFileSystemN * fs;

	bool isListable();
public:

	RebDirN(std::string path, RebFileSystemN * fs);

	std::vector<std::shared_ptr<IFile>> GetFiles();

	std::vector<std::shared_ptr<IDir>> GetDirs();

	std::string GetName();

	IFileSearch * Search(std::string reg);

	std::string GetPath();
	std::string GetRPath();

	std::shared_ptr<IDir> GetParent();

	bool Exists();
};


class RebFileSearchN : public IFileSearch
{
	std::vector<std::shared_ptr<IFile>> result;
	size_t slevel;

public:

	RebFileSearchN();

	void Start();

	void End();

	std::vector<std::shared_ptr<IFile>> * GetResult();

	

};

class RebFileSystemN : public IFileSystem
{

	std::shared_ptr<RebDirN> root;

	std::map<std::string, std::string> gpaths;

	RebFileSearchN lastsearch;

public:

	RebFileSystemN(RebGDC * gdc);

	static std::string Unixize(std::string path);

	static std::string ResolvePathSymbols(std::string path);

	std::string ResolveGamePath(std::string path);

	std::string EncodeGamePath(std::string path);

	static std::string UpDir(std::string path);

	std::shared_ptr<IDir> GetRoot();

	std::shared_ptr<IFile> GetFile(std::string path);

	std::shared_ptr<IDir> GetDir(std::string path);

	IFileSearch * GetLastSearchResult();

	IFileSearch * Search(std::string reg);

};