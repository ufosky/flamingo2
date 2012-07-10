
#include "FL/FLUtility.h"
#include <Python.h>

void AddPythonPath(std::string path) {
    PyObject *sysModule;

    PyObject *sysName = PyString_FromString("sys");
    if (sysName != NULL) {

        sysModule = PyImport_Import(sysName);
        Py_DECREF(sysName);

        if (sysModule != NULL) {

            PyObject *sysPath = PyObject_GetAttrString(sysModule, "path");

            if (sysPath != NULL) {

                PyObject *loadPath = PyString_FromString(path.c_str());

                if (loadPath != NULL) {
                    PyList_Append(sysPath, loadPath);
                    Py_DECREF(loadPath);
                    Py_DECREF(sysPath);
                }
            }
            Py_DECREF(sysModule);
        }
    }
}

