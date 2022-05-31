import random

####################Notice:
#This isn't a clean code. Never try to understand this.


cargo_types = ['N','N','N','S','V','V']


def truckerSpeedandCapacity(type):
    speed =random.randint(70,120)
    capacity = random.randint(4,9)

    return f"{type}\t{speed}\t{capacity}"



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

for v in range(2,6+1):
    file = open(f'test{v}.txt','w')
    nt = random.randint(15,23)
    st = random.randint(7,12)
    vt = random.randint(10,27)
    file.write(f"{nt}\t{st}\t{vt}\n")
    file.write(f'1\t9\t8\t7\n')
    for i in range(nt):
        file.write(f'{truckerSpeedandCapacity("N")}\n')
    for i in range(st):
        file.write(f'{truckerSpeedandCapacity("S")}\n')
    for i in range(vt):
        file.write(f'{truckerSpeedandCapacity("V")}\n')
    file.write(f'10\t4\n')
    id = 0
    file.write(f'30\n')
    for i in range(1,31):
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
    file.close()
