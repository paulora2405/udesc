from connection import Connection
from tables import Musico_Banda


class Musico_BandaDAO:

    def __init__(self) -> None:
        self.__sqlSelectAll = 'select * from musico_banda'
        self.__sqlCheckIdBanda = 'select count(id_banda) from banda where id_banda = {}'
        self.__sqlCheckReg = 'select count(num_registro) from musico where num_registro = {}'
        self.__sqlInsert = "insert into musico_banda values ({}, {})"

    def selectAll(self):
        con = Connection()
        cursor = con.cursor()
        cursor.execute(self.__sqlSelectAll)
        resul = cursor.fetchall()
        musicos_bandas = []
        for i in resul:
            musicos_bandas.append(Musico_Banda().fromTupla(i))

        return musicos_bandas

    def checkConstraints(self, musico_banda):
        con = Connection()
        cursor = con.cursor()
        cursor.execute(self.__sqlCheckIdBanda.format(
            musico_banda.__id_banda))
        resul = cursor.fecthone()
        if int(resul) == 0:
            return 'Este id_banda não existe'

        cursor.execute(self.__sqlCheckReg.format(
            musico_banda.__num_registro))
        resul = cursor.fecthone()
        if int(resul) == 0:
            return 'Este num_registro não existe'

        return None

    def insertMusico_Banda(self, musico_banda):
        ret = self.checkConstraints(musico_banda)
        if ret is not None:
            return ret

        con = Connection()
        cursor = con.cursor()
        sql = self.__sqlInsert.format(*musico_banda.getAllAtt())
        print(sql)
        cursor.execute(sql)
        con.commit()

        return None
