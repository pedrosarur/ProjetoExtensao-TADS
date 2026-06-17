#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include <time.h>

#define  NUM_MAX_CAD 1024
#define NUM_MAX_NOME 101

/*-------------------- STRUCTS -----------------------*/
typedef struct{
    int id_gato;
    int ocupado;
    int microchip;
    char nome_gato[NUM_MAX_NOME];
    char sexo_gato;
    char pelagem[101];
    char lar_temporario[101];
    int castrado;
    int vacina;
    char vacina_pendente[256];
    int status;
    char data_cadastro[11];
    char data_adocao[11];
    int id_adotante; //util para facilitar o banco
}Gato; //Struct sobre cadastro do gato

typedef struct{
    int id_tutor;
    int ocupado;
    char nome_tutor[NUM_MAX_NOME];
    char cpf[13];
    int idade;
    char email[101];
    char telefone[15];
}Tutor; //Struct sobre cadastro do adotante

/*-------------------- VARIAVEIS UNIVERSAIS------------*/
Tutor tutores[NUM_MAX_CAD] = {0};
int qtd_tutores = 0;

Gato gatos[NUM_MAX_CAD] = {0};
int qtd_gatos = 0;

/*----------------- FUNCOES PARA CADASTRO ---------------------*/

void cadastrar_gato();
void cadastrar_tutor();

/*----------- FUNCOES PARA LEITURA -----------------*/

void leia_string(); //verificação universal de string --- nome, pelagem, lar
void leia_sexo();
void leia_booleano(); // verifica universal de booleano - vacina, castrado
void leia_pendencias(); //função para escrever as pendências e verificação
void leia_cpf(); //função para ler e verificar o cpf
void leia_email(); // função para ler e verificar email
void leia_telefone(); // função para ler e verificar o telefone
void pausar();
int leia_adocao(); // função de adoção

/*---------- FUNCOES DE CONSULTA ----------*/
void mostrar_gatos_adotados();
void mostrar_gatos_disponiveis();
void mostrar_todos_gatos();

/*----------- FUNCOES DE EXCLUSAO -------------*/
void excluir_gato();

/*------------------- TELAS -------------*/

//tela de menu
int tela_menu_opcoes()
{
    //guarda a opção escolhida pelo usuário
    int opcao;

     //mostra a Tela com o "Menu de Opções"
    system("cls");
    printf(" ===============================");
    printf("\n SISTEMA DE ADOÇÃO MIAUADOTA");
    printf("\n ===============================");

    printf("\n 1 - Cadastar Novo Gato");
    printf("\n 2 - Cadastar Tutor e Adotar Gato");
    printf("\n 3 - Consultar Registros");
    printf("\n 4 - Alterar ou Excluir Registros");
    printf("\n 0 - Sair do Programa");

    //faz a leitura da opção escolhida
    printf("\n\n Escolha uma opção: ");
    int erro = scanf("%d", &opcao);

    //verifica se houve uma falha na leitura do scanf
    if(erro != 1) {
        //limpa o buffer do tecaldo (windows)
        fflush(stdin);
        //como teve uma falha na leitura, marca uma opção inválida
        opcao = -1;
    }

    //retorna a opção escolhida
    return opcao;
}

int tela_consultas()
{
    int opcao;

    system("cls");

    printf("--- CONSULTA DE GATOS ---");
    printf("\n 1 - Ver Todos os Gatos");
    printf("\n 2 - Ver Apenas Disponiveis");
    printf("\n 3 - Ver Apenas Adotados");
    printf("\n 0 - Voltar ao Menu Principal");

    //faz a leitura da opção escolhida
    printf("\n\n Escolha uma opção: ");
    int erro = scanf("%d", &opcao);

    //verifica se houve uma falha na leitura do scanf
    if(erro != 1) {
        //limpa o buffer do tecaldo (windows)
        fflush(stdin);
        //como teve uma falha na leitura, marca uma opção inválida
        opcao = -1;
    }

    //retorna a opção escolhida
    return opcao;
}

int tela_alterar_registros() //tela feita para alteracao de dados
{
    int opcao;

    system("cls");

    printf("--- ALTERAR REGISTROS ---\n");
    printf("\n 1 - Excluir Registros dos Gatos");
    printf("\n 2 - Excluir Registros dos Tutores");
    printf("\n 3 - Editar Registros dos Tatos");
    printf("\n 4 - Editar Registros dos Tutores");
    printf("\n 0 - Voltar ao Menu Principal");

    //faz a leitura da opção escolhida
    printf("\n\n Escolha uma opção: ");
    int erro = scanf("%d", &opcao);

    //verifica se houve uma falha na leitura do scanf
    if(erro != 1) {
        //limpa o buffer do tecaldo (windows)
        fflush(stdin);
        //como teve uma falha na leitura, marca uma opção inválida
        opcao = -1;
    }

    //retorna a opção escolhida
    return opcao;
}

int main()
{
    //coloca o idioma como português brasil
    setlocale(LC_ALL, "Portuguese");
    system("chcp 1252 > null");

    int opcao, opcao_consulta, opcao_registro;

    do{
        // 1. Mostra o menu e captura a opção escolhida pelo usuário
        opcao = tela_menu_opcoes();

        // 2. Avalia a opção escolhida
        switch (opcao){
            case 1:
                cadastrar_gato();
                pausar();
                break;

            case 2:
                cadastrar_tutor();
                pausar();
                break;

            case 3:
                opcao_consulta = tela_consultas();

                switch(opcao_consulta){
                    case 1:
                        printf("--- RESULTADO DA BUSCA (TODOS) ---\n");

                        mostrar_todos_gatos();
                        pausar();
                        break;

                    case 2:
                        printf("--- RESULTADO DA BUSCA (DISPONIVEL) ---\n");

                        mostrar_gatos_disponiveis();
                        pausar();
                        break;

                    case 3:
                        printf("--- RESULTADO DA BUSCA (ADOTADO) ---\n");

                        mostrar_gatos_adotados();
                        pausar();
                        break;
                }

                break; // fim do case secundario e voltando pro switch case principal

            case 4:
                opcao_registro = tela_alterar_registros();

                switch(opcao_registro){
                    case 1:
                        excluir_gato();
                        pausar();
                }

                break;

            case 0:
                printf("\nSaindo do programa... Obrigado!\n");
                break;

            default:
                printf("\nERRO: Opção inválida! Tente novamente.\n");
                system("pause");
                break;
        }

    } while (opcao != 0); // O loop continua enquanto a opção for diferente de 0

    return 0;
}

/*------------------- FUNÇÕES DE LEITURA --------------------*/

void pausar(){
    printf("\nPressione ENTER para voltar ao menu...");
    getchar();
    getchar();
}

void leia_string(char *str, char mensagem[]){ //função universarl para ler strings
    int erro;

    do{
        erro = 0; //sem erros

        printf("%s", mensagem);
        scanf(" %99[^\n]", str);

        fflush(stdin); //limpa o buffer do teclado

        if(strlen(str) > 100){ //verificação do tamanho da string
            erro = 1;
            printf("\n ERRO: Máximo de 100 caracteres!");
        }
        if(strlen(str) < 3){
            erro = 1;
            printf("\n ERRO: Mínimo de 3 caracteres!");
        }

    }while(erro == 1);
}

void leia_sexo(char *sexo){ //função universal para ler o sexo
    int erro;

    do{
        erro = 0; //sem erros
        char strSexo[3];

        printf("\n Esolha o sexo (F/M): ");
        scanf(" %2[^\n]", strSexo);

        fflush(stdin); //limpa o buffer do teclado

        if(strlen(strSexo) == 1 ){  //verificação dos caracteres F ou M
            *sexo = toupper(strSexo[0]);
        }
        else{
            erro = 1;
        }

        if ((*sexo != 'M' && *sexo != 'F') || erro == 1){
            erro = 1;
            printf("\n ERRO: São apenas disponíveis os caracteres 'M' ou 'F'");
        }

    }while(erro == 1);
}

void leia_booleano(int *boolean, char mensagem[]){ //função universal para verificar 1 ou 0, ou seja, verdadeiro ou falso
    int erro;

    do{
        erro = 0; //sem erros

        printf("\n %s \n 1 - Sim\n 0 - Não\n Escolha: ", mensagem);
        scanf("%d", boolean);


        if (*boolean != 0 && *boolean != 1){
            erro = 1;
            printf("\n ERRO: São apenas disponíveis os números 1 e 0");
        }

    }while(erro == 1);
}

void leia_pendencias(char *str){ //função para ler as pendencias de vacinação
    int erro;

    do{
        erro = 0; //sem erros

        printf("\n Pendencias da vacina: ");
        scanf(" %255[^\n]", str);

        fflush(stdin); //limpa o buffer do teclado

        if(strlen(str) > 254){ //verificação do tamanho da string
            erro = 1;
            printf("\n ERRO: Máximo de 254 caracteres!");
        }
    }while(erro == 1);
}

void leia_cpf(char *str){ //validacao e leitura do cpf
    int erro;

    do
    {
        erro = 0; //sem erros

        printf("\nDigite o CPF: ");
        scanf(" %12[^\n]", str);

        fflush(stdin); //limpa o buffer do teclado

        if(strlen(str) != 11) //verifica se o cpf tem 11 digitos
        {
            erro = 1;
            printf("ERRO: O CPF deve possuir 11 (onze) dígitos!\n");
        }

    }while(erro == 1);
}

void leia_idade (int *idade){
    int erro;

    do
    {
        erro = 0; //sem erros

        printf("\nDigite a idade: ");
        scanf(" %d", idade);

        fflush(stdin); //limpa o buffer do teclado

        if(*idade < 18) //verifica se é maior de 18
        {
            erro = 1;
            printf("ERRO: O tutor deve ser maior de 18 anos!\n");
        }

    }while(erro == 1);

}

void leia_email(char *email){ //função para ler e validar o email
    int erro;
    int arroba;

    do{
        erro = 0; //sem erros
        arroba = 0; //verificar arroba

        printf("\n Email: ");
        scanf(" %100[^\n]", email);

        fflush(stdin); //limpa o buffer do teclado

        if(strlen(email) > 100){ //verificação do tamanho da string
            erro = 1;
            printf("\n ERRO: Máximo de 100 caracteres!");
        }

        for(int i = 0; email[i] != '\0'; i++){ //for para verificar se o email cadastrado possui o @
            if(email[i] == '@'){
                arroba = 1;
                break;
            }
        }

        if(arroba == 0){ // if apenar para colocar o erro com uma mensagem diferente
            erro = 1;
            printf("\n ERRO: Email precisa ter @!");
        }

    }while(erro == 1);
}

void leia_telefone(char *numero){ //função para ler e verificar o telefone
    int erro;

    do
    {
        erro = 0; //sem erros

        printf("\nDigite o Telefone: ");
        scanf(" %14[^\n]", numero);

        fflush(stdin); //limpa o buffer do teclado

        if(strlen(numero) > 14){ //verificação do tamanho da string numero
            erro = 1;
            printf("\n ERRO: Máximo de 14 caracteres!");
        }

    }while(erro == 1);
}

int leia_adocao(Tutor *tutor) { //recebe como parâmetro o id do adotante para facilitar a manipulação de dados

    int existe = 0;

    for(int i = 0; i < NUM_MAX_CAD; i++){ //verificação para ver se existem gatos disponiveis para adoção
        if(gatos[i].ocupado == 1 && gatos[i].status == 1){
            existe = 1;
            break;
        }
    }

    if(existe == 0){
        printf("\nERRO: Não existem gatos disponíveis para adoção!");
        return 0;
    }

    printf("\n--- GATOS DISPONÍVEIS PARA ADOÇÃO ---\n");

    for(int i = 0; i < NUM_MAX_CAD; i++) {

        // status == 1 significa disponível
        if(gatos[i].ocupado == 1 && gatos[i].status == 1) {

            printf("\nID: %d",
                gatos[i].id_gato);

            printf(" | Microchip: %d",
                gatos[i].microchip);

            printf(" | Nome: %s",
                gatos[i].nome_gato);

            printf(" | Sexo: %c",
                gatos[i].sexo_gato);

            printf("\n------------------------------------");
        }
    }

    int id_escolhido;

    printf("\nDigite o ID do gato que sera adotado por este tutor: ");
    fflush(stdin);
    scanf("%d", &id_escolhido);



    for(int i = 0; i < NUM_MAX_CAD; i++) {

        if(gatos[i].ocupado == 1 && gatos[i].id_gato == id_escolhido && gatos[i].status == 1) {

            time_t agora = time(NULL);
            struct tm *data = localtime(&agora);
            strftime(gatos[i].data_adocao, 11, "%d/%m/%Y", data);

            // marca como adotado
            gatos[i].status = 0;
            gatos[i].id_adotante = (*tutor).id_tutor; //salva o id do adotante na struct do gato

            printf("\nGato '%s' adotado com sucesso!", gatos[i].nome_gato);
            return 1;
        }
    }
        printf("\nERRO: Gato não encontrado ou já adotado!");
        return 0;
}


/*--------------- FUNCOES DE CADASTRO ----------------------*/

void cadastrar_gato() {
    // Criamos uma variável do tipo da sua Struct Gato para agrupar os dados
    Gato novo_gato;

    // Inicializa campos de controle da struct
    novo_gato.ocupado = 1;
    novo_gato.status = 1; // Ativo no sistema

    time_t agora = time(NULL);
    struct tm *data = localtime(&agora);
    strftime(novo_gato.data_cadastro, 11, "%d/%m/%Y", data);

    printf("--- CADASTRO DE GATO ---");

    printf("\nDigite o numero do Microchip (Apenas numeros): ");
    scanf("%d", &novo_gato.microchip);

    // Limpa o buffer do teclado de forma segura
    fflush(stdin);

    //FUNÇÃO UNIVERSAL DE STRING (Nome)
    leia_string(novo_gato.nome_gato, "\nDigite o nome: ");

    //FUNÇÃO UNIVERSAL DE SEXO
    leia_sexo(&novo_gato.sexo_gato);

    if (novo_gato.sexo_gato == 'F') {
        printf("Sexo cadastrado com sucesso: Feminino\n");
    } else {
        printf("Sexo cadastrado com sucesso: Masculino\n");
    }

    //FUNÇÃO DE STRING PARA PELAGEM E LAR TEMPORÁRIO
    leia_string(novo_gato.pelagem, "\nDigite a pelagem: ");

    leia_string(novo_gato.lar_temporario, "\nDigite o lar temporario: ");

    //FUNÇÃO UNIVERSAL BOOLEANA (Castrado)
    leia_booleano(&novo_gato.castrado, "O gato ja foi castrado?");

    //FUNÇÃO BOOLEANA (Vacinas)
    leia_booleano(&novo_gato.vacina, "O gato possui TODAS as vacinas em dia?");

    if(novo_gato.vacina == 0) {
        // Se não está em dia, chama a sua função de pendências
        leia_pendencias(novo_gato.vacina_pendente);
    } else {
        strcpy(novo_gato.vacina_pendente, "Nenhuma");
    }

    int posicao = -1;

    for(int i = 0; i < NUM_MAX_CAD; i++){ //caso exclua algum gato, esse for funciona para repor o suposto id perdido

        if(gatos[i].ocupado == 0){
            posicao = i;
            break;
        }
    }

    //if para ver se o cadastro esta lotado ou nao
    if(posicao == -1){
    printf("\nERRO: Limite maximo de cadastros atingido!");
    return;
    }

    novo_gato.id_gato = posicao + 1;
    gatos[posicao] = novo_gato;
    qtd_gatos++;

    printf("\nData de cadastro: %s\n", novo_gato.data_cadastro);

    printf("\n=========================================");
    printf("\n*** SUCESSO: Felino '%s' gravado no banco de dados! ***\n", novo_gato.nome_gato);

}

void cadastrar_tutor(){
    Tutor novo_tutor;

    // Inicializa campos de controle da struct
    novo_tutor.ocupado = 1;

    printf("--- CADASTRO DE TUTOR E ADOCAO ---");

    leia_cpf(novo_tutor.cpf); //após ler cpf, verificação para ver o a pessoa ja esta cadastrada no sistema ou não

    int cadastro_existe = 0, posicao_cadastrado = -1;

    for(int i = 0; i < NUM_MAX_CAD; i++){
        if(tutores[i].ocupado == 1 && strcmp(novo_tutor.cpf, tutores[i].cpf) == 0){
            cadastro_existe = 1;
            posicao_cadastrado = i;
            break;
        }
    }

    if(cadastro_existe == 1){ //adoção para cadastro ja existente

        if(leia_adocao(&tutores[posicao_cadastrado]) == 1){
        printf("\n*** SUCESSO: Adoção concluída para o tutor já existente %s! ***", tutores[posicao_cadastrado].nome_tutor);
        }
        else{
            printf("\nErro! Cadastro não realizado!");
        }
    }
    else{
        leia_string(novo_tutor.nome_tutor, "\nDigite o nome: "); //adoção para cadastro não realizado

        leia_idade(&novo_tutor.idade);

        leia_email(novo_tutor.email);

        leia_telefone(novo_tutor.telefone);

        int posicao = -1;

        for(int i = 0; i < NUM_MAX_CAD; i++){ //caso exclua algum tutor, esse for funciona para repor o suposto id perdido

            if(tutores[i].ocupado == 0){
                posicao = i;
                break;
            }
        }

        //if para ver se o cadastro esta lotado ou nao
        if(posicao == -1){
        printf("\nERRO: Limite máximo de cadastros atingido!");
        return;
        }

        novo_tutor.id_tutor = posicao + 1;

        if(leia_adocao(&novo_tutor) == 1){
        tutores[posicao] = novo_tutor;
        qtd_tutores++;
        printf("\n*** SUCESSO: Tutor %s cadastrado e Adoção concluída! ***", novo_tutor.nome_tutor);
        }
        else{
            printf("\nErro! Cadastro não realizado!");
        }
    }
}

/*------------------- FUNCOES DE CONSULTA ---------------------*/

void mostrar_todos_gatos(){

    int achou = 0;

    for(int i = 0; i < NUM_MAX_CAD; i++) {

        if(gatos[i].ocupado == 1){
            achou = 1;

            printf("\n[MICROCHIP: %d]",
            gatos[i].microchip);

            printf(" NOME: %s",
            gatos[i].nome_gato);

            printf(" | SEXO: %c",
            gatos[i].sexo_gato);

            printf(" | PELAGEM: %s",
            gatos[i].pelagem);

            printf(" | ENTRADA: %s",
            gatos[i].data_cadastro);

            // Verifica o status e imprime a situação
            if(gatos[i].status == 1) {
                printf(" | STATUS: Disponivel");
            }
            else{
                printf(" | STATUS: Adotado");
            }
            printf("\n-----------------------------------------------");
        }
    }

    if(achou == 0){
        printf("\nNenhum registro encontrado.");
    }
}

void mostrar_gatos_disponiveis(){

    int achou = 0;

    for(int i = 0; i < NUM_MAX_CAD; i++) {

        if(gatos[i].ocupado == 1 && gatos[i].status == 1) {
            achou = 1;

            printf("\n[MICROCHIP: %d]",
            gatos[i].microchip);

            printf(" NOME: %s",
            gatos[i].nome_gato);

            printf(" | SEXO: %c",
            gatos[i].sexo_gato);

            printf(" | PELAGEM: %s",
            gatos[i].pelagem);

            printf(" | ENTRADA: %s",
            gatos[i].data_cadastro);

            printf(" | STATUS: Disponivel");

            printf("\n----------------------------------------------");
        }
    }

    if(achou == 0) {
        printf("\nNenhum registro encontrado.");
    }
}

void mostrar_gatos_adotados(){

    int achou = 0;

    for(int i = 0; i < NUM_MAX_CAD; i++) {

        if(gatos[i].ocupado == 1 && gatos[i].status == 0) {
            achou = 1;

            printf("\n[MICROCHIP: %d]",
            gatos[i].microchip);

            printf(" NOME: %s",
            gatos[i].nome_gato);

            printf(" | SEXO: %c",
            gatos[i].sexo_gato);

            printf(" | PELAGEM: %s",
            gatos[i].pelagem);

            printf(" | ENTRADA: %s",
            gatos[i].data_cadastro);

            printf(" | STATUS: Adotado");
            printf(" | ADOTADO EM: %s", gatos[i].data_adocao);

            printf("\n----------------------------------------------");
        }
    }

    if(achou == 0) {
        printf("\nNenhum registro encontrado.");
    }
}


/*------------------ FUNÇÕES DE EXCLUSÃO ----------------------*/

void excluir_gato(){
    int existe = 0, id_exclusao, escolha, encontrado = 0;

    for(int i = 0; i < NUM_MAX_CAD; i++){ //verificação para ver se existem gatos disponiveis para adoção
        if(gatos[i].ocupado == 1){
            existe = 1;
            break;
        }
    }

    if(existe == 0){
        printf("\nERRO: Não existem gatos disponíveis para exclusão!");
        return;
    }

   printf("\n--- GATOS DISPONÍVEIS PARA EXCLUSÃO ---\n");

    for(int i = 0; i < NUM_MAX_CAD; i++) {

        // ocupado == 1 mostrar apenas os que existem
        if(gatos[i].ocupado == 1) {

            printf("\nID: %d",
                gatos[i].id_gato);

            printf(" | Microchip: %d",
                gatos[i].microchip);

            printf(" | Nome: %s",
                gatos[i].nome_gato);

            printf(" | Sexo: %c",
                gatos[i].sexo_gato);

            printf("\n------------------------------------");
        }
    }

    printf("\nDigite o ID do gato que você deseja excluir: ");
    fflush(stdin);
    scanf("%d", &id_exclusao);

    for(int i = 0; i < NUM_MAX_CAD; i++){ //exclusão real

        if(gatos[i].ocupado == 1 && id_exclusao == gatos[i].id_gato){

            encontrado = 1;
            printf("\nVocê tem certeza que deseja excluir o gato %s dos registros?", gatos[i].nome_gato);
            leia_booleano(&escolha, "");

            if(escolha == 1){
                gatos[i].ocupado = 0; //desocupa a posição do gato == excluir

                if(gatos[i].status == 0){ //verifica se o gato tem algum registro de adoção e exclui se tiver

                    int pos_tutor = gatos[i].id_adotante - 1;

                    tutores[pos_tutor].ocupado = 0;
                    printf("\nGato %s e tutor %s excluído com sucesso!", gatos[i].nome_gato, tutores[pos_tutor].nome_tutor);
                }
                else{
                    printf("\nGato %s excluído com sucesso!", gatos[i].nome_gato);
                }
            }
            else{
                printf("\nO gato %s não foi excluido!", gatos[i].nome_gato);
            }

            break; //acaba com o laço
        }
    }

    if(encontrado == 0){ //se não achar o id
    printf("\nERRO: ID não encontrado!");
    }

}
