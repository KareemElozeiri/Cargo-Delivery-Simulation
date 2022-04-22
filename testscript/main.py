import random

####################Notice:
#This isn't a clean code. Never try to understand this.

file = open('testfile.txt','w')

cargo_types = ['N','N','N','S','V','V']

def preparationEvent(id):
    r = random.randint(0,5)
    type = cargo_types[r]
    hours = [random.randint(1,7),random.randint(8,16),random.randint(17,23)]
    date = f'{((i-1)//3)+1}:{hours[(i-1)%3]}'
    dist = (random.randint(100,2000)//10)*10
    lt = random.randint(1,4)
    cost = (random.randint(100,2000)//10)*10

    return f"R\t{type}\t{date}\t{id}\t{dist}\t{lt}\t{cost}"

def cancellationEvent():
    hours = [random.randint(1, 7), random.randint(8, 16), random.randint(17, 23)]
    date = f'{((i - 1) // 3) + 1}:{hours[(i - 1) % 3]}'
    return f"X\t\t{date}\tID"

def promotionalEvent():
    money = (random.randint(100,2000)//10)*10
    hours = [random.randint(1, 7), random.randint(8, 16), random.randint(17, 23)]
    date = f'{((i - 1) // 3) + 1}:{hours[(i - 1) % 3]}'
    return f"P\t\t{date}\tID\t{money}"

id = 0
for i in range(1,101):
    r = random.randint(1,10)
    line=''
    if(r==9):
        line = promotionalEvent()
    elif(r==10):
        line = cancellationEvent()
    else:
        id+=1
        line = preparationEvent(id)

    file.write(f"{line}\n")

