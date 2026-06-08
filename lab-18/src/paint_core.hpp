#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <stack>

constexpr int WIDTH      = 200;
constexpr int HEIGHT     = 150;
constexpr int PIXEL_SIZE = 4;

using Canvas = std::vector<std::vector<sf::Color>>;

void saveToUndo(const Canvas& canvas);
void clearCanvas(Canvas& canvas);
void drawPixel(Canvas& canvas, int x, int y, const sf::Color& color);
void drawBrush(Canvas& canvas, int x, int y, const sf::Color& color, int radius);
void drawRectangle(Canvas& canvas, int x1, int y1, int x2, int y2, const sf::Color& color);
void drawLine(Canvas& canvas, int x1, int y1, int x2, int y2, const sf::Color& color);
void undo(Canvas& canvas);
void applyGrayscale(Canvas& canvas);
void applyNegative(Canvas& canvas);
void applyBlur(Canvas& canvas);
void renderToWindow(sf::RenderWindow& window, const Canvas& canvas);
