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

void take_input_interview(struct Interview *interv);
void display_interview();
void take_input_candidate(int n, struct candidate *can);
void display_candidate();
void call_menu(struct candidate *can, struct Interview interv, int n);
void remove_skill();
int get_skill(char skill[50]);
void experience(struct candidate *can, int n);
int get_experience(int experience);
void remove_experience();
void sort_experience(struct candidate *can, int n);
void add();
void add_candidate(int c);
void is_available(int id);
void update(struct candidate can);
void get_recomendation();
void get_final_list();

void take_input_interview(struct Interview *interv)
{
     printf("Enter The Total Number Of Required Employees: ");
     scanf("%d", &interv->total_emp);
     printf("Enter The Required Skills: ");
     scanf("%s", interv->require);
     printf("Enter The Minimum Required Experience: ");
     scanf("%d", &interv->experience);
     printf("Enter The Minimum Required Age: ");
     scanf("%d", &interv->age);

     FILE *inter = fopen("interview.txt", "w");
     if (inter == NULL)
     {
          perror("Couldn't open interview file");
          return;
     }
     fwrite(interv, sizeof(struct Interview), 1, inter);
     fclose(inter);
}

void display_interview()
{
     FILE *inter = fopen("interview.txt", "r");
     struct Interview interv;
     while (fread(&interv, sizeof(struct Interview), 1, inter))
     {
          printf("Total Number Of Required Employees: %d\n", interv.total_emp);
          printf("The Required Skills: %s\n", interv.require);
          printf("The Minimum Required Experience: %d\n", interv.experience);
          printf("The Minimum Required Age: %d\n", interv.age);
     }
     fclose(inter);
}

void take_input_candidate(int n, struct candidate *can)
{
     FILE *candidateFile = fopen("candidate.txt", "w");
     if (candidateFile == NULL)
     {
          perror("Couldn't open candidate file");
          return;
     }
     for (int i = 0; i < n; i++)
     {
          printf("Enter The Id Of Candidate %d: ", i + 1);
          scanf("%d", &can[i].id);
          printf("Enter The Name Of Candidate %d: ", i + 1);
          scanf("%s", can[i].name);
          printf("Enter The Age Of Candidate %d: ", i + 1);
          scanf("%d", &can[i].age);
          printf("Enter The Degree Of Candidate %d: ", i + 1);
          scanf("%s", can[i].degree);
          printf("Enter The Experience Of Candidate %d: ", i + 1);
          scanf("%d", &can[i].experience);
          printf("Enter The Skills Of Candidate %d: ", i + 1);
          scanf("%s", can[i].skills);
          printf("Have you A Recommendation Letter? If Yes Then Enter 1, Else Enter 0: ");
          scanf("%d", &can[i].recomendations);

          fwrite(&can[i], sizeof(struct candidate), 1, candidateFile);
     }
     fclose(candidateFile);
}

void display_candidate()
{
     FILE *candidateFile = fopen("candidate.txt", "r");
     if (candidateFile == NULL)
     {
          perror("Couldn't open candidate file");
          return;
     }
     struct candidate can;
     while (fread(&can, sizeof(struct candidate), 1, candidateFile))
     {
          printf("ID: %d\n", can.id);
          printf("Name: %s\n", can.name);
          printf("Age: %d\n", can.age);
          printf("Degree: %s\n", can.degree);
          printf("Experience: %d\n", can.experience);
          printf("Skills: %s\n", can.skills);
          printf("Recommendation Letter: %d\n", can.recomendations);
          printf("\n");
     }
     fclose(candidateFile);
}

int get_skill(char skill[50])
{

     FILE *interviewFile = fopen("interview.txt", "r");
     struct Interview interv;
     while (fread(&interv, sizeof(struct Interview), 1, interviewFile))
     {
          if (strcmp(interv.require, skill) == 0)
          {
               fclose(interviewFile);
               return 1;
          }
     }
     fclose(interviewFile);
     return 0;
}

void remove_skill()
{
     FILE *candidateFile = fopen("candidate.txt", "r");
     FILE *allcandidateFile = fopen("allCandidate.txt", "w");
     FILE *temp = fopen("temp.txt", "w");

     if (candidateFile == NULL || allcandidateFile == NULL || temp == NULL)
     {
          perror("Couldn't open File");
     }

     struct candidate can;
     struct candidate tmp;

     while (fread(&can, sizeof(struct candidate), 1, candidateFile))
     {
          if (get_skill(can.skills))
          {
               fwrite(&can, sizeof(struct candidate), 1, temp);
          }
          fwrite(&can, sizeof(struct candidate), 1, allcandidateFile);
     }

     fclose(candidateFile);
     fclose(temp);
     fclose(allcandidateFile);

     candidateFile = fopen("candidate.txt", "w");
     temp = fopen("temp.txt", "r");

     if (candidateFile == NULL || temp == NULL)
     {
          perror("Couldn't open File");
     }

     while (fread(&tmp, sizeof(struct candidate), 1, temp))
     {
          fwrite(&tmp, sizeof(struct candidate), 1, candidateFile);
     }

     fclose(candidateFile);
     fclose(temp);
}

int get_experience(int experience)
{
     FILE *interviewFile = fopen("interview.txt", "r");
     if (interviewFile == NULL)
     {
          perror("Couldn't open interview file");
          return 0; // Indicate failure
     }

     struct Interview interv;
     while (fread(&interv, sizeof(struct Interview), 1, interviewFile))
     {
          if (experience < interv.experience)
          {
               fclose(interviewFile);
               return 0; // Indicate experience requirement not met
          }
     }

     fclose(interviewFile);
     return 1; // Indicate experience requirement met
}

void remove_experience()
{
     FILE *candidateFile = fopen("candidate.txt", "r+");
     if (candidateFile == NULL)
     {
          perror("Couldn't open candidate file");
          return;
     }

     FILE *tempFile = fopen("temp.txt", "w");
     if (tempFile == NULL)
     {
          perror("Couldn't open temp file");
          fclose(candidateFile);
          return;
     }

     struct candidate can;

     while (fread(&can, sizeof(struct candidate), 1, candidateFile))
     {
          if (!get_experience(can.experience))
          {
               fwrite(&can, sizeof(struct candidate), 1, tempFile);
          }
     }

     fclose(tempFile);
     fclose(candidateFile);

     candidateFile = fopen("candidate.txt", "w");
     if (candidateFile == NULL)
     {
          perror("Couldn't open candidate file");
          return;
     }

     tempFile = fopen("temp.txt", "r");
     if (tempFile == NULL)
     {
          perror("Couldn't open temp file");
          fclose(candidateFile);
          return;
     }

     struct candidate tmp;
     while (fread(&tmp, sizeof(struct candidate), 1, tempFile))
     {
          fwrite(&tmp, sizeof(struct candidate), 1, candidateFile);
     }

     fclose(tempFile);
     fclose(candidateFile);
}

void sort_experience(struct candidate *can, int n)
{
     for (int i = 0; i < n - 1; i++)
     {
          for (int j = i + 1; j < n; j++)
          {
               if (can[i].experience > can[j].experience)
               {
                    struct candidate t = can[i];
                    can[i] = can[j];
                    can[j] = t;
               }
          }
     }
     FILE *candidateFile = fopen("candidate.txt", "w");
     if (candidateFile == NULL)
     {
          perror("Couldn't open candidate file");
          return;
     }

     for (int i = 0; i < n; i++)
     {
          fwrite(&can[i], sizeof(struct candidate), 1, candidateFile);
     }

     fclose(candidateFile);
}

void experience(struct candidate *can, int n)
{
     remove_experience();
     sort_experience(can, n);
}

void update(struct candidate can)
{
     FILE *maincandidateFile = fopen("candidate.txt", "a");
     fwrite(&can, sizeof(struct candidate), 1, maincandidateFile);
     fclose(maincandidateFile);
     return;
}

void is_available(int id)
{
     FILE *candidateFile = fopen("allCandidate.txt", "r");

     struct candidate can;

     while (fread(&can, sizeof(struct candidate), 1, candidateFile))
     {
          if (can.id == id)
          {
               update(can);
               fclose(candidateFile);
               return;
          }
     }

     fclose(candidateFile);
     printf("Candidate %d is not available", id);
     return;
}

void add_as_per_recomendation(int id)
{
     FILE *candidateFile = fopen("allCandidate.txt", "r");

     struct candidate can;

     while (fread(&can, sizeof(struct candidate), 1, candidateFile))
     {
          if (can.id == id && can.recomendations == 1)
          {
               update(can);
               fclose(candidateFile);
               return;
          }
     }

     fclose(candidateFile);
     printf("Candidate %d is not available Or the %d does not have recomendation letter\n", id, id);
     return;
}

void add_candidate(int c)
{
     printf("\n");
     int id;
     printf("Enter The ID Of The Candidate That You Want to Add\n");
     scanf("%d", &id);

     if (c == 0)
          is_available(id);
     else
          add_as_per_recomendation(id);
}

void get_recomendation()
{
     FILE *candidateFile = fopen("allCandidate.txt", "r");

     if (candidateFile == NULL)
          perror("File Couldn't be opened");

     struct candidate can;

     int count = 0;

     while (fread(&can, sizeof(struct candidate), 1, candidateFile))
     {
          if (can.recomendations == 1)
          {
               count++;
               printf("ID: %d\n", can.id);
               printf("Name: %s\n", can.name);
               printf("Age: %d\n", can.age);
               printf("Degree: %s\n", can.degree);
               printf("Experience: %d\n", can.experience);
               printf("Skills: %s\n", can.skills);
               printf("Recommendation Letter: %d\n", can.recomendations);
               printf("\n");
          }
     }

     if (count == 0)
          printf("\nNO ONE HAVE A RECOMENDATION LETTER\n");
     else
          add_candidate(1);
     fclose(candidateFile);
}

void add()
{
     FILE *candidateFile = fopen("allCandidate.txt", "r");

     if (candidateFile == NULL)
          perror("File Couldn't be opened");

     struct candidate can;
     while (fread(&can, sizeof(struct candidate), 1, candidateFile))
     {
          printf("ID: %d\n", can.id);
          printf("Name: %s\n", can.name);
          printf("Age: %d\n", can.age);
          printf("Degree: %s\n", can.degree);
          printf("Experience: %d\n", can.experience);
          printf("Skills: %s\n", can.skills);
          printf("Recommendation Letter: %d\n", can.recomendations);
          printf("\n");
     }
     fclose(candidateFile);

     int choice;
menu:
     printf("1 => To Add Any Candidate\n");
     printf("2 => To Add Candidate Who Have A Recomendation Letter\n");
     printf("3 => To Cancel\n");

     printf("Enter Your Choice : ");
     scanf("%d", &choice);

     switch (choice)
     {
     case 1:
          add_candidate(0);
          goto menu;
     case 2:
          get_recomendation();
          goto menu;
     case 3:
          return;
     default:
          break;
     }
}

void get_final_list()
{
     FILE *candidateFile = fopen("candidate.txt", "r");
     if (candidateFile == NULL)
          perror("File could not be opened");

     struct candidate can;

     while (fread(&can, sizeof(struct candidate), 1, candidateFile))
     {
          printf("ID: %d\n", can.id);
          printf("Name: %s\n", can.name);
          printf("Age: %d\n", can.age);
          printf("Degree: %s\n", can.degree);
          printf("Experience: %d\n", can.experience);
          printf("Skills: %s\n", can.skills);
          printf("Recommendation Letter: %d\n", can.recomendations);
          printf("\n");
     }
     fclose(candidateFile);
}

void call_menu(struct candidate *can, struct Interview interv, int n)
{
     int choice;
     do
     {
          printf("\n1. Print Candidates Information\n");
          printf("2. Remove Candidates Who Do Not Have %s Skill\n", interv.require);
          printf("3. Sort Candidates by Experience Greater Than %d\n", interv.experience);
          printf("4. Add More Candidates\n");
          printf("5. Get Final List\n");
          printf("6. Exit\n");

          printf("Enter Your Choice: ");
          scanf("%d", &choice);
          switch (choice)
          {
          case 1:
               printf("\n\n");
               display_candidate();
               printf("\n\n");
               break;
          case 2:
               remove_skill();
               break;
          case 3:
               experience(can, n);
               break;
          case 4:
               add();
               break;
          case 5:
               get_final_list();
               break;
          case 6:
               return;
               break;
          default:
               printf("Invalid choice! Please try again.\n");
               break;
          }
     } while (choice != 7);
}

int main()
{
     struct Interview interv;

     take_input_interview(&interv);
     display_interview();

     int n;
     printf("How Many Candidates Want To Apply: ");
     scanf("%d", &n);

     struct candidate *can = malloc(n * sizeof(struct candidate));
     if (can == NULL)
     {
          perror("Memory allocation failed\n");
          return 1;
     }

     take_input_candidate(n, can);

     call_menu(can, interv, n);
     free(can);

     return 0;
}
