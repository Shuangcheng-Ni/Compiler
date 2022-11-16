import pydot

menu = {'S':
        {'B1': {'a1': '0', 'B3': {'a3': '0', 'B5': {'b1': '0'}}},
         'B2': {'a2': '0', 'B4': {'b2': '0'}}}
        }


class grammar_tree:
    graph = None

    def __init__(self):
        self.graph = pydot.Dot(graph_type='graph')

    def draw(self, parent_name, child_name):
        edge = pydot.Edge(parent_name, child_name)
        self.graph.add_edge(edge)

    def visit(self, node, parent=None):  # 运用了递归
        for k, v in node.items():
            if isinstance(v, dict):  # 是否是叶子节点
                # We start with the root node whose parent is None
                # we don't want to graph the None node
                if parent:
                    self.draw(parent, k)
                self.visit(v, k)
            else:
                if k != '$':  # 只画非空元素  $代表一个空节点，可删去，或修改为其他
                    self.draw(parent, k)
                # drawing the label using a distinct name
                # self.draw(k, k+'_'+v)   子结点为空  不用画

    def start(self, dic):

        self.visit(dic)
        # 下面二者根据自己需求使用
        self.graph.write_png('GrammarTree.png')  # 最后结果生成png图片格式
        # graph.write_pdf('tree.pdf')  #最后结果生成pdf


if __name__ == "__main__":
    photo_draw = grammar_tree()
    photo_draw.start(menu)
