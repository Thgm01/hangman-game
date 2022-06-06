#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void header();
void recive_guess();


int main()
{
    

    char sec_word[20];

    sprintf(sec_word, "MELANCIA"); //Put a word in a char string

    int win = 0;
    int hanged = 0;

    char tries[26];
    int attempts = 0;

    do
    { //begin the game

        system("clear");
        header();

        for(int i=0; i<strlen(sec_word); i++)
        {   
            int find = 0;
            for(int j=0; j<attempts; j++)
            {
                if(tries[j]==sec_word[i])
                {
                    find = 1;
                    break;
                }
            }
            if(find)
            {
                printf("%c ", sec_word[i]);
            }else
            {
                printf("_ ");
            }
            
        }
        printf("\n");

        recive_guess(tries, &attempts);

    }while(!win && !hanged);

}

void recive_guess(char tries[26], int* attempts) //recive the player's guess and save in tries
{
    char guess;
    scanf(" %c", &guess);

    tries[(*attempts)] = guess;
    (*attempts)++;
}

void header() //print game header
{
    printf("************************\n");
    printf("***   HANGMAN GAME   ***\n");
    printf("************************\n\n");
}