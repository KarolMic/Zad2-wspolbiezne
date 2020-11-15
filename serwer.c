#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define ROZMIAR_BUFORA 512
#define TRUE 1

// ODEBRANIE WIADOMOŚCI OD KLIENTA
void getMessage()
{
   int dane = 0;
   char bufor[ROZMIAR_BUFORA];
   memset(&bufor[0], 0, sizeof(bufor));

   while((dane = open("dane.txt", O_RDWR)) < 0) {}

   if(dane != 0)
   {
     while(read(dane,bufor,ROZMIAR_BUFORA) < 1) {}
     printf("\nKLIENT WYSŁAŁ WIADOMOŚĆ:\n%s", bufor);
     // close(dane);
     printf("\n");
   }
}

// WYSYŁANIE WIADOMOŚCI ZWROTNEJ DO KLIENTA
void sendMessage()
{
	int wyniki;
	char bufor[ROZMIAR_BUFORA];
  memset(&bufor[0], 0, sizeof(bufor));
	char znak[1];
	int licznik = 0;


	FILE *fp = fopen("wyniki.txt", "ab+");
	fseek(fp, 0, SEEK_END); // goto end of file

	if (ftell(fp) == 0)
	{
				printf("WIADOMOŚĆ ZWROTNA DLA KLIENTA:\n");
		while(TRUE)
		{
			char str[100];
			scanf("%s", str);
			printf("%s", str);
			read(0,znak,1);

			if(znak[0] == (char)27)
			{
				fputs(str, fp);
				fclose(fp);
				break;
			}
			bufor[licznik] = znak[0];
			licznik++;
		}
	}
	fseek(fp, 0, SEEK_SET); // goto begin of file

}

// OCZYSZCZANIE BUFORÓW
void disconnect()
{
		unlink("bin/lockfile");
		unlink("dane.txt");
}

// NAGŁÓWEK DLA SERWERA
void header()
{
  printf("\n");
  printf("┌─┐┌─┐┬─┐┬ ┬┌─┐┬─┐\n");
  printf("└─┐├┤ ├┬┘│││├┤ ├┬┘\n");
  printf("└─┘└─┘┴└─└┴┘└─┘┴└─\n");
  printf("Serwer uruchomiony, oczekuję na zgłoszenia...\n");
}

// FUNKCJA GŁÓWNA
int main()
{
  header();
	while(TRUE)
	{
		getMessage();
		sendMessage();
		disconnect();
    printf("\nSerwer oczekuje na kolejne zgłoszenie...");
		printf("\n\n");
	}
	return 0;
}
