#include "WaveformImpl.hpp"

#include <Audio/Device.hpp>
#include <Audio/Waveform.hpp>

using namespace Audio;

Waveform::Waveform( Type type, float amplitude, float frequency )
{
    create( type, amplitude, frequency );
}

void Waveform::create( Type type, float amplitude, float frequency )
{
    *this = Device::createWaveform( type, amplitude, frequency );
}

void Waveform::setType( Type type )
{
    impl->setType( type );
}

Waveform::Type Waveform::getType() const noexcept
{
    return impl->getType();
}

void Waveform::setAmplitude( float amplitude )
{
    impl->setAmplitude( amplitude );
}

float Waveform::getAmplitude() const noexcept
{
    return impl->getAmplitude();
}

void Waveform::setFrequency( float frequency )
{
    impl->setFrequency( frequency );
}

float Waveform::getFrequency() const noexcept
{
    return impl->getFrequency();
}

void Waveform::setSampleRate( uint32_t sampleRate )
{
    impl->setSampleRate( sampleRate );
}

uint32_t Waveform::getSampleRate() const noexcept
{
    return impl->getSampleRate();
}

void Waveform::start()
{
    impl->start();
}

void Waveform::stop()
{
    impl->stop();
}

Waveform::Waveform()                                 = default;
Waveform::~Waveform()                                = default;
Waveform::Waveform( const Waveform& )                = default;
Waveform::Waveform( Waveform&& ) noexcept            = default;
Waveform& Waveform::operator=( const Waveform& )     = default;
Waveform& Waveform::operator=( Waveform&& ) noexcept = default;

void Waveform::reset()
{
    impl.reset();
}

Waveform& Waveform::operator=( nullptr_t ) noexcept
{
    impl = nullptr;
    return *this;
}

bool Waveform::operator==( nullptr_t ) const noexcept
{
    return impl == nullptr;
}

bool Waveform::operator!=( nullptr_t ) const noexcept
{
    return impl != nullptr;
}

Waveform::operator bool() const noexcept
{
    return impl != nullptr;
}

std::shared_ptr<WaveformImpl> Waveform::get() const noexcept
{
    return impl;
}

Waveform::Waveform( std::shared_ptr<WaveformImpl> impl )
: impl { std::move( impl ) }
{}
