# System-design-of-LRU-and-FIFO-cache
Memory in a computer is minimal. Physical memory expansion is too expensive. To access more memory than what is available on the system, most contemporary computers have features that consist of hardware and software. This is Virtual memory. Virtual Memory is implemented in paging and segmentation. Paging is nothing but accessing the secondary memory to perform reading and writing. paging's primary goal, as stated above, is to break each operation into pages of the same size. Frames 
are used to hold these pages in the main memory.Page replacement is used to maintain the functionality of virtual memory by the demand paging concept. As the main memory is minimal and only certain pages are available when required by the CPU with the use of page replacement algorithms the pages are swapped in swapped out. 

## Goal :- 
This project focuses on efficient way of implementing LRU and FIFO cache which outlines the supporting reasons for my way of implementation.<br />
Two methods of implementation which is using arrays and using linkedlists are compared with each other in terms of optimality and correctedness.<br />
 
## My implementation of Arrays with reasons :- 
**FIFO** :- For FIFO, I have used Queue implementation but with the helps of array of frames as fixed size .Here initially in array all values are set to be -1 indicating all these values are empty.Where every line of a file address is converted to long and sent to cache. If they are not present in the cache, then they are added from starting of an array . Like Queue elements are added at back of filled slots.Now whenever there is a page fault deletion happens at First of the queue , but here in my 
algorithm what I do is I shift all elements from second index to first and leaving last cell empty for inserting. And previously first element will be not there signifying deletion when page fault occurs.<br />

(Array size is fixed that is frames given by us).<br />

In addition to that I have used array of read/write modes of same size for updating respective page number index mode with new one if any page fault occurs. Not only that, this array of read/writes modes are used to update read/ write count in non fault situations also where same address but different modes are there in which one of them is already in memory and other trying to access memory.<br />

## Time complexity analysis of arrays implementation:- 
At first in order to determine whether a specific element is present or absent in cache ,in my algorithm I need to traverse whole array to check it’s presence . Let’s number of frames be N. then for searching of faulty it will be O(N).Next if there is any fault I need to delete the element at first index and shift entire elements of array to left (as that of queue):- for this operation to be in an array it again takes time complexity as O(N).<br />
Again at time of inserting in worst case scenario, it will be added at end of queue , so in my method at last index we need to add and if cache is full then again at start element must be deleted so this is also :- O(N).<br />
Therefore as frame increases my algorithm timecomplexity will be increased linearly.

## Space complexity analysis of arrays implementation :- 
It will be O(2N) where one n is for cache memory and other n is for array that holds modes of each frame. And N is number of frames.<br />

## SUPPORTIVE REASONS FOR MY CHOICE OF METHOD-1 :-
1) Though, all my choices are O(N) , execution will be very fast in cluser as no of frames are static and we know static memory building is very much faster than dynamic one. That implies in LinkedList there is no overflowing and insertion also takes in O(1) time but the 
main problem is memory building there would be dynamic which takes lot of time in 
execution on cluster.<br />
2) Next foremost important thing is accessing a element which is O(1) in array and faster than that of LinkedList which is O(N).<br />


**LEAST RECENTLY USED** :- I mimicked HashTable approach but not exactly HashTable . I have used 3 arrays of frames size. In which one array is for cache , another array of modes and last array is for frequency (which is used for retrieving last frequent element).Basic idea is at first it will check emptiness of cache .Initially cache will be empty so it will be inserted into it. Whenever it is inserting at respective index in frequency array value will be incremented indicating it is most accessed. Therefore before inserting it checks whether this value is present or not ,if present in frequency array respective index will be incremented , if not and if cache is full , to get least frequent element traversing in frequency array and first minimum from left ,that index would be our index to replace 
element ,if any fault occurs.<br />

##Time complexity analysis of method-1 :- 
AS main cache is array inserting an element at last index is the worst case where it takes O(N) . deletion will be in worst case as O(2*N) because it needs to traverse in frequency array for the least frequent element to be replaced and with this 
respective index it should be removed in main array. Searching also will be O(N) in worstcase of element is not there.Therefore as frame sizes increases my time in every operation will be increased linearly.<br />

## Space complexity analysis of method-2:- 
As it has 3 arrays of size n frames it will be O(3*N).<br />

## SUPPORTIVE REASONS FOR MY CHOICE :-
1) First thing is accessing by index is very simple and fast as compared to key in hashmap. This is because hashing for huge frames required lot of computation time and lot of changing of functions to prevent collisions.<br />
2) Next as memory is static and fixed there won’t be any issues of waiting time in memory building. <br />


## My implementation using linkedlists with reasons :- 
Implemented Least recently used and first in first out page replacement algorithms using the queue and Linked List data structure. I used a Queue data structure in which the front pointer points toward the last node and the rear pointer points toward the first node. <br />

**LEAST RECENTLY USED** :- when any new page number comes in a situation where frames are full, then least recently used page address is removed. This is also implemented by linkedlist with the help of 3 functions in which dequing is same but search_in_lru and LRU_CACHE functions are different from above. Here LRU_CACHE works same as FIFO_CACHE function in creating new node with incoming address and mode. And here also address is converted to hexadecimal and divided by 4096 to get page number, this page number is copied to new node and depending on the mode dirtybit is set. Next this is passed in search_in_lru function which iterates and finds any match if any match is found in order to make it more recent we need to delete it and attach at back this is done by delete() function .and search_in_lru returns whether found or not. If not found and capacity is full it is removed from first. And dirtybit is set based on removed block type. And if dirty bit is true only write increments or read increments based on mode. <br />

**FIFO** :- when any new page number comes in a situation where frames are full, then first entered page is removed. This is implemented by LinkedList with the help of 3 functions FIFO_CACHE  function it creates new node with incoming address and mode. First address is converted to hexadecimal and divided by 4096 to get page number , this page number is copied to new node and depending on the mode dirtybit is set .  Next this is passed to search_in_fifo function which iterates in the linkedlist and if not found and linkedlist has frames no of nodes a node is remove by dequing function from first. Depending on the removal node dirtybit write count is incremented or reads is incremented if mode is R.

## performance analysis of LinkedList implementation :- 

I used LinkedList because deletion and adding of a node is o(1) , but searching for a particular node is linear which is o(n).So when input increases searching increases linearly as it is o(n) but adding new page and deletion of page is 0(1) which is constant no matter the input size.So altogether because of searching it can be said as worst complexity increases linearly with input size.


## Conclusion :-
Though every method has it's own advantages in terms of time complexities , Method 2 which is implementing through linkedlist have more correctedness for 10 million records due to it's dynamic storage and struct structure in which there is no need of converting adress to float. Whereas as arrays can store only type and as there is no String type in c converting them into double and storing might make the lru cache or fifo cache to read and write wrong answers.




