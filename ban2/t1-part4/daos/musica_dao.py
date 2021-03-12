from connection import Connection
from tables import Musica


class MusicaDAO:

    def __init__(self) -> None:
        self.__sqlSelectAll = 'select * from musica'
        self.__sqlCheckIdMusica = 'select count(id_musica) from musica where id_musica = {}'
        self.__sqlCheckIdBanda = 'select count(id_banda) from banda where id_banda = {}'
        self.__sqlCheckReg = 'select count(num_registro) from musico where num_registro = {}'
        self.__sqlInsert = "insert into musica values ({}, '{}', '{}', {}, {})"
        # check on insert last 2 values are None, cause they are optional

    def selectAll(self):
        con = Connection()
        cursor = con.cursor()
        cursor.execute(self.__sqlSelectAll)
        resul = cursor.fetchall()
        musicas = []
        for i in resul:
            musicas.append(Musica().fromTupla(i))
        return musicas

    def checkConstraints(self, musica):
        con = Connection()
        cursor = con.cursor()
        cursor.execute(
            self.__sqlCheckIdMusica.format(musica.__id_musica))
        resul = cursor.fecthone()
        if int(resul) > 0:
            return 'Este id_musica já existe'

        cursor.execute(
            self.__sqlCheckIdBanda.format(musica.__id_banda))
        resul = cursor.fecthone()
        if int(resul) == 0:
            return 'Este id_banda não existe'

        cursor.execute(self.__sqlCheckReg.format(
            musica.__num_registro))
        resul = cursor.fecthone()
        if int(resul) == 0:
            return 'Este num_registro não existe'

        return None

    def insertMusica(self, musica):
        ret = self.checkConstraints(musica)
        if ret is not None:
            return ret

        con = Connection()
        cursor = con.cursor()
        # unpacking all attributes from a tuple
        sql = self.__sqlInsert.format(*musica.getAllAtt())
        print(sql)
        cursor.execute(sql)
        con.commit()

        return None
