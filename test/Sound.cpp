
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
/**
*** SFML
***/
#include <SFML/Audio.hpp>
#include <iomanip>
#include <iostream>
#include <string>

/**
*** CV
***/

#include <cv.h>
#include <highgui.h>
#include "OpencvLib.h"

/**
*** Event Dispatcher
***/

#include <iostream>
#include <unistd.h>
#include "EventDispatcher.h"




class Foo : public EventDispatcher {
     public:
        void Run (int action) {
            for ( int key = 0 ; key < 5 ; key ++ ) {
                this->DispatchEvent ( "EVENT_1" );
                this->DispatchEvent ( "EVENT_2" );
                usleep ( 500000 );
            };
        };
};

class Bar {
     public:
        void EventHandler1 (void) {
            cout << "FOO_EVENT_1 listen next\n";
        };

        void EventHandler2 (void) {
            cout << "FOO_EVENT_2 listen prev \n";
        };
};







////////////////////////////////////////////////////////////
/// Play a sound
///
////////////////////////////////////////////////////////////
void playSound()
{
    // Load a sound buffer from a wav file
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("resources/canary.wav"))
        return;

    // Display sound informations
    std::cout << "canary.wav:" << std::endl;
    std::cout << " " << buffer.getDuration().asSeconds() << " seconds"       << std::endl;
    std::cout << " " << buffer.getSampleRate()           << " samples / sec" << std::endl;
    std::cout << " " << buffer.getChannelCount()         << " channels"      << std::endl;

    // Create a sound instance and play it
    sf::Sound sound(buffer);
    sound.play();

    // Loop while the sound is playing
    while (sound.getStatus() == sf::Sound::Playing)
    {
        // Leave some CPU time for other processes
        sf::sleep(sf::milliseconds(100));

        // Display the playing position
        std::cout << "\rPlaying... " << std::fixed << std::setprecision(2) << sound.getPlayingOffset().asSeconds() << " sec   ";
        std::cout << std::flush;
    }
    std::cout << std::endl << std::endl;
}


////////////////////////////////////////////////////////////
/// Play a music
///
////////////////////////////////////////////////////////////
void playMusic(const std::string& filename)
{
    // Load an ogg music file
    sf::Music music;
    if (!music.openFromFile("resources/" + filename))
        return;

    // Display music informations
    std::cout << filename << ":" << std::endl;
    std::cout << " " << music.getDuration().asSeconds() << " seconds"       << std::endl;
    std::cout << " " << music.getSampleRate()           << " samples / sec" << std::endl;
    std::cout << " " << music.getChannelCount()         << " channels"      << std::endl;

    // Play it
    music.play();

    // Loop while the music is playing
    while (music.getStatus() == sf::Music::Playing)
    {
        // Leave some CPU time for other processes
        sf::sleep(sf::milliseconds(100));

        // Display the playing position
        std::cout << "\rPlaying... " << std::fixed << std::setprecision(2) << music.getPlayingOffset().asSeconds() << " sec   ";
        std::cout << std::flush;
    }
    std::cout << std::endl << std::endl;
}


////////////////////////////////////////////////////////////
/// Entry point of application
///
/// \return Application exit code
///
////////////////////////////////////////////////////////////
int main()
{

    Foo* foo = new Foo ( );
    Bar* bar = new Bar ( );

    foo->AddEventListener ( "EVENT_1" , bar , &Bar::EventHandler1 ); //äîáàâëÿåì ñëóøàòåëÿ (ïîäïèñûâàåì) îáúåêò bar íà ñîáûòèå EVENT_1

    ImageFacade facade;
    int action = facade.Get_action();
    foo->Run(action);


    foo->RemoveEventListener ( "EVENT_1" , bar , &Bar::EventHandler1 ); // Óäàëÿåì ñëóøàòåëÿ
    foo->AddEventListener ( "EVENT_2" , bar , &Bar::EventHandler2 );
    action = facade.Get_action();
    foo->Run(action);
    foo->RemoveEventListener ( "EVENT_2" , bar , &Bar::EventHandler2 );



    // Play a sound
    // playSound();

    // Play music from an ogg file
    playMusic("yeah.ogg");

    // Play music from a flac file
    // playMusic("ding.flac");

    // Wait until the user presses 'enter' key
    std::cout << "Press enter to exit..." << std::endl;
    std::cin.ignore(10000, '\n');

    return EXIT_SUCCESS;
}
