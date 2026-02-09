# 🐍 Snake Game - SFML Edition

Un jeu Snake classique développé en C++ avec la bibliothèque SFML 3.0, utilisant une architecture orientée objet propre et maintenable.

## 🎮 Démarrage rapide

### Sur macOS

```bash
brew install sfml
git clone https://github.com/7h0mas92/Projet_cpp.git
cd Projet_cpp
./setup.sh    # Installation automatique
# ou manuellement:
make re
./jeu
```

### Sur Windows

Téléchargez SFML 3.0.2 depuis [sfml-dev.org](https://www.sfml-dev.org/download/sfml/3.0.2/) et suivez les instructions dans la section "Compiler SFML pour Windows".

### Sur Linux

```bash
sudo apt-get install libsfml-dev
git clone https://github.com/7h0mas92/Projet_cpp.git
cd Projet_cpp
./setup.sh    # Installation automatique
# ou manuellement:
make re
./jeu
```

## 🎯 Comment jouer

1. **Démarrer** : Appuyez sur **ESPACE** ou **ENTRÉE**
2. **Diriger** : Utilisez les **flèches ↑ ↓ ← →** du clavier
3. **Manger** : Collectez les carrés rouges pour grandir
4. **Game Over** : Évitez votre queue ! Appuyez sur **ESPACE** pour rejouer
5. **Quitter** : Fermez la fenêtre pour quitter

## 📋 Pré-requis

- **C++17 ou supérieur**
- **SFML 3.0.2** (voir instructions d'installation ci-dessus)
- **Make** et **g++** pour la compilation
- **Git** pour cloner le projet

## ✨ Fonctionnalités

✅ Architecture orientée objet avec classe `Game`  
✅ Menu de démarrage avec instructions  
✅ Gameplay fluide en temps réel (60 FPS)  
✅ Image de fond personnalisée  
✅ Affichage du score (taille du serpent)  
✅ Écran Game Over avec option de rejouer  
✅ Détection de collision avec le corps  
✅ Effet tunnel (wrap-around aux murs)  
✅ Police personnalisée Arial  
✅ Code modulaire et facilement extensible  

## 📁 Structure du projet

```
.
├── src/
│   └── main.cpp              # Point d'entrée du jeu
├── include/
│   └── Game.hpp              # En-tête de la classe Game
├── assets/
│   ├── background.png        # Image de fond du jeu
│   └── arial/
│       └── arial.ttf         # Police Arial Unicode
├── lib/
│   ├── macOS/                # Bibliothèques SFML pour macOS
│   └── Windows/              # Bibliothèques SFML pour Windows
├── Makefile                  # Configuration de compilation
├── setup.sh                  # Script d'installation automatique
├── .gitignore                # Fichiers à ignorer
└── README.md                 # Ce fichier
```

## 🛠️ Compilation et Nettoyage

```bash
make          # Compilation simple
make re       # Recompilation complète
make clean    # Supprime les fichiers .o
make fclean   # Supprime les fichiers .o et l'exécutable
```

## 🏗️ Architecture du Code

### Classe `Game`

Le code est organisé autour d'une classe `Game` qui encapsule toute la logique du jeu :

```cpp
class Game {
public:
    Game();                      // Constructeur
    ~Game();                     // Destructeur
    
    bool isWindowOpen() const;   // Vérifie si la fenêtre est ouverte
    bool shouldContinue() const; // Vérifie si on doit continuer
    
    void handleEvents();         // Gère les événements (touches, souris, etc.)
    void update();              // Met à jour la logique du jeu
    void render();              // Dessine à l'écran
};
```

### Flux principal (`main.cpp`)

```cpp
Game game;
while (game.isWindowOpen() && game.shouldContinue()) {
    game.handleEvents();  // Gestion des entrées
    game.update();        // Mise à jour logique
    game.render();        // Rendu graphique
}
```

## 🔧 Troubleshooting

### "Image chargée" ou "Police non chargée" (erreur au démarrage)

Assurez-vous que vous lancez le jeu depuis le répertoire racine du projet :

```bash
./jeu
```

### Erreur de compilation SFML

Vérifiez que SFML 3.0.2 est correctement installé et que les chemins dans le Makefile sont à jour.

### Sur macOS avec chip M1/M2

Installez la version ARM de SFML :

```bash
brew install sfml
```

## 🔨 Compiler SFML pour Windows (optionnel)
## � Compiler SFML pour Windows (optionnel)

Si vous devez recompiler les bibliothèques statiques SFML pour Windows :

1. **Télécharger SFML 3.0.2** depuis [https://www.sfml-dev.org/download.php](https://www.sfml-dev.org/download.php)

2. **Installer les dépendances** (dans MSYS2):
   ```bash
   pacman -S mingw-w64-x86_64-cmake mingw-w64-x86_64-ninja
   ```

3. **Compiler SFML en mode statique**:
   ```bash
   cd /chemin/vers/SFML-3.0.2
   cmake -S . -B build-static \
         -G Ninja \
         -DCMAKE_BUILD_TYPE=Release \
         -DBUILD_SHARED_LIBS=OFF \
         -DSFML_BUILD_EXAMPLES=OFF \
         -DSFML_BUILD_TEST_SUITE=OFF
   cmake --build build-static
   ```

4. **Copier les bibliothèques** dans `lib/Windows/`:
   ```bash
   mkdir -p /chemin/vers/Projet_cpp/lib/Windows
   cp build-static/lib/*.a /chemin/vers/Projet_cpp/lib/Windows/
   ```

5. **Vérifier que les bibliothèques sont présentes**:
   ```bash
   ls lib/Windows/
   # Devrait afficher: libsfml-*.a et les dépendances
   ```

## 📚 Documentation

Pour plus d'informations sur SFML, consultez :
- [Documentation officielle SFML](https://www.sfml-dev.org/documentation.php)
- [Tutoriels SFML](https://www.sfml-dev.org/tutorials.php)

## 📝 Améliorations futures possibles

- [ ] Système de score persistant (sauvegarde en fichier)
- [ ] Niveaux de difficulté (augmentation de vitesse)
- [ ] Menus supplémentaires (options, contrôles personnalisés)
- [ ] Sons et musique
- [ ] Sauvegardes du meilleur score
- [ ] Modes de jeu (infini, time attack, etc.)

## 👨‍💻 Auteur

Projet réalisé avec C++ et SFML.

---

**Amusez-vous bien en jouant ! 🎮🐍**
