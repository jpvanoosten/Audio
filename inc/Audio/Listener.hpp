#pragma once

#include "Config.hpp"
#include "Vector.hpp"

#include <memory>

namespace Audio
{
class ListenerImpl;

class AUDIO_API Listener
{
public:
    /// <summary>
    /// The global (world) position of the listener.
    /// </summary>
    /// <param name="pos">The position of the listener.</param>
    void setPosition( const Vector& pos );

    /// <summary>
    /// Get the global (world) position of the listener.
    /// </summary>
    /// <returns>The position of the listener.</returns>
    Vector getPosition() const;

    /// <summary>
    /// Set the forward direction vector of the listener.
    /// </summary>
    /// <param name="dir">The direction of the listener.</param>
    void setDirection( const Vector& dir );

    /// <summary>
    /// Get the forward direction vector of the listener.
    /// </summary>
    /// <returns>The direction vector of the listener.</returns>
    Vector getDirection() const;

    /// <summary>
    /// Set the up direction vector of the listener.
    /// </summary>
    /// <param name="up">The up vector of the listener.</param>
    void setUp( const Vector& up );

    /// <summary>
    /// Get the up direction vector of the listener.
    /// </summary>
    /// <returns>The up vector of the listener.</returns>
    Vector getUp() const;

    /// <summary>
    /// Set the listener cone angles.
    /// </summary>
    /// <remarks>
    /// When a sound is inside the inner code, no directional attenuation is
    /// applied. When the sound is outside of the outer cone, the attenuation
    /// will be set to outerGain. When the sound is in between the inner and
    /// outer cones, the attenuation will be interpolated between 1 and the
    /// outer gain.
    /// </remarks>
    /// <param name="innerConeAngle">The angle of the inner cone.</param>
    /// <param name="outerConeAngle">The angle of the outer cone.</param>
    /// <param name="outerGain">The gain to use when the sound is outside the `outerConeAngle`.</param>
    void setCone( float innerConeAngle, float outerConeAngle, float outerGain );

    /// <summary>
    /// Get the listener cone angles.
    /// </summary>
    /// <param name="innerConeAngle">The angle of the inner cone.</param>
    /// <param name="outerConeAngle">The angle of the outer cone.</param>
    /// <param name="outerGain">The gain to use when the sound is outside the `outerConeAngle`.</param>
    void getCone( float& innerConeAngle, float& outerConeAngle, float& outerGain ) const;

    Listener();
    Listener( const Listener& );
    Listener( Listener&& ) noexcept;
    Listener& operator=( const Listener& );
    Listener& operator=( Listener&& ) noexcept;

    /// <summary>
    /// Allow nullptr assignment.
    /// </summary>
    /// <remarks>
    /// Assigning `nullptr` will release the underlying implementation.
    /// This is the same as using the `reset` function on this object.
    /// </remarks>
    Listener& operator=( nullptr_t ) noexcept;

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

    /// <summary>
    /// Get the pointer to the implementation.
    /// </summary>
    /// <returns>The pointer to the listener implementation.</returns>
    std::shared_ptr<ListenerImpl> get() const noexcept;

protected:
    Listener( std::shared_ptr<ListenerImpl> impl );

private:
    std::shared_ptr<ListenerImpl> impl;
};
}  // namespace Audio
