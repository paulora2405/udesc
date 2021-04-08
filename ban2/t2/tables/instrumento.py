class Instrumento:

    def __init__(self):
        self.__cod_instrumento = -1
        self.__nome = "NONE"

    def fromList(self, lista):
        self.__nome = lista[0]
        return self

    def getAllAtt(self):
        t = (
            self.__cod_instrumento,
            self.__nome
        )
        return t

    def setId(self, _id):
        self.__cod_instrumento = _id

    def asDict(self):
        return {
            "_id": self.__cod_instrumento,
            "nome": self.__nome
        }

    def __repr__(self):
        return f'{self.__cod_instrumento}: {self.__nome}'
