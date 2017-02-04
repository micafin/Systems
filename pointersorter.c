#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

/* global declaration of struct Node to be used for this assignment */
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

    Node* prev = malloc(sizeof(Node));
    prev = NULL;
    Node* curr = malloc(sizeof(Node));

    curr = head_of_list;
   
    while(curr!=NULL){

      int comp_length = 0;
          
      int curr_length = strlen(curr->word);
      int n_length = strlen(n->word);
               
          if(curr_length<n_length){
              comp_length = n_length;
          }else{
              comp_length = curr_length;
          }
         
          int comp=strncmp(n->word,curr->word,comp_length);
          
    if(comp>0){
      prev=curr;
      curr=curr->next;
      
      if(curr == NULL){
        n->next = curr;
        prev->next = n;
        return;
      }  
    }
    else if(comp==0){
         if(curr_length>n_length){
             n->next = curr;
             if(prev!=NULL)
                prev->next = n;
              else{
                head_of_list=n;
              }
             return;
         }else{
           n->next= curr->next;
           curr->next = n;
           return;
         }
    }else{
         
      if(prev==NULL){
        n->next=curr;
        head_of_list=n;
        return;
      }
      else{
        n->next=curr;
        prev->next=n; 
        return;
      } 
    }
  }
  
  

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
     the main method calls createNode upon finding a delimiter, passing to this function the index of the start of the portion of the string, and the index of the delimiter
     
   IN THE FUNCTION:
    
   1. Memory is allocated for the Node
   
   2. Node->word is set to equal the portion of the string passed in by using memcpy
 
   3. Node->next is initialized to null

   4. Node is returned
 
*/
Node * createNode(int start, int end, char * user_inputted_String){
  Node * created_node=malloc(sizeof(Node));
  created_node->word=(char*)malloc((end-start)*sizeof(char)); 
  created_node->word = memcpy(created_node->word,user_inputted_String+start,end-start); 

  if(!isalpha(created_node->word[0])){
    return NULL;
  }
  created_node->next=NULL;
  return created_node;

}

int main(int argc, char ** argv){
  
  if(argc!=2){
    fprintf(stderr,"ERROR: Incorrect amount of arguments entered.\n");
    return 1;
  }
  char * user_inputted_String=argv[1];
        
  int i=0,start=0;
  Node * n=(Node*)malloc(sizeof(Node));
 
  while(user_inputted_String[i]!='\0'){
    
    if(!isalpha(user_inputted_String[i])){

      n=createNode(start,i,user_inputted_String);

      if(start==0){
        head_of_list=n;
      }
      else{
        sort(n);
      }
      start=i+1;
    }
    i++;
          
          if(user_inputted_String[i]=='\0'){

             n=createNode(start,i,user_inputted_String);
             if(n!=NULL)
              sort(n);
             break;
           }
                  
  }
       
  printList(head_of_list);
  free(n);
  Node *temp=(Node*)malloc(sizeof(Node));
  while(head_of_list!=NULL){
    temp=head_of_list;
    head_of_list=temp->next;
    free(temp->word);
    free(temp);
  }
  return 0;

}