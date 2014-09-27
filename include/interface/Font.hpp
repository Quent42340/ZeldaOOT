/*
 * =====================================================================================
 *
 *       Filename:  Font.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  26/09/2014 20:41:39
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  
 *
 * =====================================================================================
 */
#ifndef FONT_HPP_
#define FONT_HPP_

#include "Sprite.hpp"

class Font : public Sprite {
	public:
		Font();
		~Font();
		
		void drawChar(float x, float y, char c);
		void drawString(float x, float y, std::string str);
};

#endif // FONT_HPP_