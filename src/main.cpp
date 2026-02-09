#include "../include/Game.hpp"
#include <iostream>

int main() {
    std::cout << "🎮 Démarrage du jeu Snake SFML..." << std::endl;
    
    // Créer l'instance du jeu
    Game game;
    
    std::cout << "📋 Contrôles:" << std::endl;
    std::cout << "  - ESPACE : Démarrer le jeu" << std::endl;
    std::cout << "  - ↑↓←→ : Déplacer le serpent" << std::endl;
    std::cout << "  - ESPACE (Game Over) : Rejouer" << std::endl;
    std::cout << std::endl;
    
    // Boucle principale du jeu
    while (game.isWindowOpen() && game.shouldContinue()) {
        // Gérer les événements (clics, touches, fermeture)
        game.handleEvents();
        
        // Mettre à jour la logique du jeu (déplacement du serpent, collisions)
        game.update();
        
        // Rendre le jeu à l'écran (dessiner le serpent, la nourriture, les menus)
        game.render();
    }
    
    std::cout << "👋 Merci d'avoir joué ! À bientôt !" << std::endl;
    
    return 0;
}