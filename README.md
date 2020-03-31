# todolist

Le code est divisé en un fichier cpp pour le main puis en .h pour les différentes classes et fonctions.

Il y a 2 classes principales :
	- une classe Task qui représente l'objet Tache, il a pour attribut :
		- nom
		- description, 
		- date de fin et de création, la date de création se met immédiatement lors de la création) grâce à une fonction présente dans "temps.h"
		- un statut (ouverte ou fermée)
		- un avancement en %
		- une priorité (normale ou prioritaire)

	On peut appliquer à l'objet différentes méthodes pour le modifier, ajouter des attributs et le sauvegarder. Cependant ces méthodes sont invisbles à l'utilisateur. Toutes les intéractions se font par une interface dans le terminal.

	- une classe Editor qui represente la liste des tâches, cet éditeur permet l'affichage des menus, de la liste, et fait appel au module de sauvegarde.


Un fichier "save.h" gère les sauvegardes par des lectures/écritures de fichiers .txt grâce à une syntaxe définie au préalable.


	Pour l'utilisateur, il faudra uniquement lancer l'éditeur grâce à l'executable. Tout se fait ensuite par navigation dans le terminal à l'aide de menu et de lectures d'entrées au clavier. L'objectif était que l'utilisateur n'ait pas à entrer de fonctions ou de lignes de commande. Le programme est donc peut-être moins rapide pour un utilisateur qui serait habitué mais plus "user-friendly" même si assez rustique on l'admettra.




Installation :

	Ouvrir un terminal et se placer dans le dossier ou se trouvent les codes

	compiler les codes avec la commande
		g++ main.cpp temps.h save.h task.h editor.h -o todolist.out

	taper ensuite : 
		./todolist.out 




Exemple d'utilisation :

	1) créer un fichier de sauvegarde (il se trouvera dans le même dossier que les codes et l'executable)

	2) ajouter une tâche avec nom, description, ... et y ajouter des sous-tâches

	3) maintenant que la tâche est crée en créer une autre ou afficher la liste des tâches à faire

	4) en cas de besoin il est possible de modifier la tâche

	5) ne pas oublier de sauvegarder, il n'y a pas de sauvegarde automatique et en cas d'erreur il sera impossible de récuperer les données non sauvées.

	6) lorsqu'une tâche est terminée aller dans l'onglet "valider une tâche" puis valider la tâche correspondante

	7) quitter le programme puis le relancer en récupérant la liste de tâches crée au lancement précédent





Remarque : 

	En cas de problème faire CTRL+C pour arrêter l'éxecution.


Améliorations envisageables :

	- dans le menu d'affichage des tâches : ajout d'une fonction de filtrage/tri par priorité/date de fin

	- affichage jour par jour des tâches
	
	- suppression des tâches une fois terminées

	- ajout de sous-tâches après création dans le menu modifier

	- menus plus intéractifs et interface moins sommaire

	- pour la gestion des sauvegardes, quand l'utilisateur veut ouvrir un fichier, afficher la liste des fichiers disponibles (comme un "ls" dans le terminal).


