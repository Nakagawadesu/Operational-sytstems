#include <iostream>
#include <queue>

using namespace std;

class res
{
public:
    char valor = 'n';
    int eh_falta = 0;
};

void print_vetor(char *vetor, int tamanho_vetor)
{
    int i = 0;
    while (i < tamanho_vetor)
    {
        cout << vetor[i] << " ";
        i++;
    }
    cout << endl;
}

void print_matriz(res **matriz, int linha, int coluna)
{
    cout << endl;
    int i = 0;
    while (i < linha)
    {
        int j = 0;
        cout << "q" << i << "\t";

        while (j < coluna)
        {
            if (matriz[i][j].eh_falta == 1)
            {
                cout << "\033[31m" << matriz[i][j].valor << "\t";
            }
            else
            {
                cout << "\033[32m" << matriz[i][j].valor << "\t";
            }
            j++;
        }
        cout << endl
             << endl;
        i++;
        cout << "\033[31m";
    }
}

void apaga_memoria(char *memoria, int tamanho_memoria)
{
    int i = 0;
    while (i < tamanho_memoria)
    {
        memoria[i] = 'n';
        i++;
    }
}

void apaga_matriz(res **matriz, int linha, int coluna)
{
    int i = 0;
    while (i < linha)
    {
        int j = 0;
        while (j < coluna)
        {
            matriz[i][j].valor = 'n';
            matriz[i][j].eh_falta = 0;
            j++;
        }
        i++;
    }
}

res **cria_matriz(int linha, int coluna)
{
    res **nova_matriz = (res **)malloc(linha * sizeof(res *));

    int i = 0;
    while (i < linha)
    {
        nova_matriz[i] = (res *)malloc(coluna * sizeof(res));
        int j = 0;
        while (j < coluna)
        {
            nova_matriz[i][j].valor = 'x';
            nova_matriz[i][j].eh_falta = 0;
            j++;
        }
        i++;
    }

    return nova_matriz;
}

void free_matriz(res **matriz, int linha)
{
    int i = 0;
    while (i < linha)
    {
        free(matriz[i]);
        i++;
    }
    free(matriz);
}

void fifo(char *memoria, int tamanho_memoria, char *cadeia_referencia, int tamanho_referencia)
{
    cout << "\n\n#####  FIFO" << endl;

    int tempo = 0;
    int posicao_memoria = 0;
    queue<int> fila;

    int linha = 3;
    int coluna = 20;
    res **resultado = cria_matriz(linha, coluna);

    int faltas_de_pagina = 0;

    apaga_matriz(resultado, linha, coluna);

    while (tempo < tamanho_referencia)
    {
        int posicao_livre = -1;
        int i = 0;
        int ja_existe = -1;
        while (i < tamanho_memoria)
        {
            if (memoria[i] == 'n' && posicao_livre == -1)
            {
                posicao_livre = i;
            }
            if (memoria[i] == cadeia_referencia[tempo])
            {
                ja_existe = i;
            }

            i++;
        }

        if (ja_existe == -1)
        {
            faltas_de_pagina++;
            if (posicao_livre != -1)
            {
                memoria[posicao_livre] = cadeia_referencia[tempo];
                fila.push(posicao_livre);
            }
            else
            {
                posicao_livre = fila.front();
                if (memoria[posicao_livre] != cadeia_referencia[tempo])
                {
                    memoria[posicao_livre] = cadeia_referencia[tempo];
                    fila.pop();
                    fila.push(posicao_livre);
                }
            }
            resultado[posicao_livre][tempo].eh_falta = 1;
        }

        resultado[0][tempo].valor = memoria[0];
        resultado[1][tempo].valor = memoria[1];
        resultado[2][tempo].valor = memoria[2];

        tempo++;
    }

    print_matriz(resultado, linha, coluna);
    free_matriz(resultado, linha);
    cout << "Faltas de pagina: " << faltas_de_pagina << endl;
}

void lru(char *memoria, int tamanho_memoria, char *cadeia_referencia, int tamanho_referencia)
{
    cout << "\n\n#####  LRU" << endl;

    int tempo = 0;
    int posicao_memoria = 0;
    queue<int> fila;

    int linha = 3;
    int coluna = 20;
    res **resultado = cria_matriz(linha, coluna);

    int faltas_de_pagina = 0;

    apaga_matriz(resultado, linha, coluna);

    while (tempo < tamanho_referencia)
    {
        int posicao_livre = -1;
        int i = 0;
        int ja_existe = -1;
        int mais_tempo = -1;
        int indice_mais_tempo = -1;
        char item_mais_tempo;

        while (i < tamanho_memoria)
        {
            if (memoria[i] == 'n' && posicao_livre == -1)
            {
                posicao_livre = i;
            }

            if (memoria[i] == cadeia_referencia[tempo])
            {
                ja_existe = i;
            }
            else
            {
                int j = tempo;
                int existe = 0;
                while (j >= 0)
                {
                    if (memoria[i] == cadeia_referencia[j])
                    {
                        existe = 1;
                        if (mais_tempo < (tempo - j))
                        {
                            mais_tempo = tempo - j;
                            indice_mais_tempo = i;
                            item_mais_tempo = memoria[i];
                        }
                        j = -1;
                    }
                    j--;
                }
                if (existe == 0)
                {
                    mais_tempo = tempo;
                    indice_mais_tempo = i;
                    item_mais_tempo = memoria[i];
                }
            }

            i++;
        }

        if (ja_existe == -1)
        {
            faltas_de_pagina++;
            if (posicao_livre != -1)
            {
                memoria[posicao_livre] = cadeia_referencia[tempo];
            }
            else
            {
                posicao_livre = indice_mais_tempo;
                memoria[posicao_livre] = cadeia_referencia[tempo];
            }
            resultado[posicao_livre][tempo].eh_falta = 1;
        }

        resultado[0][tempo].valor = memoria[0];
        resultado[1][tempo].valor = memoria[1];
        resultado[2][tempo].valor = memoria[2];

        tempo++;
    }

    print_matriz(resultado, linha, coluna);
    free_matriz(resultado, linha);
    cout << "Faltas de pagina: " << faltas_de_pagina << endl;
}

void otimo(char *memoria, int tamanho_memoria, char *cadeia_referencia, int tamanho_referencia)
{
    cout << "\n\n#####  Otimo" << endl;

    int tempo = 0;
    int posicao_memoria = 0;
    queue<int> fila;

    int linha = 3;
    int coluna = 20;
    res **resultado = cria_matriz(linha, coluna);

    int faltas_de_pagina = 0;

    apaga_matriz(resultado, linha, coluna);

    while (tempo < tamanho_referencia)
    {
        int posicao_livre = -1;
        int i = 0;
        int ja_existe = -1;
        int mais_tempo = -1;
        int indice_mais_tempo = -1;
        char item_mais_tempo;

        while (i < tamanho_memoria)
        {
            if (memoria[i] == 'n' && posicao_livre == -1)
            {
                posicao_livre = i;
            }

            if (memoria[i] == cadeia_referencia[tempo])
            {
                ja_existe = i;
            }
            else
            {
                int j = tempo;
                int existe = 0;
                while (j < tamanho_referencia)
                {
                    if (memoria[i] == cadeia_referencia[j])
                    {
                        existe = 1;
                        if (mais_tempo < (j - tempo))
                        {
                            mais_tempo = j - tempo;
                            indice_mais_tempo = i;
                            item_mais_tempo = memoria[i];
                        }
                        j = tamanho_referencia;
                    }
                    j++;
                }
                if (existe == 0)
                {
                    mais_tempo = tamanho_referencia;
                    indice_mais_tempo = i;
                    item_mais_tempo = memoria[i];
                }
            }

            i++;
        }

        if (ja_existe == -1)
        {
            faltas_de_pagina++;
            if (posicao_livre != -1)
            {
                memoria[posicao_livre] = cadeia_referencia[tempo];
            }
            else
            {
                posicao_livre = indice_mais_tempo;
                memoria[posicao_livre] = cadeia_referencia[tempo];
            }
            resultado[posicao_livre][tempo].eh_falta = 1;
        }

        resultado[0][tempo].valor = memoria[0];
        resultado[1][tempo].valor = memoria[1];
        resultado[2][tempo].valor = memoria[2];

        tempo++;
    }

    print_matriz(resultado, linha, coluna);
    free_matriz(resultado, linha);

    cout << "Faltas de pagina: " << faltas_de_pagina << endl;
}

int main(void)
{
    int tamanho_refencia = 20;
    char cadeia_referencia[tamanho_refencia] = {'7', '0', '1', '2', '0', '3', '0', '4', '2', '3', '0', '3', '2', '1', '2', '0', '1', '7', '0', '1'};

    int tamanho_memoria = 3;
    char memoria[tamanho_memoria] = {'x', 'x', 'x'};

    apaga_memoria(memoria, tamanho_memoria);
    fifo(memoria, tamanho_memoria, cadeia_referencia, tamanho_refencia);

    apaga_memoria(memoria, tamanho_memoria);
    lru(memoria, tamanho_memoria, cadeia_referencia, tamanho_refencia);

    apaga_memoria(memoria, tamanho_memoria);
    otimo(memoria, tamanho_memoria, cadeia_referencia, tamanho_refencia);

    return 0;
}