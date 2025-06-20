// #include <stdio.h>
// #include <stdlib.h>

// #define MAX_CHAR 256

// int freq[MAX_CHAR] = {0};

// // Step 1: Read file and count frequency
// void countFrequency(const char *filename) {
//     FILE *fp = fopen(filename, "r");
//     if (!fp) {
//         printf("Error opening file!\n");
//         return;
//     }

//     char ch;
//     while ((ch = fgetc(fp)) != EOF) {
//         freq[(unsigned char)ch]++;
//     }

//     fclose(fp);
// }

// #include <string.h>

// typedef struct Node {
//     char ch;
//     int freq;
//     struct Node *left, *right;
// } Node;

// Node* createNode(char ch, int freq) {
//     Node* newNode = (Node*)malloc(sizeof(Node));
//     newNode->ch = ch;
//     newNode->freq = freq;
//     newNode->left = newNode->right = NULL;
//     return newNode;
// }

// // Priority Queue
// #define MAX_NODES 256
// Node* heap[MAX_NODES];
// int heapSize = 0;

// void swap(Node **a, Node **b) {
//     Node *temp = *a;
//     *a = *b;
//     *b = temp;
// }

// void heapifyUp(int index) {
//     while (index && heap[index]->freq < heap[(index - 1) / 2]->freq) {
//         swap(&heap[index], &heap[(index - 1) / 2]);
//         index = (index - 1) / 2;
//     }
// }

// void heapifyDown(int index) {
//     int smallest = index;
//     int left = 2*index + 1;
//     int right = 2*index + 2;

//     if (left < heapSize && heap[left]->freq < heap[smallest]->freq)
//         smallest = left;
//     if (right < heapSize && heap[right]->freq < heap[smallest]->freq)
//         smallest = right;

//     if (smallest != index) {
//         swap(&heap[index], &heap[smallest]);
//         heapifyDown(smallest);
//     }
// }

// void insertHeap(Node *node) {
//     heap[heapSize++] = node;
//     heapifyUp(heapSize - 1);
// }

// Node* extractMin() {
//     Node* temp = heap[0];
//     heap[0] = heap[--heapSize];
//     heapifyDown(0);
//     return temp;
// }


// Node* buildHuffmanTree() {
//     for (int i = 0; i < MAX_CHAR; i++) {
//         if (freq[i]) {
//             insertHeap(createNode((char)i, freq[i]));
//         }
//     }

//     while (heapSize > 1) {
//         Node *left = extractMin();
//         Node *right = extractMin();
//         Node *merged = createNode('\0', left->freq + right->freq);
//         merged->left = left;
//         merged->right = right;
//         insertHeap(merged);
//     }

//     return extractMin(); // Root node
// }



// char codes[MAX_CHAR][MAX_CHAR];

// void generateCodes(Node *root, char *code, int depth) {
//     if (root == NULL)
//         return;

//     if (root->left == NULL && root->right == NULL) {
//         code[depth] = '\0';
//         strcpy(codes[(unsigned char)root->ch], code);
//         return;
//     }

//     code[depth] = '0';
//     generateCodes(root->left, code, depth + 1);

//     code[depth] = '1';
//     generateCodes(root->right, code, depth + 1);
// }

// void encodeFile(const char *inputFilename, const char *outputFilename) {
//     FILE *in = fopen(inputFilename, "r");
//     FILE *out = fopen(outputFilename, "w");

//     if (!in || !out) {
//         printf("Error opening input/output file!\n");
//         return;
//     }

//     char ch;
//     while ((ch = fgetc(in)) != EOF) {
//         fputs(codes[(unsigned char)ch], out);  // Write Huffman code instead of character
//     }

//     fclose(in);
//     fclose(out);

//     printf("File compressed successfully and saved to %s\n", outputFilename);
// }



// int main() {
//     const char *inputFile = "input.txt";
//     const char *outputFile = "compressed.txt";

//     countFrequency(inputFile);

//     Node *root = buildHuffmanTree();

//     char tempCode[MAX_CHAR];
//     generateCodes(root, tempCode, 0);

//     printf("Huffman Codes:\n");
//     for (int i = 0; i < MAX_CHAR; i++) {
//         if (freq[i] > 0) {
//             printf("%c: %s\n", i, codes[i]);
//         }
//     }

//     // Step 4: Encode file
//     encodeFile(inputFile, outputFile);

//     return 0;
// }


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 256

// Frequency array
int freq[MAX_CHAR] = {0};

// Huffman Node
typedef struct Node {
    char ch;
    int freq;
    struct Node *left, *right;
} Node;

// Priority queue
Node* heap[MAX_CHAR];
int heapSize = 0;

// Huffman codes
char codes[MAX_CHAR][MAX_CHAR];

// Count frequency of each character in input file
void countFrequency(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Error opening file!\n");
        return;
    }

    char ch;
    while ((ch = fgetc(fp)) != EOF) {
        freq[(unsigned char)ch]++;
    }

    fclose(fp);
}

// Create new Huffman node
Node* createNode(char ch, int freq) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->ch = ch;
    newNode->freq = freq;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Swap utility
void swap(Node **a, Node **b) {
    Node *temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify functions
void heapifyUp(int index) {
    while (index && heap[index]->freq < heap[(index - 1) / 2]->freq) {
        swap(&heap[index], &heap[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

void heapifyDown(int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < heapSize && heap[left]->freq < heap[smallest]->freq)
        smallest = left;
    if (right < heapSize && heap[right]->freq < heap[smallest]->freq)
        smallest = right;

    if (smallest != index) {
        swap(&heap[index], &heap[smallest]);
        heapifyDown(smallest);
    }
}

// Heap insert and extract
void insertHeap(Node *node) {
    heap[heapSize++] = node;
    heapifyUp(heapSize - 1);
}

Node* extractMin() {
    Node* temp = heap[0];
    heap[0] = heap[--heapSize];
    heapifyDown(0);
    return temp;
}

// Build Huffman tree
Node* buildHuffmanTree() {
    for (int i = 0; i < MAX_CHAR; i++) {
        if (freq[i]) {
            insertHeap(createNode((char)i, freq[i]));
        }
    }

    while (heapSize > 1) {
        Node *left = extractMin();
        Node *right = extractMin();
        Node *merged = createNode('\0', left->freq + right->freq);
        merged->left = left;
        merged->right = right;
        insertHeap(merged);
    }

    return extractMin(); // root
}

// Generate Huffman codes recursively
void generateCodes(Node *root, char *code, int depth) {
    if (!root) return;

    if (!root->left && !root->right) {
        code[depth] = '\0';
        strcpy(codes[(unsigned char)root->ch], code);
        return;
    }

    code[depth] = '0';
    generateCodes(root->left, code, depth + 1);

    code[depth] = '1';
    generateCodes(root->right, code, depth + 1);
}

// Encode and write real binary compressed output
void encodeFile(const char *inputFilename, const char *outputFilename) {
    FILE *in = fopen(inputFilename, "r");
    FILE *out = fopen(outputFilename, "wb");  // Binary mode

    if (!in || !out) {
        printf("Error opening input/output file!\n");
        return;
    }

    unsigned char byte = 0;
    int bitCount = 0;

    char ch;
    while ((ch = fgetc(in)) != EOF) {
        char *code = codes[(unsigned char)ch];
        for (int i = 0; code[i] != '\0'; i++) {
            byte = byte << 1;
            if (code[i] == '1') byte |= 1;
            bitCount++;

            if (bitCount == 8) {
                fwrite(&byte, sizeof(unsigned char), 1, out);
                byte = 0;
                bitCount = 0;
            }
        }
    }

    // Write remaining bits
    if (bitCount > 0) {
        byte <<= (8 - bitCount);
        fwrite(&byte, sizeof(unsigned char), 1, out);
    }

    fclose(in);
    fclose(out);
    printf("Compressed binary file saved to %s\n", outputFilename);
}

// Main function
int main() {
    const char *inputFile = "input.txt";
    const char *outputFile = "compressed.bin";

    countFrequency(inputFile);
    Node *root = buildHuffmanTree();

    char tempCode[MAX_CHAR];
    generateCodes(root, tempCode, 0);

    printf("\nHuffman Codes:\n");
    for (int i = 0; i < MAX_CHAR; i++) {
        if (freq[i] > 0) {
            printf("%c: %s\n", i, codes[i]);
        }
    }

    encodeFile(inputFile, outputFile);

    // Compression stats
    FILE *orig = fopen(inputFile, "r");
    FILE *comp = fopen(outputFile, "rb");
    fseek(orig, 0, SEEK_END);
    fseek(comp, 0, SEEK_END);
    long origSize = ftell(orig);
    long compSize = ftell(comp);
    fclose(orig);
    fclose(comp);

    printf("\nOriginal size: %ld bytes\n", origSize);
    printf("Compressed size: %ld bytes\n", compSize);
    printf("Compression ratio: %.2f%%\n", (100.0 * compSize / origSize));

    return 0;
}

