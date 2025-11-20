#include <stdio.h>
#include <string.h>

int main() {
    char notes[100][200];
    int count = 0;
    char temp[200];
    int choice, i, j, found, word_count;
    char *word;
    
    FILE *file = fopen("episodes.txt", "r");
    if (file != NULL) {
        while (count < 100 && fgets(notes[count], 200, file) != NULL) {
            notes[count][strcspn(notes[count], "\n")] = 0;
            count++;
        }
        fclose(file);
    }
    
    do {
        printf("\n1. Add note\n2. Delete note\n3. Update note\n4. Search note\n5. Count words\n6. Display all\n7. Exit\nChoice: ");
        scanf("%d", &choice);
        getchar();
        
        switch(choice) {
            case 1:
                if (count >= 100) {
                    printf("Full!\n");
                    break;
                }
                printf("Enter note: ");
                fgets(notes[count], 200, stdin);
                notes[count][strcspn(notes[count], "\n")] = 0;
                count++;
                printf("Added!\n");
                break;
                
            case 2:
                printf("Enter note number (1-%d): ", count);
                scanf("%d", &i);
                getchar();
                
                if (i < 1 || i > count) {
                    printf("Invalid!\n");
                } else {
                    for (j = i-1; j < count-1; j++) {
                        strcpy(notes[j], notes[j+1]);
                    }
                    count--;
                    printf("Deleted!\n");
                }
                break;
                
            case 3:
                printf("Enter note number (1-%d): ", count);
                scanf("%d", &i);
                getchar();
                
                if (i < 1 || i > count) {
                    printf("Invalid!\n");
                } else {
                    printf("Current: %s\n", notes[i-1]);
                    printf("Enter new note: ");
                    fgets(notes[i-1], 200, stdin);
                    notes[i-1][strcspn(notes[i-1], "\n")] = 0;
                    printf("Updated!\n");
                }
                break;
                
            case 4:
                printf("Enter search text: ");
                fgets(temp, 200, stdin);
                temp[strcspn(temp, "\n")] = 0;
                
                found = 0;
                for (i = 0; i < count; i++) {
                    if (strstr(notes[i], temp) != NULL) {
                        printf("%d. %s\n", i+1, notes[i]);
                        found = 1;
                    }
                }
                if (!found) {
                    printf("None found.\n");
                }
                break;
                
            case 5:
                printf("Enter word to count: ");
                fgets(temp, 200, stdin);
                temp[strcspn(temp, "\n")] = 0;
                
                word_count = 0;
                for (i = 0; i < count; i++) {
                    char *ptr = notes[i];
                    while (*ptr) {
                        if (strstr(ptr, temp) == ptr) {
                            word_count++;
                        }
                        ptr++;
                    }
                }
                printf("Found %d times.\n", word_count);
                break;
                
            case 6:
                if (count == 0) {
                    printf("Empty!\n");
                } else {
                    for (i = 0; i < count; i++) {
                        printf("%d. %s\n", i+1, notes[i]);
                    }
                }
                break;
                
            case 7:
                file = fopen("episodes.txt", "w");
                if (file != NULL) {
                    for (i = 0; i < count; i++) {
                        fprintf(file, "%s\n", notes[i]);
                    }
                    fclose(file);
                }
                printf("Saved!\n");
                break;
                
            default:
                printf("Invalid!\n");
        }
    } while (choice != 7);
    
    return 0;
}