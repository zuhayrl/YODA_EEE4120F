#include <iostream>
#include <cstring>

int main() {
    
    char sentence[] = "Part 1";
    char newString[] = "\nPart 2";
    strcat(sentence, newString);
    printf("%s\n", sentence);
    size_t size_in_bytes = sizeof(sentence);
    printf("Size of sentence in bytes: %zu\n", size_in_bytes);

    return 0;
}