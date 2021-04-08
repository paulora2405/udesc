from mongo_connection import my_database
from tables import Banda


class BandaDAO:

    last_id = 0

    def __init__(self):
        self.col = my_database["Banda"]
        BandaDAO.last_id = self.col.find()
        max_id = 0
        for i in BandaDAO.last_id:
            if max_id < i["_id"]:
                max_id = int(i["_id"])
        BandaDAO.last_id = max_id

    def selectAll(self):
        cursor = self.col.find()
        ret = []
        for doc in cursor:
            ret.append(doc)

        return ret

    def insert(self, instance):
        BandaDAO.last_id += 1
        instance.setId(BandaDAO.last_id)
        self.col.insert_one(instance.asDict())
