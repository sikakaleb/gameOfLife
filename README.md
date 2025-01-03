# Game of Life

Le **Jeu de la Vie** est une célèbre simulation basée sur des cellules vivantes ou mortes évoluant selon des règles simples, mais produisant des comportements complexes. Ce projet implémente le Jeu de la Vie en C avec une interface graphique grâce à **SDL2**.

## Fonctionnalités principales

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

4. **Affichage graphique (SDL2)**
    - Utilisation de **SDL2** pour afficher la grille en temps réel.
    - Cellules vivantes : vertes
    - Cellules mortes : grises

5. **Mode automatique (auto-play)**
    - Appuyez sur `P` pour activer/désactiver la progression automatique des générations.
    - L'intervalle entre les générations est configurable (par défaut : 200 ms).

6. **Sauvegarde de l'état**
    - Les états peuvent être sauvegardés dans des fichiers (ex. `save_gen_0.txt`, `save_gen_1.txt`, etc.)

---

## Prérequis et installation

### 1. Installer Visual Studio (ou le kit de compilation C++)

Assurez-vous d’avoir installé Visual Studio **avec** la charge de travail **Desktop development with C++**.
- Si vous préférez la ligne de commande, vous pouvez simplement installer le **Build Tools for Visual Studio** (ou MinGW/GCC si vous souhaitez compiler avec MinGW).
- Mais pour ce projet, l’exemple se fait principalement avec **Visual Studio** et **MSVC**.

### 2. Installer et configurer vcpkg

**vcpkg** est un gestionnaire de paquets multiplateforme pour C++ fourni par Microsoft.

1. **Cloner le dépôt vcpkg**
   ```bash
   git clone https://github.com/microsoft/vcpkg.git
   cd vcpkg
   ```
2. **Compiler/Initialiser vcpkg**
    - Sous Windows :
      ```cmd
      .\bootstrap-vcpkg.bat
      ```
    - Sous Linux/macOS :
      ```bash
      ./bootstrap-vcpkg.sh
      ```

3. **(Optionnel) Intégration globale**  
   Pour faciliter l’utilisation de vcpkg dans tous vos projets, exécutez :
   ```cmd
   vcpkg integrate install
   ```
   Ceci permet à CMake et Visual Studio de détecter automatiquement les paquets installés.

### 3. Installer SDL2 via vcpkg

Toujours dans le répertoire de `vcpkg` :
```cmd
vcpkg install sdl2
```
> Assurez-vous de bien installer la version adaptée à la plateforme (par défaut, `x64-windows` si vous utilisez Visual Studio en 64 bits).

### 4. Cloner ce projet et placer vcpkg

Récupérez le dépôt du Jeu de la Vie :
```bash
git clone https://github.com/sikakaleb/gameOfLife.git
cd gameOfLife
```

Votre arborescence de projet pourrait ressembler à ceci si vous placez `vcpkg` dans le même dossier, ou bien vous pouvez l’installer ailleurs (l’important est juste de connaître son chemin) :
```
gameOfLife/
 ├── vcpkg/                   # (optionnel, si vous avez cloné/placé vcpkg ici)
 ├── src/
 ├── include/
 ├── CMakeLists.txt
 └── ...
```

### 5. Compilation (exemples Windows / Visual Studio / CMake)

#### Méthode A : Utilisation de Visual Studio (interface graphique)

1. Ouvrez Visual Studio.
2. Allez dans **File** > **Open** > **CMake…** (ou **Folder** si vous utilisez l’intégration CMake) et sélectionnez le dossier `gameOfLife`.
3. Assurez-vous que Visual Studio détecte bien la **Toolchain** vcpkg (via `vcpkg integrate install`) et la configuration x64.
4. Lancez la génération et la compilation depuis l’interface de Visual Studio (menu **CMake** ou **Build**).

#### Méthode B : Ligne de commande avec CMake et MSVC

1. **Nettoyer le dossier** (au besoin)  
   Si vous avez déjà essayé une autre génération (par exemple MinGW), supprimez le dossier `build` pour repartir de zéro :
   ```cmd
   rmdir /S /Q build
   ```

2. **Générer les fichiers de projet**  
   Dans le dossier `gameOfLife`, exécutez (en adaptant le chemin vers vcpkg) :
   ```cmd
   cmake -S . -B build -G "Visual Studio 17 2022" -A x64 ^
     -DCMAKE_TOOLCHAIN_FILE=C:\Chemin\Vers\vcpkg\scripts\buildsystems\vcpkg.cmake
   ```
   > Note : Le `^` sous Windows permet de passer à la ligne. Sinon, vous pouvez tout mettre sur une même ligne.

3. **Compiler**
   ```cmd
   cmake --build build --config Debug
   ```
   > Vous pouvez remplacer `Debug` par `Release` selon vos besoins.

4. **Exécuter le programme**
   ```cmd
   build\Debug\gameOfLife.exe
   ```
   ou
   ```cmd
   build\Release\gameOfLife.exe
   ```
   selon la configuration choisie.

#### Méthode C : Ligne de commande avec MinGW (optionnel)

Si vous préférez MinGW :
1. Installez MinGW et ajoutez-le à votre PATH pour avoir accès à `gcc`/`g++`.
2. Installez SDL2 via vcpkg pour la triplet `x64-mingw-dynamic` (par exemple).
3. Assurez-vous de supprimer le dossier `build` si vous aviez déjà généré avec Visual Studio.
4. Exécutez :
   ```cmd
   cmake -S . -B build -G "MinGW Makefiles" ^
     -DCMAKE_TOOLCHAIN_FILE=C:\Chemin\Vers\vcpkg\scripts\buildsystems\vcpkg.cmake
   cmake --build build
   ```
5. Lancez l’exécutable qui se trouvera dans `build/` (Debug ou Release).

---

## Utilisation du programme

1. **Fichier `grid.txt`**  
   Placez un fichier `grid.txt` dans le répertoire racine (ou modifiez le chemin dans `main.c`).
    - Exemple minimal :
      ```
      5 5
      0 1 0 0 0
      1 1 1 0 0
      0 1 0 0 0
      0 0 0 0 0
      0 0 0 0 0
      ```
   Assurez-vous que `gameOfLife.exe` puisse le trouver (ex. dans le même dossier).

2. **Lancement**
    - En ligne de commande :
      ```cmd
      build\Debug\gameOfLife.exe
      ```  
      ou
      ```cmd
      build\Release\gameOfLife.exe
      ```  
    - Depuis Visual Studio :  
      Utilisez **Debug** > **Start without debugging** (ou F5 pour le mode debug).

3. **Contrôles du jeu**
    - **Flèche gauche / Flèche droite** : parcourir l’historique des générations.
    - **Espace** : avancer d’une génération manuellement.
    - **P** : activer/désactiver la progression automatique (auto-play).
    - **Échap** : quitter.

---

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
├── include/
│   └── ...           # (fichiers .h éventuels supplémentaires)
├── main.c            # Point d'entrée du programme
├── resources/
│   └── grid.txt      # Fichier d'exemple pour la grille initiale
├── CMakeLists.txt    # Configuration de compilation
├── vcpkg/            # (optionnel si vous placez vcpkg ici, sinon ailleurs)
└── README.md         # Documentation
```

---

## Perspectives d’amélioration

1. **Amélioration graphique**
    - Zoom/dézoom avec la souris ou des raccourcis clavier.
    - Afficher les cellules qui viennent de naître ou de mourir avec des couleurs différentes.

2. **Interactivité**
    - Ajout d’un clic souris pour activer/désactiver des cellules directement.

3. **Optimisations**
    - Gestion d’un plateau infini (ou très grand) avec des structures de données appropriées (par ex. des hashtables).

4. **Utilisation de CUDA**
    - Accélérer les calculs du Jeu de la Vie en exploitant la parallélisation massive des GPU (chaque cellule comme un thread CUDA).

---

## Auteur

Projet réalisé par **sikakaleb**.  
Bon code et amusez-vous avec votre propre Jeu de la Vie ! 🎉