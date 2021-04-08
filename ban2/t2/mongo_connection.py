import pymongo
from pymongo import MongoClient

client = MongoClient("mongodb://localhost:27017/")

my_database = client['myFirstDatabase']
