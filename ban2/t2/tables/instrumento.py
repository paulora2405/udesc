class Instrumento:

    def __init__(self):
        self.__cod_instrumento = -1
        self.__nome = ""

    def fromTupla(self, tupla):
        self.__cod_instrumento = tupla[0]
        self.__nome = tupla[1]
        return self

    def nome(self, nome):
        self.__nome = nome
        return self

    def cod_instrumento(self, id):
        self.__cod_instrumento = id
        return self

    def getNome(self):
        return self.__nome

    def getCodInstrumento(self):
        return self.__cod_instrumento

    def getAllAtt(self):
        t = (
            self.__cod_instrumento,
            self.__nome
        )
        return t

    def __repr__(self):
        return f'{self.__cod_instrumento}: {self.__nome}'
