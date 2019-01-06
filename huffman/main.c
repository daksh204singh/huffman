//
//  main.c
//  huffman
//
//  Created by Daksh Pratap Singh on 25/12/18.
//  Copyright © 2018 Daksh Pratap Singh. All rights reserved.
//

#include "huffman.h"
#include "huffman_encoder.h"
#include "huffman_decoder.h"
#define COMPRESS 0
#define DECOMPRESS 1

int main(int argc, const char * argv[]) {
//    int arr[] = { 'a', 'b', 'c', 'd', 'e', 'f' };
//    unsigned int freq[] = { 5, 9, 12, 13, 16, 45 };
//
//    unsigned int size = sizeof(arr) / sizeof(arr[0]);
//    huffmanCodes(arr, freq, size);
    FILE *in_file, *out_file;
    unsigned int size;
    char *out_st;
    int i;
    int flag;
    
    if (argc != 3) {
        fprintf(stdout,"Usage: %s <file_name> <option>\n0 - compress, 1 - decompress\n", argv[0]);
        return 1;
    }
    
    if (my_strlen(argv[2]) == 2) {
        if (argv[2][0] == '0')
            flag = COMPRESS;
        else if (argv[2][0] == '1')
            flag = DECOMPRESS;
        else {
            fprintf(stderr, "Invalid option\n");
            return 1;
        }
    }
    else {
        fprintf(stderr, "Invalid option\n");
        return 1;
    }

    
    
    size = my_strlen(argv[1]);
    
    if (flag == COMPRESS) {
        in_file = fopen(argv[1], "r");
        
        if (in_file == NULL) {
            fprintf(stderr, "Unable to open %s\n", argv[1]);
            return 1;
        }
        
        out_st = (char*)malloc((size + 5) * sizeof(char));
        
        for (i = 0; i < size - 1; ++i)
            out_st[i] = argv[1][i];
        
        out_st[i++] = '.'; out_st[i++] = 'h'; out_st[i++] = 'u';
        out_st[i++] = 'f'; out_st[i++] = 'f'; out_st[i++] = '\0';
        
        printf("%s\n", out_st);
        
        out_file = fopen(out_st, "wb");
        
        if (out_file == NULL) {
            fprintf(stderr, "Unable to open %s\n", out_st);
            return 1;
        }
        
        huffmanEncoding(in_file, out_file);
    }
    else {
        in_file = fopen(argv[1], "rb");
        
        if (in_file == NULL) {
            fprintf(stderr, "Unable to open %s\n", argv[1]);
            return 1;
        }
        
        out_st = (char*)malloc((size - 5) * sizeof(char));
        for (i = 0; i < size - 5 - 1; ++i)
            out_st[i] = argv[1][i];
        out_st[i++] = '\0';
        
        printf("%s\n", out_st);
        
        out_file = fopen(out_st, "w");
        decodeHuffmanEncoding(in_file, out_file);
    }
    free(out_st);
    return 0;
}
