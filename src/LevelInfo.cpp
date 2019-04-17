#include <LevelInfo.h>
#include <string>
#include <iostream>
#include <fstream>
#include <assert.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <Font.h>

extern TTF_Font *gFont;

LevelInfo::LevelInfo(SDL_Renderer *renderer, std::string path) {
	m_path = path;
	m_nbBlocs = 0;
	m_nbEnemies = 0;
	m_nbItems = 0;
	std::ifstream levelFile;
	levelFile.open(path);
	if(!levelFile) {
		std::cerr << "Unable to read file at " << path << std::endl;
		return;
		assert(!levelFile);		
	}
	getline(levelFile, m_name);
	getline(levelFile, m_texturePath);
	levelFile >> m_x;
	levelFile >> m_y;
	levelFile >> m_nbBlocs;
	std::string garbage;
	for(int i = 0; i <= m_nbBlocs; i++) {
		getline(levelFile, garbage);
	}
	levelFile >> m_nbEnemies;
	for(int i = 0; i <= m_nbEnemies; i++) {
		getline(levelFile, garbage);
	}
	levelFile >> m_nbItems;
	levelFile.close();
	m_texture = IMG_LoadTexture(renderer, m_texturePath.c_str());
	
	SDL_Surface *surf = TTF_RenderText_Blended(gFont, m_name.c_str(), BLACK);
	m_title = SDL_CreateTextureFromSurface(renderer, surf);
	SDL_FreeSurface(surf);
	SDL_SetTextureBlendMode(m_title, SDL_BLENDMODE_BLEND);
}

LevelInfo::~LevelInfo() {
	SDL_DestroyTexture(m_title);
	SDL_DestroyTexture(m_texture);
}

std::string LevelInfo::getName() const {
	return m_name;
}

std::string LevelInfo::getTexturePath() const {
	return m_texturePath;
}

SDL_Texture *LevelInfo::getTexture() const {
	return m_texture;
}

SDL_Texture *LevelInfo::getTitle() const {
	return m_title;
}

int LevelInfo::getNbBlocs() const {
	return m_nbBlocs;
}

int LevelInfo::getNbEnemies() const {
	return m_nbEnemies;
}

int LevelInfo::getNbItems() const {
	return m_nbItems;
}

int LevelInfo::getX() const {
	return m_x;
}

int LevelInfo::getY() const {
	return m_y;
}

std::string LevelInfo::getPath() const {
	return m_path;
}
