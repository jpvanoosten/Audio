#include "ListenerImpl.hpp"

using namespace Audio;

void ListenerImpl::setPosition( const Vector& pos )
{
    ma_engine_listener_set_position( engine, index, pos.x, pos.y, pos.z );
}

Vector ListenerImpl::getPosition() const
{
    auto pos = ma_engine_listener_get_position( engine, index );
    return { pos.x, pos.y, pos.z };
}

void ListenerImpl::setDirection( const Vector& dir )
{
    ma_engine_listener_set_direction( engine, index, dir.x, dir.y, dir.z );
}

Vector ListenerImpl::getDirection() const
{
    auto dir = ma_engine_listener_get_direction( engine, index );
    return { dir.x, dir.y, dir.z };
}

void ListenerImpl::setUp( const Vector& up )
{
    ma_engine_listener_set_world_up( engine, index, up.x, up.y, up.z );
}

Vector ListenerImpl::getUp() const
{
    auto up = ma_engine_listener_get_world_up( engine, index );
    return { up.x, up.y, up.z };
}

void ListenerImpl::setCone( float innerConeAngle, float outerConeAngle, float outerGain )
{
    ma_engine_listener_set_cone( engine, index, innerConeAngle, outerConeAngle, outerGain );
}

void ListenerImpl::getCone( float& innerConeAngle, float& outerConeAngle, float& outerGain ) const
{
    ma_engine_listener_get_cone( engine, index, &innerConeAngle, &outerConeAngle, &outerGain );
}
