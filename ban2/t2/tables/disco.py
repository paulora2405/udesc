class Disco:

    def __init__(self):
        self.__id_disco = -1
        self.__titulo = ""
        self.__data = ""
        self.__formato = ""
        self.__id_produtor = -1
        self.__id_banda = -1
        self.__num_registro = -1

    def fromTupla(self, tupla):
        self.__id_disco = tupla[0]
        self.__titulo = tupla[1]
        self.__data = tupla[2]
        self.__formato = tupla[3]
        self.__id_produtor = tupla[4]
        self.__id_banda = tupla[5]
        self.__num_registro = tupla[6]
        return self

    def titulo(self, titulo):
        self.__titulo = titulo
        return self

    def id_disco(self, id):
        self.__id_disco = id
        return self

    def data(self, data):
        self.__data = data
        return self

    def formato(self, formato):
        self.__formato = formato
        return self

    def id_produtor(self, id_produtor):
        self.__id_produtor = id_produtor
        return self

    def id_banda(self, id_banda):
        self.__id_banda = id_banda
        return self

    def num_registro(self, num_registro):
        self.__num_registro = num_registro
        return self

    def getTitulo(self):
        return self.__titulo

    def getIdDisco(self):
        return self.__id_disco

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

    def __repr__(self):
        return f'{self.__id_disco}: {self.__titulo}, {self.__data}, {self.__formato}, {self.__id_produtor}, {self.__id_banda}, {self.__num_registro}'
