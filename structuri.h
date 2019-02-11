#ifndef STRUCTURI_H_INCLUDED
#define STRUCTURI_H_INCLUDED

struct Carte
{
    char valoare ;
    char culoare ;
};

struct Jucator
{
    struct Carte c[20];
    unsigned int nrCastig: 7 ;
} J1, J2;


#endif // STRUCTURI_H_INCLUDED
