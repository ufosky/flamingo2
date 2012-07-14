
from distutils.core import setup, Extension

component_module = Extension('python/flamingo/_component',
                           sources=['swig/component_wrap.cxx', 'src/Entity/Entity.cpp', 'src/Entity/Component.cpp',
                               'src/Entity/EntityManager.cpp', 'src/Event/EventManager.cpp','src/FLUtility.cpp'],
                           libraries=['physfs'],
                           include_dirs=['include'],
                           extra_compile_args=['-DSWIG_TYPE_TABLE=flamingo'])

eventmanager_module = Extension('python/flamingo/_eventmanager',
                           sources=['swig/eventmanager_wrap.cxx', 'src/Event/EventManager.cpp'],
                           include_dirs=['include'],
                           extra_compile_args=['-DSWIG_TYPE_TABLE=flamingo'])

entitymanager_module = Extension('python/flamingo/_entitymanager',
                           sources=['swig/entitymanager_wrap.cxx', 'src/Entity/EntityManager.cpp', 'src/Entity/Entity.cpp',
                               'src/Entity/Component.cpp', 'src/Event/EventManager.cpp'],
                           include_dirs=['include'],
                           extra_compile_args=['-DSWIG_TYPE_TABLE=flamingo'])

positioncomp_module = Extension('python/flamingo/components/_positioncomp',
                           sources=['swig/components/positioncomp_wrap.cxx', 'src/Entity/Entity.cpp',
                               'src/Entity/Component.cpp', 'src/Components/PositionComp.cpp'],
                           include_dirs=['include', '/Library/Frameworks/SDL.framework/Headers'],
                           extra_compile_args=['-DSWIG_TYPE_TABLE=flamingo'])
setup (name = 'flamingo ext',
       version = '0.0',
       author      = "Brad Zeis",
       description = """""",
       ext_modules = [component_module, eventmanager_module, entitymanager_module,
                      positioncomp_module])

