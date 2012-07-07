
from distutils.core import setup, Extension

component_module = Extension('lib/python/_component',
                           sources=['swig/component_wrap.cxx', 'src/Entity/Entity.cpp'],
                           extra_compile_args=['-Iinclude'])

setup (name = 'example',
       version = '0.0',
       author      = "Brad Zeis",
       description = """""",
       ext_modules = [component_module])

