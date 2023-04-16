#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

struct Tarea{
    int TareaId;   //Numerado en ciclo iterativo
    char *Descripcion;
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
void InsertarNodo(Lista* cabecera, int i);
void MuestraLista(Lista lista);
void MuestraEstructura(Tarea estruct);
bool EsListaVacia(Lista lista);
void RealizoTarea(Lista* pendientes, Lista* realizadas);
void CambiaTareas(Lista* pendientes, Lista* realizadas, Lista anterior);
void CambiarTareaPendientes(Lista* pendientes);
bool EsPrimerElemento(Lista lista);

int main(){
    Lista pendientes;
    Lista realizadas;
    int tareas;
    pendientes=CrearListaVacia();
    realizadas=CrearListaVacia();
    printf("Ingrese cuantas tareas cargara:  ");
    scanf("%d",&tareas);
    for(int i=0; i<tareas;i++){
        InsertarNodo(&pendientes,i);
    }
    MuestraLista(pendientes);
    RealizoTarea(&pendientes, &realizadas);
    printf("\n;;;;;;;;;;;;;;;;;;;;TAREAS REALIZADAS;;;;;;;;;;;;;;;;;;;\n");
    MuestraLista(realizadas);
    printf("\n++++++++++++++++++++++TAREAS PENDIENTES +++++++++++++++++++++++\n");
    MuestraLista(pendientes);
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
void InsertarNodo(Lista* cabecera, int i){
    Lista aux=CrearNodo(i);
    if(*cabecera!=NULL){
        aux->siguiente=*cabecera;
    }
    (*cabecera)=aux;
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
        lista=lista->siguiente;
        printf("\n____________________________________________\n");
    }
}
bool EsListaVacia(Lista lista){
    if(lista==NULL){
        return(true);
    }else{
        return(false);
    }
}
void RealizoTarea(Lista* pendientes, Lista* realizadas){
    Lista aux=NULL;
    Lista aux2=NULL;
    Lista anterior=NULL;
    int realizado;
    int bandera =0;
    while (!EsListaVacia((*pendientes)))
    {
        printf("\n********************************************\n"); 
        MuestraEstructura((*pendientes)->dato);
        printf("\nRealizo la tarea: \n1- Si\n0-No\n");
        scanf("%d", &realizado);
        
        if(EsPrimerElemento(*realizadas)){
            aux2= *realizadas;
        }
        if(anterior!=NULL && bandera==0){
            aux= anterior;
            bandera=1;
        }
        if(realizado==1){
            CambiaTareas(pendientes, realizadas, anterior);
            anterior=(*pendientes);
        }
        *pendientes=(*pendientes)->siguiente;
    }
    pendientes=&aux;
    realizadas=&aux2;
    free(aux);
    free(aux2);  
    free(anterior);  
}

void CambiaTareas(Lista *pendientes, Lista *realizadas, Lista anterior){
    Lista anteriorRealizada=*realizadas;
    (*pendientes)=(*pendientes)->siguiente;
    if(EsListaVacia(*realizadas)){
        (*realizadas)=(*pendientes);
        (*realizadas)->siguiente=NULL;
    }else{
        (*realizadas)=(*pendientes);
       (*realizadas)->siguiente=anteriorRealizada;
    }
    if(anterior!=NULL){
        anterior->siguiente=(*pendientes);
    }
    free(anteriorRealizada);
}

bool EsPrimerElemento(Lista lista){
    if(!EsListaVacia(lista) && EsListaVacia(lista->siguiente)){
        printf("\n\nRETORNO: ");
        MuestraEstructura(lista->dato);
        printf("\nTRUE");
        return(true);
    }else{
        printf("\n\nRETORNO: ");
        MuestraEstructura(lista->dato);
        printf("\nFALSE");
        return(false);
    }
}