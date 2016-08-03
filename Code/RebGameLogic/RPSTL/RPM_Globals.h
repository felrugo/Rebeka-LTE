#pragma once
#include <Python.h>
#include <string>
#include "../../RebSupport/RebGDC.h"

/**
Get the GameDataContainer of the module.
\return The GDC of the module.
*/
RebGDC* GetGlobalGDC();

/**
Set the GameDataContainer of the module.
\param set The GDC, that will be the one of the module.
*/
void SetGlobalGDC(RebGDC* set);

/**
Imports the dependant module when it is not imported.
\param modulename The name of the dependant module.
*/
void RebPyDepends(const char* modulename);


/**
Use it to get PType if imported.
\param tname Name of the type.
\return Return the named type from the imported modules.
*/
PyTypeObject * RebPyGetType(const char* tname);