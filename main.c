#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 50

// définir une structure pour le stockage du compte
typedef struct {
    char site[MAX_LENGTH];
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];
} Account;

// Fonction de chiffrement + chiffrement :)
void xorEncryptDecrypt(char *data, char key) {
    for (int i = 0; data[i] != '\0'; i++) {
        data[i] ^= key;
    }
}

// Fonction pour enregistrer un mot de passe
void savePassword() {
    Account account;
    char key = 'X'; // Clé de chiffrement XOR

    printf("Entrez le site : ");
    scanf("%s", account.site);
    printf("Entrez le nom d'utilisateur : ");
    scanf("%s", account.username);
    printf("Entrez le mot de passe : ");
    scanf("%s", account.password);

    xorEncryptDecrypt(account.password, key); // Chiffrement du mot de passe

    FILE *file = fopen("passwords.dat", "ab");// ab veut dire ajoute binaire (append/ binary)
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier !\n");
        return;
    }

    fwrite(&account, sizeof(Account), 1, file);
    fclose(file);

    printf("Mot de passe enregistré avec succès !\n");
}

// Fonction pour afficher les mots de passe
void viewPasswords() {
    char mainpassword[MAX_LENGTH];

    printf("Entrez le mot de passe maître : ");
    scanf("%s", mainpassword);

    if (strcmp(mainpassword, "tresdurAdeviner000*") != 0) {
        printf("Mot de passe maître incorrect !\n");
        return;
    }

    FILE *file = fopen("passwords.dat", "rb"); // ouverture du fichier en mode lecture
    if (file == NULL) {
        printf("Aucun mot de passe enregistré !\n");
        return;
    }

    Account account;
    char key = 'X';

    printf("\n--- Liste des mots de passe !!---\n");
    while (fread(&account, sizeof(Account), 1, file)) {
        xorEncryptDecrypt(account.password, key); // Déchiffrement du mot de passe car en utilisant la meme clé deux fois on peut déchiffrer le mdp
        printf("Site : %s | Utilisateur : %s | Mot de passe : %s\n", account.site, account.username, account.password);
    }
    fclose(file);
}

// Fonction principale (menu)
int main() {
    int choix;

    do {
        printf("\n=== Gestionnaire de mots de passe ===\n");
        printf("1. Enregistrer un mot de passe\n");
        printf("2. Voir les mots de passe\n");
        printf("3. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                savePassword();
                break;
            case 2:
                viewPasswords();
                break;
            case 3:
                printf("Au revoir !\n");
                break;
            default:
                printf("Option invalide, réessayez.\n");
        }
    } while (choix != 3);

    return 0;
}
