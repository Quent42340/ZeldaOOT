/*
 * =====================================================================================
 *
 *       Filename:  Map.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  20/09/2014 19:04:36
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  
 *
 * =====================================================================================
 */
#include "Application.hpp"
#include "Config.hpp"
#include "CharacterManager.hpp"
#include "GrassObject.hpp"
#include "Map.hpp"
#include "MapLoader.hpp"
#include "ResourceHandler.hpp"
#include "TilesData.hpp"
#include "Weapon.hpp"
#include "XMLFile.hpp"

Map *Map::currentMap = nullptr;

Map::Map(const std::string &filename, Tileset &tileset, u16 area, u16 x, u16 y) {
	load(filename, tileset, area, x, y);
}

void Map::load(const std::string &filename, Tileset &tileset, u16 area, u16 x, u16 y) {
	AnimatedMap::load(filename, tileset);
	
	m_area = area;
	
	m_x = x;
	m_y = y;
	
	updateTiles();
}

void Map::resetTiles() {
	XMLTileMap::resetTiles();
	
	//for(auto &it : m_objects) {
	//	it->resetTiles(this);
	//}
	
	//for(auto &it : m_enemies) {
	//	it->reset();
	//}
	
	//m_collectables.clear();
}

void Map::updateTile(u16 tileX, u16 tileY, u16 id) {
	AnimatedMap::updateTile(tileX, tileY, id);
	
	u16 x = tileX * m_tileset->tileWidth();
	u16 y = tileY * m_tileset->tileHeight();
	
	if(m_tileset->info()[id] == TilesData::TileType::GrassTile) {
		addObject<GrassObject>(x, y);
	}
	else if(m_tileset->info()[id] == TilesData::TileType::LowGrassTile) {
		addObject<GrassObject>(x, y, true);
	}
}

void Map::update(bool onlyTiles) {
	animateTiles();
	
	if(!onlyTiles) {
		for(auto &it : m_objects) {
			it->update();
		}
		//for(auto &it : m_collectables) {
			// FIXME: I actually remove the collectables from here
			//if(it) it->update();
		//}
		
		/*
		for(auto &it : m_enemies) {
			if(CharacterManager::player.inCollisionWith(*it)
			&& !it->isDead()) {
				s16 vx = CharacterManager::player.x() - it->x();
				s16 vy = CharacterManager::player.y() - it->y();
				
				if(vx != 0) vx /= abs(vx);
				if(vy != 0) vy /= abs(vy);
				
				CharacterManager::player.setVelocity(vx, vy);
				CharacterManager::player.hurt(it->strength());
			}
			
			if(CharacterManager::player.inventory().weaponA()) {
				CharacterManager::player.inventory().weaponA()->testCollisionWith(*it);
			}
			
			if(CharacterManager::player.inventory().weaponB()) {
				CharacterManager::player.inventory().weaponB()->testCollisionWith(*it);
			}
			
			it->update();
		}*/
	}
}

void Map::draw() {
	TileMap::draw();
	
	for(auto &it : m_objects) {
		it->draw();
	}
	//for(auto &it : m_collectables) {
	//	it->draw();
	//}
	
	//for(auto &it : m_enemies) {
	//	it->draw();
	//}
}

void Map::removeObject(MapObject *object) {
	m_objects.erase(std::remove_if(m_objects.begin(), m_objects.end(),
		            [&](std::unique_ptr<MapObject> &it) {
		                return it.get() == object;
		            }), m_objects.end());
}

/*

void Map::addObject(Object *obj) {
	m_objects.emplace_back(obj);
}

void Map::addEnemy(Enemy *enemy) {
	m_enemies.emplace_back(enemy);
}

void Map::removeCollectable(Collectable *collectable) {
	m_collectables.erase(std::remove_if(m_collectables.begin(), m_collectables.end(),
		                 [&](std::unique_ptr<Collectable> &it) {
		                     return it.get() == collectable;
		                 }), m_collectables.end());
}

bool Map::objectAtPosition(Object *obj, float x, float y) {
	return((floor(obj->x() / 8) == floor(x / 8)
		 || floor(obj->x() / 8) == floor(x / 8) - 1)
		&& (floor(obj->y() / 8) == floor(y / 8)
		 || floor(obj->y() / 8) == floor(y / 8) - 1));
}

void Map::sendEvent(EventType event, MapObject *object, Vector2i offsets) {
	if(!object) object = &CharacterManager::player;
	
	for(auto &it : m_objects) {
		if(objectAtPosition(it.get(), object->x() + offsets.x, object->y() + offsets.y)) {
			it->onEvent(event);
			
			break;
		}
	}
}*/

Map &Map::getMap(u16 area, u16 mapX, u16 mapY) {
	return ResourceHandler::getInstance().get<Map>(MapLoader::makeName(area, mapX, mapY));
}

