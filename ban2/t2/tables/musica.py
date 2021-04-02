class Musica:

    def __init__(self):
        self.__id_musica = -1
        self.__nome = ""
        self.__formato = ""
        self.__id_banda = -1
        self.__num_registro = -1

    def fromTupla(self, tupla):
        self.__id_musica = tupla[0]
        self.__nome = tupla[1]
        self.__formato = tupla[2]
        self.__id_banda = tupla[3]
        self.__num_registro = tupla[4]
        return self

    def nome(self, nome):
        self.__nome = nome
        return self

    def id_musica(self, id):
        self.__id_musica = id
        return self

    def formato(self, formato):
        self.__formato = formato
        return self

    def id_banda(self, id_banda):
        self.__id_banda = id_banda
        return self

    def num_registro(self, num_registro):
        self.__num_registro = num_registro
        return self

    def getNome(self):
        return self.__nome

    def getIdEndereco(self):
        return self.__id_musica

    def getAllAtt(self):
        t = (
            self.__id_musica,
            self.__nome,
            self.__formato,
            self.__id_banda,
            self.__num_registro,
        )
        return t

    def __repr__(self):
        return f'{self.__id_musica}: {self.__nome}, {self.__formato}, {self.__id_banda}, {self.__num_registro}'
