#include<stdio.h>
#include<stdlib.h>
#include<string.h>
                                                 //SRINATH SAI TRIPURANENI- A20338902.
long min=0;
int reads=0;
int writes=0;

int getmin(long frequency[],int frames){
    min=frequency[0];
    int i=1;
    int m=0;
    while(i<frames){
        if(frequency[i]<min){                 //A FUNCTION FOR GETTING LEAST ACCESSED ELEMENT.
            min=frequency[i];
            m=i;
            return m;
        }
        i++;
    }
    return 0;
}

int isempty(long cache[] ,int frames){
    for(int i=0;i<frames;i++){
        if(cache[i]==0){
            return i;
        }                                   //A FUNCTION WHICH TELLS CACHE IS EMPTY OR NOT.
    }
    return -2;
}

int ispresent(long cache[],int frames,long address){
    for(int i=0;i<frames;i++){
        if(address==cache[i]){          //THIS FUNCTION IS SAME AS ABOVE BUT USED IN LRU.
            return i;
        }
    }
    return -1;
}



void insert(long cache[],long frequency[],long address,int frames,char mode,char type[]){
    int index=ispresent(cache,frames,address);
    if(index!=-1){
                                                                                        //INSERT FUNCTION IN CACHE USED AS UPDATING IN LRU.
                                                                                        //CASE WHERE ELEMENT IS PRESENT BUT MODE IS DIFFERENT.
        if((type[index]=='R') && mode=='W'){
            writes++;
            type[index]='W';
        }
        else if((type[index]=='W')&& mode=='R'){
             reads++;
            type[index]='R';

       }
        frequency[index]=frequency[index]+1;

    }
    else if(index==-1){
        int x=isempty(cache,frames);
        if(x!=-2){
            cache[x]=address;
            type[x]=mode;
            frequency[x]=frequency[x]+1;
            if(mode=='R'){
                reads++;
            }
            else if(mode=='W'){
                writes++;                                                   //CASE WHERE CACHE IS NOT  FULL  AND ELEMENT IS NOT THERE.
            }

        }
        else if(x==-2){
            int index=getmin(frequency,frames);
            cache[index]=address;
            frequency[index]=frequency[index]+1;
            type[index]=mode;
            if(mode=='R'){                                               //CASE WHERE CACHE IS FULL AND ELEMENT IS THERE SO ACESSING MIN FUNCTION WHICH GIVES LEAST RECENTLY ACCESSED ELEMENTS.
                reads++;
            }
            else if(mode=='W'){
                writes++;
            }
        }

    }
}


int isFull(long cache[],int frames){
    for(int i=0;i<frames;i++){
        if(cache[i]=-1){
            return i;
        }
    }
    return -2;
}

int contains(long cache[],long address,int frames){
    for(int i=0;i<frames;i++){                          //A FUNCTION WHICH TELLS AN ELEMENT IS PRESENT OR NOT , IF PRESENT RESPECTIVE INDEX IS RETURNED.
        if(cache[i]==address){
            return i;
        }
    }
    return -2;
}


void enqueue(long cache[],char type[],int frames,char mode,long address){
    int y=isFull(cache,frames);
    if(y!=-2){                                      //THIS IS ENQUEUE FUNCTION WHICH IS USED BY FIFO FOR UPDATING CACHE AND MODES.
            cache[y]=address;
            type[y]=mode;
            if(mode=='R'){
                reads++;                  //IF CACHE CONTAINS ANY EMPTY SPACE IN  GIVEN  FRAMES NUMBER, THEN AT THAT POSITION ADDIING NEW PAGE NUMBER AND UPDATING RESPECTIVE MODE.
            }
            else if(mode=='W'){
                writes++;
            }
    }
    else if(y==-2){
        int x=contains(cache,address,frames);
            if(x!=-2){
                if(mode=='R' && type[x]=='W'){
                    writes++;                            //IF CACHE IS FULL AND OS NEEDS TO INSERT NEW PAGE. THIS IS THE CASE WHERE MODES ARE DIFFERENT BUT NO FAULTY OCCURS.
                    type[x]='R';
                }
                else if(mode=='W' && type[x]=='R'){
                    reads++;
                    type[x]='W';
                }
            }
            else if(x==-2){
                int i=0;
                int j=1;
                while(j<frames){
                    int temp=0;
                    cache[i]=temp;                     //THIS IS THE CASE WHERE ELEMENT IS NOT PRESENT AND DEQUING MUST HAPPEN HERE.
                    cache[i]=cache[j];
                    cache[j]=temp;
                    j++;
                    i++;

                }
                cache[frames-1]=address;
                type[frames-1]=mode;
                if(mode=='R'){
                    reads++;
                }
                else if(mode=='W'){
                    writes++;
                }
            }


        }
    }


int main(int argc,char *argv[]){
        if(argc-1!=3){
                printf("Please give only 3 arguements");
                return 0;
        }
        int frames=atoi(argv[2]);
       // long cache[frames];
       // long frequency[frames];
       // char type[frames];

        char method[50];
        strcpy(method,argv[3]);
        if(strcmp("lru",method)==0){
                long cache[frames];                               //CACHE SIMULATOR BY TAKING ARRAY.
                long frequency[frames];                          //FREQUENCY ARRAY WHICH KEEP TRACKS OF EVERY ELEMENT ACCESSING FREQUENCIES USED FOR ACESSING MINIMUM OR LEAST FREQUENT ELEMENT.
                char type[frames];                               //TYPE ARRAY IS CREATED FOR STORING AND ALTERING THEIR MODES WHENEVER ANY NEW FAULT OCCURS.
                FILE* file=fopen(argv[1],"r");
                char line[200];
               // char newString[10][10];

                while(fgets(line,sizeof(line),file)){
                 if(feof(file)){
                         break;
                 }
                 char newString[10][10];
                 int i,j,counter;
                 j=0;                                                                     //IMPLEMENTATION OF LRU.
                 counter=0;
                for(i=0;i<=(strlen(line));++i){
                        if(line[i]==' '||line[i]=='\0')
                  {
                        newString[counter][j]='\0';
                         counter++;  //for next word
                         j=0;    //for next word, init index to 0
                  }
                        else {
                newString[counter][j]=line[i];
                j++;
            }
    }
                char address[200];
                char mode[200];
                strcpy(address,(newString[0]));
                strcpy(mode,newString[1]);
                char mode1[1];
                strcpy(mode1,mode);
                insert(cache,frequency,(long)atoi(address),frames,mode1[0],type);
               // printf("\n reads count is :%d", reads
               // // printf("\n writes count is : %d", writes);
        }

               printf("\n read count is :%d",reads);
               printf("\n write count is :%d",writes);
                for(int i=0;i<frames;i++)
                        printf("\n values:%ld",cache[i]);

             return 0;
        }


    else if(strcmp("fifo",method)==0){
                long cache[frames]; //SIMULATION OF CACHE MEMORY TAKEN AS ARRAY
                char type[frames]; // FOR EVERY PAGENUMBER STROING IT'S MODE.
                FILE* file=fopen(argv[1],"r");
                char line[200];
            while(fgets(line,sizeof(line),file)){
                 if(feof(file)){
                         break;
                 }
                 char newString[10][10];
                 int i,j,counter;
                 j=0;
                 counter=0;
                for(i=0;i<=(strlen(line));++i){
                        if(line[i]==' '||line[i]=='\0')       //SPLITIING EVERY FILE LINES INTO TWO STRINGS OF ADDRESS AND MODES.
                  {
                        newString[counter][j]='\0';
                         counter++;  //for next word
                         j=0;    //for next word, init index to 0
                  }                                                                               //IMPLEMENTATION OF FIFO
                        else {
                newString[counter][j]=line[i];
                j++;
            }
    }
                char address[200];
                char mode[200];
                strcpy(address,(newString[0]));
                strcpy(mode,newString[1]);
                char mode1[1];
                strcpy(mode1,mode);
                enqueue(cache,type,frames,mode1[0],(long) atoi(address));  //ENQUEUE FUNCTION TAKES CARE OF EVERY THING IN WHICH I USED TWO ARRAYS FOR SIMULATING LIKE A QUEUE.

                                                                         //AS I AM CONVERTING ADDRESS INTO LONG AND SENDING AS ATOI THEREFORE VALUES OF CACHE WILL BE LONG.
        }

            printf("\nreads count is :%d",reads);
            printf("\nwrites count is %d",writes);
            for(int i=0;i<frames;i++){
                    printf("\nvalues are :%ld",cache[i]);
            }
         return 0;
}

return 0;
}
