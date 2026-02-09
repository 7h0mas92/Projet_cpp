#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <optional>
#include "Snake.hpp"

// Énumération pour les différents états du jeu
enum class GameState {
    Menu,
    Playing,
    GameOver
};

// Classe principale du jeu
class Game {
private:
    // Fenêtre et ressources
    sf::RenderWindow window;
    sf::Texture backgroundTexture;
    std::optional<sf::Sprite> background;
    sf::Font font;
    
    // Paramètres de la grille
    int cellSize;
    int cols;
    int rows;
    
    // Objets du jeu
    Snake snake;
    Cell food;
    
    // État du jeu
    GameState state;
    float moveDelay;
    sf::Clock clock;
    bool playAgain;
    int foodCount;  // Compteur de nourritures mangées
    
    // Méthodes privées
    void loadResources();
    void handleMenuEvents();
    void handlePlayingEvents();
    void handleGameOverEvents();
    void renderMenu();
    void renderPlaying();
    void renderGameOver();
    void resetGame();
    void spawnFood();

public:
    // Constructeur
    Game();
    
    // Méthodes publiques pour contrôler le jeu
    void handleEvents();
    void update();
    void render();
    bool isWindowOpen() const { return window.isOpen(); }
    GameState getState() const { return state; }
    bool shouldContinue() const { return playAgain; }
};

#endif // GAME_HPP
