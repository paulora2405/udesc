class Banda:

    def __init__(self):
        self.__id_banda = -1
        self.__nome = "NONE"

    def fromList(self, lista):
        self.__nome = lista[0]
        return self

    def getAllAtt(self):
        t = (
            self.__id_banda,
            self.__nome
        )
        return t

    def setId(self, _id):
        self.__id_banda = _id

    def asDict(self):
        return {
            '_id': self.__id_banda,
            'nome': self.__nome
        }

    def __repr__(self):
        return f'{self.__id_banda}: {self.__nome}'
