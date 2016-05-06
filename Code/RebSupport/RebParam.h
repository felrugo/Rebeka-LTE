#ifndef REBPARAM_H
#define REBPARAM_H

#include <string>

enum ParamType { PT_ANY, PT_INTEGER, PT_BOOL, PT_DOUBLE, PT_STRING, PT_VECTOR };


class RebParam
{
	ParamType type;
	void * Data;
public:
	RebParam();

	RebParam(void*);
	RebParam(int);
	RebParam(bool);
	RebParam(double);
	RebParam(std::string);
	RebParam(RebVector);

	operator void*();
	operator int();
	operator bool();
	operator double();
	operator std::string();
	operator RebVector();

	~RebParam();
};



#ifdef REBENTITYSYSTEM_H

//Python script funcs




#endif


#endif