from connection import Connection
from tables import Instrumento


class InstrumentoDAO:

    def __init__(self) -> None:
        self.__sqlSelectAll = 'select * from instrumento'
        self.__sqlCheckIdInst = 'select count(cod_instrumento) from instrumento where cod_instrumento = {}'
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
            instrumento.getAllAtt()[0]))
        resul = cursor.fetchone()
        if int(resul[0]) > 0:
            return 'Este cod_instrumento já existe'
        return None

    def insertInstrumento(self, instrumento):
        ret = self.checkConstraints(instrumento)
        if ret is not None:
            return ret

        con = Connection()
        cursor = con.cursor()
        sql = self.__sqlInsert.format(*instrumento.getAllAtt())
        print(f'Executando o seguinte comando: "{sql}"')
        cursor.execute(sql)
        con.commit()

        return None
