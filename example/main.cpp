#include "MarioCoin.hpp"

#include <Audio/Sound.hpp>
#include <Audio/Waveform.hpp>

#include <chrono>
#include <cstdio>
#include <iostream>
#include <thread>

static bool quit = false;

using namespace std::chrono;

enum class State
{
    NarratorPart1,
    Waveform,
    NarratorPart2,
    MarioCoin,
    Wait,
    NarratorPart3
};

void play()
{
    State state = State::NarratorPart1;

    Audio::Sound    narrator { "narrator.flac", Audio::Sound::Type::Music };
    Audio::Waveform waveform { Audio::Waveform::Type::Sine, 0.2f, 500.0f };
    MarioCoin       marioCoin;

    double totalTime = 0.0;

    steady_clock::time_point t0 = steady_clock::now();

    while ( !quit )
    {
        steady_clock::time_point t1 = steady_clock::now();

        auto elapsedTime = duration<double>( t1 - t0 );
        t0               = t1;

        totalTime += elapsedTime.count();

        switch ( state )
        {
        case State::NarratorPart1:
            narrator.play();
            if ( totalTime > 11.5 )
            {
                totalTime = 0.0;
                narrator.pause();
                state = State::Waveform;
            }
            break;
        case State::Waveform:
        {
            waveform.start();
            const auto f = ( std::sin( totalTime ) + 1.0 ) / 2.0 * 1000.0 + 20.0;
            std::cout << "Frequency: " << f << std::endl;

            // Adjust the frequency of the waveform.
            waveform.setFrequency( static_cast<float>( f ) );

            if ( totalTime > 5.0 )
            {
                totalTime = 0.0;
                waveform.stop();
                state = State::NarratorPart2;
            }
        }
        break;
        case State::NarratorPart2:
            narrator.play();
            if ( totalTime > 7.6 )
            {
                totalTime = 0.0;
                narrator.pause();
                state = State::MarioCoin;
            }
            break;
        case State::MarioCoin:
            marioCoin.play();
            state = State::Wait;
            break;
        case State::Wait:
            marioCoin.update( elapsedTime.count() );
            if ( totalTime > 1.0 )
            {
                totalTime = 0.0;
                state     = State::NarratorPart3;
            }
            break;
        case State::NarratorPart3:
            narrator.play();
            if ( totalTime > 1.5 )
            {
                quit = true;
            }
            break;
        }

        std::this_thread::sleep_for( 0.016s );
    }

    exit( 0 );
}

int main( int argc, char* argv[] )
{
    // Parse command-line arguments.
    if ( argc > 1 )
    {
        for ( int i = 0; i < argc; ++i )
        {
            if ( strcmp( argv[i], "-cwd" ) == 0 )
            {
                std::string workingDirectory = argv[++i];
                std::filesystem::current_path( workingDirectory );
            }
        }
    }

    std::thread t { play };

    std::cout << "Press enter to quit..." << std::endl;
    std::ignore = getchar();

    quit = true;

    t.join();

    return 0;
}