# LOG710-01 Laboratoire 2

Ce projet contient le code source pour compléter le laboratoire 2 du cours de
LOG710.

Dans ce laboratoire, vous aller expérimenter avec différentes stratégies
d'ordonnancement dans le langage de programmation C.  L'environnement
d'exécution est simulé afin de permettre une exécution rapide.  Cette exécution
rapide vous permettra une vitesse d'itération rapide.

## Instructions de compilation

Installer les dépendances suivantes:
```sh
sudo apt install build-essential pkg-config check
```

Pour compiler le tout et obtenir les exécutables, faire:
```sh
make
```

## Test des fonctionnalités auxiliaires

Afin de tester les fonctionnalités auxiliaires, ce gabarit vous offre des tests
unitaires afin de ne rencontrer de problèmes lors de l'implémentation de vos
stratégies d'ordonnancement.  Pour exécuter ces tests, ils vous suffit de faire:

```sh
make check
```

Les tests de fonctionnalités auxilaires sont divisés en 3 suites de tests:

  - `queue` pour les tests de file de processus;
  - `resources` pour les tests de ressources;
  - `statistics` pour les tests de statistiques.

Il est possible d'exécuter une suite de tests uniquement en mettant le nom de la
suite dans la variable d'environnement *CK_RUN_SUITE*:

```sh
CK_RUN_SUITE=resources make check
```
