#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>


/* global declarations:
  

  "_Node" contains two variables: 
    1. A char* that points to the word stored in the Node
    2. A _Node* that points to the node immediately following the current Node

  Node * "head_of_list" 
    1. Initialized to null 
    2. This pointer is supposed to point to the head of the "master" list
    3. Once head_of_list refers to a Node, the rest of the "master list" can be accessed

*/
typedef struct _Node{
  char * word;
  struct _Node * next;
}Node;

Node * head_of_list = NULL;
//Node* prev = NULL;

/*"Sort as you go" function

  When a substring from the user-inputted string is found and needs to be placed into the linked list, a node is first created. 
  THEN:

    1. Sort function traverses the list, comparing the word within the current node in the LL with the word within the passed in Node
      (PRIOR TO TRAVERSAL: prev and head pointers of type Node* are declared to keep track of place in LL)
   
    2. Once the function reaches a node where the word comes AFTER the passed in word (i.e. if passed in word is "banana" and the LL contains apple -> cat, the function stops at cat)
   
    3. The passed in node containing the word to be inserted is set to point to the node that comes AFTER the given word, and then the previous node points to the current node.
    (i.e: apple -> cat [passed in word is banana] then stops at cat, banana -> cat, then apple -> banana, updating the LL to: apple -> banana -> cat)

*/
void sort(Node * n){
    printf("\n");
    printf("I have entered the sort function!\n");
    printf("\n");

    if(n->next == NULL){
       head_of_list = n;
       return;
    }
    int head_comp_length;
           
    int head_of_list_length = sizeof(head_of_list->word)/sizeof(char*);
          
    int n_length = sizeof(n->word)/sizeof(char*);
  
    if(head_of_list_length>n_length){
      head_comp_length = n_length;
    }else{
      head_comp_length = head_of_list_length;
    }
  
    int head_comp=strncmp(n->word,head_of_list->word, head_comp_length);
    if(head_comp <0){
       head_of_list = n;
       return;
    }else if(head_comp==0){
       if(head_of_list_length>n_length){
             n->next = head_of_list;
             head_of_list = n;
             return;
         }else{
           n->next= head_of_list-> next;
           head_of_list->next = n;
           return;
         } 
    
    }
    Node* prev = malloc(sizeof(Node));
    prev = NULL;
    Node* curr = malloc(sizeof(Node));
    //Node*temp = malloc(sizeof(Node));
    
    //temp = n;
    curr = head_of_list;
   
    while(curr!=NULL){
          printf("I HAVE ENTERED THE SORTING WHILE LOOP \n");
    //Node * second=pointer->next;
                //printf("Current Node: %s -->", curr->word);
    int comp_length = 0;
                //printf("I have initialized comp_length \n");
                //printf("This is the word whose length I'm going to find: %s \n", curr->word);
                //printf("This is the length of the above word: %d \n", strlen(curr->word));
          int curr_length = sizeof(curr->word)/sizeof(char*);
                //printf("I have initialized curr_length \n");
          
                //printf("I have initialized n_length \n");
                if(curr_length>n_length){
                   comp_length = n_length;
                }else{
                   comp_length = curr_length;
                }
                //printf("I have found the smallest length \n");
                //printf(" I am about to compare strings \n");
                int comp=strncmp(n->word,curr->word, comp_length);
                printf("I have compared %s and %s, and this is the number: %d \n", curr->word, n->word, comp);
          
    if(comp>0){
         prev=curr;
      curr=curr->next;
    }
    else if(comp==0){
         if(curr_length>n_length){
             n->next = curr;
             prev->next = n;
             return;
         }else{
           n->next= curr-> next;
           curr->next = n;
           return;
         }
    }else{
         
      if(prev==NULL){
        printf("Prev was set to null, so %s was inserted \n", n->word);
        
        n->next=curr;
                    return;
        //head=n;
      }
      
      else{
                    printf("%s comes after %s and before %s \n", n->word, prev->word, curr->word);
        n->next=curr;
        prev->next=n; 
                    return;
      } 
    }
  }
  if(curr == NULL){
       n->next = curr;
       prev->next = n;
       return;
  }   
  //head_of_list = curr;
  

}

/*Following method prints out the word in each node within the Linked List
 
*/ 

void printList(Node * start){

  while(start!=NULL){
    printf("%s\n",start->word);
    start=start->next;
  }
}

//separates words into linked list

/* Following method creates a Node with the indicated portion of the string
   
   From the main method: 
     the main method calls createNode upon finding a delimiter, passing to this function the index of the start of the portion of the string, and the the index of the delimiter
     
   IN THE FUNCTION:
    
   1. Memory is allocated for the Node
   
   2. Node->word is set to equal the portion of the string passed in by using strncpy
 
   3. Node->next is initialized to null

   4. Node is returned
 
*/
Node * createNode(int start, int end, char * user_inputted_String){
     //printf("I have entered createNode function! \n");
  Node * created_node=malloc(sizeof(Node));
  created_node->word=(char*)malloc((end-start)*sizeof(char)); //do we need to malloc this?
  created_node->word = strncpy(created_node->word,user_inputted_String+start,end-start);
     //printf("This is the word in the new node: %s \n", created_node->word);
        
  created_node->next=NULL;
     //printf("This is the created node: %s \n", created_node->word);
  return created_node;

}

int main(int argc, char ** argv){
  
  if(argc!=2){
    fprintf(stderr,"ERROR: Incorrect amount of arguments entered.\n");
    return 1;
  }
  char * user_inputted_String=argv[1];
        
  int i=0,start=0;
  //Node * prev=(Node*)malloc(sizeof(Node));
  Node * n=(Node*)malloc(sizeof(Node));
  
  while(user_inputted_String[i]!='\0'){
    //printf("hello");
          printf("This is the current character: %c \n", user_inputted_String[i]);
          printf("hello");
    if(!isalpha(user_inputted_String[i])){

               char * word = strncpy(word, user_inputted_String+start, i-start);
               //printf("I am attempting to create a node with this word: %s \n", word);
      n=createNode(start,i,user_inputted_String);
      printf("done \n");
      if(start==0){
        head_of_list=n;
                    sort(n);
      }
      else{
                    //printf("This is the head node: %s \n", head_of_list->word);
        n->next = head_of_list;
        //head_of_list = n;
        sort(n);
      }
      start=i+1;
      //prev=n;
    }
    i++;
          
          if(user_inputted_String[i]=='\0'){
             n=createNode(start,i,user_inputted_String);
             n->next = head_of_list;
             //head_of_list = n;
             sort(n);
             printf("This is the head node: %s \n", head_of_list->word);
           }
                  
    
  }
       
  printList(head_of_list);
  //free(prev);
  free(n);
  //free(head);
  return 0;

}