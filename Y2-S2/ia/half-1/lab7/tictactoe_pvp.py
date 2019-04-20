GOL = '#'


def __str__(matr):
    sir = (" ".join([str(x) for x in matr[0:3]]) + "\n" +
           " ".join([str(x) for x in matr[3:6]]) + "\n" +
           " ".join([str(x) for x in matr[6:9]]) + "\n")

    return sir


def elem_identice(lista):
    '''
    lista contine elementele de pe linie, coloana  sau
     diagonale si verifica daca are doar valori de x
    sau doar valori de 0

    Daca lista contine un castigator, il intoarce pe acesta (x sau 0), altfel intoarce False
    '''
    if lista[0] != GOL and lista[0] == lista[1] and lista[0] == lista[2]:
        return lista[0]

    return False

def final(lista):
    '''
    verifica liniile, coloanele si diagonalele cu ajutorul lui elem_identice si intoarce, dupa caz, castigatorul,
    remiza, sau False
    '''
    matr = matrice_tabla(lista)
    for lin in range(3):
        winner = elem_identice(matr[lin])
        if winner:
            return winner

    for col in range(3):
        curr_col = []
        for lin in range(3):
            curr_col.append(matr[lin][col])

        winner = elem_identice(curr_col)
        if winner:
            return winner

    winner = elem_identice([matr[0][0], matr[1][1], matr[2][2]])
    if winner:
        return winner
    
    winner = elem_identice([matr[0][2], matr[1][1], matr[2][0]])
    if winner:
        return winner

    # If there are no more empty spots, game is a draw. Otherwise, it goes on.
    for lin in matr:
        for elem in lin:
            if elem == GOL:
                return False

    return 'remiza'


def afis_daca_final(stare_curenta):
    final_ans = final(stare_curenta)
    if (final_ans):
        if (final_ans == "remiza"):
            print("Remiza!")
        else:
            print("A castigat " + final_ans)

        return True

    return False


def matrice_tabla(lista):
    return [lista[0:3], lista[3:6], lista[6:9]]


def lista_tabla(matr):
    lista = []
    for i in range(3):
        for j in range(3):
            lista.append(matr[i][j])

    return lista


def mutare(tabla_curenta, symb):
    mat_tabla = matrice_tabla(tabla_curenta)
    x = int(input('X: '))
    y = int(input('Y: '))
    
    while x not in range(3) or y not in range(3) or mat_tabla[x][y] != GOL:
        print('Invalid coordinates, try again:')
        x = int(input('X: '))
        y = int(input('Y: '))

    mat_tabla[x][y] = symb
    tabla_curenta[:] = lista_tabla(mat_tabla)


def main():
    print('Incepe jocul x si 0')

    # initializare jucatori
    raspuns_valid = False
    while not raspuns_valid:
        JMIN = input("Doriti sa jucati cu x sau cu 0? ").lower()
        if (JMIN in ['x', '0']):
            raspuns_valid = True
        else:
            print("Raspunsul trebuie sa fie x sau 0.")
    JMAX = '0' if JMIN == 'x' else 'x'

    # initializare tabla
    tabla_curenta = [GOL] * 9
    print("Tabla initiala")
    print(__str__(tabla_curenta))

    # creare stare initiala
    j_curent = JMIN

    while True:
        print('Now playing: ' + str(j_curent))
        if j_curent == JMIN:
            # muta jucatorul 'x'
            mutare(tabla_curenta, JMIN)

            # afisarea starii jocului in urma mutarii utilizatorului
            print("\nTabla dupa mutarea jucatorului")
            print(__str__(tabla_curenta))

            # testez daca jocul a ajuns intr-o stare finala
            # si afisez un mesaj corespunzator in caz ca da
            if (afis_daca_final(tabla_curenta)):
                break

            # S-a realizat o mutare. Schimb jucatorul cu cel opus
            j_curent = JMAX

        # --------------------------------
        else:  # jucatorul e JMAX
            if j_curent == JMAX:
                # muta jucatorul '0'
                mutare(tabla_curenta, JMAX)

                # afisarea starii jocului in urma mutarii utilizatorului
                print("\nTabla dupa mutarea jucatorului")
                print(__str__(tabla_curenta))

                # testez daca jocul a ajuns intr-o stare finala
                # si afisez un mesaj corespunzator in caz ca da
                if (afis_daca_final(tabla_curenta)):
                    break

                # S-a realizat o mutare. Schimb jucatorul cu cel opus
                j_curent = JMIN


if __name__ == "__main__":
    main()
