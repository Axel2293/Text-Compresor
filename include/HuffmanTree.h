#ifndef REPSET_H
#define REPSET_H

typedef char * string;
typedef struct Frequency * freq;
typedef struct Tree * tree;

void HuffmanCoding(string, size_t);
void decompress(string data, tree);


#endif