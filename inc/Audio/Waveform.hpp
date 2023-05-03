#pragma once

#include "Config.hpp"

#include <memory>

namespace Audio
{
class WaveformImpl;

class AUDIO_API Waveform
{
public:
    /// <summary>
    /// Waveform function.
    /// </summary>
    enum class Type
    {
        Sine,       ///< Sine wave function. See: https://en.wikipedia.org/wiki/Sine_wave
        Square,     ///< Square wave function. See: https://en.wikipedia.org/wiki/Square_wave
        Triangle,   ///< Triangle wave function. See: https://en.wikipedia.org/wiki/Triangle_wave
        Sawtooth    ///< Sawtooth wave function. See: https://en.wikipedia.org/wiki/Sawtooth_wave
    };

    /// <summary>
    /// Construct a waveform.
    /// </summary>
    /// <param name="type">The function type for the waveform.</param>
    /// <param name="amplitude">The amplitude of the waveform.</param>
    /// <param name="frequency">The frequency (in Hz) of the waveform.</param>
    Waveform( Type type, float amplitude = 1.0f, float frequency = 0.0f );

    /// <summary>
    /// Construct a new waveform (replacing the current waveform if one was previously created for this object.
    /// </summary>
    /// <param name="type">The function type for the waveform.</param>
    /// <param name="amplitude">The amplitude of the waveform.</param>
    /// <param name="frequency">The frequency (in Hz) of the waveform.</param>
    void create( Type type, float amplitude = 1.0f, float frequency = 0.0f );

    /// <summary>
    /// Set the function type for the waveform.
    /// </summary>
    /// <param name="type">The type of the waveform.</param>
    void setType( Type type );

    /// <summary>
    /// Get the function type for this waveform.
    /// </summary>
    /// <returns>The waveform type.</returns>
    Type getType() const noexcept;

    /// <summary>
    /// Set the amplitude of the waveform.
    /// </summary>
    /// <param name="amplitude">The waveform amplitude.</param>
    void setAmplitude( float amplitude );

    /// <summary>
    /// Get the amplitude of this waveform.
    /// </summary>
    /// <returns>The amplitude of this waveform.</returns>
    float getAmplitude() const noexcept;

    /// <summary>
    /// Set the frequency (in Hz) of the waveform.
    /// </summary>
    /// <param name="frequency">The frequency (in Hz) of the waveform.</param>
    void setFrequency( float frequency );

    /// <summary>
    /// Get the frequency of the waveform.
    /// </summary>
    /// <returns>The frequency (in Hz) of this waveform.</returns>
    float getFrequency() const noexcept;

    /// <summary>
    /// Set the sample rate (samples/second) for the waveform.
    /// </summary>
    /// <param name="sampleRate">The waveform sample rate.</param>
    void setSampleRate( uint32_t sampleRate );

    /// <summary>
    /// Get the sample rate for the waveform.
    /// </summary>
    /// <returns>The sample rate (samples/second) of this waveform.</returns>
    uint32_t getSampleRate() const noexcept;

    /// <summary>
    /// Start playing the waveform.
    /// </summary>
    void start();

    /// <summary>
    /// Stop playing the waveform.
    /// </summary>
    void stop();

    Waveform();
    Waveform( const Waveform& );
    Waveform( Waveform&& ) noexcept;
    Waveform& operator=( const Waveform& );
    Waveform& operator=( Waveform&& ) noexcept;

    /// <summary>
    /// Reset the underlying pointer object.
    /// If this is the last reference, the object is destroyed.
    /// </summary>
    void reset();

    /// <summary>
    /// Allow nullptr assignment.
    /// </summary>
    /// <remarks>
    /// Assigning `nullptr` will release the underlying implementation.
    /// This is the same as using the `reset` function on this object.
    /// </remarks>
    Waveform& operator=( nullptr_t ) noexcept;

    /// <summary>
    /// Allow for null checks.
    /// </summary>
    bool operator==( nullptr_t ) const noexcept;
    bool operator!=( nullptr_t ) const noexcept;

    /// <summary>
    /// Explicit bool conversion allows to check for a valid object.
    /// </summary>
    /// <returns>`true` if this object contains a valid pointer to implementation. `false` otherwise.</returns>
    explicit operator bool() const noexcept;

protected:
    explicit Waveform( std::shared_ptr<WaveformImpl> impl );

private:
    std::shared_ptr<WaveformImpl> impl;
};

}  // namespace Audio
