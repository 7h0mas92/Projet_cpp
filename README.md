# 🐍 Snake Game - SFML Edition

Un jeu Snake classique développé en C++ avec la bibliothèque SFML 3.0.

## 🎮 Démarrage rapide

### Sur macOS
```bash
brew install sfml
git clone https://github.com/7h0mas92/Projet_cpp.git
cd Projet_cpp
make re
./jeu
```

### Sur Windows
Téléchargez SFML 3.0.2 depuis [sfml-dev.org](https://www.sfml-dev.org/download/sfml/3.0.2/) et adaptez les chemins dans le Makefile.

### Sur Linux
```bash
sudo apt-get install libsfml-dev
git clone https://github.com/7h0mas92/Projet_cpp.git
cd Projet_cpp
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

✅ Menu de démarrage avec instructions  
✅ Gameplay fluide en temps réel  
✅ Image de fond personnalisée  
✅ Affichage du score (taille du serpent)  
✅ Écran Game Over avec option de rejouer  
✅ Détection de collision avec le corps  
✅ Effet tunnel (wrap-around aux murs)  
✅ Police personnalisée Arial  

## 📁 Structure du projet

```
.
├── src/
│   ├── main.cpp          # Code principal du jeu
│   └── caracter.cpp      # Fichier auxiliaire
├── assets/
│   ├── background.png    # Image de fond du jeu
│   └── arial/
│       └── arial.ttf     # Police Arial Unicode
├── Makefile              # Configuration de compilation
├── .gitignore            # Fichiers à ignorer
└── README.md             # Ce fichier
```

## 🛠️ Compilation et Nettoyage

```bash
make          # Compilation simple
make re       # Recompilation complète
make clean    # Supprime les fichiers .o
make fclean   # Supprime les fichiers .o et l'exécutable
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
brew install sfml --with-arm64
```

## 📖 À propos du Makefile

Le Makefile gère la compilation avec :
- Chemins vers les bibliothèques SFML statiques (macOS)
- Flags de compilation C++17
- Règles de nettoyage automatique

Voir `Makefile` pour plus de détails.

## 👨‍💻 Auteur

Projet réalisé avec C++ et SFML.

Les bibliothèques statiques SFML pour Windows sont déjà incluses dans le projet dans le dossier `lib/Windows/`. Si vous devez les obtenir ou les mettre à jour:

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
   mkdir -p /chemin/vers/sample-sfml-project/lib/Windows
   cp build-static/lib/*.a /chemin/vers/sample-sfml-project/lib/Windows/
   ```

5. **Vérifier que les bibliothèques sont présentes**:
   ```bash
   ls lib/Windows/
   # Devrait afficher: libsfml-*.a et les dépendances
   ```

### Obtenir les Bibliothèques SFML pour macOS

Les bibliothèques macOS sont déjà dans `lib/macOS/`. Elles ont été compilées avec:
```bash
cmake -S . -B build-static -G Ninja \
      -DCMAKE_BUILD_TYPE=Release \
      -DBUILD_SHARED_LIBS=OFF \
      -DSFML_BUILD_EXAMPLES=OFF \
      -DSFML_BUILD_TEST_SUITE=OFF
cmake --build build-static
```

Si vous devez les recompiler, suivez les mêmes étapes que pour Windows en adaptant les chemins.

## Comprendre le Processus de Compilation

1. Lorsque vous exécutez `make`, la règle `all` est appelée
2. `all` dépend de `$(NAME)` (l'exécutable final)
3. Pour créer `$(NAME)`, make vérifie si tous les fichiers objets `$(OBJ)` existent
4. Pour chaque fichier `.cpp` qui n'a pas de fichier `.o` correspondant ou qui a été modifié, la règle `%.o: %.cpp` est appliquée
5. Une fois tous les fichiers objets créés, ils sont liés ensemble pour former l'exécutable final

