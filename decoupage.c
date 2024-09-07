#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_ip_parts(const char *ip, int n) {
    int parts[4];
    int i;
    char *token;
    char ip_copy[16];

    // Copie et decoupe l'adresse IP
    strncpy(ip_copy, ip, sizeof(ip_copy) - 1);
    ip_copy[sizeof(ip_copy) - 1] = '\0';
    token = strtok(ip_copy, ".");

    for (i = 0; i < 4 && token != NULL; i++) {
        parts[i] = atoi(token);
        token = strtok(NULL, ".");
    }

    // Calcul et affichage des parties de l'adresse IP
    int step = (i == 0) ? 1 : (i * n); // Gestion de la division
    printf("<ul>");
    for (i = 0; i < n; i++) {
        printf("<li>Part %d: %d.%d.%d.%d</li>\n",
               i + 1,
               parts[0] + (i * step) % 256,
               parts[1] + (i * step) / 256 % 256,
               parts[2] + (i * step) / (256 * 256) % 256,
               parts[3] + (i * step) / (256 * 256 * 256) % 256);
    }
    printf("</ul>");
}

int main() {
    char *data;
    char ip[16];
    int n;

    // En-tete HTTP
    printf("Content-type: text/html\n\n");

    // Recuperation des donnees de la requete
    data = getenv("QUERY_STRING");
    if (data == NULL) {
        printf("<html><body><h1>Erreur: Aucune donnee recue</h1></body></html>");
        return 1;
    }

    // Analyse de la requete
    sscanf(data, "ip=%15[^&]&n=%d", ip, &n);

    // Affichage de la reponse
    printf("<html><body>");
    printf("<h>Decoupage de l'adresse IP</h>");
    printf("<p>Adresse IP: %s</p>", ip);
    printf("<p>Decoupage en %d parties:</p>", n);
    print_ip_parts(ip, n);
    printf("</body></html>");

    return 0;
}
