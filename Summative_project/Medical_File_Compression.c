#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TREE_HT 256

typedef struct MinHeapNode {
    char data;
    unsigned freq;
    struct MinHeapNode *left, *right;
} MinHeapNode;

typedef struct MinHeap {
    unsigned size;
    unsigned capacity;
    MinHeapNode **array;
} MinHeap;

MinHeapNode *create_node(char data, unsigned freq) {
    MinHeapNode *node = (MinHeapNode *)malloc(sizeof(MinHeapNode));
    node->left = node->right = NULL;
    node->data = data;
    node->freq = freq;
    return node;
}

MinHeap *create_min_heap(unsigned capacity) {
    MinHeap *minHeap = (MinHeap *)malloc(sizeof(MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (MinHeapNode **)malloc(capacity * sizeof(MinHeapNode *));
    return minHeap;
}

void swap_nodes(MinHeapNode **a, MinHeapNode **b) {
    MinHeapNode *t = *a;
    *a = *b;
    *b = t;
}

void min_heapify(MinHeap *minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;
    
    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;
    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;
    if (smallest != idx) {
        swap_nodes(&minHeap->array[smallest], &minHeap->array[idx]);
        min_heapify(minHeap, smallest);
    }
}

MinHeapNode *extract_min(MinHeap *minHeap) {
    MinHeapNode *temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    min_heapify(minHeap, 0);
    return temp;
}

void insert_min_heap(MinHeap *minHeap, MinHeapNode *node) {
    ++minHeap->size;
    int i = minHeap->size - 1;
    while (i && node->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = node;
}

void build_min_heap(MinHeap *minHeap) {
    int n = minHeap->size - 1;
    for (int i = (n - 1) / 2; i >= 0; --i)
        min_heapify(minHeap, i);
}

int is_leaf(MinHeapNode *root) {
    return !(root->left) && !(root->right);
}

MinHeap *create_and_build_min_heap(char data[], int freq[], int size) {
    MinHeap *minHeap = create_min_heap(size);
    for (int i = 0; i < size; ++i)
        minHeap->array[i] = create_node(data[i], freq[i]);
    minHeap->size = size;
    build_min_heap(minHeap);
    return minHeap;
}

MinHeapNode *build_huffman_tree(char data[], int freq[], int size) {
    MinHeapNode *left, *right, *top;
    MinHeap *minHeap = create_and_build_min_heap(data, freq, size);
    
    while (minHeap->size != 1) {
        left = extract_min(minHeap);
        right = extract_min(minHeap);
        top = create_node('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        insert_min_heap(minHeap, top);
    }
    
    return extract_min(minHeap);
}

void print_codes(MinHeapNode *root, int arr[], int top, char codes[][MAX_TREE_HT], char data[]) {
    if (root->left) {
        arr[top] = 0;
        print_codes(root->left, arr, top + 1, codes, data);
    }
    if (root->right) {
        arr[top] = 1;
        print_codes(root->right, arr, top + 1, codes, data);
    }
    if (is_leaf(root)) {
        int idx = (unsigned char)root->data;
        for (int i = 0; i < top; i++) {
            codes[idx][i] = arr[i] + '0';
        }
        codes[idx][top] = '\0';
    }
}

void compress_file(const char *input_file, const char *output_file) {
    FILE *fp = fopen(input_file, "r");
    if (!fp) {
        printf("Error: Cannot open input file '%s'\n", input_file);
        return;
    }
    
    int freq[256] = {0};
    char ch;
    long original_size = 0;
    
    while ((ch = fgetc(fp)) != EOF) {
        freq[(unsigned char)ch]++;
        original_size++;
    }
    fclose(fp);
    
    int unique_chars = 0;
    char data[256];
    int freq_data[256];
    
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            data[unique_chars] = (char)i;
            freq_data[unique_chars] = freq[i];
            unique_chars++;
        }
    }
    
    if (unique_chars == 0) {
        printf("Error: Empty file\n");
        return;
    }
    
    MinHeapNode *root = build_huffman_tree(data, freq_data, unique_chars);
    
    char codes[256][MAX_TREE_HT] = {""};
    int arr[MAX_TREE_HT];
    print_codes(root, arr, 0, codes, data);
    
    fp = fopen(input_file, "r");
    FILE *out = fopen(output_file, "w");
    FILE *header = fopen("huffman_tree.dat", "wb");
    
    fwrite(&unique_chars, sizeof(int), 1, header);
    for (int i = 0; i < unique_chars; i++) {
        fwrite(&data[i], sizeof(char), 1, header);
        fwrite(&freq_data[i], sizeof(int), 1, header);
    }
    fclose(header);
    
    long compressed_bits = 0;
    while ((ch = fgetc(fp)) != EOF) {
        fprintf(out, "%s", codes[(unsigned char)ch]);
        compressed_bits += strlen(codes[(unsigned char)ch]);
    }
    
    fclose(fp);
    fclose(out);
    
    long compressed_size = (compressed_bits + 7) / 8;
    
    printf("\n=== Compression Results ===\n");
    printf("Original file size: %ld bytes\n", original_size);
    printf("Compressed size: %ld bytes (approx)\n", compressed_size);
    printf("Compression ratio: %.2f%%\n", (1 - (float)compressed_size / original_size) * 100);
    printf("Output: %s\n\n", output_file);
}

void decompress_file(const char *compressed_file, const char *output_file) {
    FILE *header = fopen("huffman_tree.dat", "rb");
    if (!header) {
        printf("Error: Cannot open huffman tree data\n");
        return;
    }
    
    int unique_chars;
    fread(&unique_chars, sizeof(int), 1, header);
    
    char data[256];
    int freq[256];
    for (int i = 0; i < unique_chars; i++) {
        fread(&data[i], sizeof(char), 1, header);
        fread(&freq[i], sizeof(int), 1, header);
    }
    fclose(header);
    
    MinHeapNode *root = build_huffman_tree(data, freq, unique_chars);
    
    FILE *fp = fopen(compressed_file, "r");
    FILE *out = fopen(output_file, "w");
    
    MinHeapNode *current = root;
    char bit;
    
    while ((bit = fgetc(fp)) != EOF) {
        if (bit == '0') {
            current = current->left;
        } else if (bit == '1') {
            current = current->right;
        }
        
        if (is_leaf(current)) {
            fputc(current->data, out);
            current = root;
        }
    }
    
    fclose(fp);
    fclose(out);
    
    printf("\n=== Decompression Complete ===\n");
    printf("Output: %s\n\n", output_file);
}

int verify_integrity(const char *original, const char *decompressed) {
    FILE *f1 = fopen(original, "r");
    FILE *f2 = fopen(decompressed, "r");
    
    if (!f1 || !f2) {
        if (f1) fclose(f1);
        if (f2) fclose(f2);
        return 0;
    }
    
    char ch1, ch2;
    while (((ch1 = fgetc(f1)) != EOF) && ((ch2 = fgetc(f2)) != EOF)) {
        if (ch1 != ch2) {
            fclose(f1);
            fclose(f2);
            return 0;
        }
    }
    
    int match = (fgetc(f1) == EOF && fgetc(f2) == EOF);
    fclose(f1);
    fclose(f2);
    return match;
}

int main() {
    printf("=== Hospital Medical Records Compression Tool ===\n\n");
    
    char input_file[100];
    printf("Enter patient record filename (e.g., patient_record.txt): ");
    scanf("%s", input_file);
    
    printf("\n--- Step 1: Compression ---\n");
    compress_file(input_file, "compressed.txt");
    
    printf("--- Step 2: Decompression ---\n");
    decompress_file("compressed.txt", "decompressed.txt");
    
    printf("--- Step 3: Integrity Verification ---\n");
    if (verify_integrity(input_file, "decompressed.txt")) {
        printf("✓ SUCCESS: Decompressed file matches original exactly!\n");
        printf("Lossless compression verified.\n");
    } else {
        printf("✗ ERROR: Files do not match!\n");
    }
    
    return 0;
}
