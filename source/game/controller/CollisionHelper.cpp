/*
 * =====================================================================================
 *
 *       Filename:  CollisionHelper.cpp
 *
 *    Description:
 *
 *        Created:  02/05/2015 00:09:30
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include <gk/scene/component/HitboxComponent.hpp>
#include <gk/scene/component/MovementComponent.hpp>

#include "CollisionHelper.hpp"
#include "Sprite.hpp"

#include "PositionComponent.hpp"
#include "SpriteComponent.hpp"

bool CollisionHelper::inCollision(gk::SceneObject &object1, gk::SceneObject &object2) {
	if(object1.has<PositionComponent>() && object1.has<gk::HitboxComponent>()
	&& object2.has<PositionComponent>() && object2.has<gk::HitboxComponent>()) {
		auto &hitbox1 = object1.get<gk::HitboxComponent>();
		auto &hitbox2 = object2.get<gk::HitboxComponent>();

		if(hitbox1.currentHitbox() && hitbox2.currentHitbox()) {
			auto &position1 = object1.get<PositionComponent>();
			auto &position2 = object2.get<PositionComponent>();

			sf::FloatRect rect1 = *hitbox1.currentHitbox();
			sf::FloatRect rect2 = *hitbox2.currentHitbox();

			rect1.left += position1.left;
			rect1.top += position1.top;

			rect2.left += position2.left;
			rect2.top += position2.top;

			if(object1.has<gk::MovementComponent>()) {
				auto &movement = object1.get<gk::MovementComponent>();
				rect1.left += movement.v.x;
				rect1.top += movement.v.y;
			}

			if(object2.has<gk::MovementComponent>()) {
				auto &movement = object2.get<gk::MovementComponent>();
				rect2.left += movement.v.x;
				rect2.top += movement.v.y;
			}

			if(object1.has<SpriteComponent>()) {
				auto &pos = object1.get<SpriteComponent>().sprite().currentAnimation().currentPosition();
				rect1.left += pos.x;
				rect1.top += pos.y;
			}

			if(object2.has<SpriteComponent>()) {
				auto &pos = object2.get<SpriteComponent>().sprite().currentAnimation().currentPosition();
				rect2.left += pos.x;
				rect2.top += pos.y;
			}

			if(rect1.intersects(rect2)) {
				return true;
			}
		}
	}

	return false;
}

