///////////////////////////////////////////////CABECALHO///////////////////////////////////////////////////

// Ana Cecilia de Queiroz Andrade
// Renato Augusto Silva
// Tiago de Paula Martins

// Sistema de cadastro de uma livraria

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <cstring>

using namespace std;

const int TAM_NOME = 70;
const int TAM_DEPARTAMENTO = 30;
const int TAM_AUTOR = 35;
const int TAM_EDITORA = 35;
const int TAM_DESCRICAO = 50;
const int TAM_CABECALHO = 200;

struct livro
{
    char Nome[TAM_NOME];
    char Departamento[TAM_DEPARTAMENTO];
    char Autor[TAM_AUTOR];
    char Editora[TAM_EDITORA];
    char Descricao[TAM_DESCRICAO];
    int NumeroPaginas;
    int Quantidade;
    int Volume;
    float Preco;
};

////////////////////////////////////////PREENCHER O VETOR///////////////////////////////////////
// Funcao feita para ler o arquivo csv e utilizar para conversao para binario
void preencherEntrada(ifstream &arquivoentrada, livro cadastro[], int &tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        // SOMENTE NO LINUX arquivoentrada.ignore(); // Ignorar o caractere de quebra de linha
        arquivoentrada.ignore(); // Ignorar o caractere de quebra de linha
        arquivoentrada.getline(cadastro[i].Nome, TAM_NOME, ',');
        arquivoentrada >> cadastro[i].NumeroPaginas;
        arquivoentrada.ignore(); // Ignorar o caractere de quebra de linha
        arquivoentrada.getline(cadastro[i].Departamento, TAM_DEPARTAMENTO, ',');
        arquivoentrada >> cadastro[i].Preco;
        arquivoentrada.ignore(); // Ignorar o caractere de quebra de linha
        arquivoentrada.getline(cadastro[i].Autor, TAM_AUTOR, ',');
        arquivoentrada.getline(cadastro[i].Editora, TAM_EDITORA, ',');
        arquivoentrada >> cadastro[i].Quantidade;
        arquivoentrada.ignore(); // Ignorar o caractere de quebra de linha
        arquivoentrada >> cadastro[i].Volume;
        arquivoentrada.ignore(); // Ignorar o caractere de quebra de linha
        arquivoentrada.getline(cadastro[i].Descricao, TAM_DESCRICAO, '.');
    }
}

////////////////////////////////////////ORDENAR POR NOME///////////////////////////////////////
// Funcao de comparacao para o Shell Sort pelo campo "Nome"
bool compararLivrosNome(const livro &livro1, const livro &livro2)
{
    return strcmp(livro1.Nome, livro2.Nome) > 0;
}

// Funcao de ordenacao Shell Sort
void OrdenarPorNome(livro *vetor, int tamanho)
{
    int gaps[9] = {1, 4, 10, 23, 57, 132, 301, 701, 1750};
    int pos_gap = 8;

    while (gaps[pos_gap] > tamanho)
    {
        pos_gap--;
    }

    while (pos_gap >= 0)
    {
        int gap = gaps[pos_gap];

        for (int i = gap; i < tamanho; i++)
        {
            livro aux = vetor[i];
            int j = i;
            while ((j >= gap) and compararLivrosNome(vetor[j - gap], aux))
            {
                vetor[j] = vetor[j - gap];
                j -= gap;
            }
            vetor[j] = aux;
        }

        pos_gap--;
    }
}

//////////////////////////////////////////ORDENAR POR PRECO///////////////////////////////////////
// Funcao de comparacao para o Shell Sort por preco
bool compararLivrosPreco(const livro &livro1, const livro &livro2)
{
    return livro1.Preco > livro2.Preco;
}

// Função de ordenação Shell Sort
void ordenarPorPreco(livro vetor[], int tamanho)
{
    int gaps[9] = {1, 4, 10, 23, 57, 132, 301, 701, 1750};
    int pos_gap = 8;

    while (gaps[pos_gap] > tamanho)
    {
        pos_gap--;
    }

    while (pos_gap >= 0)
    {
        int gap = gaps[pos_gap];

        for (int i = gap; i < tamanho; i++)
        {
            livro aux = vetor[i];
            int j = i;
            while ((j >= gap) and compararLivrosPreco(vetor[j - gap], aux))
            {
                vetor[j] = vetor[j - gap];
                j -= gap;
            }
            vetor[j] = aux;
        }

        pos_gap--;
    }
}

//////////////////////////////////////////ESCOLHA DA ORDENACAO///////////////////////////////////////

void EscolhaOrdenacao(livro *cadastroBIN, int tamanho)
{
    bool ContinuaOrdenacao = true;
    while (ContinuaOrdenacao)
    {

        cout << "Escolha por qual parametro voce deseja ordenar nosso cadastro de livros: \n 1 - Pelo nome do livro \n 2 - Pelo preco do livro" << endl;

        int EscolhaOrdenacao;

        cin >> EscolhaOrdenacao;

        if (EscolhaOrdenacao == 1)
        {

            OrdenarPorNome(cadastroBIN, tamanho);
            cout << endl
                 << "O sistema esta ordenado pelo nome dos livros!" << endl
                 << endl;
            ContinuaOrdenacao = false;
        }
        else if (EscolhaOrdenacao == 2)
        {
            ordenarPorPreco(cadastroBIN, tamanho);
            cout << endl
                 << "O sistema esta ordenado pelo preco dos livros!" << endl
                 << endl;
            ContinuaOrdenacao = false;
        }
        else
        {
            cout << endl
                 << "Comando invalido" << endl
                 << endl;
        }
    }
}

/////////////////////////////////////////BUSCA POR NOME////////////////////////////////////////
int buscaBinaria(const livro vetor[], int tamanho, const char *buscado)
{
    int inicio = 0;
    int fim = tamanho - 1;

    while (inicio <= fim)
    {
        int meio = (inicio + fim) / 2;
        int resultadoComparacao = strcmp(vetor[meio].Nome, buscado);

        if (resultadoComparacao == 0)
        {
            return meio; // Encontrou o livro com o nome buscado
        }
        else if (resultadoComparacao < 0)
        {
            inicio = meio + 1;
        }
        else
        {
            fim = meio - 1;
        }
    }

    return -1; // Livro nao encontrado
}

// ///////////////////////////////////////BUSCA POR DEPARTAMENTO/////////////////////////////////
void buscarPorDepartamento(const livro vetor[], int tamanho, const char *buscado)
{
    bool achou = false;

    for (int i = 0; i < tamanho; i++)
    {
        int resultadoComparacao = strcmp(vetor[i].Departamento, buscado);

        if (resultadoComparacao == 0)
        {
            cout << endl
                 << "Nome: " << vetor[i].Nome << endl;
            cout << "Numero de Paginas: " << vetor[i].NumeroPaginas << endl;
            cout << "Departamento: " << vetor[i].Departamento << endl;
            cout << "Preco: " << vetor[i].Preco << endl;
            cout << "Autor: " << vetor[i].Autor << endl;
            cout << "Editora: " << vetor[i].Editora << endl;
            cout << "Quantidade: " << vetor[i].Quantidade << endl;
            cout << "Volume: " << vetor[i].Volume << endl;
            cout << "Descricao: " << vetor[i].Descricao << endl;
            cout << "-------------------------" << endl;
            achou = true;
        }
    }

    if (achou)
    {
        cout << endl
             << "Esses sao todos os livros encontrados no departamento: " << buscado << endl
             << endl;
    }
    else
    {
        cout << endl
             << "Departamento nao encontrado!" << endl
             << endl;
    }
}

/////////////////////////////////////////////INSERIR////////////////////////////////////////////
void Insercao(livro **cadastroBIN, int &tamanho, int &capacidade)
{
    bool NaoRemovido = true;
    bool preencheuRemovido = false;

    for (int i = 0; i < tamanho; i++)
    {
        if ((*cadastroBIN)[i].Nome[0] == '\0' and !preencheuRemovido)
        {
            cout << "Digite o nome do livro que deseja cadastrar: ";
            cin.ignore();
            cin.getline((*cadastroBIN)[i].Nome, TAM_NOME);
            cout << "Digite o numero de paginas do livro que deseja cadastrar: ";
            cin >> (*cadastroBIN)[i].NumeroPaginas;
            cout << "Digite o departamento do livro que deseja cadastrar: ";
            cin.ignore();
            cin.getline((*cadastroBIN)[i].Departamento, TAM_DEPARTAMENTO);
            cout << "Digite o preco do livro que deseja cadastrar: ";
            cin >> (*cadastroBIN)[i].Preco;
            cout << "Digite o(a) autor(a) do livro que deseja cadastrar: ";
            cin.ignore();
            cin.getline((*cadastroBIN)[i].Autor, TAM_AUTOR);
            cout << "Digite a editora do livro que deseja cadastrar: ";
            cin.getline((*cadastroBIN)[i].Editora, TAM_EDITORA);
            cout << "Digite a quantidade em estoque do livro que deseja cadastrar: ";
            cin >> (*cadastroBIN)[i].Quantidade;
            cout << "Digite a descricao do livro que deseja cadastrar: ";
            cin.ignore();
            cin.getline((*cadastroBIN)[i].Descricao, TAM_DESCRICAO);
            cout << "Digite o volume do livro que deseja cadastrar, caso seja um livro unico digite 0: ";
            cin >> (*cadastroBIN)[i].Volume;
            cout << endl
                 << "Insercao feita com sucesso!\n"
                 << endl;

            NaoRemovido = false;
            preencheuRemovido = true;
        }
    }

    if (NaoRemovido)
    {
        if (tamanho == capacidade)
        {
            livro *novo = new livro[capacidade + 1];
            copy(*cadastroBIN, *cadastroBIN + tamanho, novo);
            capacidade += 1;
            delete[] *cadastroBIN;
            *cadastroBIN = novo;
        }

        cout << "Digite o nome do livro que deseja cadastrar: ";
        cin.ignore();
        cin.getline((*cadastroBIN)[tamanho].Nome, TAM_NOME);
        cout << "Digite o numero de paginas do livro que deseja cadastrar: ";
        cin >> (*cadastroBIN)[tamanho].NumeroPaginas;
        cout << "Digite o departamento do livro que deseja cadastrar: ";
        cin.ignore();
        cin.getline((*cadastroBIN)[tamanho].Departamento, TAM_DEPARTAMENTO);
        cout << "Digite o preco do livro que deseja cadastrar: ";
        cin >> (*cadastroBIN)[tamanho].Preco;
        cout << "Digite o(a) autor(a) do livro que deseja cadastrar: ";
        cin.ignore();
        cin.getline((*cadastroBIN)[tamanho].Autor, TAM_AUTOR);
        cout << "Digite a editora do livro que deseja cadastrar: ";
        cin.getline((*cadastroBIN)[tamanho].Editora, TAM_EDITORA);
        cout << "Digite a quantidade em estoque do livro que deseja cadastrar: ";
        cin >> (*cadastroBIN)[tamanho].Quantidade;
        cout << "Digite a descricao do livro que deseja cadastrar: ";
        cin.ignore();
        cin.getline((*cadastroBIN)[tamanho].Descricao, TAM_DESCRICAO);
        cout << "Digite o volume do livro que deseja cadastrar, caso seja um livro unico digite 0: ";
        cin >> (*cadastroBIN)[tamanho].Volume;
        cout << endl
             << "Insercao feita com sucesso!\n"
             << endl;

        tamanho++;
    }
}

///////////////////////////////////////////REMOVER////////////////////////////////////////////
void Remocao(livro *cadastroBIN, int tamanho)
{
    char buscado[TAM_NOME];
    cout << "Digite o nome do livro que deseja remover: ";
    cin.ignore();
    cin.getline(buscado, TAM_NOME);

    int posicao = buscaBinaria(cadastroBIN, tamanho, buscado);

    if (posicao != -1)
    {
        cadastroBIN[posicao].Nome[0] = '\0';
        cadastroBIN[posicao].NumeroPaginas = 0;
        cadastroBIN[posicao].Departamento[0] = '\0';
        cadastroBIN[posicao].Preco = 0;
        cadastroBIN[posicao].Autor[0] = '\0';
        cadastroBIN[posicao].Editora[0] = '\0';
        cadastroBIN[posicao].Quantidade = 0;
        cadastroBIN[posicao].Volume = 0;
        cadastroBIN[posicao].Descricao[0] = '\0';

        cout << "\nRemocao feita com sucesso!\n"
             << endl;
    }
    else if (posicao == -1)
    {
        cout << "\nLivro nao encontrado\n"
             << endl;
    }
}

// ///////////////////////////////////////////EDITAR////////////////////////////////////////////
void Edicao(livro *cadastroBIN, int tamanho)
{
    char buscado[TAM_NOME];
    cout << "Digite o nome do livro que deseja editar: ";
    cin.ignore();
    cin.getline(buscado, TAM_NOME);

    int posicao = buscaBinaria(cadastroBIN, tamanho, buscado);

    if (posicao != -1)
    {
        cout << "O que deseja editar? \n 1 - preco \n 2 - quantidade do livro \n 3 - descricao" << endl;
        int resposta;
        cin >> resposta;

        if (resposta == 1)
        {
            cout << "Digite o novo preco: ";
            cin >> cadastroBIN[posicao].Preco;
            cout << endl
                 << "Edicao concluida" << endl
                 << endl;
        }
        else if (resposta == 2)
        {
            cout << "Digite a nova quantidade: ";
            cin >> cadastroBIN[posicao].Quantidade;
            cout << endl
                 << "Edicao concluida" << endl
                 << endl;
        }
        else if (resposta == 3)
        {
            cout << "Digite a nova descricao: ";
            cin.ignore();
            cin.getline(cadastroBIN[posicao].Descricao, TAM_DESCRICAO);
            cout << endl
                 << "Edicao concluida" << endl
                 << endl;
        }
        else
        {
            cout << endl
                 << "Comando Invalido" << endl
                 << endl;
        }
    }
    else
    {
        cout << endl
             << "Livro nao encontrado" << endl
             << endl;
    }
}

///////////////////////////////////////////EXIBIR TODOS OS LIVROS////////////////////////////////////////////
void Exibicao(livro *cadastroBIN, int &tamanho)
{
    cout << "LISTA DE LIVROS" << endl
         << endl;

    for (int i = 0; i < tamanho; i++)
    {
        cout << "Nome: " << cadastroBIN[i].Nome << endl
             << "Numero de paginas: " << cadastroBIN[i].NumeroPaginas << endl
             << "Departamento: " << cadastroBIN[i].Departamento << endl
             << "Preco: R$" << fixed << setprecision(2) << cadastroBIN[i].Preco << endl
             << "Autor(a): " << cadastroBIN[i].Autor << endl
             << "Editora: " << cadastroBIN[i].Editora << endl
             << "Quantidade em estoque: " << cadastroBIN[i].Quantidade << endl
             << "Descricao: " << cadastroBIN[i].Descricao << endl;
        if (cadastroBIN[i].Volume == 0)
        {
            cout << "Volume unico" << endl
                 << endl;
        }
        else
        {
            cout << "Volume: " << cadastroBIN[i].Volume << endl
                 << endl;
        }
    }

    cout << "Esses sao todos os livros cadastrados em nosso sistema!\n"
         << endl;
}

/////////////////////////////////////////////CARRINHO///////////////////////////////////////////
void Carrinho(livro *cadastroBIN, int tamanho)
{
    char buscado[TAM_NOME];
    float Preco = 0.00;
    bool continua = true;
    while (continua)
    {
        cout << "Digite o nome do livro: ";
        cin.ignore();
        cin.getline(buscado, TAM_NOME);

        int posicao = buscaBinaria(cadastroBIN, tamanho, buscado);

        if (posicao != -1)
        {
            cout << endl
                 << "Nome: " << cadastroBIN[posicao].Nome << endl
                 << "Preco: R$" << fixed << setprecision(2) << cadastroBIN[posicao].Preco << endl
                 << "Quantidade em estoque: " << cadastroBIN[posicao].Quantidade << endl
                 << "Descricao: " << cadastroBIN[posicao].Descricao << endl;
            if (cadastroBIN[posicao].Volume == 0)
            {
                cout << "Volume unico" << endl
                     << endl;
            }
            else
            {
                cout << "Volume: " << cadastroBIN[posicao].Volume << endl
                     << endl;
            }
            cout << "Tem certeza que deseja adicionar esse livro ao seu carrinho? \n 1 - Sim \n 2 - Nao" << endl;
            int resposta;
            cin >> resposta;

            if (resposta == 1)
            {
                Preco += cadastroBIN[posicao].Preco;
            }
        }
        else
        {
            cout << endl
                 << "Livro nao encontrado" << endl
                 << endl;
        }

        cout << "Deseja adicionar outro livro? \n 1 - Sim \n 2 - Nao" << endl;
        int escolha;
        cin >> escolha;

        if (escolha == 1)
        {
            continua = true;
        }
        else if (escolha == 2)
        {
            continua = false;
        }
    }

    cout << endl
         << "Total do seu carrinho : R$ " << fixed << setprecision(2) << Preco << endl
         << endl;
}

///////////////////////////////////////////IMPRIMIR TRECHO DO CADASTRO///////////////////////////////////////////
void ImprimirTrecho(livro *cadastroBIN, int tamanho)
{

    bool continua = true;
    int posicaoInicial, posicaoFinal, aux, numeroDeRemovidos = 0;

    cout << " Atualmente temos " << tamanho << " livros cadastrados em nosso sistema!" << endl
         << endl
         << "Digite a posicao inicial e a final do trecho que voce deseja imprimir:" << endl;
    while (continua)
    {
        cout << "Posicao inicial: ";
        cin >> posicaoInicial;
        if (posicaoInicial > tamanho)
        {
            cout << endl
                 << "Erro: Essa posicao e maior que o numero de livros cadastrados" << endl
                 << endl;
        }
        else
        {
            continua = false;
        }
    }
    while (!continua)
    {
        cout << "Posicao final: ";
        cin >> posicaoFinal;
        if (posicaoFinal > tamanho or posicaoFinal < posicaoInicial)
        {
            cout << endl
                 << "Erro: essa posicao e maior que o numero de livros cadastrados ou e menor que a posicao inicial informada" << endl
                 << endl;
        }
        else
        {
            continua = true;
        }
    }

    cout << endl;

    aux = posicaoInicial;

    posicaoInicial -= 1;

    for (int i = 0; i < tamanho; i++)
    {
        if (cadastroBIN[i].Nome[0] == '\0')
        {
            numeroDeRemovidos++;
        }
    }

    EscolhaOrdenacao(cadastroBIN, tamanho);

    posicaoInicial += numeroDeRemovidos;

    while (posicaoInicial < posicaoFinal + numeroDeRemovidos)
    {
        cout << (posicaoInicial - numeroDeRemovidos) + 1 << endl;
        cout << "Nome: " << cadastroBIN[posicaoInicial].Nome << endl;
        cout << "Numero de paginas: " << cadastroBIN[posicaoInicial].NumeroPaginas << endl;
        cout << "Departamento: " << cadastroBIN[posicaoInicial].Departamento << endl;
        cout << "Preco: R$" << fixed << setprecision(2) << cadastroBIN[posicaoInicial].Preco << endl;
        cout << "Autor(a): " << cadastroBIN[posicaoInicial].Autor << endl;
        cout << "Editora: " << cadastroBIN[posicaoInicial].Editora << endl;
        cout << "Quantidade em estoque: " << cadastroBIN[posicaoInicial].Quantidade << endl;
        cout << "Descricao: " << cadastroBIN[posicaoInicial].Descricao << endl;
        if (cadastroBIN[posicaoInicial].Volume == 0)
        {
            cout << "Volume unico" << endl
                 << endl;
        }
        else
        {
            cout << "Volume: " << cadastroBIN[posicaoInicial].Volume << endl
                 << endl;
        }
        posicaoInicial++;
    }

    cout << "Esses sao todos os livros de acordo com o trecho escolhido de " << aux << " a " << posicaoFinal << "!" << endl
         << endl;
}

///////////////////////////////////////////PREENCHER O ARQUIVO DE SAIDA///////////////////////////////////////////
void preencherArquivoSaida(livro *cadastroBIN, int tamanho, bool &continua)
{
    ofstream arquivoSbin("baselivrariasaida.bin");

    for (int i = 0; i < tamanho; i++)
    {
        if (cadastroBIN[i].Nome[0] == '\0')
        {
            tamanho -= 1;
        }
    }

    arquivoSbin << tamanho << endl;

    for (int i = 0; i < tamanho; i++)
    {
        if (cadastroBIN[i].Nome[0] != '\0')
        {
            arquivoSbin << cadastroBIN[i].Nome << ','
                        << cadastroBIN[i].NumeroPaginas << ','
                        << cadastroBIN[i].Departamento << ','
                        << fixed << setprecision(2) << cadastroBIN[i].Preco << ','
                        << cadastroBIN[i].Autor << ','
                        << cadastroBIN[i].Editora << ','
                        << cadastroBIN[i].Quantidade << ','
                        << cadastroBIN[i].Volume << ','
                        << cadastroBIN[i].Descricao << '.' << endl;
        }
    }
    continua = false;
}

/////////////////////////////////////////EXPORTAR ARQUIVO///////////////////////////////////////////////
void ExportarCSV(livro *cadastroBIN, int tamanho)
{

    ofstream arquivocsv("baselivrariaexp.csv");

    int numRemovidos = 0;

    for (int i = 0; i < tamanho; i++)
    {
        if (cadastroBIN[i].Nome[0] == '\0')
        {
            numRemovidos++;
        }
    }

    if (arquivocsv)
    {
        arquivocsv << "Nome do livro,paginas,departamento,preco,autor,editora,quantidade do livro,volume,descricao." << endl;
        arquivocsv << tamanho - numRemovidos << endl;
        for (int i = 0; i < tamanho; i++)
        {
            if (cadastroBIN[i].Nome[0] != '\0')
            {
                arquivocsv << cadastroBIN[i].Nome << ","
                           << cadastroBIN[i].NumeroPaginas << ","
                           << cadastroBIN[i].Departamento << ","
                           << cadastroBIN[i].Preco << ","
                           << cadastroBIN[i].Autor << ","
                           << cadastroBIN[i].Editora << ","
                           << cadastroBIN[i].Quantidade << ","
                           << cadastroBIN[i].Volume << ","
                           << cadastroBIN[i].Descricao << "."
                           << "\n";
            }
        }

        arquivocsv.close();
        cout << endl << "Dados exportados com sucesso para o arquivo: baselivrariaexp.csv" << endl;
    }
    else
    {
        cout << "Erro ao abrir o arquivo. " << endl;
    }
}

/////////////////////////////////////////PRINCIPAL///////////////////////////////////////////////

int main()
{

    /////////////////////////////////////////PREENCHER O VETOR///////////////////////////////////////////////

    int tamanho, capacidade;
    char cabecalho[TAM_CABECALHO];
    int numLivros = 0;

    ifstream arquivoentrada("baselivraria.csv");

    if (not(arquivoentrada))
    {
        cout << endl
             << "Erro: Nao foi possivel abrir o arquivo, tente novamente." << endl
             << endl;
    }

    arquivoentrada.getline(cabecalho, 100, '.');
    arquivoentrada >> tamanho;

    livro cadastro[tamanho];

    capacidade = tamanho;

    preencherEntrada(arquivoentrada, cadastro, tamanho);

    ofstream arquivosaida("baselivraria2.bin", ios::binary);

    arquivosaida.write((char *)cadastro, sizeof(livro) * tamanho);

    arquivosaida.close();

    // Abrir o arquivo binário em modo de leitura binária
    ifstream arquivoBinario("baselivraria2.bin", ios::binary);

    livro *cadastroBIN;

    cadastroBIN = new livro[tamanho];

    if (!arquivoBinario)
    {
        cout << "Erro ao abrir o arquivo " << endl;
        return 1;
    }
    else
    {
        while (arquivoBinario.read(reinterpret_cast<char *>(&cadastroBIN[numLivros]), sizeof(livro)))
        {
            numLivros++;
        }
    }
    tamanho = numLivros;

    arquivoBinario.close();

    OrdenarPorNome(cadastroBIN, tamanho);

    cout << "===============================================" << endl
         << "BEM-VINDO(A) AO SISTEMA DE CADASTRO DA LIVRARIA" << endl
         << "===============================================" << endl;

    bool continua = true;
    while (continua)
    {

        cout << "Escolha qual acao deseja realizar: \n 1 - Busca \n 2 - Inserir \n 3 - Remover \n 4 - Editar \n 5 - Exibir todos os livros \n 6 - Montar um carrinho \n 7 - Imprimir trecho do cadastro \n 8 - Exportar em formato csv" << endl;

        int escolha;
        cin >> escolha;

        switch (escolha)
        {

            ///////////////////////////////////////BUSCAR//////////////////////////////////////////

        case 1:
            cout << "----------------------" << endl
                 << "Sua escolha foi: Busca" << endl
                 << "----------------------" << endl
                 << "Escolha o metodo de busca: \n 1 - Busca por nome \n 2 - Busca por departamento \n";

            int resposta;
            cin >> resposta;

            if (resposta == 1)
            {
                char buscado[70];
                cout << "Digite o nome do livro: ";
                cin.ignore();
                cin.getline(buscado, 70);
                int indiceEncontrado = buscaBinaria(cadastroBIN, numLivros, buscado);

                // Exibir o resultado da busca
                if (indiceEncontrado != -1)
                {
                    cout << endl
                         << "Livro encontrado:" << endl
                         << endl;
                    cout << "Nome: " << cadastroBIN[indiceEncontrado].Nome << endl;
                    cout << "Numero de Paginas: " << cadastroBIN[indiceEncontrado].NumeroPaginas << endl;
                    cout << "Departamento: " << cadastroBIN[indiceEncontrado].Departamento << endl;
                    cout << "Preco: R$" << cadastroBIN[indiceEncontrado].Preco << endl;
                    cout << "Autor: " << cadastroBIN[indiceEncontrado].Autor << endl;
                    cout << "Editora: " << cadastroBIN[indiceEncontrado].Editora << endl;
                    cout << "Quantidade: " << cadastroBIN[indiceEncontrado].Quantidade << endl;
                    cout << "Volume: " << cadastroBIN[indiceEncontrado].Volume << endl;
                    cout << "Descricao: " << cadastroBIN[indiceEncontrado].Descricao << endl
                         << endl;
                }
                else
                {
                    cout << endl
                         << "Livro nao encontrado." << endl
                         << endl;
                }
            }

            else if (resposta == 2)
            {
                char departamentoBuscado[50];
                cout << "Digite o departamento do livro que deseja buscar: ";
                cin.ignore();
                cin.getline(departamentoBuscado, 50);

                // Executa a busca por departamento
                buscarPorDepartamento(cadastroBIN, numLivros, departamentoBuscado);
            }

            else
            {
                cout << endl
                     << "Comando Invalido!" << endl
                     << endl;
            }
            break;

            ////////////////////////////////////////INSERIR///////////////////////////////////////////////

        case 2:
            cout << "------------------------" << endl
                 << "Sua escolha foi: Inserir" << endl
                 << "------------------------" << endl;

            Insercao(&cadastroBIN, tamanho, capacidade);

            OrdenarPorNome(cadastroBIN, tamanho);

            break;

            ////////////////////////////////////////REMOVER///////////////////////////////////////////////

        case 3:
            cout << "------------------------" << endl
                 << "Sua escolha foi: Remover" << endl
                 << "------------------------" << endl;

            Remocao(cadastroBIN, tamanho);

            OrdenarPorNome(cadastroBIN, tamanho);

            break;

            ////////////////////////////////////////EDITAR///////////////////////////////////////////////

        case 4:
            cout << "--------------------------" << endl
                 << "Sua escolha foi: Editar" << endl
                 << "--------------------------" << endl;

            Edicao(cadastroBIN, tamanho);

            OrdenarPorNome(cadastroBIN, tamanho);

            break;

            ////////////////////////////////////////EXIBIR TODOS OS LIVROS///////////////////////////////////////////////

        case 5:
            cout << "---------------------------------------" << endl
                 << "Sua escolha foi: Exibir todos os livros" << endl
                 << "---------------------------------------" << endl;

            EscolhaOrdenacao(cadastroBIN, tamanho);

            Exibicao(cadastroBIN, tamanho);

            break;

            ////////////////////////////////////////MONTAR UM CARRINHO///////////////////////////////////////////////

        case 6:
            cout << "-----------------------------------" << endl
                 << "Sua escolha foi: Montar um carrinho" << endl
                 << "-----------------------------------" << endl;

            Carrinho(cadastroBIN, tamanho);

            break;

            ////////////////////////////////////////IMPRIMIR TRECHO DO CADASTRO///////////////////////////////////////////////

        case 7:
            cout << "-----------------------------------" << endl
                 << "Sua escolha foi: Imprimir trecho do cadastro" << endl
                 << "-----------------------------------" << endl;

            ImprimirTrecho(cadastroBIN, tamanho);

            break;

        case 8:
            cout << "-----------------------------------" << endl
                 << "Sua escolha foi: Exportar arquivo em formato CSV" << endl
                 << "-----------------------------------" << endl;

            ExportarCSV(cadastroBIN, tamanho);

            break;

        default:
            cout << endl
                 << "Comando invalido" << endl
                 << endl;

            break;
        }

        bool acao = true;

        while (acao)
        {

            cout << "Deseja fazer outra acao? \n Se sim: digite 1 \n Se nao: digite 2" << endl;
            int novaAcao;
            cin >> novaAcao;
            if (novaAcao == 1)
            {
                continua = true;
                acao = false;
            }
            else if (novaAcao == 2)
            {
                preencherArquivoSaida(cadastro, tamanho, continua);

                acao = false;
            }
            else
            {
                cout << endl
                     << "Comando invalido" << endl
                     << endl;
                acao = true;
            }
        }

        ofstream arquivosaida1("baselivraria3.bin", ios::binary);

        arquivosaida1.write((char *)cadastroBIN, sizeof(livro) * tamanho);
        arquivosaida1.close();

        cout << "===============================================================" << endl;
        cout << "Agradecemos por utilizar o sistema da livraria \nVolte sempre!" << endl;
        cout << "===============================================================" << endl;
    }

    return 0;
}