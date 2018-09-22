/*
 * =====================================================================================
 *
 *       Filename:  PlayerPushState.hpp
 *
 *    Description:
 *
 *        Created:  22/09/2018 18:47:49
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef PLAYERPUSHSTATE_HPP_
#define PLAYERPUSHSTATE_HPP_

#include "PlayerState.hpp"

class PlayerPushState : public PlayerState {
	public:
		void onBegin(SceneObject &object) override;
		void onEnd(SceneObject &object) override;

		void update(SceneObject &object) override;
};

#endif // PLAYERPUSHSTATE_HPP_
