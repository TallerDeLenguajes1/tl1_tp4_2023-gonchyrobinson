#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

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
void LiberaMemoria(Tarea **punt, int cant);

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
void LiberaMemoria(Tarea **punt, int cant){
    for(int i = 0; i<cant; i++){
        free(punt[i]);
    }
    free(punt);
}