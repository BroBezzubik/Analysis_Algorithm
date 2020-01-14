from random import random
from time import perf_counter

def look_throught(arr, pos, visited, dist=0):
    if len(visited) == len(arr):
        return visited, dist

    min_dist = -1
    min_path = []
    for j in range(0, len(arr)):
        if arr[pos][j] > 0 and j not in visited:
            buf = [j]
            buf.extend(visited)
            new_visited, new_dist = \
                      look_throught(arr, j, buf, dist + arr[pos][j])
            if new_dist != -1 and (min_dist > new_dist or min_dist == -1):
                min_dist = new_dist
                min_path = new_visited

    return min_path, min_dist

def stupid_solver(arr):
    min_dist = -1
    min_path = []
    for i in range(0, len(arr)):
        new_visited, new_dist = look_throught(arr, i, [i])
        if new_dist != -1 and (min_dist > new_dist or min_dist == -1):
            min_dist = new_dist
            min_path = new_visited

    min_path.reverse()
    return min_path, min_dist


def ant_solver(arr, start_f, alpha, beta, ro, lifetime, Q):
    feromon = [[start_f for j in range(len(arr))] for i in range(len(arr))]

    for time in range(lifetime):
        new_path = []
        new_len = []

        for ant in range(len(arr)):
            new_path.append([ant])
            new_len.append(0)
            
            while True:
                where_to_go = []
                for i in range(len(arr)):
                    if i not in new_path[ant] and arr[new_path[ant][-1]][i] > 0:
                        where_to_go.append(i)

                if len(where_to_go) == 0:
                    break
                sum_variants = 0

                #print(where_to_go)
                
                for variant in where_to_go:
                    #print(1 / arr[new_path[ant][-1]][variant])
                    sum_variants += (feromon[new_path[ant][-1]][variant] ** alpha) * \
                                    ((1 / arr[new_path[ant][-1]][variant]) ** beta)

                choice = random()
                choice_var = 0
                while choice > 0:
                    #print(choice, choice_var)
                    choice -= (feromon[new_path[ant][-1]][where_to_go[choice_var]] ** alpha) * \
                              ((1 / arr[new_path[ant][-1]][where_to_go[choice_var]]) ** beta) / sum_variants
                    choice_var += 1
                    if choice_var == len(where_to_go):
                        choice_var -= 1
                        break

                new_len[ant] += arr[new_path[ant][-1]][where_to_go[choice_var]]
                new_path[ant].append(where_to_go[choice_var])                        

        for i in range(len(feromon)):
            for j in range(len(feromon)):
                feromon[i][j] *= (1 - ro)

        #print(new_len)
        #print(new_path)
        for i, ant_path in enumerate(new_path):
            for i in range(1, len(ant_path)):
                #feromon[ant_path[i-1]][ant_path[i]] += Q / new_len[i]
                feromon[ant_path[i-1]][ant_path[i]] += Q / new_len[i] * \
                                                       len(ant_path) / len(arr)

        for i in range(len(feromon)):
            for j in range(len(feromon)):
                feromon[i][j] = max(feromon[i][j], start_f)

    min_len = -1
    min_path = []
    for i, l in enumerate(new_len):
        if len(new_path[i]) == len(arr):
            if min_len == -1 or l < min_len:
                min_len = l
                min_path = new_path[i]

    return min_path, min_len

if __name__ == "__main__":
    arr = [[0, 5, 2, 7, 0],
           [5, 0, 4, 0, 9],
           [2, 4, 0, 4, 10],
           [7, 0, 4, 0, 4],
           [0, 9, 10,4, 0]]

    t_start = perf_counter()
    res1 = stupid_solver(arr)
    t = perf_counter() - t_start
    print(t)
    #ant_solver(arr, start_f, alpha, beta, ro, lifetime, Q):
    #res2 = ant_solver(arr, 1, 0.2, 0.8, 0.5, 100, 5)
    #res2 = ant_solver(arr, 1, 0.8, 0.2, 0.5, 300, 5)
    t_start = perf_counter()
    res2 = ant_solver(arr, 1, 0.5, 0.5, 0.5, 1, 5)
    t = perf_counter() - t_start
    print(t)
