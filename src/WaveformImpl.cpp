#include "WaveformImpl.hpp"

#include "Audio/Waveform.hpp"

#include <iostream>

using namespace Audio;

static ma_waveform_type ConvertWaveformType( Waveform::Type type )
{
    switch ( type )
    {
    case Waveform::Type::Sine:
        return ma_waveform_type_sine;
    case Waveform::Type::Square:
        return ma_waveform_type_square;
    case Waveform::Type::Triangle:
        return ma_waveform_type_triangle;
    case Waveform::Type::Sawtooth:
        return ma_waveform_type_sawtooth;
    }

    return ma_waveform_type_sine;
}

static Waveform::Type ConvertWaveformType( ma_waveform_type type )
{
    switch ( type )
    {
    case ma_waveform_type_sine:
        return Waveform::Type::Sine;
    case ma_waveform_type_square:
        return Waveform::Type::Square;
    case ma_waveform_type_triangle:
        return Waveform::Type::Triangle;
    case ma_waveform_type_sawtooth:
        return Waveform::Type::Sawtooth;
    }

    return Waveform::Type::Sine;
}

/// <summary>
/// Callback function to read waveform data.
/// See: https://miniaud.io/docs/examples/simple_playback_sine.html
/// </summary>
static void waveform_callback( ma_device* pDevice, void* output, const void*, ma_uint32 frameCount )
{
    ma_waveform* waveform = static_cast<ma_waveform*>( pDevice->pUserData );
    if ( !waveform )
        return;

    ma_waveform_read_pcm_frames( waveform, output, frameCount, nullptr );
}

WaveformImpl::WaveformImpl( Waveform::Type _type, float _amplitude, float _frequency, const ma_engine* pEngine )
: type( _type )
, amplitude( _amplitude )
, frequency( _frequency )
{
    if ( !pEngine || !pEngine->pDevice || !pEngine->pDevice->pContext )
        return;

    // Create a device to play the waveform.
    ma_device_config deviceConfig  = ma_device_config_init( ma_device_type_playback );
    deviceConfig.playback.format   = ma_format_f32;
    deviceConfig.playback.channels = pEngine->pDevice->playback.channels;
    deviceConfig.sampleRate        = pEngine->pDevice->sampleRate;
    deviceConfig.dataCallback      = &waveform_callback;
    deviceConfig.pUserData         = &waveform;

    if ( ma_device_init( pEngine->pDevice->pContext, &deviceConfig, &device ) != MA_SUCCESS )
    {
        std::cerr << "Failed to initialize audio device." << std::endl;
        return;
    }

    ma_waveform_config config = ma_waveform_config_init( device.playback.format, device.playback.channels, device.sampleRate, ConvertWaveformType( type ), amplitude, frequency );  // NOLINT(clang-diagnostic-double-promotion)
    ma_waveform_init( &config, &waveform );
}

WaveformImpl::~WaveformImpl()
{
    ma_waveform_uninit( &waveform );
    ma_device_uninit( &device );
}

void WaveformImpl::setType( Waveform::Type _type )
{
    type = _type;
    ma_waveform_set_type( &waveform, ConvertWaveformType( type ) );
}

Waveform::Type WaveformImpl::getType() const noexcept
{
    return type;
}

void WaveformImpl::setAmplitude( float _amplitude )
{
    amplitude = _amplitude;
    ma_waveform_set_amplitude( &waveform, amplitude );  // NOLINT(clang-diagnostic-double-promotion)
}

float WaveformImpl::getAmplitude() const noexcept
{
    return amplitude;
}

void WaveformImpl::setFrequency( float _frequency )
{
    frequency = _frequency;
    ma_waveform_set_frequency( &waveform, frequency );  // NOLINT(clang-diagnostic-double-promotion)
}

float WaveformImpl::getFrequency() const noexcept
{
    return frequency;
}

void WaveformImpl::setSampleRate( uint32_t _sampleRate )
{
    sampleRate = _sampleRate;
    ma_waveform_set_sample_rate( &waveform, sampleRate );
}

uint32_t WaveformImpl::getSampleRate() const noexcept
{
    return sampleRate;
}

void WaveformImpl::start()
{
    ma_device_start( &device );
}

void WaveformImpl::stop()
{
    ma_device_stop( &device );
}
