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
void RealizoTarea(Lista* pendientes, Lista* realizadas, Lista* pendientesNueva, Lista* enProcesp);
void CambiaTareas(Lista* pendientes, Lista* realizadas, Lista anterior);
void CambiarTareaPendientes(Lista* pendientes);
bool EsPrimerElemento(Lista lista);
void LiberaMemoria(Lista realizadas, Lista pendientes);
Lista DesenlazarNodoDeLaLista(Lista* cabecera);
void menu(Lista* pendientes, Lista* realizadas, Lista* pendientesNueva, Lista* enProceso);
Tarea BuscarTareaPorId(Lista pendientes, Lista realizadas, Lista pendientesNueva);
Tarea BuscarTareaPorPalabraClave(Lista pendientes, Lista realizadas, Lista pendientesNueva);
void EliminarTarea(Lista* tarea);
void MostrarDatos(Lista tarea);
void MoverDatos(Lista*pendientes,Lista*realizadas, Lista*EnProceso);
Lista SeleccionaNodo(Lista lista, int id);
void MoverTarea(Lista*pendientes, Lista*realizadas, Lista*enProceso, Lista nodoSacado);
Lista DescenlazarNodoId(Lista* lista,int id);
bool PerteneceTareaALaLista(Lista lista, int id);

int main(){
    Lista pendientes=CrearListaVacia();
    Lista realizadas=CrearListaVacia();
    Lista pendientesNueva=CrearListaVacia();
    Lista tareasEnProceso=CrearListaVacia();
    Lista aux;
    menu(&pendientes,&realizadas,&pendientesNueva,&tareasEnProceso);
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
    nodo->siguiente=*cabecera;
    *cabecera=nodo;
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

void RealizoTarea(Lista* pendientes, Lista* realizadas, Lista* pendientesNueva, Lista* enProceso){
    int realizado;
    Lista nodo;
    Lista anterior=NULL;
    while (!EsListaVacia(*pendientes))
    {
        printf("\n********************************************\n"); 
        MuestraEstructura((*pendientes)->dato);
        printf("\nRealizo la tarea: \n1- Si\n0-No\n2-En proceso\n");
        scanf("%d", &realizado);
        nodo=DesenlazarNodoDeLaLista(pendientes);
        switch (realizado)
        {
        case 0:
            InsertarNodo(pendientesNueva,nodo);
            break;
        case 1:
            InsertarNodo(realizadas,nodo);
            break;
        case 2:
            InsertarNodo(enProceso,nodo);
        break;
        default:
            break;
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

void menu(Lista* pendientes, Lista*realizadas, Lista*pendientesNueva, Lista* enProceso){
    int opcion;
    int bandera=0;
    int tareaEliminar;
    Tarea tareaAuxiliar;
    printf("\n::::::::::::::::::::::MENU:::::::::::::::::::::::::\n");
    while (bandera==0)
    {
        printf("\n-----------------------------------------------------------\n");
        printf("Ingrese una opcion:  \n0-salir\n1-Cargar Tareas\n2-Marcar tareas realizadas\n3- Mostrar Tareas Realizadas\n4-Buscar tareas por id\n5-Buscar tareas por palabra clave\n6-Eliminar Tara\n7-MOstrar datos de la lista\n8-MOver Datos");
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
            RealizoTarea(pendientes,realizadas,pendientesNueva,enProceso);
        default:
        case 3:
            printf("\n;;;;;;;;;;;;;;;;;;;;TAREAS REALIZADAS;;;;;;;;;;;;;;;;;;;\n");
            MuestraLista(*realizadas);
            printf("\n++++++++++++++++++++++TAREAS PENDIENTES +++++++++++++++++++++++\n");
            MuestraLista(*pendientesNueva);
            printf("\n++++++++++++++++++++++TAREAS EN PROCESO +++++++++++++++++++++++\n");
            MuestraLista(*enProceso);
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
        case 6:
            printf("\n.........................ELIMINA TAREA...................\n");
            printf("\n-Ingrese de que lista desea eliminar una tarea:  \n1- tareas Pendientes\n2- tareas Realizadas\n3- tareas en proceso");
            scanf("%d", &tareaEliminar);
            switch (tareaEliminar)
            {
            case 1:
                EliminarTarea(pendientesNueva);
                break;
            case 2:
                EliminarTarea(realizadas);
                break;
            case 3:
                EliminarTarea(enProceso);
            break;
            }
            
        
        break;
        case 7:
            printf("\n.........................Mostrar Datos...................\n");
            printf("\n-Ingrese de que lista desea ver los datos:  \n1- tareas Pendientes\n2- tareas Realizadas\n3-En proceso");
            scanf("%d", &tareaEliminar);
            switch (tareaEliminar)
            {
            case 1:
                MostrarDatos(*pendientesNueva);
                break;
            case 2:
                MostrarDatos(*realizadas);
            case 3:
                MostrarDatos(*enProceso);
            break;
            default:
                break;
            }
        break;
        case 8:
            printf("\n|||||||||||||||||||||||MOVER DATOS|||||||||||||||||||||||||||||||\n");
            MoverDatos(pendientesNueva,realizadas,enProceso);

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
void EliminarTarea(Lista* tarea){
    if(!EsListaVacia(*tarea)){
        Lista aux;
        aux=(*tarea);
        (*tarea)=(*tarea)->siguiente;
        free(aux);
    }else
    {
        printf("\n La lista esta vacia, por lo tanto, no hay elementos para eliminar");
    }
    
}
void MostrarDatos(Lista tarea){
    int cant=0;
    int tiempo=0;
    while (!EsListaVacia(tarea))
    {
        cant+=1;  
        tiempo+=tarea->dato.Duracion;
        tarea=tarea->siguiente;
    }
    printf("\n{{{{{{{{{{{{{{{{{{{MUESTRA CANTIDAD DE TAREAS Y DURACION}}}}}}}}}}}}}}}}}}}");
    printf("\nCantidad de tareas:  %d", cant);
    printf("\n-Duracion total:  %d",tiempo);

}
void MoverDatos(Lista*pendientes,Lista*realizadas, Lista*EnProceso){
            printf("\n;;;;;;;;;;;;;;;;;;;;TAREAS REALIZADAS;;;;;;;;;;;;;;;;;;;\n");
            MuestraLista(*realizadas);
            printf("\n++++++++++++++++++++++TAREAS PENDIENTES +++++++++++++++++++++++\n");
            MuestraLista(*pendientes);
            printf("\n++++++++++++++++++++++TAREAS EN PROCESO +++++++++++++++++++++++\n");
            MuestraLista(*EnProceso);
            printf("\nIngrese el id de la tarea que necesita modificar:   ");
            int id;
            int lista;
            scanf("%d", &id);
           Lista nodoSacado=CrearListaVacia();//recibe a donde apunta el nodo seleccionado
           Lista nodoSeparado=CrearListaVacia();
            if(PerteneceTareaALaLista(*pendientes,id)){
                nodoSeparado=DescenlazarNodoId(pendientes,id);
                lista=1;
            }else
            {
                if (PerteneceTareaALaLista(*realizadas,id))
                {
                    nodoSeparado=DescenlazarNodoId(realizadas,id);
                    lista=2;
                }else
                {
                    if (PerteneceTareaALaLista(*EnProceso,id))
                    {
                        nodoSeparado=DescenlazarNodoId(EnProceso,id);
                        lista=3;
                    }else
                    {
                        nodoSeparado=NULL;
                        printf("\nEl id seleccionado no existe");
                    }
                    
                    
                }
                
                
            }
            int tarea;
            if (nodoSeparado)
            {
                printf("\n Ingrese que desea hacer con la tarea seleccionada:   \n1-Mover\n2-Eliminar la tarea\n3-No hacer nada  ");
                scanf("%d", &tarea);
                switch (tarea)
                {
                case 1:
                    MoverTarea(pendientes,realizadas,EnProceso,nodoSeparado);
                    break;
                case 2:
                    free(nodoSeparado);
                    break;
                case 3:
                    switch (lista)
                    {
                    case 1:
                        InsertarNodo(pendientes,nodoSeparado);
                        break;
                    case 2:
                        InsertarNodo(realizadas,nodoSeparado);
                    case 3:
                        InsertarNodo(EnProceso,nodoSeparado);
                    default:
                        break;
                    }
                break;
                }
                }else
                {
                    printf("\nERROR al seleccionar tarea");
                }
                
            
}
Lista SeleccionaNodo(Lista lista, int id){
    Lista seleccionado=CrearListaVacia();
    if (!EsListaVacia(lista))
    {
        while (!EsListaVacia(lista) && (lista)->dato.TareaId!=id)
        {
            lista=(lista)->siguiente;
        }
        if(!EsListaVacia(lista)){
            seleccionado=lista;
        }
    }
    return(seleccionado);
    
}

void MoverTarea(Lista*pendientes, Lista*realizadas, Lista*enProceso, Lista nodoSacado){
            int lista;
            printf("\nIngrese a que lista desea insertar la tarea:  \n1-pendientes\n2-realizados\n3-en Proceso");
            scanf("%d", &lista);
            switch (lista)
            {
            case 1:
                InsertarNodo(pendientes,nodoSacado);
                break;
            case 2:
                InsertarNodo(realizadas,nodoSacado);
                break;
            case 3:
                InsertarNodo(enProceso,nodoSacado);
                break;
            default:
                break;
            }
}

Lista DescenlazarNodoId(Lista* lista,int id){
    Lista actual=*lista;
    Lista anterior=*lista;
    Lista seleccionado=NULL;
    if (!EsListaVacia(*lista)){
        if((*lista)->dato.TareaId==id)
        {
            seleccionado=*lista;
            *lista=(*lista)->siguiente;
        }else
        {     
            while (!EsListaVacia(actual) && (actual)->dato.TareaId!=id)
            {   
                anterior=*lista;
                actual=actual->siguiente;
            }
            if(!EsListaVacia(actual)){
                anterior->siguiente=actual->siguiente;
                seleccionado=actual;
            }
        }
    }
    
    return(seleccionado);
    
}
bool PerteneceTareaALaLista(Lista lista, int id){
    bool pertenece=false;
    while (!EsListaVacia(lista) && lista->dato.TareaId!=id)
    {
        lista=lista->siguiente;
    }
    if(!EsListaVacia(lista)){
        pertenece=true;
    }
    return(pertenece);
    
}