#pragma once

#include <Audio/Waveform.hpp>

#include "miniaudio.h"

namespace Audio
{
class WaveformImpl
{
public:
    WaveformImpl( Waveform::Type type, float amplitude, float frequency, ma_engine* pEngine );
    ~WaveformImpl();

    void           setType( Waveform::Type type );
    Waveform::Type getType() const noexcept;

    void  setAmplitude( float amplitude );
    float getAmplitude() const noexcept;

    void  setFrequency( float frequency );
    float getFrequency() const noexcept;

    void setSampleRate( uint32_t sampleRate );
    uint32_t getSampleRate() const noexcept;

    void start();

    void stop();

private:
    Waveform::Type type;
    float          amplitude  = 0.0f;
    float          frequency  = 0.0f;
    uint32_t       sampleRate = 0u;

    ma_waveform waveform {};
    ma_data_source_node node {};
};
}  // namespace Audio
