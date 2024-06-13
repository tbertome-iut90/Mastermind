# Mastermind

## But du jeu

Trouver la combinaison secrète en un maximum de 12 tentatives.

## Déroulé du jeu

A chaque tentative, le joueur doit entrer ce qu'il pense être la combinaison grâce au clavier présent en bas de la fenêtre. Il peut retourner en arrière s'il souhaite changer sa proposition avant de la confirmer.

A chaque fois qu'une tentative est confirmée, le jeu indique combien d'éléments sont bons et biens placés (nombre dans la case blanche) et combien d'éléments sont bons mais mal placés (nombre dans la case rouge) à côté de la tentative, ce qui permet au joueur de déduire quels éléments sont présents dans le code et quelles sont leur position.

## Fin du jeu

Si le joueur parvient à trouver la combinaison secrète dans les 12 tentatives auxquelles il a droit, il gagne.

Si le joueur ne parvient pas à trouver la combinaison secrète au bout de 12 tentatives, il perd.

## Installation de l'application

Installation de qtbase5-dev : 
```
sudo apt-get install -y qtbase5-dev
```

Installation de qt5-qmake :
```
sudo apt install qt5-qmake
```

Création des instructions de compilation :
```
qmake
```

Compilation de l'application :
```
make
```

Exécution de l'application : 
```
./Mastermind
```

## Difficultés rencontrées

J'ai choisi un projet trop ambitieux au départ, ce qui ne m'a pas laissé beaucoup de temps pour créer celui-ci.

La structure de ce projet n'est donc pas très propre, mais elle est fonctionnelle.

## Ce qui serait possible d'améliorer

* Graphismes
* Sauvegarde des parties pour établir un classement / des stats
* Saisie de la combinaison : 
- afficher la saisie du joueur directement dans la ligne actuelle plutôt que dans une ligne temporaire
- pouvoir modifier n'importe quel élément librement au lieu de devoir supprimer de la fin à l'élément à changer
* Customisation des paramètres de la partie (nombre de tenatives, longueur des codes, nombre de couleurs utilisables)# Mastermind
# Mastermind
# Mastermind
# Mastermind
