#pragma once

#if defined( _WIN32 )
    #define AUDIO_IMPORT __declspec( dllimport )
    #define AUDIO_EXPORT __declspec( dllexport )
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