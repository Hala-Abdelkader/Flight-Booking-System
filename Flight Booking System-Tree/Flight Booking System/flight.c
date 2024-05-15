#include "flight.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

//Function to display main menu of the system
void main_menu(void)
{
    printf("\t\t\t\tWelcome to our flight booking system\n\n");

       printf("The services we are providing are:\n\n");
       printf("1.Create new client.\n");
       printf("2.Update information of an existing client.\n");
       printf("3.View and manage classes.\n");
       printf("4.View free seats.\n");
       printf("5.Remove an existing client.\n");
       printf("6.View client list.\n");
       printf("7.Insert client into tree.\n");
       printf("8.Delete client from tree.\n");
       printf("9.Search in tree by ID.\n");
       printf("10.View client list using tree.\n");
       printf("11.Exit.\n");
       printf("\nPlease enter your choice: ");
}

//Function to create empty linked list
void CreateList(List* pl) {
    pl->head = NULL;
    pl->Size = 0;
}

//Function to validate the client name
EN_clientError_t CheckClientName(ST_client*ClientData)
{
    int i=0;
    EN_clientError_t x=CORRECT_NAME;
     for (i = 0; i < strlen(ClientData->name); i++)
		{
			if (!((ClientData->name[i] >= 'a' && ClientData->name[i] <= 'z')||(ClientData->name[i] >= 'A' && ClientData->name[i] <= 'Z') ||(ClientData->name[i] == ' ')))
			{
				x=WRONG_NAME;
				break;
			}
			else
            {
                  x=CORRECT_NAME;
            }
        }
        return x;
}

// Helper function to compare between client names to sort them in ascending order
int compareClients(const ST_client* client1,const ST_client* client2)
{
    return strcmp(client1->name, client2->name);
}

//Function to validate client ID
EN_clientError_t CheckClientID(ST_client* ClientData)
{
     int i=0;
    EN_clientError_t x = CORRECT_ID;

    for (i = 0; ClientData->ID[i] != '\0'; i++)
    {
        if (!isdigit(ClientData->ID[i]))
        {
            x = WRONG_ID;  // Non-digit character found
            break;
        }

        else
        {
            //no action needed
        }
    }
    return x;
}

//Function to check whether the ID exists or not
EN_clientError_t isIDExistsInList(const char newID[10], ListNode *head) {
    ListNode *pn = head;
    EN_clientError_t x = CORRECT_ID;

    while (pn != NULL) {
        if (strcmp(pn->entry.ID, newID) == 0) {
            x = REPEATED_ID;
            break;  // No need to continue searching if ID is repeated
        }
        pn = pn->next;
    }

    return x;
}

//Function to validate client Birthdate
EN_clientError_t CheckClientBirthDate(ST_client*ClientData)
{
    EN_clientError_t x=CORRECT_BIRTHDATE;
    if((strlen(ClientData->BirthDate)!=10)||(ClientData->BirthDate[2]!='/')||(ClientData->BirthDate[5]!='/'))
      {
          x=WRONG_BIRTHDATE;
      }
      else
        {
            //no action needed
        }
    if ((ClientData->BirthDate[0] !=  '0') && (ClientData->BirthDate[0] != '1') && (ClientData->BirthDate[0] != '2') && (ClientData->BirthDate[0] != '3'))
        {
		 x=WRONG_BIRTHDATE;
	    }
	    else
        {
            //no action needed
        }

    if (ClientData->BirthDate[0] == '3')
        {
		if ((ClientData->BirthDate[1] != '0') && (ClientData->BirthDate[1] != '1'))
            {
			 x=WRONG_BIRTHDATE;
		    }
        else
            {
            //no action needed
            }
        }
    else
        {
            //no action needed
        }

	if ((ClientData->BirthDate[3] != '0') && (ClientData->BirthDate[3] != '1'))
        {

		x=WRONG_BIRTHDATE;
	    }
    else
        {
            //no action needed
        }

	if (ClientData->BirthDate[3] == '1')
      {

	  if ((ClientData->BirthDate[4] != '0') && (ClientData->BirthDate[4] != '1') && (ClientData->BirthDate[4] != '2'))
        {

		x=WRONG_BIRTHDATE;
	    }
      else
        {
            //no action needed
        }
      }
    else
        {
            //no action needed
        }
      return x;
}

//Function to validate client phone number
EN_clientError_t CheckClientPhoneNumber(ST_client* ClientData) {
    int i=0;
    EN_clientError_t x = CORRECT_PHONENUMBER;

    for (i = 0; ClientData->phoneNumber[i] != '\0'; i++)
    {
        if (!isdigit(ClientData->phoneNumber[i]))
        {
            x = WRONG_PHONENUMBER;  // Non-digit character found
            break;
        }

        else
        {
            //no action needed
        }
    }

       if (x == CORRECT_PHONENUMBER && strlen(ClientData->phoneNumber) != 11)
         {
               x = WRONG_PHONENUMBER;  // Invalid length
         }

         else
         {
             //no action needed
         }

    return x;
}

//Helper function to check whether the seat number is reserved before or not
EN_clientError_t isSeatNumberReservedInClass(char* seatNumber, classType desiredClass, ListNode* head)
 {
    ListNode* pn = head;
    EN_clientError_t x=CLIENT_OK;

    while (pn!= NULL)
    {
        if (pn->entry.Class == desiredClass && strcmp(pn->entry.SeatNumber, seatNumber) == 0)
            {
                x=RESERVED_SEAT;
            }
       else
           {
             //no action needed
           }
        pn = pn->next;
    }
    return x;
}

//Function to validate the format of the seat number entered
EN_clientError_t isSeatNumberValid(char* seatNumber)
 {
     EN_clientError_t x=CLIENT_OK;
    if(!isupper(*seatNumber))
        {
               x=WRONG_SEAT;  // First character is not an uppercase letter
        }
        else
        {
            //no action needed
        }


    seatNumber++;

    // Check if the remaining characters are digits
    while (*seatNumber != '\0')
    {
        if (!isdigit(*seatNumber))
            {
               x=WRONG_SEAT;  // Not all remaining characters are digits
            }
        else
            {
               //no action needed
            }
        seatNumber++;
    }

    return x;
}

//Function to add new client
EN_clientError_t new_client(ST_client*ClientData,List*PL)
{
    system("cls");
    EN_clientError_t x;
    int numberofclients=PL->Size;
    int classChoice;
    ClientData->name[0]='\0';
    ClientData->ID[0]='\0';
    ClientData->BirthDate[0]= '\0';
    ClientData->phoneNumber[0]='\0';
    ClientData->address[0] = '\0';
    ClientData->SeatNumber[0] = '\0';


    if(numberofclients>=MAX_CLIENTS)
    {
        printf("Sorry,can't add more clients.\n");
        x=ERROR;
    }
    else
    {
        printf("\nEnter name of client:");
        scanf(" %39[^\n]",ClientData->name);

     if(CheckClientName(ClientData)!=CORRECT_NAME)
     {
         x=WRONG_NAME;
         printf("WRONG_NAME\n");
     }

     else
        {
         printf("\nEnter client ID:");
         scanf(" %s",ClientData->ID);
            if(CheckClientID(ClientData)!=CORRECT_ID)
          {
               x=WRONG_ID;
               printf("WRONG_ID\n");
          }

          else if (isIDExistsInList(ClientData->ID, PL->head)!=CORRECT_ID)
            {
               printf("Error: ID already exists.\n");
               x = REPEATED_ID;
            }
           else
            {
            printf("\nEnter client birthdate:");
            scanf(" %s",ClientData->BirthDate);
               if(CheckClientBirthDate(ClientData)!=CORRECT_BIRTHDATE)
              {
                 x=WRONG_BIRTHDATE;
                 printf("WRONG_BIRTHDATE\n");
              }

              else
              {
                  printf("\nEnter client phone number:");
                  scanf(" %s",ClientData->phoneNumber);
                   if(CheckClientPhoneNumber(ClientData)!=CORRECT_PHONENUMBER)
                 {
                   x=WRONG_PHONENUMBER;
                   printf("WRONG_PHONENUMBER\n");
                 }

                 else
                 {
                     printf("\nEnter client address:");
                     scanf(" %49[^\n]",ClientData->address);

                     printf("\nEnter class (1 for First, 2 for Business, 3 for Economy): ");
                     scanf("%d", &classChoice);

                        switch (classChoice)
                        {
                              case 1:
                                ClientData->Class = First;
                                break;
                              case 2:
                                ClientData->Class = Business;
                                break;
                              case 3:
                                ClientData->Class = Economy;
                                break;
                              default:
                                printf("\nYou entered wrong choice");
                                break;
                        }
                        if(classChoice==1||classChoice==2||classChoice==3)
                    {
                             printf("\nEnter client seat number:");
                             fflush(stdin);
                             scanf("%s",ClientData->SeatNumber);

                    if (isSeatNumberValid(ClientData->SeatNumber)!=CLIENT_OK)
                        {
                           printf("Error: Invalid seat number format. Use an uppercase letter followed by digits.\n");
                           x=WRONG_SEAT;
                        }
                     else if (isSeatNumberReservedInClass(ClientData->SeatNumber, ClientData->Class, PL->head)!=CLIENT_OK)
                        {
                           printf("Error: Seat number %s is already reserved in the desired class.\n", ClientData->SeatNumber);
                           x = RESERVED_SEAT;
                        }

                    else
                        {
                          InsertList(numberofclients,*ClientData,PL);
                          printf("\nNew client added successfully\n");
                          x = CLIENT_OK;
                        }
                    }
                    else
                        {
                            x=WRONG_CLASS;
                        }
                 }
              }
            }
        }
    }
    return x;
    }

//Function to insert node into the linked list
void InsertList(int pos, ListEntry e, List *pl)
{
   ListNode*p;
   ListNode*q;
   int i;
   p=(ListNode*)malloc(sizeof(ListNode));
   p->entry=e;
   p->next=NULL;

   if (pos==0)
    {
	p->next=pl->head;
	pl->head=p;
    }
   else
   {
	for(q=pl->head, i=0; i<pos-1; i++)
		{
           q=q->next;
		}
	p->next=q->next;
	q->next=p;
   }
   pl->Size++;
}
//Function to delete node from linked list
void DeleteList(int pos, ListEntry *pe, List *pl)
{
int i;
ListNode *q;
ListNode*tmp;
   if (pos==0)
   {
	*pe=pl->head->entry;
	tmp=pl->head->next;
	free(pl->head);
	pl->head=tmp;
   }
   else
   {
	for(q=pl->head, i=0; i<pos-1; i++)
		q=q->next;

	*pe=q->next->entry;
	tmp=q->next->next;
	free(q->next);
	q->next=tmp;
   }
   pl->Size--;
  }


//Function to delete client
EN_clientError_t delete_client(ST_client*ClientData,List*PL)
{
    system("cls");
    char id[10];
    int counter=0;
    ListNode *pn;
    EN_clientError_t x=ERROR;
  if(PL->Size>0)
    {
        printf("\n Enter the ID of the client you want to delete: ");
        fflush(stdin);
        scanf("%s",id);

        for(pn=PL->head;pn!=NULL;pn=pn->next)
        {
                     counter++;
                if(strcmp(pn->entry.ID,id)==0)
                {
                    printf("\nClient name you want to delete is: %s\n",pn->entry.name);
                    DeleteList(counter-1,&pn->entry,PL);
                    printf("\nClient deleted successfully\n");
                    x=CLIENT_OK;
                     break;
                }
                else
                {
                    //no action needed
                }
        }
        if (x==ERROR)
        {
             printf("\nYou entered wrong ID\n");
        }
        else
          {
             //no action needed
          }

    }
    else
    {
        printf("\nNo clients to delete\n");
        x=ERROR;
    }
        return x;
}

//Function to edit client information
void Client_Edit(List*PL)
{
    system("cls");
    char choice[20];
    char id[10];
    ListNode *pn;
    int classChoice;
     int idFound = 0; // Flag to track whether the ID was found
    if(PL->Size > 0)
    {
        printf("\n Enter Your ID: ");
        scanf("%s",id);
        for(pn=PL->head;pn!=NULL;pn=pn->next)
            {
              if(strcmp(pn->entry.ID,id)==0)
              {
                  idFound=1;
                printf("\n Welcome %s",pn->entry.name);
                printf("\nPlease choose which data you want to edit: ");
                scanf(" %19[^\n]",choice);
                    if(strcmp(choice,"Name")==0)
                    {
                        printf("\nEnter New Name:");
                        fflush(stdin);
                        scanf(" %39[^\n]",pn->entry.name);
                        break;
                    }
                    else if(strcmp(choice,"ID")==0)
                    {
                        printf("\nEnter New ID:");
                        scanf(" %s",pn->entry.ID);
                        break;
                    }
                    else if(strcmp(choice,"Address")==0)
                    {
                        printf("\nEnter New Address:");
                        scanf(" %49[^\n]",pn->entry.address);
                        break;
                    }
                    else if(strcmp(choice,"PhoneNumber")==0)
                    {
                        printf("\nEnter New Phone Number:");
                        scanf(" %s",pn->entry.phoneNumber);
                        break;
                    }
                    else if(strcmp(choice,"Birthdate")==0)
                    {
                        printf("\nEnter New Birthday:");
                        scanf(" %s",pn->entry.BirthDate);
                        break;
                    }
                    else if(strcmp(choice,"Class")==0)
                    {
                        printf("\nEnter New Class:");
                         scanf("%d", &classChoice);
                        switch (classChoice)
                        {
                             case 1:
                            pn->entry.Class=First;
                               break;
                             case 2:
                            pn->entry.Class=Business;
                               break;
                             case 3:
                            pn->entry.Class=Economy;
                              break;
                             default:
                            printf("\nYou entered wrong class\n");
                            break;
                        }
                        break;
                    }
                    else if(strcmp(choice,"SeatNumber")==0)
                    {
                        printf("\nEnter New Seat Number:");
                        scanf("%s",pn->entry.SeatNumber);
                        break;
                    }
                    else
                    {
                        printf("\nYou entered wrong choice\n");
                        break;
                    }
                }
                else
                 {
                    //no action needed
                 }
            }
            if (!idFound)
                {
                    printf("\n You entered wrong ID\n");
                }
            else
                {
                    //no action needed
                }
        }
        else
        {
            printf("\n There are no clients to edit\n");
        }

}

//Function to display clients in the linked list in ascending order according to their names
void Client_List(List*PL)
 {
     system("cls");
    ListNode *p;
    ListNode *q;
    ST_client client1;

    if (PL->head == NULL)
        {
        printf("\nEmpty list, there is nothing to be sorted");
        }
    else
        {
          //no action needed
        }

    for (p=PL->head;p->next!=NULL;p=p->next)
    {
        for (q=p->next;q!= NULL;q=q->next)
        {
            if (compareClients(&(p->entry),&(q->entry)) > 0)
              {
                client1=p->entry;
                p->entry=q->entry;
                q->entry=client1;
              }
            else
              {
                //no action needed
              }
        }
    }
    Display(PL);
}

//Function to display the seats reserved in each class sorted in ascending order according to the seat number
void ClassList(List *PL) {
    system("cls");
    ListNode* pn = PL->head;
    ListNode* firstClassHead = NULL;
    ListNode* businessClassHead = NULL;
    ListNode* economyClassHead = NULL;

    int firstClassCount = 0;
    int businessClassCount = 0;
    int economyClassCount = 0;

    while (pn != NULL)
    {
        switch (pn->entry.Class)
         {
            case First:
                insertSeatInfo(&firstClassHead, pn->entry);
                firstClassCount++;
                break;
            case Business:
                insertSeatInfo(&businessClassHead, pn->entry);
                businessClassCount++;
                break;
            case Economy:
                insertSeatInfo(&economyClassHead, pn->entry);
                economyClassCount++;
                break;
            default:
                break;
        }

        pn = pn->next;
    }

    // Sort seat numbers in each class
    bubbleSortSeatInfo(firstClassHead);
    bubbleSortSeatInfo(businessClassHead);
    bubbleSortSeatInfo(economyClassHead);

    // Print number of seats reserved in each class
    printf("\nNumber of seats reserved in First class: %d\n", firstClassCount);
    printf("Seat numbers and client names in First class:\n");
    printSeatNumbersAndNames(firstClassHead);
    printf("\n");

    printf("\nNumber of seats reserved in Business class: %d\n", businessClassCount);
    printf("Seat numbers and client names in Business class:\n");
    printSeatNumbersAndNames(businessClassHead);
    printf("\n");

    printf("\nNumber of seats reserved in Economy class: %d\n", economyClassCount);
    printf("Seat numbers and client names in Economy class:\n");
    printSeatNumbersAndNames(economyClassHead);
    printf("\n");
}

//Function to display all client information
void Display(List*PL)
{
     const char* className;
     ListNode *pn=PL->head;
   while(pn)
  {
    printf("\nName of client:%s",pn->entry.name);
    printf("\nClient ID:%s",pn->entry.ID);
    printf("\nClient Birthdate:%s",pn->entry.BirthDate);
    printf("\nClient Phone number:%s",pn->entry.phoneNumber);
    printf("\nClient Address:%s",pn->entry.address);
        switch (pn->entry.Class)
         {
            case First:
                className = "First";
                break;
            case Business:
                className = "Business";
                break;
            case Economy:
                className = "Economy";
                break;
            default:
                className = "Unknown";
                break;
        }

        printf("\nClient Class:%s", className);

    printf("\nClient Seat number:%s",pn->entry.SeatNumber);
    printf("\n-----------------------------------------------------\n");
    pn=pn->next;
  }
}

//Function to free the allocated memory for the linked list
void DestroyList(List* PL)
{
    ListNode* pn = PL->head;
    ListNode* next;

    while (pn != NULL)
    {
        next = pn->next;
        free(pn);
        pn = next;
    }
    PL->head = NULL;
    PL->Size = 0;
}

//Helper function to insert the seat number
void insertSeatInfo(ListNode** head, ST_client seat)
{
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    if (newNode == NULL)
    {
        // Handle memory allocation failure
        printf("Memory allocation failed\n");
        exit(0);
    }
    else
    {
         newNode->entry = seat;
         newNode->next = *head;
         *head = newNode;
    }
}

//Helper function to print the seat number and its corresponding client name
void printSeatNumbersAndNames(ListNode* head)
{
    ListNode* current = head;
    while (current != NULL)
    {
        printf("Seat Number: %s, Client Name: %s\n", current->entry.SeatNumber, current->entry.name);
        current = current->next;
    }
}

//Helper function to sort the seat numbers in ascending order
void bubbleSortSeatInfo(ListNode* head) {
    int swapped;
    ListNode* ptr1;
    ListNode* lptr = NULL;

    if (head == NULL || head->next == NULL)
    {
        printf("\nEmpty list or a list with a single element, nothing to be sorted");
        return;
    }
    else
    {
        do {
            swapped = 0;
            ptr1 = head;

            while (ptr1->next != lptr)
            {
                // Compare seat numbers and swap if necessary
                if (strcmp(ptr1->entry.SeatNumber, ptr1->next->entry.SeatNumber) > 0)
                {
                    ST_client temp = ptr1->entry;
                    ptr1->entry = ptr1->next->entry;
                    ptr1->next->entry = temp;
                    swapped = 1;
                }
                else
                {
                    // No need to swap, move to the next node
                    ptr1 = ptr1->next;
                }
            }
            lptr = ptr1;
        } while (swapped);
    }
}
//Function to display the free seats
void Free_Seats(List* PL)
{
    system("cls");

    // Initialize seat lists for each class
    SeatList firstClassSeats = { .head = NULL };
    SeatList businessClassSeats = { .head = NULL };
    SeatList economyClassSeats = { .head = NULL };
    ListNode* pn = PL->head;
    char row;
    int column;
    int i;
    while (pn != NULL)
    {
        sscanf(pn->entry.SeatNumber, "%c%d", &row, &column);

        switch (pn->entry.Class)
        {
            case First:
                insertReservedSeat(&firstClassSeats, pn->entry.SeatNumber);
                break;
            case Business:
                insertReservedSeat(&businessClassSeats, pn->entry.SeatNumber);
                break;
            case Economy:
                insertReservedSeat(&economyClassSeats, pn->entry.SeatNumber);
                break;
            default:
                // Handle unexpected class value
                break;
        }

        pn = pn->next;
    }

    // Display free seats
    printf("Free seats in First class: ");
    for (i = 1; i <= MAX_CLIENTS; i++)
    {
        row = 'A' + (i - 1) / 6;
        column = (i - 1) % 6 + 1;

        if (isSeatReserved(&firstClassSeats, row, column)!=RESERVED_SEAT)
        {
            printf("%c%d ", row, column);
        }
        else
        {
            //no action needed
        }
    }
    printf("\n");

    printf("Free seats in Business class: ");
    for (i = 1; i <= MAX_CLIENTS; i++)
    {
        row = 'A' + (i - 1) / 6;
        column = (i - 1) % 6 + 1;

        if (isSeatReserved(&businessClassSeats, row, column)!=RESERVED_SEAT)
        {
            printf("%c%d ", row, column);
        }
        else
        {
            //no action needed
        }
    }
    printf("\n");

    printf("Free seats in Economy class: ");
    for (i = 1; i <= MAX_CLIENTS; i++)
    {
        row = 'A' + (i - 1) / 6;
        column = (i - 1) % 6 + 1;

        if (isSeatReserved(&economyClassSeats, row, column)!=RESERVED_SEAT)
        {
            printf("%c%d ", row, column);
        }
        else
        {
            //no action needed
        }
    }
    printf("\n");

    // Cleanup: Free allocated memory
    freeSeatList(&firstClassSeats);
    freeSeatList(&businessClassSeats);
    freeSeatList(&economyClassSeats);
}


//Helper function to insert the reserved seat into the seat list
void insertReservedSeat(SeatList* seatList, const char* seatNumber) {
    SeatNode* newNode = (SeatNode*)malloc(sizeof(SeatNode));
    if (newNode == NULL)
    {
        // Handle memory allocation failure
        printf("Memory allocation failed\n");
        exit(0);
    }
    else
    {
         // Copy the seatNumber into the newNode
      snprintf(newNode->seatNumber, sizeof(newNode->seatNumber), "%s", seatNumber);
      newNode->next = seatList->head;
      seatList->head = newNode;
    }
}

//Helper function to check if the seat is reserved in specific class or not in the seat list
EN_clientError_t isSeatReserved(SeatList* seatList, char row, int column)
{
    SeatNode* current = seatList->head;
    EN_clientError_t x=CLIENT_OK;
    char currentRow;
    int currentColumn;
    while (current != NULL) {
        // Extract row and column from the seatNumber
        sscanf(current->seatNumber, "%c%d", &currentRow, &currentColumn);

        // Compare extracted row and column with the provided row and column
        if (currentRow == row && currentColumn == column)
        {
            x=RESERVED_SEAT; // Seat is reserved
        }
        else
        {
            //no action needed
        }

        current = current->next;
    }

    return x; // Seat is free
}

//Helper function to free the memory allocated for the seat list
void freeSeatList(SeatList* seatList)
{
    SeatNode* current = seatList->head;
    SeatNode* next;
    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
    seatList->head = NULL;
}


/*Tree Functions*/
//Function to create empty tree
void createEmptyTree(Tree*tree)
{
    tree->root=NULL;
}
//Function to create Node in the tree
TreeNode* createNode(TreeEntry data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode != NULL)
    {
        newNode->data = data;
        newNode->left = NULL;
        newNode->right = NULL;
    }
    else
    {
        //no action needed
    }
    return newNode;
}
//Function to insert client in the tree
void insertClient(Tree *tree,TreeEntry data)
{
    insertTreeRec(&(tree->root), data);
    printf("\nClient added using tree\n");
}
//Function to insert in tree recursively
void insertTreeRec(TreeNode **pt, TreeEntry data)
{
    if (!*pt)
      {
        *pt = createNode(data);
      }
    else if (strcmp(data.name, (*pt)->data.name) < 0)
          {
        insertTreeRec(&(*pt)->left, data);
          }
    else
       {
        insertTreeRec(&(*pt)->right, data);
       }
}

// Function to delete a client from the BST
void deleteClient(Tree *tree, char* name)
{
    tree->root = deleteNode(tree->root, name);
     printf("\nClient deleted using tree\n");
}

// Recursive function to delete a node from the BST
TreeNode* deleteNode(TreeNode *root, char* name)
{
    TreeNode* result = root;
    TreeNode *temp = NULL;

    if (root)
    {
        if (strcmp(name, root->data.name) < 0)
        {
            root->left = deleteNode(root->left, name);
        }
        else if (strcmp(name, root->data.name) > 0)
        {
            root->right = deleteNode(root->right, name);
        }
        else
        {
            if (!root->left)
            {
                temp = root->right;
                free(root);
                result = temp;
            }
            else if (!root->right)
            {
                temp = root->left;
                free(root);
                result = temp;
            }
            else
            {
                temp = minValueNode(root->right);
                root->data = temp->data;
                root->right = deleteNode(root->right, temp->data.name);
            }
        }
    }

    return result;
}


// Helper function to find the node with the minimum value
TreeNode* minValueNode(TreeNode* node)
{
    TreeNode* current = node;
    while (current->left != NULL)
    {
        current = current->left;
    }
    return current;
}

// Function to display the client list (in-order traversal)
void displayClientList(Tree *tree) {
    printf("Client List:\n");
    inOrderTraversal(tree->root);
}

// In-order traversal for displaying the client list
void inOrderTraversal(TreeNode *root)
{
    if (root != NULL)
    {
        inOrderTraversal(root->left);
        displayClientDetails(root->data);
        inOrderTraversal(root->right);
    }
    else
        {
            //no action needed
        }
}

// Helper function to display client details
void displayClientDetails(TreeEntry data)
{
const char* className;
    printf("\nClient Name: %s", data.name);
    printf("\nClient ID:%s",data.ID);
    printf("\nClient Birthdate:%s",data.BirthDate);
    printf("\nClient Phone number:%s",data.phoneNumber);
    printf("\nClient Address:%s",data.address);
     switch (data.Class)
        {
            case First:
                className = "First";
                break;
            case Business:
                className = "Business";
                break;
            case Economy:
                className = "Economy";
                break;
            default:
                className = "Unknown";
                break;
        }

        printf("\nClient Class:%s", className);
    printf("\nClient Seat number:%s",data.SeatNumber);
    printf("\n-----------------------------------------------------\n");
    printf("\n");
}

//Function to search in BST by client name
TreeNode* searchClientByName(TreeNode* root, const char* name)
{
    TreeNode* result = NULL;
    int compareResult;

    while (root)
    {
        compareResult = strcmp(name, root->data.name);

        if (compareResult == 0)
        {
            result = root;  // Name found in the tree
            break;
        }
        else if (compareResult < 0)
        {
            root = root->left;
        }
        else
        {
            root = root->right;
        }
    }

    return result;  // Name not found in the tree or found and stored in result
}
// Function to free allocated memory in the BST
void freeTree(Tree*tree)
{
    freeTreeRec(tree->root);
    tree->root=NULL;
}

//function to free memory allocated in BST recursively
void freeTreeRec(TreeNode*root)
{
    if(root!=NULL)
    {
        freeTreeRec(root->left);
        freeTreeRec(root->right);
        free(root);
    }
    else
    {
        //no action needed
    }
}




