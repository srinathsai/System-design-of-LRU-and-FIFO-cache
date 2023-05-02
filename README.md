# System-design-of-LRU-and-FIFO-cache
Page  replacement  algorithms  are  an  essential  part  of  completing  the  illusion  of  infinite 
virtual memory to the user by masking the need for reading pages from the disk for every execution. 

## Goal :- 
This project focuses on efficient way of implementing LRU and FIFO cache which outlines the supporting reasons for my way of implementation.<br />
Two methods of implementation which is using arrays and using linkedlists are compared with each other in terms of optimality and correctedness.<br />
 
## My implementation with reasons :- 
**FIFO** :- For FIFO, I have used Queue implementation but with the helps of array of frames as fixed size .Here initially in array all values are set to be -1 indicating all these values are empty.Where every line of a file address is converted to long and sent to cache. If they are not present in the cache, then they are added from starting of an array . Like Queue elements are added at back of filled slots.Now whenever there is a page fault deletion happens at First of the queue , but here in my 
algorithm what I do is I shift all elements from second index to first and leaving last cell empty for inserting. And previously first element will be not there signifying deletion when page fault occurs.<br />

(Array size is fixed that is frames given by us).<br />

In addition to that I have used array of read/write modes of same size for updating respective page number index mode with new one if any page fault occurs. Not only that, this array of read/writes modes are used to update read/ write count in non fault situations also where same address but different modes are there in which one of them is already in memory and other trying to access memory.<br />

## Time complexity analysis :- 
At first in order to determine whether a specific element is present or absent in cache ,in my algorithm I need to traverse whole array to check it’s presence . Let’s number of frames be N. then for searching of faulty it will be O(N).Next if there is any fault I need to delete the element at first index and shift entire elements of array to left (as that of queue):- for this operation to be in an array it again takes time complexity as O(N).<br />
Again at time of inserting in worst case scenario, it will be added at end of queue , so in my method at last index we need to add and if cache is full then again at start element must be deleted so this is also :- O(N).<br />
Therefore as frame increases my algorithm timecomplexity will be increased linearly.

## Space complexity analysis :- 
It will be O(2N) where one n is for cache memory and other n is for array that holds modes of each frame. And N is number of frames.<br />

## SUPPORTIVE REASONS FOR MY CHOICE :-
1) Though, all my choices are O(N) , execution will be very fast in cluser as no of frames are static and we know static memory building is very much faster than dynamic one. That implies in LinkedList there is no overflowing and insertion also takes in O(1) time but the 
main problem is memory building there would be dynamic which takes lot of time in 
execution on cluster.<br />
2) Next foremost important thing is accessing a element which is O(1) in array and faster than that of LinkedList which is O(N).<br />


**LEAST RECENTLY USED** :- I mimicked HashTable approach but not exactly HashTable . I have used 3 arrays of frames size. In which one array is for cache , another array of modes and last array is for frequency (which is used for retrieving last frequent element).Basic idea is at first it will check emptiness of cache .Initially cache will be empty so it will be inserted into it. Whenever it is inserting at respective index in frequency array value will be incremented indicating it is most accessed. Therefore before inserting it checks whether this value is present or not ,if present in frequency array respective index will be incremented , if not and if cache is full , to get least frequent element traversing in frequency array and first minimum from left ,that index would be our index to replace 
element ,if any fault occurs.<br />

##Time complexity analysis :- 
AS main cache is array inserting an element at last index is the worst case where it takes O(N) . deletion will be in worst case as O(2*N) because it needs to traverse in frequency array for the least frequent element to be replaced and with this 
respective index it should be removed in main array. Searching also will be O(N) in worstcase of element is not there.Therefore as frame sizes increases my time in every operation will be increased linearly.<br />

## Space complexity analysis :- 
As it has 3 arrays of size n frames it will be O(3*N).<br />

## SUPPORTIVE REASONS FOR MY CHOICE :-
1) First thing is accessing by index is very simple and fast as compared to key in hashmap. This is because hashing for huge frames required lot of computation time and lot of changing of functions to prevent collisions.<br />
2) Next as memory is static and fixed there won’t be any issues of waiting time in memory building. <br />

NOTE:- BEFORE EXECUTING READ THE README PDF OF CODE.


