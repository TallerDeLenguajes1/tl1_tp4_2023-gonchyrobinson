#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

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

int main(){
    Lista pendientes;
    Lista realizadas;
    Lista pendientesNueva=CrearListaVacia();
    Lista aux;
    int tareas;
    pendientes=CrearListaVacia();
    realizadas=CrearListaVacia();
    printf("Ingrese cuantas tareas cargara:  ");

    scanf("%d",&tareas);
    for(int i=0; i<tareas;i++){
        aux=CrearNodo(i);
        InsertarNodo(&pendientes,aux);

    }
    MuestraLista(pendientes);
    RealizoTarea(&pendientes, &realizadas,&pendientesNueva);
    printf("\n;;;;;;;;;;;;;;;;;;;;TAREAS REALIZADAS;;;;;;;;;;;;;;;;;;;\n");
    MuestraLista(realizadas);
    printf("\n++++++++++++++++++++++TAREAS PENDIENTES +++++++++++++++++++++++\n");
    MuestraLista(pendientesNueva);
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
/*void RealizoTarea(Lista* pendientes, Lista* realizadas){
    Lista aux=NULL;
    Lista primerElementoPendientes=NULL;
    Lista primero=NULL;
    Lista anterior=NULL;
    Lista aux2= NULL;
    int realizado;
    int bandera =0;
    while (!EsListaVacia((*pendientes)))
    {
        printf("\n********************************************\n"); 
        MuestraEstructura((*pendientes)->dato);
        printf("\nRealizo la tarea: \n1- Si\n0-No\n");
        scanf("%d", &realizado);
        fflush(stdin);
        if(realizado == 1){
            aux=*pendientes;
            (*pendientes)=(*pendientes)->siguiente; 
            if (!EsListaVacia(*realizadas))
            {
                aux2=*realizadas;
                *realizadas=aux;
                (*realizadas)->siguiente=aux2;
            }else
            {
                *realizadas=aux;
                (*realizadas)->siguiente=NULL;
            }
                
        }else
        {
            if (anterior==NULL)
            {
                primero=(*pendientes);
                anterior=(*pendientes);
            }else{
                anterior->siguiente=(*pendientes);
                anterior=(*pendientes);
            }
            
             (*pendientes)=(*pendientes)->siguiente;  
             printf("Se eligio la opcion 0: %s", (*pendientes)->dato.Descripcion);         
        }
}
(*pendientes)=primero;
}
*/

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
