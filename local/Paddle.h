/*
 * Copyright (c) 2015, Julien Bernard
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
#ifndef LOCAL_PADDLE_H
#define LOCAL_PADDLE_H

#include <game/Entity.h>
#include <game/Event.h>

class Paddle : public game::Entity {
public:
  static constexpr float WIDTH = 2.0f;
  static constexpr float HEIGHT = 20.0f;

  static constexpr float POSITION = 75.0f;
  static constexpr float VELOCITY = 50.0f;

  enum class Move {
    UP,
    STOP,
    DOWN,
  };

  enum class Location {
    LEFT,
    RIGHT,
  };

  Paddle(Location loc);

  void move(Move m) {
    m_move = m;
  }

  bool isOnLeft() const {
    return m_location == Location::LEFT;
  }

  bool isOnRight() const {
    return m_location == Location::RIGHT;
  }

  const sf::Vector2f& getPosition() const {
    return m_position;
  }

  virtual void update(float dt) override;
  virtual void render(sf::RenderWindow& window) override;

private:
  game::EventStatus onBallLocation(game::EventType type, game::Event *event);

private:
  Location m_location;
  sf::Vector2f m_position;
  Move m_move;
};


#endif // LOCAL_PADDLE_H
