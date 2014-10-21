/*
MEHMET BEKTAÞ	100201007
KUTAY AKYOL	    110201085
RECEP UCE	    110201083
*/


#include <allegro.h>
#include <stdio.h>
#include <string.h>

int tuglax[49];     //48 tane tuglanýn x,y ve canýný 
int tuglay[49];     //diziler yardýmýyla tutuyorum.
int tuglacan[49];   //karýþýklýðý engellemek için dizinin boyutunu 48+1=49 yaptým.

struct oyuncuicin
{
       char isim[20];
       int puan;
};


void oyunu_yukle(void);    //allegro kütüphanesi için gerekli kodlarý burada topladým
void top_gider(void);    //topun hareketi, duvarlardan ve cubuktan sekmesi
void cubuk_gider(void);  //çubuðun saða ve sola hareketi
void tuglalar(int [], int [], int[],struct oyuncuicin);        //tuglalarýn dizimi rengi ve kaç vurmada kýrýlacaðýnýn özellikleri
void top_tuglaya_carpar(int [], int [], int[],struct oyuncuicin);        //topun tuglaya çarpma anýndaki olaylar


int topx=50, topy=400;           //topun koordinatlarý
int etopx, etopy;         //topun bir önceki koordinatlarý
int cubukx=250, cubuky=450;       //cubugun koordinatlarý
int ecubukx, ecubuky;     //cubugun bir önceki koordinatlarý
int cubukuz=100;
int yon=3,puan=0;                        //1:sol-üst    2:sol-alt   3:sað-üst:   4:sað-alt

int k;           //tugla[k] struct deðiþkeni için
int x,y;

BITMAP *buffer;
SAMPLE *ses;
FILE *dosya;

int main()

{
      
      dosya=fopen("yuksek puanlar.txt","w");
      struct oyuncuicin oyuncu;
      //oyuncu.isim[20]="Player";
      
      
      //install_sound(DIGI_AUTODETECT,MIDI_AUTODETECT,"A"); 
      //ses = load_sample("boing.wav"); 
      
      oyunu_yukle();
      tuglalar(tuglax,tuglay,tuglacan,oyuncu);
      
      while(!key[KEY_ENTER])
      {
            textout_ex(screen,font,"DX-BALL Oyununa Hos Geldiniz.",200,150,makecol(0,255,255),-1);
            textout_ex(screen,font,"Oyunda cubugu sag ve sol yon tuslariyla hareket ettirebilirsiniz.",70,180,makecol(255,0,255),-1);
            textout_ex(screen,font,"Oyuncu Adi: Player",240,210,makecol(255,0,0),-1);
            textprintf_ex(screen,font,150,270,makecol(255,255,0),-1,"Oyuna baslamak icin ENTER 'e basiniz.");    
                      
      }
      
      
      while(!key[KEY_ESC])
      {
      
           draw_sprite( screen, buffer, 0, 0);                    
           top_gider();
           cubuk_gider();
           top_tuglaya_carpar(tuglax,tuglay,tuglacan,oyuncu);
           textprintf_ex(screen,font,550,20,makecol(0,255,255),-1,"PUAN: %d",puan);
           if(topy==500) break;
      }
      while(!key[KEY_ESC])
      {
           textprintf_ex(screen,font,200,280,makecol(128,128,0),-1,"OYUN BITTI. PUAN: %d",puan);
           textprintf_ex(screen,font,180,320,makecol(128,128,0),-1,"CIKMAK ICIN ESC TUSUNA BASINIZ...");
      }
      oyuncu.puan=puan;
      fprintf(dosya,"%s puan: %d",oyuncu.isim,oyuncu.puan); //dosyaya yazýyoruz
}
END_OF_MAIN();

void oyunu_yukle(void)
{
      allegro_init();
      install_keyboard();//kalvyeyi aktif ediliyor
      set_color_depth(16);
      set_gfx_mode(GFX_AUTODETECT,640,480,0,0);
      buffer=create_bitmap(640,480);
      acquire_screen();
      release_screen();
}

void top_gider()
{
     etopx=topx;
     etopy=topy;
     
     
     
     if((topy+5!=cubuky || topx>cubukx+cubukuz || topx<cubukx) && (topx>5 && topx<635 && topy>5))
     {
          
           if(yon==1) { --topx; --topy; }
           else if(yon==2) { --topx; ++topy; }
           else if(yon==3) { ++topx; --topy; }
           else if(yon==4) { ++topx; ++topy; }        
           
     }
     else 
     {
          
          if(yon==1 && topx==5) { yon=3; topx++; }
          else if(yon==1 && topy==5) { yon=2; topy++; }
          else if(yon==2 && topx==5) { yon=4; topx++; }
          else if(yon==2 && topy+5==cubuky && topx<=cubukx+cubukuz && topx>=cubukx) { yon=1; topy--; } //top cubuktan seker
          else if(yon==3 && topx==635) { yon=1; topx--; }
          else if(yon==3 && topy==5) { yon=4; topy++; }
          else if(yon==4 && topx==635) { yon=2; topx--; }
          else if(yon==4 && topy+5==cubuky && topx<=cubukx+cubukuz && topx>=cubukx) { yon=3; topy--; } //top cubuktan seker
     }
          
     circlefill(buffer, etopx, etopy, 5, makecol( 0, 0, 0));   //topun bir önceki konumu zeminin rengine getiriliyor.
     circlefill(buffer, topx, topy, 5, makecol( 255,255,0));   //   topun rengi sarý
     rest(5);     
}
//////////////////////////////////   ////////////  ///////////////////////       ///////////   
void cubuk_gider(void)
{
     
     ecubukx=cubukx;
     ecubuky=cubuky;
     
     if(cubukx>0 && cubukx<540)
     {
                 if(key[KEY_RIGHT]) cubukx+=5;
                 if(key[KEY_LEFT]) cubukx-=5;
     }
                                                                                     
     else {
          if(cubukx<=0) cubukx++;           //cubuðun ekran dýþýna
          if(cubukx>=540) cubukx--;         //çýkmasýný engellemek için
          }
          //rest(3);
     
    
    rectfill( buffer, ecubukx, ecubuky, ecubukx+cubukuz, ecubuky+10, makecol ( 0, 0, 0));
    rectfill( buffer, cubukx, cubuky, cubukx+cubukuz, cubuky+10, makecol (130, 128, 255));    
}


void tuglalar(int tuglax[49], int tuglay[49], int tuglacan[49], struct oyuncuicin oyuncu)
{
     for(y=100;y<220;y+=30)
     {
          for(x=80;x<560;x+=40)
          {
               if(y==100) rectfill(buffer,x,y,x+35,y+25,makecol(255,0,0));      //kýrmýzý (3)
               if(y==130) rectfill(buffer,x,y,x+35,y+25,makecol(0,0,255));      //yesil (2)
               if(y==160) rectfill(buffer,x,y,x+35,y+25,makecol(0,255,0));      //mavi (1) 
               if(y==190) rectfill(buffer,x,y,x+35,y+25,makecol(0,0,255));      //yesil (2)                                  
          }                            
     }

     k=0;
     for(y=100;y<220;y+=30)            //bu döngü toplam 48 kere dönüyor.
     {                                 //yani her tuðlaya özelliklerini
          for(x=80;x<560;x+=40)        //burada yüklüyorum.
          {        
               k++;            
               tuglax[k]=x;
               tuglay[k]=y;
               
               if(y==100) tuglacan[k]=3;           //üst satýrý kýrmýzý yaptým.                             
               else if(y==130) tuglacan[k]=1;      //2. satýr yeþil
               else if(y==160) tuglacan[k]=2;      //3. satýr mavi
               else if(y==190) tuglacan[k]=1;      //alt satýr tekrar yeþil
          }
     }
}

void top_tuglaya_carpar(int tuglax[49], int tuglay[49], int tuglacan[49],struct oyuncuicin oyuncu)
{
    
    for(k=1;k<49;k++)
    {         
        if(tuglacan[k]>0)
        { 
             if(tuglax[k]==topx+5 || tuglax[k]+40==topx-5 || tuglay[k]==topy+5 || tuglay[k]+30==topy-5)
             {
                  if((tuglax[k]<=topx && tuglax[k]+40>=topx) || (tuglay[k]<=topy && tuglay[k]+30>=topy))
                  {
                       if(tuglacan[k]==3) //tuðla kýrmýzý ise
                       {
                          rectfill(buffer,tuglax[k],tuglay[k],tuglax[k]+35,tuglay[k]+25,makecol(0,255,0));//yeþil(2)
                          puan+=300;
                       }
                       
                       else if(tuglacan[k]==2) //tuðla yeþil ise
                       {
                          rectfill(buffer,tuglax[k],tuglay[k],tuglax[k]+35,tuglay[k]+25,makecol(0,0,255));//mavi(1)
                          puan+=200;
                       }
                       
                       else if(tuglacan[k]==1) //tuðla mavi ise
                       {
                          rectfill(buffer,tuglax[k],tuglay[k],tuglax[k]+35,tuglay[k]+25,makecol(0,0,0));//siyah(boþluk)           
                          puan+=100;                                                          
                       }
                       
                       tuglacan[k]-=1;  //tuglanýn caný 1 azalýyor
                       
                       if(yon==1 && tuglay[k]+30==topy-5) yon=2;        //alt
                       else if(yon==1 && tuglax[k]+40==topx-5) yon=3;   //sað
                       else if(yon==2 && tuglay[k]==topy+5) yon=1;      //üst
                       else if(yon==2 && tuglax[k]+40==topx-5) yon=4;   //sað
                       else if(yon==3 && tuglay[k]+30==topy-5) yon=4;   //alt
                       else if(yon==3 && tuglax[k]==topx+5) yon=1;      //sol
                       else if(yon==4 && tuglay[k]==topy+5) yon=3;      //üst
                       else if(yon==4 && tuglax[k]==topx+5) yon=2;      //sol
                                                       
                  }
             }
        }
    }
    
}
/*

MEHMET BEKTAÞ	100201007
KUTAY AKYOL	    110201085
RECEP UCE	    110201083

*/
