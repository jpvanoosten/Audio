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

WaveformImpl::WaveformImpl( Waveform::Type _type, float _amplitude, float _frequency, ma_engine* pEngine )
: type( _type )
, amplitude( _amplitude )
, frequency( _frequency )
{
    if ( !pEngine || !pEngine->pDevice )
        return;

    ma_device*               pDevice        = pEngine->pDevice;
    const ma_waveform_config waveformConfig = ma_waveform_config_init( pDevice->playback.format, pDevice->playback.channels, pDevice->sampleRate, ConvertWaveformType( type ), amplitude, frequency );  // NOLINT(clang-diagnostic-double-promotion)
    ma_result                result         = ma_waveform_init( &waveformConfig, &waveform );

    if ( result == MA_SUCCESS )
    {
        // Get the node graph from the engine.
        ma_node_graph* nodeGraph = ma_engine_get_node_graph( pEngine );

        // Create a data source node for the waveform.
        const ma_data_source_node_config dataSourceConfig = ma_data_source_node_config_init( &waveform );
        result                                            = ma_data_source_node_init( nodeGraph, &dataSourceConfig, nullptr, &node );

        if ( result == MA_SUCCESS )
        {
            // Attach the data source node to the endpoint of the engine's node graph.
            ma_node* outputNode = ma_node_graph_get_endpoint( nodeGraph );
            result              = ma_node_attach_output_bus( &node, 0, outputNode, 0 );

            if ( result != MA_SUCCESS )
            {
                std::cerr << "Failed to attach waveform source node to endpoint node." << std::endl;
            }
        }
        else
        {
            std::cerr << "Failed to create data source node for waveform." << std::endl;
        }
    }
    else
    {
        std::cerr << "Failed to initialize waveform." << std::endl;
    }
}

WaveformImpl::~WaveformImpl()
{
    ma_node_detach_output_bus( &node, 0 );
    ma_node_uninit( &node, nullptr );
    ma_waveform_uninit( &waveform );
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
    ma_node_set_state( &node, ma_node_state_started );
}

void WaveformImpl::stop()
{
    ma_node_set_state( &node, ma_node_state_stopped );
}
