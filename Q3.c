#include <stdio.h>
#include <string.h>

int main() {
    FILE *fp;
    char recipes[40][200];
    int count = 0;
    char temp[200];
    int choice;

    fp = fopen("recipes.txt", "r");
    if (fp != NULL) {
        while (fgets(recipes[count], 200, fp) != NULL && count < 40) {
            recipes[count][strcspn(recipes[count], "\n")] = '\0';
            count++;
        }
        fclose(fp);
    }

    while (1) {
        printf("\n1. Add Recipe");
        printf("\n2. Modify Recipe");
        printf("\n3. Delete Recipe");
        printf("\n4. Search (partial/full)");
        printf("\n5. Exit (-1)");
        printf("\nEnter choice: ");
        scanf("%d", &choice);
        getchar();

        if (choice == -1 || choice == 5) break;

        if (choice == 1) {
            if (count == 40) {
                printf("Recipe list full.\n");
            } else {
                printf("Enter recipe name: ");
                fgets(recipes[count], 200, stdin);
                recipes[count][strcspn(recipes[count], "\n")] = '\0';
                count++;
            }
        }

        else if (choice == 2) {
            printf("Enter recipe name to modify: ");
            fgets(temp, 200, stdin);
            temp[strcspn(temp, "\n")] = '\0';

            int index = -1;
            for (int i = 0; i < count; i++) {
                if (strcmp(recipes[i], temp) == 0) {
                    index = i;
                    break;
                }
            }

            if (index == -1) {
                printf("Not found.\n");
            } else {
                printf("Enter new name: ");
                fgets(recipes[index], 200, stdin);
                recipes[index][strcspn(recipes[index], "\n")] = '\0';
            }
        }

        else if (choice == 3) {
            printf("Enter recipe name to delete: ");
            fgets(temp, 200, stdin);
            temp[strcspn(temp, "\n")] = '\0';

            int index = -1;
            for (int i = 0; i < count; i++) {
                if (strcmp(recipes[i], temp) == 0) {
                    index = i;
                    break;
                }
            }

            if (index == -1) {
                printf("Not found.\n");
            } else {
                for (int j = index; j < count - 1; j++)
                    strcpy(recipes[j], recipes[j + 1]);
                count--;
                printf("Deleted.\n");
            }
        }

        else if (choice == 4) {
            printf("Enter text to search: ");
            fgets(temp, 200, stdin);
            temp[strcspn(temp, "\n")] = '\0';

            int found = 0;
            for (int i = 0; i < count; i++) {
                if (strstr(recipes[i], temp) != NULL) {
                    printf("Match: %s\n", recipes[i]);
                    found = 1;
                }
            }
            if (!found) printf("No matches.\n");
        }

        else {
            printf("Invalid choice.\n");
        }
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (strcmp(recipes[i], recipes[j]) > 0) {
                strcpy(temp, recipes[i]);
                strcpy(recipes[i], recipes[j]);
                strcpy(recipes[j], temp);
            }
        }
    }

    fp = fopen("recipes.txt", "w");
    for (int i = 0; i < count; i++)
        fprintf(fp, "%s\n", recipes[i]);
    fclose(fp);

    printf("\nRecipes saved. Exiting.\n");

    return 0;
}
