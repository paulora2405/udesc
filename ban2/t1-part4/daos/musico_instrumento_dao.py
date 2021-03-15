from connection import Connection
from tables import Musico_Instrumento


class Musico_InstrumentoDAO:

    def __init__(self) -> None:
        self.__sqlSelectAll = 'select * from musico_instrumento'
        self.__sqlCheckReg = 'select count(num_registro) from musico where num_registro = {}'
        self.__sqlCheckCod = 'select count(cod_instrumento) from instrumento where cod_instrumento = {}'
        self.__sqlInsert = "insert into musico_instrumento values ({}, {})"

    def selectAll(self):
        con = Connection()
        cursor = con.cursor()
        cursor.execute(self.__sqlSelectAll)
        resul = cursor.fetchall()
        musicos_instrumentos = []
        for i in resul:
            musicos_instrumentos.append(
                Musico_Instrumento().fromTupla(i))

        return musicos_instrumentos

    def checkConstraints(self, musico_instrumento):
        con = Connection()
        cursor = con.cursor()
        cursor.execute(self.__sqlCheckReg.format(
            musico_instrumento.getAllAtt[0]))
        resul = cursor.fetchone()
        if int(resul[0]) == 0:
            return 'Este num_registro não existe'

        cursor.execute(self.__sqlCheckCod.format(
            musico_instrumento.getAllAtt[1]))
        resul = cursor.fetchone()
        if int(resul[0]) == 0:
            return 'Este cod_instrumento não existe'

        return None

    def insertMusico_Instrumento(self, musico_instrumento):
        ret = self.checkConstraints(musico_instrumento)
        if ret is not None:
            return ret

        con = Connection()
        cursor = con.cursor()
        sql = self.__sqlInsert.format(*musico_instrumento.getAllAtt())
        print(sql)
        cursor.execute(sql)
        con.commit()

        return None
