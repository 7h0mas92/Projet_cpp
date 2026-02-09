#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>

//Chaque Cell sera une case de la grille (colonne x, ligne y).
struct Cell {
    int x;
    int y;
};


int main() {

    // Initialiser la graine aléatoire
    srand(static_cast<unsigned>(time(0)));
    
    //Une fenêtre 800x600 intitulée "Snake SFML"
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Snake SFML");
    window.setFramerateLimit(60);

    // Charger l'image de fond
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/background.png")) {
        std::cerr << "❌ Erreur : impossible de charger assets/background.png" << std::endl;
        std::cerr << "Vérifiez que le fichier existe dans le dossier assets/" << std::endl;
    } else {
        std::cout << "✅ Image chargée avec succès !" << std::endl;
    }
      
    sf::Sprite background(backgroundTexture);
    
    // Redimensionner l'image à la taille de la fenêtre
    if (backgroundTexture.getSize().x > 0 && backgroundTexture.getSize().y > 0) {
        background.setScale({800.0f / backgroundTexture.getSize().x, 
                            600.0f / backgroundTexture.getSize().y});
    }
    
    // Charger la police
    sf::Font font;
    if (!font.openFromFile("assets/arial/arial.ttf")) {
        std::cerr << "❌ Erreur : impossible de charger assets/arial/arial.ttf" << std::endl;
    } else {
        std::cout << "✅ Police chargée avec succès !" << std::endl;
    }
    
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
    
    bool gameOver = false;  // Variable pour savoir si le jeu est terminé
    bool gameStarted = false;  // Variable pour savoir si le jeu a commencé
    bool playAgain = true;  // Variable pour relancer le jeu
    
    while (playAgain) {
        gameOver = false;
        gameStarted = false;
        
        // Réinitialiser le serpent
        snake.clear();
        snake.push_back({ startX,     startY });
        snake.push_back({ startX - 1, startY });
        snake.push_back({ startX - 2, startY });
        
        // Réinitialiser la direction
        dirX = 1;
        dirY = 0;
        
        // Réinitialiser la nourriture
        food.x = 10;
        food.y = 10;
        
        clock.restart();
        
    // Menu au démarrage
    while (window.isOpen() && !gameStarted) {
        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
                playAgain = false;
            }
            
            // Appuyer sur ESPACE ou ENTER pour commencer
            if (const auto* keyEvent = event->getIf<sf::Event::KeyPressed>()) {
                if (keyEvent->code == sf::Keyboard::Key::Space || 
                    keyEvent->code == sf::Keyboard::Key::Enter) {
                    gameStarted = true;
                }
            }
        }
        
        if (!window.isOpen()) break;
        
        window.clear();
        window.draw(background);
        
        // Afficher un rectangle blanc pour le menu
        sf::RectangleShape menuBox({400, 100});
        menuBox.setFillColor(sf::Color(0, 0, 0, 150));  // Noir semi-transparent
        menuBox.setPosition({200, 250});
        window.draw(menuBox);
        
        // Afficher le texte du menu
        if (font.getInfo().family != "") {
            sf::Text menuText(font, "APPUYEZ SUR ESPACE", 25);
            menuText.setFillColor(sf::Color::White);
            menuText.setPosition({210, 270});
            window.draw(menuText);
        }
        
        window.display();
    }
    
    if (!window.isOpen()) break;
    
    if (!window.isOpen()) break;
    
    // Une boucle qui attend que l'utilisateur ferme la fenêtre
    while (window.isOpen() && !gameOver) {
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

            // collision avec les murs pour savoir si le jeu doit se terminer ou non
            if (snake[0].x < 0 || snake[0].x >= cols ||
                snake[0].y < 0 || snake[0].y >= rows) {
                // TODO : gérer le game over
            }
            
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

            // Vérifier si la tête touche la queue
            for (std::size_t i = 1; i < snake.size(); ++i) {
                if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
                    gameOver = true;
                    std::cout << "💀 GAME OVER ! Vous avez mangé votre queue !" << std::endl;
                }
            }

            if (snake[0].x == food.x && snake[0].y == food.y) {
                // x) faire grandir le serpent
                // y) replacer la pomme
                food.x = rand() % cols;
                food.y = rand() % rows;

                // quand le serpent mange la pomme, on ajoute une nouvelle cellule à la fin du serpent
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
        
        // Dessiner le fond EN PREMIER
        window.draw(background);
        
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
    
    // Écran GAME OVER
    if (gameOver) {
        bool restartGame = false;
        while (window.isOpen() && !restartGame) {
            while (const auto event = window.pollEvent()) {
                if (event->is<sf::Event::Closed>()) {
                    window.close();
                    playAgain = false;
                }
                
                // Appuyer sur ESPACE pour rejouer
                if (const auto* keyEvent = event->getIf<sf::Event::KeyPressed>()) {
                    if (keyEvent->code == sf::Keyboard::Key::Space || 
                        keyEvent->code == sf::Keyboard::Key::Enter) {
                        restartGame = true;
                    }
                }
            }
            
            window.clear();
            window.draw(background);
            
            // Afficher un rectangle rouge pour le game over
            sf::RectangleShape gameOverBox({500, 200});
            gameOverBox.setFillColor(sf::Color(139, 0, 0, 200));  // Rouge foncé semi-transparent
            gameOverBox.setPosition({150, 200});
            window.draw(gameOverBox);
            
            // Afficher le texte GAME OVER
            if (font.getInfo().family != "") {
                sf::Text gameOverText(font, "GAME OVER!", 40);
                gameOverText.setFillColor(sf::Color::White);
                gameOverText.setPosition({240, 220});
                window.draw(gameOverText);
                
                // Afficher la taille du serpent
                sf::Text scoreText(font, "Serpent: " + std::to_string(snake.size()), 20);
                scoreText.setFillColor(sf::Color::Yellow);
                scoreText.setPosition({240, 290});
                window.draw(scoreText);
                
                // Afficher le bouton REJOUER
                sf::Text restartText(font, "APPUYEZ SUR ESPACE POUR REJOUER", 18);
                restartText.setFillColor(sf::Color::Cyan);
                restartText.setPosition({180, 340});
                window.draw(restartText);
            }
            
            window.display();
        }
    }
    }  // Ferme la boucle while(playAgain)
    
    return 0;
}