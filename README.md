# Preprocessor 

preprocessing is a step of the code compilation process. It performs the following functions:
1) removing comments.
2) conditional compilation.
3) implementing macros/other directives.
4) including files.

## Prerequisites

1) functional understanding of the c language.
2) file I/O in the c language.
3) string manipulation.
4) data structures
5) understanding of preprocessing functions.
6) basic compiler theory/lexical analysis (identification of lines starting with //, reading input characters etc)

## Characteristics of My Preprocessor

1) object like macro implementation (eg., #define PI 3.14)
2) function like macro implementation (eg., #define MAX(a, b) ((a) > (b) ? (a) : (b)))
3) conditional compilation (#ifdef/ifndef)
4) file inclusion.