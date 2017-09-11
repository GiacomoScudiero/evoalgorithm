#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include <math.h>
#ifdef _WIN32
    #include <windows.h>
    #define HDN 1
#endif
#define DEBUG 0

unsigned long long int p, pi, l, gn=0x00, vs=0x00; char **gnrc, *cdc=(char)0x00;
double pcrs=0.5, pmtz=0.1, **gnrd, *cfit; int r, v=0x00, sp=0x09, inf=0x00, lc=0x00;
char vt=(char)0x00, **vi, c=(char)0x00, *sc; long long int **gnr;

void _genPop(int x);
int _newGen();
void _pntGen();
void _envGen();

int main(int argc, char *argv[]){
    printf("Inserisci P: ");
    scanf("%llu", &p);
    fflush(stdin);
    printf("Inserisci L: ");
    scanf("%llu", &l);
    fflush(stdin);
    printf("Vuoi impostare valori avanzati: ");
    scanf("%d", &r);
    fflush(stdin);
    if(r){
        printf("Inserisci Pcrs: ");
        scanf("%f", &pcrs);
        fflush(stdin);
        printf("Inserisci Pmtz: ");
        scanf("%f", &pmtz);
        fflush(stdin);
    }
    slt:v=0x00;
    printf("Vuoi impostare un set di comandi: ");
    scanf("%d", &r);
    fflush(stdin);
    if(r){
        printf("Vuoi impostare un campo di esistenza (1) o dei valori precisi (2): ");
        scanf("%d", &r);
        fflush(stdin);
        if(!(r-1))
            printf("Inserisci il campo di esistenza: ");
        else
            printf("Inserisci i valori: ");
        while((c=getchar())!='#'){
            if(vt==(char)0x00)
                if((c=='I')||(c=='i')) vt='I';
                else if((c=='F')||(c=='f')) vt='F';
                else if((c=='D')||(c=='d')) vt='D';
                else vt='C';
            if(c=='['){
                unsigned long long int i = 0x00;
                vi = (char**)realloc(NULL,sizeof(char));
                *(vi+v) = (char*)realloc(NULL,sizeof(char));
                while((c=getchar())!=']'){
                    if(((!(r-1))&&(c==','))||((r-1)&&(c=='-'))){
                        *(*(vi+v)+i) = '\0';
                        vi = (char**)realloc(vi,sizeof(char)*((++v)+0x01));
                        *(vi+v) = (char*)realloc(NULL,sizeof(char)+(i=0x00));
                    }
                    if((c!='\n')&&(((!(r-1))&&(c!=','))||((r-1)&&(c!='-')))&&(c!=(char)0x00)&&(c!=' ')){
                        if((vt!='C')&&(c=='*'))
                            inf = 0x01;
                        *(*(vi+v)+i) = c;
                        *(vi+v) = realloc(*(vi+v),sizeof(char)*((++i)+0x01));
                    }
                }
                *(*(vi+v)+i) = '\0' + ((v+0x01)-(vs=v+0x01));
                if((vt=='D')&&((c=getchar())!='\n')&&(!(i=0))){
                    sc = (char*)realloc(NULL,sizeof(char));
                    do{
                        if((c>='0')&&(c<='9')){
                            *(sc+i) = c;
                            sc = (char*)realloc(sc,sizeof(char)*((++i)+0x01));
                        }
                    }while((c=getchar())!='\n');
                    sp = atoi(sc);
                }
                break;
            }
        } if(c=='#') goto slt;
    }else vt = 'I';
    printf("Inserisci Pi: ");
    scanf("%llu", &pi);
    fflush(stdin);
    if(DEBUG)
        printf("\nPopolazione di %llu individui con %llu geni.\nProbabilita\' di crossover: %f\nProbabilita\' di mutazione: %f", p, l, pcrs, pmtz);
    if(DEBUG)
        if(!(r-1)){
            if(v) printf("\nIntervallo impostato da %s a %s con valori %c\n", *(vi+0), *(vi+1), vt);
            else printf("\nIntervallo impostato da 0 a 1 con valori I\n");
        }else{
            printf("\nValori impostati: ");
            for(unsigned long long i=0;i<vs;i++)
              printf("%s ", *(vi+i));
            printf("\n");
        }
    if(DEBUG)
        printf("Generazione iniziale impostata a %llu\n\n", pi);
    _genPop(!(r-1));
    if(DEBUG){
        printf("--- Popolazione Generata ---\n\n");
        for(unsigned long long int i=0;i<p;i++){
            for(unsigned long long int j=0;j<l;j++)
                if(vt=='I') printf("%lld", !(r-1) ? *(*(gnr+i)+j) : atoi(*(vi+(*(*(gnr+i)+j)))));
                else if(vt=='F') printf("%0.2f", !(r-1) ? *(*(gnrd+i)+j) : atof(*(vi+(*(*(gnr+i)+j)))));
                else if(vt=='D') printf("%.*f", sp, !(r-1) ? *(*(gnrd+i)+j) : atof(*(vi+(*(*(gnr+i)+j)))));
                else if(!(r-1)) printf("%c", *(*(gnrc+i)+j));
                else printf("%s", *(vi+(*(*(gnr+i)+j))));
                printf("\n");
        }
    }
    printf("\n-- Inizio computazione --\n\n");
    _envGen();
    return 0;
}

void _genPop(int x){
    srand((unsigned)time(NULL));
    if((vt=='I')||(!x)) gnr = (long long int**)realloc(NULL,sizeof(long long int)*p);
    else if(vt=='C') gnrc = (char**)realloc(NULL,sizeof(char)*p);
    else gnrd = (double**)realloc(NULL,sizeof(double)*p);
    for(unsigned long long int i=0;i<p;i++)
        if((vt=='I')||(!x)) *(gnr+i) = (long long int*)realloc(NULL,sizeof(long long int)*l);
        else if(vt=='C') *(gnrc+i) = (char*)realloc(NULL,sizeof(char)*l);
        else *(gnrd+i) = (double*)realloc(NULL,sizeof(double)*l);
    for(unsigned long long int i=0;i<p;i++)
        for(unsigned long long int j=0;j<l;j++)
            if(x)
                if(vt=='I') *(*(gnr+i)+j) = atoi(*(vi+0)) + rand()%atoi(*(vi+1));
                else if(vt=='C') *(*(gnrc+i)+j) = (int)**(vi+0) + rand()%((int)**(vi+1)-(int)**(vi+0));
                else *(*(gnrd+i)+j) = ((double)rand()/(double)RAND_MAX) + (double)(rand()%(int)atof(*(vi+1)));
            else
                *(*(gnr+i)+j) = rand()%vs;
}

int _newGen(){
    srand((unsigned)time(NULL));
    long long int *t; unsigned long long int a, b, c, d, *vd, vl;
    vd = (unsigned long long int*)realloc(NULL,sizeof(unsigned long long int));
    t = (long long int*)realloc(NULL,sizeof(long long int)*0x02);
    for(short int i = 0x00;i<0x02;i++) *(t+i) = LLONG_MIN;
    for(unsigned long long i=0;i<p;i++)
        if(*(cfit+i)>*(t+0x00))  *(t+0x00) = *(cfit+i) + (i-(a=i));
    for(unsigned long long i=0x00;i<p;i++)
        if((*(cfit+i)>*(t+0x01))&&(i!=a)) *(t+0x01) = *(cfit+i) + (i-(b=i));
    for(unsigned long long i=0;i<p;i++)
        if(*(cfit+i)<*(t+0x00))  *(t+0x00) = *(cfit+i) + (i-(c=i));
    for(unsigned long long i=0x00;i<p;i++)
        if((*(cfit+i)<*(t+0x01))&&(i!=c)) *(t+0x01) = *(cfit+i) + (i-(d=i));
    if(abs(cos((double)rand()))<=pcrs){
        *(vd+0x00)=abs(rand()%((int)((l/0x02)+(0x01/0x02))-0x01))+abs(cos(rand()));
        vl = (rand()%0x02)+0x01;
        for(unsigned long long int j=0;j<*(vd+0x00);j++)
            if((vt=='I')||(!(!(r-1))))
                *(*(gnr+c)+j) = *(*(gnr+a)+j)+(*(*(gnr+b)+j)-(*(*(gnr+d)+j) = *(*(gnr+b)+j)));
            else if((vt=='F')||(vt=='D'))
                *(*(gnrd+c)+j) = *(*(gnrd+a)+j)+(*(*(gnrd+b)+j)-(*(*(gnrd+d)+j) = *(*(gnrd+b)+j)));
            else
                *(*(gnrc+c)+j) = *(*(gnrc+a)+j)+(*(*(gnrc+b)+j)-(*(*(gnrc+d)+j) = *(*(gnrc+b)+j)));
        for(unsigned long long int j=*(vd+0x00);j<l;j++)
            if((vt=='I')||(!(!(r-1))))
                *(*(gnr+c)+j) = *(*(gnr+b)+j)+(*(*(gnr+a)+j)-(*(*(gnr+d)+j) = *(*(gnr+a)+j)));
            else if((vt=='F')||(vt=='D'))
                *(*(gnrd+c)+j) = *(*(gnrd+b)+j)+(*(*(gnrd+a)+j)-(*(*(gnrd+d)+j) = *(*(gnrd+a)+j)));
            else
                *(*(gnrc+c)+j) = *(*(gnrc+b)+j)+(*(*(gnrc+a)+j)-(*(*(gnrc+d)+j) = *(*(gnrc+a)+j)));
    }
    if(abs(cos((double)rand()))<=pmtz){
        vl = (rand()%(l-0x01))+0x01;
        if(!(r-0x01))
            if(vt=='I') *(*(gnr+c)+vl) = atoi(*(vi+0)) + rand()%atoi(*(vi+1));
            else if(vt=='C') *(*(gnrc+c)+vl) = (int)**(vi+0) + rand()%((int)**(vi+1)-(int)**(vi+0));
            else *(*(gnrd+c)+vl) = ((double)rand()/(double)RAND_MAX) + (double)(rand()%(int)atof(*(vi+1)));
        else
            *(*(gnr+c)+vl) = rand()%vs;
        vl = (rand()%(l-0x01))+0x01;
        if(!(r-0x01))
            if(vt=='I') *(*(gnr+d)+vl) = atoi(*(vi+0)) + rand()%atoi(*(vi+1));
            else if(vt=='C') *(*(gnrc+d)+vl) = (int)**(vi+0) + rand()%((int)**(vi+1)-(int)**(vi+0));
            else *(*(gnrd+d)+vl) = ((double)rand()/(double)RAND_MAX) + (double)(rand()%(int)atof(*(vi+1)));
        else
            *(*(gnr+d)+vl) = rand()%vs;
    }gn++;
//    srand((unsigned)time(NULL)); char **gnsc;
//    long long int *mft, *scr, sdt, **gnsi; double **gnsf;
//    mft = (long long int*)realloc(NULL,sizeof(long long int)*0x04);
//    scr = (long long int*)realloc(NULL,sizeof(long long int)*0x02);
//    if(vt=='I') gnsi = (long long int**)realloc(NULL,sizeof(long long int)*0x02);
//    else if((vt=='F')||(vt=='D')) gnsf = (double**)realloc(NULL,sizeof(double)*0x02);
//    else gnsc = (char**)realloc(NULL,sizeof(char)*0x02);
//    for(int i=0;i<0x02;i++) if(vt=='I') *(gnsi+i) = (long long int*)realloc(NULL,sizeof(long long int));
//    else if((vt=='F')||(vt=='D')) *(gnsf+i) = (double*)realloc(NULL,sizeof(double));
//    else *(gnsc+i) = (char*)realloc(NULL,sizeof(char));
//    for(int i=0;i<0x02;i++)
//        if(!i) *(mft+i) = LLONG_MIN;
//        else *(mft+i) = -0x01;
//    for(unsigned long long int i=0;i<p;i++)
//        if(*(mft+0x00)<(*(cfit+i)))
//            for(int j=0;j<0x02;j++)
//                if(!j) *(mft+j) = *(cfit+i);
//                else *(mft+j) = i;
//    for(unsigned long long int i=0;i<p;i++)
//        if((*(mft+0x00)<(*(cfit+i)))&&(i!=*(mft+0x01)))
//            for(int j=2;j<0x04;j++)
//                if(!(j%2)) *(mft+j) = *(cfit+i);
//                else *(mft+j) = i;
//    *(scr+0x00) = rand()%(l-1);sdt = rand()%0x03;
//    *(scr+0x01) = (rand()%(l-(*(scr+0x00))))+(*(scr+0x00));
//    for(int i=0;i<0x02;i++)
//        if(!i)
//            for(unsigned long long int j=0,w=0,s=0;j<l;j++,w++){
//                if((j==(*(scr+0x00)))||(j==(*(scr+0x01)))) s+=1+(w=0);
//                if(vt=='I') *(gnsi+s) = (long long int*)realloc(*(gnsi+s),sizeof(long long int)*(w+1));
//                else if((vt=='F')||(vt=='D')) *(gnsf+s) = (double*)realloc(*(gnsf+s),sizeof(double)*(w+1));
//                else *(gnsc+s) = (char*)realloc(*(gnsc+s),sizeof(char)*(w+1));
//                if(vt=='I') *(*(gnsi+s)+w) = *(*(cri+(*(mft+0x01)))+j);
//                else if((vt=='F')||(vt=='D')) *(*(gnsf+s)+w) = *(*(crf+(*(mft+0x01)))+j);
//                else *(*(gnsc+s)+w) = *(*(crc+(*(mft+0x01)))+j);
//            }
//        else
//            for(unsigned long long int j=0,w=0,s=3;j<l;j++,w++){
//                if((j==(*(scr+0x00)))||(j==(*(scr+0x01)))) s+=1+(w=0);
//                if(vt=='I') *(gnsi+s) = (long long int*)realloc(*(gnsi+s),sizeof(long long int)*(w+1));
//                else if((vt=='F')||(vt=='D')) *(gnsf+s) = (double*)realloc(*(gnsf+s),sizeof(double)*(w+1));
//                else *(gnsc+s) = (char*)realloc(*(gnsc+s),sizeof(char)*(w+1));
//                if(vt=='I') *(*(gnsi+s)+w) = *(*(cri+(*(mft+0x03)))+j);
//                else if((vt=='F')||(vt=='D')) *(*(gnsf+s)+w) = *(*(crf+(*(mft+0x03)))+j);
//                else *(*(gnsc+s)+w) = *(*(crc+(*(mft+0x03)))+j);
//            }
    _pntGen();
    return 1;
}

void _pntGen(){
    if(DEBUG){
        printf("\n\nGenerazione numero: %llu\n\n", gn);
        for(long long int i=0;i<p;i++){
            fflush(stdout);
            for(long long int j=0;j<l;j++)
                if(vt=='I') printf("%lld", !(r-1) ? *(*(gnr+i)+j) : atoi(*(vi+(*(*(gnr+i)+j)))));
                else if(vt=='F') printf("%0.2f", !(r-1) ? *(*(gnrd+i)+j) : atof(*(vi+(*(*(gnr+i)+j)))));
                else if(vt=='D') printf("%.*f", sp, !(r-1) ? *(*(gnrd+i)+j) : atof(*(vi+(*(*(gnr+i)+j)))));
                else if(!(r-1)) printf("%c", *(*(gnrc+i)+j));
                else printf("%s", *(vi+(*(*(gnr+i)+j))));
            printf("\n");
        }
    }
}

void _envGen(){
    cfit = (double*)realloc(NULL,sizeof(double)*p);
    FILE *fn, *ft;
    do{
        fflush(stdout); fn = fopen(".in", "a+"); fflush(fn);
        #ifdef _WIN32
            if(HDN)
                SetFileAttributes(".in", FILE_ATTRIBUTE_HIDDEN);
        #endif
        printf("\n-- Contatto l\'applicazione --\n\n");
        fprintf(fn,"%llu %llu \n", p, l);
        for(unsigned long long int i=0;i<p;i++){
            for(unsigned long long int j=0;j<l;j++)
                if(vt=='I') fprintf(fn,"%lld ", !(r-1) ? *(*(gnr+i)+j) : atoi(*(vi+(*(*(gnr+i)+j)))));
                else if(vt=='F') fprintf(fn,"%0.2f ", !(r-1) ? *(*(gnrd+i)+j) : atof(*(vi+(*(*(gnr+i)+j)))));
                else if(vt=='D') fprintf(fn,"%.*f ", sp, !(r-1) ? *(*(gnrd+i)+j) : atof(*(vi+(*(*(gnr+i)+j)))));
                else if(!(r-1)) fprintf(fn,"%c ", *(*(gnrc+i)+j));
                else fprintf(fn,"%s ", *(vi+(*(*(gnr+i)+j))));
            fflush(fn);fprintf(fn,"\n");fflush(fn);
        }
        printf("\n-- Attendo risposta --\n\n");
        while((ft=fopen(".out", "r"))==NULL);
        fclose(fn);remove(".in");
        printf("\n-- Risposta ottenuta --\n\n");
        remove(".in");
        printf("\n-- Elaboro i risultati --\n\n");
        Sleep(700);
        system("PAUSE");
        remove(".in");
        for(unsigned long long int i=0;i<p;i++){
            fscanf(ft,"%lld", (cfit+i));
        }
        fclose(ft);remove(".out");
    }while(_newGen());
    _pntGen();
}
