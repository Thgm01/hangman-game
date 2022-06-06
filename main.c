#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void header();
void recive_guess();
int have_letter(char letter);
void draw_letters();
void selec_word();

char secret_word[20];
char tries[26];
int attempts = 0;

int main()
{
    selec_word();

    int win = 0;
    int hanged = 0;



    do
    { //begin the game

        system("clear");
        header();

        draw_letters();

        recive_guess();

    }while(!win && !hanged);

}

int have_letter(char letter) //verify if the user's guess has in the secret word 
{
    for(int j=0; j<attempts; j++)
    {
        if(tries[j]==letter)
        {
            return 1;
        }
    }
    return 0;
}

void recive_guess() //recive the player's guess and save in tries
{
    char guess;
    scanf(" %c", &guess);

    tries[attempts] = guess;
    attempts++;
}

void header() //print game header
{
    printf("************************\n");
    printf("***   HANGMAN GAME   ***\n");
    printf("************************\n\n");
}

void draw_letters() //draw the letter if it is in the secret word or draw an underscore if not 
{
    for(int i=0; i<strlen(secret_word); i++)
        {   
            
            //here
            int find = have_letter(secret_word[i]);
            
            if(find)
            {
                printf("%c ", secret_word[i]);
            }else
            {
                printf("_ ");
            }
            
        }
        printf("\n");
}

void selec_word() //select a word and put in a char string
{
    sprintf(secret_word, "MELANCIA");
}