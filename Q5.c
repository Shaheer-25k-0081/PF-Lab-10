#include <stdio.h>
#include <string.h>

int main() {
    char tags[100][100];
    int count = 0;
    char temp[100];
    int choice, i, j, found;
    char *word;
    int word_count;
    
    FILE *file = fopen("tags.txt", "r");
    if (file != NULL) {
        while (count < 100 && fgets(tags[count], 100, file) != NULL) {
            tags[count][strcspn(tags[count], "\n")] = 0;
            count++;
        }
        fclose(file);
    }
    
    do {
        printf("\n1. Add tag\n2. Delete tag\n3. Update tag\n4. Search tag\n5. Display all\n6. Exit\nChoice: ");
        scanf("%d", &choice);
        getchar();
        
        switch(choice) {
            case 1:
                if (count >= 100) {
                    printf("Full!\n");
                    break;
                }
                printf("Enter tag (5-7 words): ");
                fgets(temp, 100, stdin);
                temp[strcspn(temp, "\n")] = 0;
                
                word_count = 0;
                word = strtok(temp, " ");
                while (word != NULL) {
                    word_count++;
                    word = strtok(NULL, " ");
                }
                
                if (word_count < 5 || word_count > 7) {
                    printf("Must be 5-7 words!\n");
                } else {
                    printf("Enter tag: ");
                    fgets(tags[count], 100, stdin);
                    tags[count][strcspn(tags[count], "\n")] = 0;
                    count++;
                    printf("Added!\n");
                }
                break;
                
            case 2:
                printf("Enter tag number (1-%d): ", count);
                scanf("%d", &i);
                getchar();
                
                if (i < 1 || i > count) {
                    printf("Invalid!\n");
                } else {
                    for (j = i-1; j < count-1; j++) {
                        strcpy(tags[j], tags[j+1]);
                    }
                    count--;
                    printf("Deleted!\n");
                }
                break;
                
            case 3:
                printf("Enter tag number (1-%d): ", count);
                scanf("%d", &i);
                getchar();
                
                if (i < 1 || i > count) {
                    printf("Invalid!\n");
                } else {
                    printf("Current: %s\n", tags[i-1]);
                    printf("Enter new tag (5-7 words): ");
                    fgets(temp, 100, stdin);
                    temp[strcspn(temp, "\n")] = 0;
                    
                    word_count = 0;
                    word = strtok(temp, " ");
                    while (word != NULL) {
                        word_count++;
                        word = strtok(NULL, " ");
                    }
                    
                    if (word_count < 5 || word_count > 7) {
                        printf("Must be 5-7 words!\n");
                    } else {
                        printf("Enter new tag: ");
                        fgets(tags[i-1], 100, stdin);
                        tags[i-1][strcspn(tags[i-1], "\n")] = 0;
                        printf("Updated!\n");
                    }
                }
                break;
                
            case 4:
                printf("Enter search text: ");
                fgets(temp, 100, stdin);
                temp[strcspn(temp, "\n")] = 0;
                
                found = 0;
                for (i = 0; i < count; i++) {
                    if (strstr(tags[i], temp) != NULL) {
                        printf("%d. %s\n", i+1, tags[i]);
                        found = 1;
                    }
                }
                if (!found) {
                    printf("None found.\n");
                }
                break;
                
            case 5:
                if (count == 0) {
                    printf("Empty!\n");
                } else {
                    for (i = 0; i < count; i++) {
                        printf("%d. %s\n", i+1, tags[i]);
                    }
                }
                break;
                
            case 6:
                file = fopen("tags.txt", "w");
                if (file != NULL) {
                    for (i = 0; i < count; i++) {
                        fprintf(file, "%s\n", tags[i]);
                    }
                    fclose(file);
                }
                printf("Saved!\n");
                break;
                
            default:
                printf("Invalid!\n");
        }
    } while (choice != 6);
    
    return 0;
}