/*
 * =====================================================================================
 *
 *       Filename:  MapLoader.hpp
 *
 *    Description:  
 *
 *        Created:  12/02/2015 23:00:09
 *
 *         Author:  Quentin Bazin, <gnidmoo@gmail.com>
 *
 * =====================================================================================
 */
#ifndef MAPLOADER_HPP_
#define MAPLOADER_HPP_

#include "Scene.hpp"
#include "ResourceLoader.hpp"
#include "Tileset.hpp"

class MapLoader : public ResourceLoader {
	public:
		void load(const std::string &xmlFilename, ResourceHandler &handler);
		void loadMap(const std::string &name, u16 area, u16 x, u16 y, Tileset &tileset, ResourceHandler &handler);
		
		static std::string makeName(u16 area, u16 x, u16 y) {
			return std::to_string(area) + "-" + std::to_string(x) + "-" + std::to_string(y);
		}
};

#endif // MAPLOADER_HPP_
