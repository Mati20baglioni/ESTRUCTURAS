#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    int matricula;
    char nombre[30];
    char genero; // m, f, o
} stAlumno;

/// PROTOTIPADOS:
///1
int CargarAlumnos(stAlumno alumnos[], int dimension);
///2
void MostrarNombresCargados(stAlumno alumnos[], int validos);
///3
void MostrarDatosAlumno(stAlumno alumnos[],int validos,int NumeroM);
///4
int BuscarMenorMatricula(stAlumno alumnos[],int inicio ,int validos);
void OrdenarPorSeleccion(stAlumno alumnos[], int validos);
///5
void MostrarDatosAlumnoPorSexo(stAlumno alumnos[], int validos, char sexo);
///6

///7

///8
int ContarPorGenero(stAlumno alumnos[],int validos,char sexo);
///////////////////////////////////////////////////////////////////////////////
int main() {
    stAlumno NombreAlumno[30];
    int op,Numero_Matricula,contador,menor= 0;
    char control = 's';
    char Sexo;
    int validos = 0;
    printf("TRABAJO PRACTICO DE ESTRUCTURAS\n");
    do {
        printf("Ingresa una funcion:\n");
        printf("1. Cargar Alumnos.\n");
        printf("2. Mostrar Nombres Cargados.\n");
        printf("3. Encontrar y Mostrar Alumno por Matricula.\n");
        printf("4. Encontrar Menor Matricula,Ordenamiento por Seleccion.\n");
        printf("5. Encontrar y Mostrar Alumno por Sexo.\n");
        printf("6. Insertar en un arreglo ordenado por matricula un nuevo dato, conservando el orden\n");
        printf("7. Ordenar el arreglo de alumnos por nombre usando el metodo de insercion\n");
        printf("8. Cuantos alumnos de determinado genero.\n");

        scanf("%i", &op);
        switch (op) {
            case 1:
                validos = CargarAlumnos(NombreAlumno, 30);
                break;
            case 2:
                MostrarNombresCargados(NombreAlumno, validos);
                break;
            case 3:
                printf("ingrese el numero de matricula del alumno: \n");
                scanf("%i",&Numero_Matricula);
                MostrarDatosAlumno(NombreAlumno,validos,Numero_Matricula);
                break;
            case 4:
                /*menor=BuscarMenorMatricula(NombreAlumno,0,validos);
                printf("El Menor Indice es: %i con Matricula %i\n", menor, NombreAlumno[menor].matricula);*/
                OrdenarPorSeleccion(NombreAlumno, validos);
                printf("Alumnos ordenados por matricula.\n");
                MostrarNombresCargados(NombreAlumno, validos);
                break;
            case 5:
                printf("ingresa el genero a buscar: \n");
                fflush(stdin);
                scanf("%c",&Sexo);
                printf("\n\n");
                MostrarDatosAlumnoPorSexo(NombreAlumno,validos,Sexo);
                break;
            case 6:
                validos = InsertarMatricula(NombreAlumno, validos, 30);
                printf("Alumno insertado y arreglo ordenado.\n");
                MostrarNombresCargados(NombreAlumno, validos);
                break;
            case 7:
                OrdenarPorInsercionNombre(NombreAlumno, validos);
                printf("Alumnos ordenados por nombre.\n");
                MostrarNombresCargados(NombreAlumno, validos);
                break;
            case 8:
                printf("ingrese el genero a buscar: \n");
                fflush(stdin);
                scanf("%c",&Sexo);
                contador=ContarPorGenero(NombreAlumno,validos,Sexo);
                printf("el numero de alumnos %c es de:%i\n",Sexo,contador);
                break;
            default:
                printf("Opción no válida\n");
                break;
        }
        printf("Continuar (s/n)?:\n");
        fflush(stdin);
        scanf(" %c", &control);
    } while (control == 's');

    return 0;
}

///1. Hacer una función que cargue un arreglo de alumnos, hasta que el usuario lo decida.
int CargarAlumnos(stAlumno alumnos[], int dimension)
 {
    int validos = 0;
    char control = 's';

    do {
        if (validos < dimension)
            {
                printf("Ingrese la matricula del alumno: \n");
                scanf("%i", &alumnos[validos].matricula);
                printf("Ingrese un nombre:\n");
                fflush(stdin);
                scanf("%s", alumnos[validos].nombre);
                printf("Ingrese el genero (m/f): \n");
                fflush(stdin);
                scanf(" %c", &alumnos[validos].genero);
                validos++;
            if (validos < dimension)
                {
                    printf("Continuar ingresando alumnos (s/n)?: ");
                    fflush(stdin);
                    scanf(" %c", &control);
                } else
                    {
                        printf("Has alcanzado el limite de alumnos.\n");
                    }
            } else {
            control = 'n';
        }
    } while (control == 's' && validos < dimension);

    return validos;
}
///2. Hacer una función que muestre un arreglo de alumnos por pantalla. Modularizar.
void MostrarNombresCargados(stAlumno alumnos[], int validos)
 {
    for (int i = 0; i < validos; i++)
    {
        printf("Matricula: %d\n",alumnos[i].matricula);
        printf("Nombre: %s\n",alumnos[i].nombre);
        printf("Genero: %c\n",alumnos[i].genero);
        printf("\n");
    }
    printf("\n");
}
///3 Hacer una función que muestre por pantalla los datos de un alumno, conociendo su matrícula. Modularizar.
void MostrarDatosAlumno(stAlumno alumnos[], int validos, int matricula)
 {
    int encontrado = 0;
    for (int i = 0; i < validos; i++)
    {
        if (alumnos[i].matricula == matricula)
         {
            printf("Matricula: %d\n", alumnos[i].matricula);
            printf("Nombre: %s\n", alumnos[i].nombre);
            printf("Genero: %c\n", alumnos[i].genero);
            encontrado = 1;
            break;
         }
    }
    if (!encontrado)
    {
        printf("Alumno con matricula %d no encontrado.\n", matricula);
    }
    printf("\n");
}
///4 Hacer una función que ordene el arreglo de alumnos por medio del método de selección. El criterio de ordenación es el número de matrícula.
int BuscarMenorMatricula(stAlumno alumnos[], int inicio, int validos)
{
    int Menor = inicio;
    for (int i = inicio + 1; i < validos; i++)
    {
        if (alumnos[i].matricula < alumnos[Menor].matricula)
        {
            Menor = i;
        }
    }
    return Menor;
}
void OrdenarPorSeleccion(stAlumno alumnos[], int validos)
{
    for (int i = 0; i < validos - 1; i++)
    {
        int menorIndice = BuscarMenorMatricula(alumnos, i, validos);
        if (menorIndice != i)
        {
            stAlumno temp = alumnos[i];
            alumnos[i] = alumnos[menorIndice];
            alumnos[menorIndice] = temp;
        }
    }
}
///5 Hacer una función que muestre por pantalla los datos de los estudiantes de un género determinado (se envía por parámetro). Modularizar.
void MostrarDatosAlumnoPorSexo(stAlumno alumnos[], int validos, char sexo)
 {
    int encontrado = 0;
    for (int i = 0; i < validos; i++)
    {
        if (alumnos[i].genero == sexo)
        {
            printf("Matricula: %d\n", alumnos[i].matricula);
            printf("Nombre: %s\n", alumnos[i].nombre);
            printf("Genero: %c\n", alumnos[i].genero);
            encontrado = 1;
            printf("\n\n");
        }
    }
            if (!encontrado)
            {
                printf("No se encontraron alumnos con el genero '%c'.\n", sexo);
            }
    printf("\n");
}
///6 Hacer una función que inserte en un arreglo ordenado por matrícula un nuevo dato,conservando el orden.
int InsertarMatricula(stAlumno alumnos[], int validos, int dimension)
 {
    if (validos >= dimension)
    {
        printf("El arreglo está lleno, no se puede insertar más alumnos.\n");
        return validos;
    }

    stAlumno nuevoAlumno;
    printf("Ingrese la matricula del nuevo alumno: \n");
    scanf("%i", &nuevoAlumno.matricula);
    printf("Ingrese un nombre:\n");
    fflush(stdin);
    scanf("%s", nuevoAlumno.nombre);
    printf("Ingrese el genero (m/f): \n");
    fflush(stdin);
    scanf(" %c", &nuevoAlumno.genero);

    int i = validos - 1;
    while (i >= 0 && alumnos[i].matricula > nuevoAlumno.matricula)
    {
        alumnos[i + 1] = alumnos[i];
        i--;
    }
    alumnos[i + 1] = nuevoAlumno;
    validos++;

    return validos;
}
///7 Hacer una función que ordene el arreglo de alumnos por medio del método de inserción. El criterio de ordenación es el nombre.
void OrdenarPorInsercionNombre(stAlumno alumnos[], int validos)
 {
    for (int i = 1; i < validos; i++)
    {
        stAlumno temp = alumnos[i];
        int j = i - 1;
        while (j >= 0 && strcmp(alumnos[j].nombre, temp.nombre) > 0)
        {
            alumnos[j + 1] = alumnos[j];
            j--;
        }
        alumnos[j + 1] = temp;
    }
}
///8 Hacer una función que cuente y retorne la cantidad de estudiantes de un género determinado(se envía por parámetro) que tiene un arreglo de alumnos.
int ContarPorGenero(stAlumno alumnos[],int validos,char sexo)
{
    int contador=0;
    int i=0;
    for(int i=0;i<validos;i++)
    {
        if(alumnos[i].genero==sexo)
        {
            contador++;
        }
        else
        {

        }
    }

    return contador;
}

