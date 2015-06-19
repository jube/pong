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
#include "Paddle.h"

#include <cstdio>

#include "Ball.h"
#include "Events.h"
#include "Ground.h"
#include "Singletons.h"

Paddle::Paddle(Location loc)
: m_location(loc)
, m_position({ loc == Location::LEFT ? - POSITION : POSITION, 0.0f })
, m_move(Move::STOP)
{
  gEventManager().registerHandler<BallLocationEvent>(&Paddle::onBallLocation, this);
}

void Paddle::update(float dt) {
  switch (m_move) {
    case Move::UP:
      if (m_position.y > - (Ground::HEIGHT - HEIGHT) / 2) {
        m_position.y -= VELOCITY * dt;
      }

      break;

    case Move::DOWN:
      if (m_position.y < (Ground::HEIGHT - HEIGHT) / 2) {
        m_position.y += VELOCITY * dt;
      }

      break;

    case Move::STOP:
      break;
  }
}

static constexpr float PI = 3.14159265358979323846f;

game::EventStatus Paddle::onBallLocation(game::EventType type, game::Event *event) {
  auto loc = static_cast<BallLocationEvent*>(event);

  sf::Vector2f n = loc->position - m_position;

  if (n.x * loc->velocity.x < 0) {
    if (std::abs(n.x) < Ball::RADIUS + WIDTH / 2 && std::abs(n.y) < HEIGHT / 2) {
      float angle = 0.7 * n.y / HEIGHT * PI;

      if (loc->velocity.x > 0) {
        loc->velocity.x = std::cos(PI - angle) * Ball::VELOCITY;
        loc->velocity.y = std::sin(PI - angle) * Ball::VELOCITY;
      } else {
        loc->velocity.x = std::cos(angle) * Ball::VELOCITY;
        loc->velocity.y = std::sin(angle) * Ball::VELOCITY;
      }
    }
  }

  return game::EventStatus::KEEP;
}


void Paddle::render(sf::RenderWindow& window) {
  sf::RectangleShape shape({ WIDTH, HEIGHT });
  shape.setOrigin(WIDTH / 2, HEIGHT / 2);
  shape.setPosition(m_position);
  shape.setFillColor(sf::Color::White);
  window.draw(shape);
}
