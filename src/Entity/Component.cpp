
#include "FL/Entity/Component.h"
#include "FL/FLUtility.h"

#include "physfs.h"
#include <iostream>

Component::~Component() {
    if (script != NULL) {
        Py_DECREF(script);
    }
}

bool Component::LoadScript(std::string file, std::string module) {

    if (script != NULL) {
        Py_XDECREF(script);
        script = NULL;
    }

    const char *s = PHYSFS_getRealDir(std::string(PHYSFS_getMountPoint("python/") + file).c_str());
    if (s == NULL) {
        return false;
    }
    
    scriptname = std::string(s) + file;
    std::cout << "Loading: " << scriptname << "\n";

    AddPythonPath(scriptname.substr(0, scriptname.find_last_of("/") + 1));

    // Load Script
    bool res = false;
    PyObject *scriptModule, *scriptName;

    scriptName = PyString_FromString(module.c_str());
    if (scriptName != NULL) {
        scriptModule = PyImport_Import(scriptName);

        if (scriptModule != NULL) {

            PyObject *scriptClass = PyObject_GetAttrString(scriptModule, "FLSCRIPT");
            if (scriptClass != NULL) {

                script = PyObject_CallFunction(scriptClass, NULL);
                if (script != NULL) {
                    res = true;
                }
            }

            Py_XDECREF(scriptClass);
        }

        Py_DECREF(scriptName);
        Py_XDECREF(scriptModule);
    }

    return res;
}

void Component::ProcessScript() {

    if (entity->pyEntity == NULL) {
        entity->LoadPyEntity();
    }

    if (script && entity->pyEntity) {
        PyObject *res = PyObject_CallMethod(script, (char *)"process", (char *)"iO", _type, entity->pyEntity);
        Py_DECREF(res);
    }
}

int Component::Dump(sqlite3 *db) {
    int rc;
    char *msg, *query;

    query = sqlite3_mprintf("create table if not exists tblComponent_%d(componentID int PRIMARY KEY, scriptName text);"
            "insert into tblComponent_%d (componentID, scriptname) values (%d, '%q')", _type, _type, _id, scriptname.c_str());
    rc = sqlite3_exec(db, query, NULL, NULL, &msg);
    if (rc) {
        return rc;
    }

    return rc;
}

int Component::Load(sqlite3 *db) {
    return 0;
}

int Component::DumpScript(PyObject *data) {
    return 0;
}

int Component::LoadScript() {
    return 0;
}

