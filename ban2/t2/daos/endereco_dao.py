from mongo_connection import my_database
from tables import Endereco


class EnderecoDAO:

    last_id = 0

    def __init__(self):
        self.col = my_database["Endereco"]
        EnderecoDAO.last_id = self.col.find()
        max_id = 0
        for i in EnderecoDAO.last_id:
            if max_id < i["_id"]:
                max_id = int(i["_id"])
        EnderecoDAO.last_id = max_id

    def selectAll(self):
        cursor = self.col.find()
        ret = []
        for doc in cursor:
            ret.append(doc)

        return ret

    def insert(self, instance):
        EnderecoDAO.last_id += 1
        instance.setId(EnderecoDAO.last_id)
        self.col.insert_one(instance.asDict())
