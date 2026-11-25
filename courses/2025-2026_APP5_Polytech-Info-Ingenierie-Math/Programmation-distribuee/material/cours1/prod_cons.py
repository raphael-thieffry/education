import threading
import queue
import time

def producer(q):
    for i in range(5):
        print(f"Producer: adding task {i}")
        q.put(i)
        time.sleep(0.5)
    q.put(None)  # Signal d'arrêt

def consumer(q):
    while True:
        item = q.get()
        if item is None:
            break
        print(f"Consumer: processing task {item}")
        time.sleep(1)
        q.task_done()

# Créer la queue partagée
task_queue = queue.Queue()

# Démarrer les threads
p = threading.Thread(target=producer, args=(task_queue,))
c = threading.Thread(target=consumer, args=(task_queue,))

p.start()
c.start()

p.join()
c.join()

print("Done!")
