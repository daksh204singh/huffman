//
//  huffman.c
//  huffman
//
//  Created by Daksh Pratap Singh on 25/12/18.
//  Copyright © 2018 Daksh Pratap Singh. All rights reserved.
//

#include "huffman.h"

minHeapNode* createMinHeapNode (int data, unsigned int freq) {
    minHeapNode *temp = (minHeapNode*)malloc(sizeof(minHeapNode));
    temp->data = data;
    temp->freq = freq;
    temp->left = temp->right = NULL;
    return temp;
}

minHeap* createMinHeap (unsigned int capacity) {
    minHeap* temp = (minHeap*)malloc(sizeof(minHeap));
    temp->size = 0;
    temp->capacity = capacity;
    temp->arr = (minHeapNode**)malloc(capacity * sizeof(minHeap*));
    return temp;
}

void minHeapify (minHeap *min_heap, int i) {
    int n, l, r, smallest;
    
    n = min_heap->size - 1;
    if (i > (n - 1)/2)
        return;
    
    l = 2 * i + 1;
    r = 2 * i + 2;
    smallest = i;
    
    if (l <= n && min_heap->arr[l]->freq < min_heap->arr[smallest]->freq)
        smallest = l;
    if (r <= n && min_heap->arr[r]->freq < min_heap->arr[smallest]->freq)
        smallest = r;
    
    if (i != smallest) {
        swapNode(&min_heap->arr[i], &min_heap->arr[smallest]);
        minHeapify(min_heap, smallest);
    }
    
}

void swapNode (minHeapNode **a, minHeapNode **b) {
    minHeapNode *temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void buildMinHeap (minHeap *min_heap) {
    int n, i;
    
    n = min_heap->size - 1;
    if (n < 1)
        return;
    
    for (i = (n - 1)/2; i >= 0; --i)
        minHeapify(min_heap, i);
}

minHeapNode* extractMin (minHeap *min_heap) {
    int n;
    
    n = min_heap->size - 1;
    if (n < 0)
        return NULL;
    
    swapNode(&min_heap->arr[0], &min_heap->arr[n]);
    --min_heap->size;
    minHeapify(min_heap, 0);
    
    return min_heap->arr[n];
}

void insertMinHeapNode (minHeap *min_heap, minHeapNode *node) {
    int i;
    
    i = ++min_heap->size - 1;
    
    while (i > 0 && node->freq < min_heap->arr[(i - 1)/2]->freq) {
        min_heap->arr[i] = min_heap->arr[(i - 1)/2];
        i = (i - 1)/2;
    }
    min_heap->arr[i] = node;
}

minHeap* createAndBuildMinHeap (int data[], unsigned int freq[], unsigned int size) {
    int i;
    minHeap* min_heap = createMinHeap (size);
    
    for (i = 0; i < size; ++i)
        min_heap->arr[i] = createMinHeapNode(data[i], freq[i]);
    min_heap->size = size;
    
    buildMinHeap(min_heap);
    return min_heap;
}

int isSizeOne (minHeap *min_heap) {
    if (min_heap->size == 1)
        return 1;
    return 0;
}

minHeapNode* buildHuffmanTree (int data[], unsigned int freq[], unsigned int size) {
    minHeapNode *head, *left, *right;
    minHeap *min_heap = createAndBuildMinHeap(data, freq, size);
    
    while (!isSizeOne(min_heap)) {
        left = extractMin(min_heap);
        right = extractMin(min_heap);
        head = createMinHeapNode('$', left->freq + right->freq);
        head->left = left;
        head->right = right;
        insertMinHeapNode(min_heap, head);
    }
    head = extractMin(min_heap);
    deleteMinHeap(&min_heap);
    return head;
}

int isLeaf (minHeapNode *root) {
    return !(root->left) && !(root->right);
}

void printArr (huffCode arr, int arr_length) {
    int i;
    
    for (i = 0; i < arr_length; ++i)
        printf("%u", arr[i].i);
    putchar('\n');
}

void assignCodes (minHeapNode *root, huffCode arr, huffMap *huff_map, int top) {
    if (root->left) {
        arr[top].i = 0;
        assignCodes(root->left, arr, huff_map, top + 1);
    }
    if (root->right) {
        arr[top].i = 1;
        assignCodes(root->right, arr, huff_map, top + 1);
    }
    if (isLeaf(root)) {
        huff_map->arr[huff_map->size].data = root->data;
        copyCode(arr, huff_map->arr[huff_map->size].code, top);
        huff_map->arr[huff_map->size].codeSize = top;
        ++huff_map->size;
    }
}

huffMap* huffmanCodes (int data[], unsigned int freq[], unsigned int size) {
    minHeapNode *root = buildHuffmanTree(data, freq, size);
    huffCode arr;
    huffMap *huff_map = (huffMap*)malloc(sizeof(huffMap));
    huff_map->arr = (huffEntry*)malloc(size * sizeof(huffEntry));
    huff_map->size = 0;
    huff_map->capacity = size;
    int i, top = 0;

    assignCodes(root, arr, huff_map, top);
    deleteHuffmanTree(&root);

    for (i = 0; i < huff_map->size; ++i) {
        if (isprint(huff_map->arr[i].data))
            printf("%c: ", huff_map->arr[i].data);
        else
            printf("%d: ", huff_map->arr[i].data);
        printArr(huff_map->arr[i].code, huff_map->arr[i].codeSize);
    }
    
    return huff_map;
}

void copyCode (huffCode arr, huffCode code, int size) {
    int i;
    
    for (i = 0; i < size; ++i)
        code[i].i = arr[i].i;
}

void _deleteHuffmanTree (minHeapNode *root) {
    if (root != NULL) {
        _deleteHuffmanTree(root->left);
        _deleteHuffmanTree(root->right);
        free(root);
    }
}

void deleteHuffmanTree (minHeapNode **root) {
    _deleteHuffmanTree(*root);
    *root = NULL;
}

void printTree(minHeapNode *root) {
    if (root == NULL)
        return;
    printTree(root->left);
    printTree(root->right);
    printf("%u\n", root->freq);
}

void _deleteMinHeap (minHeap *min_heap) {
    free(min_heap->arr);
    free(min_heap);
}

void deleteMinHeap (minHeap **min_heap) {
    _deleteMinHeap(*min_heap);
    *min_heap = NULL;
}

void mergeSort (huffMap *huff_map, int low, int high) {
    int mid;
    if (low >= high)
        return;
    mid = low + (high - low)/2;
    
    mergeSort(huff_map, low, mid);
    mergeSort(huff_map, mid + 1, high);
    merge(huff_map, low, mid, high);
}

void merge (huffMap *huff_map, int low, int mid, int high) {
    int n1 = mid - low + 1;
    int n2 = high - mid;
    int i, j, k;
    
    huffEntry *L = (huffEntry*)malloc(n1 * sizeof(huffEntry));
    huffEntry *R = (huffEntry*)malloc(n2 * sizeof(huffEntry));
    
    for (i = 0; i < n1; ++i)
        L[i] = huff_map->arr[low + i];
    for (i = 0; i < n2; ++i)
        R[i] = huff_map->arr[mid + 1 + i];
    
    i = j = 0;
    k = low;
    while (i < n1 && j < n2)
        if (L[i].data <= R[j].data) {
            huff_map->arr[k] = L[i];
            ++i;
            ++k;
        }
        else {
            huff_map->arr[k] = R[j];
            ++j;
            ++k;
        }
    
    while (i < n1) {
        huff_map->arr[k] = L[i];
        ++i;
        ++k;
    }
    
    while (j < n2) {
        huff_map->arr[k] = R[j];
        ++j;
        ++k;
    }
    
    free(L);
    L = NULL;
    free(R);
    R = NULL;
}

int binarySearch (huffMap *huff_map, int data, int low, int high) {
    int mid;
    
    while (low <= high) {
        mid = low + (high - low)/2;
        
        if (huff_map->arr[mid].data == data)
            return mid;
        else if (huff_map->arr[mid].data < data)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

unsigned int my_strlen (const char *string) {
    unsigned int i;
    
    for (i = 0; string[i] != '\0'; ++i)
        ;
    return ++i;
}
