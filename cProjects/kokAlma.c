#include<stdio.h>

double kokAl(int, int);

int main(){
    int x;
    int y;
    double sonuc;

    printf("Sayi giriniz: ");
    scanf("%d", &x);
    printf("Kok derecesini giriniz: ");
    scanf("%d", &y);

    sonuc = kokAl(x, y);
    
    printf("Sonuc: %.10lf", sonuc);

    return 0;
}

double kokAl(int sayi1, int sayi2){//sayi1 girilen sayi sayi2 kök derecesi
    double sonuc;
    double geciciSonuc1;

    //Tam sayı kısmının hesaplanması
    for(double i = 1; i <= sayi1; i++){
        sonuc = 1;
        for(int j = 0; j < sayi2; j++){
            sonuc = sonuc * i;
        }
        
        if ( sonuc > sayi1){
            sonuc = i - 1;

            break; 
        }else if(sonuc == sayi1){
            sonuc = i;

            return sonuc;
        }
    }

    //virgülden sonraki kısmın hesaplanması(virgülden sonra 10 haneye kadar)
    for(double a = 1; a >= 0.0000000001; a /= 10){
        for(double i = 0; i <= a; i += a/10){
            geciciSonuc1 = sonuc + i;
            for(int j = 1; j < sayi2; j++){
                geciciSonuc1 *= sonuc + i;
            }
            if(geciciSonuc1 > sayi1){
                sonuc = (sonuc + i) - (a/10);
                break;
            }else if(geciciSonuc1 == sayi1){
                return geciciSonuc1;
            }
        }
    }
    
    
    return sonuc;
}