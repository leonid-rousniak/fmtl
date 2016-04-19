#!/usr/bin/env python
 
APPNAME = 'waf-project'
VERSION = '0.1'
 
top = '.'
out = 'build'
libdep = ['curl', 'ncurses']
 
def options(bld):
    bld.load('compiler_cxx')

def configure(conf):
    conf.load("compiler_cxx")
 
def build(bld):
    bld.objects(
            source = "src/CurlWrap.cpp", 
            target="CurlWrap", 
            includes=["include"],
            #use="termbox",
            lib = libdep,
            cxxflags=["-std=c++14", "-g", "-Wall"])

    bld.objects(
            source = "src/Window.cpp", 
            target="Window", 
            includes=["include"],
            #use="termbox",
            lib = libdep,
            cxxflags=["-std=c++14", "-g", "-Wall"])

    bld.program(
            source="src/main.cpp", 
            target="fmtl", 
            includes=["include"],
            use = "CurlWrap Window",
            lib = libdep,
            cxxflags=["-std=c++14", "-Wall"])
