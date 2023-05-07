#pragma once

#if defined( _WIN32 ) || defined( __CYGWIN__ )
    #define AUDIO_IMPORT __declspec( dllimport )
    #define AUDIO_EXPORT __declspec( dllexport )
#elif defined(__GNUC__) && __GNUC__ >= 4
    #define AUDIO_IMPORT __attribute__ ((visibility ("default")))
    #define AUDIO_EXPORT __attribute__ ((visibility ("default")))
#else
    #define AUDIO_IMPORT
    #define AUDIO_EXPORT
#endif

#if defined( Audio_EXPORTS )
    #define AUDIO_API AUDIO_EXPORT
    #define AUDIO_EXTERN
#elif defined( Audio_IMPORTS )
    #define AUDIO_API    AUDIO_IMPORT
    #define AUDIO_EXTERN extern
#else
    #define AUDIO_API
    #define AUDIO_EXTERN
#endif