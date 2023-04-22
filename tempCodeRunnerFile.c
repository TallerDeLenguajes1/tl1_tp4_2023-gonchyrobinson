
    int bandera =0;
    while (!EsListaVacia((*pendientes)))
    {
        printf("\n********************************************\n"); 
        MuestraEstructura((*pendientes)->dato);
        printf("\nRealizo la tarea: \n1- Si\n0-No\n");
        scanf("%d", &realizado);
        printf("%d", realizado);
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
        }
}
(*pendientes)=primero;
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