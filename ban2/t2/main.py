from col_manipulation import *


def validCommands():
    print(
        '\nComandos válidos:\n',
        '1- Ver uma tabela\n',
        '2- Inserir em uma tabela\n',
        '0- Sair',
        sep='  ',
    )


if __name__ == "__main__":
    print('Trabalho desenvolvido por Paulo Roberto Albuquerque')
    print("Digite um numero: ", end="")
    while True:
        validCommands()
        i = input()
        if i == '1':
            viewCollections()
        elif i == '2':
            insertIntoCollection()
        elif i == '0':
            exit(0)
        else:
            print('Digite um valor válido')
