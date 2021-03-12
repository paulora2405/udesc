from connection import Connection
from tables import Endereco


class EnderecoDAO:

    def __init__(self) -> None:
        self.__sqlSelectAll = 'select * from endereco'
        self.__sqlCheckIdEnd = 'select count(id_endereco) from endereco where id_endereco = {}'
        self.__sqlInsert = "insert into endereco values ({}, '{}', '{}', '{}', '{}', '{}')"

    def selectAll(self):
        con = Connection()
        cursor = con.cursor()
        cursor.execute(self.__sqlSelectAll)
        resul = cursor.fetchall()
        enderecos = []
        for i in resul:
            enderecos.append(Endereco().fromTupla(i))

        return enderecos

    def checkConstraints(self, endereco):
        con = Connection()
        cursor = con.cursor()
        cursor.execute(self.__sqlCheckIdEnd.format(
            endereco.__id_endereco))
        resul = cursor.fecthone()
        if int(resul) > 0:
            return 'Este id_endereco já existe'
        return None

    def insertEndereco(self, endereco):
        ret = self.checkConstraints(endereco)
        if ret is not None:
            return ret

        con = Connection()
        cursor = con.cursor()
        # unpacking all attributes from a tuple
        sql = self.__sqlInsert.format(*endereco.getAllAtt())
        print(sql)
        cursor.execute(sql)
        con.commit()

        return None
