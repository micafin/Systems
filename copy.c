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

Node* head_of_list= NULL;
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
void sort(Node * passed_in_node){
  
  //dynamic allocation of memory for prev and curr pointers to be used during traversal of the LL

  Node* prev = (Node*)malloc(sizeof(Node));
  prev = NULL;
  Node* curr = (Node*)malloc(sizeof(Node)); //curr = current node in the LL
  
  //curr intiialized to the head_of_list

 
  if(head_of_list==NULL){
        head_of_list=passed_in_node;
        return;
    }
  curr = head_of_list;
  //entering while loop to traverse the existing LL
  while(curr!=NULL){
    
    int comp_length = 0; 
    
    //following code checks to see which word length is smaller between passed_in_node and current node in LL in order to set as "size" in strncmp in order to avoid going out of bounds 
    int curr_length = strlen(curr->word);
    int passed_in_node_length = strlen(passed_in_node->word);
  
    if(curr_length<passed_in_node_length){
      comp_length = passed_in_node_length;
    }

    else{
      comp_length = curr_length;
    }
               
    int comp=strncmp(passed_in_node->word,curr->word, comp_length);
    
    /*following lines of code check to see in what order are the words given in: 
        1. if comp>0, then that means that the passed_in_node->word comes AFTER the curr->word 
            -If this is the case, then the traversal of the LL continues

        2. if comp==0, then that means that both of the words are equal UP TO comp_length
            -further checks are made to see order of the words based on word length;

        3. if comp <0, then that means that passed_in_node->word is supposed to come BEFORE curr->word


    */
    if(comp>0){ 
      prev=curr;
      curr=curr->next;
      
      if(curr == NULL){ // checks to see if end of the LL is reached
        passed_in_node->next = curr;
        prev->next = passed_in_node;
        return;
      } 
    }
    else if(comp==0){
      if(curr_length>passed_in_node_length){
        passed_in_node->next = curr;
        
        if(prev!=NULL){//checks to see where in the LL we are
          prev->next =passed_in_node;
        }
        else{//at head of list
          head_of_list=passed_in_node;
        }
        
        return;
      }
      else{
        passed_in_node->next= curr-> next;
        curr->next = passed_in_node;
        return;
      }
    }else{
         
      if(prev==NULL){// if prev ==NULL, then we are at head of the list
        passed_in_node->next=curr;
        head_of_list =passed_in_node;
        return;
      }
      
      else{
        passed_in_node->next=curr;
        prev->next=passed_in_node; 
        return;
      } 
    }
  }

}

/*Following method prints out the word in each node within the Linked List
  
  simple traversal of the LL, using the head_of_list as the starting point
 
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
    
   1. Memory is allocated for the Node and the node's word
   
   2. Node->word is set to equal the portion of the string passed in by using strncpy
 
   3. Node->next is initialized to null

   4. Node is returned
 
*/
Node * createNode(int start, int end, char * user_inputted_String){

  Node * created_node=(Node*)malloc(sizeof(Node));
  
  created_node->word=(char*)malloc((end-start)*sizeof(char)); 
  
  created_node->word = memcpy(created_node->word,user_inputted_String+start,end-start);
 
  if(!isalpha(created_node->word[0])){ // check to see if a node was created with null entries in the word variable --> possibility when a string of only delimiters are passed
    return NULL;
  }
  
  created_node->next=NULL;
     
  return created_node;

}

int main(int argc, char ** argv){
  
  // If there are more than two arguments - the name of the exectuable file (./____ and " ...  ") then we assume that this is an error and as such, exit immediately
  if(argc!=2){
    fprintf(stderr,"ERROR: Incorrect amount of arguments entered.\n");
    return 1;
  }
  
  char * user_inputted_String=argv[1];
        
  int iterator=0,start=0;
  
  Node * new_node=(Node*)malloc(sizeof(Node));
  
  while(user_inputted_String[iterator]!='\0'){
    
    if(!isalpha(user_inputted_String[iterator])){

      new_node=createNode(start,iterator,user_inputted_String);
      if(new_node!=NULL){
        sort(new_node);
      }

      start=iterator+1;
      
    }
    iterator++;
          
    if(user_inputted_String[iterator]=='\0'){
      
      new_node=createNode(start,iterator,user_inputted_String);
      
      if(new_node!=NULL){
        sort(new_node);
      }
      break;
    }
                  
    
  }
  
  printList(head_of_list);
 
  free(new_node);

  while(head_of_list!=NULL){
     Node*temp = (Node*) malloc(sizeof(Node));
     temp = head_of_list;
     head_of_list = temp->next;
     free(temp->word);
     free(temp);
  }
  
  return 0;

}
