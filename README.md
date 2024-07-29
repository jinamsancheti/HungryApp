# HungryApp



It is a console-based application designed to facilitate the discovery and ordering of food from restaurants. It allows users to search for restaurants based on various criteria like area, speciality and type of food and then order that food accordingly. 


My motive for developing HungryApp is to enhance the efficiency of searching through restaurants and to strengthen my understanding of data structures by applying them in a real-world project.


To enhance the efficiency of searching through restaurants I interated linked lists within AVL trees. As AVL trees are self-balancing binary search trees they ensure height to be logarithmic providing faster search times. Then I used Linked Lists to handle multiple restaurants within the same category.


For example:- As I mentioned above that a user can search a restaurant based on categories like speciality, area and type of food. So let's say that a user wants to search a restaurant based on area, then an AVL tree will be created based on area. Let's say user wants to search all the restaurants in Ambazari (Area in Nagpur) then the node Ambazari of the AVL tree formed eariler will have a lined list of all the restaurants of Ambazari.
This makes search more faster and efficient.
