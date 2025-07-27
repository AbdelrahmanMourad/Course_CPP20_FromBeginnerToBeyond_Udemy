/*
========================================================================================================
<cstring> - Most Important and Commonly Used Functions (with Examples)
========================================================================================================
| <cstring> provides C-style string and memory manipulation functions.
| Commonly used in C++ for low-level operations on arrays and C-strings.
--------------------------------------------------------------------------------
| 1. memset
|    - Sets a block of memory to a specific value.
|    - Example: int arr[10]; memset(arr, 0, sizeof(arr)); // sets all to 0
|
| 2. memcpy
|    - Copies a block of memory from source to destination.
|    - Example: char src[] = "abc"; char dst[4]; memcpy(dst, src, 4);
|
| 3. memmove
|    - Like memcpy, but safe for overlapping memory regions.
|    - Example: memmove(arr+2, arr, 5*sizeof(int));
|
| 4. strlen
|    - Returns the length of a C-string (not including null terminator).
|    - Example: size_t len = strlen("hello"); // len = 5
|
| 5. strcpy / strncpy
|    - Copies a C-string (with or without length limit).
|    - Example: char dst[10]; strcpy(dst, "hi");
|    - Example: strncpy(dst, "hello", 4); // dst = "hell"
|
| 6. strcat / strncat
|    - Concatenates C-strings (with or without length limit).
|    - Example: char s[20] = "foo"; strcat(s, "bar"); // s = "foobar"
|
| 7. strcmp / strncmp
|    - Compares two C-strings (with or without length limit).
|    - Example: strcmp("abc", "abd"); // returns <0, 0, or >0
|
| 8. strchr / strrchr
|    - Finds first/last occurrence of a character in a C-string.
|    - Example: const char* p = strchr("hello", 'l'); // points to first 'l'
|
| 9. strstr
|    - Finds first occurrence of a substring in a C-string.
|    - Example: const char* p = strstr("hello world", "world"); // points to "world"
|
| 10. memcmp
|    - Compares two blocks of memory.
|    - Example: memcmp(arr1, arr2, n*sizeof(int));
========================================================================================================
*/
