Projet Son : La Harpe de Verre

Maiwenn Kermorgant et Abdelwedoud Taya, G1

Notre projet a pour but de rejouer une mélodie jouée au micro, mais avec le son d'une harpe de verre. Comme il nous restait du temps, nous avons aussi implémenté un autre mode, assez rudimentaire, qui permet de jouer de la harpe de verre en utilisant les touches "a" à "$" du clavier, chaque touche représentant une note de la gamme. Ces deux modes permettent de découvrir la harpe de verre, un instument méconnu, de façon amusante. 
Le code se compose d'un fichier arduino, NOMFICHIER, et d'une fonction C++ ainsi que de son fichier .h, glassHarp. Téléversez-les dans la Teensy. Enfin, pour utiliser le mode clavier, il faut exécuter le programme python HarpeDeVerre.py. Prendre garde à ne pas ouvrir la console COM5 avant le lancer le programme python, car celui-ci l'utilise pour communiquer avec le programme arduino. Il faut également disposer des bibliothèques python Serial et Pynput. 

Au niveau hardaware, le port micro de la teensy peut être connecté à deux types d'entrée différents : soit directement à l'ordinateur, avec un câble double mini-Jack, ou bien à un micro. Le premier possède l'avantage de ne pas subir de bruit de fond. Le deuxième, malgré nos efforts, détecte de temps en temps des bruits indésirables, mais est plus amusant car il permet de parler dans le micro ou bien de jouer d'un réel instrument devant.
Il faut également brancher des écouteurs sur la sortie audio de la Teensy afin de pouvoir écouter notre magnifique son de harpe de verre.
La plaque arduino dispose d'un potentiomètre, qui sert à régler le son en sortie, et d'un bouton, qui sert à passer d'un mode à l'autre.

Il ne reste plus qu'à choisir la mélodie que vous voulez transformer. Quelques précautions cependant : si vous utilisez le son de l'ordinateur, veillez à ce qu'il ne soit pas trop fort, sans quoi il sature. Si vous utilisez un son capturé au micro, essayez de vous mettre dans un endroit calme pour éviter de détecter un  bruit de fond. 