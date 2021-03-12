from connection import Connection
from tables import Banda


class BandaDAO:

    def __init__(self) -> None:
        self.__sqlSelectAll = 'select * from banda'
        self.__sqlCheckIdBanda = 'select count(id_banda) from banda where id_banda = {}'
        self.__sqlInsert = "insert into banda values ({}, '{}')"

    def selectAll(self):
        con = Connection()
        cursor = con.cursor()
        cursor.execute(self.__sqlSelectAll)
        resul = cursor.fetchall()
        bandas = []
        for i in resul:
            bandas.append(Banda().fromTupla(i))

        return bandas

    def checkConstraints(self, banda):
        con = Connection()
        cursor = con.cursor()
        cursor.execute(self.__sqlCheckIdBanda.format(banda.__id_banda))
        resul = cursor.fecthone()
        if int(resul) > 0:
            return 'Este id_banda já existe'

        return None

    def insertBanda(self, banda):
        ret = self.checkConstraints(banda)
        if ret is not None:
            return ret

        con = Connection()
        cursor = con.cursor()
        # unpacking all attributes from a tuple
        sql = self.__sqlInsert.format(*banda.getAllAtt())
        print(sql)
        cursor.execute(sql)
        con.commit()

        return None
