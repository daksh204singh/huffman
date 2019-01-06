//
//  huffman_decoder.h
//  huffman
//
//  Created by Daksh Pratap Singh on 27/12/18.
//  Copyright © 2018 Daksh Pratap Singh. All rights reserved.
//

#ifndef huffman_decoder_h
#define huffman_decoder_h

#include <stdio.h>
#include <math.h>
#include "huffman.h"

void decodeHuffmanEncoding (FILE *in_file, FILE *out_file);
void reverseBits (unsigned char *c);

#endif /* huffman_decoder_h */
