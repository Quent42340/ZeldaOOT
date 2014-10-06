/*
 * =====================================================================================
 *
 *       Filename:  DoorManager.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/10/2014 23:51:37
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  
 *
 * =====================================================================================
 */
#include "Character.hpp"
#include "Door.hpp"
#include "DoorManager.hpp"
#include "MapManager.hpp"
#include "XMLFile.hpp"

void DoorManager::init() {
	XMLFile doc("data/config/doors.xml");
	
	XMLElement *doorElement = doc.FirstChildElement("doors").FirstChildElement("door").ToElement();
	while(doorElement) {
		Door *door = new Door(doorElement->FloatAttribute("tileX") * 16,
							  doorElement->FloatAttribute("tileY") * 16);
		
		u8 direction = 0;
		if(doorElement->FirstChildElement("player")->Attribute("direction", "up")) {
			direction = Character::Direction::Up;
		}
		else if(doorElement->FirstChildElement("player")->Attribute("direction", "down")) {
			direction = Character::Direction::Down;
		}
		else if(doorElement->FirstChildElement("player")->Attribute("direction", "left")) {
			direction = Character::Direction::Left;
		}
		else if(doorElement->FirstChildElement("player")->Attribute("direction", "right")) {
			direction = Character::Direction::Right;
		}
		
		door->setDestination(
			doorElement->FirstChildElement("destination")->IntAttribute("area"),
			doorElement->FirstChildElement("destination")->IntAttribute("mapX"),
			doorElement->FirstChildElement("destination")->IntAttribute("mapY"),
			doorElement->FirstChildElement("player")->FloatAttribute("tileX") * 16,
			doorElement->FirstChildElement("player")->FloatAttribute("tileY") * 16,
			direction
		);
		
		MapManager::getMap(doorElement->IntAttribute("area"),
						   doorElement->IntAttribute("mapX"),
						   doorElement->IntAttribute("mapY"))->addObject(door);
		
		doorElement = doorElement->NextSiblingElement();
	}
}

