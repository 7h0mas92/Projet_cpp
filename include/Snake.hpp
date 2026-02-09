#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <vector>

// Structure représentant une cellule dans la grille
struct Cell {
    int x;
    int y;
};

// Classe gérant le serpent
class Snake {
private:
    std::vector<Cell> body;  // Corps du serpent
    int dirX;                // Direction horizontale (-1, 0, 1)
    int dirY;                // Direction verticale (-1, 0, 1)
    int cols;                // Nombre de colonnes
    int rows;                // Nombre de lignes

public:
    // Constructeur
    Snake(int startX, int startY, int cols, int rows);
    
    // Réinitialiser le serpent
    void reset(int startX, int startY);
    
    // Déplacer le serpent
    void move();
    
    // Changer la direction
    void setDirection(int newDirX, int newDirY);
    
    // Vérifier si le serpent mange la nourriture
    bool eatsFood(const Cell& food) const;
    
    // Faire grandir le serpent (ajouter un segment)
    void grow();
    
    // Enlever le dernier segment
    void removeTail();
    
    // Vérifier si le serpent se mord lui-même
    bool checkSelfCollision() const;
    
    // Gérer le wrap-around (tunnel aux bords)
    void wrapAround();
    
    // Getters
    const std::vector<Cell>& getBody() const { return body; }
    int getDirX() const { return dirX; }
    int getDirY() const { return dirY; }
    Cell getHead() const { return body[0]; }
    std::size_t getSize() const { return body.size(); }
};

#endif // SNAKE_HPP
