/*
 * =====================================================================================
 *
 *       Filename:  MovingState.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  15/09/2014 22:25:07
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  Deloptia
 *
 * =====================================================================================
 */
#include "Keyboard.hpp"
#include "MovingState.hpp"
#include "StandingState.hpp"
#include "Weapon.hpp"

void MovingState::update() {
	if(!Keyboard::isKeyPressed(Keyboard::Left)
	&& !Keyboard::isKeyPressed(Keyboard::Right)
	&& !Keyboard::isKeyPressed(Keyboard::Up)
	&& !Keyboard::isKeyPressed(Keyboard::Down)) {
		setNextState([]{ return new StandingState; });
	}
	
	if(Keyboard::isKeyPressedOnce(Keyboard::A)
	&& m_character.inventory().weaponA() != nullptr) {
		setNextState(m_character.inventory().weaponA()->playerStateTransition());
	}
	
	if(Keyboard::isKeyPressedOnce(Keyboard::B)
	&& m_character.inventory().weaponB() != nullptr) {
		setNextState(m_character.inventory().weaponB()->playerStateTransition());
	}
	
	m_character.updateMovement();
}

void MovingState::render() {
	m_character.playAnimation(m_character.x(), m_character.y(), m_character.direction());
}

