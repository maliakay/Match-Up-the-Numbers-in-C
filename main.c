#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

#define MAX 20
void randomMatris(int matris[][MAX],int matrisKopya[][MAX], int N);// Random bir şekilde matris oluşturuyor
void drawBoard(int matris[][MAX], int N);
int choose(int matris[][MAX],int matrisKopya[][MAX],int N, int sayac, int puanlar[MAX], int pick3,int i,char kullanici[][MAX],int flag2,int flag1); // Oyun menüsü
void readFromFile(int matris[][MAX], char *fileName);
int dosyadanMatrisOlusturma(int matris[][MAX], int N);
int manuelMod(int matris[][MAX],int matrisKopya[][MAX], int N, int sayac);
int matrisHareketEttirme(int i, int j, int k, int l, int temp, int matris[][MAX],int matrisKopya[][MAX], int N,int sayac);
int sifirKontrolu(int matris[][MAX], int N);
void copyMatrix(int matris[][MAX], int matrisKopya[][MAX], int N);
void MatrisiEskiHalineGetir(int matris[][MAX], int matrisKopya[][MAX], int N);
void kullaniciKayit(char kullanici[][MAX], int i,int puanlar[MAX]);
void kullaniciGoruntuleme(char kullanici[][MAX],int i,int puanlar[MAX]);


int main()
{

    int pick,flag2=1,flag1=1;
    int matris[MAX][MAX]={{0}};
    int matrisKopya[MAX][MAX]={{0}};
    char kullanici[][MAX]={{}};
    int puanlar[MAX]={0};
    int i=0,sayac=0;
    int pick4,pick3,N=0;
    
    do{
        
        printf("1:Kullanici ekle\n2:Kullanici sec\n");
        scanf("%d",&pick4);
        switch(pick4)
        {
                
            case 1:
                i++;
                kullaniciKayit(kullanici,i,puanlar);
                kullaniciGoruntuleme(kullanici,i,puanlar);
                
                break;
                
            case 2:
                kullaniciGoruntuleme(kullanici,i,puanlar);
                printf("Adinizin karsilik geldigi numarayi tuslayiniz:");
                scanf("%d",&pick3);
                printf("%s:%d\n",kullanici[pick3],puanlar[pick3]);
                flag1=0;
                break;
        }
    }while(flag1);
    do{
        
        printf("1.Rastgele mmatris olustur:\n2.Dosyadan matris olustur:\n3.Kullanıcıların skorlarini göster:\n4.Cikis yap:\n");
        scanf("%d",&pick);
        switch(pick) // Ana menü
        {
            case 1:
                printf("Elde etmek istediğiniz matrisin boyutunu giriniz:");
                scanf("%d",&N);
                srand(time(NULL));
                sayac+= pow(5,N);
                randomMatris(matris,matrisKopya,N);
                drawBoard(matris,N);
                choose(matris,matrisKopya,N,sayac,puanlar,pick3,i,kullanici,flag2,flag1);
                break;
            case 2:
                printf("Lutfen dosyadan cekmek istediginiz matrisin boyutunu giriniz.");
                scanf("%d",&N);
                sayac+=pow(4,N);
                dosyadanMatrisOlusturma(matris,N);
                drawBoard(matris,N);
                choose(matris,matrisKopya,N,sayac,puanlar,pick3,i,kullanici,flag2,flag1);

                break;
            case 3:
                
                kullaniciGoruntuleme(kullanici,i,puanlar);
                
                break;
            case 4:
                printf("çıkış yapildi\n\n");
                flag2=0;
                break;
                
        }
    }while(flag2);
    return 0;
}

 void randomMatris(int matris[][MAX],int matrisKopya[][MAX], int N)
{

     int i=0, j=0,l,k, flag;
     for(k=0; k<2; k++)
     {
         for(l=1; l<=N; l++)
         {
             flag=1;
             while(flag)
             {
                 i = rand() % N;
                 j = rand() % N;
                 if(matris[i][j]==0)
                 {
                     matris[i][j]=l;
                     flag=0;
                 }
             }
         }
     }
 }
void drawBoard(int matris[][MAX], int N)
{
    int i, j;

    printf("     ");
    for (j = 0; j < N; j++)
    {
        printf("%-7d", j);
    }
    printf("\n");

    printf("   ");
    for (j = 0; j < N; j++)
    {
        printf("-------");
    }
    printf("\n");

    for (i = 0; i < N; i++)
    {
        printf("%-2d |", i);

        for (j = 0; j < N; j++)
        {
            if (matris[i][j] != 0)
                printf("  %d   |", matris[i][j]);
            else
                printf("      |");
        }
        printf("\n");

        printf("   ");
        for (j = 0; j < N; j++)
        {
            printf("-------");
        }
        printf("\n");
    }
}

int choose(int matris[][MAX],int matrisKopya[][MAX],int N, int sayac, int puanlar[MAX], int pick3,int i,char kullanici[][MAX],int flag2,int flag1)
{
    time_t startTime, endTime;
    int sure=0;
    int pick2,flag3=1;
    do{
        printf("1.Manuel Modda Oyna:\n2.Otomatik Modda Oyna:\n3.Ana Menuye Don\n");
        scanf("%d", &pick2);
        switch(pick2)
        {
            case 1:
                time(&startTime);
                manuelMod(matris,matrisKopya,N,sayac);
                time(&endTime);
                sure = difftime(endTime, startTime);
                sayac-=sure*10;
                printf("%d",sayac);
                puanlar[pick3]+=sayac;
                break;
            case 2:
                break;
            case 3:
                main();
                flag3=0;
                break;
                
        }
    }while(flag3);
    return main();
}
int dosyadanMatrisOlusturma(int matris[][MAX], int N){ // Dosyadan matrisi okuyor
    char fileName[20];
      printf("Dosya Adini Giriniz");
      scanf("%s",fileName);
    
    readFromFile(matris, fileName);
    return 0;
}
void readFromFile(int matris[][MAX], char *fileName){   // Dosyadan matrisi okuyor
    int i,j, temp;
    FILE *data = fopen(fileName,"r");
    if(!data){
        printf("Dosya Acilamadi!");
        return;
    }
    while(!feof(data)){
        fscanf(data,"%d %d %d\n",&i,&j,&temp);
        matris[i][j]=temp;
    }
      fclose(data);
}

int manuelMod(int matris[][MAX],int matrisKopya[][MAX], int N, int sayac){
    int i,j,k,l,temp=0;
    do{
        copyMatrix(matris,matrisKopya,N);
        printf("\nIslem yapmak istediginiz elemanin satirini giriniz:");
        scanf("%d",&i);
        printf("\nIslem yapmak istediginiz elemanin sutununu giriniz:");
        scanf("%d",&j);
        
        if(matris[i][j]==0)
        {
            printf("\nYanlis satir ve/veya sutun girdiniz");
        }
    }while(matris[i][j]==0);
    temp=matris[i][j];
    
    printf("\nEslestirmek istediginiz hedefin satirini giriniz:");
    scanf("%d",&k);
    printf("\nEslestirmek istediginiz hedefin sutununu giriniz:");
    scanf("%d",&l);

    if(matris[k][l]!=0 && matris[k][l]!=temp)
    {
        printf("Sectiginiz yone gidilemiyor\n");
        return manuelMod(matris,matrisKopya,N,sayac);
    }
    matrisHareketEttirme(i, j, k, l, temp, matris,matrisKopya,N,sayac);
    return sayac;
}
int matrisHareketEttirme(int i,int j,int k,int l,int temp,int matris[][MAX],int matrisKopya[][MAX],int N,int sayac)
    {
    int temp2,temp3,kontrol,flag=1,pick;
    temp2=matris[i][j];
    temp3=matris[k][l];
        if(k==i && j<l)
        {
            for(j=j; j<=l; j++)
            {
                if(matris[i][j]!=0 && matris[i][j]!=temp)
                {
                    printf("\nYanlis yol");
                    return manuelMod(matris,matrisKopya,N,sayac);
                }
                matris[i][j]=temp;
            }
        }
        else if (k==i && l<j)
        {
            for(j=j; j>=l; j--)
            {
                if(matris[i][j]!=0 && matris[i][j]!=temp)
                {
                    printf("\nYanlis yol");
                    return manuelMod(matris,matrisKopya,N,sayac);
                }
                matris[i][j]=temp;
            }
        }
        else if (l==j && i<k)
        {
            for(i=i; i<=k; i++)
            {
                if(matris[i][j]!=0 && matris[i][j]!=temp)
                {
                    printf("\nYanlis yol");
                    return manuelMod(matris,matrisKopya,N,sayac);
                }
                matris[i][j]=temp;
            }
        }
        else if (l==j && i>k)
        {
            for(i=i; i>=k; i--)
            {
                if(matris[i][j]!=0 && matris[i][j]!=temp)
                {
                    printf("\nYanlis yol");
                    return manuelMod(matris,matrisKopya,N,sayac);
                }
                matris[i][j]=temp;
            }
        }
    drawBoard(matris,N);
    kontrol=sifirKontrolu(matris, N);
   if(temp2==temp3)
   {
        printf("\nTebrikler iki sayiyiyi eşleştirmeyi başardiniz.\n");
   }
   if(kontrol==0)
    {
        printf("\nTebrikler matrisi cozdunuz.\nPUAN:%d\n",sayac);
        return sayac;
    }
    else if(kontrol==1)
    {
        do{
            printf("\n1:Geri al\n2:Devam et\n3:Matrisin cozumu yok\n");
            scanf("%d", &pick);
            if(pick==1)
            {
                MatrisiEskiHalineGetir(matris,matrisKopya,N);
                drawBoard(matris,N);
                return manuelMod(matris,matrisKopya,N,sayac);
            }else if(pick==2)
            {
                return manuelMod(matris,matrisKopya,N,sayac);
            }else if(pick==3)
            {
                return main();
            }
            else
            {
                printf("Yanlis sayi tusladiniz");
                flag=1;
            }
        }while(flag);
    }
    return manuelMod(matris,matrisKopya,N,sayac);
    }


int sifirKontrolu(int matris[][MAX], int N)
{
    int i, j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (matris[i][j] == 0) {
                return 1;
            }
        }
    }
    return 0;
}

void copyMatrix(int matris[][MAX], int matrisKopya[][MAX], int N) {
    int i, j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            matrisKopya[i][j] = matris[i][j];
        }
    }
}
void MatrisiEskiHalineGetir(int matris[][MAX], int matrisKopya[][MAX], int N)
{
    int i, j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            matris[i][j] = matrisKopya[i][j];
        }
    }
}
void kullaniciKayit(char kullanici[][MAX],int i,int puanlar[MAX]){
    printf("Kullanicinin adini giriniz:");
    scanf("%s",&kullanici[i]);
    puanlar[i]=0;
}
void kullaniciGoruntuleme(char kullanici[][MAX],int i,int puanlar[MAX]){
    int j;
    for(j=1; j<=i; j++){
        printf("%d:%s:%d\n", j, kullanici[j],puanlar[j]);
        
    }
}
