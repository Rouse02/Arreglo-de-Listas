#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#define DIM 30

///ESTRUCTURAS
typedef struct NotaAlumno {
    int calificacionAlumno;
    int nroLegajo;
    char nombreYapellido[DIM];
}NotaAlumno;

typedef struct Nodo {
    NotaAlumno infoNotaAlumno;
    struct Nodo *ptrSiguiente;
}Nodo;

typedef struct CeldaMaterias{
    int idMateria;
    char nombreMateria[DIM];
    Nodo *ptrListaNotas;
}CeldaMaterias;

typedef struct RegistroAlumno {
    int calificacionAlumno;
    int nroLegajo;
    char nombreYapellido[DIM];
    int idMateria;
    char nombreMateria[DIM];
}RegistroAlumno;
///PROTPTIPADO
int buscarMateria(CeldaMaterias arregloDeMaterias[], int validos);
int buscarCoincidenciaPorNombre(CeldaMaterias arregloDeMaterias[], int validos, char nombreMateria[]);
int buscarCoincidenciaPorId(CeldaMaterias arregloDeMaterias[], int validos, int id);
RegistroAlumno cargarRegistroAlumno(CeldaMaterias arregloDeMaterias[], int index, Nodo *ptrMateria);
/*----------------------------------------------------------------------------------------------------------------*/
int main(){

    ///Funcionamiento del sistema con las funciones básicas
    CeldaMaterias arregloDeMateriasPrimerAnio[DIM];
    int validosArregloMaterias = 0;

//    cargarNotasAlumnos(arregloDeMateriasPrimerAnio, &validosArregloMaterias);

    ///Pasar los datos ingresados a un Archivo Binario
    char nombreArhivoRegistroAlumnos[] = {"registroAlumnos.bin"};
//    cargarRegistroAlumnosEnArchivo(nombreArhivoRegistroAlumnos, arregloDeMateriasPrimerAnio, validosArregloMaterias);
    mostrarArchivoRegistroAlumnos(nombreArhivoRegistroAlumnos);

    ///Leer del archivo y pasar a un Arreglo de Listas. De antemano se que tengo 5 materias
    CeldaMaterias materiasPrimerCuatrimestreTUP[DIM];
    int validosArregloMaterias2 = 0;

    inicializarArregloMateriasCuatrimestreTUP(materiasPrimerCuatrimestreTUP);

    return 0;
}
/*----------------------------------------------------------------------------------------------------------------*/
///FUNCIONES
void inicializarLista(Nodo **ptrLista) {
    (*ptrLista) = NULL;
}

void crearNodo(Nodo **nuevoNodo, NotaAlumno infoNotaAlumno) {
    (*nuevoNodo)->infoNotaAlumno = infoNotaAlumno;
    (*nuevoNodo)->ptrSiguiente = NULL;
}

void agregarAlComienzo(Nodo **ptrLista, Nodo **nuevoNodo) {

    if((*ptrLista) == NULL) (*ptrLista) = (*nuevoNodo);

    else {
        (*nuevoNodo)->ptrSiguiente = (*ptrLista);
        (*ptrLista) = (*nuevoNodo);
    }
}

void mostrarLista(Nodo *ptrLista) {

    if(ptrLista != NULL) {

        printf("Nombre y Apellido --> %s \n", ptrLista->infoNotaAlumno.nombreYapellido);
        printf("Nro de Legajo --> %i \n", ptrLista->infoNotaAlumno.nroLegajo);
        printf("Calificacion --> %i \n", ptrLista->infoNotaAlumno.calificacionAlumno);
        printf("Puntero de la Lista --> %p \n", ptrLista);
        printf("Puntero siguiente --> %p \n\n", ptrLista->ptrSiguiente);

        mostrarLista(ptrLista->ptrSiguiente);
    }
}

int buscarCoincidenciaPorId(CeldaMaterias arregloDeMaterias[], int validos, int id) {

    for(int i = 0; i < validos; i++) {

        if(arregloDeMaterias[i].idMateria == id) return 1; //Hay coincidencia con el ID a crear
    }
    return 0; //No hay coincidencia con el ID a crear
}

int buscarCoincidenciaPorNombre(CeldaMaterias arregloDeMaterias[], int validos, char nombreMateria[]) {

    for(int i = 0; i < validos; i++) {
        if(strcmp(arregloDeMaterias[i].nombreMateria, nombreMateria) == 0) return 1; //Hay coincidencia con el ID a crear
    }
    return 0; //No hay coincidencia con el ID a crear
}

void crearMateria(CeldaMaterias arregloDeMaterias[], int *validos) {

    int flagNombreMateria = 0;
    int flagIdMateria = 0;
    char nombreMateriaValido[DIM];
    int idMateriaValido;

    if(*validos < DIM) {

        inicializarLista(&(arregloDeMaterias[*validos].ptrListaNotas));

        ///VERIFICACION DEL NOMBRE DE LA MATERIA
        do {
            printf("Ingrese el nombre de la Materia a crear --> ");
            fflush(stdin);
            gets(nombreMateriaValido);
            printf("\n");

            int resultadoBusquedaPorNombre = buscarCoincidenciaPorNombre(arregloDeMaterias, *validos, nombreMateriaValido);

            if(resultadoBusquedaPorNombre == 1)  printf("La Materia ingresada ya existe. Por favor ingrese otra Materia \n\n");

            else {
                strcpy(arregloDeMaterias[*validos].nombreMateria, nombreMateriaValido);
                flagNombreMateria = 1;
            }

        }while(flagNombreMateria == 0);
        ///VERIFICACION DEL ID DE LA MATERIA
        do {
            printf("Ingrese el ID de la Materia a crear --> ");
            fflush(stdin);

            if(scanf("%i", &idMateriaValido) == 1) {
                printf("\n");

                int resultadoBusquedaPorId = buscarCoincidenciaPorId(arregloDeMaterias, *validos, idMateriaValido);

                if(resultadoBusquedaPorId == 1) {
                    printf("\nEl ID ingresado ya existe. Por favor ingrese otro ID \n\n");
                    flagIdMateria = 0;
                }else {
                arregloDeMaterias[*validos].idMateria = idMateriaValido;
                flagIdMateria = 1;
                }
            }else {
                printf("\nNo se permiten caracteres. Vuelve a intentarlo \n\n");
                flagIdMateria = 0;
            }

        }while(flagIdMateria == 0);

        ///RETORNo LOS NUEVOS VALIDOS
        *validos += 1;

    }else printf("No hay espacio para otra Materia \n\n");
}

int buscarMateria(CeldaMaterias arregloDeMaterias[], int validos) {

    char nombreMateria[DIM];

    printf("Ingrese el nombre de la Materia a buscar --> ");
    fflush(stdin);
    gets(nombreMateria);
    printf("\n");

    for(int i = 0; i < validos; i++) {

        if(strcmp(arregloDeMaterias[i].nombreMateria, nombreMateria) == 0) return i; //Si la encontró, devuelve el índice en el arreglo
    }
    return -1;
}

void pedirInformacionNotaAlumno(NotaAlumno *informacionNotaAlumno) {

    int notaAlumno;
    int nroLegajoAlumno;

    int flagLegajoAlumno = 0;
    int flagCalificacionAlumno = 0;

        printf("Ingrese su Nombre y Apellido --> ");
        fflush(stdin);
        gets(informacionNotaAlumno->nombreYapellido);
        printf("\n");

    do {
        printf("Ingrese su Nro de Legajo --> ");
        fflush(stdin);
        if(scanf("%i", &nroLegajoAlumno) == 1) {

            printf("\n");
            informacionNotaAlumno->nroLegajo = nroLegajoAlumno;
            flagLegajoAlumno = 1;

        }else printf("\nNo ingresaste un Numero. Vuelve a intentarlo \n\n");

    }while(flagLegajoAlumno == 0);

    do {
        printf("Ingrese su Calificacion --> ");
        fflush(stdin);
        if(scanf("%i", &notaAlumno) == 1) {

            if((notaAlumno >= 0) && (notaAlumno <= 10)) {
                printf("\n");
                informacionNotaAlumno->calificacionAlumno = notaAlumno;
                flagCalificacionAlumno = 1;
            }else {
                printf("\nLa calificacion ingresada no es valida. Vuelve a intentarlo \n\n");
                flagCalificacionAlumno = 0;
            }
        }else {
            printf("\nNo ingresaste un Numero. Vuelve a intentarlo \n\n");
            flagCalificacionAlumno = 0;
        }
    }while(flagCalificacionAlumno == 0);
}

void cargarNota(CeldaMaterias arregloDeMaterias[], int indexMateria) {

    char eleccion;

    do {
        NotaAlumno informacionAlumno;
        pedirInformacionNotaAlumno(&informacionAlumno);

        Nodo *nuevoNodo = (Nodo *) malloc(sizeof(Nodo));
        crearNodo(&nuevoNodo, informacionAlumno);
        agregarAlComienzo(&(arregloDeMaterias[indexMateria].ptrListaNotas), &nuevoNodo);

        printf("Pulse 's' para cargar otra nota en la Materia |%s| --> ", arregloDeMaterias[indexMateria].nombreMateria);
        fflush(stdin);
        scanf("%c", &eleccion);
        printf("\n");

        }while(eleccion == 's' || eleccion == 'S');
}

void cargarNotasAlumnos(CeldaMaterias arregloDeMaterias[], int *validos) {

    char eleccion;
    char eleccionCargarNotaEnMateria;
    char eleccionCrearMateria;
    char eleccionMostrarMateria;

    do {
        int resultadoBusquedaMateria = buscarMateria(arregloDeMaterias, *validos);

        if(resultadoBusquedaMateria != -1) {

            int indexMateria = resultadoBusquedaMateria;
            printf("Existe la Materia. ");
            printf("Pulse 's' para agregar una nota en la Materia |%s| --> ", arregloDeMaterias[indexMateria].nombreMateria);
            fflush(stdin);
            scanf("%c", &eleccionCargarNotaEnMateria);
            printf("\n");

            if(eleccionCargarNotaEnMateria == 's' || eleccionCargarNotaEnMateria == 'S') cargarNota(arregloDeMaterias, indexMateria);
            }

        if(resultadoBusquedaMateria == -1) {
            printf("La materia no existe. ");
            printf("Pulse 's' para crear una Materia --> ");
            fflush(stdin);
            scanf("%c", &eleccionCrearMateria);
            printf("\n");

            if(eleccionCrearMateria == 's' || eleccionCrearMateria == 'S') {

                crearMateria(arregloDeMaterias, validos);

                char eleccionCargarNotasMateriaCreada;

                printf("Pulse 's' para agregar una nota en la Materia creada --> ");
                fflush(stdin);
                scanf("%c", &eleccionCargarNotasMateriaCreada);
                printf("\n");

                if(eleccionCargarNotasMateriaCreada == 's' || eleccionCargarNotasMateriaCreada == 'S') cargarNota(arregloDeMaterias, (*validos -1));
            }
        }

        printf("Pulse 's' para mostrar notas --> ");
        fflush(stdin);
        scanf("%c", &eleccionMostrarMateria);
        printf("\n");

        if(eleccionMostrarMateria == 's' || eleccionMostrarMateria == 'S') {

            int resultadoBusquedaMateria = buscarMateria(arregloDeMaterias, *validos);

            if(resultadoBusquedaMateria != -1) mostrarLista(arregloDeMaterias[resultadoBusquedaMateria].ptrListaNotas);

            else printf("Eror: No hay coincidencias con la Materia \n\n");
        }

        printf("Pulse 's' para cargar otra nota en alguna Materia --> ");
        fflush(stdin);
        scanf("%c", &eleccion);
        printf("\n");

    }while(eleccion == 's' || eleccion == 'S');
}

RegistroAlumno cargarRegistroAlumno(CeldaMaterias arregloDeMaterias[], int index, Nodo *ptrMateria) {

    RegistroAlumno auxRegistroAlumno;

    strcpy(auxRegistroAlumno.nombreMateria, arregloDeMaterias[index].nombreMateria);
    auxRegistroAlumno.idMateria = arregloDeMaterias[index].idMateria;
    strcpy(auxRegistroAlumno.nombreYapellido, ptrMateria->infoNotaAlumno.nombreYapellido);
    auxRegistroAlumno.nroLegajo = ptrMateria->infoNotaAlumno.nroLegajo;
    auxRegistroAlumno.calificacionAlumno = ptrMateria->infoNotaAlumno.calificacionAlumno;

    return auxRegistroAlumno;
}

void cargarRegistroAlumnosEnArchivo(char nombreArchivoRegistroAlumnos[], CeldaMaterias arregloDeMaterias[], int validos) {
    RegistroAlumno auxRegistroAlumno;

    FILE *ptrArchivoRegistroAlumno = fopen(nombreArchivoRegistroAlumnos, "ab");

    if (ptrArchivoRegistroAlumno == NULL) printf("Error al abrir el Archivo \n\n");

    else {
        for (int i = 0; i < validos; i++) {

            Nodo *auxListaMateria = arregloDeMaterias[i].ptrListaNotas;

            while (auxListaMateria != NULL) {

                auxRegistroAlumno = cargarRegistroAlumno(arregloDeMaterias, i, auxListaMateria);
                fwrite(&auxRegistroAlumno, sizeof(RegistroAlumno), 1, ptrArchivoRegistroAlumno);
                auxListaMateria = auxListaMateria->ptrSiguiente; // Avanzar al siguiente nodo de la Lista
            }
        }
        fclose(ptrArchivoRegistroAlumno);
    }
}

void mostrarRegistroAlumno( RegistroAlumno unRegistroAlumno) {

    printf("Materia --> |%s| \n", unRegistroAlumno.nombreMateria);
    printf("ID Materia --> |%i| \n", unRegistroAlumno.idMateria);
    printf("Nombre y Apellido --> |%s| \n", unRegistroAlumno.nombreYapellido);
    printf("Nro Legajo --> |%i| \n", unRegistroAlumno.nroLegajo);
    printf("Calificacion --> |%i| \n\n", unRegistroAlumno.calificacionAlumno);

}

void mostrarArchivoRegistroAlumnos(char nombreArchivoRegistroAlumnos[]) {

    RegistroAlumno auxRegistroAlumno;

    FILE *ptrArchivoRegistroAlumno = fopen(nombreArchivoRegistroAlumnos, "rb");

    if(ptrArchivoRegistroAlumno == NULL) printf("Error al abrir el Archivo \n\n");

    else {
        while(!feof(ptrArchivoRegistroAlumno)) {
            fread(&auxRegistroAlumno, sizeof(RegistroAlumno), 1, ptrArchivoRegistroAlumno);

            if(!feof(ptrArchivoRegistroAlumno)) mostrarRegistroAlumno(auxRegistroAlumno);
        }

        fclose(ptrArchivoRegistroAlumno);
    }
}

void inicializarArregloMateriasCuatrimestreTUP(CeldaMaterias materiasPrimerCuatrimestreTUP[]) {

    for(int i = 0; i < 5; i++) {

        materiasPrimerCuatrimestreTUP[i].idMateria = -1;
        strcpy(materiasPrimerCuatrimestreTUP[i].nombreMateria, "");
        ///inicializar listas en null
    }
}

void mostrarMaterias(CeldaMaterias materiasPrimerCuatrimestreTUP[]) {

    for(int i = 0; i < 5; i++) {

        printf("Posicion del Arreglo: %i \n", i);
        printf("Materia: %s \n", materiasPrimerCuatrimestreTUP[i].nombreMateria);
        printf("ID Materia: %i \n\n", materiasPrimerCuatrimestreTUP[i].idMateria);
    }

}

void pasarDeArchivoToArregloDeListas(char nombreArchivo[], CeldaMaterias arregloMaterias[], int *validos) {

    FILE *ptrArchivoRegistroAlumno = fopen(nombreArchivo, "rb");

    if(ptrArchivoRegistroAlumno == NULL) printf("Error al abrir el Archivo \n\n");

    else {
        RegistroAlumno auxRegistroAlumno; //Buffer

        while(!feof(ptrArchivoRegistroAlumno)) {

            fread(&auxRegistroAlumno, sizeof(RegistroAlumno), 1, ptrArchivoRegistroAlumno);

            if(!feof(ptrArchivoRegistroAlumno)) {




            }
        }
        fclose(ptrArchivoRegistroAlumno);
    }
}




