//
//  huffman_encoder.h
//  huffman
//
//  Created by Daksh Pratap Singh on 25/12/18.
//  Copyright © 2018 Daksh Pratap Singh. All rights reserved.
//

#ifndef huffman_encoder_h
#define huffman_encoder_h

#include "huffman.h"


huffMap* constructHuffMap (FILE* in_file, FILE* out_file);
void huffmanEncoding (FILE *in_file, FILE *out_file);

#endif /* huffman_encoder_h */
