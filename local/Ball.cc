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
#include "Ball.h"

#include "Events.h"
#include "Singletons.h"

void Ball::update(float dt) {
  m_position += m_velocity * dt;

  BallLocationEvent loc;
  loc.position = m_position;
  loc.velocity = m_velocity;

  gEventManager().triggerEvent(&loc);

  m_position = loc.position;
  m_velocity = loc.velocity;


}

void Ball::render(sf::RenderWindow& window) {
  sf::CircleShape shape(RADIUS);
  shape.setOrigin(RADIUS, RADIUS);
  shape.setPosition(m_position);
  shape.setFillColor(sf::Color::White);
  window.draw(shape);
}
