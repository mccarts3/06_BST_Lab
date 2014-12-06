06_BST_Lab
==============

Implement a binary search tree in C++

Requirements
------------

1. All methods except the destructor and `size()` should be O(h), where h is the height of the tree
2. `size()` should be O(n)

Reading
=======
"Open Data Structures," Chapter 6, the entire chapter. http://opendatastructures.org/ods-cpp/6_Binary_Trees.html

Questions
=========

#### 1. Which of the above requirements work, and which do not? For each requirement, write a brief response.

1. TODO
2. TODO

#### 2. Do exercises 6.7 and 6.9 on http://opendatastructures.org/ods-cpp/6_3_Discussion_Exercises.html. Keep in mind: You do NOT need to write real working code, you may write pseudo-code. In fact, that is preferred.

6.7
	Pre-Order - Have an int n=0
			  - METHOD BEGINS
			  -	Call the method with the root as the parameter
			  -	Assign the current node a value of n and increment n
			  -	recursively call the method with the left node as the parameter AND the method with the right node as the parameter
	In-Order  - Have an int n=0
			  - METHOD BEGINS
			  -	Call the method with the root as the parameter
			  -	Recursively call the method until the left child is null, and assign the current node a value of n and increment it
			  - Assign the current node a value of n and increment it
			  - Recursively call the method with the right node as the parameter, assign it n and increment it
	PostOrder - Have an int n=0
			  - METHOD BEGINS
			  -	Call the method with the root as the parameter
			  -	Recursively call the method until the left child is null, and assign the current node a value of n and increment it
			  - Recursively call the method with the right node as the parameter, assign it n and increment it
			  - Assign the current node a value of n and increment it

6.9
	1. Pre-Order -
	   In-Order -
	   Post-Order -
	2. Pre-Order -
	   In-Order -
	   Post-Order -
	3. Pre-Order -
	   In-Order -
	   Post-Order -

#### 3. What is one question that confused you about this exercise, or one piece of advice you would share with students next semester?

How does the BST self-rearrange itself so that it's height is as small as possible?  I'm not sure how to make sure the BST is as short as it can be.