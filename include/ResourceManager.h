#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>

class ResourceManager
{
public:
	enum Type {
		Player, Floor, Enemy, Coin, Ladder,Ground, Pole, Empty, MenuPhoto,
		Max
	};
	enum SoundType {
		S_Enemy,
		S_Coin,
		S_LevelUp,
		S_Lose,
		S_Hover,
		S_Dig,
		S_Max 
	};
	enum MusicType {
		M_Menu,
		M_Game,
		M_Max
	};
	
	static ResourceManager& getInstance();

	ResourceManager(const ResourceManager&) = delete;
	void operator=(const ResourceManager&) = delete;
	const sf::Texture& getTexture(Type type) const;
	const sf::Font& getFont() const;
	const sf::SoundBuffer& getSound(SoundType type) const;
	void playMusic(MusicType type);
private:
	ResourceManager();
	void loadTextures();
	void loadSounds();
	std::vector <sf::Texture> m_textures;
	sf::Font m_font;
	std::vector<sf::SoundBuffer> m_sounds;
	sf::Music m_music;
	std::vector<std::string> m_musicPaths;
	MusicType m_currentMusic;
	void loadMusicPaths();
	void loadOneTexture(sf::Texture& tex, const std::string& filename);
	void loadOneSound(sf::SoundBuffer& buffer, const std::string& filename);
};