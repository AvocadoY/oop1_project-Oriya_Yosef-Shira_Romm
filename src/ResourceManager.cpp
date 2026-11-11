#include "ResourceManager.h"
#include <string>
#include <iostream>

ResourceManager::ResourceManager()
{
    m_textures.resize(Max);
    m_sounds.resize(S_Max);
    loadTextures();
    loadSounds();
    m_musicPaths.resize(M_Max);
    loadMusicPaths();

    m_font.openFromFile("rainyhearts.ttf");
}

ResourceManager& ResourceManager::getInstance()
{
    static ResourceManager instance;
    return instance;
}

void ResourceManager::loadTextures()
{
    loadOneTexture(m_textures[Player], "Player.png");
    loadOneTexture(m_textures[Floor], "Floor.png");
    loadOneTexture(m_textures[Enemy], "Enemy.png");
    loadOneTexture(m_textures[Coin], "Coin.png");
    loadOneTexture(m_textures[Ladder], "Ladder.png");
    loadOneTexture(m_textures[Ground], "Ground.png");
    loadOneTexture(m_textures[Pole], "Pole.png");
    loadOneTexture(m_textures[Empty], "Empty.png");
    loadOneTexture(m_textures[MenuPhoto], "vecteezy_flag-party-celebration-festival-pixel-design-colorful_36090309.png");
}

const sf::Texture& ResourceManager::getTexture(Type type) const
{
    return m_textures[type];
}

void ResourceManager::loadOneTexture(sf::Texture& tex, const std::string& filename)
{
    if (!tex.loadFromFile(filename))
    {
        std::cerr << "Error loading: " << filename << std::endl;
    }
}

void ResourceManager::loadOneSound(sf::SoundBuffer& buffer, const std::string& filename)
{
    if (!buffer.loadFromFile(filename))
    {
        std::cerr << "Error loading sound: " << filename << std::endl;
    }
}

const sf::SoundBuffer& ResourceManager::getSound(SoundType type) const
{
    return m_sounds[type];
}

const sf::Font& ResourceManager::getFont() const
{
    return m_font;
}

void ResourceManager::loadSounds()
{
    loadOneSound(m_sounds[S_Enemy], "y69yaoqs4z-balloon-pop-sfx-6.mp3");
    loadOneSound(m_sounds[S_Coin], "sparkle-355937.mp3");
    loadOneSound(m_sounds[S_LevelUp], "crowd_small_chil_ec049202_9klCwI6.mp3");
    loadOneSound(m_sounds[S_Hover], "bubble-pop-06-351337.mp3");
    loadOneSound(m_sounds[S_Lose], "shocked-sound-effect.mp3");
    loadOneSound(m_sounds[S_Dig], "shovel-thwack-1-94135.mp3");
}

void ResourceManager::playMusic(MusicType type) //for the background music
{
    if (m_currentMusic == type) //need to change the music?
        return;
    if (!m_music.openFromFile(m_musicPaths[type]))
    {
        std::cerr << "Error opening music file: " << m_musicPaths[type] << std::endl;
        return;
    }
    m_currentMusic = type;
    m_music.setLooping(true);  
    m_music.setVolume(20);   

    m_music.play();
}

void ResourceManager::loadMusicPaths()
{
    m_musicPaths[M_Menu] = "10 Shop.mp3";
    m_musicPaths[M_Game] = "Sakura-Girl-Yay-chosic.com_.mp3";
}