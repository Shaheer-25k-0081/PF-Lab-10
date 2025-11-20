#include <stdio.h>
#include <string.h>

int main() {
    FILE *fp;
    char levels[50][200];
    int count = 0;
    char temp[200];
    int choice;

    fp = fopen("levels.txt", "r");
    if (fp != NULL) {
        while (fgets(levels[count], 200, fp) != NULL && count < 50) {
            levels[count][strcspn(levels[count], "\n")] = '\0';
            count++;
        }
        fclose(fp);
    }

    while (1) {
        printf("\n1. Add Level\n2. Search Level\n3. Update Level\n4. Delete Level\n5. Exit\nEnter choice: ");
        scanf("%d", &choice);
        getchar();

        if (choice == 5) break;

        if (choice == 1) {
            if (count == 50) {
                printf("Storage full.\n");
            } else {
                printf("Enter level description (max 7 words): ");
                fgets(temp, 200, stdin);
                temp[strcspn(temp, "\n")] = '\0';

                int words = 1;
                for (int i = 0; temp[i] != '\0'; i++)
                    if (temp[i] == ' ') words++;

                if (words > 7) {
                    printf("Too many words! (max 7)\n");
                } else {
                    strcpy(levels[count], temp);
                    count++;
                }
            }
        }

        else if (choice == 2) {
            printf("Enter level to search: ");
            fgets(temp, 200, stdin);
            temp[strcspn(temp, "\n")] = '\0';

            int found = 0;
            for (int i = 0; i < count; i++) {
                if (strcmp(levels[i], temp) == 0) {
                    printf("Found at index %d\n", i);
                    found = 1;
                    break;
                }
            }
            if (!found) printf("Not found.\n");
        }

        else if (choice == 3) {
            printf("Enter existing level to update: ");
            fgets(temp, 200, stdin);
            temp[strcspn(temp, "\n")] = '\0';

            int idx = -1;
            for (int i = 0; i < count; i++)
                if (strcmp(levels[i], temp) == 0) idx = i;

            if (idx == -1) {
                printf("Not found.\n");
            } else {
                printf("Enter new description (max 7 words): ");
                fgets(levels[idx], 200, stdin);
                levels[idx][strcspn(levels[idx], "\n")] = '\0';

                int words = 1;
                for (int i = 0; levels[idx][i] != '\0'; i++)
                    if (levels[idx][i] == ' ') words++;

                if (words > 7) {
                    printf("Too many words! Update cancelled.\n");
                }
            }
        }

        else if (choice == 4) {
            printf("Enter level to delete: ");
            fgets(temp, 200, stdin);
            temp[strcspn(temp, "\n")] = '\0';

            int idx = -1;
            for (int i = 0; i < count; i++)
                if (strcmp(levels[i], temp) == 0) idx = i;

            if (idx == -1) {
                printf("Not found.\n");
            } else {
                for (int j = idx; j < count - 1; j++)
                    strcpy(levels[j], levels[j + 1]);
                count--;
                printf("Deleted.\n");
            }
        }
    }

    fp = fopen("levels.txt", "w");
    for (int i = 0; i < count; i++)
        fprintf(fp, "%s\n", levels[i]);
    fclose(fp);

    printf("All changes saved.\n");

    return 0;
}
