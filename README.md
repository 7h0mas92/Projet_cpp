# 🐍 Snake Game - SFML Edition

Un jeu Snake classique développé en C++ avec la bibliothèque SFML 3.0.

## 📦 Bibliothèques utilisées et versions

| Bibliothèque | Version | Usage | Statut |
|---|---|---|---|
| **SFML** | 3.0.2 | Graphiques, fenêtres, événements, audio | ✅ Statique |
| **C++** | C++17 | Standard de compilation | ✅ Actif |
| **g++/clang++** | 11+ | Compilateur | ✅ Requis |
| **Make** | 3.8+ | Système de build | ✅ Requis |
| **Git** | 2.0+ | Contrôle de version | ✅ Requis |

### Dépendances SFML incluses (statiques)

```
SFML 3.0.2 modules:
├── sfml-graphics    # Rendu 2D, sprites, textures
├── sfml-window      # Gestion de fenêtre
├── sfml-system      # Clock, Vector2, Time
├── sfml-audio       # (Prêt pour future utilisation)
└── sfml-network     # (Prêt pour future utilisation)

Dépendances externes:
├── libfreetype      # Rendu de polices
├── libjpeg          # Décodage JPEG
├── libpng           # Décodage PNG
├── libogg           # Codec audio Ogg
├── libvorbis        # Codec audio Vorbis
├── libFLAC          # Codec audio FLAC
└── OpenGL           # Rendering 3D (macOS/Linux)
```

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

## � Répartition des tâches

### Architecture et structure du code

| Module | Description | Status |
|--------|-------------|--------|
| **src/main.cpp** | Point d'entrée du jeu | ✅ Complet |
| **src/Game.cpp/.hpp** | Classe principale du jeu (boucle principale, événements, rendu) | ✅ Complet |
| **src/Snake.cpp/.hpp** | Logique du serpent (mouvement, collision, croissance) | ✅ Complet |

### Fonctionnalités implémentées

| Feature | Description | Développeur | Status |
|---------|-------------|-------------|--------|
| **Menu de démarrage** | Écran titre avec instructions | ✅ | Complet |
| **Gameplay** | Boucle de jeu, déplacement du serpent | ✅ | Complet |
| **Nourriture** | Génération aléatoire, détection collision | ✅ | Complet |
| **Collision corps** | Détection de collision avec la queue | ✅ | Complet |
| **Écran Game Over** | Affichage score et option rejouer | ✅ | Complet |
| **Graphiques** | Image de fond, polices personnalisées | ✅ | Complet |
| **Tunnel (wrap)** | Passage à travers les murs | ✅ | Complet |
| **Architecture OOP** | Classes Game et Snake | ✅ | Complet |

### Tâches de développement complétées

- ✅ Configuration SFML pour macOS/Windows/Linux
- ✅ Makefile multi-plateforme
- ✅ Refactorisation du code monolithique vers architecture OOP
- ✅ Chargement des assets (images, polices)
- ✅ Gestion des événements clavier
- ✅ Boucle de jeu principale
- ✅ Détection des collisions
- ✅ Rendu graphique avec sprites
- ✅ Script de setup automatisé (setup.sh)
- ✅ Documentation complète (README.md)

### Tests effectués

- ✅ Compilation sur macOS
- ✅ Compilation sur macOS (arm64/M1/M2)
- ✅ Chargement des ressources (images, polices)
- ✅ Gameplay basique
- ✅ Collisions et game over
- ✅ Rejeu après game over
- ⚠️ Compilation sur Windows (à vérifier)
- ⚠️ Compilation sur Linux (bibliothèques manquantes)

## �👨‍💻 Auteur

Projet réalisé avec C++ et SFML.

---

**Amusez-vous bien en jouant ! 🎮🐍**
