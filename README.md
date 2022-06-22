# LOG710 - Laboratoire 2

Ce projet contient le code source du laboratoire 2 du cours LOG710.

## Dépendances

Les dépendances externes suivantes sont nécessaire sur Ubuntu pour compiler et
utiliser ce projet:

  - build-essential
  - pkg-config
  - check

Ces derniers sont disponibles par défaut sur la machine virtuelle qui vous est
fournie ou sont installable par cette commande sur Ubuntu:

```
$ sudo apt install build-essential pkg-config check
```

## Construction

Afin de construire l'exécutable final dans le cadre de ce laboratoire, il ne
suffit que d'utiliser cette commande à la racine du code du laboratoire
(celui contenant le fichier *Makefile*):

```sh
$ make
```

## Exécution

L'exécutable généré s'appele `Log710Schedulers` et se trouve dans le dossier
racine du code du laboratoire.

En l'exécutant sans arguments, vous serez présenté avec un message expliquant
sont utilisation:

```
UTILISATION:

	./Log710Schedulers --file file [--scheduler fcfs|priority|hybrid] [--trace] [--help]

DESCRIPTION:

	Lance la simulation d'une stratégie d'ordonnancement.

OPTIONS:

	--file <file>
		Indique à la simulation quel fichier d'entrées de processus à utiliser

	--scheduler fcfs|priority|hybrid
		Indique à la simulation le type d'ordonnanceur à utiliser.
		La valeur par défaut est "fcfs".

	--trace
		Active le mode *trace*. À chaque *tick*, l'état de l'ordonnanceur sera imprimmé dans la sortie standard.

	--help
		Affiche ce message d'erreur.
```

## Tests

Le laboratoire comporte aussi des tests automatiser pour vous aider à
implémenter les fonctionnalités connexes demandées, tel les files de processus,
le calcul des statistiques, etc:

```
$ make check
```

Ces tests sont divisés en 3 suites de tests:

  - `queue` pour les tests reliés à la file de processus;
  - `resources` pour les tests reliés aux resources;
  - `statistics` pour les tests reliés aux statistiques.

Il est possible d'utiliser la variable d'environnement *CK_RUN_SUITE* afin de
choisir la suite de tests à exécuter:

```sh
CK_RUN_SUITE=resources make check
```

## Suggestions

Faîtes une recherche pour les `TODO:` dans le code.  Cela indique
les fonctions que vous avez à implémenter.

### 1. Fonctionnalités utilitaires

Afin d'être en mesure d'implémenter correctement les stratégies d'ordonnancement
demandées, nous vous conseillons fortement de commencer avec les
fonctionnalitées utilisataires dans ces fichiers:

  1. `src/queue.c`
  2. `src/resources.c`
  3. `src/statistics.c`

Ces fonctionnalités utilitaires peuvent être développé en parallèle.  Vous
pouvez valider leur fonctionnement à l'aide des tests automatisés fournis.

### 2. Prendre connaissance des entêtes

Les énumérations, structures de données, et fonctions des fichiers suivant vous
permettront d'implémenter les stratégies d'ordonnancement:

  - `src/queue.h`
  - `src/ressources.h`
  - `src/process.h`

#### Déterminer si un processus s'est arrêté

Afin de déterminer si un processus s'est arrêté, vous n'avez qu'à utiliser son
champ `status`:

```c
process->status == TERMINATED
```

### 3. Stratégies d'ordonnancement

Il vous est maintenant possible d'implémenter les stratégies d'ordonnancement
dans les fichiers suivant:

  1. `src/fcfs_scheduler.c`
  2. `src/priority_scheduler.c`
  3. `src/hybrid_scheduler.c`

Pour implémenter les algorithmes d'ordonnancement, rendez vous à l'aise avec
les champs de leurs structures de données.  Vous allez remarquer certains champs
répétés entres ces ordonnanceurs (pour bonnes raison) tel `resources` et
`current_process`.  D'autres champs sont uniques à la stratégie d'ordonnancement
tel l'agencement des files d'attente.  Voir les fichiers suivant respectivement
pour cette information:

  1. `src/fcfs_scheduler.h`
  2. `src/priority_scheduler.h`
  3. `src/hybrid_scheduler.h`

Pour vous assurez du bon fonctionnement des stratégies d'ordonnancement, vous
pouvez utiliser l'information de la sortie standard.  De l'information
additionnelle est aussi disponible à l'aide de l'option`--trace` en ligne de
 commande:
```sh
$ ./Log710Schedulers [...] --trace
```
