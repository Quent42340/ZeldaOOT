/*
 * =====================================================================================
 *
 *       Filename:  Color.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  27/09/2014 22:35:38
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  
 *
 * =====================================================================================
 */
#ifndef COLOR_HPP_
#define COLOR_HPP_

#include "Types.hpp"

class Color {
	public:
		Color(u8 _r, u8 _g, u8 _b);
		~Color();
		
		float r;
		float g;
		float b;
		float a;
		
		static Color black;
		static Color white;
		static Color text;
		static Color blue;
		static Color red;
};

#endif // COLOR_HPP_
