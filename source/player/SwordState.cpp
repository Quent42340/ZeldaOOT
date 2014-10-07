/*
 * =====================================================================================
 *
 *       Filename:  SwordState.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  15/09/2014 22:25:36
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  Deloptia
 *
 * =====================================================================================
 */
#include "AnimationManager.hpp"
#include "Keyboard.hpp"
#include "MapHelper.hpp"
#include "MapManager.hpp"
#include "Sound.hpp"
#include "SwordState.hpp"
#include "TilesData.hpp"
#include "WeaponManager.hpp"

SwordState::SwordState() {
	m_stateType = StateType::TypeSword;
	m_nextStateType = StateType::TypeSword;
	
	Sound::Effect::swordSlash1.play();
	
	m_playerMoved = false;
	
	m_sword = (Sword*)WeaponManager::getWeaponByID(WeaponManager::SwordID);
}

SwordState::~SwordState() {
	m_sword->reset();
}

void SwordState::move(double dx, double dy) {
	m_player.move(dx, dy);
	m_sword->move(dx, dy);
}

void SwordState::movePlayer(u8 direction, bool forward) {
	if(direction == Character::Direction::Left) {
		if(forward) m_player.move(-4, 0);
		else		m_player.move(4, 0);
	}
	else if(direction == Character::Direction::Right) {
		if(forward) m_player.move(4, 0);
		else		m_player.move(-4, 0);
	}
	else if(direction == Character::Direction::Up) {
		if(forward) m_player.move(0, -3);
		else		m_player.move(0, 3);
	}
	else if(direction == Character::Direction::Down) {
		if(forward) m_player.move(0, 3);
		else		m_player.move(0, -3);
	}
	
	m_playerMoved = true;
}

void SwordState::update() {
	if(m_sword->state() == Sword::State::Loading) {
		m_directionLocked = true;
		
		MovingState::move();
	}
	
	m_sword->update();
	
	if(m_sword->state() != Sword::State::SpinAttack) {
		if(!m_playerMoved) {
			if(m_sword->animationCurrentFrame(m_player.direction()) == 1) {
				movePlayer(m_player.direction());
			}
			else if(m_sword->animationCurrentFrame(m_player.direction()) == 6) {
				movePlayer(m_player.direction(), false);
			}
		}
		else if((m_sword->animationCurrentFrame(m_player.direction()) != 1)
			 && (m_sword->animationCurrentFrame(m_player.direction()) != 6)) {
			m_playerMoved = false;
		}
	} else {
		if(!m_playerMoved && !(m_sword->animationCurrentFrame(8) & 1)) {
			u8 prevMovementDirection = 0;
			u8 movementDirection = 0;
			
			if(m_sword->animationCurrentFrame(8) % 8 == 0) {
				prevMovementDirection = Player::Direction::Right;
				movementDirection = Player::Direction::Down;
			}
			else if(m_sword->animationCurrentFrame(8) % 8 == 2) {
				prevMovementDirection = Player::Direction::Down;
				movementDirection = Player::Direction::Left;
			}
			else if(m_sword->animationCurrentFrame(8) % 8 == 4) {
				prevMovementDirection = Player::Direction::Left;
				movementDirection = Player::Direction::Up;
			}
			else if(m_sword->animationCurrentFrame(8) % 8 == 6) {
				prevMovementDirection = Player::Direction::Up;
				movementDirection = Player::Direction::Right;
			}
			
			if(m_sword->spinFrameCounter() != 0) {
				movePlayer(prevMovementDirection, false);
			}
			
			movePlayer(movementDirection);
		}
		else if(m_sword->animationCurrentFrame(8) & 1) {
			m_playerMoved = false;
		}
	}
	
	if((m_sword->state() == Sword::State::Swinging && m_sword->animationCurrentFrame(m_player.direction()) > 2)
	||  m_sword->state() == Sword::State::SpinAttack) {
		if((MapHelper::isTile(m_sword->x() + 8, m_sword->y() + 8, TilesData::TileType::GrassTile))
		|| (MapHelper::isTile(m_sword->x() + 8, m_sword->y() + 8, TilesData::TileType::LowGrassTile))) {
			MapManager::currentMap->sendEvent(Map::EventType::GrassCutted, m_sword, Vector2i(8, 8));
		}
	}
}

void SwordState::draw() {
	m_sword->draw();
	
	drawPlayer();
}

void SwordState::drawPlayer() {
	if(m_sword->state() == Sword::State::Swinging) {
		m_player.playAnimation(m_player.x(), m_player.y(), m_player.direction() + 8);
	}
	else if(m_sword->state() == Sword::State::Loading
		&& (Keyboard::isKeyPressed(Keyboard::Left)
		 || Keyboard::isKeyPressed(Keyboard::Right)
		 || Keyboard::isKeyPressed(Keyboard::Up)
		 || Keyboard::isKeyPressed(Keyboard::Down))) {
		m_player.playAnimation(m_player.x(), m_player.y(), m_player.direction());
	}
	else if(m_sword->state() == Sword::State::SpinAttack) {
		m_player.playAnimation(m_player.x(), m_player.y(), 12);
	} else {
		m_player.drawFrame(m_player.x(), m_player.y(), m_player.direction());
	}
}

