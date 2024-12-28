#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include "cabeceras.h"
#define LONGITUD_COMANDO 100

void Printbytemaps(EXT_BYTE_MAPS *ext_bytemaps);

int ComprobarComando(char *strcomando, char **orden, char **argumento1, char **argumento2, char *token);

void LeeSuperBloque(EXT_SIMPLE_SUPERBLOCK *psup);

int BuscaFich(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, char *nombre);

void Directorio(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos);

int Renombrar(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, char *nombreantiguo, char *nombrenuevo);

int Imprimir(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, EXT_DATOS *memdatos, char *nombre);

int Borrar(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos,
           EXT_BYTE_MAPS *ext_bytemaps, EXT_SIMPLE_SUPERBLOCK *ext_superblock,
           char *nombre, FILE *fich);

int Copiar(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos,
           EXT_BYTE_MAPS *ext_bytemaps, EXT_SIMPLE_SUPERBLOCK *ext_superblock,
           EXT_DATOS *memdatos, char *nombreorigen, char *nombredestino, FILE *fich);

void Grabarinodosydirectorio(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, FILE *fich);

void GrabarByteMaps(EXT_BYTE_MAPS *ext_bytemaps, FILE *fich);

void GrabarSuperBloque(EXT_SIMPLE_SUPERBLOCK *ext_superblock, FILE *fich);

void GrabarDatos(EXT_DATOS *memdatos, FILE *fich);

int main() {
    int i, j;
    unsigned long int m;
    char *orden = (char *) calloc(LONGITUD_COMANDO, sizeof(char));
    char *argumento1 = (char *) calloc(LONGITUD_COMANDO, sizeof(char));
    char *argumento2 = (char *) calloc(LONGITUD_COMANDO, sizeof(char));
    char *token = (char *) calloc(LONGITUD_COMANDO, sizeof(char));
    if (orden == NULL || argumento1 == NULL || argumento2 == NULL || token == NULL) {
        printf("Error allocating memory\n");
        exit(0);
    }
    EXT_SIMPLE_SUPERBLOCK ext_superblock;
    EXT_BYTE_MAPS ext_bytemaps;
    EXT_BLQ_INODOS ext_blq_inodos;
    EXT_ENTRADA_DIR directorio[MAX_FICHEROS];
    EXT_DATOS memdatos[MAX_BLOQUES_DATOS];
    EXT_DATOS datosfich[MAX_BLOQUES_PARTICION];
    int entradadir;
    FILE *fent;

    // Lectura del fichero completo de una sola vez
    // Problem found: fent was a NULL pointer, so the file was not being opened
    // Temporary solution: introduce absolute path to the "particion.bin" file. A universal solution will be implemented when found.
    //fent = fopen("particion.bin","r+b");

    //ENRIQUE FILE OPEN ABSOLUTE PATH
    fent = fopen("C:\\Users\\ikeum\\OneDrive\\Escritorio\\OS_EXT_PROJECT\\OSP_DiegoEnrique\\particion.bin","r+b");
    //DIEGO FILE OPEN ABSOLUTE PATH
    // TODO allow relative paths
    //fent = fopen("particion.bin", "r+b");
    if (fent == NULL) {
        printf("Error opening partition file, terminating program.\n");
        return 0;
    }

    fread(&datosfich, SIZE_BLOQUE, MAX_BLOQUES_PARTICION, fent);

    memcpy(&ext_superblock, (EXT_SIMPLE_SUPERBLOCK *) &datosfich[0], SIZE_BLOQUE);
    memcpy(&directorio, (EXT_ENTRADA_DIR *) &datosfich[3], SIZE_BLOQUE);
    memcpy(&ext_bytemaps, (EXT_BLQ_INODOS *) &datosfich[1], SIZE_BLOQUE);
    memcpy(&ext_blq_inodos, (EXT_BLQ_INODOS *) &datosfich[2], SIZE_BLOQUE);
    memcpy(&memdatos, (EXT_DATOS *) &datosfich[4],MAX_BLOQUES_DATOS * SIZE_BLOQUE);

    for (;;) {
        char *comando = (char *) calloc(LONGITUD_COMANDO, sizeof(char));
        if (comando == NULL) {
            printf("Error allocating memory\n");
            exit(0);
        }

        do {
            printf(">> ");
            fflush(stdin);
            fgets(comando, LONGITUD_COMANDO, stdin);
            //printf("I am 1 \n");
            //orden = strtok(comando, "\n");
            //SplitCommand(comando, orden, argumento1, argumento2, token);
            //printf("Comando: %s\n", comando);
            //printf("Orden: %s\n", orden);
            //printf("Length of comando: %d\n", strlen(comando));
            //printf("Length of orden: %d\n", strlen(orden));
            //printf("Length of \"salir\": %d\n", strlen("salir"));
            //printf("strcmp between comando and orden: %d\n", strcmp(comando, orden));
            //printf("Directorio pointer: %p\n", &directorio);
            //printf("File 1: %s\t I-Node: %d\t Size: %d\n", directorio[0].dir_nfich, directorio[0].dir_inodo, ext_blq_inodos.blq_inodos[directorio[0].dir_inodo].size_fichero);
            //printf("File 2: %s\t I-Node: %d\t Size: %d\n", directorio[1].dir_nfich, directorio[1].dir_inodo, ext_blq_inodos.blq_inodos[directorio[1].dir_inodo].size_fichero);
            //printf("File 3: %s\t I-Node: %d\t Size: %d\n", directorio[2].dir_nfich, directorio[2].dir_inodo, ext_blq_inodos.blq_inodos[directorio[2].dir_inodo].size_fichero);
            //printf("File 4: %s\t I-Node: %d\t Size: %d\n", directorio[3].dir_nfich, directorio[3].dir_inodo, ext_blq_inodos.blq_inodos[directorio[3].dir_inodo].size_fichero);


        } while (ComprobarComando(comando, &orden, &argumento1, &argumento2, token) != 0);

        // Escritura de metadatos en comandos rename, remove, copy
        //Grabarinodosydirectorio(directorio, &ext_blq_inodos, fent);
        //GrabarByteMaps(&ext_bytemaps, fent);
        //GrabarSuperBloque(&ext_superblock, fent);
        int grabardatos = 0;
        //GrabarDatos(memdatos, fent);
        //Si el comando es salir se habrán escrito todos los metadatos
        //faltan los datos y cerrar

        //printf("I am 2 \n");
        printf("Orden: %s\n", orden);
        if (strcmp(orden, "salir") == 0) {
            //GrabarDatos(memdatos, fent);
            fclose(fent);
            printf("salir command executed\n");
            return 0;
        } else if (strcmp(orden, "info") == 0) {
            LeeSuperBloque(&ext_superblock);
            printf("info command executed\n");
        } else if (strcmp(orden, "bytemaps") == 0) {
            Printbytemaps(&ext_bytemaps);
            printf("Bytemaps command executed\n");
        } else if (strcmp(orden, "dir") == 0) {
            Directorio(directorio, &ext_blq_inodos);
            printf("dir command executed\n");
        } else if (strcmp(orden, "rename") == 0) {
            if (argumento1 == NULL)
            {
                printf("NULL is not a valid file name. Try again.\n");
            }
            else if (argumento2 == NULL)
            {
                printf("NULL is not a valid file name, so you can't rename a file to that. Try again.\n");
            }
            else if (argumento1 != NULL && argumento2 != NULL)
            {
                Renombrar(directorio, &ext_blq_inodos, argumento1, argumento2);
                grabardatos = 1;
                printf("rename command executed\n");
            }

        } else if (strcmp(orden, "print") == 0) {
            if (argumento1 == NULL)
            {
                printf("NULL is not a valid file name. Try again.\n");
            }
            else if (argumento1 != NULL)
            {
                Imprimir(directorio, &ext_blq_inodos, datosfich, argumento1);
                printf("print command executed\n");
            }

        } else if (strcmp(orden, "remove") == 0) {
            if (argumento1 == NULL)
            {
                printf("NULL is not a valid file name. Try again.\n");
            }
            else if (argumento1 != NULL)
            {
                Borrar(directorio, &ext_blq_inodos, &ext_bytemaps, &ext_superblock, argumento1, fent);
                grabardatos = 1;
                printf("remove command executed\n");
            }
        } else if (strcmp(orden, "copy") == 0) {
            if (argumento1 == NULL)
            {
                printf("NULL is not a valid file name. Try again.\n");
            }
            else if (argumento2 == NULL)
            {
                printf("NULL is not a valid file name, so you can't name the new file NULL. Try again.\n");
            }
            else if (argumento1 != NULL && argumento2 != NULL)
            {
                int copyStatus = Copiar(directorio, &ext_blq_inodos, &ext_bytemaps, &ext_superblock, memdatos, argumento1, argumento2, fent);
                grabardatos = 1;
                printf("copy command executed with status: %d\n", copyStatus);
            }
        }
    }
}

int ComprobarComando(char *strcomando, char **orden, char **argumento1, char **argumento2, char *token) {
    //---------COMMAND SPLITTING---------//
    // If the command is NULL, then we return invalid command before doing anything to avoid a crash
    if (strcomando == NULL)
    {
        printf("Null command, please introduce something. \n");
        return -1;
    }
    // Single line fix, now it is not neccessary to put an extar space when using a comand with no arguments.
    strcomando = strtok(strcomando, "\n");
    printf("Comando: %s\n", strcomando);
    token = strtok(strcomando, " ");

    for (int i = 0; i < 3; i++) {
        if (token != NULL) {
            if (i == 0) {
                *orden = token;
                *argumento1 = NULL;
                *argumento2 = NULL;
            }

            if (i == 1) {
                *argumento1 = token;
                *argumento2 = NULL;
            }

            if (i == 2) {
                *argumento2 = token;
            }
            //printf("TOKEN: %s\n", token);
            token = strtok(NULL, " ");
        }
    }

     printf("Comando: %s\n",strcomando);
     printf("Orden: %s\n",*orden);
     printf("Argumento 1: %s\n",*argumento1);
     printf("Argumento 2: %s\n",*argumento2);
     //printf("Length of comando: %d\n", strlen(strcomando));
     //printf("Length of orden: %d\n", strlen(*orden));
     //printf("Length of \"dir\": %d\n", strlen("dir"));
    //---------END COMMAND SPLITTING-----------//


    if (*orden == NULL) {
        printf("No command entered.\n");
        return -1; // Invalid command
    }

    // Check for valid commands
    if (strcmp(*orden, "salir") == 0 || strcmp(*orden, "info") == 0 ||
        strcmp(*orden, "bytemaps") == 0 || strcmp(*orden, "dir") == 0 ||
        strcmp(*orden, "rename") == 0 || strcmp(*orden, "print") == 0 ||
        strcmp(*orden, "remove") == 0 || strcmp(*orden, "copy") == 0) {
        return 0; // Command is valid
    }

    printf("Invalid command: %s\n", *orden);
    return -1; // Command not recognized
}


void Printbytemaps(EXT_BYTE_MAPS *ext_bytemaps) {
    unsigned char *inodes = malloc(MAX_INODOS * sizeof(unsigned char));
    unsigned char *blocks = malloc(25 * sizeof(unsigned char));
    for (int i = 0; i < MAX_INODOS; i++) {
        inodes[i] = ext_bytemaps->bmap_inodos[i];
    }
    printf("Inodes: ");
    for (int i = 0; i < MAX_INODOS; i++) {
        printf("%x ", inodes[i]);
    }
    printf("\n");
    printf("Blocks[0-25]: ");
    for (int j = 0; j < 25; j++) {
        blocks[j] = ext_bytemaps->bmap_bloques[j];
    }
    for (int j = 0; j < 25; j++) {
        printf("%x ", blocks[j]);
    }
    printf("\n");
    free(inodes);
    free(blocks);
}

void LeeSuperBloque(EXT_SIMPLE_SUPERBLOCK *psup) {
    printf("block %d bytes\n", psup->s_block_size);
    printf("Partition inodes: %d \n", psup->s_inodes_count);
    printf("Free inodes: %d \n", psup->s_free_inodes_count);
    printf("Partition blocks: %d \n", psup->s_blocks_count);
    printf("Free blocks: %d \n", psup->s_free_blocks_count);
    printf("First Block of Data: %d \n", psup->s_first_data_block);
}

int Imprimir(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, EXT_DATOS *memdatos, char *nombre) {
    int found = -1;

    // Search for the file in the directory (once found, we break the loop)
    for (int i = 0; i < MAX_FICHEROS; i++) {
        if (directorio[i].dir_inodo != NULL_INODO && strcmp(directorio[i].dir_nfich, nombre) == 0) {
            found = i;
            break;
        }
    }

    // If the file is not found, return an error telling the user that the file either doesn't exist or wasn't found
    if (found == -1) {
        printf("Error: File \"%s\" doesn't exist or was not found.\n", nombre);
        return -1;
    }
    char *printText = malloc(sizeof(char) * SIZE_BLOQUE);

    for (int j = 0; j < 1; j++) {
        unsigned short int blocks = inodos[directorio[found].dir_inodo].blq_inodos->i_nbloque[j];
        memcpy(printText, &memdatos[blocks], SIZE_BLOQUE);
        printf("%s\n", printText);
    }


    printf("\n");

    free(printText);
    return 0;
}

void Directorio(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos)
{
    // We start the loop with 1 instead of 0 so that we don't list the directory itself.
    for (int i = 1; i < MAX_INODOS; i++)
    {
        if (directorio[i].dir_inodo != NULL_INODO)
        {
            //Now that we know that the i-node isn't null, we search it in the inodes array and print the file's attributes.
            EXT_SIMPLE_INODE *inode = &inodos->blq_inodos[directorio[i].dir_inodo];
            printf("%s\tSize: %d\tI-Node: %d\tBlocks Occupied: ", directorio[i].dir_nfich, inode->size_fichero, directorio[i].dir_inodo);

            //To know which blocks the file is occuppying, we need to go through i-node blocks array to see which ones aren't null
            //If they aren't null then they are in use by the file.
            for (int j = 0; j < MAX_NUMS_BLOQUE_INODO; j++)
            {
                if (inode->i_nbloque[j] != NULL_BLOQUE)
                {
                    printf("%d ", inode->i_nbloque[j]);
                }
            }
            printf("\n");
        }
    }
}


int Borrar(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, EXT_BYTE_MAPS *ext_bytemaps,
           EXT_SIMPLE_SUPERBLOCK *ext_superblock, char *nombre, FILE *fich) {
    int found = -1;

    // Search for the file in the directory (once found, we break the loop)
    for (int i = 0; i < MAX_FICHEROS; i++) {
        // This happens when the file we want to delete is found (not NULL inode and the name matches)
        if (directorio[i].dir_inodo != NULL_INODO && strcmp(directorio[i].dir_nfich, nombre) == 0) {
            // Found takes the value of the index where the file we want to delete is
            found = i;
            break;
        }
    }

    // If the file is not found, return an error telling the user that the file either doesn't exist or wasn't found
    if (found == -1) {
        printf("Error: File \"%s\" doesn't exist or was not found.\n", nombre);
        return -1;
    }

    // Store the inode index in an int variable for use below
    // (Technically not neccessary, but makes the code look a lot cleaner)
    int inode_index = directorio[found].dir_inodo;

    // Free the data blocks associated with the file
    for (int i = 0; i < MAX_NUMS_BLOQUE_INODO; i++) {
        if (inodos->blq_inodos[inode_index].i_nbloque[i] != NULL_BLOQUE) {
            // We store the block index in an int variable for use below
            // (Technically not neccessary, but makes the code look a lot cleaner)
            int block_index = inodos->blq_inodos[inode_index].i_nbloque[i];
            // Mark block as free
            ext_bytemaps->bmap_bloques[block_index] = 0;
            // Increment free block count
            ext_superblock->s_free_blocks_count++;
            // Clear block reference
            inodos->blq_inodos[inode_index].i_nbloque[i] = NULL_BLOQUE;
        }
    }

    // Free the inode and increment the free inode count in the superblock to reflect this change
    ext_bytemaps->bmap_inodos[inode_index] = 0;
    ext_superblock->s_free_inodes_count++;

    // Clear the directory entry
    directorio[found].dir_inodo = NULL_INODO;
    memset(directorio[found].dir_nfich, 0, LEN_NFICH);

    // Tell the user that the file was deleted and return 0 to signal correct execution.
    printf("File \"%s\" deleted.\n", nombre);
    return 0;
}


void GrabarDatos(EXT_DATOS *memdatos, FILE *fich) {
    // Move the file pointer to the first data block in the partition
    fseek(fich, PRIM_BLOQUE_DATOS * SIZE_BLOQUE, SEEK_SET);

    // Write the data blocks to the file
    int binWrite;
    binWrite = fwrite(memdatos, SIZE_BLOQUE, MAX_BLOQUES_DATOS, fich);

    printf("Objects written (DATA): %d\n", binWrite);

    // Verify that all blocks were written correctly
    if (binWrite != MAX_BLOQUES_DATOS) {
        printf("Error: Failed to write data blocks to file.\n");
    } else {
        printf("Data blocks successfully written to file.\n");
    }
}

// Almost copy paste from the "GrabarDatos" function
void GrabarSuperBloque(EXT_SIMPLE_SUPERBLOCK *ext_superblock, FILE *fich) {
    // Move the file pointer to the location of the superblock (block 0)
    fseek(fich, 0, SEEK_SET);

    // Write the superblock to the file
    int binWrite = fwrite(ext_superblock, SIZE_BLOQUE, 1, fich);

    printf("Objects written (SUPERBLOCK): %d\n", binWrite);

    // Verify that the superblock was written correctly
    if (binWrite != 1) {
        printf("Error: Failed to write the superblock to the file.\n");
    } else {
        printf("Superblock successfully written to file.\n");
    }
}

// Almost copy paste from the "GrabarDatos" function
void GrabarByteMaps(EXT_BYTE_MAPS *ext_bytemaps, FILE *fich) {
    // Move the file pointer to the location of the bytemaps (block 1)
    fseek(fich, SIZE_BLOQUE, SEEK_SET);

    // Write the bytemaps to the file
    int binWrite = fwrite(ext_bytemaps, SIZE_BLOQUE, 1, fich);

    printf("Objects written (BYTEMAPS): %d\n", binWrite);

    // Verify if the bytemaps block was written to correctly
    if (binWrite != 1) {
        printf("Error: Failed to write the bytemaps to the file.\n");
    } else {
        printf("Bytemaps successfully written to file.\n");
    }
}

// Almost copy paste from the "GrabarDatos" function, but this one is a 2x1 function (has to write the inodes and the directory)
void Grabarinodosydirectorio(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, FILE *fich) {
    // Write the inodes block to its location (block 2)
    // (Move file pointer first and write later)
    fseek(fich, 2 * SIZE_BLOQUE, SEEK_SET);
    int binWriteInode = fwrite(inodos, SIZE_BLOQUE, 1, fich);

    printf("Objects written (INODES): %d\n", binWriteInode);

    // Verify if the inodes block was written to correctly
    if (binWriteInode != 1) {
        printf("Error: Failed to write inodes block to the file.\n");
    } else {
        printf("Inodes block successfully written to file.\n");
    }

    // Write the directory block to its location (block 3)
    // (Move file pointer first and write later)
    fseek(fich, 3 * SIZE_BLOQUE, SEEK_SET);
    int binWriteDir = fwrite(directorio, SIZE_BLOQUE, 1, fich);

    printf("Objects written (DIRECTORY): %d\n", binWriteDir);

    // Verify if the directory block was written to correctly
    if (binWriteDir != 1) {
        printf("Error: Failed to write directory block to the file.\n");
    } else {
        printf("Directory block successfully written to file.\n");
    }
}


int Renombrar(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, char *nombreantiguo, char *nombrenuevo) {
    int foundOld = -1;
    int foundNew = -1;

    // Search for the old name and check if the new name already exists
    for (int i = 0; i < MAX_FICHEROS; i++) {
        if (directorio[i].dir_inodo != NULL_INODO) {
            // This happens when the file to be renamed is found
            if (strcmp(directorio[i].dir_nfich, nombreantiguo) == 0) {
                // Found old takes the value of the index where the file we want to rename is
                foundOld = i;
            }
            // This happens when a file is found with the new name already in use
            if (strcmp(directorio[i].dir_nfich, nombrenuevo) == 0) {
                // Found new takes the value of the index where there is a file with the new name.
                foundNew = i;
            }
        }
    }

    // If the old file is not found, return an error and tell the user that the file doesn't exist
    if (foundOld == -1) {
        printf("Error: File \"%s\" doesn't exist or was not found.\n", nombreantiguo);
        return -1;
    }

    // If the new name already exists, return an error and tell the user that that name is already taken
    if (foundNew != -1) {
        printf("Error: File \"%s\" already exists.\n", nombrenuevo);
        return -1;
    }

    // Rename the file
    // (when specifying the amount of chars to be copied, we add -1 because the count starts from 0, not 1)
    strncpy(directorio[foundOld].dir_nfich, nombrenuevo, LEN_NFICH - 1);
    // Make sure that the last char is the "string end" char (VERY IMPORTANT, IF NOT DONE THERE CAN BE MEMORY ISSUES)
    directorio[foundOld].dir_nfich[LEN_NFICH - 1] = '\0';

    //File renamed, we return 0 to signal that everything went well
    printf("File \"%s\" renamed to \"%s\".\n", nombreantiguo, nombrenuevo);
    return 0;
}

int Copiar(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos,
           EXT_BYTE_MAPS *ext_bytemaps, EXT_SIMPLE_SUPERBLOCK *ext_superblock,
           EXT_DATOS *memdatos, char *nombreorigen, char *nombredestino, FILE *fich) {
    int foundDest = -1;
    int foundSrc = -1;
    int freeFile = 0;
    unsigned int freeblocks = 0;
    int freeInode = 0;
    for (int i = 0; i < MAX_FICHEROS; i++) {
        // This happens when the file we want to delete is found (not NULL inode and the name matches)
        if (directorio[i].dir_inodo != NULL_INODO && strcmp(directorio[i].dir_nfich, nombreorigen) == 0) {
            // Found takes the value of the index where the file we want to delete is
            foundSrc = i;
            break;
        }
    }
    for (int i = 0; i < MAX_FICHEROS; i++) {
        // This happens when the file we want to delete is found (not NULL inode and the name matches)
        if (directorio[i].dir_inodo != NULL_INODO && strcmp(directorio[i].dir_nfich, nombredestino) == 0) {
            // Found takes the value of the index where the file we want to delete is
            foundDest = i;
            break;
        }
    }

    // If the file is not found, return an error telling the user that the file either doesn't exist or wasn't found
    if (foundSrc == -1) {
        printf("Error: File \"%s\" doesn't exist or was not found.\n", nombreorigen);
        return -1;
    }
    if (foundDest != -1) {
        printf("You cannot paste a file in the position of another file\n");
        return -1;
    }
    //check for a free file postion
    for (int i = 0; i < MAX_FICHEROS; i++) {
        if (directorio[i].dir_inodo != NULL_INODO) {
            freeFile = i;
        }
    }
    for (int i = 0; i < MAX_INODOS; i++) {
        if (inodos[i].blq_inodos != NULL) {
            freeInode = i;
        }
    }
    memcpy(directorio[freeFile].dir_nfich, directorio[foundSrc].dir_nfich,LEN_NFICH);
    memcpy(&inodos->blq_inodos[freeInode].size_fichero,
           &inodos->blq_inodos[directorio[foundSrc].dir_inodo].size_fichero, sizeof(unsigned int));

    for (int i = 0; i < MAX_NUMS_BLOQUE_INODO; i++) {
        if (inodos[freeInode].blq_inodos == NULL) {
            freeblocks = i;
            memcpy(&inodos[freeInode].blq_inodos[freeblocks], &inodos[directorio[foundSrc].dir_inodo].blq_inodos,
                   sizeof(unsigned int));
        }
    }
    for (int k = 0; k < MAX_INODOS; k++) {
        if (k == freeInode) {
            memcpy(&ext_bytemaps->bmap_inodos[k], &inodos->blq_inodos[freeInode], sizeof(unsigned int));
        }

        for (int i1 = 0; i1 < MAX_BLOQUES_PARTICION; i1++) {
            if (i1 == freeblocks) {
                memcpy(&ext_bytemaps->bmap_bloques[i1], &inodos->blq_inodos[freeInode].i_nbloque, sizeof(unsigned int));
            }
        }


        return 0;
    }
}
