#include <Audio/Waveform.hpp>

#include <chrono>
#include <cstdio>
#include <iostream>
#include <thread>

static bool quit = false;

using namespace std::chrono;

void play()
{
    Audio::Waveform waveform { Audio::Waveform::Type::Sine, 0.2f, 500.0f };
    // Start playing the waveform.
    waveform.start();

    double totalTime = 0.0;

    steady_clock::time_point t0 = steady_clock::now();

    while ( !quit )
    {
        steady_clock::time_point t1 = steady_clock::now();

        auto elapsedTime = duration<double>( t1 - t0 );
        t0               = t1;

        totalTime += elapsedTime.count();

        const auto f = ( std::sin( totalTime ) + 1.0 ) / 2.0 * 1000.0 + 20.0;
        std::cout << "Frequency: " << f << std::endl;

        // Adjust the frequency of the waveform.
        waveform.setFrequency( static_cast<float>( f ) );

        std::this_thread::sleep_for( 0.016s );
    }

    waveform.stop();
}

int main()
{
    std::thread t { play };

    std::cout << "Press enter to quit..." << std::endl;
    std::ignore = getchar();

    quit = true;

    t.join();

    return 0;
}