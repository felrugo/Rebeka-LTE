#include "RebGL_SS.h"


RebShaderSystem::RebShaderSystem(RebGDC * data)
{
	gdc = data;
	LoadIntoBank();
}


void RebShaderSystem::LoadIntoBank()
{
	//find Shaders.cfg
	RebFile * f = gdc->rfs->Search("Shaders.cfg")[0];
	//Open it
	std::string pname;
	std::ifstream file;
	RebGLShaderProgram * prog = 0;
	file.open(f->GetAPath());
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
				prog->AddShaderFile(gdc->rfs->Search(buffer)[0]);
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

void RebGLShaderProgram::AddShaderFile(RebFile * shad)
{
	RebGLShader * sh = new RebGLShader;
	sh->Source(shad);
	switch (sh->GetType())
	{
	case RebGLShader::RS_VERTEX:
		if(vs != 0)
			delete vs;
		vs = sh;
		break;
	case RebGLShader::RS_FRAGMENT:
		if(fs != 0)
			delete fs;
		fs = sh;
		break;
	case RebGLShader::RS_GEOMETRY:
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
	error = new bool(false); 
	compiled = new bool(false);
	copied = new unsigned int;
	*copied = 0;
}

bool RebGLShader::IsCompiled()
{
	return *compiled;
}

std::string RebGLShader::GetShaderData(std::string file)
{
	std::ifstream t(file.c_str());
std::string str((std::istreambuf_iterator<char>(t)),
                 std::istreambuf_iterator<char>());
 
return str;
}

void RebGLShader::Source(RebFile * file)
{
		if (file->GetAPath().find(".rvs", 0, 4) != std::string::npos)
{
	pshader = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
	ty = RS_VERTEX;
}
else if (file->GetAPath().find(".rfs", 0, 4) != std::string::npos)
{
pshader = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);
ty = RS_FRAGMENT;
}
	else if (file->GetAPath().find(".rgs", 0, 4) != std::string::npos)
{
	pshader = glCreateShaderObjectARB(GL_GEOMETRY_SHADER_ARB);
ty = RS_GEOMETRY;
}
else
{
	return;
}

std::string asd = GetShaderData(file->GetAPath());

const char * g = asd.c_str();

glShaderSourceARB(pshader, 1, &g, NULL);

}





void RebGLShader::operator =(RebGLShader e)
{
	if(*copied > 0)
	{
	*copied = *copied - 1;
	}
	pshader =  e.pshader;
	ty = e.ty;
	compiled = e.compiled;
	error = e.error;
	copied = e.copied;
	*copied = *copied + 1;
	
}


RebGLShader::RebGLShader(const RebGLShader& cop)
{
pshader =  cop.pshader;
	ty = cop.ty;
	compiled = cop.compiled;
	error = cop.error;
	copied = cop.copied;
	*copied = *copied + 1;
}


RebGLShader::ShaderType RebGLShader::GetType()
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
	*error = true;	
}
*compiled = true;
}


	RebGLShader::~RebGLShader()
	{
		glDeleteObjectARB(pshader);
	}