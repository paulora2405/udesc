class Musico:

    def __init__(self):
        self.__num_registro = -1
        self.__nome = "NONE"
        self.__id_endereco = -1

    def fromList(self, lista):
        self.__nome = lista[0]
        self.__id_endereco = lista[1]
        return self

    def getAllAtt(self):
        t = (
            self.__num_registro,
            self.__nome,
            self.__id_endereco
        )
        return t

    def setId(self, _id):
        self.__num_registro = _id

    def asDict(self):
        return {
            "_id": self.__num_registro,
            "nome": self.__nome,
            "id_endereco": self.__id_endereco
        }

    def __repr__(self):
        return f'{self.__num_registro}: {self.__nome}, {self.__id_endereco}'
