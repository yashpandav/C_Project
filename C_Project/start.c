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
     int id;
     char name[20];
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


void take_input_candidate(int n , struct candidate* canp){
     FILE* candidateFile = fopen("candidates.txt", "w");

     if(candidateFile == NULL){
          perror("Couldn't open candidate file");
          return;
     }

     for(int i = 0; i < n; i++){
          printf("Enter The Id Of %d Candidate : " , i+1);
          scanf("%d", (canp+i)->id);
          printf("Enter The Name Of %d Candidate : " , i+1);
          scanf("%s", (canp+i)->name);
          printf("Enter The Age Of %d Candidate : " , i+1);
          scanf("%d", (canp+i)->age);
          printf("Enter The Degree Of %d Candidate : " , i+1);
          scanf("%s", (canp+i)->degree);
          printf("Enter The Experience Of %d Candidate : " , i+1);
          scanf("%d", (canp+i)->experience);
          printf("Enter The Skills Of %d Candidate : " , i+1);
          scanf("%s", (canp+i)->skills);
          printf("Have you A Recomendation Letter , If Yes Then Enter 1 Else Enter 0 : ");
          scanf("%d", (canp+i)->recomendations);

          fwrite((canp+i) , sizeof(struct candidate) , 1 , candidateFile);
     }
     return;
}


     /*
     ! DISPLAY_CANDIDATE
     */

void display_candidate(int n , struct candidate* canp){
     FILE* candidateFile = fopen("candidates.txt", "r");
     
     if(candidateFile == NULL){
          perror("Couldn't open candidate file");
          return;
     }

     while (fread(canp , sizeof(struct candidate), 1, candidateFile)){
          printf("ID : %d\n", canp->id);
          printf("Name : %s\n", canp->name);
          printf("Age : %d\n", canp->age);
          printf("Degree : %s\n", canp->degree);
          printf("Experience : %d\n", canp->experience);
          printf("Skills : %s\n", canp->skills);
          printf("Recomendation Letter : %d\n", canp->recomendations);
          printf("\n");
     }     
     fclose(candidateFile);
     return;

}

int main(){
     /*
     ! STARTING
     */
     struct Interview interv;

     // take_input_interview(interv);
     // display_interview(interv);
     int n;
     printf("How Many Candidates Wants To Apply : ");
     scanf("%d", &n);
     struct candidate can[n];
     take_input_candidate(n , &can[0]);
     display_candidate(n , &can[0]);

     return 0;
}
