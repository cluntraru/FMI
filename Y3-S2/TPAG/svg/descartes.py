import numpy as np

t = np.arange(-0.9, 0, 0.01) # Ramura stanga
t = np.concatenate((t, np.arange(0, 100, 0.01))) # Bucla
t = np.concatenate((t, np.arange(-1000, -1.01, 0.01))) # Ramura dreapta

# Raza cercului care reprezinta un punct
r = 0.1

print(r"""<svg version="1.1"
     baseProfile="full"
     width="20" height="20">""")

# Alegem a = 1
for tVal in t:
    x = 3 * tVal / (1 + tVal * tVal * tVal) + 10
    y = 20 - (3 * tVal * tVal / (1 + tVal * tVal * tVal) + 10)
    print("\t<circle cx=\"" + str(x) + "\" cy=\"" + str(y) + "\" r=\"" + str(r) + "\"/>")

print("</svg>")
