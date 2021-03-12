from connection import Connection
from tables import Instrumento


class InstrumentoDAO:

    def __init__(self) -> None:
        self.__sqlSelectAll = 'select * from instrumento'
        self.__sqlCheckIdInst = 'select count(id_instrumento) from instrumento where id_instrumento = {}'
        self.__sqlInsert = "insert into instrumento values ({}, '{}')"

    def selectAll(self):
        con = Connection()
        cursor = con.cursor()
        cursor.execute(self.__sqlSelectAll)
        resul = cursor.fetchall()
        instrumentos = []
        for i in resul:
            instrumentos.append(Instrumento().fromTupla(i))

        return instrumentos

    def checkConstraints(self, instrumento):
        con = Connection()
        cursor = con.cursor()
        cursor.execute(self.__sqlCheckIdInst.format(
            instrumento.__id_instrumento))
        resul = cursor.fecthone()
        if int(resul) > 0:
            return 'Este id_instrumento já existe'
        return None

    def insertInstrumento(self, instrumento):
        ret = self.checkConstraints(instrumento)
        if ret is not None:
            return ret

        con = Connection()
        cursor = con.cursor()
        sql = self.__sqlInsert.format(*instrumento.getAllAtt())
        print(sql)
        cursor.execute(sql)
        con.commit()

        return None
