#pragma once

#include "Config.hpp"
#include "Listener.hpp"
#include "Sound.hpp"
#include "Waveform.hpp"

#include <filesystem>

namespace Audio
{
class AUDIO_API Device
{
public:
    /// <summary>
    /// Set the master volume for the audio device. A value of 0 is silent,
    /// a value of 1 is 100% volume and a value over 1 is amplification.
    /// </summary>
    /// <param name="volume">The master volume.</param>
    static void setMasterVolume( float volume );

    /// <summary>
    /// Get a audio listener at a particular index.
    /// </summary>
    /// <remarks>
    /// There is a maximum of 4 listeners at index 0 - 3. Requesting an out-of-range listener
    /// will result in an invalid listener.
    /// </remarks>
    /// <param name="listenerIndex">(optional) The listener index to retrieve. Default: 0</param>
    /// <returns>The listener at the specified index.</returns>
    static Listener getListener( uint32_t listenerIndex = 0 );

    /// <summary>
    /// Load a sound from a file.
    /// Use this method for loading small sound effects.
    /// </summary>
    /// <param name="filePath">The path to the effect file to load.</param>
    /// <returns>A valid sound or empty sound if the file is not valid.</returns>
    static Sound loadSound( const std::filesystem::path& filePath );

    /// <summary>
    /// Load music from a file.
    /// This is intended to be used to load larger, streaming sounds like background music.
    /// </summary>
    /// <param name="filePath">The path to the music file to load.</param>
    /// <returns>A valid sound or empty sound if the file is not valid.</returns>
    static Sound loadMusic( const std::filesystem::path& filePath );

    /// <summary>
    /// Create a waveform.
    /// </summary>
    /// <param name="type">The function to use for the waveform.</param>
    /// <param name="amplitude">The amplitude of the waveform.</param>
    /// <param name="frequency">The frequency of the waveform.</param>
    /// <returns>The waveform.</returns>
    static Waveform createWaveform( Waveform::Type type, float amplitude, float frequency );

    // Singleton class.
    Device()                           = delete;
    ~Device()                          = delete;
    Device( const Device& )            = delete;
    Device( Device&& )                 = delete;
    Device& operator=( const Device& ) = delete;
    Device& operator=( Device&& )      = delete;
};
}  // namespace Audio