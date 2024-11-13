#ifndef _I_PLUGIN_EXPORT_H_
#define _I_PLUGIN_EXPORT_H_

#ifdef WIN32
#ifndef PLUGIN_BUILD_STATIC
    #ifdef PLUGIN_LIBRARY
        #define IPLUGINEXPORT __declspec(dllexport)
    #else
        #define IPLUGINEXPORT __declspec(dllimport)
    #endif
#endif
#else   // UNIX
    #define IPLUGINEXPORT __attribute__((visibility ("default")))
#endif

#endif /* _I_PLUGIN_EXPORT_H_ */
