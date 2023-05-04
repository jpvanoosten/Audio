#include <Audio/Device.hpp>

#include "ListenerImpl.hpp"
#include "SoundImpl.hpp"
#include "WaveformImpl.hpp"

#include "miniaudio.h"

#include <iostream>

namespace Audio
{
struct MakeListener : Listener
{
    MakeListener( std::shared_ptr<ListenerImpl> impl )
    : Listener( std::move( impl ) )
    {}
};

struct MakeSound : Sound
{
    MakeSound( std::shared_ptr<SoundImpl> impl )
    : Sound( std::move( impl ) )
    {}
};

struct MakeWaveform : Waveform
{
    MakeWaveform( std::shared_ptr<WaveformImpl> impl )
    : Waveform( std::move( impl ) )
    {}
};

class DeviceImpl
{
public:
    DeviceImpl();
    ~DeviceImpl();

    static DeviceImpl& get()
    {
        static DeviceImpl inst;
        return inst;
    }

    Listener getListener( uint32_t listenerIndex );
    void     setMasterVolume( float volume );

    Sound loadSound( const std::filesystem::path& filePath );

    Sound loadMusic( const std::filesystem::path& filePath );

    Waveform createWaveform( Waveform::Type type, float amplitude, float frequency );

private:
    ma_engine engine {};
};
}  // namespace Audio

using namespace Audio;

DeviceImpl::DeviceImpl()
{
    ma_engine_config config = ma_engine_config_init();
    config.listenerCount    = MA_ENGINE_MAX_LISTENERS;

    if ( ma_engine_init( &config, &engine ) != MA_SUCCESS )
    {
        std::cerr << "Failed to initialize audio engine." << std::endl;
        return;
    }
}

DeviceImpl::~DeviceImpl()
{
#if !defined( Audio_EXPORTS )
    // There is a bug that causes destruction of the audio engine to hang when building
    // as a DLL. This does not happen when building as a static library.
    // As a workaround, don't call this function when building as a DLL
    // until I can find a better solution.
    ma_engine_uninit( &engine );
#endif
}

Listener DeviceImpl::getListener( uint32_t listenerIndex )
{
    if ( listenerIndex < MA_ENGINE_MAX_LISTENERS )
    {
        return MakeListener( std::make_shared<ListenerImpl>( listenerIndex, &engine ) );
    }

    return MakeListener( nullptr );
}

void DeviceImpl::setMasterVolume( float volume )
{
    ma_engine_set_volume( &engine, volume );
}

Sound DeviceImpl::loadSound( const std::filesystem::path& filePath )
{
    auto sound = std::make_shared<SoundImpl>( filePath, &engine, nullptr, MA_SOUND_FLAG_DECODE );
    return MakeSound( std::move( sound ) );
}

Sound DeviceImpl::loadMusic( const std::filesystem::path& filePath )
{
    auto sound = std::make_shared<SoundImpl>( filePath, &engine, nullptr, MA_SOUND_FLAG_STREAM | MA_SOUND_FLAG_NO_SPATIALIZATION );
    return MakeSound( std::move( sound ) );
}

Waveform DeviceImpl::createWaveform( Waveform::Type type, float amplitude, float frequency )
{
    auto waveform = std::make_shared<WaveformImpl>( type, amplitude, frequency, &engine );
    return MakeWaveform( std::move( waveform ) );
}

void Device::setMasterVolume( float volume )
{
    DeviceImpl::get().setMasterVolume( volume );
}

Listener Device::getListener( uint32_t listenerIndex )
{
    return DeviceImpl::get().getListener( listenerIndex );
}

Sound Device::loadSound( const std::filesystem::path& filePath )
{
    return DeviceImpl::get().loadSound( filePath );
}

Sound Device::loadMusic( const std::filesystem::path& filePath )
{
    return DeviceImpl::get().loadMusic( filePath );
}

Waveform Device::createWaveform( Waveform::Type type, float amplitude, float frequency )
{
    return DeviceImpl::get().createWaveform( type, amplitude, frequency );
}
