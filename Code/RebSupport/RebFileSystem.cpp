#include "RebFileSystem.h"



RebFile::RebFile(std::string abspath)
{
	APath = abspath;
}

std::string RebFile::GetName()
{
	size_t loc = APath.find_last_of("/") + 1;
	return APath.substr(loc, APath.size() - loc);
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





RebDir::RebDir(std::string abspath)
{
	APath = abspath;

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
				dirs.push_back(new RebDir(abspath + "/" + ret));
		}
		else {
			files.push_back(new RebFile(abspath + "/" + ret));
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


std::vector<RebFile*>  RebDir::Search(std::string name)
{
	std::vector<RebFile*> ret;
	ret.clear();
	
	for (std::vector<RebFile*>::iterator i = files.begin(); i != files.end(); i++)
	{
		if ((*i)->GetName() == name)
		ret.push_back((*i));
	}

	 //Deep search

	for (std::vector<RebDir*>::iterator i = dirs.begin(); i != dirs.end(); i++)
	{
		std::vector<RebFile*> deeps = (*i)->Search(name);
		ret.insert(ret.end(), deeps.begin(), deeps.end());
	}
	
	return ret;

}

std::vector<RebDir*>  RebDir::SearchDir(std::string name)
{
	std::vector<RebDir*> ret;
	ret.clear();

	for (std::vector<RebDir*>::iterator i = dirs.begin(); i != dirs.end(); i++)
	{
		if ((*i)->GetName() == name)
			ret.push_back((*i));
	}

	//Deep search

	for (std::vector<RebDir*>::iterator i = dirs.begin(); i != dirs.end(); i++)
	{
		std::vector<RebDir*> deeps = (*i)->SearchDir(name);
		ret.insert(ret.end(), deeps.begin(), deeps.end());
	}

	return ret;
}

std::vector<RebFile*>  RebDir::GetAllFiles()
{
	std::vector<RebFile*> ret;
	ret.clear();

	for (std::vector<RebFile*>::iterator i = files.begin(); i != files.end(); i++)
	{
			ret.push_back((*i));
	}

	//Deep search

	for (std::vector<RebDir*>::iterator i = dirs.begin(); i != dirs.end(); i++)
	{
		std::vector<RebFile*> deeps = (*i)->GetAllFiles();
		ret.insert(ret.end(), deeps.begin(), deeps.end());
	}

	return ret;
}


std::vector<RebDir*> *  RebDir::GetDirs()
{
	return &dirs;
}

std::vector<RebFile*> *  RebDir::GetFiles()
{
	return &files;
}










RebFileSystem::RebFileSystem()
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




std::vector<RebFile*> RebFileSystem::GetAllFiles()
{
	return Root->GetAllFiles();
}




#elif __linux__
#endif




std::vector<RebFile*> RebFileSystem::Search(std::string name)
{
	return Root->Search(name);
}

std::vector<RebDir*> RebFileSystem::SearchDir(std::string name)
{
	return Root->SearchDir(name);
}