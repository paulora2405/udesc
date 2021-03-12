class Musico_Instrumento:

    def __init__(self):
        self.__num_registro = -1
        self.__cod_instrumento = -1

    def fromTupla(self, tupla):
        self.__num_registro = tupla[0]
        self.__cod_instrumento = tupla[1]
        return self

    def num_registro(self, num_registro):
        self.__num_registro = num_registro
        return self

    def cod_instrumento(self, cod):
        self.__cod_instrumento = cod
        return self

    def getNumRegistro(self):
        return self.__num_registro

    def getCodInstrumento(self):
        return self.__cod_instrumento

    def getAllAtt(self):
        t = (
            self.__num_registro,
            self.__cod_instrumento
        )
        return t

    def __repr__(self):
        return f'{self.__num_registro}, {self.__cod_instrumento}'
