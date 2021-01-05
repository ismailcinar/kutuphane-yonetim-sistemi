#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<dos.h>
#include<time.h>
#include<locale.h>
#define RETURNTIME 15



void kitapEkle();
void kitapSil();
void kitapDuzenle();
void kitapAra();
void kitapVer();
void kitapGor();
void donusFonk();
void anaMenu();
void uygKapat();
int  veriAl();
char kategoriler[][15]={"Tarih","Psikoloji","Bilim Kurgu","Fantastik","Polisiye","Sağlık"};
int  noKontrol(int);
int t(void);
void verdiKaydi();
int gun();
int yil();
int ay();

FILE *fp,*ft,*fs;


int s;
char findbook;


struct meroDate
{
    int mm,dd,yy;
};
struct kitaplar
{
    int numara;
    char ogrenciismi[35];
    char kitapismi[35];
    char yazar[35];
    int adet;
    float ucret;
    int count;
    int kitaplikno;
    char *cat;
    struct meroDate duedate;
};
struct kitaplar a;

int main()
{
    
    setlocale(LC_ALL, "Turkish");
    anaMenu();
    getch();
    return 0;
}
void anaMenu()
{
    system("cls");
    int i;
    printf("\n\n\t\t**************************** ANA MENÜ ****************************");
    printf("\n\n\t\t*********> 1. Yeni Kitap Ekle");
    printf("\n\n\t\t*********> 2. Kitap Bilgilerini Düzenle");
    printf("\n\n\t\t*********> 3. Kitap Ara");
    printf("\n\n\t\t*********> 4. Kitap Ödünç Verme Menüsü");
    printf("\n\n\t\t*********> 5. Kitap listesini görüntüle");
    printf("\n\n\t\t*********> 6. Eklenmi˛ bir kitabın kaydını düzenle");
    printf("\n\n\t\t********** 7. Uygulamayı kapat");
    printf("\n\n\t\t******************************************************************************");
    t();
    printf("\n\n\n\t\tSeçiminizi Giriniz:");
    switch(getch())
    {
    case '1':
        kitapEkle();
        break;
    case '2':
        kitapSil();
        break;
    case '3':
        kitapAra();
        break;
    case '4':
        kitapVer();
        break;
    case '5':
        kitapGor();
        break;
    case '6':
        kitapDuzenle();
        break;
    case '7':
    {
        system("cls");
        printf("\tKütüphane Yönetim Sistemi\n\n");
        printf("\t2019-2020 Guz\n\n");
        printf("\tAhmet Buğra Yiğiter\n\tİsmail Çınar\n\tAbdurrahman Yorulmaz\n");
        printf("\t******************************************\n");
        printf("\t*******************************************\n");
        printf("\t*******************************************\n");
        printf("\t********************************************\n");
        printf("\tProgram 3 saniye icinde kapanacak...........>\n");
        Sleep(3000);
        exit(0);
    }
    default:
    {
        printf("\aYanlış Giriş!!Lütfen Doğru Giriş Yapınız!\n");
        if(getch())
            anaMenu();
    }
    
    }
    }
    void kitapEkle()
    {
        system("cls");
        int i;
        printf("\n\n\t\t******************************* KATEGORİLER *********************************");
        printf("\n\n\t\t********** 1. Tarih");
        printf("\n\n\t\t********** 2. Psikoloji");
        printf("\n\n\t\t********** 3. Bilim Kurgu");
        printf("\n\n\t\t********** 4. Fantastik");
        printf("\n\n\t\t********** 5. Polisiye");
        printf("\n\n\t\t********** 6. Saglık");
        printf("\n\n\t\t******************************************************************************");
        printf("\n\n\t\t********** 7. Ana menüye dön¸˛");
        printf("\n\n\t\tSeçiminizi giriniz:");
        scanf("%d",&s);
        if(s==7)
            anaMenu() ;
        system("cls");
        fp=fopen("Bibek.dat","ab+");
        if(veriAl()==1)
        {
            a.cat=kategoriler[s-1];
            fseek(fp,0,SEEK_END);
            fwrite(&a,sizeof(a),1,fp);
            fclose(fp);
            printf("\nKayit basariyla kaydedildi\n");
            printf("\nBaska kaydetmek ister misiniz?(E / H):\n");
            if(getch()=='h')
                anaMenu();
            else
                system("cls");
            kitapEkle();
        }
    }
    void kitapSil()
    {
        system("cls");
        int d;
        char another='e';
        while(another=='e')
        {
            system("cls");
            printf("Silmek istedi�iniz kita�n ID'sini giriniz:\n");
            scanf("%d",&d);
            fp=fopen("Bibek.dat","rb+");
            rewind(fp);
        while(fread(&a,sizeof(a),1,fp)==1)
        {
            if(a.numara==d)
            {
                printf("Kitap kaydi mevcuttur\n");
                printf("Kitap ismi %s\n",a.kitapismi);
                printf("Kitaplik Numarasi %d\n",a.kitaplikno);
                findbook='t';
            }
        }
        if(findbook!='t')
        {
            printf("Hicbir kayit bulunamadi aramayi de�i�tir\n");
            printf("Ana Men�ye dönmek için bir tu�a bas�n�z..");
            if(getch())
            
                anaMenu();
        }
        if(findbook=='t' )
        {
            printf("Silmek ister misiniz?(E/H):\n");
            if(getch()=='e')
            {
                ft=fopen("test.dat","wb+");
                rewind(fp);
                while(fread(&a,sizeof(a),1,fp)==1)
                {
                    if(a.numara!=d)
                    {
                        fseek(ft,0,SEEK_CUR);
                        fwrite(&a,sizeof(a),1,ft);
                    }
                }
                fclose(ft);
                fclose(fp);
                
                if(findbook=='t')
                {
                    printf("Kayit basariyla silinmistir\n");
                    printf("Baska kayit silmek ister misiniz?(E/H)\n");
                }
                remove("Bibek.dat");
                rename("test.dat","Bibek.dat");
                fp=fopen("test.dat","rb+");
            }
            else
                anaMenu();
            fflush(stdin);
            another=getch();
        }
    }
    anaMenu();
    }
    void kitapAra()
    {
        system("cls");
        int d;
        printf("*****************************Kitap Arama*********************************\n");
        printf("******** 1. Kitap kimli�ii ile arama\n");
        printf("******** 2. Adiyla ara\n");
        printf("******** 3. Ana menüye dön\n");
        printf("Seçiminizi giriniz\n");
        fp=fopen("Bibek.dat","rb+");
        rewind(fp);
        switch(getch())
        {
            case '1':
            {
                system("cls");
                printf("**** Kay�t numaras� ile ara ****\n");
                printf("Kayıt numarasını giriniz:\n");
                scanf("%d",&d);
                printf("Aran�yor........\n");
                while(fread(&a,sizeof(a),1,fp)==1)
                {
                    if(a.numara==d)
                    {
                        Sleep(2);
                        printf("Kitap mevcuttur\n");
                        printf("********************************************************\n");
                        printf("** Kayıt numarası : %d\n",a.numara);
                        printf("**\n");
                        printf("** Kitap ismi : %s\n",a.kitapismi);
                        printf("**\n");
                        printf("** Yazar : %s \n",a.yazar);
                        printf("**\n");
                        printf("** Adet : %d \n",a.adet);
                        printf("**\n");
                        printf("**\n");
                        printf("** Fiyat : Rs.%.2f\n",a.ucret);
                        printf("**\n");
                        printf("** Kitaplık numarası :%d \n",a.kitaplikno);
                        printf("**\n");
                        printf("********************************************************\n");
                        findbook='t';
                    }
    
                }
                if(findbook!='t')
                {
                    printf("\n**************************************");
                    printf("\n**");
                    printf("\n**");
                    printf("\n**************************************");
                    printf("\n\aKayıt bulunamad˝");
                }
                printf("\nBaşka bir arama yapmak ister misiniz ?(E/H)");
                if(getch()=='e' || getch()=='E')
                    kitapAra();
                else if(getch()=='h' || getch()=='H')
                    anaMenu();
                else
                printf("Hatalı giri˛ yaptınız.\n");
                break;
            }
            case '2':
            {
                char s[15];
                system("cls");
                printf("**** Kitap adi ile arama ****");
                printf("\nKitabin adini giriniz:");
                scanf("%s",s);
                int d=0;
                while(fread(&a,sizeof(a),1,fp)==1)
                {
                    if(strcmp(a.kitapismi,(s))==0)
                    {
                        printf("Kitap mevcuttur\n");
                        printf("********************************************************\n");
                        printf("** Kayit numarasi : %d\n",a.numara);
                        printf("**\n");
                        printf("** Kitap ismi : %s\n",a.kitapismi);
                        printf("**\n");
                        printf("** Yazar : %s \n",a.yazar);
                        printf("**\n");
                        printf("** Adet : %d \n",a.adet);
                        printf("**\n");
                        printf("**\n");
                        printf("** Fiyat : Rs.%.2f\n",a.ucret);
                        printf("**\n");
                        printf("** Kitaplık numarasi : %d\n",a.kitaplikno);
                        printf("**\n");
                        printf("********************************************************\n");
                        d++;
                    }
                }
                if(d==0)
                {
                    printf("**************************************\n");
                    printf("**\n");
                    printf("**");
                    printf("**************************************\n");
                    printf("\aKayit bulunamadi\n");
                }
                printf("Baska bir arama yapmayi dener misiniz?(E/H)\n");
                if(getch()=='e')
                    kitapAra();
                else
                    anaMenu();
                break;
            }
            case '3': {
                anaMenu() ;
                break;
            }
            default :
                getch();
            anaMenu();
        }
    fclose(fp);
    }
    void kitapVer()
    {
        int t;
        system("cls");
        printf("*************************** KİTAP ÖDÜNÇ VERME MENÜSÜ *********************");
        printf("\n********** 1. Kitap Ödünçver");
        printf("\n********** 2. Alınmış kitapları görüntüle");
        printf("\n********** 3. Ödünç verilen kitabı sorgula");
        printf("\n********** 4. Ödün. verilen kitabı geri al");
        printf("\n********** 5. Ana menüye dön¸˛");
        printf("\nSeçiminizi giriniz:");
        switch(getch())
        {
            case '1':
            {
                system("cls");
                int c=0;
                char another='e';
                while(another=='e')
                {
                    system("cls");
                    printf("***Ödunc kitap bolumu***");
                    printf("\n\tKitap kimligini giriniz:");
                    scanf("%d",&t);
                    fp=fopen("Bibek.dat","rb");
                    fs=fopen("Issue.dat","ab+");
                    if(noKontrol(t)==0)
                    {
                        printf("\n\nKitap kaydı mevcuttur");
                        printf("\n\nKutuphanede bu kitaptan %d adet mevcut ",a.adet);
                        printf("\n\nKitabın adı : %s",a.kitapismi);
                        printf("\n\n÷Öğrenci adını giriniz:");
                        scanf("%s",a.ogrenciismi);
                        
                        printf("\n\nÖdünç alma tarihi: %d-%d-%d",gun(),ay(),yil());
                        printf("\n%d Numaralı kitap ödünç verilmi˛tir.",a.numara);
                        a.duedate.dd=gun()+RETURNTIME;
                        a.duedate.mm=ay();
                        a.duedate.yy=yil();
                        if(a.duedate.dd>30)
                        {
                            a.duedate.mm+=a.duedate.dd/30;
                            a.duedate.dd-=30;
                        }
                        if(a.duedate.mm>12)
                        {
                            a.duedate.yy+=a.duedate.mm/12;
                            a.duedate.mm-=12;
                        }
                        
                        printf("\nGeri alinacak tarih:%d-%d-%d",a.duedate.dd,a.duedate.mm,a.duedate.yy);
                        fseek(fs,sizeof(a),SEEK_END);
                        fwrite(&a,sizeof(a),1,fs);
                        fclose(fs);
                        c=1;
                    }
                    if(c==0)
                    {
                        printf("Kayit bulunamadi\n");
                    }
                    printf("Başka kitap ister misiniz(E/H):\n");
                    fflush(stdin);
                    another=getche();
                    fclose(fp);
                }
    
                break;
            }
            case '2':
            {
                system("cls");
                int j=4;
                printf("*******************************Odunc Kitap Listesi*******************************\n");
                printf("OGRENCI ADI\t\t\tKATEGORI\t\t\tKITAP NUMARASI\t\t\tKITAP ADI\t\tODUN« ALINMA TARIHI\t\tGERI DONUS TARIHI\n");
                fs=fopen("Issue.dat","rb");
                while(fread(&a,sizeof(a),1,fs)==1)
                {
                    printf("%-20s\t\t",a.ogrenciismi);
                    printf("%-20s\t\t\t",a.cat);
                    printf("%-20d\t",a.numara);
                    printf("%-20s\t",a.kitapismi);
                    printf("%d-%d-%d\t\t\t\t",gun(),ay(),yil());
                    printf("%d-%d-%d\t\t\t\n",a.duedate.dd,a.duedate.mm,a.duedate.yy);
                    j++;
                }
                fclose(fs);
                donusFonk();
            }
                break;
            case '3':
            {
                system("cls");
                printf("\nKitap kayit numarasini giriniz:");
                int p,c=0;
                char another='e';
                while(another=='e')
                {
                    scanf("%d",&p);
                    fs=fopen("Issue.dat","rb");
                    while(fread(&a,sizeof(a),1,fs)==1)
                    {
                        if(a.numara==p)
                        {
                            verdiKaydi();
                            printf("\nHerhangi bir sey giriniz.......");
                            getch();
                            verdiKaydi();
                            c=1;
                        }
                    }
                    fflush(stdin);
                    fclose(fs);
                    if(c==0)
                    {
                        printf("\nKayit bulunamadi");
                    }
                    printf("\nBaşka Arama Yapacak mısın?(E/H)");
                    another=getch();
                }
            }
                break;
            case '4':
            {
                system("cls");
                int b;
                FILE *fg;
                char another='e';
                while(another=='e')
                {
                    printf("\nGeri alınacak kitabın id'sini giriniz:\n");
                    scanf("%d",&b);
                    fs=fopen("Issue.dat","rb+");
                    while(fread(&a,sizeof(a),1,fs)==1)
                    {
                        if(a.numara==b)
                        {
                            verdiKaydi();
                            findbook='t';
                        }
                        if(findbook =='t')
                        {
                            printf("\nKaldirmak ister misiniz?(E/H): ");
                            if(getch()=='e')
                            {
                                fg=fopen("record.dat","wb+");
                                rewind(fs);
                                while(fread(&a,sizeof(a),1,fs)==1)
                                {
                                    if(a.numara!=b)
                                    {
                                        fseek(fs,0,SEEK_CUR);
                                        fwrite(&a,sizeof(a),1,fg);
                                    }
                                }
                                fclose(fs);
                                fclose(fg);
                                remove("Issue.dat");
                                rename("record.dat","Issue.dat");
                                printf("\nOdunc alinan kitap listeden kaldirildi\n");
                            }
                        }
                        if(findbook!='t')
                        {
                            printf("\nKayıt bulunamadı");
                            break;
                        }
                    }
                    printf("\nBaska silmek ister misiniz?(E/H) : ");
                    another=getch();
                }
                
            }
            case '5': {
                anaMenu() ;
                break;
            }
            default:
                printf("\nBir Onceki Menuye Dönmek için Herhangi Bir Tuşa Basınız...");
            getch();
            kitapVer();
            break;
        }
        donusFonk();
    }
    void kitapGor()
    {
        int i=0,j;
        system("cls");
        printf("******************************************************Kitap Listesi************************************************************");
        printf("\n\nKategori\t\tKimlik\t\tKitap Adi\t\tYAZAR\t\tAdet\t\tFiyat\t\tKitaplik Numarasi\n");
        j=4;
        fp=fopen("Bibek.dat","rb");
        while(fread(&a,sizeof(a),1,fp)==1)
        {
            
            printf("%s\t\t\t",a.cat);
            printf("%d\t\t",a.numara);
            printf("%s\t\t\t",a.kitapismi);
            printf("%s\t\t",a.yazar);
            printf("%d\t\t",a.adet);
            printf("%.2f\t\t",a.ucret);
            printf("%d\t\t",a.kitaplikno);
            printf("\n\n");
            j++;
            i=i+a.adet;
        }
        printf("Tum Kitaplar =%d",i);
        fclose(fp);
        donusFonk();
    }
    void kitapDuzenle()
    {
        system("cls");
        int c=0;
        int d,e;
        printf("\n\n\t\t*********************** Eklenmiş Bir Kitabin Kaydını Duzenle ***********************");
        char another='y';
        while(another=='y')
        {
            system("cls");
            printf("\nDüzenlemek istediğiniz kitabin Numarasini giriniz :");
            scanf("%d",&d);
            fp=fopen("Bibek.dat","rb+");
            while(fread(&a,sizeof(a),1,fp)==1)
            {
                if(noKontrol(d)==0)
                {
                    printf("\nKitap mevcuttur");
                    printf("\nKitap kayit numarasi:%d",a.numara);
                    printf("\nYeni isim giriniz:");scanf("%s",a.kitapismi);
                    printf("\nYeni yazar giriniz:");scanf("%s",a.yazar);
                    printf("\nYeni adet giriniz:");scanf("%d",&a.adet);
                    printf("\nYeni fiyat giriniz:");scanf("%f",&a.ucret);
                    printf("\nYeni kitaplik numarasi giriniz:");scanf("%d",&a.kitaplikno);
                    printf("\n Kitabinizin kayd˝ ba˛ar˝yla d¸zenlenmi˛tir.");
                    fseek(fp,ftell(fp)-sizeof(a),0);
                    fwrite(&a,sizeof(a),1,fp);
                    fclose(fp);
                    c=1;
                }
                if(c==0)
                {
                    printf("\nKayit bulunamadi");
                }
            }
            printf("\nBaşka bir kitabi düzenlemek ister misiniz? (E/H)");
            fflush(stdin);
            another=getch();
        }
        donusFonk();
    }
    void donusFonk()
    {
        {
        printf("\n\nAna menüye dönmek için ENTER tuşuna basiniz.");
        }
    a:
        if(getch()==13)
            anaMenu();
        else
            goto a;
    }
    int veriAl()
    {
        int t;
        printf(">>Lütfen aşağıdaki bilgileri doldurunuz.\n");
        printf("****************************************************\n");
        printf("***İKİ KELİME ARASINDA SPACE (BOŞLUK) BIRAKMAYINIZ!");
        printf("\n***ALT ÇİZGİ (_) KULLANINIZ !");
        printf("\n\n\nKategori:\t");
        printf("%s",kategoriler[s-1]);
        printf("\n\nBook ID:\t");
        scanf("%d",&t);
        if(noKontrol(t) == 0)
        {
            printf("\n\aKitap kimliği zaten var.\a");
            getch();
            anaMenu();
            return 0;
        }
        a.numara=t;
        printf("\nKitap Adı : ");
        scanf("%s",a.kitapismi);
        printf("\nYazar : ");
        scanf("%s",a.yazar);
        printf("\nAdet : ");
        scanf("%d",&a.adet);
        printf("\nFiyat : ");
        scanf("%f",&a.ucret);
        printf("\nKitaplık numarası : ");
        scanf("%d",&a.kitaplikno);
        return 1;
    }
    int noKontrol(int t)
    {
        rewind(fp);
        while(fread(&a,sizeof(a),1,fp)==1)
        if(a.numara==t)
        return 0;
        return 1;
    }
    int t()
    {
        time_t t;
        time(&t);
        printf("\n\n\t\tAnlık Tarih ve Zaman:\t%s\n",ctime(&t));
        return 0 ;
    }
    void verdiKaydi()
    {
        system("cls");
        printf("Kitap Sayın %s tarafından Ödünç alınmıştır.",a.ogrenciismi);
        printf("Kitabın ödünç veriliş tarihi: %d-%d-%d",gun(),ay(),yil);
        printf("Kitabın geri getirilmesi gereken tarih: %d-%d-%d",a.duedate.dd,a.duedate.mm,a.duedate.yy);
    }
    int gun()
    {
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
  
        return tm.tm_mday;
    }
    int yil()
    {
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
  
        return tm.tm_year + 1900;
    }
    int ay()
    {
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
  
        return tm.tm_mon + 1;
    }



