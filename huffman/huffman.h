//
//  huffman.h
//  huffman
//
//  Created by Daksh Pratap Singh on 25/12/18.
//  Copyright © 2018 Daksh Pratap Singh. All rights reserved.
//

#ifndef huffman_h
#define huffman_h

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXCHAR 128
#define MAXTREEHT 128

typedef struct code {
    unsigned char i:1;
} huffCode[MAXTREEHT];

typedef struct {
    int data;
    huffCode code;
    int codeSize;
} huffEntry;

typedef struct {
    unsigned int size;
    unsigned int capacity;
    huffEntry *arr;
} huffMap;

typedef struct node {
    int data;
    unsigned int freq;
    struct node *left;
    struct node *right;
} minHeapNode;

typedef struct heap {
    unsigned int size;
    unsigned int capacity;
    minHeapNode **arr;
} minHeap;



minHeapNode* createMinHeapNode (int data, unsigned int freq);
minHeap* createMinHeap (unsigned int capacity);
void swapNode (minHeapNode **a, minHeapNode **b);
void minHeapify (minHeap *min_heap, int position);
void buildMinHeap (minHeap *min_heap);
minHeapNode* extractMin (minHeap *min_heap);
void insertMinHeapNode (minHeap *min_heap, minHeapNode *node);
minHeap* createAndBuildMinHeap (int data[], unsigned int freq[], unsigned int size);
int isSizeOne (minHeap *min_heap);
minHeapNode* buildHuffmanTree (int data[], unsigned int freq[], unsigned int size);
int isLeaf (minHeapNode *node);
void printArr (huffCode arr, int arr_length);
void copyCode (huffCode arr, huffCode code, int size);
void assignCodes (minHeapNode *root, huffCode arr, huffMap *huff_map, int top);
huffMap* createHuffMap (unsigned int capacity);
huffMap* huffmanCodes (int data[], unsigned int freq[], unsigned int size);
void printTree(minHeapNode *root);
void deleteHuffmanTree (minHeapNode **root);
void _deleteHuffmanTree (minHeapNode *root);
void _deleteMinHeap (minHeap *min_heap);
void deleteMinHeap (minHeap **min_heap);
void merge (huffMap *huff_map, int low, int mid, int high);
void mergeSort (huffMap *huff_map, int low, int high);
int binarySearch (huffMap *huff_map, int data, int l, int r);
unsigned int my_strlen(const char *string);

#endif /* huffman_h */
