/*
    Archivo:   shm_com.h

    Funcion:    Definicion de datos utilizados por los programas shared_mem1.c y shared_mem2.c

    Autores:    Dave Mathew y Richard Stone (Beginning Linux Programming, 4th Edition)

*/


#define TEXT_SZ 2048

struct shared_use_st {
   int  written_by_you;
   char some_text[TEXT_SZ];
};
