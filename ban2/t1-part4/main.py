from tables.disco import Disco
from tables.produtor import Produtor
from tables.musico import Musico
from tables.musico_instrumento import Musico_Instrumento
from tables.musico_banda import Musico_Banda
from tables.musica import Musica
from tables.musica_disco import Musica_Disco
from tables.instrumento import Instrumento
from tables.endereco import Endereco
from tables.banda import Banda
from daos import *

tables = [
    'banda',
    'disco',
    'endereco',
    'instrumento',
    'musica_disco',
    'musica',
    'musico_banda',
    'musico_instrumento',
    'musico'
]


def viewTables():
    print(
        '\n\nDigite qual tabela voce deseja consultar:\n',
        'banda(1)',
        'disco(2)',
        'endereco(3)',
        'instrumento(4)',
        'musica_disco(5)',
        'musica(6)',
        'musico_banda(7)',
        'musico_instrumento(8)',
        'musico(9)',
        'produtor(10)',
        'CANCELAR(0)',
        sep=' ',
        end='\n\n'
    )

    def foreach(entrys):
        for entry in entrys:
            print(entry)

    i = input()
    if i == '1':
        entrys = BandaDAO().selectAll()
        foreach(entrys)
    elif i == '2':
        entrys = DiscoDAO().selectAll()
        foreach(entrys)
    elif i == '3':
        entrys = EnderecoDAO().selectAll()
        foreach(entrys)
    elif i == '4':
        entrys = InstrumentoDAO().selectAll()
        foreach(entrys)
    elif i == '5':
        entrys = Musica_DiscoDAO().selectAll()
        foreach(entrys)
    elif i == '6':
        entrys = MusicaDAO().selectAll()
        foreach(entrys)
    elif i == '7':
        entrys = Musico_BandaDAO().selectAll()
        foreach(entrys)
    elif i == '8':
        entrys = Musico_InstrumentoDAO().selectAll()
        foreach(entrys)
    elif i == '9':
        entrys = MusicoDAO().selectAll()
        foreach(entrys)
    elif i == '10':
        entrys = ProdutorDAO().selectAll()
        foreach(entrys)
    elif i == '0':
        pass
    else:
        print('Opção não válida')


def insertValues():
    print(
        '\n\nDigite em qual tabela voce deseja inserir:\n',
        'banda(1)',
        'disco(2)',
        'endereco(3)',
        'instrumento(4)',
        'musica_disco(5)',
        'musica(6)',
        'musico_banda(7)',
        'musico_instrumento(8)',
        'musico(9)',
        'produtor(10)',
        'CANCELAR(0)',
        sep=' ',
        end='\n\t'
    )

    def keysListing(table):
        print(
            'Digite os seguintes atributos separados por virgulas:\n',
            'OBS:',
            'Nenhum campo pode conter vírgulas;',
            'Insira campos em branco com duas virgulas seguidas'
        )
        for key, v in table.__dict__.items():
            print(key)

    def inputAttributes(table):
        attributes = input()
        attributes = attributes.split(',')
        if len(attributes) != len(table.__dict__.items()):
            print('Quantidade errada de atributos!')
            return None
        try:
            for i in range(len(attributes)):
                attributes[i].strip()
            attributes = tuple(attributes)
            new_obj = globals()[table.__class__.__name__](attributes)
            return new_obj
        except:
            return None

    i = input()
    print('\n\n')
    if i == '1':
        table = Banda()
        keysListing(table)
        ret = inputAttributes(table)
        if ret is not None:
            BandaDAO().insertBanda(ret)
    elif i == '2':
        table = Disco()
        keysListing(table)
        ret = inputAttributes(table)
        if ret is not None:
            DiscoDAO().insertDisco(ret)
    elif i == '3':
        table = Endereco()
        keysListing(table)
        ret = inputAttributes(table)
        if ret is not None:
            EnderecoDAO().insertEndereco(ret)
    elif i == '4':
        table = Instrumento()
        keysListing(table)
        ret = inputAttributes(table)
        if ret is not None:
            InstrumentoDAO().insertInstrumento(ret)
    elif i == '5':
        table = Musica_Disco()
        keysListing(table)
        ret = inputAttributes(table)
        if ret is not None:
            Musica_DiscoDAO().insertMusica_Disco(ret)
    elif i == '6':
        table = Musica()
        keysListing(table)
        ret = inputAttributes(table)
        if ret is not None:
            MusicaDAO().insertMusica(ret)
    elif i == '7':
        table = Musico_Banda()
        keysListing(table)
        ret = inputAttributes(table)
        if ret is not None:
            Musico_BandaDAO().insertMusico_Banda(ret)
    elif i == '8':
        table = Musico_Instrumento()
        keysListing(table)
        ret = inputAttributes(table)
        if ret is not None:
            Musico_InstrumentoDAO().insertMusico_Instrumento(ret)
    elif i == '9':
        table = Musico()
        keysListing(table)
        ret = inputAttributes(table)
        if ret is not None:
            MusicoDAO().insertMusico(ret)
    elif i == '10':
        table = Produtor()
        keysListing(table)
        ret = inputAttributes(table)
        if ret is not None:
            ProdutorDAO().insertProdutor(ret)
    elif i == '0':
        pass
    else:
        print('Opção não válida')


def testes():
    dao = BandaDAO()
    bandas = dao.selectAll()
    for banda in bandas:
        print(banda)


def validCommands():
    print(
        '\nComandos válidos:\n',
        '1- Ver uma tabela\n',
        '2- Inserir em uma tabela\n',
        '3- Testes\n',
        '0- Sair\n',
        sep='  ',
        end=''
    )


if __name__ == "__main__":

    print('Trabalho desenvolvido por Paulo Roberto Albuquerque')

    i = None
    while True:
        validCommands()
        i = input()
        if i == '1':
            viewTables()
        elif i == '2':
            insertValues()
        elif i == '3':
            testes()
        elif i == '0':
            exit(0)
        else:
            print('Digite um valor válido')
