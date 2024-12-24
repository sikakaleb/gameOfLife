# Game of Life

Le **Jeu de la Vie** est une célèbre simulation basée sur des cellules vivantes ou mortes évoluant selon des règles simples, mais produisant des comportements complexes. Ce projet implémente le Jeu de la Vie en C avec une interface graphique grâce à **SDL2**.

## Fonctionnalités

1. **Chargement de la grille initiale**
   - La grille initiale est lue depuis un fichier texte (par exemple, `grid.txt`).
   - Format attendu :
      - Première ligne : largeur et hauteur (ex. `30 20`)
      - Les lignes suivantes contiennent les cellules : `0` (morte), `1` (vivante).

2. **Simulation des générations**
   - Les règles du Jeu de la Vie sont respectées :
      - Une cellule vivante avec 2 ou 3 voisins survit.
      - Une cellule vivante avec moins de 2 ou plus de 3 voisins meurt.
      - Une cellule morte avec exactement 3 voisins devient vivante.

3. **Gestion de l'historique**
   - Les états successifs de la grille sont sauvegardés dans une structure d'historique.
   - Navigation interactive :
      - **Flèche gauche** : revenir à la génération précédente.
      - **Flèche droite** : avancer à la génération suivante (si déjà calculée).

4. **Affichage graphique**
   - Utilisation de **SDL2** pour afficher la grille en temps réel.
   - Cellules vivantes : vertes
   - Cellules mortes : grises

5. **Mode automatique (auto-play)**
   - Appuyez sur `P` pour activer/désactiver la progression automatique des générations.
   - L'intervalle entre les générations est configurable (par défaut : 200 ms).

6. **Sauvegarde de l'état**
   - Les états peuvent être sauvegardés dans des fichiers (ex. `save_gen_0.txt`, `save_gen_1.txt`, etc.)

## Prérequis

### Dépendances

- **SDL2** (installée via [vcpkg](https://github.com/microsoft/vcpkg))
- **CMake** (version 3.15 ou supérieure)
- **Compilateur C** (MSVC, GCC ou équivalent)

### Installation des dépendances

1. **Installer vcpkg**
   ```bash
   git clone https://github.com/microsoft/vcpkg.git
   cd vcpkg
   ./bootstrap-vcpkg.sh # (Linux/macOS)
   .\bootstrap-vcpkg.bat # (Windows)
   ```

2. **Installer SDL2**
   ```bash
   ./vcpkg install sdl2
   ```

3. **Configurer CMake avec vcpkg**
   Ajoutez l'option suivante à vos commandes CMake :
   ```
   -DCMAKE_TOOLCHAIN_FILE=path/to/vcpkg/scripts/buildsystems/vcpkg.cmake
   ```

## Compilation et exécution

### Compilation

1. Clonez le projet :
   ```bash
   git clone https://github.com/sikakaleb/gameOfLife.git
   cd gameOfLife
   ```

2. Configurez le projet avec CMake :
   ```bash
   cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=path/to/vcpkg/scripts/buildsystems/vcpkg.cmake
   ```

3. Compilez le projet :
   ```bash
   cmake --build build
   ```

### Exécution

1. Placez un fichier `grid.txt` dans le répertoire racine (ou configurez le chemin dans `main.c`).
   - Exemple minimal :
     ```
     5 5
     0 1 0 0 0
     1 1 1 0 0
     0 1 0 0 0
     0 0 0 0 0
     0 0 0 0 0
     ```

2. Lancez l'exécutable :
   ```bash
   ./cmake-build-debug/gameOfLife
   ```

3. Profitez de la simulation et utilisez les commandes pour interagir :
   - **Flèches gauche/droite** : navigation dans l'historique
   - **Espace** : avancer d'une génération
   - **P** : activer/désactiver le mode automatique
   - **Échap** : quitter

## Structure du projet

```plaintext
.
├── src/
│   ├── board.c       # Gestion des grilles (création, sauvegarde, chargement)
│   ├── board.h
│   ├── rules.c       # Application des règles du Jeu de la Vie
│   ├── rules.h
│   ├── history.c     # Gestion de l'historique des grilles
│   ├── history.h
│   ├── graphics.c    # Affichage graphique avec SDL2
│   ├── graphics.h
├── main.c            # Point d'entrée du programme
├── resources/
│   └── grid.txt      # Fichier d'exemple pour la grille initiale
├── CMakeLists.txt    # Configuration de compilation
└── README.md         # Documentation
```

## Perspectives

Quelques pistes pour aller plus loin :

1. **Amélioration graphique**
   - Zoom/dézoom avec la souris ou des raccourcis clavier.
   - Afficher les cellules qui viennent de naître ou de mourir avec des couleurs différentes.

2. **Interactivité**
   - Ajout d'un clic souris pour activer/désactiver des cellules directement.

3. **Optimisations**
   - Gestion d'un plateau infini (ou très grand) avec des structures de données comme des hashtables.

4. **Utilisation de CUDA**
   - Accélérer les calculs du Jeu de la Vie en exploitant la parallélisation massive des GPU.
   - Chaque cellule pourrait être calculée comme un thread CUDA, permettant de gérer des grilles beaucoup plus grandes en temps réel.
   - Exemples d'application : simulation scientifique, optimisation des règles ou des patterns complexes.

## Auteur

Projet réalisé par **sikakaleb** .

---

Bon code et amusez-vous avec votre propre Jeu de la Vie ! 🎉
