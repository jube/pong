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
#include <cassert>
#include <cstdio>

#include "game/Action.h"
#include "game/Camera.h"
#include "game/Clock.h"
#include "game/EntityManager.h"
#include "game/Log.h"
#include "game/Resources.h"
#include "game/WindowSettings.h"

#include "local/Ball.h"
#include "local/Ground.h"
#include "local/Paddle.h"
#include "local/Points.h"
#include "local/Singletons.h"

#include "config.h"


int main(int argc, char *argv[]) {
  game::Log::setLevel(game::Log::INFO);

  // setup singletons

  game::SingletonStorage<game::EventManager> storageForEventManager(gEventManager);

  // initialize

  static constexpr unsigned INITIAL_WIDTH = 1024;
  static constexpr unsigned INITIAL_HEIGHT = 576;

  game::WindowSettings settings(INITIAL_WIDTH, INITIAL_HEIGHT, "Game template (version " GAME_VERSION ")");

  sf::RenderWindow window;
  settings.applyTo(window);
  window.setKeyRepeatEnabled(false);

  // add cameras
  game::CameraManager cameras;

  game::FixedRatioCamera mainCamera(Ground::WIDTH / Ground::HEIGHT, Ground::WIDTH);
  cameras.addCamera(mainCamera);

  // add actions
  game::ActionManager actions;

  game::Action closeWindowAction("Close window");
  closeWindowAction.addCloseControl();
  closeWindowAction.addKeyControl(sf::Keyboard::Escape);
  actions.addAction(closeWindowAction);

  game::Action fullscreenAction("Fullscreen");
  fullscreenAction.addKeyControl(sf::Keyboard::F);
  actions.addAction(fullscreenAction);


  game::Action leftPaddleUpAction("Left paddle up");
  leftPaddleUpAction.addKeyControl(sf::Keyboard::S);
  leftPaddleUpAction.setContinuous();
  actions.addAction(leftPaddleUpAction);

  game::Action leftPaddleDownAction("Left paddle down");
  leftPaddleDownAction.addKeyControl(sf::Keyboard::X);
  leftPaddleDownAction.setContinuous();
  actions.addAction(leftPaddleDownAction);

  game::Action rightPaddleUpAction("Right paddle up");
  rightPaddleUpAction.addKeyControl(sf::Keyboard::Up);
  rightPaddleUpAction.setContinuous();
  actions.addAction(rightPaddleUpAction);

  game::Action rightPaddleDownAction("Left paddle down");
  rightPaddleDownAction.addKeyControl(sf::Keyboard::Down);
  rightPaddleDownAction.setContinuous();
  actions.addAction(rightPaddleDownAction);


  // add entities
  game::EntityManager mainEntities;

  Ground ground;
  mainEntities.addEntity(ground);

  Points points;
  mainEntities.addEntity(points);

  Paddle leftPaddle(Paddle::Location::LEFT);
  mainEntities.addEntity(leftPaddle);

  Paddle rightPaddle(Paddle::Location::RIGHT);
  mainEntities.addEntity(rightPaddle);

  Ball ball;
  mainEntities.addEntity(ball);


  // main loop
  game::Clock clock;

  while (window.isOpen()) {
    // input
    sf::Event event;

    while (window.pollEvent(event)) {
      actions.update(event);
      cameras.update(event);
    }

    if (closeWindowAction.isActive()) {
      window.close();
    }

    if (fullscreenAction.isActive()) {
      settings.toggleFullscreen();
      settings.applyTo(window);
      auto sz = window.getSize();

      // fake resize event (not sent when going fullscreen before SFML 2.3.1)
      sf::Event event;
      event.type = sf::Event::Resized;
      event.size.width = sz.x;
      event.size.height = sz.y;
      cameras.update(event);
    }

    if (leftPaddleDownAction.isActive()) {
      leftPaddle.move(Paddle::Move::DOWN);
    } else if (leftPaddleUpAction.isActive()) {
      leftPaddle.move(Paddle::Move::UP);
    } else {
      leftPaddle.move(Paddle::Move::STOP);
    }

    if (rightPaddleDownAction.isActive()) {
      rightPaddle.move(Paddle::Move::DOWN);
    } else if (rightPaddleUpAction.isActive()) {
      rightPaddle.move(Paddle::Move::UP);
    } else {
      rightPaddle.move(Paddle::Move::STOP);
    }

    // update
    auto elapsed = clock.restart();
    auto dt = elapsed.asSeconds();
    mainEntities.update(dt);

    // render
    window.clear({ 0x30, 0x30, 0x30 });

    mainCamera.configure(window);
    mainEntities.render(window);

    window.display();

    actions.reset();
  }

  return 0;
}
