#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>

//Chaque Cell sera une case de la grille (colonne x, ligne y).
struct Cell {
    int x;
    int y;
};


int main() {
    srand(time(0));  // Initialiser le générateur aléatoire
    
    //Une fenêtre 800x600 intitulée "Snake SFML"
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Snake SFML");
    window.setFramerateLimit(60);  // Limiter à 60 FPS

    // Paramètres de grille
    int cellSize = 20;
    int cols = 800 / cellSize; // 40
    int rows = 600 / cellSize; // 30
    
    // Création du snake
    std::vector<Cell> snake;

    // Position de départ au milieu
    int startX = cols / 2;     // 20
    int startY = rows / 2;     // 15

    // Tête
    snake.push_back({ startX,     startY });

    // Corps
    snake.push_back({ startX - 1, startY });
    snake.push_back({ startX - 2, startY });
    
    // Nourriture
    Cell food{10, 10};
    
    // Direction du serpent
    int dirX = 1;  // vers la droite
    int dirY = 0;  // pas de déplacement vertical

    // Vitesse : le serpent bouge tous les 0.2s
    float moveDelay = 0.2f;
    sf::Clock clock;  // Chronomètre pour contrôler la vitesse
    
    // Une boucle qui attend que l'utilisateur ferme la fenêtre
    while (window.isOpen()) {
        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();

            // Gestion des flèches
            if (const auto* keyEvent = event->getIf<sf::Event::KeyPressed>()) {
                if (keyEvent->scancode == sf::Keyboard::Scan::Right && dirX != -1) {
                    dirX = 1;
                    dirY = 0;
                }
                else if (keyEvent->scancode == sf::Keyboard::Scan::Left && dirX != 1) {
                    dirX = -1;
                    dirY = 0;
                }
                else if (keyEvent->scancode == sf::Keyboard::Scan::Up && dirY != 1) {
                    dirX = 0;
                    dirY = -1;
                }
                else if (keyEvent->scancode == sf::Keyboard::Scan::Down && dirY != -1) {
                    dirX = 0;
                    dirY = 1;
                }
            }
        }

        // Temps écoulé depuis le dernier mouvement
        float elapsed = clock.getElapsedTime().asSeconds();

        if (elapsed >= moveDelay) {
            // On redémarre le chrono
            clock.restart();

            // collision avec les murs pour savoir si le jeu doit se terminer ou non
        if (snake[0].x < 0 || snake[0].x >= cols ||
            snake[0].y < 0 || snake[0].y >= rows) {
            // TODO : gérer le game over
               }
            // ou bien : remettre le serpent et la direction comme au début 

            // wrap autour de la grille (tunnel)
            if (snake[0].x < 0) {
                snake[0].x = cols - 1;
            }
            else if (snake[0].x >= cols) {
                snake[0].x = 0;
            }

            if (snake[0].y < 0) {
                snake[0].y = rows - 1;
            }
            else if (snake[0].y >= rows) {
                snake[0].y = 0;
            }


            // 1) Nouvelle position de tête
            Cell oldHead = snake[0];
            snake[0].x += dirX;
            snake[0].y += dirY;

            if (snake[0].x == food.x && snake[0].y == food.y) {
            // x) faire grandir le serpent
            // y) replacer la pomme

            food.x = rand() % cols;
            food.y = rand() % rows;

            
            //quand le serpent mange la pomme, on ajoute une nouvelle cellule à la fin du serpent
            Cell tail = snake.back();
            snake.push_back(tail);

    }


            // 2) Propager l'ancienne position le long du corps
            Cell prev = oldHead;
            for (std::size_t i = 1; i < snake.size(); ++i) {
                Cell tmp = snake[i];
                snake[i] = prev;
                prev = tmp;
            }
        }
        
        window.clear();
        
        // Crée un rectangle pour le serpent
        sf::RectangleShape segmentShape;
        segmentShape.setSize({ (float)cellSize, (float)cellSize });
        segmentShape.setFillColor(sf::Color::Green);

        // Dessin du serpent
        for (const auto& cell : snake) {
            segmentShape.setPosition({(float)(cell.x * cellSize), (float)(cell.y * cellSize)});
            window.draw(segmentShape);
        }
        
        // Dessin de la nourriture
        sf::RectangleShape foodShape;
        foodShape.setSize({ (float)cellSize, (float)cellSize });
        foodShape.setFillColor(sf::Color::Red);
        foodShape.setPosition({(float)(food.x * cellSize), (float)(food.y * cellSize)});
        window.draw(foodShape);
        
        window.display();
    }
    
    return 0;
}
