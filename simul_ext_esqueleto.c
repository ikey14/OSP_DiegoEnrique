#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include "cabeceras.h"
#define LONGITUD_COMANDO 100

void Printbytemaps(EXT_BYTE_MAPS *ext_bytemaps);
int ComprobarComando(char *strcomando, char *orden, char *argumento1, char *argumento2);
void LeeSuperBloque(EXT_SIMPLE_SUPERBLOCK *psup);
int BuscaFich(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, char *nombre);
void Directorio(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, char *nombre);
int Renombrar(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, char *nombreantiguo, char *nombrenuevo);
int Imprimir(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, EXT_DATOS *memdatos, char *nombre);
int Borrar(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos,
           EXT_BYTE_MAPS *ext_bytemaps, EXT_SIMPLE_SUPERBLOCK *ext_superblock,
           char *nombre,  FILE *fich);
int Copiar(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos,
           EXT_BYTE_MAPS *ext_bytemaps, EXT_SIMPLE_SUPERBLOCK *ext_superblock,
           EXT_DATOS *memdatos, char *nombreorigen, char *nombredestino,  FILE *fich);
void Grabarinodosydirectorio(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, FILE *fich);
void GrabarByteMaps(EXT_BYTE_MAPS *ext_bytemaps, FILE *fich);
void GrabarSuperBloque(EXT_SIMPLE_SUPERBLOCK *ext_superblock, FILE *fich);
void GrabarDatos(EXT_DATOS *memdatos, FILE *fich);

	 int main(){
	 int i,j;
	 unsigned long int m;
	 	char *orden;
	 	char *argumento1;
	 	char *argumento2;
     EXT_SIMPLE_SUPERBLOCK ext_superblock;
     EXT_BYTE_MAPS ext_bytemaps;
     EXT_BLQ_INODOS ext_blq_inodos;
     EXT_ENTRADA_DIR directorio[MAX_FICHEROS];
     EXT_DATOS memdatos[MAX_BLOQUES_DATOS];
     EXT_DATOS datosfich[MAX_BLOQUES_PARTICION];
     int entradadir;
     FILE *fent;
     
     // Lectura del fichero completo de una sola vez
     
     fent = fopen("particion.bin","r+b");
     fread(&datosfich, SIZE_BLOQUE, MAX_BLOQUES_PARTICION, fent);    
     
     
/*   memcpy(&ext_superblock,(EXT_SIMPLE_SUPERBLOCK *)&datosfich[0], SIZE_BLOQUE);
     memcpy(&directorio,(EXT_ENTRADA_DIR *)&datosfich[3], SIZE_BLOQUE);
     memcpy(&ext_bytemaps,(EXT_BLQ_INODOS *)&datosfich[1], SIZE_BLOQUE);
     memcpy(&ext_blq_inodos,(EXT_BLQ_INODOS *)&datosfich[2], SIZE_BLOQUE);
     memcpy(&memdatos,(EXT_DATOS *)&datosfich[4],MAX_BLOQUES_DATOS*SIZE_BLOQUE); */
     
     for (;;){
     	char* comando = (char*)calloc(LONGITUD_COMANDO, sizeof(char));
		if (comando == NULL)
		{
			printf("Error allocating memory\n");
			exit(0);
        }

	     do {
		 printf (">> ");
		 fflush(stdin);
		 fgets(comando, LONGITUD_COMANDO, stdin);
	     //printf("I am 1 \n");
	     orden = strtok(comando, "\n");
	     /* printf("Comando: %s\n", comando);
	     printf("Orden: %s\n", orden);
	     printf("Length of comando: %d\n", strlen(comando));
	     printf("Length of orden: %d\n", strlen(orden));
	     printf("Length of \"salir\": %d\n", strlen("salir"));
	     printf("strcmp between comando and orden: %d\n", strcmp(comando, orden)); */
		 } while (ComprobarComando(comando,orden,argumento1,argumento2) !=0);

         // Escritura de metadatos en comandos rename, remove, copy     
         /* GrabarByteMaps(&ext_bytemaps,fent);
         GrabarSuperBloque(&ext_superblock,fent);
	     int grabardatos;
         if (grabardatos)
           GrabarDatos(memdatos,fent);
         grabardatos = 0;
         //Si el comando es salir se habrán escrito todos los metadatos
         //faltan los datos y cerrar
         */

     	 //printf("I am 2 \n");
			if(strcmp(orden, "salir") == 0) {
				//GrabarDatos(memdatos,fent);
				//fclose(fent);
				printf("salir command executed\n");
				return 0;
			}else if(strcmp(orden, "info") == 0) {
				//LeeSuperBloque(&ext_superblock);
				printf("info command executed\n");
			}else if(strcmp(orden, "bytemaps") == 0) {
				//Printbytemaps(&ext_bytemaps);
				printf("Bytemaps command executed\n");
			}else if(strcmp(orden, "dir") == 0) {
				//Directorio(&directorio[MAX_FICHEROS],&ext_blq_inodos,argumento1);
				printf("dir command executed\n");
			}else if(strcmp(orden, "rename\n") == 0) {
				printf("rename command executed\n");
			}else if(strcmp(orden, "print") == 0) {
				printf("print command executed\n");
			}else if(strcmp(orden, "remove") == 0) {
				printf("remove command executed\n");
			}else if(strcmp(orden, "copy") == 0) {
				printf("copy command executed\n");
			}
     	//switch (orden) {
	        // case "salir":
	         //	GrabarDatos(&memdatos,fent);
         	//	fclose(fent);
         	//	return 0;
         	//case "info":
         	//	void LeeSuperBloque(EXT_SIMPLE_SUPERBLOCK *psup);


         	//	break;
         	//case "bytemaps":
         	//	void Printbytemaps();

         	//	break;
         //	case "dir":
         	//	Directorio(&directorio,&ext_blq_inodos);
         	//	break;
         	//case "rename":
         	//	break;
         	//case "print":
         	//	break;
         	//case"remove":
         	//	break;
         	//case "copy":
         	//	break;
         //	default:
         //		printf("invalid command[info,bytemaps,dir,rename,print,remove,copy]");
         //	break;
         }//


     }


int ComprobarComando(char *strcomando, char *orden, char *argumento1, char *argumento2){
	if (orden == NULL) {
		printf("No command entered.\n");
		return -1; // Invalid command
	}

	// Check for valid commands
	if (strcmp(orden, "salir") == 0 || strcmp(orden, "info") == 0 ||
		strcmp(orden, "bytemaps") == 0 || strcmp(orden, "dir") == 0 ||
		strcmp(orden, "rename") == 0 || strcmp(orden, "print") == 0 ||
		strcmp(orden, "remove") == 0 || strcmp(orden, "copy") == 0) {
		return 0; // Command is valid
		}

	printf("Invalid command: %s\n", orden);
	return -1; // Command not recognized
}

void Printbytemaps(EXT_BYTE_MAPS *ext_bytemaps) {
	printf("Inodes: %p\n", ext_bytemaps->bmap_inodos);
	printf("Blocks: %p\n",ext_bytemaps->bmap_bloques);


}
void LeeSuperBloque(EXT_SIMPLE_SUPERBLOCK *psup) {
	printf("block %d bytes\n",psup->s_block_size);
	printf("Partition inodes: %d \n",psup->s_inodes_count);
	printf("Free inodes: %d \n",psup->s_free_inodes_count);
	printf("Partition blocks: %d \n",psup->s_blocks_count);
	printf("Free blocks: %d \n",psup->s_free_blocks_count);
	printf("First Block of Data: %d \n",psup->s_first_data_block);


}
int Imprimir(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, EXT_DATOS *memdatos, char *nombre) {

}
void Directorio(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos,  char *nombre) {
int i;

	for(i=0;i<20;i++){
	printf("%p\tsize:%p\tblocks:%p",&directorio->dir_nfich,&inodos->INODE->size_fichero,&inodos->INODE->i_nbloque );
	}
}

int Borrar(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, EXT_BYTE_MAPS *ext_bytemaps,
			EXT_SIMPLE_SUPERBLOCK *ext_superblock, char *nombre,  FILE *fich)
{
	 	//Mark one i-node as free in the superblock, since we are getting rid of one file.
	 	ext_superblock->s_free_inodes_count++;
	 	return 0;
}
