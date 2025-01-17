#include "raylib.h"
#include "raymath.h"
#include "Game.h"
#include "Entity.h"
#include "Simulation.h"

#include <iostream>
#include <string>

Game::Game() {
	SetConfigFlags(FLAG_MSAA_4X_HINT);
	InitWindow(width, height, "Gravity The Game");
	SetTargetFPS(250);
	initEntities();
	start();
}

Game::~Game() {
	CloseWindow();
}

void Game::initEntities() {
	// Initialize the entities
	// EarthMass / SunMass = 3 * 10^-6 (3 / 1,000,000)
	Vector2 sunVelocity = { 0.0f, 0.0f };
	Vector2 sunPosition = { width / 2, height / 2 };
	Entity sun(50l, 1000000l, sunVelocity, sunPosition);

	Vector2 earthVelocity = { 0.001f, 0.0f };
	Vector2 earthPosition = { sunPosition.x, (height / 2) + 100 };
	Entity earth(5l, 3l, earthVelocity, earthPosition);

	Vector2 marsVelocity = { 0.001f, 0.0f };
	Vector2 marsPosition = { sunPosition.x, (height / 2) + 150 };
	Entity mars(5l, 2l, marsVelocity, marsPosition);

	entities.push_back(sun);
	entities.push_back(earth);
	entities.push_back(mars);
}

void Game::initEntities(const std::vector<Entity>& entities) {
	// TODO: Finish this function
}

void Game::start() {
	// Set camera zoom
	camera.zoom = 1.0f;
	
	// Start a frame counter
	int framCounter = 0;

	// Main game loop
	while (!WindowShouldClose()) {
		
		handleMouseEvents();
		processKeyPresses();

		BeginDrawing();
		
			ClearBackground(BLACK);
			DrawFPS(10, 10);

			/*
			switch (currentScreen) {
			case Screen::TITLE: drawTitleScreen();
				break;
			case Screen::GAME: // Draw game screen
				break;
			default: std::cout << "Unknown Screen type." << std::endl;
			}
			*/
			BeginMode2D(camera);

				Entity::drawEntities(entities);
				if (sim.getIsPaused()) {
					drawPauseModal();
				}
				
				if (showDebug) {
					drawDebugInfo();
				}
		
			EndMode2D();
		
		EndDrawing();

		// Calculate how many steps to perfrom each frame
		// Frame Rate is limited so that stepsThisFrame should never be 0
		float deltaTime = GetFrameTime();
		int stepsPerSecond = sim.getStepsPerSecond();
		int stepsThisFrame = floor(deltaTime * stepsPerSecond);

		int steps = 0;
		if (!sim.getIsPaused()) {
			while (steps < stepsThisFrame) {
				sim.updateSim(entities);
				steps++;
			}
		}
	}
}

void Game::processKeyPresses() {
	while (int keyCode = GetKeyPressed()) {
		switch (keyCode) {
		case KEY_SPACE: sim.toggleIsPaused();
			break;
		case KEY_I: toggleDebug();
			break;
		case KEY_PERIOD: incTimeScale();
			break;
		case KEY_COMMA: decTimeScale();
			break;
		default: std::cout << "KeyCode: " << keyCode << std::endl;
		}
	}
}

void Game::handleMouseEvents() {
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
		dragCamera();
	}
	else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		// Change screens to the game screen
	}
}

void Game::drawTitleScreen() {
	std::string title = "Gravity the Game!";
	int titleCenter = MeasureText(title.c_str(), 30) / 2;

	std::string start = "Start";
	int startCenter = MeasureText(start.c_str(), 20) / 2;

	DrawText(title.c_str(), getCenter().x - titleCenter, getCenter().y - 15, 30, WHITE);
	DrawText(start.c_str(), getCenter().x - startCenter, getCenter().y - 10, 20, WHITE);
}

void Game::drawPauseModal() {
	float targetX = camera.target.x + (getCenter().x - 100);
	float targetY = camera.target.y + (getCenter().y - 50);
	int textCenter = MeasureText("Paused", 30) / 2;

	DrawRectangle(targetX, targetY, 200, 100, BLACK);
	DrawRectangleLines(targetX, targetY, 200, 100, WHITE);
	DrawText("Paused", targetX + (100 - textCenter), targetY + 35, 30, WHITE);
}

void Game::drawDebugInfo() {
	float offsetX = camera.target.x + 10;
	float camY = camera.target.y;
	int fontSize = 20;

	float deltaTime = GetFrameTime();
	int stepsPerSecond = sim.getStepsPerSecond();

	std::string deltaStr = "Delta Time: " + std::to_string(deltaTime);
	DrawText(deltaStr.c_str(), offsetX, camY + 40, fontSize, WHITE);

	std::string stepsStr = "Steps per second: " + std::to_string(stepsPerSecond);
	DrawText(stepsStr.c_str(), offsetX, camY + 70, fontSize, WHITE);

	std::string timeStr = "Time Scale: " + std::to_string(sim.getTimeScale());
	DrawText(timeStr.c_str(), offsetX, camY + 100, fontSize, WHITE);
}

void Game::dragCamera() {
	Vector2 delta = GetMouseDelta();
	delta = Vector2Scale(delta, -1.0f / camera.zoom);
	camera.target = Vector2Add(camera.target, delta);
}

void Game::toggleDebug() {
	showDebug = !showDebug;
}

void Game::incTimeScale() {
	int timeScale = sim.getTimeScale();
	if (timeScale < 5) {
		sim.setTimeScale(timeScale + 1);
		sim.updateStepsPerSecond();
	}
	else if (timeScale < 25) {
		sim.setTimeScale(timeScale + 5);
		sim.updateStepsPerSecond();
	}
	
}

void Game::decTimeScale() {
	int timeScale = sim.getTimeScale();
	if (timeScale > 5) {
		sim.setTimeScale(timeScale - 5);
		sim.updateStepsPerSecond();
	}
	else if (timeScale > 1) {
		sim.setTimeScale(timeScale - 1);
		sim.updateStepsPerSecond();
	}
}
