#include "raylib.h"
#include "raymath.h"
#include "Game.h"
#include "Entity.h"
#include "Simulation.h"
#include "../util/Vector2.h"

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

// Initialize the entities
void Game::initEntities() {
	util::Vector2 sunVelocity(0.0, 0.0);
	util::Vector2 sunPosition(width / 2, height / 2);
	double sunRadius = 6.957e5;
	double sunMass = 1.988416e30;
	Entity sun(100, sunMass, sunVelocity, sunPosition, YELLOW);

	// Mercury
	util::Vector2 mercuryVelocity(47.36, 0.0);
	util::Vector2 mercuryPosition(sunPosition.x, sunPosition.y + 57.91e6);
	double mercuryRadius = 2439.7;
	double mercuryMass = 3.3011e23;
	Entity mercury(15, mercuryMass, mercuryVelocity, mercuryPosition, GRAY);

	// Venus
	util::Vector2 venusVelocity(35.02, 0.0);
	util::Vector2 venusPosition(sunPosition.x, sunPosition.y + 108.94e6);
	double venusRadius = 6051.8;
	double venusMass = 4.8675e24;
	Entity venus(25, venusMass, venusVelocity, venusPosition, {192, 191, 187, 255});

	// EarthMass / SunMass = 3 * 10^-6 (3 / 1,000,000)
	util::Vector2 earthVelocity(29.7827, 0.0);
	util::Vector2 earthPosition(sunPosition.x, sunPosition.y + 149598023);
	double earthRadius = 6371;
	double earthMass = 5.972168e24;
	Entity earth(25, earthMass, earthVelocity, earthPosition, BLUE);

	// MarsMass / SunMass = 3.227 * 10^-7 kg/kg (3.227 / 10,000,000)
	util::Vector2 marsVelocity(24.07, 0.0);
	util::Vector2 marsPosition(sunPosition.x, sunPosition.y + 227939366);
	double marsRadius = 3389.5;
	double marsMass = 6.4171e23;
	Entity mars(20, marsMass, marsVelocity, marsPosition, RED);


	entities.push_back(sun);
	entities.push_back(mercury);
	entities.push_back(venus);
	entities.push_back(earth);
	entities.push_back(mars);

	// Jupiter
	entities.emplace_back(
		Entity(
			50,
			1.8982e27,
			util::Vector2(13.06, 0.0),
			util::Vector2(sunPosition.x, sunPosition.y + 7.78595e8),
			DARKBROWN
		));
	// Saturn
	entities.emplace_back(
		Entity(
			45,
			5.6834e26,
			util::Vector2(9.68, 0.0),
			util::Vector2(sunPosition.x, sunPosition.y + 1.43353e9),
			BROWN
		));
	// Uranus
	entities.emplace_back(
		Entity(
			40,
			8.6810e25,
			util::Vector2(6.80, 0.0),
			util::Vector2(sunPosition.x, sunPosition.y + 2.870972e9),
			{113, 212, 240, 255} // Light Blue
		));
	// Neptune
	entities.emplace_back(
		Entity(
			40,
			1.024e26,
			util::Vector2(5.43, 0.0),
			util::Vector2(sunPosition.x, sunPosition.y + 4.50e9),
			{153, 227, 247, 255} // Lighter Blue
		));
	// Pluto (It's a planet in my heart)
	entities.emplace_back(
		Entity(
			10,
			1.3025e22,
			util::Vector2(4.743, 0.0),
			util::Vector2(sunPosition.x, sunPosition.y + 5.90638e9),
			LIGHTGRAY
		));
}

void Game::initEntities(const std::vector<Entity>& entities) {
	// TODO: Finish this function
}

void Game::start() {
	// Set camera zoom
	camera.zoom = 0.5f;
	
	// Start a frame counter
	int framCounter = 0;

	// Main game loop
	while (!WindowShouldClose()) {
		
		zoomCamera();
		handleMousePresses();
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
				
			EndMode2D();

			if (sim.getIsPaused()) {
				drawPauseModal();
			}

			if (showDebug) {
				drawDebugInfo();
			}
		
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

void Game::handleMousePresses() {
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
		dragCamera();
	}
	else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		// Change screens to the game screen
	}
}

void Game::drawTitleScreen() const {
	std::string title = "Gravity the Game!";
	int titleCenter = MeasureText(title.c_str(), 30) / 2;

	std::string start = "Start";
	int startCenter = MeasureText(start.c_str(), 20) / 2;

	DrawText(title.c_str(), getCenter().x - titleCenter, getCenter().y - 15, 30, WHITE);
	DrawText(start.c_str(), getCenter().x - startCenter, getCenter().y - 10, 20, WHITE);
}

void Game::drawPauseModal() const {
	float targetX = getCenter().x - 100;
	float targetY = getCenter().y - 50;
	int textCenter = MeasureText("Paused", 30) / 2;

	DrawRectangle(targetX, targetY, 200, 100, BLACK);
	DrawRectangleLines(targetX, targetY, 200, 100, WHITE);
	DrawText("Paused", targetX + (100 - textCenter), targetY + 35, 30, WHITE);
}

void Game::drawDebugInfo() {
	float posX = 10.0f;
	int fontSize = 20;

	float deltaTime = GetFrameTime();
	int stepsPerSecond = sim.getStepsPerSecond();

	std::string deltaStr = "Delta Time: " + std::to_string(deltaTime);
	DrawText(deltaStr.c_str(), posX, 40, fontSize, WHITE);

	std::string stepsStr = "Steps per second: " + std::to_string(stepsPerSecond);
	DrawText(stepsStr.c_str(), posX, 70, fontSize, WHITE);

	std::string timeStr = "Time Scale: " + std::to_string(sim.getTimeScale());
	DrawText(timeStr.c_str(), posX, 100, fontSize, WHITE);
}

void Game::dragCamera() {
	Vector2 delta = GetMouseDelta();
	delta = Vector2Scale(delta, -1.0f / camera.zoom);
	camera.target = Vector2Add(camera.target, delta);
}

void Game::zoomCamera() {
	float wheel = GetMouseWheelMove();
	if (wheel != 0) {
		// Get the world point that is under the mouse
		Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);

		// Set the offset to where the mouse is
		camera.offset = GetMousePosition();

		// Set the target to match, so that the camera maps the world space point 
		// under the cursor to the screen space point under the cursor at any zoom
		camera.target = mouseWorldPos;

		// Zoom increment
		float scaleFactor = 1.0f + (0.25f * fabs(wheel));
		if (wheel < 0) 
			scaleFactor = 1.0f / scaleFactor;
		camera.zoom = Clamp(camera.zoom * scaleFactor, 0.125f, 64.0f);
	}
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
	else if (timeScale < 20) {
		sim.setTimeScale(timeScale + 5);
		sim.updateStepsPerSecond();
	}
	else if (timeScale < 50) {
		sim.setTimeScale(timeScale + 10);
		sim.updateStepsPerSecond();
	}
	
}

void Game::decTimeScale() {
	int timeScale = sim.getTimeScale();
	if (timeScale > 20) {
		sim.setTimeScale(timeScale - 10);
		sim.updateStepsPerSecond();
	}
	else if (timeScale > 5) {
		sim.setTimeScale(timeScale - 5);
		sim.updateStepsPerSecond();
	}
	else if (timeScale > 1) {
		sim.setTimeScale(timeScale - 1);
		sim.updateStepsPerSecond();
	}
}
