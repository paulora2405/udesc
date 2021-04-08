from mongo_connection import my_database
from tables import Instrumento


class InstrumentoDAO:

    last_id = 0

    def __init__(self):
        self.col = my_database["Instrumento"]
        InstrumentoDAO.last_id = self.col.find()
        max_id = 0
        for i in InstrumentoDAO.last_id:
            if max_id < i["_id"]:
                max_id = int(i["_id"])
        InstrumentoDAO.last_id = max_id

    def selectAll(self):
        cursor = self.col.find()
        ret = []
        for doc in cursor:
            ret.append(doc)

        return ret

    def insert(self, instance):
        InstrumentoDAO.last_id += 1
        instance.setId(InstrumentoDAO.last_id)
        self.col.insert_one(instance.asDict())
