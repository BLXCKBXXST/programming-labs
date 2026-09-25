#include "paint_core.hpp"
#include <algorithm>
#include <cmath>
#include <stack>

extern std::stack<Canvas> undoStack;

void saveToUndo(const Canvas& canvas) {
    undoStack.push(canvas);
}

void clearCanvas(Canvas& canvas) {
    for (auto& row : canvas)
        std::fill(row.begin(), row.end(), sf::Color::White);
}

void drawPixel(Canvas& canvas, int x, int y, const sf::Color& color) {
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
        canvas[y][x] = color;
}

void drawBrush(Canvas& canvas, int x, int y, const sf::Color& color, int radius) {
    for (int dy = -radius; dy <= radius; ++dy)
        for (int dx = -radius; dx <= radius; ++dx)
            if (dx*dx + dy*dy <= radius*radius)
                drawPixel(canvas, x + dx, y + dy, color);
}

void drawRectangle(Canvas& canvas, int x1, int y1, int x2, int y2, const sf::Color& color) {
    saveToUndo(canvas);
    int left   = std::min(x1, x2);
    int right  = std::max(x1, x2);
    int top    = std::min(y1, y2);
    int bottom = std::max(y1, y2);
    for (int y = top; y <= bottom; ++y)
        for (int x = left; x <= right; ++x)
            drawPixel(canvas, x, y, color);
}

void drawLine(Canvas& canvas, int x1, int y1, int x2, int y2, const sf::Color& color) {
    saveToUndo(canvas);
    // TODO (оценка 4)
}

void undo(Canvas& canvas) {
    // TODO (оценка 4)
}

void applyGrayscale(Canvas& canvas) {
    saveToUndo(canvas);
    // TODO (оценка 5)
}

void applyNegative(Canvas& canvas) {
    saveToUndo(canvas);
    // TODO (оценка 5)
}

void applyBlur(Canvas& canvas) {
    saveToUndo(canvas);
    // TODO (оценка 5)
}

void renderToWindow(sf::RenderWindow& window, const Canvas& canvas) {
    static sf::Image image;
    static sf::Texture texture;
    static sf::Sprite sprite;

    image.create(WIDTH, HEIGHT);
    for (int y = 0; y < HEIGHT; ++y)
        for (int x = 0; x < WIDTH; ++x)
            image.setPixel(x, y, canvas[y][x]);

    texture.loadFromImage(image);
    texture.setSmooth(false);
    sprite.setTexture(texture);
    sprite.setScale(PIXEL_SIZE, PIXEL_SIZE);
    window.draw(sprite);
}
