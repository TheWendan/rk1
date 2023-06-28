#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#define MAX_TEXT_LENGTH 1000

int main() {
    FILE *file;
    char text[MAX_TEXT_LENGTH];
    char inputChar;
    int index = 0;
    int score = 0;
    int mistakes = 0; int mistake_limit;
    int select;
    time_t start, end; double endTime; int time_limit;
    int flag1 = 0; int flag2 = 0;
    int typingSpeed;
    char warning1[] = "Time limit has been exceeded!"; char warning2[] = "Limit of mistakes!";
    
  
    printf("Choose the difficulty of the game:\n 1 - easy \n 2 - medium \n 3 - hard \n");
    scanf("%d", &select);
    switch(select) {
        case 1:
            file = fopen("easy.txt", "r");
            time_limit = 5;
            mistake_limit = 5;
            printf("You have chosen difficulty \"easy\", time limit = %d\n\n", time_limit);
            break;
        case 2:
            file = fopen("medium.txt", "r");
            time_limit = 20;
            mistake_limit = 10;
            printf("You have chosen difficulty \"medium\", time limit = %d\n\n", time_limit);
            break;
        case 3:
            time_limit = 40;
            file = fopen("hard.txt", "r");
            mistake_limit = 15;
            printf("You have chosen difficulty \"hard\", time limit = %d\n\n", time_limit);
            break;        
    }

    // Ошибка открытия
    if (file == NULL) {
        printf("The text file could not be opened.\n");
        return 1;
    }
    fgets(text, MAX_TEXT_LENGTH, file); // Считываем текст из файла
    fclose(file); // Закрываем файл

    printf("Text to enter:\n");
    printf("%s\n", text); // Текст из файла
    printf("Press the keys to enter text:\n");
    start = clock(); 

    // Цикл ввода текста
    while ((text[index] != '\0') && (text[index] != '\n')) {
        inputChar = getch();

        // Проверяем правильность нажатой клавиши
        if (inputChar == text[index]) 
        {
            printf("\033[32m%c\033[0m", inputChar);
            score++;
        } 
        else    
        {
            printf("\033[31m%c\033[0m", text[index]);
            mistakes++;
        }
        index++;
        end = clock();
        endTime = ((double) (end - start)) / CLOCKS_PER_SEC;
        if (endTime > time_limit) {
            flag1 = 1;
            break;
        }
        if (mistakes > mistake_limit) {
            flag2 = 1;
            break;
        }
    }
    if (flag1 == 1) {
        printf("\n\033[31m%s\033[0m\n", warning1);
    }
    if (flag2 == 1) {
        printf("\n\033[31m%s\033[0m\n", warning2);
    }

    printf("\nResults:\n");
    printf("True: %d symbols\n", score);
    printf("Mistakes: %d\n", mistakes);
    printf("Time: %.2f seconds\n", endTime);
    typingSpeed = (double)score / endTime;
    printf("Typing Speed: %.2f characters per second\n", endTime);

    return 0;
}