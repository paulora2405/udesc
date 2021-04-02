class Endereco:

    def __init__(self):
        self.__id_endereco = -1
        self.__rua = ""
        self.__num = ""
        self.__cidade = ""
        self.__cep = ""
        self.__telefone = ""

    def fromTupla(self, tupla):
        self.__id_endereco = tupla[0]
        self.__rua = tupla[1]
        self.__num = tupla[2]
        self.__cidade = tupla[3]
        self.__cep = tupla[4]
        self.__telefone = tupla[5]
        return self

    def rua(self, rua):
        self.__rua = rua
        return self

    def id_endereco(self, id):
        self.__id_endereco = id
        return self

    def num(self, num):
        self.__num = num
        return self

    def cidade(self, cidade):
        self.__cidade = cidade
        return self

    def cep(self, cep):
        self.__cep = cep
        return self

    def telefone(self, telefone):
        self.__telefone = telefone
        return self

    def getRua(self):
        return self.__rua

    def getIdEndereco(self):
        return self.__id_endereco

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

    def __repr__(self):
        return f'{self.__id_endereco}: {self.__rua}, {self.__num}, {self.__cidade}, {self.__cep}, {self.__telefone}'
