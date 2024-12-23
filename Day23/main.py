from collections import defaultdict

graph = defaultdict(list)
with open('names.in', 'r') as file:
    for line in file:
        node_a, node_b = line.strip().split('-')
        graph[node_a].append(node_b)
        graph[node_b].append(node_a)

triangles = {}
for node, neighbors in graph.items():
    if not node.startswith('t'):
        continue
    for i in range(len(neighbors) - 1):
        for j in range(i + 1, len(neighbors)):
            if neighbors[i] in graph[neighbors[j]]:
                triangle = tuple(sorted([node, neighbors[i], neighbors[j]]))
                triangles[triangle] = True

print(len(triangles))

def bron_kerbosch_with_pivot(P, R=None, X=None):
    if R is None: R = []
    if X is None: X = []
    
    if not P and not X:
        yield R
        return
    
    pivot = next(iter(P or X))
    
    for v in [u for u in P if u not in graph[pivot]]:
        yield from bron_kerbosch_with_pivot(
            [u for u in P if u in graph[v]],
            R + [v],
            [u for u in X if u in graph[v]]
        )
        P.remove(v)
        X.append(v)


largest_clique = sorted(bron_kerbosch_with_pivot(list(graph.keys())), key = len)[-1]
print(','.join(sorted(largest_clique)))
