class Produtor:

    def __init__(self):
        self.__id_produtor = -1
        self.__nome = ""

    def fromTupla(self, tupla):
        self.__id_produtor = tupla[0]
        self.__nome = tupla[1]
        return self

    def nome(self, nome):
        self.__nome = nome
        return self

    def id_produtor(self, id):
        self.__id_produtor = id
        return self

    def getNome(self):
        return self.__nome

    def getIdProdutor(self):
        return self.__id_produtor

    def getAllAtt(self):
        t = (
            self.__id_produtor,
            self.__nome
        )
        return t

    def __repr__(self):
        return f'{self.__id_produtor}: {self.__nome}'
