#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>
using namespace std;

struct livro
{
    string Nome;
    string Departamento;
    string Autor;
    string Editora;
    string Descricao;
    int NumeroPaginas;
    int Quantidade;
    int Volume;
    float Preco;
};

////////////////////////////////////////PREENCHER O VETOR///////////////////////////////////////

void preencherEntrada(ifstream &arquivoentrada, livro *&cadastro, int &tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        // SOMENTE NO LINUX arquivoentrada.ignore(); // Ignorar o caractere de quebra de linha
        arquivoentrada.ignore(); // Ignorar o caractere de quebra de linha
        getline(arquivoentrada, cadastro[i].Nome, ',');
        arquivoentrada >> cadastro[i].NumeroPaginas;
        arquivoentrada.ignore(); // Ignorar o caractere de quebra de linha
        getline(arquivoentrada, cadastro[i].Departamento, ',');
        arquivoentrada >> cadastro[i].Preco;
        arquivoentrada.ignore(); // Ignorar o caractere de quebra de linha
        getline(arquivoentrada, cadastro[i].Autor, ',');
        getline(arquivoentrada, cadastro[i].Editora, ',');
        arquivoentrada >> cadastro[i].Quantidade;
        arquivoentrada.ignore(); // Ignorar o caractere de quebra de linha
        arquivoentrada >> cadastro[i].Volume;
        arquivoentrada.ignore(); // Ignorar o caractere de quebra de linha
        getline(arquivoentrada, cadastro[i].Descricao, '.');
    }
}

////////////////////////////////////////ORDENAR POR NOME///////////////////////////////////////

void OrdenarPorNome(livro *cadastro, int tamanho)
{

    // sequência de Ciura, a que tem os melhores resultados experimentais
    int gaps[9] = {1, 4, 10, 23, 57, 132, 301, 701, 1750};
    int pos_gap = 8;
    while (gaps[pos_gap] > tamanho)
    {
        pos_gap--;
    }
    string value;
    int j;
    while (pos_gap >= 0)
    {
        int gap = gaps[pos_gap];

        for (int i = gap; i < tamanho; i++)
        {
            value = cadastro[i].Nome;
            j = i;
            while ((j >= gap) and (value < cadastro[j - gap].Nome))
            {
                cadastro[j].Nome = cadastro[j - gap].Nome;
                j = j - gap;
            }
            cadastro[j].Nome = value;
        }

        pos_gap--;
    }
}

////////////////////////////////////////ORDENAR POR PRECO///////////////////////////////////////

void OrdenarPorPreco(livro *cadastro, int tamanho)
{

    // sequência de Ciura, a que tem os melhores resultados experimentais
    int gaps[9] = {1, 4, 10, 23, 57, 132, 301, 701, 1750};
    int pos_gap = 8;
    while (gaps[pos_gap] > tamanho)
    {
        pos_gap--;
    }
    float value;
    int j;
    while (pos_gap >= 0)
    {
        int gap = gaps[pos_gap];

        for (int i = gap; i < tamanho; i++)
        {
            value = cadastro[i].Preco;
            j = i;
            while ((j >= gap) and (value < cadastro[j - gap].Preco))
            {
                cadastro[j].Preco = cadastro[j - gap].Preco;
                j = j - gap;
            }
            cadastro[j].Preco = value;
        }

        pos_gap--;
    }
}

/////////////////////////////////////////BUSCA POR NOME////////////////////////////////////////

void buscaNome(livro *cadastro, int tamanho)
{
    string buscado;
    cout << "Digite o nome do livro: ";
    cin.ignore();
    getline(cin, buscado);

    int posicao = -1;
    int i = 0;
    bool naoAchou = true;

    while (i < tamanho and naoAchou)
    {
        if (buscado == cadastro[i].Nome)
        {
            naoAchou = false;
            posicao = i;
        }
        else
            i++;
    }

    if (posicao == i)
    {
        cout << "\nDados do livro Buscado:" << endl
             << endl;
        cout << "Nome: " << cadastro[i].Nome << endl
             << "Numero de paginas: " << cadastro[i].NumeroPaginas << endl
             << "Departamento: " << cadastro[i].Departamento << endl
             << "Preco: R$" << fixed << setprecision(2) << cadastro[i].Preco << endl
             << "Autor(a): " << cadastro[i].Autor << endl
             << "Editora: " << cadastro[i].Editora << endl
             << "Quantidade em estoque: " << cadastro[i].Quantidade << endl
             << "Descricao: " << cadastro[i].Descricao << endl;
        if (cadastro[i].Volume == 0)
        {
            cout << "Volume unico" << endl
                 << endl;
        }
        else
        {
            cout << "Volume: " << cadastro[i].Volume << endl
                 << endl;
        }
    }
    else if (posicao == -1)
    {
        cout << endl
             << "Livro nao encontrado" << endl
             << endl;
    }
}

///////////////////////////////////////BUSCA POR DEPARTAMENTO/////////////////////////////////

void buscaDepartamento(livro *cadastro, int tamanho)
{
    string buscado;
    cout << "Digite o departamento: ";
    cin.ignore();
    getline(cin, buscado);

    int posicao = -1;
    bool imprimir = false;

    for (int i = 0; i < tamanho; i++)
    {
        if (buscado == cadastro[i].Departamento)
        {
            posicao = i;
            imprimir = true;
        }
        if (posicao == i)
        {
            cout << endl
                 << "Nome: " << cadastro[i].Nome << endl
                 << "Numero de paginas: " << cadastro[i].NumeroPaginas << endl
                 << "Departamento: " << cadastro[i].Departamento << endl
                 << "Preco: R$" << fixed << setprecision(2) << cadastro[i].Preco << endl
                 << "Autor(a): " << cadastro[i].Autor << endl
                 << "Editora: " << cadastro[i].Editora << endl
                 << "Quantidade em estoque: " << cadastro[i].Quantidade << endl
                 << "Descricao: " << cadastro[i].Descricao << endl;
            if (cadastro[i].Volume == 0)
            {
                cout << "Volume unico" << endl;
            }
            else
            {
                cout << "Volume: " << cadastro[i].Volume << endl;
            }
        }
    }

    if (imprimir)
    {
        cout << endl
             << "Esses sao todos os livros do nosso departamento de " << buscado << endl
             << endl;
    }

    if (posicao == -1)
    {
        cout << endl
             << "Departamento nao encontrado" << endl
             << endl;
    }
}

///////////////////////////////////////////INSERIR////////////////////////////////////////////

void Insercao(livro **cadastro, int &tamanho, int &capacidade)
{
    bool NaoRemovido = true;
    bool preencheuRemovido = false;

    for (int i = 0; i < tamanho; i++)
    {
        if ((*cadastro)[i].Nome == "Removido" and !preencheuRemovido)
        {
            cout << "Digite o nome do livro que deseja cadastrar: ";
            cin.ignore();
            getline(cin, (*cadastro)[i].Nome);
            cout << "Digite o numero de paginas do livro que deseja cadastrar: ";
            cin >> (*cadastro)[i].NumeroPaginas;
            cout << "Digite o departamento do livro que deseja cadastrar: ";
            cin.ignore();
            getline(cin, (*cadastro)[i].Departamento);
            cout << "Digite o preco do livro que deseja cadastrar: ";
            cin >> (*cadastro)[i].Preco;
            cout << "Digite o(a) autor(a) do livro que deseja cadastrar: ";
            cin.ignore();
            getline(cin, (*cadastro)[i].Autor);
            cout << "Digite a editora do livro que deseja cadastrar: ";
            getline(cin, (*cadastro)[i].Editora);
            cout << "Digite a quantidade em estoque do livro que deseja cadastrar: ";
            cin >> (*cadastro)[i].Quantidade;
            cout << "Digite a descricao do livro que deseja cadastrar: ";
            cin.ignore();
            getline(cin, (*cadastro)[i].Descricao);
            cout << "Digite o volume do livro que deseja cadastrar, caso seja um livro unico digite 0: ";
            cin >> (*cadastro)[i].Volume;
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
            copy(*cadastro, *cadastro + tamanho, novo);
            capacidade += 1;
            delete[] *cadastro;
            *cadastro = novo;
        }

        cout << "Digite o nome do livro que deseja cadastrar: ";
        cin.ignore();
        getline(cin, (*cadastro)[tamanho].Nome);
        cout << "Digite o numero de paginas do livro que deseja cadastrar: ";
        cin >> (*cadastro)[tamanho].NumeroPaginas;
        cout << "Digite o departamento do livro que deseja cadastrar: ";
        cin.ignore();
        getline(cin, (*cadastro)[tamanho].Departamento);
        cout << "Digite o preco do livro que deseja cadastrar: ";
        cin >> (*cadastro)[tamanho].Preco;
        cout << "Digite o(a) autor(a) do livro que deseja cadastrar: ";
        cin.ignore();
        getline(cin, (*cadastro)[tamanho].Autor);
        cout << "Digite a editora do livro que deseja cadastrar: ";
        getline(cin, (*cadastro)[tamanho].Editora);
        cout << "Digite a quantidade em estoque do livro que deseja cadastrar: ";
        cin >> (*cadastro)[tamanho].Quantidade;
        cout << "Digite a descricao do livro que deseja cadastrar: ";
        cin.ignore();
        getline(cin, (*cadastro)[tamanho].Descricao);
        cout << "Digite o volume do livro que deseja cadastrar, caso seja um livro unico digite 0: ";
        cin >> (*cadastro)[tamanho].Volume;

        cout << endl
             << "Insercao feita com sucesso!\n"
             << endl;

        tamanho++;
    }
}

///////////////////////////////////////////REMOVER////////////////////////////////////////////

void Remocao(livro *cadastro, int tamanho)
{
    string buscado;
    cout << "Digite o nome do livro que deseja remover: ";
    cin.ignore();
    getline(cin, buscado);

    int posicao = -1;
    int i = 0;
    bool naoAchou = true;

    while (i < tamanho and naoAchou)
    {
        if (buscado == cadastro[i].Nome)
        {
            naoAchou = false;
            posicao = i;
        }
        else
        {
            i++;
        }
    }

    if (posicao == i)
    {
        cadastro[i].Nome = "Removido";
        cadastro[i].NumeroPaginas = 0;
        cadastro[i].Departamento = "Removido";
        cadastro[i].Preco = 0;
        cadastro[i].Autor = "Removido";
        cadastro[i].Editora = "Removido";
        cadastro[i].Quantidade = 0;
        cadastro[i].Volume = 0;
        cadastro[i].Descricao = "Removido";

        cout << "\nRemocao feita com sucesso!\n"
             << endl;
    }
    else if (posicao == -1)
    {
        cout << "\nLivro nao encontrado\n"
             << endl;
    }
}

///////////////////////////////////////////EDITAR////////////////////////////////////////////

void Edicao(livro *cadastro, int tamanho)
{
    string buscado;
    cout << "Digite o nome do livro que deseja editar: ";
    cin.ignore();
    getline(cin, buscado);

    bool naoAchou = true;
    int i = 0;

    while (i < tamanho and naoAchou)
    {
        if (buscado == cadastro[i].Nome)
        {
            naoAchou = false;
        }
        else
        {
            i++;
        }
    }

    if (!naoAchou)
    {
        cout << "O que deseja editar? \n 1 - preco \n 2 - quantidade do livro \n 3 - descricao" << endl;
        int resposta;
        cin >> resposta;

        if (resposta == 1)
        {
            cout << "Digite o novo preco: ";
            float Preco;
            cin >> Preco;
            cadastro[i].Preco = Preco;
            cout << endl
                 << "Edicao concluida" << endl
                 << endl;
        }
        else if (resposta == 2)
        {
            cout << "Digite a nova quantidade: ";
            int Quantidade;
            cin >> Quantidade;
            cadastro[i].Quantidade = Quantidade;
            cout << endl
                 << "Edicao concluida" << endl
                 << endl;
        }
        else if (resposta == 3)
        {
            cout << "Digite a nova descricao: ";
            string Descricao;
            cin.ignore();
            getline(cin, Descricao);
            cadastro[i].Descricao = Descricao;
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

void Exibicao(livro *cadastro, int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        cout << "Nome: " << cadastro[i].Nome << endl;
        cout << "Numero de paginas: " << cadastro[i].NumeroPaginas << endl;
        cout << "Departamento: " << cadastro[i].Departamento << endl;
        cout << "Preco: R$" << fixed << setprecision(2) << cadastro[i].Preco << endl;
        cout << "Autor(a): " << cadastro[i].Autor << endl;
        cout << "Editora: " << cadastro[i].Editora << endl;
        cout << "Quantidade em estoque: " << cadastro[i].Quantidade << endl;
        cout << "Descricao: " << cadastro[i].Descricao << endl;
        if (cadastro[i].Volume == 0)
        {
            cout << "Volume unico" << endl
                 << endl;
        }
        else
        {
            cout << "Volume: " << cadastro[i].Volume << endl
                 << endl;
        }
    }

    cout << "Esses sao todos os livros cadastrados em nosso sistema!\n"
         << endl;
}

///////////////////////////////////////////CARRINHO///////////////////////////////////////////
void Carrinho(livro *cadastro, int tamanho)
{
    string buscado;
    float Preco = 0.00;
    bool continua = true;
    while (continua)
    {
        cout << "Digite o nome do livro: ";
        cin.ignore();
        getline(cin, buscado);
        int posicao = -1;
        int i = 0;
        bool naoAchou = true;

        while (i < tamanho and naoAchou)
        {
            if (buscado == cadastro[i].Nome)
            {
                naoAchou = false;
                posicao = i;
            }
            else
                i++;
        }

        if (posicao == i)
        {
            cout << endl
                 << "Nome: " << cadastro[i].Nome << endl
                 << "Preco: R$" << fixed << setprecision(2) << cadastro[i].Preco << endl
                 << "Quantidade em estoque: " << cadastro[i].Quantidade << endl
                 << "Descricao: " << cadastro[i].Descricao << endl;
            if (cadastro[i].Volume == 0)
            {
                cout << "Volume unico" << endl
                     << endl;
            }
            else
            {
                cout << "Volume: " << cadastro[i].Volume << endl
                     << endl;
            }
            cout << "Tem certeza que deseja adicionar esse livro ao seu carrinho? \n 1 - Sim \n 2 - Nao" << endl;
            int resposta;
            cin >> resposta;

            if (resposta == 1)
            {
                Preco += cadastro[i].Preco;
            }
        }
        else if (posicao == -1)
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

void ImprimirTrecho(livro *cadastro, int tamanho)
{

    int posicaoInicial, posicaoFinal, Aux;

    cout << " Atualmente temos " << tamanho << " livros cadastrados em nosso sistema!" << endl
         << endl
         << "Digite a posicao inicial e a final do trecho que voce deseja imprimir:" << endl
         << "Posicao inicial: ";
    cin >> posicaoInicial;
    cout << "Posicao final: ";
    cin >> posicaoFinal;
    cout << endl;

    Aux = posicaoInicial;

    posicaoInicial -= 1;

    while (posicaoInicial < posicaoFinal)
    {
        cout << posicaoInicial + 1 << endl;
        cout << "Nome: " << cadastro[posicaoInicial].Nome << endl;
        cout << "Numero de paginas: " << cadastro[posicaoInicial].NumeroPaginas << endl;
        cout << "Departamento: " << cadastro[posicaoInicial].Departamento << endl;
        cout << "Preco: R$" << fixed << setprecision(2) << cadastro[posicaoInicial].Preco << endl;
        cout << "Autor(a): " << cadastro[posicaoInicial].Autor << endl;
        cout << "Editora: " << cadastro[posicaoInicial].Editora << endl;
        cout << "Quantidade em estoque: " << cadastro[posicaoInicial].Quantidade << endl;
        cout << "Descricao: " << cadastro[posicaoInicial].Descricao << endl;
        if (cadastro[posicaoInicial].Volume == 0)
        {
            cout << "Volume unico" << endl
                 << endl;
        }
        else
        {
            cout << "Volume: " << cadastro[posicaoInicial].Volume << endl
                 << endl;
        }
        posicaoInicial++;
    }

    cout << "Esses sao todos os livros de acordo com o trecho escolhido de " << Aux << " a " << posicaoFinal << "!" << endl
         << endl;
}

///////////////////////////////////////////PREENCHER O ARQUIVO DE SAIDA///////////////////////////////////////////

void preencherArquivoSaida(livro *cadastro, string cabecalho, int tamanho, bool &continua)
{
    ofstream arquivoremocao("baselivraria2.csv");

    for (int i = 0; i < tamanho; i++)
    {
        if (cadastro[i].Nome == "Removido")
        {
            tamanho -= 1;
        }
    }

    arquivoremocao << cabecalho << endl;
    arquivoremocao << tamanho << endl;

    for (int i = 0; i < tamanho; i++)
    {
        if (cadastro[i].Nome == "Removido")
        {
            arquivoremocao << cadastro[i + 1].Nome << ','
                           << cadastro[i + 1].NumeroPaginas << ','
                           << cadastro[i + 1].Departamento << ','
                           << fixed << setprecision(2) << cadastro[i + 1].Preco << ','
                           << cadastro[i + 1].Autor << ','
                           << cadastro[i + 1].Editora << ','
                           << cadastro[i + 1].Quantidade << ','
                           << cadastro[i + 1].Volume << ','
                           << cadastro[i + 1].Descricao << '.' << endl;
            i += 1;
            tamanho += 1;
        }
        else
        {
            arquivoremocao << cadastro[i].Nome << ','
                           << cadastro[i].NumeroPaginas << ','
                           << cadastro[i].Departamento << ','
                           << fixed << setprecision(2) << cadastro[i].Preco << ','
                           << cadastro[i].Autor << ','
                           << cadastro[i].Editora << ','
                           << cadastro[i].Quantidade << ','
                           << cadastro[i].Volume << ','
                           << cadastro[i].Descricao << '.' << endl;
        }
    }
    continua = false;
}

///////////////////////////////////////////////Função para converter um arquivo CSV para binário//////////////////////////////////////////////////////////////////

// void converterCSVParaBinario(const string &arquivoCSV, const string &arquivoBinario)
// {
//     ifstream arquivoEntrada(arquivoCSV);
//     if (!arquivoEntrada.is_open())
//     {
//         cerr << "Erro ao abrir o arquivo CSV." << endl;
//         return;
//     }

//     string linha;
//     getline(arquivoEntrada, linha); // Ignorar o cabeçalho do CSV

//     // Contar o número de registros no arquivo CSV
//     int numRegistros = 0;
//     while (getline(arquivoEntrada, linha))
//     {
//         numRegistros++;
//     }

//     // Voltar ao início do arquivo CSV
//     arquivoEntrada.clear();
//     arquivoEntrada.seekg(0, ios::beg);

//     // Ignorar o cabeçalho do CSV novamente
//     getline(arquivoEntrada, linha);

//     // Criar um array de registros com o tamanho do número de registros
//     livro *cadastro = new livro[numRegistros];

//     // Ler o arquivo CSV linha por linha
//     int registroAtual = 0;
//     while (getline(arquivoEntrada, linha))
//     {
//         size_t posInicio = 0;
//         size_t posFim = linha.find(',');

//         // Processar o valor do campo "nome"
//         cadastro[registroAtual].Nome = linha.substr(posInicio, posFim - posInicio);

//         posInicio = posFim + 1;
//         posFim = linha.find(',', posInicio);

//         // Processar o valor do campo "paginas"
//         cadastro[registroAtual].NumeroPaginas = stoi(linha.substr(posInicio, posFim - posInicio));

//         posInicio = posFim + 1;
//         posFim = linha.find(',', posInicio);

//         // Processar o valor do campo "departamento"
//         cadastro[registroAtual].Departamento = linha.substr(posInicio, posFim - posInicio);

//         posInicio = posFim + 1;
//         posFim = linha.find(',', posInicio);

//         // Processar o valor do campo "preco"
//         cadastro[registroAtual].Preco = stod(linha.substr(posInicio, posFim - posInicio));

//         posInicio = posFim + 1;
//         posFim = linha.find(',', posInicio);

//         // Processar o valor do campo "autor"
//         cadastro[registroAtual].Autor = linha.substr(posInicio, posFim - posInicio);

//         posInicio = posFim + 1;
//         posFim = linha.find(',', posInicio);

//         // Processar o valor do campo "editora"
//         cadastro[registroAtual].Editora = linha.substr(posInicio, posFim - posInicio);

//         posInicio = posFim + 1;
//         posFim = linha.find(',', posInicio);

//         // Processar o valor do campo "quantidade"
//         cadastro[registroAtual].Quantidade = stoi(linha.substr(posInicio, posFim - posInicio));

//         posInicio = posFim + 1;
//         posFim = linha.find(',', posInicio);

//         // Processar o valor do campo "volume"
//         cadastro[registroAtual].Volume = stoi(linha.substr(posInicio, posFim - posInicio));

//         posInicio = posFim + 1;

//         // Processar o valor do campo "descricao"
//         cadastro[registroAtual].Descricao = linha.substr(posInicio);

//         registroAtual++;
//     }

//     arquivoEntrada.close();

//     // Abrir o arquivo binário para escrita
//     ofstream arquivoSaida(arquivoBinario, ios::binary);
//     if (!arquivoSaida.is_open())
//     {
//         cerr << "Erro ao abrir o arquivo binário." << endl;
//         delete[] cadastro; // Liberar a memória alocada
//         return;
//     }

//     // Escrever os registros no arquivo binário
//     arquivoSaida.write(reinterpret_cast<const char *>(cadastro), numRegistros * sizeof(livro));

//     arquivoSaida.close();

//     delete[] cadastro; // Liberar a memória alocada

//     cout << "Arquivo binário criado com sucesso." << endl;
// }

/////////////////////////////////////////PRINCIPAL///////////////////////////////////////////////

int main()
{

    /////////////////////////////////////////PREENCHER O VETOR///////////////////////////////////////////////

    int tamanho, capacidade;
    string cabecalho;
    string buscado;

    ifstream arquivoentrada("baselivraria.csv");

    if (not(arquivoentrada))
    {
        cout << endl
             << "Erro: Nao foi possivel abrir o arquivo, tente novamente." << endl
             << endl;
    }
    else
    {
        getline(arquivoentrada, cabecalho);
        arquivoentrada >> tamanho;

        livro *cadastro;

        capacidade = tamanho;

        cadastro = new livro[capacidade];

        preencherEntrada(arquivoentrada, cadastro, tamanho);

        // string arquivoCSV = "baselivraria.csv";
        // string arquivoBinario = "baselivraria.bin";

        // converterCSVParaBinario(arquivoCSV, arquivoBinario);

        cout << "===============================================" << endl
             << "BEM-VINDO(A) AO SISTEMA DE CADASTRO DA LIVRARIA" << endl
             << "===============================================" << endl;

        bool ContinuaOrdenacao = true;
        while (ContinuaOrdenacao)
        {

            cout << "Escolha por qual parametro voce deseja ordenar nosso cadastro de livros: \n 1 - Pelo nome do livro \n 2 - Pelo preco do livro" << endl;

            int EscolhaOrdenacao;

            cin >> EscolhaOrdenacao;

            if (EscolhaOrdenacao == 1)
            {
                OrdenarPorNome(cadastro, tamanho);
                cout << endl
                     << "O sistema esta ordenado pelo nome dos livros!" << endl
                     << endl;
                ContinuaOrdenacao = false;
            }
            else if (EscolhaOrdenacao == 2)
            {
                OrdenarPorPreco(cadastro, tamanho);
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

        bool continua = true;
        while (continua)
        {

            cout << "Escolha qual acao deseja realizar: \n 1 - Busca \n 2 - Inserir \n 3 - Remover \n 4 - Editar \n 5 - Exibir todos os livros \n 6 - Montar um carrinho \n 7- Imprimir trecho do cadastro" << endl;

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
                    buscaNome(cadastro, tamanho);
                }
                else if (resposta == 2)
                {
                    buscaDepartamento(cadastro, tamanho);
                }
                else
                {
                    cout << "\nComando Invalido\n"
                         << endl;
                }

                break;

                ////////////////////////////////////////INSERIR///////////////////////////////////////////////

            case 2:
                cout << "------------------------" << endl
                     << "Sua escolha foi: Inserir" << endl
                     << "------------------------" << endl;

                Insercao(&cadastro, tamanho, capacidade);

                OrdenarPorNome(cadastro, tamanho);

                break;

                ////////////////////////////////////////REMOVER///////////////////////////////////////////////

            case 3:
                cout << "------------------------" << endl
                     << "Sua escolha foi: Remover" << endl
                     << "------------------------" << endl;

                Remocao(cadastro, tamanho);

                OrdenarPorNome(cadastro, tamanho);

                break;

                ////////////////////////////////////////EDITAR///////////////////////////////////////////////

            case 4:
                cout << "--------------------------" << endl
                     << "Sua escolha foi: Editar" << endl
                     << "--------------------------" << endl;

                Edicao(cadastro, tamanho);

                OrdenarPorNome(cadastro, tamanho);

                break;

                ////////////////////////////////////////EXIBIR TODOS OS LIVROS///////////////////////////////////////////////

            case 5:
                cout << "---------------------------------------" << endl
                     << "Sua escolha foi: Exibir todos os livros" << endl
                     << "---------------------------------------" << endl;

                Exibicao(cadastro, tamanho);

                break;

                ////////////////////////////////////////MONTAR UM CARRINHO///////////////////////////////////////////////

            case 6:
                cout << "-----------------------------------" << endl
                     << "Sua escolha foi: Montar um carrinho" << endl
                     << "-----------------------------------" << endl;

                Carrinho(cadastro, tamanho);

                break;

                ////////////////////////////////////////IMPRIMIR TRECHO DO CADASTRO///////////////////////////////////////////////

            case 7:
                cout << "-----------------------------------" << endl
                     << "Sua escolha foi: Imprimir trecho do cadastro" << endl
                     << "-----------------------------------" << endl;

                ImprimirTrecho(cadastro, tamanho);

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

                cout << "Deseja fazer outra acao?: \n Se sim: digite 1 \n Se nao: digite 2" << endl;
                int novaAcao;
                cin >> novaAcao;
                if (novaAcao == 1)
                {
                    continua = true;
                    acao = false;
                }
                else if (novaAcao == 2)
                {
                    preencherArquivoSaida(cadastro, cabecalho, tamanho, continua);
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
        }
        cout << "===============================================================" << endl;
        cout << "Agradecemos por utilizar o sistema da livraria \n Volte sempre!" << endl;
        cout << "===============================================================" << endl;
    }

    return 0;
}