/* Alunos:
Bruno Szura
Matheus Nakagawa
*/


#include <iostream>
#include <omp.h>

using namespace std;

omp_lock_t lock;

int main(void)
{
    int tamanho_buffer = 10;
    int buffer[tamanho_buffer];
    int itens_buffer = 0;
    int posicao_entrada = 0;
    int posicao_saida = 0;
    int id_item_atual = 0;
    int max_itens = 1000;
    int numero_consumidos = 0;
    int item_consumido;

    int cont0 = 0;
    int cont1 = 0;
    int cont2 = 0;
    int cont3 = 0;

    int itens_consumidos[1000];

    int i = 0;
    while(i < tamanho_buffer)
    {
        buffer[i] = -1;
        i++;
    }

    #pragma omp parallel num_threads(4)
    {
        while(numero_consumidos < max_itens)
        {
            int id_thread = omp_get_thread_num();
            if(id_thread == 0 || id_thread == 1)
            {
                omp_set_lock(&lock);
                if(id_item_atual < max_itens)
                {
                    if(itens_buffer < tamanho_buffer)
                    {
                        if(id_thread == 0)
                        {
                            cont0++;
                        }
                        else
                        {
                            cont1++;
                        }

                        buffer[posicao_entrada] = id_item_atual;
                        itens_buffer++;
                        posicao_entrada = (posicao_entrada + 1) % tamanho_buffer;
                        cout << "Thread " << id_thread << " produzindo item " << id_item_atual << endl;
                        id_item_atual++;
                    }
                }
                omp_unset_lock(&lock);
            }
            else if(id_thread == 2 || id_thread == 3)
            {
                omp_set_lock(&lock);
                if(itens_buffer > 0)
                {
                    if(id_thread == 2)
                    {
                        cont2++;
                    }
                    else
                    {
                        cont3++;
                    }

                    item_consumido = buffer[posicao_saida];
                    itens_consumidos[numero_consumidos] = item_consumido;
                    itens_buffer--;
                    posicao_saida = (posicao_saida + 1) % tamanho_buffer;
                    numero_consumidos++;
                    cout << "Thread " << id_thread << " consumindo item " << item_consumido << endl;
                }
                omp_unset_lock(&lock);
            }
        }

        omp_destroy_lock(&lock);
    }

    cout << "\nNumero de produtos produzidos " << id_item_atual << endl;
    cout << "\nNumero de produtos consumidos " << numero_consumidos << endl;

    cout << "\nProduzidos pela thread 0: " << ((cont0 * 100.0) / max_itens) << "%" << endl;
    cout << "\nProduzidos pela thread 1: " << ((cont1 * 100.0) / max_itens) << "%" << endl;
    cout << "\nConsumidos pela thread 2: " << ((cont2 * 100.0) / max_itens) << "%" << endl;
    cout << "\nConsumidos pela thread 3: " << ((cont3 * 100.0) / max_itens) << "%" << endl;

    i = 0;

    /*cout << "\n### Itens consumidos ###\n" << endl;

    while(i < max_itens)
    {
        cout << itens_consumidos[i] << endl;

        i++;
    }*/

    return 0;
}