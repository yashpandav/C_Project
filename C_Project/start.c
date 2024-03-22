#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void take_input_interview(struct Interview *interv)
{
     FILE *inter = fopen("interview.txt", "w");

     if (inter == NULL)
     {
          perror("Couldn't open interview file");
          return;
     }

     printf("Enter The Total Number Of Required Employees : ");
     scanf("%d", &interv->total_emp);
     printf("Enter The Required Skills : ");
     scanf("%s", interv->require);
     printf("Enter The Minimum Required Expierence : ");
     scanf("%d", &interv->experience);
     printf("Enter The Minimum Required Age : ");
     scanf("%d", &interv->age);

     fwrite(interv, sizeof(struct Interview), 1, inter);
     fclose(inter);
     return;
}

void display_interview(struct Interview *interv)
{
     FILE *inter = fopen("interview.txt", "r");

     if (inter == NULL)
     {
          perror("Couldn't open interview file");
          return;
     }

     fread(interv, sizeof(struct Interview), 1, inter);

     printf("Total Number Of Required Employees : %d\n", interv->total_emp);
     printf("The Required Skills : %s\n", interv->require);
     printf("The Minimum Required Experience : %d\n", interv->experience);
     printf("The Minimum Required Age : %d\n", interv->age);

     fclose(inter);
}

void take_input_candidate(int n, struct candidate *can)
{
     FILE *candidateFile = fopen("candidates.txt", "w");

     if (candidateFile == NULL)
     {
          perror("Couldn't open candidate file");
          return;
     }

     for (int i = 0; i < n; i++)
     {
          printf("Enter The Id Of %d Candidate : ", i + 1);
          scanf("%d", &can[i].id);
          printf("Enter The Name Of %d Candidate : ", i + 1);
          scanf("%s", can[i].name);
          printf("Enter The Age Of %d Candidate : ", i + 1);
          scanf("%d", &can[i].age);
          printf("Enter The Degree Of %d Candidate : ", i + 1);
          scanf("%s", can[i].degree);
          printf("Enter The Experience Of %d Candidate : ", i + 1);
          scanf("%d", &can[i].experience);
          printf("Enter The Skills Of %d Candidate : ", i + 1);
          scanf("%s", can[i].skills);
          printf("Have you A Recommendation Letter, If Yes Then Enter 1 Else Enter 0 : ");
          scanf("%d", &can[i].recomendations);

          fwrite(&can[i], sizeof(struct candidate), 1, candidateFile);
     }

     fclose(candidateFile);
}

void display_candidate(int n)
{
     FILE *candidateFile = fopen("candidates.txt", "r");

     if (candidateFile == NULL)
     {
          perror("Couldn't open candidate file");
          return;
     }

     struct candidate can;

     while (fread(&can, sizeof(struct candidate), 1, candidateFile))
     {
          printf("ID : %d\n", can.id);
          printf("Name : %s\n", can.name);
          printf("Age : %d\n", can.age);
          printf("Degree : %s\n", can.degree);
          printf("Experience : %d\n", can.experience);
          printf("Skills : %s\n", can.skills);
          printf("Recommendation Letter : %d\n", can.recomendations);
          printf("\n");
     }

     fclose(candidateFile);
}

void call_menu(struct candidate *can , int n){
     
     int choice;

     menu:
          printf("To Print Candidates Informatio , Enter 1: \n");
          printf("To Remove The Candidates Who Does Not Have %s Skill, Enter 2: \n" , can->skills);
          printf("To Sort The Candidates As Per The Experience Greater Than %d , Enter 3: \n" , can->experience);
          printf("To Display Who Have A Recommendation Letter , Enter 4: \n");
          printf("To Add More Candidates , Enter 5: \n");
          printf("To Get Final List , Enter 6: \n");
          printf("To Exit , Enter 7: \n");

          printf("Enter Your Choice : ");
          scanf("%d", &choice);

          switch (choice)
          {
          case 1:
               display_candidate(n);
               goto menu;
          case 2:
               remove_skill();
               goto menu;
          case 3:
               sort_exp();
               goto menu;
          case 4:
               is_recommmend();
               goto menu;
          case 5:
               add();
               goto menu;
          case 6:
               final_list();
               return;
          case 7:
               return;
          default:
               remove_skill();
               sort_exp();
               final_list();
          }
}

int main()
{
     struct Interview interv;

     take_input_interview(&interv);
     display_interview(&interv);

     int n;
     printf("How Many Candidates Wants To Apply : ");
     scanf("%d", &n);
     struct candidate *can = malloc(n * sizeof(struct candidate));
     take_input_candidate(n, can);

     call_menu(&interv , n);
     free(can);

     return 0;
}
