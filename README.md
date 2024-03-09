# Project_Meteo
	Ce programme a pour but de retourner un graphique en fonction des options passées en paramètre
   
   	Syntaxe d'appel : ./bash Ififroi.sh [OPTIONS...] -f <fichier>
	Le -f <fichier> peut être placé n'importe où et aucun espace entre le -f et le <fichier> n'est requis.
   	
	Au minimum un argument obligatoire  (-t | -p | -w | -m | -h ) est requis pour le lancement du programme
	Un <nom_de_fichier> précéder d'un -f est requis pour le fonctionnement du programme.

   	OPTION GENERAL :
   	-t<mode>     
		t1 : produit un graphique triant les températures maximales, minimales et moyennes pour chaque stations
		t2 : produit un graphique triant les températures moyennes dans l'ordre chronologique
		t3 : produit un graphique triant les températures moyennes dans l'ordre chronologique pour chaque stations
	-p<mode>
		p1 : produit un graphique triant les pressions maximales, minimales et moyennes pour chaque stations
		p2 : produit un graphique triant les pressions moyennes dans l'ordre chronologique
		p3 : produit un graphique triant les pressions moyennes dans l'ordre chronologique pour chaque stations
	
	ATTENTION : Pour les arguments -t<mode> et -p<mode>, un seul mode peut être activé à la fois !

	-w : produit un graphique imageant les vecteurs de direction et de vitesse du vent pour chaque station
	-h : produit un graphique montrant l'altitude de chaque station (dans l'ordre décroissant)
	-m : produit un graphique montrant l'humidité maximale pour chaque station (dans l'ordre décroissant)

	OPTIONS DE LIEUX :
	Limite le rendu final à une certaine zone géographique.
	Ces options ne sont pas requise pour lancer le programme.
	Une seule restriction géographique peut être activé en même temps.

	-F : France métropolitaine + Corse
	-G : Guyane française
	-S : Saint-Pierre et Miquelon
	-A : Antilles
	-O : Océan indien
	-Q : Antarctique

	OPTIONS DE TRIS :
	Ces options permettent d'imposer une méthode de tri particulière.
	Ces options ne sont pas requise pour lancer le programme.
	Une seule option de tri peut être activé en même temps.
	
	-liste : impose un tri des données par une liste chainée
	-abr : impose un tri des données par une structure de type ABR
	-avl : impose un tri des données par une structure de type AVL

	AUTRES :

	-help : permet l'affichage de l'aide
------------------------------------------------------------------------------------------------------------------------------------------------------------
La compilation du programme c se fera automatiquement grâce au Makefile.
Si celui ne marche pas, merci de se reporter sur les fichiers du dossier 'old', utilisant une compilation classique avec gcc (toujours aucune action particulière requise)

