#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#define TAMA 100
#define INDEFINIDO -999999
struct Tarea{
    int TareaId;   //Numerado en ciclo iterativo
    char* Descripcion;
    int Duracion; // entre 10 – 100

} typedef Tarea;

struct nodo
{
    Tarea dato;
    struct nodo* siguiente;
};
typedef struct nodo* Lista;

Lista CrearListaVacia();
Lista CrearNodo(int i); // PREGUNTAR SI NO HAY PROBLEMA SI ES QUE NO PASO COMO PARAMETRO LA DESCRIPCION Y LA INICIO ACA
Tarea CargaTarea(int i);
void InsertarNodo(Lista* cabecera, Lista nodo);
void MuestraLista(Lista lista);
void MuestraEstructura(Tarea estruct);
bool EsListaVacia(Lista lista);
void RealizoTarea(Lista* pendientes, Lista* realizadas, Lista* pendientesNueva);
void CambiaTareas(Lista* pendientes, Lista* realizadas, Lista anterior);
void CambiarTareaPendientes(Lista* pendientes);
bool EsPrimerElemento(Lista lista);
void LiberaMemoria(Lista realizadas, Lista pendientes);
Lista DesenlazarNodoDeLaLista(Lista* cabecera);
void menu(Lista* pendientes, Lista* realizadas, Lista* pendientesNueva);
Tarea BuscarTareaPorId(Lista pendientes, Lista realizadas, Lista pendientesNueva);
Tarea BuscarTareaPorPalabraClave(Lista pendientes, Lista realizadas, Lista pendientesNueva);

int main(){
    Lista pendientes=CrearListaVacia();
    Lista realizadas=CrearListaVacia();
    Lista pendientesNueva=CrearListaVacia();
    Lista aux;
    menu(&pendientes,&realizadas,&pendientesNueva);
    LiberaMemoria(realizadas,pendientesNueva);
}

Lista CrearListaVacia(){
    return(NULL);
}
Lista CrearNodo(int i){
    Lista nodo=(Lista)malloc(sizeof(Lista));
    printf("\n===========================CREAR NODO ===============================\n");
    printf("Numero de nodo:  %d",i);
    nodo->dato=CargaTarea(i);
    nodo->siguiente=NULL;
    return(nodo);
}
Tarea CargaTarea(int i){
   Tarea aux;
    aux.TareaId=i;
    aux.Descripcion=(char*)malloc(sizeof(char)*100);
    printf("\nDescripcion:  ");
    fflush(stdin);
    gets(aux.Descripcion);
    aux.Duracion=10+rand()%91;
    return(aux);
}
void InsertarNodo(Lista* cabecera,Lista nodo){
    Lista aux=nodo;
    aux->siguiente=*cabecera;
    *cabecera=aux;
}
void MuestraEstructura(Tarea estruct){
    printf("\n.ID:  %d", estruct.TareaId);
    printf("\n.Descripcion:  %s",estruct.Descripcion);
    printf("\n.DUracion:  %d", estruct.Duracion);
}
void MuestraLista(Lista lista){
    while(lista!=NULL){
        printf("\n____________________________________________");
        MuestraEstructura((lista)->dato);
        printf("\n____________________________________________\n");
        lista=lista->siguiente;
    }
}
bool EsListaVacia(Lista lista){
    if(lista==NULL){
        return(true);
    }else{
        return(false);
    }
}

Lista DesenlazarNodoDeLaLista(Lista* cabecera){
    Lista aux;
    aux=*cabecera;
    (*cabecera)=(*cabecera)->siguiente;
    aux->siguiente=NULL;
    return(aux);
}

void RealizoTarea(Lista* pendientes, Lista* realizadas, Lista* pendientesNueva){
    int realizado;
    Lista nodo;
    Lista anterior=NULL;
    while (!EsListaVacia(*pendientes))
    {
        printf("\n********************************************\n"); 
        MuestraEstructura((*pendientes)->dato);
        printf("\nRealizo la tarea: \n1- Si\n0-No\n");
        scanf("%d", &realizado);
        nodo=DesenlazarNodoDeLaLista(pendientes);
        if (realizado==1)
        {
            InsertarNodo(realizadas,nodo);
        }else{
            InsertarNodo(pendientesNueva,nodo);      
        }
    } 
}


bool EsPrimerElemento(Lista lista){
    if(!EsListaVacia(lista) && EsListaVacia(lista->siguiente)){
        return(true);
    }else{
        return(false);
    }
}

void LiberaMemoria(Lista realizadas, Lista pendientes){
    Lista aux;
    while (!EsListaVacia(pendientes))
    {
        aux=pendientes;
        free(pendientes->dato.Descripcion);
        pendientes=pendientes->siguiente;
        free(aux); 
    }
    while (!EsListaVacia(realizadas))
    {
        aux=realizadas;
        free(aux->dato.Descripcion);
        realizadas=realizadas->siguiente;
        free(aux);
    }
    
    
}

void menu(Lista* pendientes, Lista*realizadas, Lista*pendientesNueva){
    int opcion;
    int bandera=0;
    Tarea tareaAuxiliar;
    printf("\n::::::::::::::::::::::MENU:::::::::::::::::::::::::\n");
    while (bandera==0)
    {
        printf("\n-----------------------------------------------------------\n");
        printf("Ingrese una opcion:  \n0-salir\n1-Cargar Tareas\n2-Marcar tareas realizadas\n3- Mostrar Tareas Realizadas\n4-Buscar tareas por id\n5-Buscar tareas por palabra clave");
        printf("\nOpcion eleginda:  ");
        scanf("%d", &opcion);
        switch (opcion)
        {
        case 0:
            bandera=1;
            break;
        case 1:
            int tareas;
            Lista aux;
            printf("Ingrese cuantas tareas cargara:  ");

            scanf("%d",&tareas);
            for(int i=0; i<tareas;i++){
                aux=CrearNodo(i);
                InsertarNodo(pendientes,aux);
            }
        break;
        case 2:
            RealizoTarea(pendientes,realizadas,pendientesNueva);
        default:
        case 3:
            printf("\n;;;;;;;;;;;;;;;;;;;;TAREAS REALIZADAS;;;;;;;;;;;;;;;;;;;\n");
            MuestraLista(*realizadas);
            printf("\n++++++++++++++++++++++TAREAS PENDIENTES +++++++++++++++++++++++\n");
            MuestraLista(*pendientesNueva);
        break;
        case 4: 
            tareaAuxiliar=BuscarTareaPorId(*pendientes,*realizadas,*pendientesNueva);
            printf("\n- La tarea buscada es:  ");
            MuestraEstructura(tareaAuxiliar);
        break;
        case 5: 
            tareaAuxiliar=BuscarTareaPorPalabraClave(*pendientes,*realizadas,*pendientesNueva);
            if(tareaAuxiliar.TareaId!=INDEFINIDO){
                printf("\n -La tarea buscada es :  \n");
                MuestraEstructura(tareaAuxiliar);
            }else
            {
                printf("\nNo se encontro la tarea buscada\n");
            }
        break;
            
        }

    }
    
}
Tarea BuscarTareaPorId(Lista pendientes, Lista realizadas, Lista pendientesNueva){
    Tarea tareaBuscada;
    int id;
    int bandera=0;
    printf("\n''''''''''''''''''''''''''''''BUSCAR TAREA POR ID'''''''''''''''''''''''''''''\n");
    printf("Ingrese el numero de id de la tarea buscada:  ");
    scanf("%d",&id);
    while (!EsListaVacia(pendientes) && bandera==0)
    {
        if(pendientes->dato.TareaId==id){
            tareaBuscada=pendientes->dato;
            bandera=1;
        }
        pendientes=pendientes->siguiente;
    }
    while (!EsListaVacia(realizadas) && bandera==0)
    {
        if(realizadas->dato.TareaId==id){
            tareaBuscada=realizadas->dato;
            bandera=1;
        }
        realizadas=realizadas->siguiente;
    }
    while (!EsListaVacia(pendientesNueva) && bandera==0)
    {
        if(pendientesNueva->dato.TareaId==id){
            tareaBuscada=pendientesNueva->dato;
            bandera=1;
        }
        pendientesNueva=pendientesNueva->siguiente;
    }
    if(bandera==0){
        tareaBuscada=CargaTarea(INDEFINIDO);
    }
    return(tareaBuscada);
    
}

Tarea BuscarTareaPorPalabraClave(Lista pendientes, Lista realizadas, Lista pendientesNueva){
    char palabraClave[TAMA];
    int bandera=0;
    Tarea tareaBuscada;
    printf("\n---------------------BUSQUEDA POR PALABRA CLAVE ----------------------------------\n");
    printf("Ingrese la palabra clave:  ");
    fflush(stdin);
    gets(palabraClave);
    while (!EsListaVacia(pendientes) && bandera==0)
    {
        if(strstr(pendientes->dato.Descripcion,palabraClave)!=NULL){
            bandera=1;
            tareaBuscada=pendientes->dato;
        }
        pendientes=pendientes->siguiente;
    }
    while (!EsListaVacia(realizadas) && bandera==0)
    {
        if(strstr(realizadas->dato.Descripcion,palabraClave)!=NULL){
            bandera=1;
            tareaBuscada=realizadas->dato;
        }
        realizadas=realizadas->siguiente;
    }
    while (!EsListaVacia(pendientesNueva) && bandera==0)
    {
        if(strstr(pendientesNueva->dato.Descripcion,palabraClave)!=NULL){
            bandera=1;
            tareaBuscada=pendientesNueva->dato;
        }
        pendientesNueva=pendientesNueva->siguiente;
    }
    if(bandera==0){
        tareaBuscada=CargaTarea(INDEFINIDO);
    }
    return(tareaBuscada);
    
}