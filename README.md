# CPanorama
[FR] Fusionne des photos en créant un panorama

## Documentation

Utilisez Doxygen pour générer la documentation.

## Get Started:
```
$make
```
Lancer le programme

Vous pouvez voir la liste des options à l'aide de la commande :
```
$./bin/panorama –help ou $./bin/panorama -?
```
Pour tester le programme nous avons mis plusieurs images dans le dossier src/images/
```
$./bin/panorama -i src/images/image.ppm -g -o test.pgm
```
Si vous ne précisez pas de fichier en output, le programme le génèrera directement dans le dossier courrant :
```
$./bin/panorama -r src/images/ -g
```
Les options seront exécutées successivement respectivement à l'ordre donnée dans la liste d'input. Par exemple :
```
$./bin/panorama -li src/images/image.ppm src/images/image.pgm -g -d
```
Cette commande exécute l'option -g sur le premier input et -d sur le second. 
