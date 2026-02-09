#include "../include/Game.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

Game::Game() 
    : window(sf::VideoMode({800, 600}), "Snake SFML"),
      cellSize(20),
      cols(800 / 20),
      rows(600 / 20),
      snake(cols / 2, rows / 2, cols, rows),
      food{10, 10},
      state(GameState::Menu),
      moveDelay(0.2f),
      playAgain(true),
      foodCount(0),
      currentFps(60),
      selectedFpsIndex(0),
      displayedFps(60),
      frameCount(0) {
    
    // Initialiser la graine aléatoire
    srand(static_cast<unsigned>(time(0)));
    
    setFps(60);  // Démarrer avec 60 FPS
    loadResources();
}

void Game::loadResources() {
    // Charger l'image de fond
    if (!backgroundTexture.loadFromFile("assets/background.png")) {
        std::cerr << "❌ Erreur : impossible de charger assets/background.png" << std::endl;
        std::cerr << "Vérifiez que le fichier existe dans le dossier assets/" << std::endl;
    } else {
        std::cout << "✅ Image chargée avec succès !" << std::endl;
    }
    
    // Créer le sprite avec la texture
    background.emplace(backgroundTexture);
    
    // Redimensionner l'image à la taille de la fenêtre
    if (backgroundTexture.getSize().x > 0 && backgroundTexture.getSize().y > 0) {
        background->setScale({800.0f / backgroundTexture.getSize().x, 
                            600.0f / backgroundTexture.getSize().y});
    }
    
    // Charger la police
    if (!font.openFromFile("assets/arial/arial.ttf")) {
        std::cerr << "❌ Erreur : impossible de charger assets/arial/arial.ttf" << std::endl;
    } else {
        std::cout << "✅ Police chargée avec succès !" << std::endl;
    }
}

void Game::resetGame() {
    state = GameState::Menu;
    snake.reset(cols / 2, rows / 2);
    food.x = 10;
    food.y = 10;
    moveDelay = 0.2f;
    foodCount = 0;
}

void Game::handleEvents() {
    switch (state) {
        case GameState::Menu:
            handleMenuEvents();
            break;
        case GameState::FpsSelection:
            handleFpsSelectionEvents();
            break;
        case GameState::Playing:
            handlePlayingEvents();
            break;
        case GameState::GameOver:
            handleGameOverEvents();
            break;
    }
}

void Game::handleMenuEvents() {
    while (const auto event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
            playAgain = false;
        }
        
        if (const auto* keyEvent = event->getIf<sf::Event::KeyPressed>()) {
            if (keyEvent->code == sf::Keyboard::Key::Space || 
                keyEvent->code == sf::Keyboard::Key::Enter) {
                state = GameState::FpsSelection;  // Aller au menu de sélection des FPS
            }
        }
    }
}

void Game::handlePlayingEvents() {
    while (const auto event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
        
        if (const auto* keyEvent = event->getIf<sf::Event::KeyPressed>()) {
            if (keyEvent->scancode == sf::Keyboard::Scan::Right) {
                snake.setDirection(1, 0);
            }
            else if (keyEvent->scancode == sf::Keyboard::Scan::Left) {
                snake.setDirection(-1, 0);
            }
            else if (keyEvent->scancode == sf::Keyboard::Scan::Up) {
                snake.setDirection(0, -1);
            }
            else if (keyEvent->scancode == sf::Keyboard::Scan::Down) {
                snake.setDirection(0, 1);
            }
        }
    }
}

void Game::handleGameOverEvents() {
    while (const auto event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
            playAgain = false;
        }
        
        if (const auto* keyEvent = event->getIf<sf::Event::KeyPressed>()) {
            if (keyEvent->code == sf::Keyboard::Key::Space || 
                keyEvent->code == sf::Keyboard::Key::Enter) {
                resetGame();  // Réinitialiser le jeu avant de retourner au menu
            }
        }
    }
}

void Game::update() {
    if (state != GameState::Playing) {
        return;
    }
    
    float elapsed = clock.getElapsedTime().asSeconds();
    
    if (elapsed >= moveDelay) {
        clock.restart();
        
        // Déplacer le serpent
        snake.move();
        
        // Gérer le wrap-around
        snake.wrapAround();
        
        // Vérifier si le serpent mange la nourriture
        if (snake.eatsFood(food)) {
            spawnFood();
            foodCount++;
            
            // Augmenter la vitesse tous les 7 aliments
            if (foodCount >= 7) {
                moveDelay *= 0.9f;  // Réduction de 10% du délai = 10% plus rapide
                if (moveDelay < 0.05f) moveDelay = 0.05f;  // Limite minimale
                foodCount = 0;
                std::cout << "⚡ VITESSE AUGMENTÉE ! Délai: " << moveDelay << "s" << std::endl;
            }
        } else {
            snake.removeTail();
        }
        
        // Vérifier la collision avec soi-même
        if (snake.checkSelfCollision()) {
            state = GameState::GameOver;
            std::cout << "💀 GAME OVER ! Vous avez mangé votre queue !" << std::endl;
        }
    }
}

void Game::spawnFood() {
    food.x = rand() % cols;
    food.y = rand() % rows;
}

void Game::render() {
    window.clear();
    
    switch (state) {
        case GameState::Menu:
            renderMenu();
            break;
        case GameState::FpsSelection:
            renderFpsSelection();
            break;
        case GameState::Playing:
            renderPlaying();
            break;
        case GameState::GameOver:
            renderGameOver();
            break;
    }
    
    // Afficher les FPS en temps réel
    frameCount++;
    if (fpsTimer.getElapsedTime().asSeconds() >= 1.0f) {
        displayedFps = frameCount;
        frameCount = 0;
        fpsTimer.restart();
    }
    
    // Afficher le compteur FPS en haut à droite
    if (font.getInfo().family != "") {
        sf::Text fpsDisplay(font, std::to_string(displayedFps) + " FPS", 20);
        fpsDisplay.setFillColor(sf::Color::Green);
        fpsDisplay.setPosition({750 - fpsDisplay.getLocalBounds().size.x, 10});
        window.draw(fpsDisplay);
    }
    
    window.display();
}

void Game::renderMenu() {
    if (background) window.draw(*background);
    
    // Afficher un rectangle pour le menu
    sf::RectangleShape menuBox({400, 100});
    menuBox.setFillColor(sf::Color(0, 0, 0, 150));
    menuBox.setPosition({200, 250});
    window.draw(menuBox);
    
    // Afficher le texte du menu
    if (font.getInfo().family != "") {
        sf::Text menuText(font, "APPUYEZ SUR ESPACE", 25);
        menuText.setFillColor(sf::Color::White);
        menuText.setPosition({210, 270});
        window.draw(menuText);
    }
}

void Game::renderPlaying() {
    // Dessiner le fond
    if (background) window.draw(*background);
    
    // Dessiner le serpent
    sf::RectangleShape segmentShape;
    segmentShape.setSize({(float)cellSize, (float)cellSize});
    segmentShape.setFillColor(sf::Color::Green);
    
    for (const auto& cell : snake.getBody()) {
        segmentShape.setPosition({(float)(cell.x * cellSize), (float)(cell.y * cellSize)});
        window.draw(segmentShape);
    }
    
    // Dessiner la nourriture
    sf::RectangleShape foodShape;
    foodShape.setSize({(float)cellSize, (float)cellSize});
    foodShape.setFillColor(sf::Color::Red);
    foodShape.setPosition({(float)(food.x * cellSize), (float)(food.y * cellSize)});
    window.draw(foodShape);
}

void Game::renderGameOver() {
    if (background) window.draw(*background);
    
    // Afficher un rectangle pour le game over
    sf::RectangleShape gameOverBox({500, 200});
    gameOverBox.setFillColor(sf::Color(139, 0, 0, 200));
    gameOverBox.setPosition({150, 200});
    window.draw(gameOverBox);
    
    // Afficher le texte GAME OVER
    if (font.getInfo().family != "") {
        sf::Text gameOverText(font, "GAME OVER!", 40);
        gameOverText.setFillColor(sf::Color::White);
        gameOverText.setPosition({240, 220});
        window.draw(gameOverText);
        
        // Afficher la taille du serpent
        sf::Text scoreText(font, "Serpent: " + std::to_string(snake.getSize()), 20);
        scoreText.setFillColor(sf::Color::Yellow);
        scoreText.setPosition({240, 290});
        window.draw(scoreText);
        
        // Afficher le bouton REJOUER
        sf::Text restartText(font, "APPUYEZ SUR ESPACE POUR REJOUER", 18);
        restartText.setFillColor(sf::Color::Cyan);
        restartText.setPosition({180, 340});
        window.draw(restartText);
    }
}

void Game::setFps(int fps) {
    currentFps = fps;
    window.setFramerateLimit(fps);
}

void Game::handleFpsSelectionEvents() {
    while (const auto event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
            playAgain = false;
            return;
        }
        
        if (const auto* keyEvent = event->getIf<sf::Event::KeyPressed>()) {
            // Flèches gauche/droite pour naviguer les FPS
            if (keyEvent->code == sf::Keyboard::Key::Right && 
                selectedFpsIndex < (int)availableFps.size() - 1) {
                selectedFpsIndex++;
            } else if (keyEvent->code == sf::Keyboard::Key::Left && selectedFpsIndex > 0) {
                selectedFpsIndex--;
            }
            // ESPACE ou ENTRÉE pour confirmer et commencer
            else if (keyEvent->code == sf::Keyboard::Key::Space || 
                     keyEvent->code == sf::Keyboard::Key::Enter) {
                setFps(availableFps[selectedFpsIndex]);
                state = GameState::Playing;
                clock.restart();
                return;
            }
        }
    }
}

void Game::renderFpsSelection() {
    window.clear();
    if (background) {
        window.draw(*background);
    }
    
    // Afficher un rectangle sombre pour le menu des FPS
    sf::RectangleShape fpsBox({500, 350});
    fpsBox.setFillColor(sf::Color(0, 0, 0, 230));
    fpsBox.setPosition({150, 125});
    window.draw(fpsBox);
    
    // Titre
    sf::Text titleText(font, "CHOISIR LES FPS", 38);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition({200, 150});
    window.draw(titleText);
    
    // Afficher les options de FPS en grille
    float startX = 170;
    float startY = 235;
    float spacingX = 105;
    float spacingY = 70;
    int itemsPerRow = 3;
    
    for (size_t i = 0; i < availableFps.size(); i++) {
        int row = i / itemsPerRow;
        int col = i % itemsPerRow;
        
        float posX = startX + (col * spacingX);
        float posY = startY + (row * spacingY);
        
        // Créer un rectangle pour chaque option FPS
        sf::RectangleShape fpsButton({85, 50});
        fpsButton.setPosition({posX, posY});
        
        if ((int)i == selectedFpsIndex) {
            // FPS sélectionné en blanc avec bordure cyan épaisse
            fpsButton.setFillColor(sf::Color::White);
            fpsButton.setOutlineThickness(3);
            fpsButton.setOutlineColor(sf::Color::Cyan);
        } else {
            // FPS non sélectionné en gris foncé avec bordure grise
            fpsButton.setFillColor(sf::Color(80, 80, 80));
            fpsButton.setOutlineThickness(2);
            fpsButton.setOutlineColor(sf::Color(120, 120, 120));
        }
        window.draw(fpsButton);
        
        // Texte FPS (centré simplement)
        std::string fpsStr = std::to_string(availableFps[i]);
        sf::Text fpsText(font, fpsStr, 22);
        
        // Couleur du texte en contraste avec le bouton
        if ((int)i == selectedFpsIndex) {
            fpsText.setFillColor(sf::Color::Black);  // Noir sur blanc
        } else {
            fpsText.setFillColor(sf::Color::White);  // Blanc sur gris
        }
        
        // Centrer le texte manuellement
        float centerX = posX + 42.5f - (fpsStr.length() * 7);  // ~7 pixels par caractère
        float centerY = posY + 12;
        fpsText.setPosition({centerX, centerY});
        window.draw(fpsText);
    }
    
    // Instructions en bas
    sf::Text instructText(font, "Flèches ◄ ► pour choisir | ESPACE pour valider", 13);
    instructText.setFillColor(sf::Color::Yellow);
    instructText.setPosition({160, 380});
    window.draw(instructText);
}
