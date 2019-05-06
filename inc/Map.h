#ifndef MAP_H
#define MAP_H

#include <Bloc.h>
#include <Position.h>
#include <Enemy.h>
#include <Item.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>


/*Sets up the map, which(among other things) includes a lot of getters, updating the enemies status, checking if things are colliding, etc...*/

using namespace std;
class Enemy;
class Map {
private:
	/**
	@brief Position X of player of begining
	*/
	float m_spawnX;
	/**
	@brief Position Y of player of begining
	*/
	float m_spawnY;
	/**
	@brief Group of blocs
	*/
	std::vector<Bloc> m_blocs;
	/**
	@brief Group of enemys
	*/
	std::vector<Enemy> m_enemies;
	/**
	@brief Group of items
	*/
	std::vector<Item> m_items;
	/**
	@brief Title of map
	*/
	std::string m_title;
	/**
	@brief Path for miniature
	*/
	std::string m_minipath;
	/**
	@brief Path for image
	*/
	std::string m_path;
	/**
	@brief height map
	*/
	float m_h;
	/**
	@brief width map
	*/
	float m_w;
	
public:
	/**
	@brief Constructor
	@param filename string
	*/
	Map(const std::string &filename);
	/**
	@brief Destructor
	*/
	~Map();
	/**
	@brief Test collide with player and many blocs 
	@param v pointer vector<Bloc> 
	@param x float position x player
	@param y float position y player
	@return Bloc m_blocs
	*/
	Bloc *collide(std::vector<Bloc> *v, const float x, const float y);
	/**
	@brief Test collide with player and many enemys 
	@param v pointer vector<Enemy> 
	@param x float position x player 
	@param y float position y player
	@return m_enemies
	*/
	Enemy *collide(std::vector<Enemy> *v, const float x, const float y);
	/**
	@brief Test collide with player and many items 
	@param v pointer vector<Item> 
	@param x float position x player 
	@param y float position y player
	@return Item pointer m_items
	*/
	const Item *collide(std::vector<Item> *v, const float x, const float y);
	/**
	@brief Test if bloc exist 
	@param c pointer bloc 
	@return true if bloc exist and false if bloc not exist
	*/
	bool blocExists(Bloc *c);
	/**
	@brief Recovers the blocs not far away 
	@param x float position 
	@param w float weight
	@return vector<Bloc> m_blocs
	*/
	std::vector<Bloc> *getBlocsInRange(float x, float w);
	/**
	@brief Recovers the enemies not far away 
	@param x float position
	@param w float weight
	@return vector<Enemy> m_enemies
	*/
	std::vector<Enemy> *getEnemiesInRange(float x, float w);
	/**
	@brief Recovers the item not far away 
	@param x float position
	@param w float weight
	@return vector<Item> m_items
	*/
	std::vector<Item> *getItemsInRange(float x, float w);
	/**
	@brief get number of blocs 
	@return int nb_blocs
	*/
	int getNbBloc();
	/**
	@brief Get blocs 
	@return vector<Bloc> m_blocs
	*/
	std::vector<Bloc> *getBlocs();
	/**
	@brief Get enemys 
	@return vector<Enemy> m_enemies
	*/
	std::vector<Enemy> *getEnemies();
	/**
	@brief Get items 
	@return vector<Item> m_items
	*/
	std::vector<Item> *getItems();
	/**
	@brief Open the Map and definition of this objects 
	@param path string m_path
	*/
	void open(const string &path);
	/**
	@brief Download position of enemy
	*/
	void updateEnemies();
	/**
	@brief Get height of map
	@return float m_height
	*/
	float getH();
	/**
	@brief Get width of map
	@return float m_width
	*/
	float getW();
	/**
	@brief Get first position X of player
	@return float m_spawnX
	*/
	float getSpawnX() const;
	/**
	@brief Get first position Y of player
	@return float m_spawnY
	*/
	float getSpawnY() const;
	/**
	@brief Get mini path
	@return m_minipath
	*/
	std::string getMiniPath();
	/**
	@brief Get Path 
	@return string m_path
	*/
	std::string getPath();
	/**
	@brief Get title 
	@return string m_title
	*/
	std::string getTitle();
	/**
	@brief the player is he falling ?
	@param x position X of player
	@param y position Y of player
	@param w width of map 
	@return bool true if player fall and false if player not fall
	*/
	bool fall(float x, float y, float w);
};

#endif
