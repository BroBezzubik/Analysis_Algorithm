import heapq

# формирование списка чисел Леонардо, являющихся размерами куч
# size - размер входного массива для плавной сортировки
# возвращает список чисел Леонардо
def numbersLeonardo(size):
    numbers = [1, 1] # начальные элементы для последовательности чисел Леонардо
    nextNumber = numbers[-1] + numbers[-2] + 1
    while len(numbers) >= 2 and size > nextNumber:
        numbers.append(nextNumber)
        nextNumber = numbers[-1] + numbers[-2] + 1
    numbers.reverse()
    return numbers

# формирование списка куч по числам Леонардо
# data - входной массив данных
# возвращает выходной список с кучами
def doListHeaps(data):
    # формируем список чисел Леонардо для входной последовательности
    leonardoNumbers = numbersLeonardo(len(data))
    # формируем список куч
    listHeaps = [] # финальный список куч
    m = 0 # хвост предыдущей части и начало следующей
    for i in leonardoNumbers:
        if len(data) - m >= i:
            # если оставшаяся нераспределённая часть входного массива данных больше или равна очередному числу Леонардо
            listHeaps.append(data[m : m+i])
            # переходим к оставшейся нераспределённой части
            m += i
    # восстанавливаем свойство кучи для каждой кучи
    for i in listHeaps:
        heapq.heapify(i)
    # так как кучи неубывающие, конечный результат будет заполняться с начала - минимального элемента 
    # до максимального элемента последовательности, то меняем порядок куч на обратный
    listHeaps.reverse()
    return listHeaps

# формирование списка элементов по заданным индексам:
# i - индекс, потомки которого ищутся
# indexes - список индексов
def countIndexes(i, indexes):
    indexes.append(2*indexes[i]+1)
    indexes.append(2*indexes[i]+2)

    return indexes

# формирование подкучи из заданного списка индексов и исходной кучи
# indexPart - список индексов
# heapPart - найденная подкуча
def getList(indexPart, heap):
    heapPart = []
    for i in indexPart:
        if i < len(heap):
            heapPart.append(heap[i])

    return heapPart

# деление кучи на левые и правые подкучи
# heap - куча для деления
# возвращается кортеж из левой и правой подкучи
def heapDivision(heap):
    heapleft = []
    heapright = []
    index = 0
    indexesLeft = [1] # список индексов для элементов левой подкучи
    indexesRight = [2] # список индексов для элементов правой подкучи
    while indexesLeft[-1] < len(heap): 
        # исходя из логики построения куч, левая подкуча никогда не будет меньше правой

        # считаем индексы для левой подкучи
        indexesLeft = countIndexes(index, indexesLeft)

        # считаем индексы для правой подкучи
        indexesRight = countIndexes(index, indexesRight)

        index += 1

    # составляем списки левой и правой подкуч
    heapleft = getList(indexesLeft, heap)
    heapright = getList(indexesRight, heap)

    return heapleft, heapright

# плавная сортировка
# listHeaps - кучи
# возвращает отсортированную последовательность данных
def smoothSort(listHeaps):
    result = []
    while (listHeaps != []):
        # чтобы не писать пустые подкучи
        flag = 0
        # находим минимальный элемент среди корней куч
        min_index = listHeaps.index(min(listHeaps)) # индекс кучи с минимальным корнем
        # меняем его местами с корнем первой кучи
        # запомним корень текущей кучи
        current_root = listHeaps[0][0]
        # и минимальный элемент
        current_min = listHeaps[min_index][0]
        heapq.heapreplace(listHeaps[0], current_min)
        heapq.heapreplace(listHeaps[min_index], current_root)
        # т.к. корень первой кучи будет в дальнейшем удален, размер кучи
        # уменьшится на 1 -> образуются две кучи из его левого и правого поддерева
        if len(listHeaps[0]) > 1:
            heapLeft, heapRight = heapDivision(listHeaps[0])
            flag = 1
        # удаляем корень первой кучи - это минимальный элемент из всех возможных
        minimum = heapq.heappop(listHeaps[0])
        # ставим его в конечную последовательность чисел
        result.append(minimum)
        # удалим первый элемент списка и вставим его ранее полученные поддеревья
        listHeaps.pop(0)
        # добавим две получившиеся кучи в начало всей последовательности куч
        if flag == 1:
            listHeaps.insert(0, heapLeft)
            listHeaps.insert(0, heapRight)
    return result

#print(smoothSort(doListHeaps([9, 3, 1, 0, 2])))
