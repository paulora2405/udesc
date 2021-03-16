class Musico:

    def __init__(self):
        self.__num_registro = -1
        self.__nome = ""
        self.__id_endereco = -1

    def fromTupla(self, tupla):
        self.__num_registro = tupla[0]
        self.__nome = tupla[1]
        self.__id_endereco = tupla[2]
        return self

    def num_registro(self, num):
        self.__num_registro = num
        return self

    def nome(self, nome):
        self.__nome = nome
        return self

    def id_endereco(self, id):
        self.__id_endereco = id
        return self

    def getNome(self):
        return self.__nome

    def getNumRegistro(self):
        return self.__num_registro

    def getAllAtt(self):
        t = (
            self.__num_registro,
            self.__nome,
            self.__id_endereco
        )
        return t

    def __repr__(self):
        return f'{self.__num_registro}: {self.__nome}, {self.__id_endereco}'
