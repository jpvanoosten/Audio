#pragma once

#include "miniaudio.h"
#include <Audio/Vector.hpp>

#include <cstdint>

namespace Audio
{
class ListenerImpl
{
public:
    ListenerImpl( uint32_t index, ma_engine* pEngine )
    : index { index }
    , engine { pEngine }
    {}

    ~ListenerImpl() = default;

    void   setPosition( const Vector& pos );
    Vector getPosition() const;

    void   setDirection( const Vector& dir );
    Vector getDirection() const;

    void      setUp( const Vector& up );
    Vector getUp() const;

    void setCone( float innerConeAngle, float outerConeAngle, float outerGain = 1.0f );
    void getCone( float& innerConeAngle, float& outerConeAngle, float& outerGain ) const;

    uint32_t getIndex() const noexcept
    {
        return index;
    }

private:
    uint32_t   index;
    ma_engine* engine = nullptr;
};
}  // namespace Audio
