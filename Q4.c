#include <stdio.h>
#include <string.h>

int main() {
    char affirmations[100][200];
    int count = 0;
    char temp[200];
    int choice, i, j, found, word_count;
    char *word;
    
    FILE *file = fopen("affirm.txt", "r");
    if (file != NULL) {
        while (count < 100 && fgets(affirmations[count], 200, file) != NULL) {
            affirmations[count][strcspn(affirmations[count], "\n")] = 0;
            count++;
        }
        fclose(file);
        printf("Loaded %d affirmations from file.\n", count);
    } else {
        printf("No existing file found. Starting fresh.\n");
    }
    
    do {
        printf("\n1. Add affirmation\n2. Delete affirmation\n3. Update affirmation\n");
        printf("4. Search affirmation\n5. Display all\n6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();
        
        switch(choice) {
            case 1:
                if (count >= 100) {
                    printf("Maximum affirmations reached!\n");
                    break;
                }
                printf("Enter new affirmation (max 7 words): ");
                fgets(temp, 200, stdin);
                temp[strcspn(temp, "\n")] = 0;
                
                word_count = 0;
                word = strtok(temp, " ");
                while (word != NULL) {
                    word_count++;
                    word = strtok(NULL, " ");
                }
                
                if (word_count > 7) {
                    printf("Error: Affirmation must be 7 words or less!\n");
                } else {
                    printf("Enter new affirmation: ");
                    fgets(affirmations[count], 200, stdin);
                    affirmations[count][strcspn(affirmations[count], "\n")] = 0;
                    count++;
                    printf("Affirmation added!\n");
                }
                break;
                
            case 2:
                printf("Enter affirmation number to delete (1-%d): ", count);
                scanf("%d", &i);
                getchar();
                
                if (i < 1 || i > count) {
                    printf("Invalid number!\n");
                } else {
                    for (j = i-1; j < count-1; j++) {
                        strcpy(affirmations[j], affirmations[j+1]);
                    }
                    count--;
                    printf("Affirmation deleted!\n");
                }
                break;
                
            case 3:
                printf("Enter affirmation number to update (1-%d): ", count);
                scanf("%d", &i);
                getchar();
                
                if (i < 1 || i > count) {
                    printf("Invalid number!\n");
                } else {
                    printf("Current: %s\n", affirmations[i-1]);
                    printf("Enter new affirmation (max 7 words): ");
                    fgets(temp, 200, stdin);
                    temp[strcspn(temp, "\n")] = 0;
                    
                    word_count = 0;
                    word = strtok(temp, " ");
                    while (word != NULL) {
                        word_count++;
                        word = strtok(NULL, " ");
                    }
                    
                    if (word_count > 7) {
                        printf("Error: Affirmation must be 7 words or less!\n");
                    } else {
                        printf("Enter new affirmation: ");
                        fgets(affirmations[i-1], 200, stdin);
                        affirmations[i-1][strcspn(affirmations[i-1], "\n")] = 0;
                        printf("Affirmation updated!\n");
                    }
                }
                break;
                
            case 4:
                printf("Enter phrase to search: ");
                fgets(temp, 200, stdin);
                temp[strcspn(temp, "\n")] = 0;
                
                found = 0;
                for (i = 0; i < count; i++) {
                    if (strstr(affirmations[i], temp) != NULL) {
                        printf("%d. %s\n", i+1, affirmations[i]);
                        found = 1;
                    }
                }
                if (!found) {
                    printf("No matching affirmations found.\n");
                }
                break;
                
            case 5:
                if (count == 0) {
                    printf("No affirmations stored.\n");
                } else {
                    printf("\nAll Affirmations:\n");
                    for (i = 0; i < count; i++) {
                        printf("%d. %s\n", i+1, affirmations[i]);
                    }
                }
                break;
                
            case 6:
                file = fopen("affirm.txt", "w");
                if (file != NULL) {
                    for (i = 0; i < count; i++) {
                        fprintf(file, "%s\n", affirmations[i]);
                    }
                    fclose(file);
                    printf("Affirmations saved to file. Goodbye!\n");
                } else {
                    printf("Error saving to file!\n");
                }
                break;
                
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 6);
    
    return 0;
}