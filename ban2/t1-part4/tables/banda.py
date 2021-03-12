class Banda:

    def __init__(self):
        self.__id_banda = -1
        self.__nome = ""

    def fromTupla(self, tupla):
        self.__id_banda = tupla[0]
        self.__nome = tupla[1]
        return self

    def nome(self, nome):
        self.__nome = nome
        return self

    def id_banda(self, id):
        self.__id_banda = id
        return self

    def getNome(self):
        return self.__nome

    def getIdBanda(self):
        return self.__id_banda

    def getAllAtt(self):
        t = (
            self.__id_banda,
            self.__nome
        )
        return t

    def __repr__(self):
        return f'{self.__id_banda}: {self.__nome}'
