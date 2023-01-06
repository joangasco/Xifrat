#include <stdio.h>
#include <stdlib.h>

#define MAX 80

void mostrar_menu()
{
    printf("\n\n -------------------------- XIFRAT --------------------------\n\n");
    printf("Aquest programa serveix per xifrar i desxifrar text, escull com vols utilitzar-lo:\n");
    printf("1- Encriptar un text que s'introdueix pel teclat\n");
    printf("2- Desencriptar un text que s'introdueix pel teclat\n");
    printf("3- Encriptar un text inclos en un arxiu de text\n");
    printf("4- Desencriptar un text inclos en un arxiu de text\n");
    printf("5- Tancar el programa\n");
    printf("Quina opcio vols?: ");
}

char passar_majuscules(char caracter)
{
    if (caracter > 96 && caracter < 123)
    {
        caracter = caracter - 32;
    }

    return caracter;
}

int xifrar_frase(char frase[MAX], char matriu_clau[7][7])
{
    int cnt_aux = 0, cnt_frase = 0;
    int i, j;
    char aux[MAX];
    char lletra, aux_lletra;

    //copiem la frase original a aux
    i = 0;

    while (frase[i] != '\n')
    {
        aux[i] = frase[i];
        i++;
    }

    aux[i] = '\0';


    //xifrem la frase
    while (aux[cnt_aux] != '\0')
    {
        lletra = passar_majuscules(aux[cnt_aux]);

        j = 0;
        i = 1;

        //busquem la lletra que volem xifrar a la matriu clau
        do {

            j++;
            if (j > 6)
            {
                j = 1;
                i++;
            }

            aux_lletra = matriu_clau[i][j]; //serveix per saber en quina posicio de la matriu clau ens trobem

        } while (lletra != aux_lletra && matriu_clau[i][j] != '9');

        if (lletra != matriu_clau[i][j])
        {
            return 1;
        }

        //copiem el codi assignat a la lletra al vector frase
        frase[cnt_frase] = matriu_clau[i][0];
        cnt_frase++;
        frase[cnt_frase] = matriu_clau[0][j];
        cnt_frase++;

        cnt_aux++;
    }


    frase[cnt_frase] = '\0';
    return 0;
}

void desxifrar_frase(char frase[MAX])
{

}

void escriure_vector(char frase[MAX])
{
    int i;

    i = 0;

    while (frase[i] != '\0')
    {
        printf("%c",frase[i]);
        i++;
    }
}

int main()
{

    char matriu_clau[7][7] = {
        " XIFRAT",
        "NABCDEF",
        "OGHIJKL",
        "RMNOPQR",
        "MSTUVWX",
        "AYZ 123",
        "L456789"
    };

    int opcio, i, j, error, linia, cnt;
    char text[MAX], nom_fitxer[MAX];
    char frases_fitxer[MAX][MAX];

    FILE* fit;

    i = 0;
    j = 0;

    
	mostrar_menu();
    scanf_s("%d", &opcio);  //scanf_s fa el mateix que scanf, pero no dona warnings :)

    while (opcio < 1 || opcio > 4)
    {
        printf("No has introduit un valor correcte, torna a introduir-lo\n");
        scanf_s("%d", &opcio);
    }

    while (opcio > 0 && opcio < 6)
    {
        if (opcio == 1)
        {
            printf("Escriu el text que vols xifrar\n");
            fgets(text, MAX, stdin);  //queda un \n al buffer, el llegim en aquest fgets
            fgets(text, MAX, stdin);  //ara el buffer esta net, llegim la frase
            error = xifrar_frase(text, matriu_clau);

            if (error)
            {
                printf("Error xifrant la frase.  No s'ha trobat alguna lletra.\n\t-> Nomes es poden xifrar lletres angleses, espais i numeros\n");
            }
            else {
                printf("-> Frase xifrada: ");
                escriure_vector(text);
            }
        }

        else if (opcio == 2)
        {
            printf("Escriu el text que vols desxifrar\n");
            fgets(text, MAX, stdin);
            desxifrar_frase(text);
            escriure_vector(text);
        }

        else if (opcio == 3)
        {
            printf("Introdueix el nom de l'archiu que vols xifrar\n");
            fgets(nom_fitxer, MAX, stdin);
            fgets(nom_fitxer, MAX, stdin);

            cnt = 0;
            while (nom_fitxer[cnt] != '\n')
            {
                cnt++;
            }
            nom_fitxer[cnt] = '\0';

            fit = fopen(nom_fitxer, "r");
            if (fit != NULL)
            {
                //llegim el contingut del fitxer
                linia = 0;
                while (fgets(frases_fitxer[linia], MAX, fit) != NULL) //fgets retorna la frase, ens assegurem que no sigui NULL
                {
                    error = xifrar_frase(frases_fitxer[linia], matriu_clau);

                    if (error)
                    {
                        printf("Error xifrant la frase.  No s'ha trobat alguna lletra.\n\t-> Nomes es poden xifrar lletres angleses, espais i numeros\n");
                    }
                    else 
                    {
                        linia++;
                    }
                }
                fclose(fit);


                //escribim el contingut xifrat
                fit = fopen("xifrat.txt", "w");
                for (int cnt2 = 0; cnt2 < linia; cnt2++)
                {
                    fputs(frases_fitxer[cnt2], fit);
                    fputs("\n", fit);
                }
                fclose(fit);
                printf("Fitxer xifrat correctament.  Resultat a xifrat.txt.\n");
            }
            else {
                printf("El fitxer %s no existeix", nom_fitxer);
            }
            
        }

        else if (opcio == 4)
        {

        }

        else
        {
            return 1;
        }
        mostrar_menu();
        scanf_s("%d", &opcio);
    }
        
	return 0;
}
