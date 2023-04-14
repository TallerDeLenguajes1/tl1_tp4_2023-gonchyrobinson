#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

struct Tarea{
    int TareaId;   //Numerado en ciclo iterativo
    char *Descripcion;
    int Duracion; // entre 10 – 100

} typedef Tarea;
void InicializaNulo(Tarea**punt, int cant);
void CargaPuntero(Tarea** punt, int cant);
Tarea CargaTarea(int i);
void MuestraEstructura(Tarea estruct);
void MuestraPunteroDoble(Tarea**  p, int cant);
void RealizaTarea(Tarea**pendientes, Tarea**realizadas,int cant);
Tarea BuscarTarea(Tarea** punt, Tarea** punt2, int cant, int id);
Tarea BuscarTareaPorPalabra(Tarea **punt, Tarea** punt2, int cant, char* palabra);
void Menu(Tarea**pendientes, Tarea**realizadas, int cant);

int main(){
    int cantTareas;
    printf("Ingrese cuantas tareas desea cargar:  ");
    scanf("%d", &cantTareas );
    Tarea** tareasPendientes=(Tarea**)malloc(sizeof(Tarea*)*cantTareas);
    Tarea** tareasRealizadas=(Tarea**)malloc(sizeof(Tarea*)*cantTareas);
    InicializaNulo(tareasPendientes,cantTareas);
    InicializaNulo(tareasRealizadas,cantTareas);
    CargaPuntero(tareasPendientes, cantTareas);
    RealizaTarea(tareasPendientes, tareasRealizadas, cantTareas);
    printf("\n\n::::::::::::::::::TAREAS REALIZADAS::::::::::::::::::\n");
    MuestraPunteroDoble(tareasRealizadas, cantTareas);
    printf("\n\n::::::::::::::::::TAREAS PENDIENTES::::::::::::::::::\n");
    MuestraPunteroDoble(tareasPendientes, cantTareas);
    printf("\n____________________________________________________\n");
    Menu(tareasPendientes, tareasRealizadas, cantTareas);
}


void InicializaNulo(Tarea**punt, int cant){
    for (int i = 0; i < cant; i++)
    {
        punt[i]=NULL;
    }
    
}
void CargaPuntero(Tarea** punt, int cant){
    for (int i = 0; i < cant; i++)
    {
        printf("\n=============CARGA TAREA %d ===========",i);
        punt[i]=(Tarea*)(malloc(sizeof(Tarea)));
        *punt[i]=CargaTarea(i);
    }
    
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
void MuestraEstructura(Tarea estruct){
    printf("\n.ID:  %d", estruct.TareaId);
    printf("\n.Descripcion:  %s",estruct.Descripcion);
    printf("\n.DUracion:  %d", estruct.Duracion);
}
void MuestraPunteroDoble(Tarea**  p, int cant){
    for (int i = 0; i <cant; i++)
    {
        if(p[i]!=NULL){
            printf("\n*******************MUESTRA ESTRUCTURA %d ***********************",i);
            MuestraEstructura(*p[i]);
        }
    }
    
}
void RealizaTarea(Tarea**pendientes, Tarea**realizadas,int cant){
    int realiza;
    for (int i = 0; i < cant; i++){
        printf("\n---------------ESTRUCTURA %d ------------------",i);
        MuestraEstructura(*pendientes[i]);
        printf("\n-Presione 1 si realizo la tarea, 0 si no lo hizo:  ");
        scanf("%d", &realiza);
        if(realiza){
            realizadas[i]=pendientes[i];
            pendientes[i]=NULL;
        }
    }
    
}
Tarea BuscarTarea(Tarea** punt, Tarea** punt2, int cant, int id){
    int bandera=0;
    for (int i = 0; i < cant; i++)
    {
        if(punt[i]!=NULL){
            if(punt[i]->TareaId==id){
                return(*(punt[i]));
                bandera=1;
            }
        }
        if(punt2[i]!=NULL){
            if(punt2[i]->TareaId==id){
                return(*(punt2[i]));
                bandera=1;
            }
        }
    }
}
Tarea BuscarTareaPorPalabra(Tarea **punt, Tarea** punt2, int cant, char* palabra){
    int bandera=0;
    for (int i = 0; i < cant; i++)
    {
        if(punt[i]!=NULL && bandera==0){
            if (strstr(punt[i]->Descripcion, palabra)!=NULL)
            {
                return(*punt[i]);
                bandera=1;
            }
            
        }
        if(punt2[i]!=NULL && bandera==0){
            if (strstr(punt2[i]->Descripcion, palabra)!=NULL)
            {
               return(*punt2[i]);
               bandera=1;
            }
            
        }
    }
    
}
void Menu(Tarea**pendientes, Tarea**realizadas, int cant){
    int menu=1;
    int id;
    char* palabra=(char*)malloc(sizeof(char)*100);
    printf("{{{{{{{{{{MENU}}}}}}}}}}");
    while (menu!=0){
        printf("\n1- Buscar por id\n2- Buscar por palabra clave\n0-Salir  ");
        scanf("%d", &menu);
        switch (menu)
        {
        case 1:
            printf("\n id que desea buscar:  ");
            scanf("%d", &id);
            BuscarTarea(pendientes, realizadas, cant,id);
            printf("Ingrese el id de la tarea que busca:  \n");
            MuestraEstructura(BuscarTarea(pendientes,realizadas,cant,id));
            break;
        case 2:
            printf("\n palabra clave que busca: ");
            fflush(stdin);
            gets(palabra);
            MuestraEstructura(BuscarTareaPorPalabra(pendientes,realizadas,cant,palabra));
        default:
            break;
        }
    }
    
}