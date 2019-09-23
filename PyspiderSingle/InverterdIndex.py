class InvererdIndex(object):
    def __init__(self, arg):
        self.index_dict = {}
        for index, line in enumerate(sentences):
            print(index, line)
            for char in line:
                if not char.strip():
                    continue
                if char in index_dict:
                    index_dict[char].add(index)
                else:
                    index_dict[char] = {index}

    def ShowIndex(aim)
        index_list = []
        for letter in aim:
            index_list.append(index_dict.get(letter,{}))

        common_index=set.intersection(*index_list)
        for index in common_index:
            print(self.sentences[index])

            
