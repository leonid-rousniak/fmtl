#!/usr/bin/env python
 
APPNAME = "waf-project"
VERSION = "0.1"
 
top = "."
out = "build"
libdep = ["curl", "ncurses"]

wafObjects = ["Window", "Screen", "central"]
 
def options(bld):
    bld.load("compiler_cxx")

def configure(conf):
    conf.load("compiler_cxx")
 
def build(bld):

    for wobj in wafObjects:
        bld.objects(
                source = "src/" + wobj + ".cpp", 
                target = wobj, 
                includes=["include"],
                lib = libdep,
                cxxflags=["-std=c++14", "-g", "-Wall"])

    bld.program(
            source="src/main.cpp", 
            target="fmtl", 
            includes=["include"],
            use = wafObjects, 
            lib = libdep,
            cxxflags=["-std=c++14", "-Wall"])

