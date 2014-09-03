/*
 * =====================================================================================
 *
 *       Filename:  Timer.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  22/07/2014 14:26:40
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  Deloptia
 *
 * =====================================================================================
 */
#include "Timer.hpp"

Timer::Timer() {
	reset();
}

Timer::~Timer() {
}

void Timer::stop() {
	if(m_isStarted) {
		m_isStarted = false;
		m_tick = TimeManager::getTicks() - m_t;
	}
}

void Timer::start() {
	if(!m_isStarted) {
		m_isStarted = true;
		m_t = TimeManager::getTicks() - m_tick;
	}
}

void Timer::reset() {
	m_t = TimeManager::getTicks();
	m_tick = 0;
	m_isStarted = false;
}

void Timer::setTime(u32 time) {
	if(m_isStarted) {
		m_t = TimeManager::getTicks() - time;
	} else {
		m_tick = time;
	}
}

