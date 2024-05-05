Projet réalisé par : MOHAMMED-AYMAN ZROUDI/ZAKARIA LAALYEJ/ AYMAN EL GARNAOUI GROUPE 2
Le code ci-dessus est un programme de gestion de bibliothèque écrit en langage C. Il permet d'effectuer diverses opérations sur une collection de livres, notamment l'ajout, la modification, la suppression, l'affichage, la recherche, le tri et la sauvegarde dans un fichier CSV. Voici une description détaillée des fonctions implémentées dans ce programme :

Structures et Définitions
Structure Livre :
Définit les attributs d'un livre, tels que l'identifiant (id), l'auteur (auteur), le titre (titre), la description (description), le nom de l'utilisateur (Nom_U), le prix (prix), la catégorie (categorie), et la disponibilité (disponibilite).
Fonctions Principales
chargerLivresCSV :
Description : Charge les livres à partir d'un fichier CSV spécifié.
Paramètres :
Livre **t : Pointeur vers le tableau de livres.
int *n : Pointeur vers le nombre de livres.
const char *nomFichier : Nom du fichier CSV à charger.
Fonctionnement : Lit chaque ligne du fichier CSV (après la première ligne d'en-têtes), parse les données en utilisant sscanf pour remplir les structures Livre, et agrandit dynamiquement le tableau t à mesure que les livres sont ajoutés.
sauvegarderLivresCSV :
Description : Sauvegarde les livres actuellement en mémoire dans un fichier CSV.
Paramètres :
Livre *t : Tableau de livres.
int n : Nombre de livres dans le tableau.
const char *nomFichier : Nom du fichier CSV de destination.
Fonctionnement : Ouvre un fichier en mode écriture, écrit les en-têtes CSV et ensuite itère sur le tableau t pour écrire chaque livre dans le fichier CSV.
ajout :
Description : Permet d'ajouter un nouveau livre à la collection.
Paramètres :
Livre **t : Pointeur vers le tableau de livres.
int *n : Pointeur vers le nombre de livres.
Fonctionnement : Utilise realloc pour agrandir le tableau t, puis demande à l'utilisateur de saisir les détails du nouveau livre et les ajoute au tableau.
modifier :
Description : Permet de modifier les détails d'un livre existant en fonction de son identifiant.
Paramètres :
Livre *t : Tableau de livres.
int n : Nombre de livres dans le tableau.
Fonctionnement : Demande à l'utilisateur l'identifiant du livre à modifier, puis permet de modifier ses attributs sélectionnés.
supprimer :
Description : Permet de supprimer un livre de la collection en fonction de son identifiant.
Paramètres :
Livre *t : Tableau de livres.
int *n : Pointeur vers le nombre de livres.
Fonctionnement : Demande à l'utilisateur l'identifiant du livre à supprimer, puis effectue le décalage des éléments pour supprimer le livre du tableau.
affichage :
Description : Affiche la liste complète des livres avec leurs détails.
Paramètres :
Livre *t : Tableau de livres.
int n : Nombre de livres dans le tableau.
Fonctionnement : Parcourt le tableau t et affiche chaque livre avec ses détails.
recherche :
Description : Permet de rechercher un livre par titre ou par nom d'auteur.
Paramètres :
Livre *t : Tableau de livres.
int n : Nombre de livres dans le tableau.
Fonctionnement : Demande à l'utilisateur un terme de recherche, puis affiche tous les livres correspondants trouvés dans le tableau.
trier :
Description : Trie les livres en fonction d'un critère spécifié.
Paramètres :
Livre *t : Tableau de livres.
int n : Nombre de livres dans le tableau.
int critere : Critère de tri (par ID, auteur, titre, description, nom utilisateur, catégorie, prix, disponibilité).
Fonctionnement : Utilise un algorithme de tri (bubble sort) pour réorganiser les livres en fonction du critère sélectionné.
Fonction Principale (main)
Description : L'interface utilisateur principale qui utilise les fonctions définies ci-dessus pour permettre à l'utilisateur de gérer les livres de la bibliothèque.
Fonctionnement : Affiche un menu interactif où l'utilisateur peut choisir parmi différentes actions (ajouter, modifier, supprimer, afficher, rechercher, trier, sauvegarder et quitter) en fonction de ses besoins. Les choix de l'utilisateur déclenchent les fonctions appropriées pour effectuer les opérations sur le tableau de livres en mémoire.
Conclusion
Ce programme fournit une base complète pour gérer une collection de livres dans une bibliothèque en utilisant des opérations de base telles que l'ajout, la modification, la suppression, l'affichage, la recherche, le tri et la sauvegarde des données. Les fonctions sont organisées de manière modulaire pour faciliter la maintenance et l'extension du programme.
