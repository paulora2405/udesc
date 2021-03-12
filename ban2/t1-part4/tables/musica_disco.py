class Musica_Disco:

    def __init__(self):
        self.__id_disco = -1
        self.__id_musico = -1

    def fromTupla(self, tupla):
        self.__id_disco = tupla[0]
        self.__id_musico = tupla[1]
        return self

    def id_musico(self, id):
        self.__id_musico = id
        return self

    def id_disco(self, id):
        self.__id_disco = id
        return self

    def getIdDisco(self):
        return self.__id_musico

    def getIdMusico(self):
        return self.__id_disco

    def getAllAtt(self):
        t = (
            self.__id_disco,
            self.__id_musico
        )
        return t

    def __repr__(self):
        return f'{self.__id_disco}, {self.__id_musico}'
