import pika


parameters = pika.ConnectionParameters(
    credentials=pika.PlainCredentials(
        'username',
        'password'
    )
)
connection = pika.BlockingConnection(parameters)
channel = connection.channel()


channel.queue_declare(queue='maphello')


def callback(ch, method, properties, body):
    print(" [x] Received %r" % body)


channel.basic_consume(callback,
                      queue='maphello',
                      no_ack=True)

print(' [*] Waiting for messages. To exit press CTRL+C')
channel.start_consuming()
