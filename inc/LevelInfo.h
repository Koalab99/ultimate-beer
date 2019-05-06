#ifndef LEVEL_INFO_H
#define LEVEL_INFO_H

#include <string>
#include <SDL2/SDL.h>

/**
*detailed description Defines what has to be known for each level: it's name, what it looks like, it's number of ennemies and items... */ 
class LevelInfo {
private:
	/**
	@brief Name 
	*/
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
	/**
	@brief Constructor
	@param renderer pointer SDL_Renderer
	@param path string
	*/
	LevelInfo(SDL_Renderer *renderer, std::string path);
	/**
	@brief Destructor
	*/
	~LevelInfo();
	/**
	@brief Get Name of level
	@return string m_name
	*/
	std::string getName() const;
	/**
	@brief Get texture Path
	@return string
	*/
	std::string getTexturePath() const;
	/**
	@brief Get Texture of level
	@return SDL_Texture pointer
	*/
	SDL_Texture *getTexture() const;
	/**
	@brief Get Title of level
	@return SDL_Texture pointer m_title
	*/
	SDL_Texture *getTitle() const;
	/**
	@brief Get number of blocs in level
	@return int m_nbBlocs
	*/
	int getNbBlocs() const;
	/**
	@brief Get number of enemys  in level
	@return int m_nbEnemies
	*/
	int getNbEnemies() const;
	/**
	@brief Get number of items in level
	@return int m_nbItems
	*/
	int getNbItems() const;
	/**
	@brief Get position X
	@return int m_x
	*/
	int getX() const;
	/**
	@brief Get position X
	@return int m_y
	*/
	int getY() const;
	/**
	@brief Get path
	@return string m_texturePath
	*/
	std::string getPath() const;
};

#endif
