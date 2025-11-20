#include <stdio.h>
#include <string.h>

int main() {
    FILE *fp;
    char songs[10][200];
    int count = 0;
    char temp[200];
    int choice;

    fp = fopen("playlist.txt", "r");
    if (fp != NULL) {
        while (fgets(songs[count], 200, fp) != NULL && count < 10) {
            songs[count][strcspn(songs[count], "\n")] = '\0';
            count++;
        }
        fclose(fp);
    }

    while (1) {
        printf("\n1. Add Song\n2. Delete Song\n3. Search Song\n4. Exit (-1)\nEnter: ");
        scanf("%d", &choice);
        getchar();

        if (choice == -1 || choice == 4) break;

        if (choice == 1) {
            if (count == 10) {
                printf("Playlist full.\n");
            } else {
                printf("Enter song: ");
                fgets(songs[count], 200, stdin);
                songs[count][strcspn(songs[count], "\n")] = '\0';
                count++;
            }
        }

        else if (choice == 2) {
            printf("Enter song to delete: ");
            fgets(temp, 200, stdin);
            temp[strcspn(temp, "\n")] = '\0';

            int i, found = 0;
            for (i = 0; i < count; i++) {
                if (strcmp(songs[i], temp) == 0) {
                    found = 1;
                    break;
                }
            }

            if (found) {
                for (int j = i; j < count - 1; j++)
                    strcpy(songs[j], songs[j + 1]);
                count--;
                printf("Deleted.\n");
            } else {
                printf("Not found.\n");
            }
        }

        else if (choice == 3) {
            printf("Enter song to search: ");
            fgets(temp, 200, stdin);
            temp[strcspn(temp, "\n")] = '\0';

            int found = 0;
            for (int i = 0; i < count; i++) {
                if (strcmp(songs[i], temp) == 0) {
                    printf("Found at position %d\n", i + 1);
                    found = 1;
                    break;
                }
            }
            if (!found) printf("Not found.\n");
        }
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (strcmp(songs[i], songs[j]) > 0) {
                strcpy(temp, songs[i]);
                strcpy(songs[i], songs[j]);
                strcpy(songs[j], temp);
            }
        }
    }

    fp = fopen("playlist.txt", "w");
    for (int i = 0; i < count; i++)
        fprintf(fp, "%s\n", songs[i]);
    fclose(fp);

    printf("\nFinal Playlist:\n");
    for (int i = 0; i < count; i++)
        printf("%d. %s\n", i + 1, songs[i]);

    return 0;
}
