/*
Daniel Gapper

ADVANTAGES/DISADVANTAGES LINKED LIST:
+
The most clear advantage of using a linked list is it's dynamic size and ability to change the ammount of memory it takes up on the fly.
For this assignment this was useful when adding and removing commands since it meant there was not limit and deleting a command 
actually deallocated the memory.

-
The biggest disadvantage of using a linked list is that it is hard to walk through since you need to go from one node to the next one at a time.
You also need to be consious to deallocate the memory once you save and quit and delete a node. For this assignment I needed to go step by
step through the entire linked list (as seen in displayAllCommands()) by using getNext() to get the next node.

ADVANTAGES/DISADVANTAGES ARRAY:
+
The biggest advantage for using an array is how easy it is to walk through. Unlike a linked list you don't need to start at one end
and walk through one by one. Instead you can search using index which made getting the profiles in the getter much more straight forward
and efficient. You also don't need to worry about deallocating the memory since it isn't dynamic.

- 
The biggest disadvantage would be not having the ability to dynamically allocate memory. For this assignment it meant that we needed
to set the size of the profiles array which is inefficient since there can be a lot of wasted space since the array is the same size 
regardless of the number of profiles. It also means that if we create a lot of profiles we could run out of space.
*/

#include "header.h"
#include "GameRunner.h"

int main()
{
    GameRunner game;
    game.displayMenu(); 

    return 0;
}
