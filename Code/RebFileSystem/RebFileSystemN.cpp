#include "RebFileSystemN.h"

extern "C"
{
	void _declspec(dllexport) CreateFileSystem(RebGDC * gdc)
	{
		gdc->rfs = new RebFileSystemN(gdc);
	}

	void _declspec(dllexport) ReleaseFileSystem(RebGDC * gdc)
	{
		delete gdc->rfs;
		gdc->rfs = 0;
	}
}






RebFileN::RebFileN(std::string path, RebFileSystemN * fs) : fs(fs)
{
	Path = path;
}


std::string RebFileN::GetPath()
{
	return Path;
}

bool RebFileN::Exists()
{
	WIN32_FIND_DATA ffd;
	HANDLE hFind = INVALID_HANDLE_VALUE;

	hFind = FindFirstFile(Path.c_str(), &ffd);

	if (hFind != INVALID_HANDLE_VALUE)
	{
		FindClose(hFind);
		return true;
	}
	FindClose(hFind);
	return false;
}

std::string RebFileN::GetName(bool wex)
{
	int pos = 0;
	if ((pos = Path.find_last_of("/")) != std::string::npos)
	{
		if(wex)
		return Path.substr(pos, Path.length() - pos);
		else
		{
			std::string nwe = Path.substr(pos, Path.length() - pos);
			if ((pos = Path.find_last_of(".")) != std::string::npos)
			{
				return nwe.substr(0, pos);
			}
			return nwe;
		}
	}
	return Path;
}

std::string RebFileN::GetExtension()
{
	int pos = 0;
	if ((pos = Path.find_last_of("/")) != std::string::npos)
	{
			std::string nwe = Path.substr(pos, Path.length() - pos);
			if ((pos = Path.find_last_of(".")) != std::string::npos)
			{
				return nwe.substr(pos, Path.length() - pos);
			}
	}
	throw "Wrong Path";
}

std::shared_ptr<IDir> RebFileN::GetParent()
{
	return std::shared_ptr<RebDirN>(new RebDirN(RebFileSystemN::UpDir(Path), fs));
}


bool RebDirN::isListable()
{
	WIN32_FIND_DATA ffd;
	HANDLE hFind = INVALID_HANDLE_VALUE;

	hFind = FindFirstFile((Path + "/.nomedia").c_str(), &ffd);

	if (hFind != INVALID_HANDLE_VALUE)
	{
		FindClose(hFind);
		return false;
	}
	FindClose(hFind);
	return true;
}

RebDirN::RebDirN(std::string path, RebFileSystemN * fs) : fs(fs)
{
	Path = path;
}

std::vector<std::shared_ptr<IFile>> RebDirN::GetFiles()
{
	std::vector<std::shared_ptr<IFile>> ret;

	if (!isListable())
		return ret;

	WIN32_FIND_DATA ffd;
	HANDLE hFind = INVALID_HANDLE_VALUE;

	hFind = FindFirstFile((Path+"/*").c_str(), &ffd);

	if (hFind != INVALID_HANDLE_VALUE)
	{
		//vannak fájlok, de lehet, hogy mappák...
		//a * miatt a . és .. relatív út is megjelenik, õket ne vegyük figyelembe
		if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && !(ffd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN))
		{
			std::string name = ffd.cFileName;
			if (name[0] != '.')
				ret.push_back(std::shared_ptr<RebFileN>(new RebFileN(Path + "/" + name, fs)));
		}
		while (FindNextFile(hFind, &ffd) != 0)
		{
			if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && !(ffd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN))
			{
				std::string name = ffd.cFileName;
				if (name[0] != '.')
					ret.push_back(std::shared_ptr<RebFileN>(new RebFileN(Path + "/" + name, fs)));
			}
		}
	}
	FindClose(hFind);

	return ret;

}


std::string RebDirN::GetName()
{
	int pos = 0;
	if ((pos = Path.find_last_of("/")) != std::string::npos)
	{
		return Path.substr(pos, Path.length() - pos);
	}
	throw "Invalid Path";
}

bool RebDirN::Exists()
{
	WIN32_FIND_DATA ffd;
	HANDLE hFind = INVALID_HANDLE_VALUE;

	hFind = FindFirstFile(Path.c_str(), &ffd);

	if (hFind != INVALID_HANDLE_VALUE)
	{
		FindClose(hFind);
		return true;
	}
	FindClose(hFind);
	return false;
}


std::vector<std::shared_ptr<IDir>> RebDirN::GetDirs()
{
	std::vector<std::shared_ptr<IDir>> ret;

	if (!isListable())
		return ret;


	WIN32_FIND_DATA ffd;
	HANDLE hFind = INVALID_HANDLE_VALUE;

	hFind = FindFirstFile((Path+"/*").c_str(), &ffd);

	if (hFind != INVALID_HANDLE_VALUE)
	{
		//vannak fájlok, de lehet, hogy mappák...
		//a * miatt a . és .. relatív út is megjelenik, õket ne vegyük figyelembe
		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY && !(ffd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN))
		{
			std::string name = ffd.cFileName;
			if(name[0] != '.')
			ret.push_back(std::shared_ptr<RebDirN>(new RebDirN(Path + "/" + name, fs)));
		}
		while (FindNextFile(hFind, &ffd) != 0)
		{
			if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY && !(ffd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN))
			{
				std::string name = ffd.cFileName;
				if (name[0] != '.')
					ret.push_back(std::shared_ptr<RebDirN>(new RebDirN(Path + "/" + name, fs)));
			}
		}
	}
	FindClose(hFind);
	return ret;
}


std::string RebDirN::GetPath()
{
	return Path;
}


std::shared_ptr<IDir> RebDirN::GetParent()
{
	return std::shared_ptr<RebDirN>(new RebDirN(RebFileSystemN::UpDir(Path), fs));
}


IFileSearch * RebDirN::Search(std::string reg)
{
	std::regex cr(reg);
	RebFileSearchN * ret = (RebFileSearchN *)(fs->GetLastSearchResult());
	ret->Start();
	std::vector<std::shared_ptr<IFile>> files = GetFiles();
	for (size_t i = 0; i < files.size(); i++)
	{
		if (std::regex_match(files[i]->GetPath(), cr))
		{
			ret->GetResult()->push_back(files[i]);
		}
	}

	std::vector<std::shared_ptr<IDir>> dirs = GetDirs();
	for (size_t i = 0; i < dirs.size(); i++)
	{
		dirs[i]->Search(reg);
	}

	ret->End();
	return ret;
}





RebFileSearchN::RebFileSearchN()
{
	slevel = 0;
}

void RebFileSearchN::Start()
{
	if (slevel == 0)
	{
		result.clear();
	}
	slevel++;
}

void RebFileSearchN::End()
{
	slevel--;
}

std::vector<std::shared_ptr<IFile>> * RebFileSearchN::GetResult()
{
	return &result;
}




std::string RebFileSystemN::Unixize(std::string path)
{
	int pos = 0;
	while ((pos = path.find_first_of("\\")) != std::string::npos)
	{
		path[pos] = '/';
	}
	return path;
}

std::string RebFileSystemN::ResolvePathSymbols(std::string path)
{
	path = Unixize(path);
	//resolve ..
	int pos = 0;
	while ((pos = path.find("..")) != std::string::npos)
	{
		if (pos >= 2)
		{
			int bp = path.find_last_of("/", pos - 2);
			int ap = path.find_first_of("/", pos + 2);
			if(bp != std::string::npos && ap != std::string::npos)
			path.erase(bp, ap - bp);
		}
		else
		{
			throw "Relative path not supported!";
		}
	}

	//resolve .

	while ((pos = path.find("/./")) != std::string::npos)
	{
		path.erase(pos, 2);
	}
	return path;
}


std::string RebFileSystemN::ResolveGamePath(std::string path)
{
	if (path[0] == '<')
	{
		for (std::map<std::string, std::string>::iterator i = gpaths.begin(); i != gpaths.end(); i++)
		{
			if (path.find(i->first) != std::string::npos)
			{
				path = i->second + path.substr(i->first.length(), path.length() - i->first.length());
				break;
			}
		}
		if (path.find("<") != std::string::npos)
			throw "Invalid Path";
	}
	return path;
}


std::string RebFileSystemN::UpDir(std::string path)
{
	path = Unixize(path);
	int pos = 0;
	if ((pos = path.find_last_of("/")) != std::string::npos)
	{
		return path.substr(0, pos);
	}
}


RebFileSystemN::RebFileSystemN(RebGDC * gdc)
{
	//Get root dir by the exe
	HMODULE hModule = GetModuleHandleW(NULL);
	char path[MAX_PATH];
	GetModuleFileName(hModule, path, MAX_PATH);

	RebFileN exe(ResolvePathSymbols(path), this);
	root = std::shared_ptr<RebDirN>(new RebDirN(UpDir(UpDir(exe.GetPath())), this));

	//fill gpaths

	gpaths["<root>"] = root->GetPath();
	gpaths["<config>"] = root->GetPath()+"/Config";
	gpaths["<shaders>"] = root->GetPath()+"/Game/Shaders";
	gpaths["<entities>"] = root->GetPath() + "/Game/Entities";
	gpaths["<objects>"] = root->GetPath() + "/Game/Objects";
	gpaths["<scripts>"] = root->GetPath() + "/Game/Scripts";



	gdc->rfs = this;
}



std::shared_ptr<IFile> RebFileSystemN::GetFile(std::string path)
{
	return std::shared_ptr<RebFileN>(new RebFileN(ResolveGamePath(path), this));
}


std::shared_ptr<IDir> RebFileSystemN::GetDir(std::string path)
{
	return std::shared_ptr<RebDirN>(new RebDirN(ResolveGamePath(path), this));
}


std::shared_ptr<IDir> RebFileSystemN::GetRoot()
{
	return root;
}

IFileSearch * RebFileSystemN::GetLastSearchResult()
{
	return &lastsearch;
}

IFileSearch * RebFileSystemN::Search(std::string reg)
{
	return root->Search(reg);
}