#!/usr/bin/env python
 
APPNAME = 'waf-project'
VERSION = '0.1'
 
top = '.'
out = 'build'
 
def options(bld):
    bld.load('compiler_cxx')

def configure(bld):
    bld.load('compiler_cxx')
 
def build(bld):
    bld.stlib(
            source = "src/Screen.cpp", 
            target="Screen", 
            includes=["include"],
            cxxflags=["-std=c++14", "-g", "-Wall"])
         
    bld.program(
            source="src/main.cpp", 
            target="main", 
            includes=["include"],
            cxxflags=["-std=c++14", "-Wall"],
            use="Screen")
