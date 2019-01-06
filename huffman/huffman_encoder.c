//
//  huffman_encoder.c
//  huffman
//
//  Created by Daksh Pratap Singh on 25/12/18.
//  Copyright © 2018 Daksh Pratap Singh. All rights reserved.
//

#include "huffman_encoder.h"

huffMap* constructHuffMap (FILE *in_file, FILE *out_file) {
    int c, i, j;
    unsigned int size;
    unsigned int cc[MAXCHAR + 1];
    int data[MAXCHAR + 1];
    unsigned int freq[MAXCHAR + 1];
    huffMap *huff_map;
    
    for (i = 0; i <= MAXCHAR; ++i)
        cc[i] = 0;
    
    while ((c = fgetc(in_file)) != EOF)
        ++cc[c];
    cc[MAXCHAR] = 1;
    
    j = 0;
    for (i = 0; i <= MAXCHAR; ++i)
        if (cc[i] > 0) {
            data[j] = i;
            freq[j] = cc[i];
            ++j;
        }
    size = j;
    
    for (i = 0; i < size; ++i) {
        fwrite(&data[i], 1, 1, out_file);
        fwrite(&freq[i], 4, 1, out_file);
    }
    
    huff_map = huffmanCodes(data, freq, size);
    mergeSort(huff_map, 0, huff_map->size - 1);
    
    rewind(in_file);
    
    return huff_map;
}

void huffmanEncoding (FILE *in_file, FILE *out_file) {
    huffMap* huff_map = constructHuffMap(in_file, out_file);

    int c, i, pos, size;
    unsigned int buffer;
    
    buffer = 0;
    size = 0;
    while ((c = fgetc(in_file)) != EOF) {
        pos = binarySearch(huff_map, c, 0, huff_map->size - 1);
        if (pos == -1) {
            fprintf(stderr, "Error in calculating pos\n");
            return;
        }
        for (i = 0; i < huff_map->arr[pos].codeSize; ++i) {
            if (size == 8) {
                fwrite(&buffer, 1, 1, out_file);
                buffer = 0;
                size = 0;
            }
            buffer <<= 1;
            if (huff_map->arr[pos].code[i].i)
                buffer |= 1;
            ++size;
        }
    }
    for (i = 0; i < huff_map->arr[huff_map->size - 1].codeSize; ++i) {
        if (size == 8) {
            fwrite(&buffer, 1, 1, out_file);
            buffer = 0;
            size = 0;
        }
        buffer <<= 1;
        if (huff_map->arr[huff_map->size - 1].code[i].i)
            buffer |= 1;
        ++size;
    }
    if (size < 8)
        buffer <<= (8 - size);
    fwrite(&buffer, 1, 1, out_file);
    
    fclose(in_file);
    fclose(out_file);
}
