#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <float.h>
#define MAX_SIZE 20
#define MIN_SIZE 8
#define ID_INPUT_SIZE 3
#define PASSWORD_SIZE 8

//buffer cleaner function
void ClearBuffer(void) {
   int cleaner;
   while((cleaner = getchar()) != '\n' && cleaner != EOF);
}

//account struct and type
typedef struct account {
   int ID;                                                              
   char username[MAX_SIZE + 2];                                                            
   char password[PASSWORD_SIZE + 2];                                                                           
   struct account *next;
}account;

//list of the accounts type 
typedef struct accounts_List{                                                                             
   account *first;                                                                           
}List;

//struct for the loadaccounts function work properly
typedef struct {
   List aux_list;
   int aux_id;
} loadResult;

//username char validation
int username_validation(char str[]) {
   for(int i = 0; str[i] != '\0';i++) {
      if(!isalpha(str[i])) {
         return 0;
      }
   }
   return 1;
}

//validates the ID input 
int ID_validation(char str[]) {
   for(int i = 0; str[i] != '\0';i++) {
      if(!isdigit(str[i])) {
         return 0;
      }
   }
   return 1;
}

//password int validation
int password_validation(char str[]) {
   for(int i = 0; str[i] != '\0'; i++) {
      if(!isdigit(str[i])) {
         return 0;
      }
   }
   return 1;
}

//function to validate an valid ID input for login
bool get_valid_ID(int *result) {
   char buffer[100];
   char *endptr;
   if(fgets(buffer, sizeof(buffer), stdin) == NULL) {
      return false;
   }

   long val = strtol(buffer, &endptr, 10);

   if(endptr == buffer) {
      return false;
   }

   while(*endptr != '\0') {
      if(!isspace((unsigned char)*endptr)) { 
      return false;
      }
   endptr++;
   }
   *result = (int)val;
   return true;
}

//creating a new account function 
void AccountInsertion(List *acc_list, int *global_id, char username[MAX_SIZE + 2], char password[PASSWORD_SIZE + 2]) {
   int true_id = *global_id + 1;
   *global_id = true_id;
   account *new = (account*)malloc(sizeof(account));                                          
   strcpy(new->username, username);
   strcpy(new->password, password);
   new->ID = true_id;
   new->next = acc_list->first;
   acc_list->first = new;
}

//print the entire list
void printAccountsList(List *acc_list) {
   account *current = acc_list->first;
   if(current == NULL) {
      printf("That list is empty.\n");
      return;
   } else {
      while(current != NULL) {
         printf("ID: %d\n", current->ID);
         printf("USERNAME: %s \n", current->username);
         printf("PASSWORD: %s \n\n", current->password);
         current = current->next;                                                           
      }
   }
   printf("\n\n");
}

//save the accounts in a file
void saveAccount(List *acc_list) {
   account *saved = acc_list->first;
   FILE *fptr;
   fptr = fopen("BankAccounts.txt", "a");
   if(fptr == NULL) {
      printf("Error: the accounts cant be saved...\n\n");
      return;
   }
   fprintf(fptr, "%d|%s|%s\n", saved->ID, saved->username, saved->password);
   fclose(fptr);
   fptr = NULL;
}

//load the accounts saved in the list of the system
loadResult loadAccounts(void) {
   char line[200];
   int id, highest_id;
   loadResult result;
   List temp_list;
   FILE *fptr;

   highest_id = 99;
   temp_list.first = NULL;

   fptr = fopen("BankAccounts.txt", "r");
   if(fptr == NULL) {
      printf("Error: the accounts cant be sucessfully loaded...\n\n");
   }
   while(fgets(line, sizeof(line), fptr) != NULL) {
      account *temp = malloc(sizeof(account));
      sscanf(line, "%d|%[^|]|%[^|]", &temp->ID, temp->username, temp->password);
      temp->next = temp_list.first;
      temp_list.first = temp;
      sscanf(line, "%d", &id);
      if(id > highest_id) {
         highest_id = id;
      }
   }
   fclose(fptr);
   fptr = NULL;

   result.aux_list = temp_list;
   result.aux_id = highest_id;

   return result;
}

bool Login_search(List *acc_list, int *login_id, char *username, char *password) {
   do {
      account *login_acc = malloc(sizeof(account));
      account *current = acc_list->first;
      strcpy(login_acc->username, username);
      strcpy(login_acc->password, password);
      login_acc->ID = *login_id;
      login_acc->next = NULL;
      if (current == NULL) {
         printf("Error: account not found.\n\n");
         return false;
      } else if (login_acc->ID != current->ID && strcmp(login_acc->username, current->username) != 0 && strcmp(login_acc->password, current->password) != 0) {
         current = current->next;
      } else {
         printf("Login successful!\n\n");
         return true;
      }
   } while(1);
}

//the main bank system starting
int main() {
   loadResult temp = loadAccounts();
   List acc_list = temp.aux_list;
   int global_id = temp.aux_id;

   char *BankAccountsFile = "BankAccounts.txt";
   char username[MAX_SIZE + 2], password[PASSWORD_SIZE + 2];
   int login_id, valid, too_long, menu_option, return_menu;
   size_t length = 0;

   bool valid_login;

   do {
      return_menu = 0;
      printf("____________________________________\n");
      printf("              BANK MENU             \n");
      printf("------------------------------------\n\n");
      printf("[1]Create new account.\n");
      printf("[2]Log in\n");
      printf("[3]Print accounts.\n");
      printf("[4]Exit.\n");
      printf("------------------------------------\n\n");
      printf("Select an option: \n\n");
      scanf("%d", &menu_option);
      ClearBuffer();
      if(menu_option < 1 || menu_option > 4) {
         printf("Error: invalid input\n\n");
      } else {
      switch(menu_option) {
      case 1:
      printf("Redirecting...\n\n");
      do {
         too_long = 0;
         printf("____________________________________\n");
         printf("          CREATING ACCOUNT          \n");
         printf("------------------------------------\n\n");
         printf("Enter your username:    \n");
         printf("------------------------------------\n\n");
         if(fgets(username, sizeof(username), stdin) == NULL) {
            printf("Error: an error with the stream occurred. \n\n");
            return 1;
         }
         if(strchr(username, '\n') == NULL) {
            too_long = 1;
            ClearBuffer();
            printf("Error: username cannot have more than %zu characters.\n\n", (size_t)MAX_SIZE);
         } else {
            username[strcspn(username, "\n")] = '\0';
         }
         length = strlen(username);   
         valid = username_validation(username);
         if(length >= MIN_SIZE && valid && !too_long) {
            printf("Valid username: %s", username);
            printf("\n\n");
         }
         if(!valid) {
            printf("Error: only characters can be used in your username. (A-Z, a-z)\n\n");
         }
         if(length < MIN_SIZE) {
            printf("Error: a username should have a minimum of 8 characters and a maximum of 20 characters.\n\n");
         }
      } while(!valid || length < MIN_SIZE || too_long);
      do {
         too_long = 0;
         printf("____________________________________\n");
         printf("          CREATING ACCOUNT          \n");
         printf("------------------------------------\n\n");
         printf("Enter your password:  \n");
         printf("------------------------------------\n\n");
         if(fgets(password, sizeof(password), stdin) == NULL) {
            printf("Error: an error occured with the stream. \n\n");
            return 1;
         }
         if(strchr(password, '\n') == NULL) {
            too_long = 1;
            ClearBuffer();
         } else {
            password[strcspn(password, "\n")] = '\0';
         }
         length = strlen(password);   
         valid = password_validation(password);
         if(length == PASSWORD_SIZE && valid && !too_long) {
            printf("Valid password: %s \n\n", password);
         }
         if(too_long) {
            printf("Error: the maximum digits the password can have is %zu.\n\n", (size_t)PASSWORD_SIZE);
         }
         if(!valid) {
            printf("Error: only numbers can be used in your password. (0-9)\n\n");
         }
         if(length < PASSWORD_SIZE) {
            printf("Error: password must have exactly 8 digits.\n\n");
         }
      } while(!valid || too_long || length < PASSWORD_SIZE);
      AccountInsertion(&acc_list, &global_id, username, password);
      saveAccount(&acc_list);
      break;
      case 2:
      printf("Redirecting...\n\n");
      do {
         printf("____________________________________\n");
         printf("                 LOGIN              \n");
         printf("------------------------------------\n\n");
         printf("Enter your ID:  \n");
         printf("------------------------------------\n\n");

         valid = get_valid_ID(&login_id);
         if(!valid) {
            printf("Error.\n\n");
         } else { 
            printf("Success.\n\n");
         }
      } while(!valid);
      do {
         too_long = 0;
         printf("____________________________________\n");
         printf("               LOGIN                \n");
         printf("------------------------------------\n\n");
         printf("Enter your username:    \n");
         printf("------------------------------------\n\n");
         if(fgets(username, sizeof(username), stdin) == NULL) {
            printf("Error: an error with the stream occurred. \n\n");
            return 1;
         }
         if(strchr(username, '\n') == NULL) {
            too_long = 1;
            ClearBuffer();
            printf("Error: username cannot have more than %zu characters.\n\n", (size_t)MAX_SIZE);
         } else {
            username[strcspn(username, "\n")] = '\0';
         }
         length = strlen(username);   
         valid = username_validation(username);
         if(length >= MIN_SIZE && valid && !too_long) {
            printf("Valid username: %s", username);
            printf("\n\n");
         }
         if(!valid) {
            printf("Error: only characters can be used in your username. (A-Z, a-z)\n\n");
         }
         if(length < MIN_SIZE) {
            printf("Error: a username should have a minimum of 8 characters and a maximum of 20 characters.\n\n");
         }
      } while(!valid || length < MIN_SIZE || too_long);
      do {
         too_long = 0;
         printf("____________________________________\n");
         printf("                 LOGIN              \n");
         printf("------------------------------------\n\n");
         printf("Enter your password:  \n");
         printf("------------------------------------\n\n");
         if(fgets(password, sizeof(password), stdin) == NULL) {
            printf("Error: an error occured with the stream. \n\n");
            return 1;
         }
         if(strchr(password, '\n') == NULL) {
            too_long = 1;
            ClearBuffer();
         } else {
            password[strcspn(password, "\n")] = '\0';
         }
         length = strlen(password);   
         valid = password_validation(password);
         if(length == PASSWORD_SIZE && valid && !too_long) {
            printf("Valid password: %s \n\n", password);
         }
         if(too_long) {
            printf("Error: the maximum digits the password can have is %zu.\n\n", (size_t)PASSWORD_SIZE);
         }
         if(!valid) {
            printf("Error: only numbers can be used in your password. (0-9)\n\n");
         }
         if(length < PASSWORD_SIZE) {
            printf("Error: password must have exactly 8 digits.\n\n");
         }
      } while(!valid || too_long || length < PASSWORD_SIZE);
      Login_search(&acc_list, &login_id, username, password);
      break;
      case 3:
      printf("Redirecting...\n\n");
      printAccountsList(&acc_list);
      break;
      case 4:
      printf("Exiting...\n\n");
      return 0;
      default:
      printf("Error: invalid option.\n\n");
      continue;
      }
      }
   } while (menu_option != 4);
}