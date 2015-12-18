////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include < SFML / Audi.hpp >

    #include < iomanip >

    #include < iosream >

    #include < string >




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

    std::cout << " " << buffer.getDuration().asSeconds() << " seconds" << std::endl;

    std::cout << " " << buffer.getSampleRate() << " samples / sec" << std::endl;

    std::cout << " " << buffer.getChannelCount() << " channels" << std::endl;



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

void playMusic(const std::string & filename)

{

    // Load an ogg music file

    sf::Music music;

    if (!music.openFromFile("resources/" + filename))

        return;



    // Display music informations

    std::cout << filename << s
    ppppp
}
}
}