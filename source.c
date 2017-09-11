#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>

unsigned long long int p, pi, l, gn=0x00, vs=0x00, im=0x00, rn;
double pcrs=0.5, pmtz=0.1; int r, v=0x00, *il, sp=0x09, b=0x00, ts;
char vt = (char)0x00, **vi, c=(char)0x00, *sc, **crc;
double **crf; long long int **cri, *cfit, **crcv;

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
    slt:
    printf("Vuoi impostare un set di comandi: ");
    scanf("%d", &r);
    fflush(stdin);
    if(r){
        printf("Vuoi impostare un campo di esistenza (1) o dei valori precisi (2): ");
        scanf("%d", &r);
        if(!(ts=r-1)){
            printf("Inserisci il campo di esistenza: ");
            while((c=getchar())!='#'){
                if(vt==(char)0x00)
                    if((c=='I')||(c=='i')){
                        cri = (long long int**)realloc(NULL,sizeof(long long int)*p+((int)'I'-(int)(vt='I')));
                        for(unsigned long long int i=0;i<p;i++)
                            *(cri+i) = (long long int*)realloc(NULL,sizeof(long long int)*l);
                    }else if((c=='F')||(c=='f')){
                        crf = (double**)realloc(NULL,sizeof(double)*p+((int)'F'-(int)(vt='F')));
                        for(unsigned long long int i=0;i<p;i++)
                            *(crf+i) = (double*)realloc(NULL,sizeof(double)*l);
                    }else if((c=='D')||(c=='d')){
                        crf = (double**)realloc(NULL,sizeof(double)*p+((int)'D'-(int)(vt='D')));
                        for(unsigned long long int i=0;i<p;i++)
                            *(crf+i) = (double*)realloc(NULL,sizeof(double)*l);
                    }else if((c=='C')||(c=='c')){
                        crc = (char**)realloc(NULL,sizeof(char)*p+((int)'C'-(int)(vt='C')));
                        for(unsigned long long int i=0;i<p;i++)
                            *(crc+i) = (char*)realloc(NULL,sizeof(char)*l);
                    }
                if(c=='['){
                    int i = 0x00;
                    il = (int*)realloc(NULL,sizeof(int)*0x02);
                    vi = (char**)realloc(NULL,sizeof(char)*0x02);
                    *(vi+v) = (char*)realloc(NULL,sizeof(char));
                    while((c=getchar())!=']'){
                        if(c==','){
                            *(il+v) = i;
                            i=0x00;
                            *(vi+(++v)) = (char*)realloc(NULL,sizeof(char));
                        }
                        if((c!='\n')&&(c!=',')&&(c!=(char)0x00)){
                            *(*(vi+v)+i) = c;
                            printf("%c - %c\n", c, *(*(vi+v)+i));
                            *(vi+v) = realloc(*(vi+v),sizeof(char)*((++i)+0x01));
                        }
                    }
                    *(il+v) = i;
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
            }
        }else{
            printf("Inserisci i valori: ");
            while((c=getchar())!='#'){
                if(vt==(char)0x00)
                    if((c=='I')||(c=='i')){
                        cri = (long long int**)realloc(NULL,sizeof(long long int)*p+((int)'I'-(int)(vt='I')));
                        for(unsigned long long int i=0;i<p;i++)
                            *(cri+i) = (long long int*)realloc(NULL,sizeof(long long int)*l);
                    }else if((c=='F')||(c=='f')){
                        crf = (double**)realloc(NULL,sizeof(double)*p+((int)'F'-(int)(vt='F')));
                        for(unsigned long long int i=0;i<p;i++)
                            *(crf+i) = (double*)realloc(NULL,sizeof(double)*l);
                    }else if((c=='D')||(c=='d')){
                        crf = (double**)realloc(NULL,sizeof(double)*p+((int)'D'-(int)(vt='D')));
                        for(unsigned long long int i=0;i<p;i++)
                            *(crf+i) = (double*)realloc(NULL,sizeof(double)*l);
                    }else if((c=='C')||(c=='c')) {
                        crcv = (long long int**)realloc(NULL,sizeof(long long int)*p+((int)'C'-(int)(vt='C')));
                        for(unsigned long long int i=0;i<p;i++)
                            *(crcv+i) = (long long int*)realloc(NULL,sizeof(long long int));
                    }
                if(c=='['){
                    int i = 0x00;
                    il = (int*)realloc(NULL,sizeof(int));
                    vi = (char**)realloc(NULL,sizeof(char));
                    *(vi+v) = (char*)realloc(NULL,sizeof(char));
                    while((c=getchar())!=']'){
                        if(c=='-'){
                            *(il+v) = i;
                            *(*(vi+v)+i) = '\0';
                            il = (int*)realloc(il,sizeof(int)*((++v)+0x01)+(i=0x00));
                            vi = (char**)realloc(vi,sizeof(char)*(v+0x01));
                            *(vi+v) = (char*)realloc(NULL,sizeof(char));
                        }
                        if((c!='\n')&&(c!='-')&&(c!=(char)0x00)){
                            *(*(vi+v)+i) = c;
                            *(vi+v) = (char*)realloc(*(vi+v),sizeof(char)*((++i)+0x01));
                        }
                        fflush(stdout);
                        printf("%s \n", *(vi+v));
                    }
                    *(il+v) = i + (v+0x01-(vs=v+0x01));
                    printf("%llu", vs);
                    *(*(vi+v)+i) = '\0'; break;
                }
            }
            if(c=='#')
                goto slt;
        }
    }else{
        vt = 'I';
        cri = (long long int**)realloc(NULL,sizeof(long long int)*p);
            for(int i=0;i<p;i++)
                *(cri+i) = (long long int*)realloc(NULL,sizeof(long long int)*l);
    }
    printf("Inserisci Pi: ");
    scanf("%llu", &pi);
    fflush(stdin);
    printf("\nPopolazione di %llu individui con %llu geni.\nProbabilita\' di crossover: %f\nProbabilita\' di mutazione: %f", p, l, pcrs, pmtz);
    if(!ts)
        if(v){ printf("\nIntervallo impostato da "); for(int i=0;i<*(il+0);i++)printf("%c",*(*(vi+0)+i)); printf(" a "); for(int i=0;i<*(il+1);i++)printf("%c", *(*(vi+1)+i)); printf(" con valori %c\n", vt);}
        else printf("\nIntervallo impostato da 0 a 1 con valori I\n");
    else{
        printf("\nValori impostati: ");
        for(unsigned long long i=0;i<vs;i++)
          printf("%s ", *(vi+i));
        printf("\n");
    }
    printf("Generazione iniziale impostata a %llu\n\n", pi);
    _genPop(ts);
    printf("--- Popolazione Generata ---\n\n", pi);
    for(unsigned long long int i=0;i<p;i++){
        for(unsigned long long int j=0;j<l;j++)
            if(vt=='I') printf("%lld", *(*(cri+i)+j));
            else if(vt=='F') printf("%0.2f", *(*(crf+i)+j));
            else if(vt=='D') printf("%.*f", sp, *(*(crf+i)+j));
            else if(!ts) printf("%c", *(*(crc+i)+j));
            else printf("%s", *(vi+(*(*(crcv+i)+j))));
        printf("\n");
    }
    printf("\n-- Inizio computazione --\n\n");
    _envGen();
    return 0;
}

void _genPop(int x){
    srand((unsigned)time(NULL));
    for(unsigned long long int i=0;i<p;i++){
        for(unsigned long long int j=0;j<l;j++)
            if(!x)
                if(!v) *(*(cri+i)+j) = rand()%2;
                else if(vt=='I') *(*(cri+i)+j) = atoi(*(vi+0))+(rand()%(atoi(*(vi+1))-atoi(*(vi+0))+0x01));
                else if(vt=='F') *(*(crf+i)+j) = (double)((rand()/(double)RAND_MAX)+atoi(*(vi+0)))+(double)(rand()%(atoi(*(vi+1))-atoi(*(vi+0))));
                else if(vt=='D') *(*(crf+i)+j) = (double)((rand()/(double)RAND_MAX)+atoi(*(vi+0)))+(double)(rand()%(atoi(*(vi+1))-atoi(*(vi+0))));
                else *(*(crc+i)+j) = (char)(((int)(*(*(vi+0)+0)))+(int)(rand()%(int)(((int)(*(*(vi+1)+0)))-((int)(*(*(vi+0)+0)))+0x01)));
            else
                if(vt=='I') *(*(cri+i)+j) = atoi(*(vi+(rand()%vs)));
                else if(vt=='F') *(*(crf+i)+j) = (double)atof(*(vi+(rand()%vs)));
                else if(vt=='D') *(*(crf+i)+j) = (double)atof(*(vi+(rand()%vs)));
                else *(*(crcv+i)+j) = rand()%vs;
    }
}

int _newGen(){
    srand((unsigned)time(NULL)); char **gnsc;
    long long int *mft, *scr, sdt, **gnsi; double **gnsf;
    mft = (long long int*)realloc(NULL,sizeof(long long int)*0x04);
    scr = (long long int*)realloc(NULL,sizeof(long long int)*0x02);
    if(vt=='I') gnsi = (long long int**)realloc(NULL,sizeof(long long int)*0x02);
    else if((vt=='F')||(vt=='D')) gnsf = (double**)realloc(NULL,sizeof(double)*0x02);
    else gnsc = (char**)realloc(NULL,sizeof(char)*0x02);
    for(int i=0;i<0x02;i++) if(vt=='I') *(gnsi+i) = (long long int*)realloc(NULL,sizeof(long long int));
    else if((vt=='F')||(vt=='D')) *(gnsf+i) = (double*)realloc(NULL,sizeof(double));
    else *(gnsc+i) = (char*)realloc(NULL,sizeof(char));
    for(int i=0;i<0x02;i++)
        if(!i) *(mft+i) = LLONG_MIN;
        else *(mft+i) = -0x01;
    for(unsigned long long int i=0;i<p;i++)
        if(*(mft+0x00)<(*(cfit+i)))
            for(int j=0;j<0x02;j++)
                if(!j) *(mft+j) = *(cfit+i);
                else *(mft+j) = i;
    for(unsigned long long int i=0;i<p;i++)
        if((*(mft+0x00)<(*(cfit+i)))&&(i!=*(mft+0x01)))
            for(int j=2;j<0x04;j++)
                if(!(j%2)) *(mft+j) = *(cfit+i);
                else *(mft+j) = i;
    *(scr+0x00) = rand()%(l-1);sdt = rand()%0x03;
    *(scr+0x01) = (rand()%(l-(*(scr+0x00))))+(*(scr+0x00));
    for(int i=0;i<0x02;i++)
        if(!i)
            for(unsigned long long int j=0,w=0,s=0;j<l;j++,w++){
                if((j==(*(scr+0x00)))||(j==(*(scr+0x01)))) s+=1+(w=0);
                if(vt=='I') *(gnsi+s) = (long long int*)realloc(*(gnsi+s),sizeof(long long int)*(w+1));
                else if((vt=='F')||(vt=='D')) *(gnsf+s) = (double*)realloc(*(gnsf+s),sizeof(double)*(w+1));
                else *(gnsc+s) = (char*)realloc(*(gnsc+s),sizeof(char)*(w+1));
                if(vt=='I') *(*(gnsi+s)+w) = *(*(cri+(*(mft+0x01)))+j);
                else if((vt=='F')||(vt=='D')) *(*(gnsf+s)+w) = *(*(crf+(*(mft+0x01)))+j);
                else *(*(gnsc+s)+w) = *(*(crc+(*(mft+0x01)))+j);
            }
        else
            for(unsigned long long int j=0,w=0,s=3;j<l;j++,w++){
                if((j==(*(scr+0x00)))||(j==(*(scr+0x01)))) s+=1+(w=0);
                if(vt=='I') *(gnsi+s) = (long long int*)realloc(*(gnsi+s),sizeof(long long int)*(w+1));
                else if((vt=='F')||(vt=='D')) *(gnsf+s) = (double*)realloc(*(gnsf+s),sizeof(double)*(w+1));
                else *(gnsc+s) = (char*)realloc(*(gnsc+s),sizeof(char)*(w+1));
                if(vt=='I') *(*(gnsi+s)+w) = *(*(cri+(*(mft+0x03)))+j);
                else if((vt=='F')||(vt=='D')) *(*(gnsf+s)+w) = *(*(crf+(*(mft+0x03)))+j);
                else *(*(gnsc+s)+w) = *(*(crc+(*(mft+0x03)))+j);
            }
}

void _pntGen(){
    printf("\n\nGenerazione numero: %llu\n\n", gn);
    for(long long int i=0;i<p;i++){
        for(long long int j=0;j<l;j++)
            if(vt=='I') printf("%lld", *(*(cri+i)+j));
            else if(vt=='F') printf("%0.2f", *(*(crf+i)+j));
            else if(vt=='D') printf("%.*f", sp, *(*(crf+i)+j));
            else printf("%c", *(*(crc+i)+j));
        printf("\n");
    }
}

void _envGen(){
    cfit = (long long int*)realloc(NULL,sizeof(long long int)*p);
    FILE *fn, *ft;
    do{
        fflush(stdout);
        gn++;
        fn = fopen(".in", "a+");
        for(unsigned long long int i=0;i<p;i++){
                printf("\nTest %llu\n", i);
            for(unsigned long long int j=0;j<l;j++)
                if(vt=='I') fprintf(fn,"%lld ", *(*(cri+i)+j));
                else if(vt=='F') fprintf(fn,"%0.2f ", *(*(crf+i)+j));
                else if(vt=='D') fprintf(fn,"%.*f ", sp, *(*(crf+i)+j));
                else if(!ts) fprintf(fn,"%c ", *(*(crc+i)+j));
                else fprintf(fn,"%s ", *(vi+(*(*(crcv+i)+j))));
            fprintf(fn,"-1 \n");
        }
        printf("\n-- Attendo risposta --\n\n");
        while((ft=fopen(".out", "r"))==NULL);
        printf("\n-- Risposta ottenuta --\n\n");
        for(unsigned long long int i=0;i<p;i++)
            fscanf(ft,"%lld", (cfit+i));
        fclose(fn);fclose(ft);
        remove(".in");remove(".out");
        for(unsigned long long int i=0;i<p;i++)
            printf("%lld ", *(cfit+i));
        system("PAUSE");
    }while(1);
    _pntGen();
}
