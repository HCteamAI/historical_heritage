import osmnx as ox
import networkx as nx


def find_distance_avto(coordinates, file_name):
    result = open(file_name, 'w')
    ox.config(log_console=True, use_cache=True)

    place = 'Belarus'
    mode = 'drive'  # 'drive', 'bike', 'walk'
    graph = ox.graph_from_place(place, network_type=mode)

    for i in range(len(coordinates)):
        for j in range(i + 1, len(coordinates)):
            start_latlng = (float(coordinates[i][1][0]), float(coordinates[i][2][0]))
            end_latlng = (float(coordinates[j][1][0]), float(coordinates[j][2][0]))
            orig_node = ox.get_nearest_node(graph, start_latlng)
            dest_node = ox.get_nearest_node(graph, end_latlng)
            distance = nx.shortest_path_length(graph, orig_node, dest_node)
            result.write("({}<-{})=>nrel_distance:[{}];;".format(coordinates[i][0][0], coordinates[j][0][0], distance) + '\n')
            result.write("({}->{})=>nrel_distance:[{}];;".format(coordinates[i][0][0], coordinates[j][0][0], distance) + '\n')
            print(distance)
            print("----------------------")
    result.close()


if __name__ == '__main__':

    a = '\n'
    file = open("coordinates.txt", 'r')
    tmp = []
    coordinates = []
    count = 0
    for line in file:
        count = count + 1
        tmp.append(line.split())
        if count == 3:
            count = 0
            coordinates.append(tmp)
            tmp = []

    result = open("distances.scs", 'w')
    find_distance_avto(coordinates, "distances.scs")
    file.close()

