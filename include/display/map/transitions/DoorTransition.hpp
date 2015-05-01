/*
 * =====================================================================================
 *
 *       Filename:  DoorTransition.hpp
 *
 *    Description:  
 *
 *        Created:  05/10/2014 21:52:46
 *
 *         Author:  Quentin Bazin, <gnidmoo@gmail.com>
 *
 * =====================================================================================
 */
#ifndef DOORTRANSITION_HPP_
#define DOORTRANSITION_HPP_

#include "Map.hpp"
#include "RectangleShape.hpp"
#include "StatsBar.hpp"
#include "Transition.hpp"

class DoorTransition : public Transition {
	public:
		DoorTransition(u16 area, u16 mapX, u16 mapY, u16 playerX, u16 playerY, u8 playerDirection, bool movePlayer = false);
		
		void update();
		
		void draw();
		
	private:
		Map *m_nextMap;
		
		u16 m_playerX;
		u16 m_playerY;
		
		u16 m_playerDirection;
		
		bool m_movePlayer;
		
		Timer m_timer;
		
		RectangleShape m_rect1;
		RectangleShape m_rect2;
		
		StatsBar m_statsBar;
};

#endif // DOORTRANSITION_HPP_