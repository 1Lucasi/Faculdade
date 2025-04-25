#include <stdio.h>
#include <stdlib.h>

#define TAM 15

typedef struct {
    int dia, mes, ano;
} Data;

typedef struct {
    char rua[50];
    char bairro[50];
    char cidade[50];
    char pais[50];
    int num, cep;
} Endereco;

typedef struct {
    int codigo;
    Data dataAss;
    char cargo[50];
    float salario;
} Contrato;

typedef struct {
    char nome[50];
    int cpf;
    Data dataNas;
    Endereco end;
    Contrato contr;
} Pessoa;

// ---------------- Funções de Impressão ----------------

void imprimirData(Data d) {
    printf("%02d/%02d/%04d\n", d.dia, d.mes, d.ano);
}

void imprimirEndereco(Endereco end) {
    printf("\tEndereco:\n");
    printf("\t\tRua: %s", end.rua);
    printf("\t\tBairro: %s", end.bairro);
    printf("\t\tCidade: %s", end.cidade);
    printf("\t\tPais: %s", end.pais);
    printf("\t\tNumero: %d\n", end.num);
    printf("\t\tCEP: %d\n", end.cep);
}

void imprimirContrato(Contrato c) {
    printf("\tContrato %d:\n", c.codigo);
    printf("\t\tCargo: %s", c.cargo);
    printf("\t\tSalario: R$%.2f\n", c.salario);
    printf("\t\tData de assinatura: ");
    imprimirData(c.dataAss);
}

void imprimirPessoa(Pessoa p) {
    printf("\n\tNome: %s", p.nome);
    printf("\tCpf: %d\n", p.cpf);
    printf("\tData de nascimento: ");
    imprimirData(p.dataNas);
    imprimirEndereco(p.end);
    imprimirContrato(p.contr);
}

// ---------------- Funções de Leitura ----------------

Data lerData(char texto[]) {
    Data d;
    printf("%s", texto);
    scanf("%d%d%d", &d.dia, &d.mes, &d.ano);
    getchar(); // limpa o ENTER do teclado
    return d;
}

Endereco lerEndereco() {
    Endereco end;
    char buffer[100];

    printf("\nRua: ");
    fgets(end.rua, sizeof(end.rua), stdin);

    printf("Bairro: ");
    fgets(end.bairro, sizeof(end.bairro), stdin);

    printf("Cidade: ");
    fgets(end.cidade, sizeof(end.cidade), stdin);

    printf("Pais: ");
    fgets(end.pais, sizeof(end.pais), stdin);

    printf("Numero: ");
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, "%d", &end.num);

    printf("CEP: ");
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, "%d", &end.cep);

    return end;
}

Contrato lerContrato() {
    Contrato c;
    char buffer[100];

    printf("\nCodigo do contrato: ");
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, "%d", &c.codigo);

    c.dataAss = lerData("Digite a data de assinatura do contrato (dd mm aaaa): ");

    printf("Cargo: ");
    fgets(c.cargo, sizeof(c.cargo), stdin);

    printf("Salario: R$");
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, "%f", &c.salario);

    return c;
}

Pessoa lerPessoa() {
    Pessoa p;
    char buffer[100];

    printf("\nNome: ");
    fgets(p.nome, sizeof(p.nome), stdin);

    printf("Cpf: ");
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, "%d", &p.cpf);

    p.dataNas = lerData("Digite a data de nascimento (dd mm aaaa): ");

    p.contr = lerContrato();

    p.end = lerEndereco();

    return p;
}

// ---------------- Funções da Tabela ----------------

void inicializarTabela(Pessoa t[]) {
    for (int i = 0; i < TAM; i++) {
        t[i].cpf = 0;
    }
}

// Função de inserção sequencial a partir da posição 0
void inserirSequencial(Pessoa t[]) {
    Pessoa p = lerPessoa();
    int id = 0;
    while (id < TAM && t[id].cpf != 0) { // Encontra a próxima posição livre a partir do 0
        id++;
    }
    if (id < TAM) {
        t[id] = p;
    } else {
        printf("Tabela cheia! Não é possível inserir mais registros.\n");
    }
}

// Função de busca ajustada para uma tabela sequencial
Pessoa* buscaSequencial(Pessoa t[], int chave) {
    for (int id = 0; id < TAM; id++) {
        if (t[id].cpf == chave) {
            printf("\nIndice encontrado: %d\n", id);
            return &t[id];
        }
    }
    return NULL;
}

void imprimir(Pessoa t[]) {
    for (int i = 0; i < TAM; i++) {
        printf("%d\n", i);
        if (t[i].cpf != 0)
            imprimirPessoa(t[i]);
        printf("----------------------\n");
    }
}

// ---------------- Main ----------------

int main() {
    int opc, valor;
    Pessoa* buscar;
    Pessoa tabela[TAM];

    inicializarTabela(tabela);

    do {
        printf("\n\n====================================\n");
        printf("        Sistema de Cadastro         \n");
        printf("====================================\n");
        printf("  0 - Sair\n");
        printf("  1 - Inserir Novo Registro\n");
        printf("  2 - Buscar por CPF\n");
        printf("  3 - Imprimir Registros\n");
        printf("====================================\n");
        printf("Digite sua opcao: ");
        scanf("%d", &opc);
        getchar(); // Limpa o ENTER depois de scanf!

        switch (opc) {
        case 1:
            printf("\n====================================\n");
            printf("     Inserir Novo Registro         \n");
            printf("====================================\n");
            printf("Preencha as informacoes solicitadas:\n\n");
            inserirSequencial(tabela);
            printf("\n------------------------------------\n");
            printf("Registro inserido com sucesso!\n");
            printf("------------------------------------\n");
            break;
        case 2:
            printf("\n====================================\n");
            printf("         Buscar por CPF            \n");
            printf("====================================\n");
            printf("Qual CPF deseja buscar? ");
            scanf("%d", &valor);
            getchar();
            buscar = buscaSequencial(tabela, valor);
            if (buscar) {
                printf("\n------------------------------------\n");
                printf("CPF encontrado:\n");
                imprimirPessoa(*buscar);
                printf("------------------------------------\n");
            } else {
                printf("\n------------------------------------\n");
                printf("CPF nao encontrado!\n");
                printf("------------------------------------\n");
            }
            break;
        case 3:
            printf("\n====================================\n");
            printf("     Lista de Registros            \n");
            printf("====================================\n");
            imprimir(tabela);
            break;
        case 0:
            printf("\n====================================\n");
            printf("     Encerrando Programa...        \n");
            printf("====================================\n");
            break;
        default:
            printf("\n------------------------------------\n");
            printf("Opcao Invalida! Tente novamente.\n");
            printf("------------------------------------\n");
            break;
        }
    } while (opc != 0);

    return 0;
}