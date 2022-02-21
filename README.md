# C++ Implementations of Common Data Structures

This implementation is partially based on *Data Structures and Algorithm Analysis in C Second Edition* by Mark Allen Weiss.

## Content

Ch2: Intro to Algorithms, a few utility functions to help me calculate and display execution time of a function

Ch3: Linked List, Stack and Queue

Ch4: N-ary Tree, Binary Tree, Binary Search Tree, AVL Tree, B+Tree

Ch5: Hashing (Not Implemented, but I implemented my own HashMap using DJB hash function)

Ch6: Heap and Priority Queue (Not Implemented)

Ch7: String (Implemented) and Multi-Dimensional Array (Not Implemented)

Ch8: Adjacency List as Graph (Partially Implemented)

Ch9: Sorting Algorithm

- BubbleSort
- RadixSort
- InsertionSort, ShellSort

Ch10: Indexing Algorithm (Not Implemented)

Ch11: Advanced Structures and Designing Algorithms (Not Implemented)

## Directories

ChX: Chapter files and codes

CommonDS_v2: Refactored DS library for other uses

HashMap: An hash map implementation using AVL tree and linked list

Utils.hpp: Utility functions such as memory, log, timer and random array generator

## How to use for other purposes

Download CommonDS_v2/CommonDS_v2. The ds.h is the interface header file including all data structure headers and sources. Users can also include only needed headers and sources instead of ds.h.

ds.h also defines several macros for shorter class names and function names. The reason for such long original names is to avoid name collisions. Users may customize their own shorter versions by renaming the macros in ds.h.

To expand node capabilities, create custom node_impl* or tnode_impl* file and replace the included one in ds.h.