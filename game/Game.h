#pragma once

#include "Simulation.h"
#include "Entity.h"

#include <vector>

class Game {
public:
	Game();

	~Game();

	int getWidth() const { return width; }
	int getHeight() const { return height; }
	Vector2 getCenter() const { return center; }

	void toggleDebug();

private:
	const int height = 900;
	const int width = 1600;
	const Vector2 center = { width / 2.0f, height / 2.0f };
	Simulation sim;
	Camera2D camera = { 0 };
	bool showDebug = false;
	int frameCounter = 0;
	std::vector<Entity> entities;
	enum class Screen {
		TITLE,
		GAME
	};
	Screen currentScreen = Screen::TITLE;

	void start();
	void initEntities();
	void initEntities(const std::vector<Entity>& entities);
	void processKeyPresses();
	void handleMousePresses();
	void dragCamera();
	void zoomCamera();

	void drawTitleScreen() const;
	void drawPauseModal() const;
	void drawDebugInfo();

	void incTimeScale();
	void decTimeScale();
};

