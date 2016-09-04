#include "RebFileSystem.h"


extern "C"
{
	void _declspec(dllexport) CreateFileSystem(RebGDC * gdc)
	{
		gdc->rfs = new RebFileSystem(gdc);
	}

	void _declspec(dllexport) ReleaseFileSystem(RebGDC * gdc)
	{
		delete gdc->rfs;
		gdc->rfs = 0;
	}
}



RebFile::RebFile(std::string abspath, RebDir * spar)
{
	APath = abspath;
	Par = spar;
}

std::string RebFile::GetName(bool wex)
{
	std::string ret;
	size_t loc = APath.find_last_of("/") + 1;
	if (loc != std::string::npos)
	ret = APath.substr(loc, APath.size() - loc);
	if (!wex)
	{
		loc = ret.find_last_of(".");
		if(loc != std::string::npos)
		ret = ret.substr(0, loc);
	}
	return ret;
}

std::string RebFile::GetAPath()
{
	return APath;
}

std::string RebFile::GetRPath()
{
	return "";
}

std::string RebFile::GetExtension()
{
	size_t loc = APath.find_last_of(".");
	if (loc == std::string::npos)
		return "";
	loc++;
	return APath.substr(loc, APath.size() - loc);
}


IDir * RebFile::GetParent()
{
	return Par;
}




RebDir::RebDir(std::string abspath, RebDir * spar)
{
	APath = abspath;
	Par = spar;

	WIN32_FIND_DATA search_data, sd2;

	std::string ret;
	memset(&search_data, 0, sizeof(WIN32_FIND_DATA));
	memset(&sd2, 0, sizeof(WIN32_FIND_DATA));

	HANDLE nomedia = FindFirstFile((abspath + "/.nomedia").c_str(), &search_data);

	if (nomedia != INVALID_HANDLE_VALUE)
	{
		FindClose(nomedia);
		return;
	}

	HANDLE handle = FindFirstFile((abspath + "/*").c_str(), &search_data);

	while (handle != INVALID_HANDLE_VALUE)
	{
		ret = search_data.cFileName;
		if ((search_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && !(search_data.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN))
		{
			if (ret != "." && ret != "..")
				dirs.push_back(new RebDir(abspath + "/" + ret, this));
		}
		else {
			files.push_back(new RebFile(abspath + "/" + ret, this));
		}
		if (FindNextFile(handle, &search_data) == FALSE)
			break;
	}

	//Close the handle after use or memory/resource leak
	FindClose(handle);
}



std::string RebDir::GetAPath()
{
	return APath;
}

std::string  RebDir::GetRPath()
{
	return "";
}

std::string  RebDir::GetName()
{
	size_t loc = APath.find_last_of("/") + 1;
	return APath.substr(loc, APath.size() - loc);
}


std::vector<IFile*>  RebDir::Search(std::string name)
{
	std::regex am(name);

	std::vector<IFile*> ret;
	ret.clear();
	
	for (std::vector<IFile*>::iterator i = files.begin(); i != files.end(); i++)
	{
		if (std::regex_match((*i)->GetAPath(), am))
		ret.push_back((*i));
	}

	 //Deep search

	for (std::vector<IDir*>::iterator i = dirs.begin(); i != dirs.end(); i++)
	{
		std::vector<IFile*> deeps = (*i)->Search(name);
		ret.insert(ret.end(), deeps.begin(), deeps.end());
	}
	
	return ret;

}

std::vector<IDir*>  RebDir::SearchDir(std::string name)
{
	std::regex am(name);

	std::vector<IDir*> ret;
	ret.clear();

	for (std::vector<IDir*>::iterator i = dirs.begin(); i != dirs.end(); i++)
	{
		if (std::regex_match((*i)->GetAPath(), am))
			ret.push_back((*i));
	}

	//Deep search

	for (std::vector<IDir*>::iterator i = dirs.begin(); i != dirs.end(); i++)
	{
		std::vector<IDir*> deeps = (*i)->SearchDir(name);
		ret.insert(ret.end(), deeps.begin(), deeps.end());
	}

	return ret;
}

std::vector<IFile*>  RebDir::GetAllFiles()
{
	std::vector<IFile*> ret;
	ret.clear();

	for (std::vector<IFile*>::iterator i = files.begin(); i != files.end(); i++)
	{
			ret.push_back((*i));
	}

	//Deep search

	for (std::vector<IDir*>::iterator i = dirs.begin(); i != dirs.end(); i++)
	{
		std::vector<IFile*> deeps = (*i)->GetAllFiles();
		ret.insert(ret.end(), deeps.begin(), deeps.end());
	}

	return ret;
}


std::vector<IDir*> *  RebDir::GetDirs()
{
	return &dirs;
}

std::vector<IFile*> *  RebDir::GetFiles()
{
	return &files;
}


IDir * RebDir::GetParent()
{
	return Par;
}







RebFileSystem::RebFileSystem(RebGDC * gdc)
{
	Root = NULL;
	GetRootAdress();
}

std::string DeWindowsize(std::string path)
{
	while(path.find("\\") != std::string::npos)
	path.at(path.find("\\")) = '/';
	return path;
}

PathType RebFileSystem::GetPT(std::string path) // hybrid path not allowed
{
	path = DeWindowsize(path);
	size_t lastd, lastdd;
	lastd = path.find_last_of(".");
	lastdd = path.find_last_of("..");

	bool rel = (lastdd != std::string::npos);

		if (lastd - 1 != lastdd)
			return (PathType)(PT_ABS_FILE + rel);

		return (PathType)(PT_ABS_DIR + rel);
}

std::string RebFileSystem::SDPathUp(std::string path)
{
	std::string ret = DeWindowsize(path);
	if (ret.find_last_of("/") != std::string::npos)
	{
		ret = ret.substr(0, ret.find_last_of("/"));
	}
	return ret;
}



#ifdef _WIN32

void RebFileSystem::GetRootAdress()
{
	char pb[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, pb);
	Root = new RebDir(SDPathUp(pb));
}


#elif __linux__
#endif




std::vector<IFile*> RebFileSystem::Search(std::string name)
{
	return Root->Search(name);
}

std::vector<IDir*> RebFileSystem::SearchDir(std::string name)
{
	return Root->SearchDir(name);
}

std::vector<IFile*> RebFileSystem::GetAllFiles()
{
	return Root->GetAllFiles();
}