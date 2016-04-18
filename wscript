#!/usr/bin/env python
 
APPNAME = 'waf-project'
VERSION = '0.1'
 
top = '.'
out = 'build'
 
def options(bld):
    bld.load('compiler_cxx')

def configure(conf):
        from waflib.Tools.compiler_cxx import cxx_compiler
        conf.env.CXX = "/usr/bin/g++-5" #specify the cxx compiler.
        conf.load("compiler_cxx")
        print conf.env
	conf.check(header_name="stdio.h", features="cxx cxxprogram", mandatory=False)
 
def build(bld):
    bld.objects(
            source = "src/CurlWrap.cpp", 
            target="CurlWrap", 
            includes=["include"],
            #use="termbox",
            lib = ["curl"],
            cxxflags=["-std=c++14", "-g", "-Wall"])

    bld.objects(
            source = "src/URL.cpp", 
            target="URL", 
            includes=["include"],
            #use="termbox",
            lib = ["curl"],
            cxxflags=["-std=c++14", "-g", "-Wall"])

    bld.program(
            source="src/main.cpp", 
            target="fmtl", 
            includes=["include"],
            use = "CurlWrap URL",
            lib = ["curl"],
            cxxflags=["-std=c++14", "-Wall"])
