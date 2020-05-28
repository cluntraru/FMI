import hashlib, struct
 
# Submit input
ver = 0x20400000
prev_block = "00000000000000000006a4a234288a44e715275f1775b77b2fddb6c02eb6b72f"
mrkl_root = "2dc60c563da5368e0668b81bc4d8dd369639a1134f68e425a9a74e428801e5b8"
time_ = 0x5DB8AB5E
bits = 0x17148EDF

# Test input
#ver = 0x3fff0000
#prev_block = "0000000000000000000140ac4688aea45aacbe7caf6aaca46f16acd93e1064c3"
#mrkl_root = "422458fced12693312058f6ee4ada19f6df8b29d8cac425c12f4722e0dc4aafd"
#time_ = 0x5E664C76
#bits = 0x17110119
 
# https://en.bitcoin.it/wiki/Difficulty
exp = bits >> 24
mant = bits & 0xffffff
target_hexstr = '%064x' % (mant * (1<<(8*(exp - 3))))
target_str = target_hexstr.decode('hex')
 
#Submit case 1
#nonce = 3000000000
#maxNonce = 3100000000
#Submit case 2
nonce = 3430787322
maxNonce = 3530787322

# Test
#nonce = 530000000
#maxNonce = 540000000
while nonce < maxNonce:
    header = ( struct.pack("<L", ver) + prev_block.decode('hex')[::-1] +
          mrkl_root.decode('hex')[::-1] + struct.pack("<LLL", time_, bits, nonce))
    hash = hashlib.sha256(hashlib.sha256(header).digest()).digest()
    print nonce, hash[::-1].encode('hex')
    if hash[::-1] < target_str:
        print 'success'
        break
    nonce += 1
