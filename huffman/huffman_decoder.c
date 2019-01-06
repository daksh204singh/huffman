
//
//  huffman_decoder.c
//  huffman
//
//  Created by Daksh Pratap Singh on 27/12/18.
//  Copyright © 2018 Daksh Pratap Singh. All rights reserved.
//

#include "huffman_decoder.h"

void decodeHuffmanEncoding (FILE *in_file, FILE *out_file) {
    unsigned char buffer = 0;
    int i;
    unsigned char c;
    unsigned int frequency = 0;
    unsigned int size;
    short iPos;
    unsigned int freq[MAXCHAR + 1];
    int data[MAXCHAR + 1];
    minHeapNode *root, *node;
    
    i = 0;
    c = 0;
    while (c != MAXCHAR) {
        fread(&c, 1, 1, in_file);
        fread(&frequency, 4, 1, in_file);
        data[i] = (int)c;
        freq[i] = frequency;
        ++i;
    }
    
    size = i;
    
    root = buildHuffmanTree(data, freq, size);

    node = root;
    iPos = 7;
    fread(&buffer, 1, 1, in_file);
    printf("`%d`\n", node->data);
    while (1) {
        while (iPos >= 0 && !isLeaf(node)) {
            if (buffer & (1 << iPos))
                node = node->right;
            else
                node = node->left;
            --iPos;
        }
        if (isLeaf(node)) {
            printf("%d\n", node->data);
            if (node->data < MAXCHAR) {
                fprintf(out_file, "%c", node->data);
                node = root;
            }
            else
                break;
        }
        if (iPos < 0) {
            if (fread(&buffer, 1, 1, in_file) == 0 )
                break;
            iPos = 7;
        }
    }
    
    fclose(in_file);
    fclose(out_file);
}

void reverseBits (unsigned char *c) {
    unsigned char x;
    unsigned char reverse_bits;
    short int i = 0;
    
    x = *c;
    reverse_bits = 0;
    for (i = 0; i < 8; ++i)
        if (x & (1 << i))
            reverse_bits = (unsigned char)pow(2, 7 - i);
    *c = reverse_bits;
}
