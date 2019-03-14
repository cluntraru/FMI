import collections


def check_terminal(word):
    return len(word) == 1 and (word.islower() or word == '`')


def word_of_code(code):
    return chr(code - gram_size + ord('a') - 1)


def code_of_word(word):
    # code gram_size is epsilon
    return gram_size + ord(word) - ord('a') + 1


def is_code_of_eps(code):
    return code == gram_size


def check_productions_for_split(gram, mat, curr_len, start_pos, split_len):
    for prod_idx in range(gram_size):
        prod_list = gram[prod_idx]
        # we check each production
        for result in prod_list:
            res1, res2 = result
            if res2 == -1:
                continue

            rg_len = curr_len - split_len
            rg_start = start_pos + split_len

            if mat[split_len][start_pos][res1] and mat[rg_len][rg_start][res2]:
                mat[curr_len][start_pos][prod_idx] = True


def cyk(word, gram):
    word_len = len(word)
    gram_len = len(gram)
    # boolean matrix for CYK DP
    mat = [[[False for i in range(gram_len)]
            for j in range(word_len + 1)]
           for k in range(word_len + 1)]

    for curr_list in gram:
        for gram_idx in range(gram_size):
            curr_list = gram[gram_idx]
            for prod in curr_list:
                res1, res2 = prod
                if res2 == -1 and is_code_of_eps(res1):
                    # if the terminal is the null word, then we should be able to
                    # evaporate the production
                    for str_idx in range(word_len + 1):
                        mat[0][str_idx][gram_idx] = True

    for str_idx in range(word_len):
        gram_idx = 0
        for gram_idx in range(gram_size):
            curr_list = gram[gram_idx]
            for prod in curr_list:
                res1, res2 = prod

                if res2 == -1 and word_of_code(res1) == word[str_idx]:
                    # if we only have a terminal on the right of our production and
                    # it is the terminal we are searching for
                    mat[1][str_idx][gram_idx] = True

    for curr_len in range(1, word_len + 1):
        for start_pos in range(word_len - curr_len + 1):
            for split_len in range(1, curr_len + 1):
                check_productions_for_split(gram, mat, curr_len, start_pos, split_len)
            check_productions_for_split(gram, mat, curr_len, start_pos, 0)

    return mat[word_len][0][0]


def check_exist(local_exists, word):
    if word == '':
        return None

    global gram_size
    if word not in local_exists:
        local_exists[word] = gram_size
        gram_size += 1

    return local_exists[word]


# a grammar is an ordered dictionary of lists
# grammar[NT] = [(A1, A2), (a, ), (-1, )]
MAX_GRAMMAR_SIZE = 100
# grammar = collections.OrderedDict()
grammar = [[] for i in range(MAX_GRAMMAR_SIZE)]
#
terminalProds = []
with open("test.in", "rt") as file_in:
    exists = {}
    gram_size = 0
    word = None
    for line in file_in:
        if word is None:
            word = line.rstrip()
            continue

        lf, rg = line.split('->')
        rg = rg.rstrip()
        lf_idx = check_exist(exists, lf)

        if check_terminal(rg):
            terminalProds.append((lf, rg))
        else:
            rg1, rg2 = rg.split(' ')
            rg1_idx = check_exist(exists, rg1)
            rg2_idx = check_exist(exists, rg2)
            # if lf_idx not in grammar:
            #     grammar[lf_idx] = []

            grammar[lf_idx].append((rg1_idx, rg2_idx))

    for prod in terminalProds:
        lf_idx = check_exist(exists, prod[0])
        # if lf_idx not in grammar:
        #     grammar[lf_idx] = []

        grammar[lf_idx].append((code_of_word(prod[1]), -1))

# grammar = sorted(grammar)

print(cyk(word, grammar))
