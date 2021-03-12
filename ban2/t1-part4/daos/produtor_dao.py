from connection import Connection
from tables import Produtor


class ProdutorDAO:

    def __init__(self) -> None:
        self.__sqlSelectAll = 'select * from produtor'
        self.__sqlCheckIdProd = 'select count(id_produtor) from produtor where id_produtor = {}'
        self.__sqlInsert = "insert into produtor values ({}, '{}')"

    def selectAll(self):
        con = Connection()
        cursor = con.cursor()
        cursor.execute(self.__sqlSelectAll)
        resul = cursor.fetchall()
        produtores = []
        for i in resul:
            produtores.append(Produtor().fromTupla(i))
        con.close()
        return produtores

    def checkConstraints(self, produtor):
        con = Connection()
        cursor = con.cursor()
        cursor.execute(
            self.__sqlCheckIdProd.format(produtor.__id_produtor))
        resul = cursor.fecthone()
        if int(resul) > 0:
            return 'Este id_produtor já existe'
        con.close()
        return None

    def insertProdutor(self, produtor):
        ret = self.checkConstraints(produtor)
        if ret is not None:
            return ret

        con = Connection()
        cursor = con.cursor()
        sql = self.__sqlInsert.format(*produtor.getAllAtt())
        print(sql)
        cursor.execute(sql)
        con.commit()
        con.close()
        return None
