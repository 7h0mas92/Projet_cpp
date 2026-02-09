#include "../include/Snake.hpp"

Snake::Snake(int startX, int startY, int cols, int rows) 
    : dirX(1), dirY(0), cols(cols), rows(rows) {
    // Initialiser le serpent avec 3 segments
    body.push_back({ startX,     startY });     // Tête
    body.push_back({ startX - 1, startY });     // Corps
    body.push_back({ startX - 2, startY });     // Queue
}

void Snake::reset(int startX, int startY) {
    body.clear();
    body.push_back({ startX,     startY });
    body.push_back({ startX - 1, startY });
    body.push_back({ startX - 2, startY });
    dirX = 1;
    dirY = 0;
}

void Snake::move() {
    // Ajouter une nouvelle tête dans la direction actuelle
    body.insert(body.begin(), {body[0].x + dirX, body[0].y + dirY});
}

void Snake::setDirection(int newDirX, int newDirY) {
    // Vérifier qu'on ne va pas dans la direction opposée
    if ((newDirX == -dirX && newDirY == 0) || (newDirY == -dirY && newDirX == 0)) {
        return;  // Ignorer les directions opposées
    }
    dirX = newDirX;
    dirY = newDirY;
}

bool Snake::eatsFood(const Cell& food) const {
    return body[0].x == food.x && body[0].y == food.y;
}

void Snake::grow() {
    // La croissance se fait en ne supprimant pas la queue après le move()
    // Cette méthode est là pour la clarté du code
}

void Snake::removeTail() {
    if (!body.empty()) {
        body.pop_back();
    }
}

bool Snake::checkSelfCollision() const {
    // Vérifier si la tête touche le corps
    for (std::size_t i = 1; i < body.size(); ++i) {
        if (body[0].x == body[i].x && body[0].y == body[i].y) {
            return true;
        }
    }
    return false;
}

void Snake::wrapAround() {
    // Gestion du tunnel aux bords de la grille
    if (body[0].x < 0) {
        body[0].x = cols - 1;
    } else if (body[0].x >= cols) {
        body[0].x = 0;
    }
    
    if (body[0].y < 0) {
        body[0].y = rows - 1;
    } else if (body[0].y >= rows) {
        body[0].y = 0;
    }
}
