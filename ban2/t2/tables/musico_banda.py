class Musico_Banda:

    def __init__(self):
        self.__id_banda = -1
        self.__num_registro = -1

    def fromTupla(self, tupla):
        self.__id_banda = tupla[0]
        self.__num_registro = tupla[1]
        return self

    def num_registro(self, num_registro):
        self.__num_registro = num_registro
        return self

    def id_banda(self, id):
        self.__id_banda = id
        return self

    def getNumRegistro(self):
        return self.__num_registro

    def getIdBanda(self):
        return self.__id_banda

    def getAllAtt(self):
        t = (
            self.__id_banda,
            self.__num_registro
        )
        return t

    def __repr__(self):
        return f'{self.__id_banda}, {self.__num_registro}'
