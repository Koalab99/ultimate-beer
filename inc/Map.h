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
	float m_spawnX;
	float m_spawnY;
	std::vector<Bloc> m_blocs;
	std::vector<Enemy> m_enemies;
	std::vector<Item> m_items;
	std::string m_title;
	std::string m_minipath;
	std::string m_path;
	float m_h;
	float m_w;
	
public:
	/**
	@brief Constructor
	@param string filename
	*/
	Map(const std::string &filename);
	/**
	@brief Destructor
	*/
	~Map();
	/**
	@brief Test collide with player and many blocs 
	@param vector<Bloc> 
	@param  float x: position x player , float y: position y player
	@return m_blocs
	*/
	Bloc *collide(std::vector<Bloc> *v, const float x, const float y);
	/**
	@brief Test collide with player and many enemys 
	@param vector<Enemy> 
	@param  float x: position x player , float y: position y player
	@return m_enemies
	*/
	Enemy *collide(std::vector<Enemy> *v, const float x, const float y);
	/**
	@brief Test collide with player and many items 
	@param vector<Item> 
	@param  float x: position x player , float y: position y player
	@return m_items
	*/
	const Item *collide(std::vector<Item> *v, const float x, const float y);
	/**
	@brief Test if bloc exist 
	@param bloc 
	@return true if bloc exist and false if bloc not exist
	*/
	bool blocExists(Bloc *c);
	/**
	@brief Recovers the blocs not far away 
	@param x:position w:weight
	@return vector<Bloc> m_blocs
	*/
	std::vector<Bloc> *getBlocsInRange(float x, float w);
	/**
	@brief Recovers the enemies not far away 
	@param x:position w:weight
	@return vector<Enemy> m_enemies
	*/
	std::vector<Enemy> *getEnemiesInRange(float x, float w);
	/**
	@brief Recovers the item not far away 
	@param x:position w:weight
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
	@param string path m_path
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
	@return m_spawnX
	*/
	float getSpawnX() const;
	/**
	@brief Get first position Y of player
	@return m_spawnY
	*/
	float getSpawnY() const;
	/**
	@brief Get mini path
	@return m_minipath
	*/
	std::string getMiniPath();
	/**
	@brief Get Path 
	@return m_path
	*/
	std::string getPath();
	/**
	@brief Get title 
	@return m_title
	*/
	std::string getTitle();
	/**
	@brief the player is he falling ?
	@param x:position X of player, y:position Y of player, w:width of map 
	@return true if player fall and false if player not fall
	*/
	bool fall(float x, float y, float w);
};

#endif
