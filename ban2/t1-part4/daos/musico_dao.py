from connection import Connection
from tables import Musico


class MusicoDAO:

    def __init__(self):
        self.__sqlSelectAll = 'select * from musico'
        self.__sqlCheckReg = 'select count(num_registro) from musico where num_registro = {}'
        self.__sqlCheckIdEnd = 'select count(id_endereco) from endereco where id_endereco = {}'
        self.__sqlInsert = "insert into musico values ({}, '{}', {})"

    def selectAll(self):
        con = Connection()
        cursor = con.cursor()
        cursor.execute(self.__sqlSelectAll)
        resul = cursor.fetchall()
        musicos = []
        for i in resul:
            musicos.append(Musico().fromTupla(i))
        con.close()
        return musicos

    def checkConstraints(self, musico):
        con = Connection()
        cursor = con.cursor()
        cursor.execute(
            self.__sqlCheckReg.format(musico.__num_registro))
        resul = cursor.fecthone()
        if int(resul) > 0:
            return 'Este num_registro já existe'

        cursor.execute(
            self.__sqlCheckIdEnd.format(musico.__id_endereco))
        resul = cursor.fecthone()
        if int(resul) == 0:
            return 'Este id_endereco não existe'
        return None

    def insertMusico(self, musico):
        ret = self.checkConstraints(musico)
        if ret is not None:
            return ret

        con = Connection()
        cursor = con.cursor()
        # unpacking all attributes from a tuple
        sql = self.__sqlInsert.format(*musico.getAllAtt())
        print(sql)
        cursor.execute(sql)
        con.commit()
        con.close()
        return None
