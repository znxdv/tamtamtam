#include<conio.h>
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<windows.h>
#define RED   "\x1b[31m"
#define RESET "\x1b[0m"
#define GREEN "\x1b[32m"

struct tamagochi{
    int makan;
    int kesenangan;
    int tidur;
    int level;
};
char username[100], password[100];
void intro(); void new_acc(char *username);
FILE *fp;
void gotoxy (int x, int y){
    COORD coord = {0, 0};
    coord.X = x; coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void gameplay(char username[]){ 
    system("cls");
    fp=fopen(username,"a");
    if(fp==NULL){
        perror("Error");
    }
    fseek(fp, 0, SEEK_END);
    if(ftell(fp)== 0){
        new_acc(username);
    }
    while(1){ system("cls");
        char strip[100];
        memset(strip, '_', 40);
        gotoxy(7,2);
        printf("%s", strip);
        

    }

}
void new_acc(char username[]){ 
    system("cls");
    char nama_pet[10];
    int c, x=46; 
    gotoxy(13,2);
    printf("Selamat datang di Tamagothci World"); 
    gotoxy(13,4);
    printf("Karena creator nya mager dan masih cupu"); 
    gotoxy(13,5);
    printf("Kalian ngga bisa milih character yaa..");
    gotoxy(13,6);
    printf("Jadi pake character ini aja, hehe\n"); 
    gotoxy(30,8);
    printf("=^..^="); 
    gotoxy(13,10);
    printf("Kucing ini namanya Tom, kalian bisa ngasi nama baru kok");
    gotoxy(13,12);
    printf("Kasi nama baru buat character baru kamu : ");
    scanf("%[^\n]", nama_pet); while(getchar()!='\n'); 
    gotoxy(13,12);
    if(strlen(nama_pet)>8){ 
        gotoxy(13,14);
        printf("Nama character barunya kepanjangan, maksimal cuma 8 character. "); 
        getch();
        new_acc(username);
    } 
    gotoxy(13,14);
    printf("Apakah kamu yakin '%s' adalah nama character baru kamu?", nama_pet); 
    while(1){
        gotoxy(x,17);
        gotoxy(x,17);
        gotoxy(34,16);
        printf(GREEN"Yap"RESET); gotoxy(44,16);
        printf(RED"Tidak"RESET); 
        gotoxy(x,17);
        putchar('^');
        c=getch();
        if(x==46){ 
            if(c==77){
                Beep(2000,5);
                printf("\b \b");
                x-=11; 
                continue;
            }
            else if(c==75){ 
                Beep(2000,5);
                printf("\b \b");
                x-=11; 
                continue;
            }
        }
        if(x==35){
            if(c==77){
                Beep(2000,5); 
                printf("\b \b");
                x+=11; 
                continue;
            }
            else if(c==75){ 
                Beep(2000,5);
                printf("\b \b");
                x+=11; 
                continue;
            }
        }
        if(c==27){
            gotoxy(0,15);
            puts("\n\n\n");
        }
        else if(c==13){
            if(x==46) new_acc(username);
            if(x==35){
                if(fp==NULL){
                    perror("Error");
                }
                fp=fopen(username, "w");
                fprintf(fp,"Nama pet : %s\n",nama_pet); 
                gotoxy(13,18);
                printf("Nama character kamu sudah tersimpan! "); 
                gotoxy(13,18); 
                getch();
                fclose(fp);
                gameplay(username);
            }
        }
    }
}
int check_pass(char *pass){
    fp = fopen("accounts.txt", "r");
    int check=0;
    char line[200];
    while (fgets(line, 200, fp) != NULL){
        char currentPass[100];
        sscanf(line,"%s", currentPass);
        if(strcmp(pass, currentPass)==0){
            check = 1;
            break;
        }
    }
    fclose(fp);
    return check;
}
int check_id(char *id){
    fp = fopen("accounts.txt", "r");
    int check=0;
    char line[200];
    while (fgets(line, 200, fp) != NULL){
        char currentId[100];
        sscanf(line,"%s", currentId);
        if(strcmp(id, currentId)==0){
            check = 1;
            break;
        }
    }
    fclose(fp);
    return check;
}
void login(){ 
    system("cls");
    while(1){ 
        system("cls");
        gotoxy(7,3);
        printf("Masukkan username : ");
        scanf("%s", username);
        if(check_id(username)==0){
            gotoxy(7,5);
            printf(RED"Username tidak terdaftar ! "RESET);
            gotoxy(7,7);
            printf("Tekan ESC kalo mau kembali ke menu utama. ");
            if(getch()==27) break;
            continue;
        }
        gotoxy(7,5);
        printf("Masukkan password : ");
        scanf("%s", password); 
        while(getchar()!='\n');
        if(check_pass(password)==0){
            gotoxy(7,7);
            printf(RED"Password salah ! "RESET);
            gotoxy(7,9);
            printf("Tekan ESC kalo mau kembali ke menu utama. "); 
            if(getch()==27) break;
            continue;
        }
        gotoxy(7,7);
        printf(GREEN"Login berhasil. . . "RESET); 
        getch();
        gameplay(username);
    }
    intro();
}
void regist(){ 
    system("cls");
    while(1){ 
        system("cls");
        char username[100], password[100], currentUsername[100], currentPassword[100];
        bool check_username = false;
        gotoxy(8,3);
        printf("Silahkan daftarkan username : ");
        scanf("%[^\n]", username); while(getchar()!='\n');
        if(strchr(username, ' ')!=0){
            gotoxy(8,5);
            printf(RED"\nUsername nya ngga boleh pake spasi."RESET);
            gotoxy(8,7); 
            printf("Tekan ESC kalo mau balik kemenu utama.");
            if(getch()==27); break; continue;
        }
        else if(strlen(username)<7){
            gotoxy(8,5);
            printf(RED"\nUsername nya minimal 6 character. "RESET);
            gotoxy(8,7); 
            printf("Tekan ESC kalo mau balik ke menu utama. ");
            if(getch()==27); break; continue;
        }
        fp=fopen("accounts.txt", "r");
        char line[200];
        while (fgets(line, 200, fp) != NULL){
            sscanf(line,"%s", currentUsername);
            if(!strcmp(username, currentUsername)){
                check_username = true;
                break;
            }
        }
        fclose(fp);
        if(check_username){
            Sleep(2000);
            gotoxy(8,5); 
            gotoxy(8,5); 
            printf(RED"\nUsername nya udah ada yang make, coba username yang lain. "RESET);
            gotoxy(8,7); 
            printf("Tekan ESC untuk kembali ke menu utama. ");
            if(getch()==27); break; continue;
        }
        gotoxy(8,5);
        printf("Daftarkan password : ");
        scanf("%s", password);
        fp = fopen("accounts.txt", "a");
        fprintf(fp, "%s %s", username, password);
        fclose(fp);
        Sleep(2000);
        gotoxy(8,5);
        printf(GREEN"\nAkun mu sudah terdaftar. "RESET); 
        getch();
        break;
    }
    intro();
}
void intro(){ system("cls");
    int c, y = 7;
    while(1){
        gotoxy(63,y); 
        gotoxy(63,y); 
        gotoxy(16,3);
        puts("<<<Selamat datang di Tamagochi Virtual Pet>>>"); gotoxy(16,5);
        puts("---------------------------------------------"); gotoxy(16,6);
        puts("Apakah kamu sudah punya akun sebelumnya ?  ");   gotoxy(16,7);
        puts("[1] Sudah");                                     gotoxy(16,8);
        puts("[2] Belum");                                     gotoxy(16,9);
        puts("---------------------------------------------"); 
        printf("\n\n\n\t\tTekan ESC untuk keluar dari game.");           
        gotoxy(62,y);
        putchar('<');
        c = getch();
        if(y==7){ 
            if(c==0x48){
                Beep(1000,100);
                printf("\b \b");
                y++; 
                continue;
            }
            else if(c==0x50){ 
                Beep(1000,100);
                printf("\b \b");
                y++; 
                continue;
            }
        }
        if(y==8){
            if(c==0x48){
                Beep(1000,100); 
                printf("\b \b");
                y--; 
                continue;
            }
            else if(c==0x50){ 
                Beep(1000,100);
                printf("\b \b");
                y--; 
                continue;
            }
        }
        if(c==27){
            gotoxy(0,15);
            puts("\n\n\n");
            return;
        }
        else if(c==13) break;
    }
    if(y==7) login();
    if(y==8) regist();
}
void passw(){ 
    system("cls");
    int max_pass_lenght =10, pass_post=0;
    char ch, password[7], ans[7] ={"tamtam"};
    gotoxy(6,3);
	  puts("\t  _____                       _       _   _    _            _         ");
    puts("\t |_   _| __ _____  __ ___ ___| |_ ___| |_|_|  | |_ _ _    _| |___ _ _ ");
    puts("\t   | |  |. |     ||. | . | . |  _| ._| . | |  | . | | |  | . | -_| | |");
    puts("\t   |_| |___|_|_|_|___|_  |___| | |___|_|_|_|  |___|_  |  |___|___| _/ ");
    puts("\t                      |__|   |__|                 |___|               ");
    gotoxy(17,11);
    printf("Silahkan masukkan password untuk masuk kedalam game ");
    gotoxy(39,14);
    while(1){
        ch = getch();
        if(ch==13){
            break;
        }
        else if(ch==8){
            if(pass_post>0){    
                pass_post--;
                password[pass_post]='\0';
                printf("\b \b");
            }
        }
        else if(ch == 32&& ch==9){
            continue;
        }
        else if(ch>47&&ch<127){
            if(pass_post<max_pass_lenght){
                password[pass_post]=ch;
                pass_post++;
                printf("*");
            }
        }
    }
    password[pass_post]='\0';
    if(strcmp(password,ans)==0){                    
        gotoxy(37,14);
        printf(GREEN"Password benar");                          
        gotoxy(30,15); 
        Beep(2000,125);
        Beep(1000,125);
        printf("Silahkan masuk ke dalam game! "RESET);
        gotoxy(0,0); 
        getch();
        intro();
    }
    else{                                           
        gotoxy(35,14); 
        Beep(300,300); 
        Beep(300,300); 
        Beep(300,300);
        printf(RED"Password salah!"RESET);
        gotoxy(0,0); 
        getch(); 
        passw();
    }
}
int main(){
    passw();
}
