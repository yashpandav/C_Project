#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Interview
{
     char require[50];
     int experience;
     int age;
     int total_emp;
};

struct candidate
{
     char name[20];
     int year;
     int age;
     char degree[20];
     int experience;
     char skills[50];
     int recomendations;
};


     /*
     ! input_interview
     */

void take_input_interview(struct Interview interv){
     FILE* inter = fopen("interview.txt", "w");

     if(inter == NULL){
          perror("Couldn't open candidate file");
          return;
     }

     printf("Enter The Total Number Of Required Employees : ");
     scanf("%d", &interv.total_emp);
     printf("Enter The Required Skills : ");
     scanf("%s", interv.require);
     printf("Enter The Minimum Required Expierence : ");
     scanf("%d", &interv.experience);
     printf("Enter The Minimum Required Age : ");
     scanf("%d", &interv.age);     

     fwrite(&interv , sizeof(interv), 1, inter);
     fclose(inter);  
     return;      
}


     /*
     ! Display_interview
     */

void display_interview(struct Interview interv){
     FILE* inter = fopen("interview.txt", "r");
     printf("\n");
     if(inter == NULL){
          perror("Couldn't open candidate file");
          return;
     }

     while (fread(&interv , sizeof(interv), 1, inter))
     {
          printf("Total Number Of Required Employees : %d\n", interv.total_emp);
          printf("The Required Skills : %s\n", interv.require);
          printf("The Minimum Required Expierence : %d\n", interv.experience);
          printf("The Minimum Required Age : %d\n", interv.age);    
     }
     fclose(inter);
}



     /*
     ! INPUT_CANDIDATE
     */

void take_input_candidate(){
     int n;
     printf("How Many Candidates Wants To Apply : %d\n", n);
     
     struct candidate can[n];
     FILE* candp = fopen("candidates.txt", "w");

     if(candp == NULL){
          perror("Couldn't open candidate file");
          return;
     }

     for(int i = 0; i < n; i++){
          printf()
     }
     return;
}

int main(){
     /*
     ! STARTING
     */
     struct Interview interv;

     take_input_interview(interv);
     display_interview(interv);
     take_input_candidate();


     return 0;
}
