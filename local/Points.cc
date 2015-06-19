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
#include "Points.h"

#include <cassert>

#include "Events.h"
#include "Singletons.h"

Points::Points()
: game::Entity(1)
, m_leftPlayerPoints(0)
, m_rightPlayerPoints(0)
{
  gEventManager().registerHandler<PointEvent>(&Points::onPoint, this);
}


static const char digits[10][5][4] = {
  {
    " ##",
    "# #",
    "# #",
    "# #",
    "## ",
  },
  {
    " # ",
    " # ",
    " # ",
    " # ",
    " # ",
  },
  {
    "## ",
    "  #",
    " # ",
    "#  ",
    "###",
  },
  {
    "###",
    "  #",
    " ##",
    "  #",
    "###",
  },
  {
    "#  ",
    "#  ",
    "# #",
    "###",
    "  #",
  },
  {
    "###",
    "#  ",
    "###",
    "  #",
    "## ",
  },
  {
    "#  ",
    "#  ",
    "###",
    "# #",
    "###",
  },
  {
    "###",
    "  #",
    "  #",
    "  #",
    "  #",
  },
  {
    "###",
    "# #",
    "###",
    "# #",
    "###",
  },
  {
    "###",
    "# #",
    "###",
    "  #",
    "  #",
  },
};

static void displayDigit(unsigned d, const sf::Vector2f& position, sf::RenderWindow& window) {
  assert(0 <= d && d <= 9);

  static constexpr float WIDTH = 1.3f;
  static constexpr float HEIGHT = 2.0f;

  sf::RectangleShape shape({ WIDTH, HEIGHT });
  shape.setOrigin(WIDTH / 2, HEIGHT / 2);
  shape.setFillColor(sf::Color::White);

  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 3; ++j) {
      if (digits[d][i][j] == '#') {
        shape.setPosition(position.x + (j - 1) * WIDTH, position.y + (i - 2) * HEIGHT);
        window.draw(shape);
      }
    }
  }
}

void Points::render(sf::RenderWindow& window) {
  static constexpr float HI_X = 85.0f;
  static constexpr float LO_X = 90.0f;
  static constexpr float Y = 40.0f;

  displayDigit((m_rightPlayerPoints / 10) % 10, { HI_X, -Y }, window);
  displayDigit(m_rightPlayerPoints % 10, { LO_X, -Y }, window);

  displayDigit((m_leftPlayerPoints / 10) % 10, { -LO_X, -Y }, window);
  displayDigit(m_leftPlayerPoints % 10, { - HI_X, -Y }, window);
}

game::EventStatus Points::onPoint(game::EventType type, game::Event *event) {
  auto point = static_cast<PointEvent*>(event);

  if (point->location == Paddle::Location::RIGHT) {
    m_leftPlayerPoints++;
  } else {
    m_rightPlayerPoints++;
  }

  return game::EventStatus::KEEP;
}
