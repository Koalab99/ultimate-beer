#ifndef LEVEL_INFO_H
#define LEVEL_INFO_H

#include <string>
#include <SDL2/SDL.h>

/*Defines what has to be known for each level: it's name, what it looks like, it's number of ennemies and items... */ 
class LevelInfo {
private:
	std::string m_name;
	std::string m_texturePath;
	std::string m_path;
	int m_nbBlocs;
	int m_nbEnemies;
	int m_nbItems;
	float m_x;
	float m_y;
	SDL_Texture *m_texture;
	SDL_Texture *m_title;
public:
	LevelInfo(SDL_Renderer *renderer, std::string path);
	~LevelInfo();

	std::string getName() const;
	std::string getTexturePath() const;
	SDL_Texture *getTexture() const;
	SDL_Texture *getTitle() const;
	int getNbBlocs() const;
	int getNbEnemies() const;
	int getNbItems() const;
	int getX() const;
	int getY() const;
	std::string getPath() const;
};

#endif
