#include <Audio/Listener.hpp>
#include "ListenerImpl.hpp"

using namespace Audio;

Listener::Listener( std::shared_ptr<ListenerImpl> impl )
: impl { std::move(impl) }
{}

Listener::Listener()                                 = default;
Listener::Listener( const Listener& )                = default;
Listener::Listener( Listener&& ) noexcept            = default;
Listener::~Listener()                                = default;
Listener& Listener::operator=( const Listener& )     = default;
Listener& Listener::operator=( Listener&& ) noexcept = default;
Listener& Listener::operator=( nullptr_t ) noexcept
{
    impl = nullptr;
    return *this;
}

bool Listener::operator==( nullptr_t ) const noexcept
{
    return impl == nullptr;
}

bool Listener::operator!=( nullptr_t ) const noexcept
{
    return impl != nullptr;
}

void Listener::setPosition( const Vector& pos )
{
    impl->setPosition( pos );
}

Vector Listener::getPosition() const
{
    return impl->getPosition();
}

void Listener::setDirection( const Vector& dir )
{
    impl->setDirection( dir );
}

Vector Listener::getDirection() const
{
    return impl->getDirection();
}

void Listener::setUp( const Vector& up )
{
    impl->setUp( up );
}

Vector Listener::getUp() const
{
    return impl->getUp();
}

void Listener::setCone( float innerConeAngle, float outerConeAngle, float outerGain )
{
    impl->setCone( innerConeAngle, outerConeAngle, outerGain );
}

void Listener::getCone( float& innerConeAngle, float& outerConeAngle, float& outerGain ) const
{
    impl->getCone( innerConeAngle, outerConeAngle, outerGain );
}

Listener::operator bool() const noexcept
{
    return impl != nullptr;
}

std::shared_ptr<ListenerImpl> Listener::get() const noexcept
{
    return impl;
}
