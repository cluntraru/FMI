text = input('Encrypted text')

for i in range(26):
    print("Key " + str(i) + ": ")
    dec = ""
    for ch in text:
        if ch == ' ':
            dec += ' '
            continue
            
        newOrd = (ord(ch) + i - ord('A')) % 26 + ord('A')
        newChr = chr(newOrd)
        dec += newChr
    
    print(dec + "\n\n\n")

