/*
** DLLoader.hpp for OOP_Bootstrap_Arcade_2019 in /home/arthurbertaud/Second_year/OOP/OOP_Bootstrap_Arcade_2019
**
** Made by arthurbertaud
** Login   <EPITECH>
**
** Started on  Tue Mar 3 11:21:01 AM 2020 arthurbertaud
** Last update Sat Mar 13 8:58:09 PM 2020 arthurbertaud
*/

#ifndef DLLOADER_HPP_
#define DLLOADER_HPP_

#include <dlfcn.h>
#include <iostream>
#include "Error.hpp"

class DLLoader
{
public:
    DLLoader(const std::string &libpath)
    try : _handler(nullptr)
    {
        _handler = dlopen(libpath.c_str(), RTLD_NOW);
        if (!_handler) {
            throw ErrorDLLoader(dlerror());
        }
    }
    catch (ErrorDLLoader const &err)
    {
        throw err;
    }

    template <typename T>
    T *getInstance(const std::string &name) const
    {
        T *(*sample)(void);
        char *error;

        sample = reinterpret_cast<T *(*)()>(dlsym(_handler, name.c_str()));
        if ((error = dlerror()) != NULL)
            throw ErrorDLLoader(error);
        return (sample());
    }
    DLLoader(const DLLoader &other) = default;
    DLLoader &operator=(const DLLoader &other) = default;
    ~DLLoader()
    {
        if (dlclose(_handler) != 0)
            std::cerr << dlerror() << std::endl;
    }

protected:
private:
    void *_handler;
};
#endif /* !DLLOADER_HPP_ */
