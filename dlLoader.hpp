#pragma once

template<typename HandleType>
class LibLoader
{
protected:
    std::string m_libPath;
    HandleType  m_handle;
public:
    LibLoader(std::string const &path)
        :
        m_libPath(path),
        m_handle(0)
        {}
    virtual ~LibLoader(){}    
    HandleType handle() { return m_handle; }
};

#if defined(Darwin) || defined (Linux)
#include <dlfcn.h>
class DlLoader : public LibLoader<void *>
{

public:
    DlLoader(std::string const &path)
        :
        LibLoader(path)
    {
        m_handle = dlopen(m_libPath.c_str(), RTLD_NOW);
    }
    ~DlLoader()
    {
        dlclose(m_handle);
    }
    template<typename FuncType>
    FuncType func(std::string const& funcName)
    {
        return reinterpret_cast<FuncType>(dlsym(m_handle, funcName.c_str()));
    }
    
};
#endif
#if defined(Win32) 
#include <windows.h>
class DlLoader : public LibLoader<HMODULE>
{
public:
    DlLoader(std::string const& path)
        :
        LibLoader(path)
    {
        m_handle = ::LoadLibrary(path.c_str());
    }
    template<typename FuncType>
    FuncType func(std::string const& funcName)
    {
        return reinterpret_cast<FuncType>(GetProcAddress(m_handle, funcName.c_str()));
    }
};
#endif
