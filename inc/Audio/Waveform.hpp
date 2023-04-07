#pragma once

#include <memory>

namespace Audio
{
class WaveformImpl;

class Waveform
{
public:
    /// <summary>
    /// Waveform function.
    /// </summary>
    enum class Type
    {
        Sine,
        Square,
        Triangle,
        Sawtooth
    };

    Waveform( Type type, float amplitude, float frequency );

    void create( Type type, float amplitude, float frequency );

    void setType( Type type );
    Type getType() const noexcept;

    void setAmplitude( float amplitude );
    float getAmplitude() const noexcept;

    void setFrequency( float frequency );
    float getFrequency() const noexcept;

    void setSampleRate( uint32_t sampleRate );
    uint32_t getSampleRate() const noexcept;

    void start();

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
