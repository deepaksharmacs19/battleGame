#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_CHARACTERS 10
#define STRING_LENGTH 21

int read_character_file(FILE *, char[][STRING_LENGTH],int[]);
void write_to_file(char[][STRING_LENGTH],int[],int);
void display_characters(char[][STRING_LENGTH],int[],int);
int find_character(char[],char[][STRING_LENGTH],int);
int add_character(char[][STRING_LENGTH],int[],char[],int,int*);
int remove_character(char[][STRING_LENGTH],int[],char[],int*);
void display_highest_health(char[][STRING_LENGTH],int[],int);
void do_battle(char[][STRING_LENGTH],int[],int,int);



int main()
{
FILE *f;
int index;
char choice[21];
char character_array[MAX_CHARACTERS][STRING_LENGTH]={'\0'};
int health_array[MAX_CHARACTERS]={0};
int size=read_character_file(f,character_array,health_array);

do{
printf("Please enter command\n[list, search, reset, add, remove, high, battle, quit] : ");
scanf("%s",choice);
if(strcmp(choice,"list")==0) {
display_characters(character_array,health_array,size);
}
else if(strcmp(choice,"search")==0){
char name[21];
printf("\n\nEnter superhero you want to search : ");
fflush(stdin);
gets(name);
index=find_character(name,character_array,size);
if(index>0) printf("\nSuperhero : %s and health : %d\n",character_array[index],health_array[index]);
else printf("\nCharacter has not been found!\n");
}

else if(strcmp(choice,"reset")==0){
char name[21];
printf("Enter the name of the superhero to reset : ");
fflush(stdin);
scanf("%[^\n]",name);
int n=find_character(name,character_array,size);
if(n<0) 
{
printf("Character not found cannot reset\n");
}
else 
{
printf("Character's health reset successfully\n");
health_array[n]=100;
}
}

else if(strcmp(choice,"add")==0){
char name[21];
int health;
printf("Please enter character's name : ");
fflush(stdin);
gets(name);
printf("Please enter character's health : ");
scanf("%d",&health);
int p=add_character(character_array,health_array,name,health,&size);
if(p==-1) printf("Character length is full - %s unable to added\n",name);
else if(p==-2) printf("Character already exists - %s unable to added\n",name);
else printf("Character %s successfully added to the list\n",name);
}
else if(strcmp(choice,"remove")==0){
char name[21];
printf("Please enter character's name : ");
fflush(stdin);
gets(name);
int n=remove_character(character_array,health_array,name,&size);
if(n>0) printf("%s removed successfully from the list\n",name);
else printf("character not removed - not found\n");

printf("%d\n",size);
}
else if(strcmp(choice,"high")==0){
display_highest_health(character_array,health_array,size);
}
else if(strcmp(choice,"battle")==0){
char firstOpponent[21],secondOpponent[21];
int battleRounds;
printf("Please enter opponent one's name: ");
fflush(stdin);
gets(firstOpponent);
printf("Please enter opponent two's name: ");
fflush(stdin);
gets(secondOpponent);
int indexOne=find_character(firstOpponent,character_array,size);
int indexTwo=find_character(secondOpponent,character_array,size);
do_battle(character_array,health_array,indexOne,indexTwo);
}
else if(strcmp(choice,"quit")==0) printf("Exiting the menu!");
else printf("Invalid Input, try again!");
} while(strcmp(choice,"quit")!=0);

return 0;
}

void do_battle(char character_array[][STRING_LENGTH],int health_array[],int indexOne,int indexTwo)
{
int powerOfOne=health_array[indexOne];
int powerOfTwo=health_array[indexTwo];
int damage1=0;
int damage2=0;
int battleRounds=0;
printf("Please enter the number of battle rounds: ");
scanf("%d",&battleRounds);
printf("-- Battle --\n");
printf("%s versus %s - %d rounds:",character_array[indexOne],character_array[indexTwo],battleRounds);
for(int i=0;i<battleRounds && (powerOfOne>0 || powerOfTwo>0) ;i++)
{
damage1=rand()%50;
powerOfOne=powerOfOne-damage1;
damage2=rand()%50;
powerOfTwo=powerOfTwo-damage2;

printf("Round %d: \n\n",i+1);
printf("    > %s -Damage: %d - current health: %d\n",character_array[indexOne],damage1,powerOfOne);
printf("    > %s -Damage: %d - current health: %d\n",character_array[indexTwo],damage2,powerOfTwo);
}

printf("-- End of battle --\n");
if(powerOfOne>powerOfTwo) 
{
printf("** %s wins! **\n",character_array[indexOne]);
}
else 
{
printf("** %s wins! **\n",character_array[indexTwo]);
}

health_array[indexOne]=powerOfOne;
health_array[indexTwo]=powerOfTwo;
}

int remove_character(char char_array[][STRING_LENGTH],int health_array[],char name[],int*size)
{
if(find_character(name,char_array,*size)<0) return -1;
int ind=0;
for(int i=0;i<*size;i++) 
{
if(strcmp(name,char_array[i])==0) ind=i; 
}
if(ind==*size)
{
*size=*size-1;
return 1;
}
printf("%d\n",*size);
for(int i=ind+1;i<*size;i++)
{
strcpy(char_array[i-1],char_array[i]);
health_array[i-1]=health_array[i];
}
*size=*size-1;

printf("%d\n",*size);
return 1;
}


void display_highest_health(char character_array[][STRING_LENGTH],int health_array[],int size){
int max=0;
for(int i=0;i<size;i++)if(max<health_array[i]) max=health_array[i];
for(int i=0;i<size;i++) if(max==health_array[i]) printf("\nSuperhero : %s, health : %d\n",character_array[i],health_array[i]);
}


int add_character(char character_array[][STRING_LENGTH],int health_array[],char name[],int health,int*size)
{
if(*size==MAX_CHARACTERS) return -1;
if(find_character(name,character_array,*size)!=-1)return -2;

strcpy(character_array[*size],name);
health_array[*size]=health;
*size=*size+1;

return 1;
}


int find_character(char name[],char character_array[][STRING_LENGTH],int n){
int index=-1;


for(int i=0;i<n;i++)
{
if(strcmp(name,character_array[i])==0) {
index=i;
}
}
return index;
}




int read_character_file(FILE *f, char character_array[][STRING_LENGTH],int health_array[]){
char name[31];
f=fopen("characters.txt","rb");
int i=0;
int j,k;
j=0;
k=0;

while(!feof(f))
{
fscanf(f,"%[^\n]\n",name);
if(i%2==0){
strcpy(character_array[j],name);
character_array[j][strlen(character_array[j])-1]='\0';
j++;
}
else{
health_array[k]=atoi(name);
k++;
}
i++;
}
return j;
}




void display_characters(char str[][STRING_LENGTH],int arr[MAX_CHARACTERS],int n)
{
int i=0;
printf("================================================\n");
printf("-            Character Summary                 -\n");
printf("================================================\n");
printf("-  Name                                Health  -");
printf("\n================================================\n");

for(i=0;i<n;i++){
int space=(41-strlen(str[i]));
//printf("-   %s\t\t\t\t%d      -\n",str[i],arr[i]);
printf("-  %s %*d  -\n",str[i],space,arr[i]);
printf("------------------------------------------------\n");
}

printf("================================================\n");
}
