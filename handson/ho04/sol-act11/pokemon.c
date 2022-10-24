#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pokemon.h"

struct pokemon pokedex[POKEMONS];

void show_pokemon(int position){
    struct pokemon pokemon = pokedex[position];
    printf("\n============================= \n");
    printf("==  id: %d \n",  pokemon.id);
    printf("==  name: %s \n",  pokemon.name);
    printf("==  attack: %d \n",  pokemon.attack);
    printf("==  defense: %d \n",  pokemon.defense);
    printf("============================= \n");
}

void init_pokedex(void){

  FILE* f = fopen("./pokedex.csv", "r");
  if(!f) {
    perror("fopen");
    exit(1);
  }

  char *buf = malloc(POKEMONS);
  char *info;
  int i = 0;


  while (fgets(buf, POKEMONS, f) != NULL) {
    if ((strlen(buf)>0) && (buf[strlen (buf) - 1] == '\n'))
        buf[strlen (buf) - 1] = '\0';

    struct pokemon p;
 
    info = strtok(buf, ",");
    int id  = atoi(info);
    p.id = id;
    
    info = strtok(NULL, ",");
    strcpy(p.name, info);

    info = strtok(NULL, ",");
    strcpy(p.type[0], info);

    info = strtok(NULL, ",");
    strcpy(p.type[1], info);

    info = strtok(NULL, ",");
    p.total = atoi(info);

    info = strtok(NULL, ",");
    p.hp = atoi(info); 

    info = strtok(NULL, ",");
    p.attack = atoi(info);

    info = strtok(NULL, ",");
    p.defense = atoi(info);

    info = strtok(NULL, ",");
    p.spAttack = atoi(info);

    info = strtok(NULL, ",");
    p.spDefense = atoi(info);

    info = strtok(NULL, ",");
    p.speed = atoi(info);

    info = strtok(NULL, ",");
    p.generation = atoi(info);

    info = strtok(NULL, ",");
    p.legendary = atoi(info);

    pokedex[i]=p;
  
    i++;

  }
  fclose(f);
  free(buf); // corrects the valgrind possibily lost
}
