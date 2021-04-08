class Disco:

    def __init__(self):
        self.__id_disco = -1
        self.__titulo = "NONE"
        self.__data = "NONE"
        self.__formato = "NONE"
        self.__id_produtor = -1
        self.__id_banda = -1
        self.__num_registro = -1

    def fromList(self, lista):
        self.__titulo = lista[0]
        self.__data = lista[1]
        self.__formato = lista[2]
        self.__id_produtor = lista[3]
        self.__id_banda = lista[4]
        self.__num_registro = lista[5]
        return self

    def getAllAtt(self):
        t = (
            self.__id_disco,
            self.__titulo,
            self.__data,
            self.__formato,
            self.__id_produtor,
            self.__id_banda,
            self.__num_registro
        )
        return t

    def setId(self, _id):
        self.__id_disco = _id

    def asDict(self):
        return {
            "_id": self.__id_disco,
            "titulo": self.__titulo,
            "data": self.__data,
            "formato": self.__formato,
            "id_produtor": self.__id_produtor,
            "id_banda": self.__id_banda,
            "num_registro": self.__num_registro
        }

    def __repr__(self):
        return f'{self.__id_disco}: {self.__titulo}, {self.__data}, {self.__formato}, {self.__id_produtor}, {self.__id_banda}, {self.__num_registro}'
