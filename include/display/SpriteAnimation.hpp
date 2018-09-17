/*
 * =====================================================================================
 *
 *       Filename:  SpriteAnimation.hpp
 *
 *    Description:
 *
 *        Created:  15/09/2014 20:40:52
 *
 *         Author:  Quentin Bazin, <gnidmoo@gmail.com>
 *
 * =====================================================================================
 */
#ifndef SPRITEANIMATION_HPP_
#define SPRITEANIMATION_HPP_

#include <vector>

#include "Timer.hpp"
#include "Vector2.hpp"

class SpriteAnimation {
	public:
		SpriteAnimation(u16 delay, bool isRepeated = true)
			: m_delay(delay), m_isRepeated(isRepeated) {}
		// FIXME: To remove
		SpriteAnimation(std::vector<u16> frames, u16 delay, bool isRepeated = true)
			: m_frames(frames), m_positions(frames.size(), {0, 0}), m_delay(delay), m_isRepeated(isRepeated) {}
		SpriteAnimation(std::vector<u16> frames, std::vector<Vector2i> positions, u16 delay, bool isRepeated = true)
			: m_frames(frames), m_positions(positions), m_delay(delay), m_isRepeated(isRepeated) {}

		void reset(u16 frameID = 0);

		void start();
		void stop();

		void play();

		void addFrame(u16 frameID, Vector2i position = {0, 0}) { m_frames.emplace_back(frameID); m_positions.emplace_back(position); }
		u16 getFrame(u16 frameID) const;
		u16 currentFrame() const;
		u16 displayedFramesAmount() const;

		const Vector2i &currentPosition() const;

		bool isPlaying() const { return m_timer.isStarted() && !m_isPaused; }
		bool isFinished() const { return displayedFramesAmount() >= m_frames.size(); }

		u32 size() const { return m_frames.size(); }

		u16 delay() const { return m_delay; }

		void setRepeated(bool isRepeated) { m_isRepeated = isRepeated; }

	private:
		std::vector<u16> m_frames;
		std::vector<Vector2i> m_positions;

		Timer m_timer;

		u16 m_delay = 0;

		bool m_isPaused = false;
		bool m_isRepeated = true;
};

#endif // SPRITEANIMATION_HPP_
