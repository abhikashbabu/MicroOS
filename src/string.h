#ifndef STRING_H
#define STRING_H

// Strings compare karna (Puraana code)
static inline int strcmp(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

// Number ko string mein convert karna (NEW)
static inline void itoa(int num, char* str) {
    int i = 0;
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return;
    }
    
    // Digits extract karna (ulta order mein aayega)
    while (num != 0) {
        int rem = num % 10;
        str[i++] = rem + '0';
        num = num / 10;
    }
    str[i] = '\0';
    
    // String ko seedha karna (Reverse)
    int start = 0;
    int end = i - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

#endif