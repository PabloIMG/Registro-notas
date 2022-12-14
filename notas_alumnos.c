#include <stdio.h>
#include <windows.h>

//* .: Estructuras :. *//
typedef struct alumno
{
    char rut[12]; // Con puntos y guión.
    char nombre[15];
    char apellido_paterno[20];
    char apellido_materno[20];
    float nota_examen1;
    float nota_examen2;
    float promedio_tests;
}ALUMNO;

//* .: Variables globales :. *//
ALUMNO curso[10];

int notasIngresadas_Examen1 = 0;
int notasIngresadas_Examen2 = 0;
int notasIngresadas_Tests = 0;

int alumnoSeleccionado;

//* .: Definición de funciones :. *//
int menu();
void ingresar_Notas(int modo);
float obtenerPromedioAlumno(int modo); // 1: Obtener manualmente, 2: Obtener automáticamente.
void obtenerPromedioCurso();

//* .: Programa Principal :. *//
int main() {

    //? Variables.
    int opcion;
    float promedioAlumno;
    
    do {
        opcion = menu();

        switch (opcion) {
            case 11:
                printf("Ingresar Nota - Examen 1\n");
                ingresar_Notas(1);
                break;

            case 12:
                printf("Ingresar Nota - Examen 2\n");
                ingresar_Notas(2);
                break;

            case 13:
                printf("Ingresar Nota - Promedio Tests\n");
                ingresar_Notas(3);
                break;

            case 2:
                printf("Promedio de X alumno\n");
                promedioAlumno = obtenerPromedioAlumno(1);

                //? Dependiendo de la respuesta que recibamos, imprimimos mensajes.
                if (promedioAlumno != 0) {
                    printf("El alumno %d tiene un promedio de %.2f\n\nPresione Enter para continuar ...", alumnoSeleccionado, promedioAlumno);
                    getchar(); getchar();
                }

                break;

            case 3:
                printf("Promedio general del curso\n");
                obtenerPromedioCurso();
                break;

            case 4:
                printf("Muchas gracias por usar el programa!!\n\nPresione Enter para salir ... ");
                getchar(); getchar();
                break;
        }

    }while(opcion != 4);

    return 0;
}

//* .: Desarrollo de funciones :. *//
int menu() {
    int opcion;

    //? Menu pricipal.
    do{
        system("cls");
        printf("\t.: MENU :.\n\n");
        printf("1. Ingresar notas.\n");
        printf("2. Promedio de notas de X alumno.\n");
        printf("3. Promedio general del curso.\n");
        printf("4. Salir.\n");
        printf("\n-> ");

        scanf("%d", &opcion);
    }while(opcion < 1 || opcion > 4);

    //? Tipo de nota a ingresar.
    if (opcion == 1) {
        do {
            system("cls");
            printf("\t.: Ingresar Notas :.\n\n");
            printf("1. Examen 1.\n");
            printf("2. Examen 2.\n");
            printf("3. Promedio tests.\n");
            printf("\n-> ");

            scanf("%d", &opcion);
        }while(opcion < 1 || opcion > 3);

        if(opcion == 1){opcion = 11;}
        if(opcion == 2){opcion = 12;}
        if(opcion == 3){opcion = 13;}
    }

    system("cls");

    return opcion;
}

void ingresar_Notas(int modo) {

    int i;
    float nota;

    //? Entramos al ciclo para ingresar las notas.
    for(i = 0; i < 10; i++) {

        do {
            system("cls");
            if(modo == 1){printf("Ingresar Nota - Examen 1\n\n");}
            if(modo == 2){printf("Ingresar Nota - Examen 2\n\n");}
            if(modo == 3){printf("Ingresar Nota - Promedio Tests\n\n");}

            printf("Ingrese nota del alumno %d: ", i+1);
            scanf("%f", &nota);
        }while(nota < 1 || nota > 7);
        
        //? Preguntamos a cual alumno le ingresamos la nota y a qué atributo.
        if(modo == 1) { // Nota examen 1.
            curso[i].nota_examen1 = nota;
            notasIngresadas_Examen1 ++;
        }
        if(modo == 2) { // Nota examen 2.
            curso[i].nota_examen2 = nota;
            notasIngresadas_Examen2 ++;
        }
        if(modo == 3) { // Nota promedio tests.
            curso[i].promedio_tests = nota;
            notasIngresadas_Tests ++;
        }
    }
}

float obtenerPromedioAlumno(int modo) {

    //! CALCULO DEL PROMEDIO SE HARÁ SUMANDO NOTAS Y DIVIDIENDO EN 3. AJUSTAR A LA PONDERACIÓN EN EL FUTURO ..

    int i;
    float promedioAlumno = 0, promedioAuxiliar;

    if (modo == 1) {
        do {
            system("cls");

            printf("Promedio de X alumno\nIngrese ID de alumno\n\n-> ");
            scanf("%d", &alumnoSeleccionado);

        }while(alumnoSeleccionado < 1 || alumnoSeleccionado > 10);
    }

    //? Pregunto si todas las notas fueron ingresadas, para saber si puedo calcular el promedio.
    if(notasIngresadas_Examen1 >= 10 && notasIngresadas_Examen2 >= 10 && notasIngresadas_Tests >= 10) {
        
        if (modo == 1) {
            promedioAlumno = curso[alumnoSeleccionado-1].nota_examen1 + curso[alumnoSeleccionado-1].nota_examen2 + curso[alumnoSeleccionado-1].promedio_tests;
            promedioAlumno = promedioAlumno / 3;
        }
        else {
            for(i = 0; i < 10; i++) {
                promedioAuxiliar = curso[i].nota_examen1 + curso[i].nota_examen2 + curso[i].promedio_tests;
                promedioAuxiliar = promedioAuxiliar / 3;

                promedioAlumno = promedioAlumno + promedioAuxiliar;
            }
            promedioAlumno = promedioAlumno / 10;
        }

        return promedioAlumno;
    }
    else {
        printf("\nNo se puede calcular el promedio\n[Faltan notas]\nPresione Enter para continuar ... ");
        getchar(); getchar();
        return 0;
    }
}

void obtenerPromedioCurso() {
    
    //! CALCULO DEL PROMEDIO SE HARÁ SUMANDO NOTAS Y DIVIDIENDO EN 3. AJUSTAR A LA PONDERACIÓN EN EL FUTURO ..

    float promedioCurso = obtenerPromedioAlumno(2);

    if(promedioCurso != 0) {
        printf("El promedio del curso es %.2f\n\nPresione Enter para continuar ...", promedioCurso);
        getchar(); getchar();
    }
}