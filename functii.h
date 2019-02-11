#ifndef FUNCTII_H_INCLUDED
#define FUNCTII_H_INCLUDED

void verificareFisier( FILE *f )
{
    if(f == NULL)
    {
        printf( "Nu s-a putut deschide fisierul" );
    }
}

//generarea cartilor in fisier in mod aleator
void generare()
{
    FILE *f = fopen( "poker.txt", "w" );
    verificareFisier(f);
    struct Carte c[100];
    unsigned int i, j;
    char sir1[] = "23456789TAJQK";
    char sir2[] = "HDSC";
    for( j=0; j<100; j++ )
    {
        for( i=0; i<10; i++ )
        {
            c[i].valoare = sir1[rand() % (sizeof(sir1)-1)];
            c[i].culoare = sir2[rand() % (sizeof(sir2)-1)];
            if(c[i].valoare==c[i+1].valoare
                    && c[i].culoare==c[i+1].culoare)
                    c[i].valoare=sir1[rand() % (sizeof(sir1)-1)];
                    fprintf( f, "%c%c ", c[i].valoare, c[i].culoare );
        }
    fprintf(f, "\n");
    }
    fclose(f);
}
//Alocare dinamica
void alocare (struct Jucator *J1, struct Jucator *J2, int *v1, int *v2)
{
    J1 = ( struct Jucator * ) malloc( sizeof( struct Jucator ));
    J2 = ( struct Jucator * ) malloc( sizeof( struct Jucator ));
    v1 = ( int * ) malloc (5*sizeof(int));
    v2 = ( int * ) malloc (5*sizeof(int));
    if((J1==NULL) || (J2==NULL)) printf( "Eroare la alocare" );
    if((v1 == NULL) || (v2 == NULL)) printf( "Eroare la alocare" );
}

//Citirea din fisier
void citire ( struct Jucator *J1, struct Jucator *J2, FILE *f )
{
    unsigned int i;
    char x;
    for( i=0; i<5; i++ )
    {
        J1->c[i].valoare = fgetc(f);
        J1->c[i].culoare = fgetc(f);
        x = fgetc(f);
    }
    for( i=0; i<5; i++ )
    {
        J2->c[i].valoare = fgetc(f);
        J2->c[i].culoare = fgetc(f);
        x = fgetc(f);
    }
    x = fgetc(f);

    printf( "Cartile jucatorului J1 sunt: " );
    for( i=0; i<5; i++ )
        printf( "%c%c ", J1->c[i].valoare, J1->c[i].culoare );

    printf( "\nCartile jucatorului J2 sunt: " );
    for( i=0; i<5; i++ )
        printf( "%c%c ", J2->c[i].valoare, J2->c[i].culoare) ;
    printf("\n");
}
//Conversia valorilor cartilor din char in int
void conversie (struct Jucator *J, int *v)
{
    unsigned int i;
    for( i=0; i<5; i++ )
        switch( J->c[i].valoare )
        {
        case '2':
            *(v+i)=2;
            break;
        case '3':
            *(v+i)=3;
            break;
        case '4':
            *(v+i)=4;
            break;
        case '5':
            *(v+i)=5;
            break;
        case '6':
            *(v+i)=6;
            break;
        case '7':
            *(v+i)=7;
            break;
        case '8':
            *(v+i)=8;
            break;
        case '9':
            *(v+i)=9;
            break;
        case 'T':
            *(v+i)=10;
            break;
        case 'J':
            *(v+i)=12;
            break;
        case 'Q':
            *(v+i)=13;
            break;
        case 'K':
            *(v+i)=14;
            break;
        case 'A':
            *(v+i)=15;
            break;
        }
}

//functia de comparare pentru qsort, folosita la ordonarea vectorilor cu valorile cartilor
int cmp (const void *a, const void *b)
{
    const int *aaux = (const int *) a;
    const int *baux = (const int *) b;
    return (*aaux) - (*baux);
}

int verificareMana (struct Jucator *J, int *v)
{
    int i,a;

    //verificare Straight Flush - chinta de culoare
    a=0;
    for( i=0; i<4; i++ )
        if((J->c[i].culoare == J->c[i+1].culoare)
                && (v[i+1] == v[i+1])) a++;
    if( a==4 )return 9;

    //Verificare Straight Flush (cazul in care asul este carte mica)
    a=0;
    for( i=0; i<4; i++ )
        if(J->c[i].culoare == J->c[i+1].culoare)
            a++;
    if((a==4)
            && ((v[0]==2)
                && (v[1]==3)
                && (v[2]==4)
                && (v[3]==5)
                && (v[4]==15)))
        return 9;


    //verificare Four of a kind (careu)
    a=0;
    for( i=0; i<4; i++ )
        if(v[i] != v[i+1]) a++;
    if( a==1 ) return 8;

    //verificare Full House (3 carti de un fel, 2 carti de un fel)
    if ((v[0]==v[1] && v[2]==v[3]==v[4])
            || (v[0]==v[1]==v[2] && v[3]==v[4])) return 7;

    //verificare Flush (Culoare)
    a=0;
    for( i=0; i<4; i++ )
        if( J->c[i].culoare != J->c[i+1].culoare) a++;
    if ( a==0 ) return 6;

    //verificare Straight - chinta
    a=0;
    for( i=0; i<4; i++ )
        if (v[i+1] != v[i]+1) a++;
    if( a==0 ) return 5;

    //verificare Straight (cazul in care asul este carte mica)
    if((v[0]==2)
            && (v[1]==3)
            && (v[2]==4)
            && (v[3] ==5)
            && (v[4]==15)) return 5;

    //verificare Three of a Kind
    a=0;
    for( i=0; i<4; i++ )
        if (v[i] != v[i+1]) a++;
    if(a==2) return 4;

    //verificare Two Pair
    if ((v[0]==v[1]&& v[2]==v[3])
            || (v[0]==v[1] && v[3]==v[4])
            || (v[1]==v[2]&& v[3]==v[4]))
        return 3;

    //verificare One Pair
    a=0;
    for( i=0; i<4; i++ )
        if(v[i] != v[i+1]) a++;
    if( a==3 ) return 2;

    //verificare High Cards (No Pair)
    a=0;
    for( i=0; i<4; i++ )
        if( v[i] != v[i+1]) a++;
    if( a==4 ) return 1;
}

void afisareMana(int x)
{

    switch (x)
    {
    case 9:
        printf ( "Straight Flush (chinta de culoare)" );
        break;
    case 8:
        printf( "Four of a kind (careu)" );
        break;
    case 7:
        printf ( "Full House (trei carti de un fel, doua carti de un fel)" );
        break;
    case 6:
        printf ( "Flush (culoare)" );
        break;
    case 5:
        printf( "Straight (chinta)" );
        break;
    case 4:
        printf( "Three of a kind (trei carti de un fel)" );
        break;
    case 3:
        printf( "Two pair (doua perechi)" );
        break;
    case 2:
        printf( "One pair (o pereche)" );
        break;
    case 1:
        printf( "No pair (high cards)" );
        break;
    }
}
//verificarea mainilor si a castigatorului pentru o runda
void joc(struct Jucator *J1, struct Jucator *J2, int *v1, int *v2, int i)
{
    int a = verificareMana( &J1, v1 );
    printf( "Mana jucatorului 1 este " );
    afisareMana( a );
    printf("\n");
    int b = verificareMana( &J2, v2 );
    printf("Mana jucatorului 2 este ");
    afisareMana( b );
    printf("\n");

    //daca ambele maini sunt chinte sau chinte de culoare (se verifica doar cea mai mare carte)
    if((a==b==9)||(a==b==5))
    {
        if( v1[4] > v2[4] )
        {
            printf( "Jucatorul 1 castiga runda %d \n", i );
            J1->nrCastig++;
        }
        else if ( v1[4] < v2[4] )
        {
            printf( "Jucatorul 2 castiga runda %d \n", i );
            J2->nrCastig++;
        }
    }
    //daca ambele maini sunt 4 of a kind, 3 of a kind sau one pair
    else if(((a==4)&&(b==4)) || ((a==8)&&(b==8)) || ((a==3) &&(b==3)))
    {
        int k, x, y;
        for( k=0; k<4; k++ )
        {
            if(v1[k] == v1[k+1]) x = k;
            if(v2[k] == v2[k+1]) y = k;
        }
        if( v1[x] > v2[y] )
        {
            printf( "Jucatorul 1 castiga runda %d \n", i );
            J1->nrCastig++;
        }
        else if( v1[x] < v2[y] )
        {
            printf( "Jucatorul 2 castiga runda %d \n", i );
            J2->nrCastig++;
        }
        else printf("Remiza");
    }
    //daca mana este oricare alta:
    else if ( a > b )
    {
        printf( "Jucatorul 1 castiga runda %d \n", i );
        J1->nrCastig++;
    }
    else if ( a < b )
    {
        printf( "Jucatorul 2 castiga runda %d \n", i );
        J2->nrCastig++;
    }
    else if ( v1[4] > v2[4] )
    {
        printf( "Jucatorul 1 castiga runda %d \n", i );
        J1->nrCastig++;
    }
    else if ( v1[4] < v2[4] )
    {
        printf( "Jucatorul 2 castiga runda %d \n", i );
        J2->nrCastig++;
    }
    else if( v1[3] > v2[3] )
    {
        printf( "Jucatorul 1 castiga runda %d \n",i );
        J1->nrCastig++;
    }
    else if( v1[3] < v2[3] )
    {
        printf( "Jucatorul 2 castiga runda %d \n", i );
        J2->nrCastig++;
    }
    else if ( v1[2] > v2[2] )
    {
        printf( "Jucatorul 1 castiga runda %d \n",i );
        J1->nrCastig++;
    }
    else if( v1[2] < v2[2] )
    {
        printf( "Jucatorul 2 castiga runda %d \n", i );
        J2->nrCastig++;
    }
    else if( v1[1] > v2[1] )
    {
        printf( "Jucatorul 1 castiga runda %d \n",i );
        J1->nrCastig++;
    }
    else if( v1[1] < v2[1] )
    {
        printf( "Jucatorul 2 castiga runda %d \n", i );
        J2->nrCastig++;
    }
    else if( v1[0] > v2[0] )
    {
        printf( "Jucatorul 1 castiga runda %d \n",i );
        J1->nrCastig++;
    }
    else if( v1[0] < v2[0] )
    {
        printf( "Jucatorul 2 castiga runda %d \n", i );
        J2->nrCastig++;
    }
    else printf( "Remiza \n" );

    printf("\n");
}

void poker ()
{
    int v1[5], v2[5], i;
    generare();
    FILE *f = fopen( "poker.txt","r" );
    verificareFisier(f);
    alocare( &J1, &J2, v1, v2);
    for( i = 1; i <= 100; i++ )
    {
        printf( "RUNDA %d \n", i );
        citire( &J1, &J2, f );
        conversie( &J1, v1 );
        conversie( &J2, v2 );
        qsort( v1, 5, sizeof(int), cmp );
        qsort( v2, 5, sizeof(int), cmp );
        joc( &J1, &J2, v1, v2, i );
        if( feof(f) )break;

    }
    printf( "Jucatorul 1 a castigat %d runde \n", J1.nrCastig );
    printf( "Jucatorul 2 a castigat %d runde", J2.nrCastig );
    fclose( f );
    free( &J1 );
    free( &J2 );
    free( v1 );
    free( v2 );
}

#endif // FUNCTII_H_INCLUDED
