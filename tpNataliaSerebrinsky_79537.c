#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct articulos{
    int art_codigo;
    char art_descripcion[40];
    int art_stock;
    int art_compras;
	int art_pcompra;
    int art_ventas;
	int art_pventa;
    struct articulos *sig;
} nodo_articulos;

typedef struct clientes{
    int cli_codigo;
    char cli_nombre[40];
	int cli_ventas;
	int cli_cobranza;
    struct ventas *ven; //pila
	struct cobranza *cob; //cola
	struct cobranza *cobult; //agregado puntero a ultimo de cola
    struct clientes *sig;
} nodo_clientes;

typedef struct ventas{
    int ven_codigo;
	int ven_cantidad;
    struct ventas *sig;
} nodo_ventas;

typedef struct cobranza{
	int cob_importe;
    struct cobranza *sig;
} nodo_cobranza;

typedef struct proveedores{
    int prv_codigo;
    char prv_nombre[40];
	int prv_compras;
	int prv_pagos;
    struct compras *com; //pila
	struct pagos *pag; //cola
	struct pagos *pagult; //agregado puntero a ultimo de cola
    struct proveedores *sig;
} nodo_proveedores;

typedef struct compras{
    int com_codigo;
	int com_cantidad;
    struct compras *sig;
} nodo_compras;

typedef struct pagos{
	int pag_importe;
    struct pagos *sig;
} nodo_pagos;

//void loadFileArts();
//void loadFileCliente();
//void loadFileProveedores();
void menuAdmin(nodo_articulos* art, nodo_clientes*cli, nodo_proveedores**nprov);
void menuUsuarioCliente(nodo_articulos*art,nodo_clientes*cli,nodo_proveedores*prov);
void menuUsuarioProveedor(nodo_articulos*art,nodo_clientes*cli,nodo_proveedores*prov);
void menuPrincipal(nodo_articulos* art, nodo_clientes*cli, nodo_proveedores*nprov);

void GenPass(char *pass);

void crearArticulos(nodo_articulos *pt);
void crearClientes(nodo_clientes *pt);
void crearProveedores(nodo_proveedores *pt);

void mostrarArticulos(nodo_articulos *pt);
void mostrarClientes(nodo_clientes *pt);
void mostrarProveedores(nodo_proveedores *pt);

//escribe en archivo nuevo la lista respectiva
void escribeListaArts(nodo_articulos *pt);
void escribeListaClientes(nodo_clientes *pt, nodo_articulos *art);
void escribeListaProveedores(nodo_proveedores *pt, nodo_articulos *art);
//inserta, elimina y modifica de articulo
nodo_articulos *menuArticulosAdmin(nodo_articulos *pt);
nodo_articulos *insertaArticulo(nodo_articulos *pt);
nodo_articulos *eliminaArticulo(nodo_articulos *pt);
nodo_articulos *modificaArticulo(nodo_articulos *pt);
//inserta, elimina y modifica de cliente
nodo_clientes *menuClientesAdmin(nodo_clientes *cli);
nodo_clientes *insertaCliente(nodo_clientes *pt);
nodo_clientes *eliminaCliente(nodo_clientes *pt);
nodo_clientes *modificaCliente(nodo_clientes *pt);
//inserta, elimina y modifica de proveedores
nodo_proveedores *menuProveedoresAdmin(nodo_proveedores *pv);
nodo_proveedores *insertaProveedor(nodo_proveedores *pt);
nodo_proveedores *eliminaProveedor(nodo_proveedores *pt);
nodo_proveedores *modificaProveedor(nodo_proveedores *pt);
//cliente compra
void usuarioCompra(nodo_clientes *cli, nodo_articulos *nt);
int existeArtYHayCant(int *ven_codigo, int *ven_cantidad, nodo_articulos *nt);
//cliente paga
void usuarioPaga(nodo_clientes *cli);
//proveedor
void proveedorVende(nodo_proveedores *nprov, nodo_articulos *nt);
void proveedorCobra(nodo_proveedores *nprov);
nodo_pagos *obtieneUltPago(nodo_pagos * n);
void muestraComprasProveedores(nodo_proveedores *pr);
//procesa
void procesaVentas(nodo_clientes *cli, nodo_articulos *nt);
void procesaCobranzas(nodo_clientes *cli);
nodo_cobranza *obtieneAnteUltCob(nodo_cobranza * nc);
void procesaCompras(nodo_proveedores *np, nodo_articulos *nt);
void procesaPagos(nodo_proveedores *nprov);
nodo_pagos *obtieneAnteUltPagos(nodo_pagos * nc);
void mostrarComprasAux(nodo_ventas *nv);
void mostrarCompras(nodo_clientes *cli);
//funciones de manejo pila
void apilaVentas(nodo_ventas **pila, nodo_ventas *nv);
nodo_ventas *desapilaVentas(nodo_ventas **pila);
void guardaArchivos(nodo_articulos*art,nodo_clientes*cli,nodo_proveedores*nprov);
nodo_proveedores *buscaProv(nodo_proveedores *prov, int nroProv);
nodo_clientes *buscaCliente(nodo_clientes *cli, int nroCli);

int main()
{
    //Cargo Lista Articulos
    nodo_articulos*art;
    art = (nodo_articulos*)malloc(sizeof(nodo_articulos));
    crearArticulos(art);
    //mostrarArticulos(art);
    //Cargo Lista Clientes
    nodo_clientes*cli;
    cli = (nodo_clientes*)malloc(sizeof(nodo_clientes));
    crearClientes(cli);
    //mostrarClientes(cli);
    //Cargo Lista Proveedores
    nodo_proveedores*nprov;
    nprov = (nodo_proveedores*)malloc(sizeof(nodo_proveedores));
    crearProveedores(nprov);
    //mostrarProveedores(nprov);
    menuPrincipal(art,cli,nprov);
    guardaArchivos(art,cli,nprov);
    printf("Se grabó en archivos con éxito.\n");

    return 0;
}

void menuPrincipal(nodo_articulos* art, nodo_clientes*cli, nodo_proveedores*nprov){
    //system("cls");
    int opcion=0;

    while(opcion!=4)
    {
        printf("Indique la opcion que corresponda:\n");
        printf("1. Si es administrador \n");
        printf("2. Si es Cliente \n");
        printf("3. Si es Proveedor \n");
        printf("4. Si desea salir \n");
        scanf("%d",&opcion);


        switch(opcion)
        {
        case 1:
            menuAdmin(art, cli, &nprov);
            break;
        case 2:
            menuUsuarioCliente(art,cli,nprov);
            break;
        case 3:
            menuUsuarioProveedor(art,cli,nprov);
            break;
        case 4:
            return;
		default:
			printf("Ingresó una opcion no valida\n");
			break;
        }
    }
}


void menuAdmin(nodo_articulos* art, nodo_clientes*cli, nodo_proveedores**nprov)
{
    //system("cls");
    char password[5];
    char passAdmin[5];
    strcpy(password, "");
    GenPass(password);
    int cmp = 0;
    do{
        printf("\n Ingrese la contraseña:");
        scanf("%s", passAdmin);
        cmp = strcmp(password, passAdmin);
    }while((cmp) != 0);

    int opcion=0;
    printf("\n");
    printf(" 1)Articulos\n 2)Clientes\n 3)Proveedores\n 4)Procesar Ventas\n 5)Procesar Cobranzas\n 6)Procesar Compras\n 7)Procesar Pagos\n 8)Mostrar Articulos\n 9)Mostrar Clientes\n 10)Mostrar Proveedores\n 11)Volver\n");
    printf("\n");
    printf("Ingrese opcion:\n");
    scanf("%d",&opcion);

        switch(opcion){
        case 1:
            art = menuArticulosAdmin(art);
            break;
        case 2:
            cli = menuClientesAdmin(cli);
            break;
        case 3:
            printf("\n %p", nprov);
            *nprov = menuProveedoresAdmin(*nprov);
            printf("\n %p", nprov);
            break;
        case 4:
            procesaVentas(cli, art);
            break;
        case 5:
            procesaCobranzas(cli);
            break;
        case 6:
            procesaCompras(*nprov, art);
            break;
        case 7:
            procesaPagos(*nprov);
            break;
        case 8:
            mostrarArticulos(art);
            break;
        case 9:
            mostrarClientes(cli);
            break;
        case 10:
            mostrarProveedores(*nprov);
            break;
        case 11:
            //menuPrincipal(art, cli, *nprov);
            break;
        default:
			printf("Ingresó una opcion no valida\n");
			break;
        }
        system("PAUSE");
}

nodo_proveedores *menuProveedoresAdmin(nodo_proveedores *nprov)
{
    //nprov = insertaProveedor(nprov);
    printf("\n menuprov antes %p", nprov);
    nprov = eliminaProveedor(nprov);
    printf("\n menuprov dsps %p", nprov);
    //nprov = modificaProveedor(nprov);
    return nprov;
}

nodo_clientes *menuClientesAdmin(nodo_clientes *cli)
{
    cli = insertaCliente(cli);
    //cli = eliminaCliente(cli);
    //cli = modificaCliente(cli);
    return cli;
}

nodo_articulos *menuArticulosAdmin(nodo_articulos *art)
{
    //art = insertaArticulo(art);
    //art = eliminaArticulo(art);
    art = modificaArticulo(art);
    return art;
}

nodo_proveedores *buscaProv(nodo_proveedores *prov, int nroProv)
{
    while(prov->sig != NULL)
    {
        if(prov->prv_codigo == nroProv)
        {
            return prov;
        }
        prov = prov->sig;
    }
    return NULL;
}

nodo_clientes *buscaCliente(nodo_clientes *cli, int nroCli)
{
    while(cli->sig != NULL)
    {
        if(cli->cli_codigo == nroCli)
        {
            return cli;
        }
        cli = cli->sig;
    }
    return NULL;
}

void menuUsuarioCliente(nodo_articulos*art,nodo_clientes*cli,nodo_proveedores*prov)
{
    int opcion=0, nroCli;
    printf("\n");
    printf("Ingrese nro de cliente:\n");
    scanf("%d",&nroCli);
    printf("\n");
    cli = buscaCliente(cli, nroCli);
    printf(" 1)Mostrar Articulos\n 2)Comprar\n 3)Pagar\n 4)Ver compras \n");
    printf("\n");
    printf("Ingrese opcion:\n");
    scanf("%d",&opcion);

        switch(opcion){
        case 1:
            //loadFileArts();
            mostrarArticulos(art);
            break;
        case 2:
            usuarioCompra(cli, art);
            break;
        case 3:
            usuarioPaga(cli);
            break;
        case 4:
            mostrarCompras(cli);
            break;
        }
        system("PAUSE");
}

void menuUsuarioProveedor(nodo_articulos*art,nodo_clientes*cli,nodo_proveedores*prov)
{
    int opcion=0, nroProv;
    printf("\n");
    printf("Ingrese nro de proveedor:\n");
    scanf("%d",&nroProv);
    printf("\n");
    printf(" 1)Mostrar Articulos\n 2)Vender\n 3)Cobrar\n 4)Ver ventas\n");
    printf("\n");
    printf("Ingrese opcion:\n");
    scanf("%d",&opcion);
    nodo_proveedores *pv = buscaProv(prov, nroProv);

        switch(opcion){
        case 1:
            //loadFileArts();
            mostrarArticulos(art);
            break;
        case 2:
            proveedorVende(pv, art);
            break;
        case 3:
            proveedorCobra(pv);
            break;
        case 4:
        //Ver Ventas
        //apila y desapila, mismo que en clientes
            break;
        }
        system("PAUSE");
}

void crearArticulos(nodo_articulos *pt)
{
    FILE *l;
    l = fopen("articulos.dat", "r");
    if(l == NULL){
        printf("Archivo inexistente");
        return;
    }
    while(!feof(l)){
        fscanf(l,"%d;%39[^;];%d;%d;%d;%d;%d\n",&pt->art_codigo, pt->art_descripcion, &pt->art_stock, &pt->art_compras, &pt->art_pcompra, &pt->art_ventas, &pt->art_pventa);
        pt->sig=(nodo_articulos*)malloc(sizeof(nodo_articulos));
        pt = pt->sig;
    }
    pt->sig = NULL;
    fclose(l);
}

void mostrarArticulos(nodo_articulos *pt)
{
    while(pt != NULL){
        printf("\n%d;%s;%d;%d;%d;%d;%d\n", pt->art_codigo, pt->art_descripcion, pt->art_stock, pt->art_compras, pt->art_pcompra, pt->art_ventas, pt->art_pventa);
        pt = pt->sig;
    }
}

void crearClientes(nodo_clientes *pt)
{
    FILE *l;
    l = fopen("clientes.dat", "r");
    if(l == NULL){
        printf("Archivo inexistente");
        return;
    }
    while(!feof(l)){
        fscanf(l,"%d;%39[^;];%d;%d\n",&pt->cli_codigo, pt->cli_nombre, &pt->cli_ventas, &pt->cli_cobranza);
        pt->ven = NULL;
        pt->cob = NULL;
        pt->cobult = NULL;
        pt->sig=(nodo_clientes*)malloc(sizeof(nodo_clientes));
        pt = pt->sig;
    }
    fclose(l);
    pt->sig = NULL;
}


void mostrarClientes(nodo_clientes *pt)
{
    while(pt != NULL)
    {
        printf("%d\t%s\t%d\t%d\n", pt->cli_codigo, pt->cli_nombre, pt->cli_ventas, pt->cli_cobranza);
        pt = pt->sig;
    }
}

void mostrarCompras(nodo_clientes *cli)
{
    while(cli != NULL)
    {
        mostrarComprasAux(cli->ven);
        cli = cli->sig;
    }
}

void mostrarComprasAux(nodo_ventas *nv)
{
    nodo_ventas *pilaAux;
    nodo_ventas *elimino, *napila;
    pilaAux = (nodo_ventas*)malloc(sizeof(nodo_ventas));
    //desapila nv y va apilando en pilaAux

    while(nv !=NULL)
    {   //desapilo y voy mostrando lo que hay
        printf("\n%d;%d", nv->ven_codigo, nv->ven_cantidad);
        elimino = nv;
        napila = (nodo_ventas*)malloc(sizeof(nodo_ventas));
        napila = nv;
        nv = nv->sig;
        apilaVentas(&pilaAux, napila);
        free(elimino);
    }
    pilaAux->sig = NULL;
    nv = desapilaVentas(&pilaAux);
}

void apilaVentas(nodo_ventas **pila, nodo_ventas *nv)
{
    nodo_ventas *pilaaux = *pila;
    *pila = nv;
    (*pila)->sig = pilaaux;
}

nodo_ventas *desapilaVentas(nodo_ventas **pila)
{
    nodo_ventas *res, *aux, *viaja;
    viaja = *pila;
    res = NULL;
    while(viaja != NULL)
    {
        aux = res;
        res = viaja;
        res->sig = aux;
        viaja = viaja->sig;
    }
    return res;
}

void crearProveedores(nodo_proveedores *pt)
{
    FILE *l;
    l = fopen("proveedores.dat", "r");
    if(l == NULL){
        printf("Archivo inexistente");
        return;
    }
    while(!feof(l)){
        fscanf(l,"%d;%39[^;];%d;%d\n",&pt->prv_codigo, pt->prv_nombre, &pt->prv_compras, &pt->prv_pagos);
        pt->com = NULL;
        pt->pag = NULL;
        pt->pagult = NULL;
        pt->sig=(nodo_proveedores*)malloc(sizeof(nodo_proveedores));
        pt = pt->sig;
    }
    pt->sig = NULL;
    fclose(l);
}

void mostrarProveedores(nodo_proveedores *pt)
{
    while(pt != NULL){
       printf("%d\t%s\t%d\t%d\n", pt->prv_codigo, pt->prv_nombre, pt->prv_compras, pt->prv_pagos);
       pt = pt->sig;
    }
}

void escribeListaArts(nodo_articulos *pt)
{
    FILE *l;
    l = fopen("escribeArts.dat", "w");
    fprintf(l, "Imprimo los nodos de articulos: \n");
    while(pt->sig != NULL)
    {
        fprintf(l, "%d\t%s\t%d\t%d\t%d\t%d\t%d\n", pt->art_codigo, pt->art_descripcion, pt->art_stock, pt->art_compras, pt->art_pcompra, pt->art_ventas, pt->art_pventa);
        pt = pt->sig;
    }
    fclose(l);
}

void escribeListaClientes(nodo_clientes *pt, nodo_articulos *art)
{
    FILE *l;
    l = fopen("escribeClientes.dat", "w");
    fprintf(l, "Imprimo los nodos de clientes: \n");
    while(pt->sig != NULL)
    {
        if(pt->ven != NULL)
        {
            printf("\n Falta procesar ventas");
            procesaVentas(pt, art);
        }
        if(pt->ven != NULL)
        {
            printf("\n Falta procesar cobranzas");
            procesaCobranzas(pt);
        }

        fprintf(l, "%d\t%s\t%d\t%d\n", pt->cli_codigo, pt->cli_nombre, pt->cli_ventas, pt->cli_cobranza);
        pt = pt->sig;
    }
    fclose(l);
}

void escribeListaProveedores(nodo_proveedores *pt, nodo_articulos *art)
{
    FILE *l;
    l = fopen("escribeProveedores.dat", "w");
    fprintf(l, "Imprimo los nodos de proveedores: \n");

    while(pt->sig != NULL)
    {
        if(pt->com != NULL)
        {
            printf("\n Falta procesar compras");
            procesaCompras(pt, art);
        }
        if(pt->pag != NULL)
        {
            printf("\n Falta procesar pagos");
            procesaPagos(pt);
        }
        fprintf(l, "%d\t%s\t%d\t%d\n", pt->prv_codigo, pt->prv_nombre, pt->prv_compras, pt->prv_pagos);
        pt = pt->sig;
    }
    fclose(l);
}

nodo_articulos *insertaArticulo(nodo_articulos *pt)
{
    nodo_articulos *prim = pt;

    while(pt->sig->sig != NULL)
    {
        pt = pt->sig;
    }

    nodo_articulos *nuevo;
    nuevo = (nodo_articulos*)malloc(sizeof(nodo_articulos));
    nuevo->art_codigo = (pt->art_codigo) + 1;
    printf("\n Ingrese pcompra y pventa y descripcion: ");
    scanf("%d %d %s", &nuevo->art_pcompra, &nuevo->art_pventa, nuevo->art_descripcion);
    nuevo->art_stock = 0;
    nuevo->art_compras = 0;
    nuevo->art_ventas = 0;
    nuevo->sig = NULL;
    pt->sig = nuevo;

    return prim;
}

/*
El usuario ingresa el nro. de artículo.
Valida la existencia, muestra los datos y pide confirmación.
*/
nodo_articulos *eliminaArticulo(nodo_articulos *pt)
{
    nodo_articulos *prim, *anterior;
    prim = pt;
    int codigo, confirma;
    int existe = 0;
    printf(" \n Ingrese nro de codigo de un articulo a eliminar: ");
    scanf("%d", &codigo);

    while(pt->sig != NULL)
    {
        if(pt->art_codigo == codigo ){
            existe = 1;
            break;
        }
        anterior = pt;
        pt = pt->sig;
    }

    if(existe != 1){
        printf("\n El articulo no existe ");
    }else{
        printf("\n El artículo es: ");
        printf("\n%d;%s;%d;%d;%d;%d;%d\n", pt->art_codigo, pt->art_descripcion, pt->art_stock, pt->art_compras, pt->art_pcompra, pt->art_ventas, pt->art_pventa);
        printf("\n Desea eliminar dicho artículo? (confirme con 1) ");
        scanf("%d", &confirma);

        if(confirma){
            //se elimina la cabeza
            if(pt->art_codigo == prim->art_codigo){
                prim = pt->sig;
                nodo_articulos *aux;
                aux = pt;
                free(aux);
            }else{
            //rutina que elimina el nodo linkea anterior con siguiente y libera el nodo
            anterior->sig = pt->sig;
            free(pt);
            }
        }else{
            printf("No confirmó, luego no hace nada");
        }
    }

    return prim;
}

nodo_articulos *modificaArticulo(nodo_articulos *pt)
{
    nodo_articulos *prim;
    prim = pt;
    int codigo, confirma;
    int existe = 0;
    printf(" \n Ingrese nro de codigo de un articulo a modificar: ");
    scanf("%d", &codigo);
    char art_descripcion[40];

    while(pt->sig != NULL)
    {
        if(pt->art_codigo == codigo ){
            existe = 1;
            break;
        }
        pt = pt->sig;
    }
    if(existe != 1){
        printf("\n El articulo no existe ");
    }else{
        printf("\n El artículo es: ");
        printf("\n%d;%s;%d;%d;%d;%d;%d\n", pt->art_codigo, pt->art_descripcion, pt->art_stock, pt->art_compras, pt->art_pcompra, pt->art_ventas, pt->art_pventa);
        printf("\n Desea modificar dicho artículo? (confirme con 1) ");
        scanf("%d", &confirma);

        if(confirma){
        //aca pisa la descripcion del nodo con una ingresada por el usuario
        printf("\n Ingrese descripción: ");
        scanf("%s", art_descripcion);
        strcpy(pt->art_descripcion, art_descripcion);

        }else{
            printf("No confirmó, luego no hace nada");
        }
    }

    return prim;

}

/*
Inserción
Código de cliente igual el último de la lista más 1.
El usuario ingresa el nombre.
*/
nodo_clientes *insertaCliente(nodo_clientes *pt)
{
    nodo_clientes *prim;
    prim = pt;

    while(pt->sig->sig != NULL)
    {
    pt = pt->sig;
    }

    nodo_clientes *nuevo;
    nuevo = (nodo_clientes*)malloc(sizeof(nodo_clientes));
    int cli_codigo = (pt->cli_codigo) + 1;
    char nombre[40];
    nuevo->cli_codigo = cli_codigo;
    printf("\n Ingrese nombre del cliente ");
    scanf("%s", nombre);
    strcpy(nuevo->cli_nombre, nombre);
    nuevo->cli_ventas = 0;
    nuevo->cli_cobranza = 0;
    nuevo->sig = NULL;
    nuevo->cob = NULL;
    nuevo->ven = NULL;
    pt->sig = nuevo;

    return prim;
}

nodo_clientes *eliminaCliente(nodo_clientes *pt)
{
    nodo_clientes *prim, *anterior;
    prim = pt;
    int codigo, confirma;
    int existe = 0;
    printf(" \n Ingrese nro de cliente a eliminar: ");
    scanf("%d", &codigo);

    while(pt->sig != NULL)
    {
        if(pt->cli_codigo == codigo ){
            existe = 1;
            break;
        }
        anterior = pt;
        pt = pt->sig;
    }
    if(existe != 1){
        printf("\n El articulo no existe ");
    }else{
        printf("\n El cliente es: ");
        printf("%d\t%s\t%d\t%d\n", pt->cli_codigo, pt->cli_nombre, pt->cli_ventas, pt->cli_cobranza);
        printf("\n Desea eliminar dicho cliente? (confirme con 1) ");
        scanf("%d", &confirma);

        if(confirma){
            //se elimina la cabeza
            if(pt->cli_codigo == prim->cli_codigo){
                prim = pt->sig;
                nodo_clientes *aux;
                aux = pt;
                free(aux);
            }else{
            //rutina que elimina el nodo linkea anterior con siguiente y libera el nodo
            anterior->sig = pt->sig;
            free(pt);
            }
        }else{
            printf("No confirmó, luego no hace nada");
        }
    }

    return prim;
}

nodo_clientes *modificaCliente(nodo_clientes *pt)
{
    nodo_clientes *prim;
    prim = pt;
    int codigo, confirma;
    int existe = 0;
    printf(" \n Ingrese nro de cliente a modificar: ");
    scanf("%d", &codigo);
    char cli_nombre[40];

    while(pt->sig != NULL)
    {
        if(pt->cli_codigo == codigo ){
            existe = 1;
            break;
        }
        pt = pt->sig;
    }
    if(existe != 1){
        printf("\n Dicho cliente no existe ");
    }else{
        printf("\n El cliente es: ");
        printf("%d\t%s\t%d\t%d\n", pt->cli_codigo, pt->cli_nombre, pt->cli_ventas, pt->cli_cobranza);
        printf("\n Desea modificar dicho cliente? (confirme con 1) ");
        scanf("%d", &confirma);

        if(confirma){
        //aca pisa la descripcion del nodo con una ingresada por el usuario
        printf("\n Ingrese nombre: ");
        scanf("%s", cli_nombre);
        strcpy(pt->cli_nombre, cli_nombre);

        }else{
            printf("No confirmó, luego no hace nada");
        }
    }

    return prim;
}

//inserta, elimina y modifica de proveedores
nodo_proveedores *insertaProveedor(nodo_proveedores *pt)
{
    nodo_proveedores *prim;
    prim = pt;

    while(pt->sig->sig != NULL)
    {
    pt = pt->sig;
    }

    nodo_proveedores *nuevo;
    nuevo = (nodo_proveedores*)malloc(sizeof(nodo_proveedores));
    int prv_codigo = (pt->prv_codigo) + 1;
    char nombre[40];
    nuevo->prv_codigo = prv_codigo;
    printf("\n Ingrese nombre del proveedor ");
    scanf("%s", nombre);
    strcpy(nuevo->prv_nombre, nombre);
    nuevo->prv_compras = 0;
    nuevo->prv_pagos = 0;
    nuevo->com = NULL;
    nuevo->pag = NULL;
    nuevo->sig = NULL;
    pt->sig = nuevo;

    return prim;
}

nodo_proveedores *eliminaProveedor(nodo_proveedores *pt)
{
    nodo_proveedores *prim, *anterior;
    prim = pt;
    int codigo, confirma;
    int existe = 0;
    printf(" \n Ingrese nro de proveedor a eliminar: ");
    scanf("%d", &codigo);

    while(pt->sig != NULL)
    {
        if(pt->prv_codigo == codigo ){
            existe = 1;
            break;
        }
        anterior = pt;
        pt = pt->sig;
    }
    if(existe != 1){
        printf("\n El proveedor no existe ");
    }else{
        printf("\n El proveedor es: ");
        printf("%d\t%s\t%d\t%d\n", pt->prv_codigo, pt->prv_nombre, pt->prv_compras, pt->prv_pagos);
        printf("\n Desea eliminar dicho proveedor? (confirme con 1) ");
        scanf("%d", &confirma);

        if(confirma){
            //se elimina la cabeza
            if(pt->prv_codigo == prim->prv_codigo){
                nodo_proveedores *aux;
                prim = pt->sig;
                printf("\n prim %p", prim);
                aux = pt;
                free(aux);
                //return prim;
            }else{
            //rutina que elimina el nodo linkea anterior con siguiente y libera el nodo
            anterior->sig = pt->sig;
            free(pt);
            }
        }else{
            printf("No confirmó, luego no hace nada");
        }
    }
    return prim;
}

nodo_proveedores *modificaProveedor(nodo_proveedores *pt)
{
    nodo_proveedores *prim;
    prim = pt;
    int codigo, confirma;
    int existe = 0;
    printf(" \n Ingrese nro de proveedor a modificar: ");
    scanf("%d", &codigo);
    char prv_nombre[40];

    while(pt->sig != NULL)
    {
        if(pt->prv_codigo == codigo ){
            existe = 1;
            break;
        }
        pt = pt->sig;
    }
    if(existe != 1){
        printf("\n Dicho proveedor no existe ");
    }else{
        printf("\n El proveedor es: ");
        printf("%d\t%s\t%d\t%d\n", pt->prv_codigo, pt->prv_nombre, pt->prv_compras, pt->prv_pagos);
        printf("\n Desea modificar dicho proveedor? (confirme con 1) ");
        scanf("%d", &confirma);

        if(confirma){
        //aca pisa la descripcion del nodo con una ingresada por el usuario
        printf("\n Ingrese nombre: ");
        scanf("%s", prv_nombre);
        strcpy(pt->prv_nombre, prv_nombre);

        }else{
            printf("No confirmó, luego no hace nada");
        }
    }

    return prim;
}

void GenPass(char *pass){
    int i;
    char c, letra[2];

    /* Inicialización de la secuencia */
    srand(time(NULL));
    printf("\n\nEste es el control de acceso: ");

    for (i=0; i<4; i++) {
        c=rand() % 26 + 97;
        putchar(c);
        sprintf(letra, "%c", c);
        strcat(pass, letra);
    }
}

int existeArtYHayCant(int *ven_codigo, int *ven_cantidad, nodo_articulos *nt)
{
    int existe = 0, hayCant = 0;
    while(nt != NULL && existe != 1)
    {
        if(nt->art_codigo == *ven_codigo)
        {
            hayCant = (*ven_cantidad >= nt->art_stock);
            existe = 1;
        }
        nt = nt->sig;
    }
    return (existe && hayCant);
}

//el usuario compra e inserta en la pila de ventas, del cliente
void usuarioCompra(nodo_clientes *cli, nodo_articulos *nt)
{
    int ven_codigo, ven_cantidad;
    printf("\n Ingrese el código de artículo que desea comprar ");
    scanf("%d %d", &ven_codigo, &ven_cantidad);
    if(!existeArtYHayCant(&ven_codigo, &ven_cantidad, nt)){
        printf("Art o cant no disponibles no se concreta la compra");
    }
    nodo_ventas *pri = (nodo_ventas *)malloc(sizeof(nodo_ventas));
    pri = cli->ven;
    nodo_ventas *nuevo = (nodo_ventas *)malloc(sizeof(nodo_ventas));
    nuevo->ven_codigo = ven_codigo;
    nuevo->ven_cantidad = ven_cantidad;
    nuevo->sig = pri;
    cli->ven = nuevo;
}

void usuarioPaga(nodo_clientes *cli)
{
    int pago;
    printf("\n Ingrese monto a pagar: ");
    scanf("%d", &pago);
    while(0 >= pago){
        printf("\n Ingrese monto mayor ");
        scanf("%d", &pago);
    }
        nodo_cobranza *nuevo = (nodo_cobranza *)malloc(sizeof(nodo_cobranza));
        nuevo->cob_importe = pago;
        nuevo->sig = NULL;
        nodo_cobranza *pri = cli->cob;

        if(pri == NULL)
        {//cola vacía
            cli->cob = nuevo;
            nuevo->sig = NULL;
            cli->cobult = nuevo;
        }else{
            cli->cob = nuevo;
            nuevo->sig = pri;
        }
}

//Ver Compras: apila y desapila
//Debe recorrer las ventas de la estructura clientes y mostrarlas.
void muestraVentasCliente(nodo_clientes *cli)
{
    nodo_ventas *com;
    while(cli != NULL)
    {
        com = cli->ven;
        printf("\n El cliente tiene las siguientes ventas: ");
        while(com != NULL)
        {
            scanf("\n %d; %d", &com->ven_codigo, &com->ven_cantidad);
            com = com->sig;
        }
        cli = cli->sig;
    }
}

void proveedorVende(nodo_proveedores *nprov, nodo_articulos *nt)
{
    int com_codigo, com_cantidad;
    printf("\n Ingrese el código de artículo que desea vender ");
    scanf("%d %d", &com_codigo, &com_cantidad);
    if(!existeArtYHayCant(&com_codigo, &com_cantidad, nt)){
        printf("Art o cant no disponibles no se concreta la venta");
        return;
    }
    nodo_compras *prim = nprov->com;
    nodo_compras* c;
    c = (nodo_compras *)malloc(sizeof(nodo_compras));
    c->com_codigo = com_codigo;
    c->com_cantidad = com_cantidad;
    c->sig = prim;
    nprov->com = c;
}

void proveedorCobra(nodo_proveedores *nprov)
{
    int pago;
    printf("\n Ingrese monto a pagar: ");
    scanf("%d", &pago);
    while(0 >= pago){
        printf("\n Ingrese monto mayor ");
        scanf("%d", &pago);
    }
        //encola el nuevo pago
        nodo_pagos *pri = nprov->pag;
        nodo_pagos *nuevo = (nodo_pagos *)malloc(sizeof(nodo_pagos));
        nuevo->pag_importe = pago;
        nprov->pag = nuevo;
        if(pri == NULL)
        {
            nprov->pagult = nuevo;
        }
        nuevo->sig = pri;
}

nodo_pagos *obtieneUltPago(nodo_pagos * n)
{
    while(n->sig != NULL){
        n = n->sig;
    }
    return n;
}

void muestraComprasProveedores(nodo_proveedores *pr)
{
    nodo_compras *com;
    while(pr != NULL)
    {
        com = pr->com;
        printf("\n El proveedor tiene las siguientes ventas: ");
        while(com != NULL)
        {
            scanf("\n %d; %d", &com->com_codigo, &com->com_cantidad);
            com = com->sig;
        }
        pr = pr->sig;
    }
}

void procesaVentas(nodo_clientes *cli, nodo_articulos *nt)
{
    nodo_ventas *nv, *aux;
    nv = cli->ven;
    nodo_articulos *itera;
    itera = nt;

    while(nv != NULL)
    { //para que se empiece por la cabeza de artículos
        nt = itera;
        while(nt != NULL)
        {
            if(nv->ven_codigo == nt->art_codigo){
                nt->art_stock = (nt->art_stock) - (nv->ven_cantidad);
                break;
            }
            nt = nt->sig;
        }
        aux = nv;
        nv = nv->sig;
        //voy desapilando ventas a medida que proceso
        free(aux);
    }

}


void procesaCobranzas(nodo_clientes *cli)
{
    nodo_cobranza *ultcob, *anteultcob;

    if(cli->cob == NULL) //no hay cobranzas
    {
        return;
    }

    anteultcob = obtieneAnteUltCob(cli->cob);
    ultcob = anteultcob->sig;

    while(ultcob != NULL)
    {
        if(anteultcob == NULL) // cola de 1 solo elemento
        {
            cli->cli_cobranza += ultcob->cob_importe;
            free(ultcob);
            cli->cob = NULL;
            return;
        }else{//cola con más de 1 elem
            cli->cli_cobranza += ultcob->cob_importe;
            anteultcob->sig = NULL;
            free(ultcob);
            ultcob = anteultcob;
            anteultcob = obtieneAnteUltCob(cli->cob);
        }
    }
}

nodo_cobranza *obtieneAnteUltCob(nodo_cobranza * nc)
{
    if(nc->sig == NULL){
    //hay un solo elemento en la pila
        return nc;
    }else{
        while(nc->sig->sig != NULL)
        {
            nc = nc->sig;
        }
        return nc;
    }
}

void procesaCompras(nodo_proveedores *np, nodo_articulos *nt)
{
    nodo_compras *nc, *aux;
    nc = np->com;
    nodo_articulos *itera;
    itera = nt;

    while(nc != NULL)
    {
        //para que se empiece por la cabeza de artículos
        nt = itera;
        while(nt != NULL)
        {
            if(nc->com_codigo == nt->art_codigo){
                nt->art_stock = (nt->art_stock) - (nc->com_cantidad);
                break;
            }
            nt = nt->sig;
        }
        aux = nc;
        nc = nc->sig;
        //voy desapilando ventas a medida que proceso
        free(aux);
    }
}

void procesaPagos(nodo_proveedores *nprov)
{
    nodo_pagos *ultcob, *anteultcob;

    if(nprov->pag == NULL) //no hay pagos
    {
        return;
    }

    anteultcob = obtieneAnteUltPagos(nprov->pag);
    ultcob = anteultcob->sig;

    while(ultcob != NULL)
    {
        if(anteultcob == NULL) // cola de 1 solo elemento
        {
            nprov->prv_pagos += ultcob->pag_importe;
            free(ultcob);
            nprov->pag = NULL;
            return;
        }else{//cola con más de 1 elem
            nprov->prv_pagos += ultcob->pag_importe;
            anteultcob->sig = NULL;
            free(ultcob);
            ultcob = anteultcob;
            anteultcob = obtieneAnteUltPagos(nprov->pag);
        }
    }
}

nodo_pagos *obtieneAnteUltPagos(nodo_pagos * nc)
{
    if(nc->sig == NULL){
    //hay un solo elemento en la pila
        return nc;
    }else{
        while(nc->sig->sig != NULL)
        {
            nc = nc->sig;
        }
        return nc;
    }
}

void guardaArchivos(nodo_articulos*art,nodo_clientes*cli,nodo_proveedores*nprov)
{
    escribeListaArts(art);
    escribeListaClientes(cli, art);
    escribeListaProveedores(nprov, art);
}
