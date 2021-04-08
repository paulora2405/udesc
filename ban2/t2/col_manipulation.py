from tables import *
from daos import *
from mongo_connection import my_database

cols = ['Banda', 'Disco', 'Endereco', 'Instrumento', 'Musica', 'Musico']


def listCollections():
    i = 0
    for c in cols:
        print(c, f"({i})", sep="", end="  ")
        i += 1
    print()


def keysListing(col_instance):
    print('Digite os seguintes atributos separados por virgulas:')
    first = True
    for key, v in col_instance.__dict__.items():
        if not first:
            print(key)
        else:
            first = False


def inputAttributes(col_instance):
    keysListing(col_instance)
    att = input()
    att = att.split(',')
    if len(att) != len(col_instance.__dict__.items()) - 1:
        print("Quantidade errada de atributos!")
        return
    try:
        for i in range(len(att)):
            att[i] = att[i].strip(' ')
        new_obj = globals()[
            str(col_instance.__class__.__name__)
        ]().fromList(att)

        return new_obj
    except:
        pass


def insertIntoCollection():
    print("Escolha codigo da coleção a inserir:")
    listCollections()
    i = int(input())
    col_instance = globals()[str(cols[i])]()
    obj = inputAttributes(col_instance)
    globals()[str(cols[i] + "DAO")]().insert(obj)


def viewCollections():
    print("Escolha codigo da coleção a visualizar:")
    listCollections()
    i = int(input())
    docs = globals()[str(cols[i] + "DAO")]().selectAll()
    for doc in docs:
        print(doc)
