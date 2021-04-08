class Musica:

    def __init__(self):
        self.__id_musica = -1
        self.__nome = "NONE"
        self.__formato = "NONE"
        self.__id_banda = -1
        self.__num_registro = -1

    def fromList(self, lista):
        self.__nome = lista[0]
        self.__formato = lista[1]
        self.__id_banda = lista[2]
        self.__num_registro = lista[3]
        return self

    def getAllAtt(self):
        t = (
            self.__id_musica,
            self.__nome,
            self.__formato,
            self.__id_banda,
            self.__num_registro,
        )
        return t

    def setId(self, _id):
        self.__id_musica = _id

    def asDict(self):
        return {
            "_id": self.__id_musica,
            "nome": self.__nome,
            "formato": self.__formato,
            "id_banda": self.__id_banda,
            "num_registro": self.__num_registro
        }

    def __repr__(self):
        return f'{self.__id_musica}: {self.__nome}, {self.__formato}, {self.__id_banda}, {self.__num_registro}'
