
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char auteur[50];
    char titre[50];
    char description[200];
    char Nom_U[50];
    float prix;
    char categorie[50];
    char disponibilite[50];
} Livre;
void sauvegarderLivresCSV(Livre *t, int n, const char *nomFichier) {
    FILE *fichier = fopen(nomFichier, "w");

    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    fprintf(fichier, "ID,Auteur,Titre,Description,Nom Utilisateur,Categorie,Prix,Disponibilite\n");

    for (int i = 0; i < n; i++) {
        Livre *current = t + i;

        fprintf(fichier, "%d,%s,%s,%s,%s,%s,%.2f,%s\n",
                current->id, current->auteur, current->titre, current->description,
                current->Nom_U, current->categorie, current->prix, current->disponibilite);
    }

    fclose(fichier);
    printf("Données sauvegardées dans %s avec succès.\n", nomFichier);
}

void chargerLivresCSV(Livre **t, int *n, const char *nomFichier) {
    FILE *fichier = fopen(nomFichier, "r");

    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    // Ignorer la première ligne (en-têtes)
    char ligne[500];
    fgets(ligne, sizeof(ligne), fichier);

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        Livre nouveauLivre;
        sscanf(ligne, "%d,%49[^,],%49[^,],%199[^,],%49[^,],%49[^,],%f,%49[^\n]",
               &nouveauLivre.id, nouveauLivre.auteur, nouveauLivre.titre,
               nouveauLivre.description, nouveauLivre.Nom_U,
               nouveauLivre.categorie, &nouveauLivre.prix, nouveauLivre.disponibilite);

        *t = (Livre *)realloc(*t, (*n + 1) * sizeof(Livre));
        if (*t == NULL) {
            printf("Erreur d'allocation mémoire.\n");
            fclose(fichier);
            return;
        }

        (*t)[*n] = nouveauLivre;
        (*n)++;
    }

    fclose(fichier);
    printf("Données chargées depuis %s avec succès.\n", nomFichier);
}

int counter = 1;

void ajout(Livre **t, int *n) {
    int continuer = 1; // Variable pour contrôler la boucle d'ajout de livres

    do {
        *t = (Livre*)realloc(*t, (*n + 1) * sizeof(Livre));
        if (*t == NULL) {
            printf("Erreur d'allocation mémoire.\n");
            return;
        }

        Livre *nouveauLivre = *t + *n; // Pointe vers le nouveau livre à ajouter

        nouveauLivre->id = counter;
        counter++;

        printf("Entrer le nom de l'auteur : ");
        fgets(nouveauLivre->auteur, sizeof(nouveauLivre->auteur), stdin);
        nouveauLivre->auteur[strcspn(nouveauLivre->auteur, "\n")] = '\0'; // Supprimer le newline

        printf("Entrer le titre : ");
        fgets(nouveauLivre->titre, sizeof(nouveauLivre->titre), stdin);
        nouveauLivre->titre[strcspn(nouveauLivre->titre, "\n")] = '\0'; // Supprimer le newline

        printf("Entrer la description : ");
        fgets(nouveauLivre->description, sizeof(nouveauLivre->description), stdin);
        nouveauLivre->description[strcspn(nouveauLivre->description, "\n")] = '\0'; // Supprimer le newline

        printf("Entrer le nom de l'utilisateur : ");
        fgets(nouveauLivre->Nom_U, sizeof(nouveauLivre->Nom_U), stdin);
        nouveauLivre->Nom_U[strcspn(nouveauLivre->Nom_U, "\n")] = '\0'; // Supprimer le newline

        printf("Entrer la categorie : ");
        fgets(nouveauLivre->categorie, sizeof(nouveauLivre->categorie), stdin);
        nouveauLivre->categorie[strcspn(nouveauLivre->categorie, "\n")] = '\0'; // Supprimer le newline

        printf("Entrer le prix : ");
        scanf("%f", &nouveauLivre->prix);
        getchar(); // Pour absorber le newline restant après le scanf

        printf("Entrer la disponibilité : ");
        fgets(nouveauLivre->disponibilite, sizeof(nouveauLivre->disponibilite), stdin);
        nouveauLivre->disponibilite[strcspn(nouveauLivre->disponibilite, "\n")] = '\0'; // Supprimer le newline

        (*n)++; // Augmente le nombre de livres dans le tableau

        printf("Livre ajouté avec succès !\n");

        // Demander à l'utilisateur s'il veut ajouter un autre livre
        printf("Voulez-vous ajouter un autre livre ? (oui/non) : ");
        char reponse[5];
        fgets(reponse, sizeof(reponse), stdin);
        reponse[strcspn(reponse, "\n")] = '\0'; // Supprimer le newline

        if (strcmp(reponse, "oui") == 0 || strcmp(reponse, "o") == 0) {
            continuer = 1; // Continuer à ajouter des livres
        } else {
            continuer = 0; // Arrêter d'ajouter des livres
        }

    } while (continuer);
}

void affichage(Livre *t, int n) {
    printf("\nListe des livres :\n");
    printf("-----------------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        Livre *current = t + i; // Pointeur vers le livre actuel

        printf("Livre %d :\n", current->id);
        printf("-----------------------------------------------------------------------------------------------------------------------\n");
        printf("Titre         : %s\n", current->titre);
        printf("Auteur        : %s\n", current->auteur);
        printf("Description   : %s\n", current->description);
        printf("Utilisateur   : %s\n", current->Nom_U);
        printf("Catégorie     : %s\n", current->categorie);
        printf("Prix          : %.2f\n", current->prix);
        printf("Disponibilité : %s\n", current->disponibilite);
        printf("-----------------------------------------------------------------------------------------------------------------------\n");
    }
}

void modifier(Livre *t, int n) {
    int id;
    printf("Entrer l'id du livre que vous souhaitez modifier : ");
    scanf("%d", &id);
    getchar(); // Absorber le newline restant dans le buffer

    for (int i = 0; i < n; i++) {
        if ((t + i)->id == id) {
            printf("Entrer le nouveau nom de l'auteur : ");
            fgets((t + i)->auteur, sizeof((t + i)->auteur), stdin);
            (t + i)->auteur[strcspn((t + i)->auteur, "\n")] = '\0'; // Supprimer le newline

            printf("Entrer le nouveau titre : ");
            fgets((t + i)->titre, sizeof((t + i)->titre), stdin);
            (t + i)->titre[strcspn((t + i)->titre, "\n")] = '\0'; // Supprimer le newline

            printf("Entrer la nouvelle description : ");
            fgets((t + i)->description, sizeof((t + i)->description), stdin);
            (t + i)->description[strcspn((t + i)->description, "\n")] = '\0'; // Supprimer le newline

            printf("Entrer le nouveau nom de l'utilisateur : ");
            fgets((t + i)->Nom_U, sizeof((t + i)->Nom_U), stdin);
            (t + i)->Nom_U[strcspn((t + i)->Nom_U, "\n")] = '\0'; // Supprimer le newline

            printf("Entrer la nouvelle categorie : ");
            fgets((t + i)->categorie, sizeof((t + i)->categorie), stdin);
            (t + i)->categorie[strcspn((t + i)->categorie, "\n")] = '\0'; // Supprimer le newline

            printf("Entrer le nouveau prix : ");
            scanf("%f", &(t + i)->prix);
            getchar(); // Absorber le newline restant après le scanf

            printf("Entrer la nouvelle disponibilité : ");
            fgets((t + i)->disponibilite, sizeof((t + i)->disponibilite), stdin);
            (t + i)->disponibilite[strcspn((t + i)->disponibilite, "\n")] = '\0'; // Supprimer le newline

            printf("Le livre a été modifié avec succès !\n");
            return; // Sortir de la fonction après la modification
        }
    }

    printf("L'id du livre n'a pas été trouvé.\n");
}

void supprimer(Livre *t, int *n) {
    int id, indice = -1;
    printf("Entrer l'id du livre à supprimer : ");
    scanf("%d", &id);

    for (int i = 0; i < *n; i++) {
        if ((t + i)->id == id) {
            indice = i;
            break;
        }
    }

    if (indice != -1) {
        // Décalage des éléments pour supprimer le livre
        for (int i = indice; i < *n - 1; i++) {
            *(t + i) = *(t + i + 1);
        }
        *n = *n - 1; // Diminue le nombre de livres
        t = (Livre*)realloc(t, *n * sizeof(Livre)); // Réalloue la mémoire
        printf("-----------------------Le livre a été supprimé avec succès ----------------------!\n");
        printf("\n");
        printf("\n");
        printf("\n");
    } else {
        printf("L'id du livre n'a pas été trouvé.\n");
    }
}

void recherche(Livre *t, int n) {
    char recherche[50];
    int trouve = 0;

    printf("Entrer le titre ou le nom de l'auteur du livre à rechercher : ");
    fgets(recherche, sizeof(recherche), stdin);
    recherche[strcspn(recherche, "\n")] = '\0'; // Supprimer le newline

    printf("\nRésultats de la recherche :\n");
    printf("-----------------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        if (strstr((t + i)->titre, recherche) != NULL || strstr((t + i)->auteur, recherche) != NULL) {
            printf("Livre %d :\n", (t + i)->id);
            printf("-----------------------------------------------------------------------------------------------------------------------\n");
            printf("Titre         : %s\n", (t + i)->titre);
            printf("Auteur        : %s\n", (t + i)->auteur);
            printf("Description   : %s\n", (t + i)->description);
            printf("Utilisateur   : %s\n", (t + i)->Nom_U);
            printf("Catégorie     : %s\n", (t + i)->categorie);
            printf("Prix          : %.2f\n", (t + i)->prix);
            printf("Disponibilité : %s\n", (t + i)->disponibilite);
            printf("-----------------------------------------------------------------------------------------------------------------------\n");
            trouve = 1;
        }
    }

    if (!trouve) {
        printf("Aucun livre correspondant trouvé.\n");
    }
}

void trier(Livre *t, int n, int critere) {
    Livre temp;
    switch (critere) {
        case 1: // Tri par ID
            for (int i = 0; i < n - 1; i++) {
                for (int j = 0; j < n - i - 1; j++) {
                    if ((t + j)->id > (t + j + 1)->id) {
                        temp = *(t + j);
                        *(t + j) = *(t + j + 1);
                        *(t + j + 1) = temp;
                    }
                }
            }
            printf("Livres triés par ID.\n");
            break;
        case 2: // Tri par Auteur
            for (int i = 0; i < n - 1; i++) {
                for (int j = 0; j < n - i - 1; j++) {
                    if (strcmp((t + j)->auteur, (t + j + 1)->auteur) > 0) {
                        temp = *(t + j);
                        *(t + j) = *(t + j + 1);
                        *(t + j + 1) = temp;
                    }
                }
            }
            printf("Livres triés par Auteur.\n");
            break;
        case 3: // Tri par Titre
            for (int i = 0; i < n - 1; i++) {
                for (int j = 0; j < n - i - 1; j++) {
                    if (strcmp((t + j)->titre, (t + j + 1)->titre) > 0) {
                        temp = *(t + j);
                        *(t + j) = *(t + j + 1);
                        *(t + j + 1) = temp;
                    }
                }
            }
            printf("Livres triés par Titre.\n");
            break;
        case 4: // Tri par Description
            for (int i = 0; i < n - 1; i++) {
                for (int j = 0; j < n - i - 1; j++) {
                    if (strcmp((t + j)->description, (t + j + 1)->description) > 0) {
                        temp = *(t + j);
                        *(t + j) = *(t + j + 1);
                        *(t + j + 1) = temp;
                    }
                }
            }
            printf("Livres triés par Description.\n");
            break;
        case 5: // Tri par Nom Utilisateur
            for (int i = 0; i < n - 1; i++) {
                for (int j = 0; j < n - i - 1; j++) {
                    if (strcmp((t + j)->Nom_U, (t + j + 1)->Nom_U) > 0) {
                        temp = *(t + j);
                        *(t + j) = *(t + j + 1);
                        *(t + j + 1) = temp;
                    }
                }
            }
            printf("Livres triés par Nom Utilisateur.\n");
            break;
        case 6: // Tri par Catégorie
            for (int i = 0; i < n - 1; i++) {
                for (int j = 0; j < n - i - 1; j++) {
                    if (strcmp((t + j)->categorie, (t + j + 1)->categorie) > 0) {
                        temp = *(t + j);
                        *(t + j) = *(t + j + 1);
                        *(t + j + 1) = temp;
                    }
                }
            }
            printf("Livres triés par Catégorie.\n");
            break;
        case 7: // Tri par Prix
            for (int i = 0; i < n - 1; i++) {
                for (int j = 0; j < n - i - 1; j++) {
                    if ((t + j)->prix > (t + j + 1)->prix) {
                        temp = *(t + j);
                        *(t + j) = *(t + j + 1);
                        *(t + j + 1) = temp;
                    }
                }
            }
            printf("Livres triés par Prix.\n");
            break;
        case 8: // Tri par Disponibilité
            for (int i = 0; i < n - 1; i++) {
                for (int j = 0; j < n - i - 1; j++) {
                    if (strcmp((t + j)->disponibilite, (t + j + 1)->disponibilite) > 0) {
                        temp = *(t + j);
                        *(t + j) = *(t + j + 1);
                        *(t + j + 1) = temp;
                    }
                }
            }
            printf("Livres triés par Disponibilité.\n");
            break;
        default:
            printf("Critère de tri invalide.\n");
            break;
    }
}


int main() {
    int choix;
    Livre *t = NULL;
    int n = 0;
    char Nom[50];
    chargerLivresCSV(&t, &n, "livres.csv");
    printf("Entrer votre nom : ");
    fgets(Nom, sizeof(Nom), stdin);
    Nom[strcspn(Nom, "\n")] = '\0'; // Supprimer le newline

    do {
        printf("---------------------------------------------------------\n");
printf("Bienvenue, %s !\n", Nom);
printf("---------------------------------------------------------\n");
printf("Menu de Gestion de Bibliothèque :\n");
printf("---------------------------------------------------------\n");
printf("1. Ajouter un livre\n");
printf("2. Modifier un livre\n");
printf("3. Supprimer un livre\n");
printf("4. Afficher la liste des livres\n");
printf("5. Rechercher un livre\n");
printf("6. Trier les livres\n");
printf("7. Sauvegarder et Quitter\n");
printf("---------------------------------------------------------\n");
printf("Votre choix : ");

        scanf("%d", &choix);
        getchar(); // Pour absorber le newline restant après le scanf

        switch (choix) {
            case 1:
                ajout(&t, &n);
                break;
            case 2:
                modifier(t, n);
                break;
            case 3:
                supprimer(t, &n);
                break;
            case 4:
                affichage(t, n);
                break;
            case 5:
                recherche(t, n);
                break;
            case 6:
		    int critereTri;
		    printf("Choisir le critère de tri :\n");
		    printf("1. ID\n");
		    printf("2. Auteur\n");
		    printf("3. Titre\n");
		    printf("4. Description\n");
		    printf("5. Nom Utilisateur\n");
		    printf("6. Catégorie\n");
		    printf("7. Prix\n");
		    printf("8. Disponibilité\n");
		    printf("Votre choix : ");
		    scanf("%d", &critereTri);
		    trier(t, n, critereTri);
		    break;
            case 7:
                sauvegarderLivresCSV(t, n, "livres.csv"); // Sauvegarder les livres dans le fichier CSV
                printf("Au revoir, %s !\n", Nom);
                break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }
    } while (choix != 7);

    // Libérer la mémoire allouée pour le tableau de livres avant de quitter
    free(t);

    return 0;
}
