class Endereco:

    def __init__(self):
        self.__id_endereco = -1
        self.__rua = "NONE"
        self.__num = "NONE"
        self.__cidade = "NONE"
        self.__cep = "NONE"
        self.__telefone = "NONE"

    def fromList(self, lista):
        self.__rua = lista[0]
        self.__num = lista[1]
        self.__cidade = lista[2]
        self.__cep = lista[3]
        self.__telefone = lista[4]
        return self

    def getAllAtt(self):
        t = (
            self.__id_endereco,
            self.__rua,
            self.__num,
            self.__cidade,
            self.__cep,
            self.__telefone
        )
        return t

    def setId(self, _id):
        self.__id_endereco = _id

    def asDict(self):
        return {
            '_id': self.__id_endereco,
            'rua': self.__rua,
            'num': self.__num,
            'cidade': self.__cidade,
            'cep': self.__cep,
            'telefone': self.__telefone
        }

    def __repr__(self):
        return f'{self.__id_endereco}: {self.__rua}, {self.__num}, {self.__cidade}, {self.__cep}, {self.__telefone}'
