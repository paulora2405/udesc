from connection import Connection
from tables import Disco


class DiscoDAO:

    def __init__(self) -> None:
        self.__sqlSelectAll = 'select * from disco'
        self.__sqlCheckIdDisco = 'select count(id_disco) from disco where id_disco = {}'
        self.__sqlCheckIdProd = 'select count(id_produtor) from produtor where id_produtor = {}'
        self.__sqlCheckIdBanda = 'select count(id_banda) from banda where id_banda = {}'
        self.__sqlCheckReg = 'select count(num_registro) from musico where num_registro = {}'
        self.__sqlInsert = "insert into disco values ({}, '{}', '{}', '{}', {}, {}, {})"

    def selectAll(self):
        con = Connection()
        cursor = con.cursor()
        cursor.execute(self.__sqlSelectAll)
        resul = cursor.fetchall()
        discos = []
        for i in resul:
            discos.append(Disco().fromTupla(i))

        return discos

    def checkConstraints(self, disco):
        con = Connection()
        cursor = con.cursor()
        cursor.execute(self.__sqlCheckIdDisco.format(disco.getAllAtt[0]))
        resul = cursor.fetchone()
        if int(resul[0]) > 0:
            return 'Este id_disco já existe'

        cursor.execute(
            self.__sqlCheckIdProd.format(disco.getAllAtt[4]))
        resul = cursor.fetchone()
        if int(resul[0]) == 0:
            return 'Este id_produtor não existe'

        cursor.execute(
            self.__sqlCheckIdBanda.format(disco.getAllAtt[5]))
        resul = cursor.fetchone()
        # if resul != '':
        if int(resul[0]) == 0:
            return 'Este id_banda não existe'

        cursor.execute(
            self.__sqlCheckReg.format(disco.getAllAtt[6]))
        resul = cursor.fetchone()
        # if resul != '':
        if int(resul[0]) == 0:
            return 'Este num_registro não existe'

        return None

    def insertDisco(self, disco):
        ret = self.checkConstraints(disco)
        if ret is not None:
            return ret

        con = Connection()
        cursor = con.cursor()
        # unpacking all attributes from a tuple
        sql = self.__sqlInsert.format(*disco.getAllAtt())
        print(sql)
        cursor.execute(sql)
        con.commit()

        return None
