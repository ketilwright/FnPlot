#include "libGenerator.hpp"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <stdlib.h>
LibGenerator::LibGenerator(std::string const &outPath, std::string const &code)
    :
    m_libPath(outPath)
{
    const std::string cFileName = outPath + ".c";
    const std::string libFileName = outPath + ".so";
    // delete previous c & so file
    std::ostringstream osDeleteC;
    osDeleteC << "rm -f " << cFileName;
    int rcDeleteC = system(osDeleteC.str().c_str());
    std::cout << "delete old C file return code: " << rcDeleteC << std::endl;
    std::ostringstream osDeleteSo;
    osDeleteSo << "rm -f " << libFileName;
    int rcDeleteSo = system(osDeleteSo.str().c_str());
    std::cout << "delete old so file return code: " << rcDeleteSo << std::endl;

    std::ofstream of;
    of.open(cFileName);
    of << "#include <cmath>" << std::endl;
    of << "extern \"C\"" << std::endl;
    of << "{" << std::endl;
    of << "    double compute(double x)" << std::endl;
    of << "    {" << std::endl;
    of << "        return " << code << ";" << std::endl;
    of << "    }" << std::endl;
    of << "}" << std::endl;
    of.close();
    // print it to console to be sure it's ok.
    std::ifstream in;
    in.open(outPath);
    if(in)
    {
        in.seekg(0, in.end);
        size_t length = in.tellg();
        in.seekg(0, in.beg);
        std::string s;
        s.resize(length);
        char *begin = &*s.begin();
        in.read(begin, length);
        in.close();
        std::cout << begin << std::endl;
    }
    // delete any compute.so which existed before
    // run g++ -Wall -shared -fPIC -o ./%outPath%.so %outPath%.c
    std::ostringstream os;
    os << "g++ -Wall -shared -fPIC -o " << outPath << ".so " << outPath << ".c " << std::endl;
    std::cout << "running: " << os.str() << std::endl;
    int rcCompile = system(os.str().c_str());
    std::cout << "compile returns: " << rcCompile << std::endl;

}
LibGenerator::~LibGenerator()
{
    
}
