#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2];
    pipe(fd);  // Création du pipe

    pid_t pid = fork();  // Création du processus enfant

    if (pid == 0) {  
        // --- Processus enfant ---
        close(fd[1]);  // Ferme l’extrémité d’écriture
        char message[50];
        read(fd[0], message, sizeof(message));
        printf("Enfant a reçu : %s\n", message);
        close(fd[0]);
    } else {  
        // --- Processus parent ---
        close(fd[0]);  // Ferme l’extrémité de lecture
        char *text = "Salut de ton parent !";
        write(fd[1], text, strlen(text) + 1);
        close(fd[1]);
    }

    return 0;
}
