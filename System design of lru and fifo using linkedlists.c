#include <stdio.h>
#include <stdlib.h>
#include <string.h>             //necessary packages are imported.
#include <stdbool.h>
#include <time.h>

struct node_class{
    char page_number[150];    
    char mode[10];
    char isdirty;		              //boolean isdirty bit is created to keep track of controversy modes when they are inserting. And this bit is used later in updating writes.			
    struct node_class *prev;         // a struct class is created which stores page address, read or write mode, and 2 pointers previous and next;
    struct node_class *next;
};

struct node_class *head;  // head pointer is created to mark first node of LinkedList and also to delete from starting.
struct node_class *tail;  // tail pointer is created to mark last node of LinkedList and also used for adding a new node.
int size  = 0; //global size pointer is initiated to check for current LinkedList to not to exceed frames given in command line.
int reads = 0;  //global reads and writes are created for keeping reading and writing count.
int writes= 0;





void deleteblock(struct node_class * block){    //A linkedlist node is deleted here once we have found in linkedlist, but generally we will be having 4 cases which are taken in to consideration here to avoid segmentation faults.
    struct node_class* dup1 = block;
    if(block->prev != NULL && block->next != NULL){               
        struct node_class* dup2 = dup1->next;                 //case 1- when a block is in middle of the linkedlist.
        struct node_class* dup0 = dup1->prev;                 //what will be done here is current block prev is connected to current's block next and current block's next's prev is connected to current block's prev.
        dup2->prev = dup0;
        dup0->next = dup2;
        free(dup1);
    }
    else if (block->prev == NULL && block->next!= NULL) {			
         struct node_class* dup = block;
	     head  = head->next;
	     block = block->next;                                  //case-2 when block is in first node of linkedlist, then head is shifted to next node making current block net to null.
	     block->prev = NULL;
         free(dup);
	}
        else if (block->prev != NULL && block->next== NULL) {			
	     tail = tail->prev;
	     struct node_class*  dup= block->prev;
             dup->next = NULL;                                 //case-3 when block is the last node tail is shifted to previous node and connection between them is disconnected by making it to null.
             free(block);
        }else{									
	     tail = NULL;
	     head = NULL;                                         //case-4 when linkedlist is empty .
	     block =NULL;
	    free(block);
	}
        size--;				//as we deleted one node reducing the size of linkedlist.
        //Note :- free(linkedlist block) is used to disconnect and making node disappear.
}

struct node_class* dequing(){
    struct node_class* dup = head;
    head= head->next;
    if(head!=NULL){
        head->prev = NULL;
    }                                                   //generally dequing is done here where it is follows Queue principle of dequing.
    else{                                               //so logic implemented here is first node next to which head is shifted and previous edge is made to null.
        tail = NULL;
    }
    size--; // as we removed first node decrementing one node.
    return dup;
}





bool search_in_LRU(struct node_class * block, char address[]){    // This module is designed to search when lru algorithm is implemented it returns boolean when element is found.
    struct node_class* dup = head;
    bool isFound =false;                                          //logic implemented here is we iterate over a linkedlist and search for the matching address .
    while(dup != NULL){
        if(strcmp(dup->page_number,address)==0){
            deleteblock(dup);           //if we find a node that is matched we will remove it as in Lru it will be most recent, so calling that function which implements deletion. 
            isFound = true;
            if(dup->isdirty=='Y'){
                block->isdirty = 'Y';           //if we removed block dirtybit is true then new block which matched removed block's address bit is also set to made true.              
            }
            if(tail == NULL){
                head = block;
                tail = block;     // Now in LRU this most recent block is added at first of linkedlist and these lines implement that logic.
            }
            else{							
		        tail->next = block;
		        tail->next->prev = tail;
		        tail = tail->next;
            }
            size++; //again incrementing size as we added most recent to first.
            break;

        }
        dup = dup->next;
    }
    return isFound; // returning boolean value of foundness of block.
}

bool search_in_FIFO(struct node_class* block, char address[]){  //here this module implements search of fifo linkedlist.
    struct node_class* dup = head;
    bool isFound = false;
    while(dup != NULL){
        if(strcmp(dup->page_number,address)==0){         //here it is different from lru we won't remove and add at first instead we search normally .
            if(block->isdirty == 'Y'){
                dup->isdirty ='N';
            }
            isFound = true;	
            break;
        }
       
        dup = dup->next;  //linkedlist is iterated untill we find a match.
    }
    return isFound; //returns booleaness of node whether it is present or not.
    
}



void LRU_cache(char address[], char type[],int no_of_frames){
    struct node_class * newEntry = malloc(sizeof(struct node_class)); //A new node with incoming address, mode is created using malloc.
     int length = strlen(address); // taking length of address
     //printf("Length of the string: %d\n", length);
	if(length==8){ //only this process is done to big 2 testcases.
		unsigned int x =0;
		sscanf(address, "%x", &x);
		unsigned int size_of_page =4096;                  //this is the process of mapping a virtual adress to orginal page number and this is done by converting into hexadecimal and dividing by 4096
		unsigned int pageNumber = x/ size_of_page;
		sprintf(address,"%x",pageNumber); //address is modified to the result of page number obtained from above
	}

    strcpy(newEntry->page_number,address); 
    strcpy(newEntry->mode,type);  // taking the page number and modes from parameters to new node.
    if(type[0] == 'W'){							
         newEntry->isdirty = 'Y';
     }                                 //depending on the mode dirtybit is set.
     else{
	    newEntry->isdirty = 'N';
	}
    newEntry->prev = NULL;
    newEntry->next = NULL;

    //struct node_class* dup = head;
    bool found = search_in_LRU(newEntry, address); //this node and address is passed to check whether it is present in linkedlist or not.

    if(found==false){
        if(no_of_frames == size){
            struct node_class* removed_block = dequing(); //if found and capacity is full we remove from first.

            if(removed_block->isdirty =='Y'){
                writes++;                          //write is incremented only when removed block dirtybit is true.
            }
            free(removed_block);
        }
        if(tail == NULL){
                head = newEntry;
                tail = newEntry;
        }
            else{							
		        tail->next = newEntry;
		        tail->next->prev = tail;    //new node is added to the linkedlist.
		        tail = tail->next;
            }
            size++;
        reads++;
    }
}


void FIFO_cache(char address[], char type[],int no_of_frames){   
    struct node_class * newEntry = malloc(sizeof(struct node_class)); ///A new node with incoming address, mode is created using malloc.
    int length = strlen(address); // taking length of address
     //printf("Length of the string: %d\n", length);
	if(length==8){
		unsigned int x =0;
		sscanf(address, "%x", &x);                        
		unsigned int size_of_page =4096;                            //this is the process of mapping a virtual adress to orginal page number and this is done by converting into hexadecimal and dividing by 4096
		unsigned int pageNumber = x/ size_of_page;
		sprintf(address,"%x",pageNumber);                //address is modified to the result of page number obtained from above
    }
    strcpy(newEntry->page_number,address);  // taking the page number and modes from parameters to new node.
    strcpy(newEntry->mode,type);
    if(type[0] == 'W'){							
        newEntry->isdirty = 'Y';
     }                                         
    else{                               //depending on the mode dirtybit is set.
	    newEntry->isdirty = 'N';
	}
    newEntry->prev = NULL;
    newEntry->next = NULL;

    bool found = search_in_FIFO(newEntry, address);  //this node and address is passed to check whether it is present in linkedlist or not.
    if(found==false){
        if(no_of_frames == size){
            struct node_class* removed_block = dequing();  //if found and capacity is full we remove from first.
            if(removed_block->isdirty=='Y'){                           
                writes++;                               //write is incremented only when removed block dirtybit is true.
            }
            free(removed_block);

        }
        if(tail == NULL){
                head = newEntry;
                tail = newEntry;
        }
            else{							      
		        tail->next = newEntry;                   //new node is added to the linkedlist.
		        tail->next->prev = tail;
		        tail = tail->next;
            }
            size++;
            reads++;

    }

}

    

    




int main(int argc, char *argv[]){
    head = NULL;
    tail = NULL;
    int frames=atoi(argv[2]);
    if(argc!=4){
        printf("please give 4 arguements in commandline and it should be in the format <filename> <frames> <method>"); //program exectuion stops if arguements are not correct.
        return 1;
    }else{
        FILE *filepointer = fopen(argv[1], "r");
        char ch[200];
        if(filepointer){
            while(fgets(ch, sizeof(ch), filepointer) != NULL){
                char *line = strtok(ch, " ");
                int address_index= 0;
                char page_number[150];
                char mode[10];
                while(line != NULL){
                    if(address_index==0)
                        strcpy(page_number,line);
                                                                           // line by line file is read here and every line is splitted by space.
                    else
                        strcpy(mode,line);
                    address_index++;
                    line = strtok(NULL,"");

                    
                }
                if(strcmp(argv[3],"fifo")==0){
                    FIFO_cache(page_number,mode,frames);      // if arguement[3] is fifo it passed to fifo cache.
                }
                else if(strcmp(argv[3],"lru")==0){
                    LRU_cache(page_number,mode,frames);      //else it passed to lru cache.
                }
               

            }
             printf("\n Contents of pages are :-");
             struct node_class* dup = head;
             while(dup!= NULL){
                printf("%s ", dup->page_number);            //printing of contents is done from most least to most recent.
                dup = dup->next;
             }
             
             printf("\n");
             printf("\n Number of Reads = %d",reads);
		     printf("\n Number of Writes = %d\n",writes);  // global reads and writes are printed.
        }
        else{
            printf("Enter valid file"); //checking for valid file.
            return 1;
        }
    }
    return 0; 
}
