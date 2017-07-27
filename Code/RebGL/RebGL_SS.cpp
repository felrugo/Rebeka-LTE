#include "RebGL_SS.h"


RebShaderSystem::RebShaderSystem(RebGDC * data)
{
	glewInit();
	gdc = data;
	LoadIntoBank();
}


void RebShaderSystem::LoadIntoBank()
{
	//find Shaders.cfg
	std::shared_ptr<IFile> f = gdc->rfs->GetFile("<config>/Shaders.cfg");
	//Open it
	std::string pname;
	std::ifstream file;
	RebGLShaderProgram * prog = 0;
	file.open(f->GetPath());
	if (file.is_open())
	{
		while (!file.eof())
		{
			std::string buffer;
			std::getline(file, buffer);
			if (buffer == "")
				continue;

			if (buffer.back() == ':')
			{
				if (prog != 0)
				{
					//push into bank
					prog->Link();
					Bank[pname] = prog;
				}
				prog = new RebGLShaderProgram();
				pname = buffer.substr(0, buffer.length() - 1);
			}
			else if (prog != 0)
			{
				//load Shader
				prog->AddShaderFile(gdc->rfs->GetFile(buffer));
			}
		}
		if (prog != 0)
		{
			//push into Bank
			prog->Link();
			Bank[pname] = prog;
		}
		//Close
		file.close();
		//End
	}
}



RebShaderSystem::~RebShaderSystem()
{
	for (std::map<std::string, RebGLShaderProgram*>::iterator i = Bank.begin(); i != Bank.end(); i++)
	{
		delete i->second;
	}
}





RebGLShaderProgram * RebShaderSystem::GetFromBank(std::string name)
{
	if (Bank.find(name) != Bank.end())
	{
		return Bank[name];
	}
	return 0;
}



RebGLShaderProgram::RebGLShaderProgram()
{
	linked = false;
	vs = fs = 0;

	phandle = glCreateProgramObjectARB();
}

void RebGLShaderProgram::AddShaderFile(std::shared_ptr<IFile> shad)
{
	RebGLShader * sh = new RebGLShader;
	sh->Source(shad);
	switch (sh->GetType())
	{
	case RS_VERTEX:
		if(vs != 0)
			delete vs;
		vs = sh;
		break;
	case RS_FRAGMENT:
		if(fs != 0)
			delete fs;
		fs = sh;
		break;
	case RS_GEOMETRY:
		if(gs != 0)
			delete gs;
		gs = sh;
		break;
	default:
		break;
	}

	if(!sh->IsCompiled())
		sh->Compile();

glAttachObjectARB(phandle, sh->GetHandle());



	}

	void RebGLShaderProgram::Link()
	{
	glLinkProgramARB(phandle);
	linked = true;
	}

	void RebGLShaderProgram::Use()
	{
		if(!linked)
		Link();
	glUseProgramObjectARB(phandle);
	}

	void RebGLShaderProgram::UseDefault()
	{
		glUseProgramObjectARB(0);
	}

	unsigned int RebGLShaderProgram::GetHandle()
	{
		return phandle;
	}

	RebGLShaderProgram::~RebGLShaderProgram()
	{
		if(vs != 0)
		delete vs;
		if(fs != 0)
		delete fs;
		glDeleteObjectARB(phandle);
	}






RebGLShader::RebGLShader()
{
	error = false; 
	compiled = false;
}

bool RebGLShader::IsCompiled()
{
	return compiled;
}

std::string RebGLShader::GetShaderData(std::string file)
{
	std::ifstream t(file.c_str());
std::string str((std::istreambuf_iterator<char>(t)),
                 std::istreambuf_iterator<char>());
 
return str;
}

void RebGLShader::Source(std::shared_ptr<IFile> file)
{
	shadfile = file;
		if (file->GetPath().find(".rvs", 0, 4) != std::string::npos)
{
	pshader = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
	ty = RS_VERTEX;
}
else if (file->GetPath().find(".rfs", 0, 4) != std::string::npos)
{
pshader = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);
ty = RS_FRAGMENT;
}
	else if (file->GetPath().find(".rgs", 0, 4) != std::string::npos)
{
	pshader = glCreateShaderObjectARB(GL_GEOMETRY_SHADER_ARB);
ty = RS_GEOMETRY;
}
else
{
	return;
}

std::string asd = GetShaderData(file->GetPath());

const char * g = asd.c_str();

glShaderSourceARB(pshader, 1, &g, NULL);

}





void RebGLShader::operator =(RebGLShader e)
{

}


RebGLShader::RebGLShader(const RebGLShader& cop)
{

}


ShaderType RebGLShader::GetType()
{
	return ty;
}

unsigned int RebGLShader::GetHandle()
{
	return pshader;
}

void RebGLShader::Compile()
{
		glCompileShaderARB(pshader);
		GLint isCompiled = 0;
glGetShaderiv(pshader, GL_COMPILE_STATUS, &isCompiled);
if(isCompiled == GL_FALSE)
{
	GLint maxLength = 0;
        glGetShaderiv(pshader, GL_INFO_LOG_LENGTH, &maxLength);
 
        //The maxLength includes the NULL character
        std::vector<char> errorLog(maxLength);
		glGetShaderInfoLog(pshader, maxLength, &maxLength, &errorLog[0]);
	error = true;	
}
compiled = true;
}


	RebGLShader::~RebGLShader()
	{
		glDeleteObjectARB(pshader);
	}