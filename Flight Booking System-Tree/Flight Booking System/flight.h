#ifndef FLIGHT_H_INCLUDED
#define FLIGHT_H_INCLUDED
#define ListEntry ST_client
#define TreeEntry ST_client
#define MAX_CLIENTS 50

typedef enum class
{
    First=1,Business,Economy
}classType;

typedef struct SeatNode {
    char seatNumber[10];
    struct SeatNode* next;
} SeatNode;

typedef struct {
    SeatNode* head;
} SeatList;

typedef struct client
{
  char name[40];
  char ID[10];
  char BirthDate[11];
  char phoneNumber[12];
  char address[50];
  classType Class;
  char SeatNumber[3];
}ST_client;

typedef struct listnode{
	ListEntry entry;
	struct listnode*next;
}ListNode;

typedef struct List {
    ListNode* head;
    int Size;
} List;

typedef enum EN_clientError_t
{
	CORRECT_NAME,WRONG_NAME,ERROR,CLIENT_OK,WRONG_BIRTHDATE,CORRECT_BIRTHDATE,WRONG_ID,REPEATED_ID,CORRECT_ID,
	WRONG_PHONENUMBER,CORRECT_PHONENUMBER,RESERVED_SEAT,WRONG_SEAT,WRONG_CLASS
}EN_clientError_t;

/*BINARY SEARCH TREE*/

typedef struct node
{
    TreeEntry data;
    struct node *left;
    struct node *right;
}TreeNode;

typedef struct tree
{
    TreeNode* root;
}Tree;

void createEmptyTree(Tree*tree);
TreeNode* createNode(TreeEntry data);
void insertClient(Tree *tree, TreeEntry data);
void insertTreeRec(TreeNode **pt, TreeEntry data);
void deleteClient(Tree *tree, char* name);
TreeNode* deleteNode(TreeNode *root, char* name);
TreeNode* minValueNode(TreeNode* node);
void displayClientList(Tree *tree);
void inOrderTraversal(TreeNode *root);
void displayClientDetails(TreeEntry data);
TreeNode* searchClientByName(TreeNode* root, const char* name);
void freeTree(Tree*tree);
void freeTreeRec(TreeNode*root);

//************************************************************************//

void CreateList(List *pl);
void main_menu(void);
EN_clientError_t new_client(ST_client*ClientData,List*PL);
EN_clientError_t delete_client(ST_client*ClientData,List*PL);
void Client_Edit(List*PL);
void Client_List(List*PL);
void ClassList(List*PL);
void Free_Seats(List* PL);
void InsertList(int pos, ListEntry e, List *pl);
void DeleteList(int pos, ListEntry *pe, List *pl);
void Display(List*PL);
void DestroyList(List* PL);
int compareClients(const ST_client* client1,const ST_client* client2);
EN_clientError_t CheckClientName(ST_client*ClientData);
EN_clientError_t CheckClientID(ST_client*ClientData);
EN_clientError_t isIDExistsInList(const char newID[10], ListNode *head);
EN_clientError_t CheckClientBirthDate(ST_client*ClientData);
EN_clientError_t CheckClientPhoneNumber(ST_client*ClientData);
EN_clientError_t isSeatNumberReservedInClass(char* seatNumber, classType desiredClass, ListNode* head);
EN_clientError_t isSeatNumberValid(char* seatNumber);
void insertSeatInfo(ListNode** head, ST_client seat);
void printSeatNumbersAndNames(ListNode* head);
void bubbleSortSeatInfo(ListNode* head);
void insertReservedSeat(SeatList* seatList, const char* seatNumber);
EN_clientError_t isSeatReserved(SeatList* seatList, char row, int column);
void freeSeatList(SeatList* seatList);

#endif // FLIGHT_H_INCLUDED
