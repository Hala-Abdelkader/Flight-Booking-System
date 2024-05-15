#include <stdio.h>
#include <stdlib.h>
#include "flight.h"
int main()
{
    int choice=0;
    ST_client ClientInfo;
    List L;
   char name[40];
    CreateList(&L);

    Tree clientTree;
    createEmptyTree(&clientTree);
   while(1)
    {
        main_menu();
        scanf("%d",&choice);

        if(choice == 1)
        {
            new_client(&ClientInfo,&L);
        }
        else if(choice == 2)
        {
            Client_Edit(&L);
        }
        else if(choice == 3)
        {
            ClassList(&L);
        }
        else if(choice == 4)
        {
            Free_Seats(&L);
        }
        else if(choice == 5)
        {
             delete_client(&ClientInfo,&L);
        }
        else if(choice == 6)
        {
            Client_List(&L);
        }
        else if(choice == 7)
        {
          new_client(&ClientInfo,&L);
          insertClient(&clientTree,ClientInfo);

        }
        else if(choice==8)
        {
          printf("\nEnter the name of the client you want to delete:");
          scanf(" %39[^\n]s",name);
          deleteClient(&clientTree,name);
        }
        else if(choice==9)
        {
          printf("\nEnter the name of the client:");
          scanf(" %39[^\n]s",name);
          TreeNode* foundNode =searchClientByName(clientTree.root,name);
          if (foundNode)
              {
                 printf("Client found:\n");
                 displayClientDetails(foundNode->data);
              }
             else
               {
                printf("Client with name %s not found.\n",name);
               }
        }
        else if(choice==10)
        {
            displayClientList(&clientTree);
        }
        else if(choice==11)
        {
            break;
        }
        else
        {
            main_menu();
            printf("\nWrong choice,Please enter (1:11)\n");
        }

    }
    DestroyList(&L);
    freeTree(&clientTree);
    return 0;
}
