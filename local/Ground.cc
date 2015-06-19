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
#include "Ground.h"

#include "Ball.h"
#include "Events.h"
#include "Singletons.h"

Ground::Ground() {
  gEventManager().registerHandler<BallLocationEvent>(&Ground::onBallLocation, this);
}

void Ground::render(sf::RenderWindow& window) {
  sf::RectangleShape shape({ WIDTH, HEIGHT });
  shape.setOrigin(WIDTH / 2, HEIGHT / 2);
  shape.setPosition(0.0f, 0.0f);
  shape.setFillColor(sf::Color::Black);
  window.draw(shape);
}

game::EventStatus Ground::onBallLocation(game::EventType type, game::Event *event) {
  auto loc = static_cast<BallLocationEvent*>(event);

  static constexpr float Y_LIMIT = HEIGHT / 2 - Ball::RADIUS;

  if (loc->position.y > Y_LIMIT) {
    loc->velocity.y = -loc->velocity.y;
    loc->position.y = Y_LIMIT;
  }

  if (loc->position.y < -Y_LIMIT) {
    loc->velocity.y = -loc->velocity.y;
    loc->position.y = -Y_LIMIT;
  }

  static constexpr float X_LIMIT = WIDTH / 2 - Ball::RADIUS;

  if (loc->position.x > X_LIMIT) {
    PointEvent point;
    point.location = Paddle::Location::RIGHT;
    gEventManager().triggerEvent(&point);

    loc->velocity.x = -loc->velocity.x;
    loc->position = sf::Vector2f(0, 0);
  }

  if (loc->position.x < -X_LIMIT) {
    PointEvent point;
    point.location = Paddle::Location::LEFT;
    gEventManager().triggerEvent(&point);

    loc->velocity.x = -loc->velocity.x;
    loc->position = sf::Vector2f(0, 0);
  }

  return game::EventStatus::KEEP;
}
