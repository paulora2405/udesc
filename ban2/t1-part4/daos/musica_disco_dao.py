from connection import Connection
from tables import Musica_Disco


class Musica_DiscoDAO:

    def __init__(self) -> None:
        self.__sqlSelectAll = 'select * from musica_disco'
        self.__sqlCheckIdBanda = 'select count(id_banda) from banda where id_banda = {}'
        self.__sqlCheckIdMusico = 'select count(id_musico) from musico where id_musico = {}'
        self.__sqlInsert = "insert into musica_disco values ({}, {})"

    def selectAll(self):
        con = Connection()
        cursor = con.cursor()
        cursor.execute(self.__sqlSelectAll)
        resul = cursor.fetchall()
        musicas_discos = []
        for i in resul:
            musicas_discos.append(Musica_Disco().fromTupla(i))
        con.close()
        return musicas_discos

    def checkConstraints(self, musica_disco):
        con = Connection()
        cursor = con.cursor()
        cursor.execute(self.__sqlCheckIdBanda.format(
            musica_disco.__id_banda))
        resul = cursor.fecthone()
        if int(resul) == 0:
            return 'Este id_banda não existe'

        cursor.execute(self.__sqlCheckIdMusico.format(
            musica_disco.__id_musico))
        resul = cursor.fecthone()
        if int(resul) == 0:
            return 'Este id_musico não existe'
        con.close()
        return None

    def insertMusica_Disco(self, musica_disco):
        ret = self.checkConstraints(musica_disco)
        if ret is not None:
            return ret

        con = Connection()
        cursor = con.cursor()
        sql = self.__sqlInsert.format(*musica_disco.getAllAtt())
        print(sql)
        cursor.execute(sql)
        con.commit()
        con.close()
        return None
