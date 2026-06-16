"""
Simple Graph Visualizer
Reads CSV with comments and multiple edges
"""

import csv
import networkx as nx
import matplotlib.pyplot as plt


def load_graph(filename):
    """Load graph from CSV file"""
    G = nx.MultiDiGraph()  # Use MultiDiGraph for multiple edges

    try:
        with open(filename, 'r', encoding='utf-8') as f:
            lines = [line.strip() for line in f if line.strip()
                     and not line.startswith('#')]

            # Find edges section
            edge_start = 0
            for i, line in enumerate(lines):
                if 'source' in line and 'target' in line:
                    edge_start = i + 1
                    break

            # Parse edges
            for line in lines[edge_start:]:
                parts = line.split(',')
                if len(parts) >= 3:
                    try:
                        source = parts[0].strip()
                        target = parts[1].strip()
                        weight = float(parts[2].strip())
                        G.add_edge(source, target, weight=weight)
                    except ValueError:
                        continue
    except Exception as e:
        print(f"Error: {e}")
        return None

    return G


def visualize(filename):
    """Visualize graph"""
    G = load_graph(filename)

    if not G or G.number_of_nodes() == 0:
        print("No data")
        return

    plt.figure(figsize=(14, 10))

    # Layout
    pos = nx.spring_layout(G, seed=42, k=2)

    # Node size based on degree
    deg = dict(G.degree())
    max_deg = max(deg.values()) if deg else 1
    sizes = [1500 + 500 * (deg[n] / max_deg) for n in G.nodes()]

    # Draw
    nx.draw_networkx_nodes(G, pos, node_size=sizes,
                           node_color='skyblue',
                           edgecolors='black',
                           linewidths=2)

    # Draw edges with different styles for multiple edges
    for u, v, key, d in G.edges(keys=True, data=True):
        rad = 0.1 * key if G.number_of_edges(u, v) > 1 else 0.1
        nx.draw_networkx_edges(G, pos, edgelist=[(u, v)],
                               width=2,
                               edge_color='gray',
                               arrowstyle='->',
                               arrowsize=20,
                               connectionstyle=f'arc3,rad={rad}')

    # Labels
    nx.draw_networkx_labels(G, pos, font_size=12, font_weight='bold')

    # Edge labels
    edge_labels = {}
    for u, v, d in G.edges(data=True):
        key = (u, v)
        if key not in edge_labels:
            edge_labels[key] = []
        edge_labels[key].append(f"{d['weight']:.0f}")

    labels = {k: ','.join(v) for k, v in edge_labels.items()}
    nx.draw_networkx_edge_labels(G, pos, labels,
                                 font_size=9,
                                 font_color='red',
                                 bbox=dict(boxstyle='round,pad=0.2',
                                           facecolor='white',
                                           alpha=0.8))

    plt.title(f'Graph: {G.number_of_nodes()} nodes, {G.number_of_edges()} edges',
              fontsize=14, fontweight='bold')
    plt.axis('off')
    plt.tight_layout()
    plt.savefig('graph.png', dpi=300, bbox_inches='tight')
    plt.show()


if __name__ == "__main__":
    import sys
    filename = sys.argv[1] if len(sys.argv) > 1 else "..\..\..\graph.csv"
    visualize(filename)
